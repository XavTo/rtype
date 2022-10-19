#include "Engine/Network/Serializer.hpp"

eng::Serializer::Serializer()
{
}

_STORAGE_DATA eng::Serializer::convertToArray(std::vector<uint8_t> &packet)
{
    _STORAGE_DATA convert = {0};

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert[i] = packet[i];
    }
    return convert;
}

std::vector<uint8_t> eng::Serializer::convertToVector(_STORAGE_DATA &packet)
{
    std::vector<uint8_t> convert;

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert.push_back(packet[i]);
    }
    return convert;
}

void eng::Serializer::insertMagic(std::vector<uint8_t> &packet)
{
    for (auto elem : MAGIC) {
        packet.push_back(elem);
    }
}

bool eng::Serializer::checkMagic(std::vector<uint8_t> &packet, std::size_t adv)
{
    for (std::size_t i = 0; i < MAGIC_SIZE; i++) {
        if (packet[adv + i] != MAGIC[i]) {
            return false;
        }
    }
    return true;
}

std::size_t eng::Serializer::getEntityID(SyncID syncID, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t id = 0;
    auto masks = entityManager.getMasks();

    for (; id < masks.size(); id++) {
        if (masks[id].has_value() && (masks[id].value() & InfoComp::SYNCID) && componentManager.getSingleComponent<SyncID>(id).id == syncID.id) {
            return id;
        }
    }
    throw std::runtime_error("[ERROR] SyncID not found");
}

void eng::Serializer::pushComponents(std::vector<uint8_t> &packet, std::size_t mask, std::size_t id, ComponentManager &componentManager)
{
    for (std::size_t i = 0; i < componentManager.getComponentArray().size(); i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        switch (i) {
        case 0:
            this->serializeComponent<Position>(packet, &componentManager.getSingleComponent<Position>(id));
            break;
        case 1:
            this->serializeComponent<Velocity>(packet, &componentManager.getSingleComponent<Velocity>(id));
            break;
        case 2:
            this->serializeComponent<Size>(packet, &componentManager.getSingleComponent<Size>(id));
            break;
        case 3:
            this->serializeComponent<SpriteID>(packet, &componentManager.getSingleComponent<SpriteID>(id));
            break;
        case 4:
            this->serializeComponent<Controllable>(packet, &componentManager.getSingleComponent<Controllable>(id));
            break;
        case 5:
            this->serializeComponent<Parallax>(packet, &componentManager.getSingleComponent<Parallax>(id));
            break;
        case 6:
            this->serializeComponent<Projectile>(packet, &componentManager.getSingleComponent<Projectile>(id));
            break;
        case 7:
            this->serializeComponent<Life>(packet, &componentManager.getSingleComponent<Life>(id));
            break;
        case 8:
            this->serializeComponent<Enemy>(packet, &componentManager.getSingleComponent<Enemy>(id));
            break;
        case 9:
            this->serializeComponent<Appearance>(packet, &componentManager.getSingleComponent<Appearance>(id));
            break;
        case 10:
            this->serializeComponent<Disappearance>(packet, &componentManager.getSingleComponent<Disappearance>(id));
            break;
        case 11:
            this->serializeComponent<CooldownShoot>(packet, &componentManager.getSingleComponent<CooldownShoot>(id));
            break;
        case 12:
            this->serializeComponent<CooldownBar>(packet, &componentManager.getSingleComponent<CooldownBar>(id));
            break;
        case 13:
            this->serializeComponent<LifeBar>(packet, &componentManager.getSingleComponent<LifeBar>(id));
            break;
        case 14:
            this->serializeComponent<Parent>(packet, &componentManager.getSingleComponent<Parent>(id));
            break;
        case 15:
            this->serializeComponent<Patern>(packet, &componentManager.getSingleComponent<Patern>(id));
            break;
        case 16:
            this->serializeComponent<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));
            break;
        case 17:
            this->serializeComponent<DropBonus>(packet, &componentManager.getSingleComponent<DropBonus>(id));
            break;
        case 18:
            this->serializeComponent<Text>(packet, &componentManager.getSingleComponent<Text>(id));
            break;
        case 19:
            this->serializeComponent<SoundID>(packet, &componentManager.getSingleComponent<SoundID>(id));
            break;
        case 20:
            this->serializeComponent<SpriteAttribut>(packet, &componentManager.getSingleComponent<SpriteAttribut>(id));
            break;
        default:
            break;
        }
    }
}

std::size_t eng::Serializer::updateEntity(std::vector<uint8_t> &packet, std::size_t id, std::size_t &adv, ComponentManager &componentManager)
{
    Position pos = {0, 0};
    adv = this->deserializeComponent<Position>(packet, adv, &pos);
    componentManager.getSingleComponent<Position>(id) = pos;

    Velocity vel = {0, 0};
    adv = this->deserializeComponent<Velocity>(packet, adv, &vel);
    componentManager.getSingleComponent<Velocity>(id) = vel;

    SpriteID spriteID = {0};
    adv = this->deserializeComponent(packet, adv, &spriteID);
    componentManager.getSingleComponent<SpriteID>(id) = spriteID;
    return adv;
}

_STORAGE_DATA eng::Serializer::serializeEntity(std::size_t id, EntityType type, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::vector<uint8_t> packet;

    this->insertMagic(packet);

    // header
    PacketType packetType = PacketType::ENTITY;
    this->serializeComponent(packet, &packetType);
    this->serializeComponent(packet, &type);

    // sync id
    this->serializeComponent<SyncID>(packet, &componentManager.getSingleComponent<SyncID>(id));

    // mask
    std::optional<std::size_t> mask = entityManager.getMasks()[id];
    if (!entityManager.getMasks()[id].has_value()) {
        throw std::runtime_error("[ERROR] Entity has no mask");
    }
    this->serializeComponent<std::size_t>(packet, &entityManager.getMasks()[id].value());

    // components
    this->pushComponents(packet, mask.value(), id, componentManager);

    this->insertMagic(packet);
    return this->convertToArray(packet);
}

void eng::Serializer::synchronizeEntity(std::vector<uint8_t> packet, EntityManager &entityManager, ComponentManager &componentManager)
{
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    EntityType type = EntityType::UNKNOWN_ENTITY;
    SyncID syncID = {0};
    std::size_t mask = 0;
    std::size_t id = 0;

    adv = this->deserializeComponent<EntityType>(packet, adv, &type);
    adv = this->deserializeComponent<SyncID>(packet, adv, &syncID);
    adv = this->deserializeComponent<std::size_t>(packet, adv, &mask);

    if (type == EntityType::DESTROY) {
        id = this->getEntityID(syncID, entityManager, componentManager);
        entityManager.removeMask(id);
        componentManager.removeAllComponents(id);
        return;
    }
    if (type == EntityType::CREATE) {
        id = entityManager.addMask(mask, componentManager);
        componentManager.getSingleComponent<SyncID>(id) = syncID;
    } else if (type == EntityType::UPDATE) {
        id = this->getEntityID(syncID, entityManager, componentManager);
    } else {
        throw std::runtime_error("[ERROR] Unknown entity type");
    }
    adv = this->updateEntity(packet, id, adv, componentManager);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
}

_STORAGE_DATA eng::Serializer::serializeInput(sf::Keyboard::Key input)
{
    std::vector<uint8_t> packet;
    PacketType type = PacketType::INPUT;

    this->insertMagic(packet);

    this->serializeComponent<PacketType>(packet, &type);
    this->serializeComponent<sf::Keyboard::Key>(packet, &input);

    this->insertMagic(packet);
    return this->convertToArray(packet);
}

void eng::Serializer::synchronizeInput(std::vector<uint8_t> packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                       std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = MAGIC_SIZE + sizeof(PacketType);
    sf::Keyboard::Key keyPress = sf::Keyboard::Key::Unknown;

    adv = this->deserializeComponent<sf::Keyboard::Key>(packet, adv, &keyPress);
    if (!this->checkMagic(packet, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    input.checkInput(id, keyPress, componentManager, entityManager, clock);
}

void eng::Serializer::handlePacket(_STORAGE_DATA packet, std::size_t id, EntityManager &entityManager, ComponentManager &componentManager, Input &input,
                                   std::shared_ptr<sf::Clock> clock)
{
    std::size_t adv = 0;
    std::vector<uint8_t> packetVector = this->convertToVector(packet);
    PacketType type;

    if (!this->checkMagic(packetVector, adv)) {
        throw std::runtime_error("[ERROR] Bad packet format");
    }
    adv += MAGIC_SIZE;
    adv = this->deserializeComponent<PacketType>(packetVector, adv, &type);
    switch (type) {
    case ENTITY:
        this->synchronizeEntity(packetVector, entityManager, componentManager);
        break;
    case INPUT:
        this->synchronizeInput(packetVector, id, entityManager, componentManager, input, clock);
        break;
    default:
        throw std::runtime_error("[ERROR] Unknown packet type");
    }
}
