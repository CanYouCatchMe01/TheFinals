#pragma once
namespace flecs {
    struct world;
}

namespace physx {
    class PxScene;
    class PxControllerManager;
    class PxPhysics;
    class PxController;
    class PxRigidDynamic;
}

namespace physics {
    struct Controller {
        physx::PxController *controller = nullptr;
    };

    struct RigidDynamic {
        physx::PxRigidDynamic *rigid_dynamic = nullptr;
    };


    extern physx::PxPhysics *g_physics;

    void setup();
    void update(physx::PxScene *physics_scene, float physics_accumulator, flecs::world &world, float delta_time);
    void create_scene(physx::PxScene **physics_scene, physx::PxControllerManager **controller_manager);
}