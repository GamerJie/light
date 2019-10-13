//
// Created by k on 12/10/19.
//

#ifndef LIGHT_SPRITE_SYSTEM_H
#define LIGHT_SPRITE_SYSTEM_H

#include <core/system.h>

namespace light {
    class SpriteSystem : public System {
    public:
        const char* Init(const char *name) override;

        void Update(ecs_rows_t *rows) override;
    };
}


#endif //LIGHT_SPRITE_SYSTEM_H
