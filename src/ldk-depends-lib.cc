#include "elf-dependency.hh"

#include <iostream>
#include <fstream>

int main(int argc, const char *argv[]) {
    std::cout << std::boolalpha;
    if(argc <= 1) {
        std::cerr << "ERROR: specify an ELF executable as the argument" << std::endl;
        return 1;
    }
    std::fstream f(argv[1], std::ios::in | std::ios::binary);
    ElfDependency scanner([&](void *buf, size_t size) -> size_t {
        f.read((char *)buf, size);
        return f.gcount();
    });
    scanner.scan();
    for(const auto& so: scanner.so_depends) {
        std::cout << so << std::endl;
    }
}
