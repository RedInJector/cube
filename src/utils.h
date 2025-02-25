#ifndef CUBE_UTILS
#define CUBE_UTILS

#include <filesystem>
#ifdef __WIN32
#include <windows.h>
#include <iostream>
#endif

namespace utils {

/**
 * Get absolute path to an object file in ./obj
 *
 * https://stackoverflow.com/questions/1528298/get-path-of-executable
 */
std::filesystem::path getObjPath(std::string filename) {
#ifdef __linux__
    auto p = std::filesystem::canonical("/proc/self/exe");
    auto d = p.parent_path().parent_path().append("obj").append(filename);
    return d;
#endif
#ifdef __WIN32
    //Windows: pass NULL as the module handle to GetModuleFileName.
    std::cout << "Not implemented" << std::endl;
    exit(1);
#endif
}
}  // namespace utils

#endif
