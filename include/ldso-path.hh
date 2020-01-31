#ifndef _LDSO_PATH_HH_
#define _LDSO_PATH_HH_
#include <string>

struct load_env {
    std::string rpath;
    std::string ld_library_path;
    std::string runpath;
    bool no_default_lib;
};

std::string find_library(const std::string& soname, const load_env& env);
#endif
