#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Clock> clock, Loader &loader)
{
    this->_clock = clock;
    this->_window = window;
    this->_sprites = loader.getSprites();
}

void RenderSystem::displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();

    std::size_t cooldownBarParent = (InfoComp::COOLDOWNBAR | InfoComp::SPRITEID | InfoComp::PARENT);
    std::size_t cooldownBarChild = (InfoComp::COOLDOWNSHOOT);

    if (masks[i].has_value() && (masks[i].value() & cooldownBarParent) == cooldownBarParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & cooldownBarChild) == cooldownBarChild) {
                CooldownShoot &cooldownShoot = componentManager.getSingleComponent<CooldownShoot>(idPar);
                spriteRef.setScale(((this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay) > 100
                                       ? 100
                                       : (this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * 100 / cooldownShoot.shootDelay,
                                   1);
            }
        } else
            spriteRef.setScale(0, 0);
    }
}

void RenderSystem::displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    auto &masks = entityManager.getMasks();
    std::size_t lifeBarParent = (InfoComp::POS | InfoComp::LIFEBAR | InfoComp::PARENT);
    std::size_t lifeBarChild = (InfoComp::POS | InfoComp::LIFE | InfoComp::SIZE);

    if (masks[i].has_value() && (masks[i].value() & lifeBarParent) == lifeBarParent) {
        std::size_t idPar = componentManager.getSingleComponent<Parent>(i).id;
        if (masks[idPar].has_value()) {
            if ((masks[idPar].value() & lifeBarChild) == lifeBarChild) {
                LifeBar &lifeBar = componentManager.getSingleComponent<LifeBar>(i);
                Life &life = componentManager.getSingleComponent<Life>(idPar);
                Position &pos = componentManager.getSingleComponent<Position>(idPar);
                Size &sz = componentManager.getSingleComponent<Size>(idPar);
                spriteRef.setScale(life.life * sz.x / lifeBar.lifeMax, 1);
                spriteRef.setPosition(pos.x, pos.y - 20);
            }
        } else
            spriteRef.setScale(0, 0);
    }
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    auto &masks = entityManager.getMasks();
    std::size_t render = (InfoComp::POS | InfoComp::SPRITEID);
    std::size_t renderCooldown = (InfoComp::PARENT | InfoComp::COOLDOWNBAR);
    std::size_t renderLife = (InfoComp::PARENT | InfoComp::LIFEBAR);
    std::size_t renderParallax = (InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARALLAX);
    std::size_t renderProj = (InfoComp::PROJECTILE);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;

    for (std::size_t i = 0; i < masks.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & render) == render) {
            Position &pos = componentManager.getSingleComponent<Position>(i);
            SpriteID &spriteId = componentManager.getSingleComponent<SpriteID>(i);
            sf::Sprite &spriteRef = this->_sprites[spriteId.id];
            spriteRef.setPosition(pos.x, pos.y);
            if ((masks[i].value() & renderCooldown) == renderCooldown)
                displayCooldownBar(componentManager, entityManager, spriteRef, i);
            if ((masks[i].value() & renderLife) == renderLife)
                displayLifeBar(componentManager, entityManager, spriteRef, i);
            if ((masks[i].value() & renderProj) == renderProj) {
                Projectile &proj = componentManager.getSingleComponent<Projectile>(i);
                spriteRef.setScale(proj.size, proj.size);
            }
            if (spriteId.priority == Priority::HIGH)
                stockSpriteHigh.push_back(spriteRef);
            if (spriteId.priority == Priority::MEDIUM)
                stockSpriteMedium.push_back(spriteRef);
            if (spriteId.priority == Priority::LOW)
                stockSpriteLow.push_back(spriteRef);
        }
    }
    for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
        if (masks[i].has_value() && (masks[i].value() & renderParallax) == renderParallax) {
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x + _window->getSize().x, stockSpriteHigh[i].getPosition().y);
            this->_window->draw(stockSpriteHigh[i]);
            stockSpriteHigh[i].setPosition(stockSpriteHigh[i].getPosition().x - _window->getSize().x, stockSpriteHigh[i].getPosition().y);
        }
        this->_window->draw(stockSpriteHigh[i]);
    }
    for (std::size_t i = 0; i < stockSpriteMedium.size(); i++)
        this->_window->draw(stockSpriteMedium[i]);
    for (std::size_t i = 0; i < stockSpriteLow.size(); i++)
        this->_window->draw(stockSpriteLow[i]);
}

// animations rects data:
// enemy: 63x48 (offset 63 on x)
// boss: 48x48 (offset 48 on x)
// player: 32x14 (offset 32 on x and 14 on y to change color)