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
#include <core/components.h>
#include <core/res_manager.h>
#include <systems/imgui/im_window_system.h>

typedef int TestCom;

typedef struct pos {
    int x;
    int y;
} pos;

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
    m_res = new ResManager("./assets/");
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    m_game = new sf::RenderTexture;
    m_game->create(800, 600);


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

    lua_pushcfunction(m_lua, lua_set_entity);
    lua_setglobal(m_lua, "set_entity");

    lua_pushcfunction(m_lua, lua_new_entity_value);
    lua_setglobal(m_lua, "entity_value");

    ImGui::SFML::Init(*m_window);
    auto IO = ImGui::GetIO();
    IO.Fonts->Clear();
    IO.Fonts->AddFontFromFileTTF("assets/fonts/WenQuan.ttf", 20.f, nullptr, IO.Fonts->GetGlyphRangesChineseFull());
    ImGui::SFML::UpdateFontTexture();

    Register("ComWindow", sizeof(ComWindow));
    Register("ComWindowEvent", sizeof(ComWindowEvent));
    Register("ComTransform", sizeof(ComTransform));

    Register("TestCom", sizeof(TestCom));
    CreateSystem(new LuaSystem, "test_system", EcsOnSet);
    _ecs_new(m_world, ecs_type_from_entity(m_world, GetType("TestCom")));

    CreateSystem(new ImWindowSystem, "ImWindowSystem", EcsOnUpdate);

    luaL_dofile(m_lua, fullname.c_str());
    lua_getglobal(m_lua, "main");
    int ret = lua_pcall(m_lua, 0, 0, 0);

    if (ret) {
        m_console->error("[app] [main] {}", lua_tostring(m_lua, -1));
    }
}

void light::App::Run() {
    while (m_window->isOpen()) {
        sf::Event event{};
        sf::Clock deltaClock;
        while (m_window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            ProcessEvent(&event);
        }
        auto delta = deltaClock.restart();
        ImGui::SFML::Update(*m_window, delta);

        m_game->clear(sf::Color(111, 111, 111));
        ecs_progress(m_world, delta.asSeconds());
        m_game->display();

        const sf::Texture &texture = m_game->getTexture();

        // ImGui::ShowTestWindow();

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Engine")) {
            ImGui::MenuItem("About");
            if (ImGui::MenuItem("Exit")) {
                m_window->close();
            }

            ImGui::EndMenu();
        }

        ImGui::MenuItem("▶");
        ImGui::MenuItem("▣");
        ImGui::MenuItem("▶");

        ImGui::EndMainMenuBar();

        ImGui::SetNextWindowContentSize(ImVec2(400, 300));
        ImGui::Begin("Game");
        ImGui::Image(texture, sf::Vector2f(400, 300));
        ImGui::End();

        m_window->clear();
        ImGui::SFML::Render();
        m_window->display();
    }

    ImGui::SFML::Shutdown();
}

void light::App::ProcessEvent(sf::Event *event) {
    if (event->type == sf::Event::Closed)
        m_window->close();

    auto w_event = new ComWindowEvent;
    w_event->type = event->type;

    ecs_entity_t com = GetType("ComWindowEvent");
    ecs_entity_t ent = _ecs_new(m_world, ecs_type_from_entity(m_world, com));
    _ecs_set_ptr(m_world, ent, com, sizeof(ComWindowEvent), w_event);
}

uint64_t light::App::Register(const char *name, int size) {
    auto iter = m_types.find(name);
    if(iter == m_types.end()) {
        ecs_entity_t ent = ecs_new_component(m_world, name, size);
        m_types[name] = ent;
        m_console->info("register type: [{},size: {}, id: {}].now totals: {}", name, size, ent,m_types.size());
        return ent;
    }

    m_console->warn("type: [{}] already registered !", name);
    return -1;
}

uint64_t light::App::GetType(const char *name) {
    auto iter = m_types.find(name);
    if(iter == m_types.end()) {
        m_console->error("get type [{}] failed !, now count: {}", name, m_types.size());
        return -1;
    }

    return m_types[name];
}

uint64_t light::App::CreateSystem(System *system, const char* name,int type) {
    system->console = spdlog::stdout_color_mt(name);

    ecs_entity_t sys = ecs_new_system(m_world, name, (EcsSystemKind)type, system->Init(name), [](ecs_rows_t *rows){
        auto s = (System*)rows->param;
        s->Update(rows);
    });

    ecs_set_system_context(m_world, sys, system);
    return sys;
}

uint64_t light::App::CreateEntity() {
    return _ecs_new(m_world, nullptr);
}

void light::App::SetEntity(uint64_t ent, const char *component, int size, void *data) {
    ecs_entity_t com = GetType(component);
    if (com < 0) return;
    _ecs_set_ptr(m_world, ent, com, size, data);
}

uint64_t light::App::CreateEntityValue(const char *components, int size, void *data) {
    ecs_entity_t ent = _ecs_new(m_world, nullptr);
    _ecs_set_ptr(m_world, ent, GetType(components), size, data);
    return ent;
}

void light::App::Draw(sf::Drawable *drawable) {
    m_game->draw(*drawable);
}



