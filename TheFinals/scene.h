#pragma once
#include "flecs/flecs.h"

namespace physx {
    class PxScene;
    class PxControllerManager;
}

namespace scene {
    struct Scene {
        flecs::world world;

        physx::PxScene *physics_scene = nullptr;
        float physics_accumulator = 0.0f;
        physx::PxControllerManager *controller_manager = nullptr;
    };

    void setup(Scene &scene);
    void update(Scene &scene);
}
