//
// Created by k on 9/10/19.
//

#include <tester.h>
#include <core/app.h>
#include <core/components.h>

using namespace light;

int main (int argc, char* argv[]) {
//     modules_test(argc, argv);

    App app("light Example", 1280, 720);

    bool show = false;
    auto window = new ComImWindow;
    window->name = "TestWindow";
    window->size = Vector2f(200, 300);
    auto widget = new ImWidget;
    widget->type = 1;
    widget->text = "text widget";
    window->child.push_back(widget);
    window->show = show;
    app.CreateEntityValue("ComImWindow", sizeof(ComImWindow), window);

    app.Run();

    return 0;
}