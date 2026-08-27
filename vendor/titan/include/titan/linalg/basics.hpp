#ifndef TITAN_LINALG_BASICS_HPP
#define TITAN_LINALG_BASICS_HPP

#include "mat.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "vec3.hpp"

#include <vector>
#include <cmath>


namespace titan
{
    
    inline vec3 MinVec3(vec3 vec1, vec3 vec2)
    {
        vec3 result;
        result[0] = std::min(vec1[0], vec2[0]);
        result[1] = std::min(vec1[1], vec2[1]);
        result[2] = std::min(vec1[2], vec2[2]);
        return result;
    }

    inline vec3 MaxVec3(vec3 vec1, vec3 vec2)
    {
        vec3 result;
        result[0] = std::max(vec1[0], vec2[0]);
        result[1] = std::max(vec1[1], vec2[1]);
        result[2] = std::max(vec1[2], vec2[2]);
        return result;
    }

    inline mat3 ToMat3(mat4& mat)
    {
        return mat3({mat(0,0), mat(0,1), mat(0,2), 
                     mat(1,0), mat(1,1), mat(1,2), 
                     mat(2,0), mat(2,1), mat(2,2)});
    }

    inline mat3 ToMat4(mat3& mat)
    {
        return mat3({mat(0,0), mat(0,1), mat(0,2), 0.0f,
                     mat(1,0), mat(1,1), mat(1,2), 0.0f,
                     mat(2,0), mat(2,1), mat(2,2), 0.0f,
                     0.0f,     0.0f,     0.0f,     1.0f});
    }

    inline bool SameDirection(const vec3& v1, const vec3& v2)
    {
        return (v1 ^ v2).length() < 1e-6;
    }

} // namespace titan


#endif // TITAN_LINALG_BASICS_HPP