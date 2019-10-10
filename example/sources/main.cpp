//
// Created by k on 9/10/19.
//

#include <tester.h>
#include <core/app.h>

using namespace light;

int main (int argc, char* argv[]) {
    // modules_test(argc, argv);

    App app("light Example", 800, 600);

    app.Run();

    return 0;
}