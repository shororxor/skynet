#ifndef TITAN_ROTATION_HPP
#define TITAN_ROTATION_HPP

#include "vec3.hpp"
#include "mat4.hpp"
#include "constants.hpp"

namespace titan
{
    /**
     * @brief Converts Euler angles to a transformation matrix.
     * 
     * This function takes a vector of Euler angles (in radians) and converts it into a 4x4 transformation matrix.
     * 
     * @param e A reference to a vec3 containing the Euler angles (pitch, yaw, and roll).
     * @return A 4x4 transformation matrix representing the rotation defined by the Euler angles.
     */
    inline mat4 Euler2T(vec3& e)
    {
        float cx = cos(e[0]);
        float cy = cos(e[1]);
        float cz = cos(e[2]);
        float sx = sin(e[0]);
        float sy = sin(e[1]);
        float sz = sin(e[2]);

        mat4 T = mat4::identity();

        T(0,0) = cz*cy;   T(0,1) = cz*sy*sx - sz*cx;  T(0,2) = cz*sy*cx + sz*sx;
        T(1,0) = sz*cy;   T(1,1) = sz*sy*sx + cz*cx;  T(1,2) = sz*sy*cx - cz*sx;
        T(2,0) = -sy;     T(2,1) = cy*sx;             T(2,2) = cy*cx;

        return T;
    }


    /**
     * @brief Generates a 4x4 rotation matrix for a rotation around the X-axis.
     * 
     * This function creates a 4x4 transformation matrix that represents a rotation
     * around the X-axis by the given angle in degrees.
     * 
     * @param a The angle of rotation in degrees.
     * @return A 4x4 matrix representing the rotation around the X-axis.
     */
    inline mat4 AxisX2T(float& a)
    {
        const float cs = cos(DEG2RAD(a));
        const float sn = sin(DEG2RAD(a));

        mat4 T = mat4::identity();

        T(1,1) = cs;  T(1,2) = -sn;
        T(2,1) = sn;  T(2,2) = cs;

        return T;
    }

    /**
     * @brief Generates a 4x4 rotation matrix for a rotation around the Y-axis.
     * 
     * This function creates a 4x4 transformation matrix that represents a rotation
     * around the Y-axis by the given angle in degrees.
     * 
     * @param a The angle in degrees by which to rotate around the Y-axis.
     * @return A 4x4 matrix representing the rotation transformation.
     */
    inline mat4 AxisY2T(float& a)
    {
        const float cs = cos(DEG2RAD(a));
        const float sn = sin(DEG2RAD(a));

        mat4 T = mat4::identity();

        T(0,0) = cs;  T(0,2) = -sn;
        T(2,0) = sn;  T(2,2) = cs;

        return T;
    }

    /**
     * @brief Generates a 4x4 rotation matrix for a rotation around the Z-axis.
     * 
     * This function creates a 4x4 transformation matrix that represents a rotation
     * around the Z-axis by the given angle in degrees.
     * 
     * @param a The angle in degrees by which to rotate around the Z-axis.
     * @return A 4x4 matrix representing the rotation transformation.
     */
    inline mat4 AxisZ2T(float& a)
    {
        const float cs = cos(DEG2RAD(a));
        const float sn = sin(DEG2RAD(a));

        mat4 T = mat4::identity();

        T(0,0) = cs;  T(0,1) = -sn;
        T(1,0) = sn;  T(1,1) = cs;

        return T;
    }

    /**
     * @brief Generates a rotation matrix from an axis and an angle.
     * 
     * This function computes a 4x4 rotation matrix based on a given axis vector and an angle.
     * 
     * @param w The axis of rotation represented as a 3D vector.
     * @param a The angle of rotation in radians.
     * @return A 4x4 rotation matrix.
     */
    inline mat4 Axis2T(vec3& w, float& a)
    {
        const float cs = cos(-a);
        const float sn = sin(-a);

        w.normalized();
        vec3 t =  w * (1 - cs);

        mat4 T = mat4::identity();

        T(0,0) = cs + t[0] * w[0];          T(0,1) = t[0] * w[1] + sn * w[2];   T(0,2) = t[0] * w[2] - sn * w[1];
        T(1,0) = t[0] * w[1] - sn * w[2];   T(1,1) = cs + t[1] * w[1];          T(1,2) = t[1] * w[2] + sn * w[0];
        T(2,0) = t[0] * w[2] + sn * w[1];   T(2,1) = t[1] * w[2] - sn * w[0];   T(2,2) = cs + t[2] * w[2]; 

        return T;
    }

    inline mat3 Skew(vec3& vec)
    {
        mat3 res;

        res(0,0) = 0.0f;    res(0,1) = -vec[2]; res(0,2) = vec[1];
        res(1,0) = vec[2];  res(1,1) = 0.0f;    res(1,2) = -vec[0];
        res(2,0) = -vec[1]; res(2,1) = vec[0];  res(2,2) = 0.0f; 

        return res;
    }

} // namespace titan


#endif // TITAN_ROTATION_HPP