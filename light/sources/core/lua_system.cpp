//
// Created by k on 10/10/19.
//

#include <lua.hpp>
#include <flecs.h>
#include <spdlog/spdlog.h>

#include <core/lua_system.h>
#include <core/lua_api.h>

using namespace light;

void LuaSystem::Init(const char* name) {
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);

    auto fullname = fmt::format("scripts/systems/{}.lua", name);

    add_search_path(m_lua, "path", "scripts/light/?.lua");

    lua_pushstring(m_lua, name);
    lua_setglobal(m_lua, "name");
    lua_pushcfunction(m_lua, lua_print);
    lua_setglobal(m_lua, "print");

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

    lua_pushcfunction(m_lua, lua_column);
    lua_setglobal(m_lua, "column");

    luaL_dofile(m_lua, fullname.c_str());
    lua_getglobal(m_lua, "init");
    int ret = lua_pcall(m_lua, 0, 0, 0);

    if (ret) {
        const char *data = lua_tostring(m_lua, -1);
        console->error("[{}] [init] {}", name, data);
    }
}

void LuaSystem::Update(ecs_rows_t *rows) {
    lua_getglobal(m_lua, "update");
    lua_pushlightuserdata(m_lua, rows);

    int ret = lua_pcall(m_lua, 1, 0, 0);
    if(ret) {
        console->error("[update] {}", lua_tostring(m_lua, -1));
    }
}