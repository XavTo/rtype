/**
 * @file Client.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The client handling functions.
 * @copyright Epitech Rennes 2022
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

/// @cond
#include "Client/ClientNetwork.hpp"
#include "Engine.hpp"
#include "Engine/ECS/PreloadEntities/BackgroundMusicPreload.hpp"
#include "Engine/ECS/PreloadEntities/LobbyPreload.hpp"
#include "Engine/ECS/PreloadEntities/MenuPreload.hpp"
#include "Engine/ECS/PreloadEntities/ParallaxPreload.hpp"
#include "Engine/ECS/PreloadEntities/RoomPreload.hpp"
#include "Engine/ECS/PreloadEntities/ScoreTextPreload.hpp"
#include "GameSerializer.hpp"
#include "Includes.hpp"
#include "MenuSerializer.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The client handling functions.
     * @class Client
     */
    class Client
    {
        private:
            Engine _engine;
            std::unique_ptr<ClientNetwork> _network = nullptr;

            MenuSerializer _menuSerializer;
            GameSerializer _gameSerializer;

            std::size_t _id;

            std::size_t _roomId = 0;
            std::vector<Room> _rooms;

            sf::Time _networkTime = sf::milliseconds(50);
            sf::Time _keysTime = sf::milliseconds(16);

            bool _isLevelFinished = false;

            void createNetwork();

            void initSystems();
            void initComponents();
            void initEntities();
            void syncUdpNetwork();
            void syncTcpNetwork();
            void updateNetwork();
            void updateEvent();
            bool checkIfEnemyAlive(EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic);
            bool manageEnemy(Level &level, Graphic &graphic, ECS &ecs);
            void updateKeys();

        public:
            /**
             * @brief Client constructor
             * @fn Client()
             */
            Client();
            /**
             * @brief Client destructor
             * @fn ~Client()
             */
            ~Client() = default;

            /**
             * @brief Main loop of the client
             * @fn void mainLoop()
             */
            void mainLoop();
    };
}

#endif // CLIENT_HPP
