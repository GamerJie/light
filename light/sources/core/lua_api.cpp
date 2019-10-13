//
// Created by k on 10/10/19.
//

#include <lua.hpp>
#include <flecs.h>
#include <spdlog/spdlog.h>

#include <core/app.h>
#include <core/lua_api.h>
#include <core/lua_system.h>

int light::lua_print(lua_State* L) {
    int args = lua_gettop(L);

    char *msg = new char[2048];
    char* temp = new char[1024];
    sprintf(msg, "%s", "");

    for (int i = 1; i <= args; i++) {

        int type = lua_type(L, i);
        switch (type)
        {
            case LUA_TNUMBER:
                sprintf(temp, "%g\t", lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                sprintf(temp, "%s\t", lua_tostring(L, i));
                break;
            case LUA_TTABLE:
                sprintf(temp, "%s", "[table]\t");
                break;
            case LUA_TNIL:
                sprintf(temp, "%s", "[nil]\t");
                break;
            case LUA_TUSERDATA:
                sprintf(temp, "%s", "[userdata]\t");
                break;
            case LUA_TBOOLEAN:
                sprintf(temp, "%s\t", lua_toboolean(L, i) ? "[true]" : "[false]");
                break;
            case LUA_TFUNCTION:
                sprintf(temp, "%s", "[function]\t");
                break;
            case LUA_TTHREAD:
                sprintf(temp, "%s", "[thread]\t");
                break;
            case LUA_TLIGHTUSERDATA:
                sprintf(temp, "[l_userdata]\t");
                break;
            default:
                const void* data = lua_topointer(L, i);
                if (data) {
                    sprintf(temp, "[type %lu]\t", sizeof(typeof(data)));
                } else  sprintf(temp, "[unknowns]\t");
                break;
        }

        sprintf(msg, "%s%s", msg, temp);
    }

    lua_getglobal(L, "name");
    const char* name = luaL_checkstring(L, -1);

    lua_Debug ar;

    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "l", &ar);

    auto console = spdlog::get(name);
    console->info("[{}.lua:{}] {}",name, ar.currentline, msg);

    return 0;
}

void light::add_search_path(lua_State *L, const char *name, const char *value) {
    lua_getglobal(L, "package");
    lua_getfield(L, -1, name);
    const char* old = lua_tostring(L, -1);
    lua_pushstring(L, fmt::format("{};{}", old, value).c_str());
    lua_setfield(L, -3, name);
    lua_pop(L, 2);
}

int light::lua_new_system(lua_State *L) {
    const char* name = luaL_checkstring(L, 1);
    int type = luaL_checkint(L, 2);

    uint64_t ent = App::Instance()->CreateSystem(new LuaSystem, name, type);
    lua_pushinteger(L, ent);
    return 1;
}

int light::lua_new_component(lua_State *L) {
    const char* name = luaL_checkstring(L, 1);
    int size = luaL_checkint(L, 2);

    uint64_t ent = App::Instance()->Register(name, size);
    lua_pushinteger(L, ent);
    return 1;
}

int light::lua_new_entity(lua_State *L) {
    uint64_t ent = App::Instance()->CreateEntity();
    lua_pushinteger(L, ent);
    return 1;
}

int light::lua_get_type(lua_State *L) {
    const char* name = luaL_checkstring(L, 1);

    uint64_t ent = App::Instance()->GetType(name);
    lua_pushinteger(L, ent);
    return 1;
}

int light::lua_column(lua_State* L) {
    auto rows = (ecs_rows_t*)lua_touserdata(L, 1);
    int size = lua_tonumber(L, 2);
    int column = lua_tonumber(L, 3);

    void* ret = _ecs_column(rows, size, column);
    lua_pushlightuserdata(L, ret);
    lua_pushnumber(L, rows->count);

    return 2;
}

typedef struct pos {
    int x;
    int y;
} pos;

int light::lua_new_entity_value(lua_State *L) {
    const char* components = luaL_checkstring(L, 1);
    int size = luaL_checkint(L, 2);
    void * data = (void*)lua_topointer(L, 3);

    uint64_t ent = App::Instance()->CreateEntityValue(components, size, data);
    lua_pushinteger(L, ent);
    return 1;
}

int light::lua_set_entity(lua_State *L) {
    uint64_t ent = luaL_checkint(L, 1);
    const char* component = luaL_checkstring(L, 2);
    int size = luaL_checkint(L, 3);
    void* data = (void*)lua_topointer(L, 4);

    App::Instance()->SetEntity(ent, component, size, data);
}