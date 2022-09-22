#ifndef MODELIDSYSTEM_HPP
#define MODELIDSYSTEM_HPP

#include "ASystem.hpp"

namespace ECS
{
    class ModelIdSystem : public virtual ASystem
    {
        private:
            std::size_t id;

        public:
            ModelIdSystem();
            ~ModelIdSystem() = default;
            void update(ComponentManager componentManager) override;
    };
}

#endif // MODELIDSYSTEM_HPP