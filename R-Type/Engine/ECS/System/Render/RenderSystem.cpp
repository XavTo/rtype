#include "Engine/ECS/System/Render/RenderSystem.hpp"

using namespace eng;

RenderSystem::RenderSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_clock = graphic.getClock();
    this->_window = graphic.getWindow();
    this->_screenSize = graphic.getScreenSize();
    this->_sprites = sprites;
    this->_sceneId = graphic.getSceneId();
    if (!this->_font.loadFromFile("R-Type/Assets/Fonts/PeachDays.ttf"))
        throw std::runtime_error("Error: Font not found");
    this->_text.setFont(this->_font);
    this->_text.setCharacterSize(35);
    this->_text.setFillColor(sf::Color::White);

    entityManager.addMaskCategory(this->_renderTag);
    entityManager.addMaskCategory(this->_textTag);
}

bool RenderSystem::displayCooldownBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    std::size_t cooldownBarParent = (InfoComp::COOLDOWNBAR | InfoComp::SPRITEID | InfoComp::PARENT);
    std::size_t cooldownBarChild = (InfoComp::COOLDOWNSHOOT);
    std::size_t size = 100 / this->_screenSize->x * this->_window->getSize().x;

    if (entityManager.hasMask(i, cooldownBarParent)) {
        std::size_t idPar = entityManager.getBySyncId(componentManager.getSingleComponent<Parent>(i).id, componentManager);
        if (entityManager.hasMask(idPar, cooldownBarChild)) {
            CooldownShoot &cooldownShoot = componentManager.getSingleComponent<CooldownShoot>(idPar);
            spriteRef.setScale(
                ((this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * size / cooldownShoot.shootDelay) > size ? size : (this->_clock->getElapsedTime().asSeconds() - cooldownShoot.lastShoot + cooldownShoot.shootDelay) * size / cooldownShoot.shootDelay,
                1);
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
            return true;
        }
    }
    return false;
}

bool RenderSystem::displayLifeBar(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    std::size_t lifeBarParent = (InfoComp::POS | InfoComp::LIFEBAR | InfoComp::PARENT);
    std::size_t lifeBarChild = (InfoComp::POS | InfoComp::LIFE | InfoComp::SIZE);

    if (entityManager.hasMask(i, lifeBarParent)) {
        std::size_t idPar = entityManager.getBySyncId(componentManager.getSingleComponent<Parent>(i).id, componentManager);
        if (entityManager.hasMask(idPar, lifeBarChild)) {
            LifeBar &lifeBar = componentManager.getSingleComponent<LifeBar>(i);
            Life &life = componentManager.getSingleComponent<Life>(idPar);
            Position &pos = componentManager.getSingleComponent<Position>(idPar);
            Size &sz = componentManager.getSingleComponent<Size>(idPar);
            spriteRef.setScale(life.life * sz.x / lifeBar.lifeMax, 1);
            spriteRef.setPosition(pos.x, pos.y - (20 / this->_screenSize->x * this->_window->getSize().x));
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
            return true;
        }
    }
    return false;
}

bool RenderSystem::displayShield(ComponentManager &componentManager, EntityManager &entityManager, sf::Sprite &spriteRef, std::size_t i)
{
    std::size_t shieldParent = (InfoComp::POS | InfoComp::SHIELD | InfoComp::PARENT);
    std::size_t shieldChild = (InfoComp::POS | InfoComp::LIFE | InfoComp::SIZE | InfoComp::SPRITEAT);

    if (entityManager.hasMask(i, shieldParent)) {
        std::size_t idPar = entityManager.getBySyncId(componentManager.getSingleComponent<Parent>(i).id, componentManager);
        if (entityManager.hasMask(idPar, shieldChild)) {
            Shield &shield = componentManager.getSingleComponent<Shield>(i);
            if (shield.life > 0) {
                SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(i);
                Position &pos = componentManager.getSingleComponent<Position>(idPar);
                SpriteAttribut &spriteAtPar = componentManager.getSingleComponent<SpriteAttribut>(idPar);
                spriteRef.setColor(sf::Color(255, 255, 255, shield.life * 255 / shield.defaultLife));
                spriteRef.setScale(spriteAt.scale.x * spriteAtPar.scale.x, spriteAt.scale.y * spriteAtPar.scale.y);
                spriteRef.setRotation(spriteAtPar.rotation);
                spriteRef.setOrigin(spriteAt.offset.x, spriteAt.offset.y);
                spriteRef.setPosition(pos.x + spriteAtPar.offset.x * spriteAtPar.scale.x * _window->getSize().x / _screenSize->x, pos.y + spriteAtPar.offset.y * spriteAtPar.scale.y * _window->getSize().y / _screenSize->y);
            } else {
                componentManager.removeAllComponents(i);
                entityManager.removeMask(i);
                return true;
            }
        } else {
            componentManager.removeAllComponents(i);
            entityManager.removeMask(i);
            return true;
        }
    }
    return false;
}

void RenderSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t renderAnim = (InfoComp::SPRITEAT);
    std::size_t renderCooldown = (InfoComp::PARENT | InfoComp::COOLDOWNBAR);
    std::size_t renderLife = (InfoComp::PARENT | InfoComp::LIFEBAR);
    std::size_t renderParallax = (InfoComp::POS | InfoComp::SPRITEID | InfoComp::PARALLAX);
    std::size_t renderShield = (InfoComp::PARENT | InfoComp::SHIELD);
    std::vector<sf::Sprite> stockSpriteHigh;
    std::vector<sf::Sprite> stockSpriteMedium;
    std::vector<sf::Sprite> stockSpriteLow;
    std::vector<sf::Text> stockText;

    for (auto id : entityManager.getMaskCategory(this->_textTag)) {
        sf::Text &textRef = this->_text;
        Text &text = componentManager.getSingleComponent<Text>(id);
        if (entityManager.hasMask(id, this->_sceneTag)) {
            Scene &scene = componentManager.getSingleComponent<Scene>(id);
            if (scene.id != *this->_sceneId)
                continue;
        }
        if (componentManager.getSingleComponent<Text>(id).hasValue)
            textRef.setString(text.str + std::to_string(text.value));
        else {
            textRef.setString(text.str);
            textRef.setOrigin(textRef.getLocalBounds().width / 2, textRef.getLocalBounds().height / 2);
        }
        textRef.setFillColor(text.color);
        textRef.setCharacterSize(text.size);
        textRef.setPosition(text.pos);
        stockText.push_back(textRef);
    }
    for (auto id : entityManager.getMaskCategory(this->_renderTag)) {
        if (!entityManager.hasMask(id, InfoComp::POS) || !entityManager.hasMask(id, InfoComp::SPRITEID))
            continue;

        Position &pos = componentManager.getSingleComponent<Position>(id);
        SpriteID &spriteId = componentManager.getSingleComponent<SpriteID>(id);
        if (entityManager.hasMask(id, this->_sceneTag)) {
            Scene &scene = componentManager.getSingleComponent<Scene>(id);
            if (scene.id != *this->_sceneId)
                continue;
        }
        sf::Sprite &spriteRef = this->_sprites->at(spriteId.id);
        spriteRef.setPosition(pos.x, pos.y);
        if (entityManager.hasMask(id, renderAnim)) {
            SpriteAttribut &spriteAt = componentManager.getSingleComponent<SpriteAttribut>(id);
            spriteRef.setTextureRect(static_cast<sf::IntRect>(spriteAt.rect));
            spriteRef.setRotation(spriteAt.rotation);
            spriteRef.setColor(spriteAt.color);
            spriteRef.setScale(spriteAt.scale);
            sf::Vector2f ratio = {_screenSize->x / _window->getSize().x, _screenSize->y / _window->getSize().y};
            spriteRef.setOrigin({spriteAt.offset.x * ratio.x, spriteAt.offset.y * ratio.y});
            spriteRef.setPosition(pos.x + spriteAt.offset.x * spriteAt.scale.x * ratio.x + spriteAt.delay.x * spriteAt.scale.x * ratio.x, pos.y + spriteAt.offset.y * spriteAt.scale.y * ratio.y + spriteAt.delay.y * spriteAt.scale.x * ratio.y);
        }
        if (entityManager.hasMask(id, renderCooldown) && displayCooldownBar(componentManager, entityManager, spriteRef, id))
            continue;
        if (entityManager.hasMask(id, renderLife) && displayLifeBar(componentManager, entityManager, spriteRef, id))
            continue;
        if (entityManager.hasMask(id, renderShield) && displayShield(componentManager, entityManager, spriteRef, id))
            continue;
        if (spriteId.priority == Priority::HIGH)
            stockSpriteHigh.push_back(spriteRef);
        if (spriteId.priority == Priority::MEDIUM)
            stockSpriteMedium.push_back(spriteRef);
        if (spriteId.priority == Priority::LOW)
            stockSpriteLow.push_back(spriteRef);
    }

    for (std::size_t i = 0; i < stockSpriteHigh.size(); i++) {
#ifndef NDEBUG
        entityManager.hasMask(i, renderParallax);
        continue;
#endif
        if (entityManager.hasMask(i, renderParallax)) {
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
    for (std::size_t i = 0; i < stockText.size(); i++)
        this->_window->draw(stockText[i]);
}
