//
// Created by k on 11/10/19.
//

#ifndef LIGHT_IM_WINDOW_SYSTEM_H
#define LIGHT_IM_WINDOW_SYSTEM_H

#include <core/system.h>

namespace light {
    class ImWindowSystem : public System {
    public:
        const char* Init(const char* name) override;

        void Update(ecs_rows_t *rows) override;
    };
}


#endif //LIGHT_IM_WINDOW_SYSTEM_H
