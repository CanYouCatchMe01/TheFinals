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
    class PxRigidStatic;
    
    template <typename T>
    class PxTransformT;

    typedef PxTransformT<float> PxTransform;
}

namespace transform {
    struct Transform;
}

namespace physics {
    struct Controller {
        physx::PxController *controller = nullptr;
    };

    struct RigidDynamic {
        physx::PxRigidDynamic *rigid_dynamic = nullptr;
    };

    struct RigidStatic {
        physx::PxRigidStatic *rigid_static = nullptr;
    };

    extern physx::PxPhysics *g_physics;

    void TransformToPxTransform(const transform::Transform &in_transform, physx::PxTransform &out_transform);

    void setup();
    void update(physx::PxScene *physics_scene, float &physics_accumulator, flecs::world &world, float delta_time);
    void create_scene(physx::PxScene **physics_scene, physx::PxControllerManager **controller_manager);
}