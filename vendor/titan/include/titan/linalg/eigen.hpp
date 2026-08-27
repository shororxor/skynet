#ifndef TITAN_EIGEN_HPP
#define TITAN_EIGEN_HPP

#include "mat.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "vec3.hpp"

#include <vector>
#include <cmath>

namespace titan
{
    /**
     * @brief Perform Eigen decomposition using the Jacobi method.
     * @param mat Input symmetric 3x3 matrix.
     * @param eigenvalues Output vec3 for eigenvalues.
     * @param eigenvectors Output matrix for eigenvectors (columns are eigenvectors).
     * @param maxIterations Maximum number of iterations.
     * @param tolerance Convergence tolerance.
     */
    inline void EigenDecompositionJacobi(const mat3& mat, vec3& eigenvalues, mat3& eigenvectors, int maxIterations = 50, float tolerance = 1e-6) 
    {
        eigenvectors = mat3::identity();

        mat3 A = mat;

        for (int iter = 0; iter < maxIterations; ++iter) 
        {
            // Find the largest off-diagonal element
            int p = 0, q = 1;
            float maxOffDiag = std::abs(A(0, 1));
            for (int i = 0; i < 3; ++i) {
                for (int j = i + 1; j < 3; ++j) 
                {
                    if (std::abs(A(i, j)) > maxOffDiag) 
                    {
                        maxOffDiag = std::abs(A(i, j));
                        p = i;
                        q = j;
                    }
                }
            }

            // Check for convergence
            if (maxOffDiag < tolerance) {
                break;
            }

            // Compute the rotation angle
            float theta = 0.5f * std::atan2(2.0f * A(p, q), A(q, q) - A(p, p));
            float c = std::cos(theta);
            float s = std::sin(theta);

            // Apply the rotation to A
            float App = A(p, p);
            float Aqq = A(q, q);
            float Apq = A(p, q);

            A(p, p) = c * c * App - 2.0f * c * s * Apq + s * s * Aqq;
            A(q, q) = s * s * App + 2.0f * c * s * Apq + c * c * Aqq;
            A(p, q) = A(q, p) = 0.0f;

            for (int r = 0; r < 3; ++r) 
            {
                if (r != p && r != q) 
                {
                    float Arp = A(r, p);
                    float Arq = A(r, q);
                    A(r, p) = c * Arp - s * Arq;
                    A(p, r) = A(r, p);
                    A(r, q) = s * Arp + c * Arq;
                    A(q, r) = A(r, q);
                }
            }

            // Update the eigenvectors
            for (int r = 0; r < 3; ++r) 
            {
                float Vrp = eigenvectors(r, p);
                float Vrq = eigenvectors(r, q);
                eigenvectors(r, p) = c * Vrp - s * Vrq;
                eigenvectors(r, q) = s * Vrp + c * Vrq;
            }
        }

        // Extract eigenvalues from the diagonal of A
        eigenvalues[0] = A(0, 0);
        eigenvalues[1] = A(1, 1);
        eigenvalues[2] = A(2, 2);
    }



    /**
     * @brief Perform Eigen decomposition using the power iteration method.
     * @param mat Input 3x3 matrix.
     * @param eigenvalues Output vec3 for eigenvalues.
     * @param eigenvectors Output matrix for eigenvectors (columns are eigenvectors).
     * @param maxIterations Maximum number of iterations.
     * @param tolerance Convergence tolerance.
     */
    inline void EigenDecompositionIterative(const mat3& mat, vec3& eigenvalues, mat3& eigenvectors, int maxIterations = 50, float tolerance = 1e-6) 
    {
        mat3 M = mat;
        eigenvectors = mat3();

        for (int eig = 0; eig < 3; ++eig) 
        {
            vec3 v(1.0f, 1.0f, 1.0f);
            v = v.normalized();

            float lambda = 0.0f; // eigenvalue estimate

            for (int iter = 0; iter < maxIterations; ++iter) 
            {
                vec3 vNew = M * v;
                lambda = vNew.length();   // approximate eigenvalue
                vNew = vNew.normalized(); // normalize eigenvector

                // convergence check
                if ((v - vNew).length() < tolerance) break;
                v = vNew;
            }

            // store eigenvalue & eigenvector
            eigenvalues[eig] = lambda;
            eigenvectors(0, eig) = v[0];
            eigenvectors(1, eig) = v[1];
            eigenvectors(2, eig) = v[2];

            // outer product (v * v^T)
            mat3 outerProduct;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    outerProduct(i, j) = v[i] * v[j];

            M = M -  outerProduct * lambda;
        }
    }

    

} // namespace titan



#endif // TITAN_EIGEN_HPP