/**
 * @file EnemyPreload.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief Preload the enemy.
 * @copyright Epitech Rennes 2022
 */

#ifndef ENEMYPRELOAD_HPP
#define ENEMYPRELOAD_HPP

/// @cond
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief Preloads the enemy.
     * @class EnemyPreload
     */
    class EnemyPreload : public EntityPreload
    {
        public:
            /**
             * @brief Preloads the enemy.
             * @fn static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager)
             * @param engine A reference to the engine.
             */
            static void preload(Graphic &graphic, EntityManager &entityManager, ComponentManager &componentManager, std::size_t syncId);
    };
}

#endif // ENEMYPRELOAD_HPP
