#include "SAT.h"

namespace Skynet
{
	titan::real ComputeContactDepth(const AABB& boxA, const AABB& boxB, const RigidBody& bodyA, const RigidBody& bodyB, const titan::vec3& axis) {
		float centerA = boxA.GetCenter().dot(axis);
		float centerB = boxB.GetCenter().dot(axis);

		titan::vec3 halfA = boxA.GetHalfExtent();
		titan::vec3 halfB = boxB.GetHalfExtent();

		float r1 = 0.0f, r2 = 0.0f;
		
		for (int i = 0; i < 3; i++) {
			titan::vec4 cA = bodyA.R.col(i);
			titan::vec4 cB = bodyB.R.col(i);

			r1 += std::abs(axis * titan::vec3(cA)) * halfA[i];
			r2 += std::abs(axis * titan::vec3(cB)) * halfB[i];
		}

		float overlap = (r1 + r2) - std::abs(centerA - centerB);
		return (overlap > 0) ? overlap : -1.0f;
	}

	bool IsPointInsideBox(const titan::vec3& point, const AABB& box, const RigidBody& body) {
		titan::vec3 center = box.GetCenter();
		titan::vec3 half = box.GetHalfExtent();

		for (int i = 0; i < 3; i++) {
			titan::vec4 orientation = body.R.col(i);
			float distance = (point - center) * titan::vec3(orientation);
			if (std::abs(distance) > half[i]) return false;
		}
		return true;
	}

	list<titan::vec3> GetInterSectionPoints(const AABB& boxA, const AABB& boxB, const RigidBody& bodyA, const RigidBody& bodyB) {
		list<titan::vec3> points;

		list<titan::vec3> cornersA = boxA.GetCorners();
		list<titan::vec3> cornersB = boxB.GetCorners();

		for (const titan::vec3 p : cornersA)
			if (IsPointInsideBox(p, boxB, bodyB))
				points.push_back(p);

		for (const titan::vec3& p : cornersB)
			if (IsPointInsideBox(p, boxA, bodyA))
				points.push_back(p);
		
		return points;
	}

	Contact SAT(AABB& boxA, AABB& boxB, RigidBody& bodyA, RigidBody& bodyB) {
		titan::vec3 axes[15];

		titan::vec3 A_axes[3] = {
			titan::vec3(bodyA.R(0,0), bodyA.R(1,0), bodyA.R(2,0)),
			titan::vec3(bodyA.R(0,1), bodyA.R(1,1), bodyA.R(2,1)),
			titan::vec3(bodyA.R(0,2), bodyA.R(1,2), bodyA.R(2,2))
		};

		titan::vec3 B_axes[3] = {
			titan::vec3(bodyB.R(0,0), bodyB.R(1,0), bodyB.R(2,0)),
			titan::vec3(bodyB.R(0,1), bodyB.R(1,1), bodyB.R(2,1)),
			titan::vec3(bodyB.R(0,2), bodyB.R(1,2), bodyB.R(2,2))
		};

		int count = 0;

		/* Axes are face normals */
		for (int i = 0; i < 3; i++) {
	        axes[count++] = A_axes[i];
	        axes[count++] = B_axes[i];
	    }

	    /* Axes are cross product of edges */
	    for (int i=0; i < 3; i++) {
	    	for (int j=0; j < 3; j++) {
	    		titan::vec3 axis = A_axes[i].cross(B_axes[j]);
	    		if (axis.length() > 1e-6) {
	    			axes[count++] = axis.normalized();
	    		}
	    	}
	    }

	    /* Check penetration depth */
	    Contact contact;
	    titan::real minDepth = FLT_MAX;
	    titan::vec3 bestAxis;

	    for (int i=0; i < count; i++) {
	    	titan::vec3 axis = axes[i];
	    	titan::real depth = ComputeContactDepth(boxA, boxB, bodyA, bodyB, axis);
	    	
	    	if (depth < 0) return contact; // SAT found => no collision

	    	if (depth < minDepth) {
	    		minDepth = depth;
	    		bestAxis = axis;
	    	}
	    }

	    contact.valid = true;
	    contact.normal = bestAxis.normalized();
	    contact.depth = minDepth;

	    /* Get a set of intersection points */
	    list<titan::vec3> points = GetInterSectionPoints(boxA, boxB, bodyA, bodyB);

	    if (points.size() > 0) {
	    	titan::vec3 avg;
	        for (const auto& p : points) avg = avg +  p;
	        contact.point = avg * (1.0f / (float)points.size());
	    }

	    return contact;
	}

} // namespace Skynet
