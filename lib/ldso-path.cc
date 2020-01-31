#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <regex>
#include <sys/stat.h>

struct load_env {
    std::string rpath;
    std::string ld_library_path;
    std::string runpath;
    bool no_default_lib;
};

std::vector<std::string> string_split(const std::string& s, const std::string& r) {
    std::regex re(r);
    return std::vector<std::string>(
        std::sregex_token_iterator(s.begin(), s.end(), re, -1),
        std::sregex_token_iterator());
}

static bool file_exists(const std::string& filename) {
    struct stat buf;
    int err = stat(filename.c_str(), &buf);
    if(err == 0) return true;
    if(errno == ENOENT) return false;
    throw std::runtime_error(strerror(errno));
}

static std::string file_exists_in(const std::vector<std::string>& list, const std::string& filename) {
    for(auto s: list) {
        if(s.empty()) continue;
        if(s.back() != '/') s.push_back('/');
        s += filename;
        if(file_exists(s)) return s;
    }
    return std::string();
}

#ifndef SYSTEM_DIRS
#define SYSTEM_DIRS
#endif
static std::string default_path = { SYSTEM_DIRS ":/lib:/usr/lib"};

std::string find_library(const std::string& soname, const load_env& env) {
    std::string fullpath;
    if(soname.find('/') == std::string::npos) {
        if(env.runpath.empty())
            if(!(fullpath = file_exists_in(string_split(env.rpath, "[:]+"), soname)).empty()) return fullpath;
        if(!(fullpath = file_exists_in(string_split(env.ld_library_path, "[:;]+"), soname)).empty()) return fullpath;
        if(!(fullpath = file_exists_in(string_split(env.runpath, "[:]+"), soname)).empty()) return fullpath;
        if(!env.no_default_lib)
            if(!(fullpath = file_exists_in(string_split(default_path, "[:]+"), soname)).empty()) return fullpath;
    } else {
        if(file_exists(soname)) return soname;
    }
    return std::string();
}
