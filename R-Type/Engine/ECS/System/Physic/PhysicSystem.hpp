/**
 * @file PhysicSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the physics.
 * @copyright Epitech Rennes 2022
 */

#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/VesselPreload.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "Engine/Graphic/Graphic.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief System of the physics.
     * @class PhysicSystem
     */
    class PhysicSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<std::size_t> _syncId;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            std::shared_ptr<sf::Clock> _clock;

            std::size_t _speedTag = (InfoComp::VEL | InfoComp::POS);
            std::size_t _shieldTag = (InfoComp::PARENT | InfoComp::SHIELD);
            std::size_t _dropTag = (InfoComp::POS | InfoComp::SIZE | InfoComp::DROP);

            void createBonus(std::size_t id, std::size_t drop, ComponentManager &componentManager, EntityManager &entityManager);
            void switchCreateBonus(std::size_t addEntity, std::size_t drop, ComponentManager &componentManager, Size &size, Position &pos);
            bool checkAppareance(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position &pos, Velocity &vel);
            bool checkDisappearance(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, Position &pos, Velocity &vel, std::size_t &it);
            void killWhenDisappeared(EntityManager &entityManager, ComponentManager &componentManager, std::size_t i, std::size_t &it);
            bool checkCollision(Position pos, Position pos2, Size sz, Size sz2);
            bool collisionBonus(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos);
            void bonusFound(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, DropBonus drop, Size size);
            bool collisionEnemy(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos, std::size_t &it);
            bool collisionEnemySplit(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position pos, std::size_t &it);
            bool collisionFireball(std::size_t i, ComponentManager &componentManager, EntityManager &entityManager, Position pos, std::size_t &it);
            bool splitCollisionFireball(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, Position pos, std::size_t &it);
            void collisionFireballEnemy(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j, bool &checkShield);
            void collisionCheckShield(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t j);
            void physicVessel(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i);
            void physicPattern(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i);
            bool physicCollision(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, Position pos, std::size_t &it);
            bool physicAnim(ComponentManager &componentManager, EntityManager &entityManager, std::size_t i, std::size_t &it, Position &pos, Velocity &vel);

        public:
            /**
             * @brief PhysicSystem constructor.
             * @fn PhysicSystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             * @param syncId A shared pointer to the synchronized id of the client
             */
            PhysicSystem(Graphic &graphic, EntityManager &entityManager);
            /**
             * @brief PhysicSystem destructor.
             * @fn ~PhysicSystem
             */
            ~PhysicSystem() = default;
            /**
             * @brief Update the physics system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // PHYSICSYSTEM_HPP
