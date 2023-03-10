#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"

using namespace eng;

void ParallaxPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = 0;
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    sf::Vector2f size{screenSize->x / (1920 / 2), screenSize->y / (1080 / 2)};
    sf::Vector2f size3{screenSize->x / (1920 / 3), screenSize->y / (1080 / 3)};

    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_1, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_0, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_2, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 96, 96), sf::Color::White, sf::Vector2f(size.x / screenSize->x * windowsSize.x, size.y / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_4, Priority::HIGH, 0, 76, true, false, 0, 0.05, 96, 0});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}

void ParallaxPreload::preload(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Vector2f> screenSize, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = 0;
    sf::Vector2u windowsSize = window->getSize();
    sf::Vector2f size{screenSize->x / (1920 / 2), screenSize->y / (1080 / 2)};
    sf::Vector2f size3{screenSize->x / (1920 / 3), screenSize->y / (1080 / 3)};

    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_1, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1.5, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_0, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.2, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_2, Priority::HIGH, 0, 8, true, false, 0, 0.2, 640, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 640, 360), sf::Color::White, sf::Vector2f(screenSize->x / 640 / screenSize->x * windowsSize.x, screenSize->y / 360 / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 0, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-0.6, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
    id = entityManager.addMask((InfoComp::SPRITEID | InfoComp::POS | InfoComp::VEL | InfoComp::PARALLAX | InfoComp::SPRITEAT), componentManager);
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, sf::FloatRect(0, 0, 96, 96), sf::Color::White, sf::Vector2f(size.x / screenSize->x * windowsSize.x, size.y / screenSize->y * windowsSize.y)});
    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_PARALLAX_4, Priority::HIGH, 0, 76, true, false, 0, 0.05, 96, 0});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{0, 100, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{-1, 0, 0});
    componentManager.getComponent(typeid(Parallax)).emplaceData(id, Parallax{true});
}
