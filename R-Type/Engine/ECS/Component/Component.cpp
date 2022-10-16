#include "Engine/ECS/Component/Component.hpp"

using namespace eng;

Component::Component()
{
}

void Component::addData(std::size_t id, std::any data)
{
    if (id >= this->_component.size())
        this->_component.resize(id + 1);
    this->_component[id] = data;
}

void Component::emplaceData(std::size_t id, std::any data)
{
    if (id > this->_component.size())
        throw std::runtime_error("Incorrect ID");
    this->_component[id] = data;
}

std::optional<std::any> &Component::getField(std::size_t id)
{
    if (id > this->_component.size())
        throw std::runtime_error("Incorrect ID");
    return this->_component[id];
}

std::size_t Component::getSize()
{
    return this->_component.size();
}

void Component::destroyData(std::size_t id)
{
    if (id > this->_component.size())
        throw std::runtime_error("Incorrect ID");
    this->_component[id].reset();
}