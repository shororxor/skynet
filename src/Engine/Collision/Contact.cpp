#include "Contact.h"
#include "SAT.h"

namespace Skynet
{
	void ApplyImpulse(RigidBody& bodyA, RigidBody& bodyB, const Contact& contact) {	
		/* Compute relative velocity - gap function */
		titan::vec3 n = contact.normal;
		titan::vec3 rA = contact.point - bodyA.x;
		titan::vec3 rB = contact.point - bodyB.x;

		titan::vec3 vA = bodyA.vel + bodyA.omega ^ rA;
		titan::vec3 vB = bodyB.vel + bodyB.omega ^ rB;
		
		float vrel = n * (vA - vB);
		float epsilon = 0.5f;
		float numerator =  -(1.0f + epsilon) * vrel;

		/* Calculate the denominator in four parts */
		float term1 = 1.0f / bodyA.mass;
		float term2 = 1.0f / bodyB.mass;
		float term3 = n * ((bodyA.Iinv * (rA ^ n)) ^ rA);
		float term4 = n * ((bodyB.Iinv * (rB ^ n)) ^ rB);

		/* Compute the impulse magnitude */
		double j = numerator / (term1 + term2 + term3 + term4);
		titan::vec3 impulse = n * j;

		/* Apply the impulse to the bodies */
		bodyA.P = bodyA.P +  impulse;
		bodyB.P = bodyB.P -  impulse;
		
		bodyA.L = bodyA.L + rA ^ impulse;
		bodyB.L = bodyB.L - rB ^ impulse;

		/* recompute auxiliary variables */
		bodyA.vel = bodyA.P * (1.0f / bodyA.mass);
		bodyB.vel = bodyB.P * (1.0f / bodyB.mass);

		bodyA.omega = bodyA.Iinv * bodyA.L;
		bodyB.omega = bodyB.Iinv * bodyB.L;
	}

	void ComputeContact(PointCloud& cloud, AABB& boxA, AABB& boxB, RigidBody& bodyA, RigidBody& bodyB) {
		#ifdef GJK_DEBUG
		cloud.Clear();
		cloud.Add(titan::vec3(0.0f, 0.0f, 0.0f));
		#endif

		Simplex simplex;

		if (SimpleSolverGJK(cloud, simplex, boxA, boxB, bodyA, bodyB)) {
			#ifdef GJK_DEBUG
			cloud.MakeLines();
			#endif

			INFO("True");
			Contact contact = SimpleSolverEPA(simplex, boxA, boxB, bodyA, bodyB);
			if (contact.valid) ApplyImpulse(bodyA, bodyB, contact);
		}
	}

	void CheckCollision(entt::registry& bodies, entt::registry& points, float& k, float& b) {
		size_t n = bodies.size();
		auto& ground = bodies.get<BVHComp>((entt::entity)0).root->box;
		auto& cloud = points.get<PointCloud>((entt::entity)0);

        for (int i = 1; i < n; i++) {
            auto& boxA  = bodies.get<BVHComp>((entt::entity)i).root->box;
            auto& bodyA = bodies.get<RigidBodyComp>((entt::entity)i).body;

            /* Check collision with other objects */ 
            for (int j = i + 1; j < n; j++) {
                auto& boxB  = bodies.get<BVHComp>((entt::entity)j).root->box;
                auto& bodyB = bodies.get<RigidBodyComp>((entt::entity)j).body;
               	ComputeContact(cloud, boxA, boxB, bodyA, bodyB);
            }

            /* Check collision with default ground */
            float level = boxA.GetTransMin(bodyA.GetTransform())[1];
            if (level < ground.max[1] + 0.5f) {
                float depth = level - ground.max[1];
                bodyA.force_int[1] = -k * depth - b * bodyA.vel[1] + bodyA.mass * 9.81;
            }
            else bodyA.force_int[1] = 0.0f;
        }
	}

} // namespace Skynet