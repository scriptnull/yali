#include <iostream>

#include "app/app.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char* argv[]) {
    try {
        auto app = yali::app::create(argc, argv);
        app->run();
    } catch (...) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}