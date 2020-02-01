#include "elf-dependency.hh"
#include "ldso-path.hh"

#include <dlfcn.h>
#include <elf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

int main(int argc, const char *argv[]) {
    std::cout << std::boolalpha;
    std::string filename;
    bool find_pathname = false;
    switch(argc) {
    case 2:
        filename = argv[1];
        break;
    case 3:
        find_pathname = true;
        filename = argv[2];
        if(argv[1] != std::string("-p"))
            throw std::runtime_error("invalid arguments");
        break;
    default:
        throw std::runtime_error("invalid arguments");
    }
    std::fstream f(filename, std::ios::in | std::ios::binary);
    ElfDependency scanner([&](void *buf, size_t size) -> size_t {
        f.read((char *)buf, size);
        return f.gcount();
    });
    scanner.scan();
    for(const auto& so: scanner.so_depends) {
        if(find_pathname) {
            const char *ld_library_path = secure_getenv("LD_LIBRARY_PATH");
            load_env env {
                .rpath = scanner.dyn_rpath,
                .ld_library_path = ld_library_path? ld_library_path: "",
                .runpath = scanner.dyn_runpath,
                .no_default_lib = scanner.dyn_flags & DF_1_NODEFLIB,
            };
            std::string path = find_library(so, env);
            if(!path.empty())
                std::cout << path << std::endl;
            else
                std::cerr << so << std::endl;
        } else
            std::cout << so << std::endl;
    }
}
