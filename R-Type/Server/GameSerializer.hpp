/**
 * @file GameSerializer.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The game serializer
 * @copyright Epitech Rennes 2022
 */

#ifndef GAMESERIALIZER_HPP
#define GAMESERIALIZER_HPP

/// @cond
#include "Client.hpp"
#include "Engine/ECS/PreloadEntities/ProjectilePreload.hpp"
#include "Engine/Graphic/Graphic.hpp"
#include "Engine/Network/Serializer.hpp"

/// @endcond

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng
{
    /**
     * @brief The game packet type enum
     * @enum GamePacketType
     */
    enum GamePacketType {
        ENTITY,
        INPUT,

        UNKNOWN_GAME
    };

    /**
     * @brief The game serializer
     * @enum GameSerializer
     */
    class GameSerializer : protected Serializer
    {
        protected:
            template <typename T> void updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager)
            {
                T component = T();

                deserializeData(packet, adv, &component);
                componentManager.addComponent<T>(id);
                componentManager.getSingleComponent<T>(id) = component;
            };

            void pushComponents(std::vector<uint8_t> &packet, std::size_t mask, std::size_t id, ComponentManager &componentManager);
            // void getComponents(std::vector<uint8_t> &packet, std::size_t id, std::size_t mask, std::size_t &adv, ComponentManager &componentManager);

        public:
            /**
             * @brief GameSerializer constructor.
             * @fn GameSerializer()
             */
            GameSerializer();
            /**
             * @brief GameSerializer destructor.
             * @fn ~GameSerializer()
             */
            ~GameSerializer() = default;

            /**
             * @brief Handle a game packet.
             * @fn handlePacket(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client)
             * @param packet The packet to handle.
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             * @param graphic A reference to the Graphic
             * @param client A reference to the Client who send the packet
             */
            void handlePacket(_STORAGE_DATA packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client, std::shared_ptr<std::size_t> syncId);

            /**
             * @brief Serialize an entity
             * @fn _STORAGE_DATA serializeEntity(std::size_t id, CrudType type, EntityManager &entityManager, ComponentManager &componentManager)
             * @param id The id of the entity to serialize.
             * @param type The type of operation to perform on the entity
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             * @return The serialized packet
             */
            _STORAGE_DATA serializeEntity(std::size_t entityId, CrudType type, EntityManager &entityManager, ComponentManager &componentManager);
            /**
             * @brief Deserialize an entity
             * @fn void deserializeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
             * @param packet The serialized packet
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             */
            // void deserializeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager);

            /**
             * @brief Serialize an input
             * @fn _STORAGE_DATA serializeInput(sf::Keyboard::Key input)
             * @param input The input to serialize.
             * @return The serialized packet
             */
            // _STORAGE_DATA serializeInput(sf::Keyboard::Key input);
            /**
             * @brief Deserialize an input
             * @fn void deserializeInput(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client)
             * @param packet The serialized packet
             * @param entityManager A reference to the EntityManager
             * @param componentManager A reference to the ComponentManager
             * @param graphic A reference to the Graphic
             * @param client A reference to the Client who send the packet
             */
            void deserializeInput(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager, Graphic &graphic, Client &client, std::shared_ptr<std::size_t> syncId);

            /**
             * @brief Get the client id
             * @fn std::size_t getClientId(_STORAGE_DATA packet)
             * @param packet The packet
             * @return The client id
             */
            std::size_t getClientId(_STORAGE_DATA packet);
    };
}

#endif // GAMESERIALIZER_HPP
