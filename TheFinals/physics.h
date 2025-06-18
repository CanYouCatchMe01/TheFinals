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

    template <typename T>
    class PxVec3T;
    typedef PxVec3T<float> PxVec3;
    typedef PxVec3T<double> PxVec3d;
    typedef PxVec3d	PxExtendedVec3;
}

namespace transform {
    struct Transform;
}

namespace DirectX {
    struct XMFLOAT3;
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
    void Float3ToPxVec3(const DirectX::XMFLOAT3 &in_float3, physx::PxVec3 &out_vec3);
    void PxExtendedVec3ToFloat3(const physx::PxExtendedVec3 &in_ext_vec3, DirectX::XMFLOAT3 &out_float3);

    void setup();
    void update(physx::PxScene *physics_scene, float &physics_accumulator, flecs::world &world, float delta_time);
    void create_scene(physx::PxScene **physics_scene, physx::PxControllerManager **controller_manager);
}