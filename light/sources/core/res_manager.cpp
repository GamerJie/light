//
// Created by k on 12/10/19.
//

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <SFML/Graphics.hpp>

#include <core/res_manager.h>

using namespace light;

ResManager* ResManager::instance = nullptr;

ResManager* ResManager::Instance() {
    return instance;
}

ResManager::ResManager(const char* rootPath) {
    instance = this;
    m_root = rootPath;
    m_console = spdlog::stdout_color_mt("resMgr");

    m_console->info("init root path: {}", m_root);
}

sf::Texture* ResManager::GetTexture(const std::string& name) {
    auto texture = new sf::Texture;
    if (texture->loadFromFile(fmt::format("{}{}", m_root, name))){
        return nullptr;
    }

    m_textures[name] = texture;
    return texture;
}