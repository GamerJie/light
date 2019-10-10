//
// Created by k on 10/10/19.
//

#ifndef LIGHT_LUA_SYSTEM_H
#define LIGHT_LUA_SYSTEM_H

#include <core/system.h>

struct lua_State;

namespace light {
    LightAPI class LuaSystem: public System {
    public:
        void Init(const char *name) override ;
        void Update(ecs_rows_t*) override ;

    private:
        lua_State *m_lua;
    };
}


#endif //LIGHT_LUA_SYSTEM_H
