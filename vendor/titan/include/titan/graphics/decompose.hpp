#ifndef TITAN_DECOMPOSE_HPP
#define TITAN_DECOMPOSE_HPP

#include "vec3.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "constants.hpp"

namespace titan
{
    /**
     * @brief Decomposes a transformation matrix into its position, scale, and Euler angles.
     * 
     * This function takes a 4x4 transformation matrix and decomposes it into its 
     * translation (position), scale, and rotation (Euler angles) components.
     * 
     * @param T The 4x4 transformation matrix to decompose.
     * @param p A reference to a vec3 where the position will be stored.
     * @param s A reference to a vec3 where the scale will be stored.
     * @param e A reference to a vec3 where the Euler angles will be stored.
     */
    inline void Decompose(mat4& T, vec3& p, vec3& s, vec3& e)
    {
        p[0] = T(0,3);
        p[1] = T(1,3);
        p[2] = T(2,3);

        s[0] = std::sqrt(T(0,0) * T(0,0) + T(1,0) * T(1,0) + T(2,0) * T(2,0));
        s[1] = std::sqrt(T(0,1) * T(0,1) + T(1,1) * T(1,1) + T(2,1) * T(2,1));
        s[2] = std::sqrt(T(0,2) * T(0,2) + T(1,2) * T(1,2) + T(2,2) * T(2,2));

        mat3 R;
        R(0,0) = T(0,0) / s[0]; R(0,1) = T(0,1) / s[1]; R(0,2) = T(0,2) / s[2];
        R(1,0) = T(1,0) / s[0]; R(1,1) = T(1,1) / s[1]; R(1,2) = T(1,2) / s[2];
        R(2,0) = T(2,0) / s[0]; R(2,1) = T(2,1) / s[1]; R(2,2) = T(2,2) / s[2];

        if (std::abs(R(2,0)) < 0.9999f) 
        {
            e[0] = std::atan2(R(2,1), R(2,2));
            e[1] = std::asin(-R(2,0));
            e[2] = std::atan2(R(1,0), R(0,0));
        } 
        else 
        {
            e[1] = R(2,0) > 0 ? -M_PI_2 : M_PI_2;
            e[0] = std::atan2(-R(0,1), R(1,1));
            e[2] = 0.0f;
        }
    }

} // namespace titan


#endif // TITAN_DECOMPOSE_HPP