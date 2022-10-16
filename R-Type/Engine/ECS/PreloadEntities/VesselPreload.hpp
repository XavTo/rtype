#ifndef VESSELPRELOAD_HPP
#define VESSELPRELOAD_HPP

#include <Includes.hpp>

#include "Engine/ECS/ECS.hpp"
#include "Engine/ECS/PreloadEntities/EntityPreload.hpp"

namespace eng
{
    class VesselPreload : public EntityPreload
    {
        public:
            void preload(Engine &engine) override;
    };
}

#endif // VESSELPRELOAD_HPP
