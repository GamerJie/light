//
// Created by k on 12/10/19.
//

#ifndef LIGHT_RES_MANAGER_H
#define LIGHT_RES_MANAGER_H

#include <string>
#include <unordered_map>

#include <light.h>

namespace spdlog {
    class logger;
}

namespace sf {
    class Texture;
    class Sprite;
}

namespace light {
    LightAPI class ResManager {
    public:
        static ResManager *Instance();

        ResManager(const char* rootPath);
        sf::Texture *GetTexture(const std::string& name);

    private:
        static ResManager *instance;

        const char* m_root;
        std::shared_ptr<spdlog::logger> m_console;
        std::unordered_map<std::string, sf::Texture*> m_textures;
    };
}

#endif //LIGHT_RES_MANAGER_H
