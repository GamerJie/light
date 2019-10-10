//
// Created by k on 10/10/19.
//

#include <lua.hpp>
#include <flecs.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <core/app.h>
#include <core/system.h>
#include <core/lua_api.h>
#include <core/lua_system.h>

typedef int TestCom;

light::App* light::App::m_instance = nullptr;

light::App* light::App::Instance() {
    return m_instance;
}

light::App::App(const char *title, int width, int height) {
    if (m_instance != nullptr) {
        spdlog::error("only one App can be create !");
        return;
    }

    m_instance = this;
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    m_world = ecs_init();
    m_console = spdlog::stdout_color_mt("app");

    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);

    add_search_path(m_lua, "path", "scripts/light/?.lua");

    auto fullname = fmt::format("scripts/app.lua");
    lua_pushstring(m_lua, "app");
    lua_setglobal(m_lua, "name");

    lua_pushcfunction(m_lua, lua_print);
    lua_setglobal(m_lua, "print");

    lua_pushcfunction(m_lua, lua_new_component);
    lua_setglobal(m_lua, "component");

    lua_pushcfunction(m_lua, lua_new_system);
    lua_setglobal(m_lua, "system");

    lua_pushcfunction(m_lua, lua_new_entity);
    lua_setglobal(m_lua, "entity");

    lua_pushcfunction(m_lua, lua_get_type);
    lua_setglobal(m_lua, "get_type");

    luaL_dofile(m_lua, fullname.c_str());
    lua_getglobal(m_lua, "main");
    int ret = lua_pcall(m_lua, 0, 0, 0);

    if (ret) {
        m_console->error("[app] [init] {}", lua_tostring(m_lua, -1));
    }

    ImGui::SFML::Init(*m_window);
//    auto IO = ImGui::GetIO();
//    IO.Fonts->Clear();
//    IO.Fonts->AddFontFromFileTTF("assets/fonts/WenQuanYiMicroHei.ttf", 20.f, nullptr, IO.Fonts->GetGlyphRangesChineseFull());
//    ImGui::SFML::UpdateFontTexture();

    Register("TestCom", sizeof(TestCom));
    CreateSystem(new LuaSystem, "test_system", EcsOnSet, "TestCom");
    _ecs_new(m_world, ecs_type_from_entity(m_world, GetType("TestCom")));
}

void light::App::Run() {
    while (m_window->isOpen()) {
        sf::Event event{};
        sf::Clock deltaClock;
        while (m_window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            ProcessEvent(&event);

            auto delta = deltaClock.restart();
            ImGui::SFML::Update(*m_window, delta);

            m_window->clear();
            ecs_progress(m_world, delta.asSeconds());
            ImGui::ShowTestWindow();

            ImGui::SFML::Render();
            m_window->display();
        }
    }

    ImGui::SFML::Shutdown();
}

void light::App::ProcessEvent(sf::Event *event) {
    if (event->type == sf::Event::Closed)
        m_window->close();
}

uint64_t light::App::Register(const char *name, int size) {
    ecs_entity_t ent = ecs_new_component(m_world, name, size);
    m_types[name] = ent;
    m_console->info("register type: [{}]", name);
    return ent;
}

uint64_t light::App::GetType(const char *name) {
    auto iter = m_types.find(name);
    if(iter == m_types.end()) {
        m_console->error("get type failed !");
        return 0;
    }

    return m_types[name];
}

uint64_t light::App::CreateSystem(System *system, const char* name,int type, const char* components) {
    system->console = spdlog::stdout_color_mt(name);
    system->Init(name);

    ecs_entity_t sys = ecs_new_system(m_world, name, (EcsSystemKind)type, components, [](ecs_rows_t *rows){
        auto s = (System*)rows->param;
        s->Update(rows);
    });

    ecs_set_system_context(m_world, sys, system);
    return sys;
}

uint64_t light::App::CreateEntity(const char* id, const char* components) {
    return ecs_new_entity(m_world, id, components);
}

