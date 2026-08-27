#ifndef SKYNET_ENGINE_COLLISION_EPA
#define SKYNET_ENGINE_COLLISION_EPA

#include "Component.h"
#include "GJK.h"

namespace Skynet 
{
	struct Contact {
		bool valid = false;
		titan::vec3 point;
		titan::vec3 normal;
		titan::real depth;
	};
		
	Contact SimpleSolverEPA(Simplex& simplex, AABB& box1, AABB& box2, RigidBody& body1, RigidBody& body2);

} // namespace Skynet

#endif // SKYNET_ENGINE_COLLISION_EPA