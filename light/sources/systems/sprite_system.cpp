//
// Created by k on 12/10/19.
//

#include <flecs.h>
#include <SFML/Graphics.hpp>

#include <systems/sprite_system.h>
#include <core/app.h>
#include <core/components.h>
#include <core/res_manager.h>

using namespace light;

const char* SpriteSystem::Init(const char *name) {
    App::Instance()->Register("ComSprite", sizeof(ComSprite));
    App::Instance()->Register("ComTransform", sizeof(ComTransform));
    return "ComSprite, ComTransform";
}

void SpriteSystem::Update(ecs_rows_t *rows) {
    auto sprites = ecs_column(rows, ComSprite, 1);
    auto transforms = ecs_column(rows, ComTransform, 2);
    for (uint32_t i = 0; i < rows->count; ++i) {
        auto texture = ResManager::Instance()->GetTexture(sprites[i].file);
        auto transform = transforms[i];
        if (texture != nullptr) {
            auto sprite = new sf::Sprite(*texture);
            sprite->setPosition(sf::Vector2f(transform.position.x, transform.position.y));
            sprite->setRotation(transform.rotation);
            sprite->setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
        }
    }
}
