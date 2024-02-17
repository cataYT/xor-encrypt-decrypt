#include <iostream> // for output / input
#include <windows.h> // for loading xorCpp.dll
#include <string> // for tolower();
#include <limits> // for clearing input buffer, specifically std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// Declare function ptr
typedef std::string (*xorFuncs)(char key, const std::string &strToXor);

int main() {
    // Load the DLL
    HINSTANCE hDLL = LoadLibraryA("xorCpp.dll");
    if (hDLL == NULL) {
        std::cerr << "Failed to load DLL\n";
        return 1;
    }

    // Get pointer to the function xorEncrypt
    xorFuncs xorE = (xorFuncs)GetProcAddress(hDLL, "xorEncrypt");

    // Get pointer to the function xorDecrypt
    xorFuncs xorD = (xorFuncs)GetProcAddress(hDLL, "xorDecrypt");

    // Check if we got the address or not
    if (xorE == NULL || xorD == NULL) {
        std::cerr << "Failed to get function address of xorDecrypt\n";
        return 1;
    }

    // dummy input so that the program doesnt exit as soon as its done, giving user chance to see output
    char _dummy;

    std::cout << "Enter choice (E or e for encrypt and D or d for decrypt): ";
    char input;
    std::cin.get(input); // for getting single char input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    if (tolower(input) == 'e') {
        // Call the function
        std::cout << "Enter key for xor encryption: ";
        char key;
        std::cin.get(key);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter the string for xor encryption: ";
        std::string strToXor;
        std::getline(std::cin, strToXor);
        std::string result = xorE(key, strToXor);
        std::cout << "Encrypted string: " << result << std::endl;
        std::cin.get(_dummy);
    } else if (tolower(input) == 'd') {
        std::cout << "Enter key for xor decryption: ";
        char key;
        std::cin.get(key);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "Enter the string for xor decryption: ";
        std::string strToXor;
        std::getline(std::cin, strToXor);
        std::string result = xorD(key, strToXor);
        std::cout << "Encrypted string: " << result << std::endl;
        std::cin.get(_dummy);
    } else {
        std::cout << "Invalid input, the choices are E or e for encrypting and D or d for decrypting";
        std::cin.get(_dummy);
        exit(1);
    }

    // Free the DLL
    FreeLibrary(hDLL);

    return 0;
}
