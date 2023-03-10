#include "Engine/ECS/PreloadEntities/EnemyPreload.hpp"

using namespace eng;

void EnemyPreload::preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::shared_ptr<std::size_t> syncId, sf::Vector2f pos)
{
    sf::Vector2u windowsSize = graphic.getWindow()->getSize();
    std::shared_ptr<sf::Vector2f> screenSize = graphic.getScreenSize();
    std::size_t rand = static_cast<std::size_t>(createRandom(0, 3));
    sf::Vector2f size{2 / screenSize->x * windowsSize.x, 2 / screenSize->y * windowsSize.y};
    std::size_t id = entityManager.addMask((InfoComp::POS | InfoComp::VEL | InfoComp::SPRITEID | InfoComp::ENEMY | InfoComp::LIFE | InfoComp::SIZE | InfoComp::PATTERN | InfoComp::SYNCID | InfoComp::SPRITEAT | InfoComp::COOLDOWNSHOOT), componentManager);

    componentManager.getComponent(typeid(SpriteID)).emplaceData(id, SpriteID{S_ENEMY, Priority::MEDIUM, 0, 2, false, false, 0, 0.075, 63, 0});
    componentManager.getComponent(typeid(SpriteAttribut)).emplaceData(id, SpriteAttribut{0, {0, 0, 63, 48}, sf::Color::White, {size.x, size.y}});
    componentManager.getComponent(typeid(Position)).emplaceData(id, Position{pos.x / screenSize->x * windowsSize.x, pos.y / screenSize->y * windowsSize.y, 0});
    componentManager.getComponent(typeid(Velocity)).emplaceData(id, Velocity{(3 / screenSize->x * windowsSize.x) * -1, 0, 0});
    componentManager.getComponent(typeid(Pattern)).emplaceData(id, Pattern{TypePattern(rand), TypeStatus::MOVE, TypePhase::PHASE01, 0});
    componentManager.getComponent(typeid(Enemy)).emplaceData(id, Enemy{true});
    componentManager.getComponent(typeid(Size)).emplaceData(id, Size{63 * size.x, 48 * size.y});
    componentManager.getComponent(typeid(Life)).emplaceData(id, Life{2});
    componentManager.getComponent(typeid(CooldownShoot)).emplaceData(id, CooldownShoot{0, (float)(rand == 0 ? 1.0 : 0.0)});
    componentManager.getComponent(typeid(SyncID)).emplaceData(id, SyncID{*syncId});
    *syncId += 1;
}
