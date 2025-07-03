#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__APPLE__)
    #include <sys/utsname.h>
#elif defined(__linux__)
    #include <sys/utsname.h>
#endif

std::string getOSInfo() {
    std::string osInfo;
    
    #ifdef _WIN32
        osInfo = "Windows";
        // Get Windows version
        OSVERSIONINFO osvi;
        ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        
        if (GetVersionEx(&osvi)) {
            osInfo += " ";
            osInfo += std::to_string(osvi.dwMajorVersion);
            osInfo += ".";
            osInfo += std::to_string(osvi.dwMinorVersion);
        }
        
    #elif defined(__APPLE__)
        struct utsname uts;
        if (uname(&uts) == 0) {
            osInfo = "macOS";
            osInfo += " (";
            osInfo += uts.release;
            osInfo += ")";
        } else {
            osInfo = "macOS (version detection failed)";
        }
        
    #elif defined(__linux__)
        struct utsname uts;
        if (uname(&uts) == 0) {
            osInfo = "Linux";
            osInfo += " ";
            osInfo += uts.sysname;
            osInfo += " ";
            osInfo += uts.release;
        } else {
            osInfo = "Linux (version detection failed)";
        }
        
    #elif defined(__unix__)
        osInfo = "Unix";
        
    #elif defined(__FreeBSD__)
        osInfo = "FreeBSD";
        
    #else
        osInfo = "Unknown Operating System";
    #endif
    
    return osInfo;
}

std::string getArchitecture() {
    std::string arch;
    
    #ifdef _WIN32
        #ifdef _WIN64
            arch = "x64 (64-bit)";
        #else
            arch = "x86 (32-bit)";
        #endif
    #elif defined(__APPLE__)
        #ifdef __x86_64__
            arch = "x86_64 (64-bit)";
        #elif defined(__arm64__)
            arch = "ARM64 (64-bit)";
        #else
            arch = "Unknown";
        #endif
    #elif defined(__linux__)
        #ifdef __x86_64__
            arch = "x86_64 (64-bit)";
        #elif defined(__i386__)
            arch = "x86 (32-bit)";
        #elif defined(__aarch64__)
            arch = "ARM64 (64-bit)";
        #else
            arch = "Unknown";
        #endif
    #else
        arch = "Unknown";
    #endif
    
    return arch;
}

int main() {
    std::cout << "=== Operating System Detection ===" << std::endl;
    std::cout << "OS: " << getOSInfo() << std::endl;
    std::cout << "Architecture: " << getArchitecture() << std::endl;
    
    // Additional compiler information
    std::cout << "\n=== Compiler Information ===" << std::endl;
    
    #ifdef __GNUC__
        std::cout << "Compiler: GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
    #elif defined(__clang__)
        std::cout << "Compiler: Clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
    #elif defined(_MSC_VER)
        std::cout << "Compiler: Microsoft Visual C++ " << _MSC_VER << std::endl;
    #else
        std::cout << "Compiler: Unknown" << std::endl;
    #endif
    
    #ifdef __cplusplus
        std::cout << "C++ Standard: " << __cplusplus << std::endl;
    #endif
    
    return 0;
} 