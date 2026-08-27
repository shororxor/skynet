#ifndef SKYNET_ENGINE_COLLISION_GJK
#define SKYNET_ENGINE_COLLISION_GJK

#include "Component.h"

namespace Skynet
{
    struct Simplex {
        int count;
        titan::vec3 A;
        titan::vec3 B;
        titan::vec3 C;
        titan::vec3 D;
    };

    struct Face {
        titan::vec3 a, b, c;
        titan::vec3 n;
        titan::real d;

        Face(titan::vec3 a, titan::vec3 b, titan::vec3 c) : a(a), b(b), c(c) {
            n = ((b - a) ^ (c - a)).normalized();
            d = n * a;
            if (d < 0) {
                n = -n;
                d = -d;
            }
        }

        bool IsVisibleFrom(const titan::vec3& p) const {
            return (n * (p - a)) > 0;
        }
    };

    struct Edge {
        titan::vec3 a, b;
        bool operator<(const Edge& other) const {
            return true;
        }
    };

    titan::vec3 GetSupport(AABB& box, RigidBody& body, const titan::vec3& direction);
    bool GJKBruteForce(PointCloud& cloud, AABB& boxA, AABB& boxB, RigidBody& bodyA, RigidBody& bodyB);
    bool SimpleSolverGJK(PointCloud& cloud, Simplex& simplex, AABB& box1, AABB& box2, RigidBody& body1, RigidBody& body2);

} // namespace Skynet


#endif // SKYNET_ENGINE_COLLISION_GJK