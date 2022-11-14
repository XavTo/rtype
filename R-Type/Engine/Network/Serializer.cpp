#include "Engine/Network/Serializer.hpp"

using namespace eng;

Serializer::Serializer()
{
}

_STORAGE_DATA Serializer::convertToData(std::vector<uint8_t> &packet)
{
    _STORAGE_DATA convert = {0};

    for (std::size_t i = 0; i < packet.size(); i++) {
        convert[i] = packet[i];
    }
    return convert;
}

std::vector<uint8_t> Serializer::convertToVector(_STORAGE_DATA &packet)
{
    std::vector<uint8_t> convert;
    // std::size_t magic = 0;

    for (std::size_t i = 0; i < packet.size(); i++) {
        // for (std::size_t j = 0; packet[i + j] == MAGIC[j] && (i + j) < packet.size(); j++) {
        //     if (j == MAGIC_SIZE - 1) {
        //         magic++;
        //         if (magic == 2) {
        //             std::cout << "MAGIC: " << i + j << std::endl;
        //         }
        //         break;
        //     }
        // }
        convert.push_back(packet[i]);
    }
    return convert;
}

void Serializer::insertMagic(std::vector<uint8_t> &packet)
{
    for (auto elem : MAGIC) {
        packet.push_back(elem);
    }
}

bool Serializer::checkMagic(std::vector<uint8_t> &packet, std::size_t adv)
{
    for (std::size_t i = 0; i < MAGIC_SIZE; i++) {
        if (packet[adv + i] != MAGIC[i]) {
            return false;
        }
    }
    return true;
}
