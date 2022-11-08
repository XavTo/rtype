/**
 * @file ClickSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System that handle mouse inputs.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLICKSYSTEM_HPP
#define CLICKSYSTEM_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
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
     * @brief System that handle mouse inputs.
     * @class ClickSystem
     */
    class ClickSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;

        public:
            /**
             * @brief ClickSystem constructor.
             * @fn ClickSystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             */
            ClickSystem(Graphic &graphic, EntityManager &entityManager);
            /**
             * @brief ClickSystem destructor.
             * @fn ~ClickSystem()
             */
            ~ClickSystem() = default;
            /**
             * @brief Update the click system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // CLICKSYSTEM_HPP