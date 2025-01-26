#include "network.hpp"
neko::networkBase::Config neko::networkBase::Dconfig;

namespace neko{
 auto networkBase::init() -> std::future<void> {
        using namespace std::literals::string_literals;

        std::string proxy = exec::getConfigObj().GetValue("net", "proxy", "true");
        // "" or true or proxyAdd ,otherwise set ""
        bool proxyUnexpected = exec::allTrue((proxy != ""), (proxy != "true"), !exec::isProxyAddress(proxy));
        if (proxyUnexpected)
            proxy = ""s;

        bool
            dev = exec::getConfigObj().GetBoolValue("dev", "enable", false),
            tls = exec::getConfigObj().GetBoolValue("dev", "tls", true);

        networkBase::Dconfig = {
            "NekoLc /"s + info::getVersion(),
            proxy | exec::move,
            Api::hostList[0],
            (dev == true && tls == false) ? "http://"s : "https://"s};

        nlog::Info(FI, LI, "%s :  proxy : %s , dev: %s , tls : %s , protocol : %s , dUseragent : %s ", FN, Dconfig.proxy.c_str(), exec::boolTo<const char *>(dev), exec::boolTo<const char *>(tls), Dconfig.protocol.c_str(), Dconfig.userAgent.c_str());

        return exec::getThreadObj().enqueue([] {
            network net;
            for (auto it : Api::hostList) {

                std::string url = buildUrl(Api::testing, it);
                int retCode;

                decltype(net)::Args args{
                    url.c_str(),
                    nullptr,
                    &retCode};
                std::string id = "testing-"s + it;
                args.id = id.c_str();

                decltype(net)::autoRetryArgs Aargs{args, std::vector<int>{200}, 2, 50};

                if (net.autoRetry(Opt::onlyRequest, Aargs)) {
                    nlog::Info(FI, LI, "%s : testing okay , host : %s , retCode : %d", FN, it, retCode);
                    // neko::networkBase::Dconfig.host = std::string(it);
                    return;
                } else {
                    nlog::Warn(FI, LI, "%s : faild to testing host : %s , now try to the next", FN, it);
                }
            };
            nlog::Err(FI, LI, "%s : Test: No available hosts! End to network test", FN);
            return;
        });
    };
}//namesp neko
