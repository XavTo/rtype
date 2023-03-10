#include "Engine/ECS/System/Animation/AnimationSystem.hpp"

using namespace eng;

AnimationSystem::AnimationSystem(Graphic &graphic, EntityManager &entityManager, std::shared_ptr<std::vector<sf::Sprite>> sprites)
{
    this->_event = graphic.getEvent();
    this->_clock = graphic.getClock();
    this->_sprites = sprites;

    entityManager.addMaskCategory(this->_spriteTag);
}

void AnimationSystem::update(ComponentManager &componentManager, EntityManager &entityManager)
{
    std::size_t appMask = (InfoComp::APP);
    std::size_t contMask = (InfoComp::CONTROLLABLE | InfoComp::VEL);

    for (auto id : entityManager.getMaskCategory(this->_spriteTag)) {
        SpriteID &spriteID = componentManager.getSingleComponent<SpriteID>(id);
        SpriteAttribut &spriteAT = componentManager.getSingleComponent<SpriteAttribut>(id);
        if (entityManager.hasMask(id, contMask)) {
            Velocity &vel = componentManager.getSingleComponent<Velocity>(id);
            spriteAT.rect.top = spriteID.offsetY;
            if (vel.y < 0)
                spriteAT.rect.left = spriteID.offsetX * 2;
            else if (vel.y > 0)
                spriteAT.rect.left = spriteID.offsetX;
            else
                spriteAT.rect.left = 0;
            continue;
        }
        if (spriteID.nbFrame == 0 || (entityManager.hasMask(id, appMask) && componentManager.getSingleComponent<Appearance>(id).app))
            continue;
        if (this->_clock->getElapsedTime().asSeconds() >= spriteID.lastTime + spriteID.delay) {
            if (spriteID.curFrame == 0 && !spriteID.autoLoop)
                spriteID.sign = false;
            if (spriteID.curFrame == spriteID.nbFrame && !spriteID.autoLoop)
                spriteID.sign = true;
            if (!spriteID.autoLoop)
                spriteID.sign == false ? spriteID.curFrame++ : spriteID.curFrame--;
            else
                spriteID.curFrame == spriteID.nbFrame ? spriteID.curFrame = 0 : spriteID.curFrame++;
            spriteAT.rect.left = spriteID.offsetX * spriteID.curFrame;
            spriteAT.rect.top = spriteID.offsetY * spriteID.curFrame;
            spriteID.lastTime = this->_clock->getElapsedTime().asSeconds();
        }
    }
}

// animations rects data:
// enemy: 63x48 (offset 63 on x)
// boss: 48x48 (offset 48 on x)
// player: 32x14 (offset 32 on x and 14 on y to change color)
