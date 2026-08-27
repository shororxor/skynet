#ifndef TITAN_CAMERA_HPP
#define TITAN_CAMERA_HPP

#include "vec3.hpp"
#include "mat4.hpp"
#include "constants.hpp"

namespace titan
{

    inline mat4 Perspective(float fov, float aspect, float znear, float zfar)
    {
        float tanHalfFov = tan(DEG2RAD(fov) / 2.0f);
        float zrange = znear - zfar;

        mat4 P;

        P(0,0) = 1 / (aspect * tanHalfFov);  P(0,1) = 0.0f;             P(0,2)  = 0.0f;                     P(0,3) = 0.0f;
        P(1,0) = 0.0f;                       P(1,1) = 1 / tanHalfFov;   P(1,2)  = 0.0f;                     P(1,3) = 0.0f;
        P(2,0) = 0.0f;                       P(2,1) = 0.0f;             P(2,2) = (zfar + znear) / zrange;   P(2,3) = (2.0f * zfar * znear) / zrange;
        P(3,0) = 0.0f;                       P(3,1) = 0.0f;             P(3,2) = -1.0f;                     P(3,3) = 0.0f;

        return P;
    }

} // namespace titan

#endif // TITAN_CAMERA_HPP