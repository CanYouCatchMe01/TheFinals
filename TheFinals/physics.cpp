#include "physics.h"
#include "PxPhysicsAPI.h"

//#define PHYSX_DEBUG

#ifdef PHYSX_DEBUG
#pragma message("WARNING: PHYSX_DEBUG ENABLED, DO NOT COMMIT LIKE THIS!")
#endif

namespace physics {
    physx::PxDefaultAllocator globalDefaultAllocator;
    physx::PxDefaultErrorCallback globalDefaultErrorCallback;

    physx::PxFoundation *globalFoundation = NULL;
    physx::PxPhysics *globalPhysics = NULL;
    physx::PxDefaultCpuDispatcher *globalDispatcher = NULL;

#ifdef PHYSX_DEBUG 
    physx::PxPvd *globalPvd = NULL;
    physx::PxPvdTransport *globalTransport = NULL;
#endif

    void setup() {
		globalFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, globalDefaultAllocator, globalDefaultErrorCallback);

#ifdef PHYSX_DEBUG 
		globalPvd = PxCreatePvd(*globalFoundation);
		globalTransport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		//globalPvd->connect(*globalTransport, physx::PxPvdInstrumentationFlag::eALL); //Not needed. Doing later
		bool recordMemoryAllocations = true;

		globalPhysics = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*globalFoundation,
			physx::PxTolerancesScale(),
			recordMemoryAllocations,
			globalPvd
		);

		PxInitExtensions(*globalPhysics, globalPvd);
#else
		globalPhysics = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*globalFoundation,
			physx::PxTolerancesScale()
		);

		PxInitExtensions(*globalPhysics, nullptr);
#endif

		globalDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    }
}