#include "EPA.h"

namespace Skynet
{
    const static float EPS = 1e-6f;
    const static size_t MAXITER = 20;

    Contact SimpleSolverEPA(Simplex& simplex, AABB& box1, AABB& box2, RigidBody& body1, RigidBody& body2) {
        Contact contact;
        list<titan::vec3> polytope = { simplex.A, simplex.B, simplex.C, simplex.D };
        list<Face> faces = {
            {simplex.A, simplex.B, simplex.C}, // ABC
            {simplex.A, simplex.C, simplex.D}, // ACD
            {simplex.A, simplex.D, simplex.B}, // ADB
            {simplex.B, simplex.D, simplex.C}  // BDC
        };

        size_t maxIter = 15;
        for(size_t i = 0; i < maxIter; i++) {
            // find closest face and new point
            Face closestFace = faces.front();
            for(const Face& face : faces) if (face.d < closestFace.d) closestFace = face;
            titan::vec3 sp2 = GetSupport(box2, body2, closestFace.n);
            titan::vec3 sp1 = GetSupport(box1, body1, -closestFace.n);
            titan::vec3 newPoint = sp2 - sp1;

            // check convergence
            if ((newPoint * closestFace.n) - closestFace.d < EPS) {
                INFO("EPA Converged!");
                INFO("Normal: "); closestFace.n.log();
                INFO("Depth: {}", closestFace.d);

                contact.valid = true;
                contact.point = (sp1 + sp2) * 0.5f;
                contact.normal = closestFace.n;
                contact.depth = closestFace.d;
                if (contact.normal * (body1.x - body2.x) < 0) contact.normal = -contact.normal;
                return contact;
            }

            struct EdgeComparator {
            bool operator()(const std::pair<titan::vec3, titan::vec3>& a, 
                            const std::pair<titan::vec3, titan::vec3>& b) const {
                    return true;
                }
            };

            std::set<std::pair<titan::vec3, titan::vec3>, EdgeComparator> edgeBuffer;
            auto it = faces.begin();
            while (it != faces.end()) {
                if (it->IsVisibleFrom(newPoint)) {
                    auto addEdge = [&](const titan::vec3& from, const titan::vec3& to) {
                        std::pair<titan::vec3, titan::vec3> edge = {from, to};
                        std::pair<titan::vec3, titan::vec3> reversed = {to, from};
                        if (edgeBuffer.count(reversed))
                            edgeBuffer.erase(reversed);
                        else
                            edgeBuffer.insert(edge);
                    };
                    addEdge(it->a, it->b);
                    addEdge(it->b, it->c);
                    addEdge(it->c, it->a);
                    it = faces.erase(it);
                } else {
                    ++it;
                }
            }
            for (const auto& edge : edgeBuffer) {
                faces.emplace_back(edge.first, edge.second, newPoint);
            }

        }
        INFO("EPA Failed to Converge!");
        return contact;
    }

} // namespace Skynet