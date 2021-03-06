#ifndef _ELF_DEPENDENCY_H_
#define _ELF_DEPENDENCY_H_

#include <stdexcept>
#include <functional>
#include <set>
#include <string>

class elf_corrupted : public std::runtime_error {
public:
    explicit elf_corrupted() : runtime_error("elf corrupted") {};
};

class ElfDependency {
public:
    explicit ElfDependency(std::function<size_t(void *, size_t)>);

    void scan();

    bool is_dyn;
    int dyn_flags;
    std::string dyn_runpath;
    std::string dyn_rpath;
    std::string so_name;
    std::set<std::string> so_depends;

private:
    template<typename _Ehdr, typename _Shdr, typename _Dyn>
    void scan();

    template<typename T>
    T H(T v) noexcept;

    void must_read(void *, size_t);

    void must_seek(size_t);

    std::string lookup_table(size_t);

    std::function<size_t(void *, size_t)> read;
    size_t current = 0;
    std::string buffer;
    std::string dyn_str_table;
    unsigned char endian;
};

#endif
