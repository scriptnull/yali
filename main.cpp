#include <iostream>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char* argv[]) {
    try {
        std::cout << "hello world!" << std::endl;
    } catch (...) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}