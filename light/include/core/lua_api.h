//
// Created by k on 10/10/19.
//

#ifndef LIGHT_LUA_API_H
#define LIGHT_LUA_API_H

struct lua_State;

namespace light {

    int lua_print(lua_State* L);
    void add_search_path(lua_State *L, const char *name, const char *value);

    int lua_new_system(lua_State *L);
    int lua_new_component(lua_State *L);
    int lua_get_type(lua_State *L);
    int lua_new_entity(lua_State *L);
    int lua_new_entity_value(lua_State *L);
    int lua_set_entity(lua_State *L);

    int lua_column(lua_State* L);
}


#endif //LIGHT_LUA_API_H
