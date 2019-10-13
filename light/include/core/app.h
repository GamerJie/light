//
// Created by k on 10/10/19.
//

#ifndef LIGHT_APP_H
#define LIGHT_APP_H

#include <memory>
#include <string>
#include <unordered_map>

#include <light.h>

struct ecs_world;
struct lua_State;

namespace sf {
    class Event;
    class Drawable;
    class RenderWindow;
    class RenderTexture;
}

namespace spdlog {
    class logger;
}

namespace light {
    class System;
    class LuaSystem;
    class ResManager;

    LightAPI class App {
    public:
        static App *Instance();

        App(const char *title, int width, int height);
        void Run();

        uint64_t GetType(const char *name);
        uint64_t Register(const char *name, int size);
        uint64_t CreateSystem(System *system, const char* name,int type);
        uint64_t CreateEntity();
        void SetEntity(uint64_t ent, const char *component, int size, void *data);
        uint64_t CreateEntityValue (const char *components, int size, void *data);

        void Draw(sf::Drawable* drawable);

    private:
        void ProcessEvent(sf::Event *event);

    private:
        static App *m_instance;

        lua_State *m_lua;
        ecs_world *m_world;
        ResManager *m_res;
        sf::RenderWindow *m_window;
        std::shared_ptr<spdlog::logger> m_console;
        std::unordered_map<std::string, uint64_t> m_types;

        sf::RenderTexture *m_game;
    };
}


#endif //LIGHT_APP_H
