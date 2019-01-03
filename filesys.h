#ifndef FILESYS_H
#define FILESYS_H

//#include <exception>

#include <filesystem>
namespace filesys = std::filesystem;

/* #ifdef _WIN32
    namespace filesys = std::experimental::filesystem;
#else
    #ifdef __unix
        namespace filesys = std::filesystem;
    #else
        std::terminate();
    #endif
    
#endif
*/
#endif