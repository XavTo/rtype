/**
 * @file InputSystem.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief System of the inputs.
 * @copyright Epitech Rennes 2022
 */

#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

/// @cond
#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"
#include "Engine/ECS/System/ISystem.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

/// @cond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief System of an input.
     * @class InputSystem
     */
    class InputSystem : public virtual ISystem
    {
        private:
            std::shared_ptr<std::size_t> _syncId;
            std::shared_ptr<sf::Event> _event;
            std::shared_ptr<sf::Clock> _clock;
            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<sf::Vector2f> _screenSize;
            std::shared_ptr<bool> _isLocal;

            std::size_t _controlTag = (InfoComp::CONTROLLABLE | InfoComp::VEL | InfoComp::POS | InfoComp::COOLDOWNSHOOT | InfoComp::SIZE);
            std::size_t _buttonTag = (InfoComp::BUTTON | InfoComp::POS | InfoComp::SPRITEID | InfoComp::SPRITEAT | InfoComp::SIZE);

        public:
            /**
             * @brief InputSystem constructor.
             * @fn InputSystem(Graphic &graphic, EntityManager &entityManager)
             * @param graphic A reference to the Graphic
             * @param entityManager A reference to the EntityManager
             */
            InputSystem(Graphic &graphic, EntityManager &entityManager);
            /**
             * @brief InputSystem destructor.
             * @fn ~InputSystem
             */
            ~InputSystem() = default;
            /**
             * @brief Update the input system.
             * @fn void update(ComponentManager &componentManager, EntityManager &entityManager)
             * @param componentManager A reference to the component manager.
             * @param entityManager A reference to the entity manager.
             */
            void update(ComponentManager &componentManager, EntityManager &entityManager);
    };
}

#endif // INPUTSYSTEM_HPP
