//
// Created by k on 9/10/19.
//

#include <lua.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <flecs.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

void luajit_test () {
    lua_State *lua = luaL_newstate();
    luaL_openlibs(lua);
    luaL_dofile(lua, "scripts/test.lua");
    lua_close(lua);

    spdlog::info("lua jit test over");
}

void modules_test(int argc, char* argv[]) {
    auto window = new sf::RenderWindow(sf::VideoMode(800, 600), "tester");

    luajit_test();

    ecs_world *world = ecs_init_w_args(argc, argv);

    ImGui::SFML::Init(*window, false);

    auto IO = ImGui::GetIO();
    IO.Fonts->Clear();
    IO.Fonts->AddFontFromFileTTF("assets/fonts/WenQuanYiMicroHei.ttf", 20.f, NULL, IO.Fonts->GetGlyphRangesChineseFull());
    ImGui::SFML::UpdateFontTexture();

    spdlog::info("init over");

    sf::Clock deltaClock;
    while (window->isOpen()) {
        sf::Event event{};
        while(window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window->close();
        }
        auto delta = deltaClock.restart();
        ImGui::SFML::Update(*window, delta);

        ImGui::ShowTestWindow();

        ImGui::Begin("中文测试");
        ImGui::LabelText("","%s", "这是一段简单的文字。");
        ImGui::Button("按钮");
        ImGui::End();

        window->clear();

        ecs_progress(world, delta.asSeconds());
        ImGui::SFML::Render(*window);

        window->display();
    }

    ImGui::SFML::Shutdown();
    ecs_fini(world);

    spdlog::info("app quit");
}

int main (int argc, char* argv[]) {
    modules_test(argc, argv);

    return 0;
}