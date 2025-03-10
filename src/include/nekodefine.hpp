#pragma once

constexpr const char *launcherMode = "minecraft"; // Option: `minecraft`. Used in the `launcher` function in core.hpp

// Import the logging module for nerr exceptions , in nerr.hpp
#define nerrImpLoggerModeDefine true

#define NetWorkAuthlibHostDefine "skin.oha.li"

// If true, it means that the definition of NetWorkHostListDefine will be used regardless of the presence of a hostlist file. By default (false), it will attempt to read the hostlist file.
#define UseNetWorkHostListDefine true
// e.g {"api.example.com","api.example.org","" ...}
#define NetWorkHostListDefine {"svc.oha.li/neko"};

// If true, the version number defined by NekoLcCoreVersionDefine will be used; otherwise, attempt the version number in the data/version file will be used.
#define UseNekoLcCoreVersionDefine true
//any string
#define NekoLcCoreVersionDefine "v0.0.1"





using uint_64 =  unsigned long long;
using uint_32 = unsigned int;
using uint_16 = unsigned short;

using int_64 = long long;
using int_32 = int;
using int_16 = short;

using uint = uint_32;

// Define a convenient macro for printing logs
#define FN __FUNCTION__

#define FI __FILE__

#define LI __LINE__