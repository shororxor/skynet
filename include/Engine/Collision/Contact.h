#ifndef SKYNET_COLLISION_CONTACT_H
#define SKYNET_COLLISION_CONTACT_H

#include "Titan.hpp"
#include "BVHData.h"
#include "Component.h"
#include "GJK.h"
#include "EPA.h"
#include "entt.hpp"

namespace Skynet
{
	void ApplyImpulse(RigidBody& bodyA, RigidBody& bodyB, const Contact& contact);
	void ComputeContact(PointCloud& cloud, AABB& boxA, AABB& boxB, RigidBody& bodyA, RigidBody& bodyB);
	void CheckCollision(entt::registry& bodies, entt::registry& points, float& k, float& b);

} // namespace Skynet

#endif // SKYNET_COLLISION_CONTACT_H