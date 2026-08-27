#ifndef SKYNET_ENGINE_COLLISION_SAT_H
#define SKYNET_ENGINE_COLLISION_SAT_H

#include "Titan.hpp"
#include "BVHData.h"
#include "Component.h"
#include "entt.hpp"
#include "EPA.h"

namespace Skynet
{
	Contact SAT(AABB& boxA, AABB& boxB, RigidBody& bodyA, RigidBody& bodyB);

} // namespace Skynet

#endif // SKYNET_ENGINE_COLLISION_SAT_H