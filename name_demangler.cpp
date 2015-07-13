// Name demangler, via StackOverflow
#ifdef __GNUG__

#include <cstdlib>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -1; // some arbitrary value to eliminate the compiler warning

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

#else

// does nothing if not g++
std::string demangle(const char* name) {
    return name;
}

#endif
}
