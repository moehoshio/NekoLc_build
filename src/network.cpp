#include "network.hpp"
neko::networkBase::Config neko::networkBase::Dconfig;

namespace neko{
 void networkBase::init(){
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
            "NekoLc /"s + info::getVersion() + "-" + info::getOsNameS(),
            proxy | exec::move,
            Api::hostList[0],
            (dev == true && tls == false) ? "http://"s : "https://"s};

        nlog::Info(FI, LI, "%s :  proxy : %s , dev: %s , tls : %s , protocol : %s , dUseragent : %s ", FN, Dconfig.proxy.c_str(), exec::boolTo<const char *>(dev), exec::boolTo<const char *>(tls), Dconfig.protocol.c_str(), Dconfig.userAgent.c_str());
 }
        
}//namesp neko
