//
// Created by k on 10/10/19.
//

#ifndef LIGHT_SYSTEM_H
#define LIGHT_SYSTEM_H

#include <memory>

#include <light.h>

struct ecs_rows_t;

namespace spdlog {
    class logger;
}

namespace light {
    LightAPI class System {
    public:
        virtual const char* Init(const char* name){ return ""; };
        virtual void Update(ecs_rows_t *rows) {};

    public:
        bool isLua;
        std::shared_ptr<spdlog::logger> console;
    };
}

#endif //LIGHT_SYSTEM_H
