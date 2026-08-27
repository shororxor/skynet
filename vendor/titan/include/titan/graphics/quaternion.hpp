#ifndef TITAN_QUATERNION_HPP
#define TITAN_QUATERNION_HPP

#include "vec3.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "constants.hpp"

namespace titan
{
    /**
     * @brief A structure representing a quaternion.
     */
    struct quat 
    {
        float w, x, y, z;

        /**
         * @brief Default constructor. Initializes the quaternion to the identity quaternion.
         */
        quat() : w(1), x(0), y(0), z(0) {}

        /**
         * @brief Parameterized constructor.
         * @param w The scalar part of the quaternion.
         * @param x The x-component of the vector part.
         * @param y The y-component of the vector part.
         * @param z The z-component of the vector part.
         */
        quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

        /**
         * @brief Constructs a quaternion from an axis-angle representation.
         * @param axis The axis of rotation.
         * @param angle The angle of rotation in radians.
         */
        quat(const vec3& axis, float angle) 
        {
            float halfAngle = angle * 0.5f;
            float s = sin(halfAngle);

            w = cos(halfAngle);
            x = axis[0] * s;
            y = axis[1] * s;
            z = axis[2] * s;
        }

        /**
         * @brief Calculates the length (magnitude) of the quaternion.
         * @return The length of the quaternion as a float.
         */
        float length()
        {
            return std::sqrt(w * w + x * x + y * y + z * z);
        }

        /**
         * @brief Normalizes the quaternion to have a magnitude of 1.
         */
        void normalize() 
        {
            float len = length();
        
            if (len > 0.0f) 
            {
                float invLen = 1.0f / len;
                w *= invLen;
                x *= invLen;
                y *= invLen;
                z *= invLen;
            }
        }

        /**
         * @brief Computes the dot product of two quaternions.
         * @param q1 The first quaternion.
         * @param q2 The second quaternion.
         * @return The dot product of q1 and q2.
         */
        static float dot(const quat& q1, const quat& q2) 
        {
            return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
        }

        /**
         * @brief Converts the quaternion to a 4x4 transformation matrix.
         * @return The transformation matrix corresponding to the quaternion.
         */
        mat4 Quat2T() const 
        {
            mat4 T;

            float xx = x * x, yy = y * y, zz = z * z;
            float xy = x * y, xz = x * z, yz = y * z;
            float wx = w * x, wy = w * y, wz = w * z;

            T(0,0) = 1 - 2 * (yy + zz);
            T(0,1) = 2 * (xy - wz);
            T(0,2) = 2 * (xz + wy);
            T(0,3) = 0;

            T(1,0) = 2 * (xy + wz);
            T(1,1) = 1 - 2 * (xx + zz);
            T(1,2) = 2 * (yz - wx);
            T(1,3) = 0;

            T(2,0) = 2 * (xz - wy);
            T(2,1) = 2 * (yz + wx);
            T(2,2) = 1 - 2 * (xx + yy);
            T(2,3) = 0;

            T(3,0) = 0;
            T(3,1) = 0;
            T(3,2) = 0;
            T(3,3) = 1;

            return T;
        }

        /**
         * @brief Rotates a vector by the quaternion.
         * @param v The vector to be rotated.
         * @return The rotated vector.
         */
        vec3 rotateVector(const vec3& v) const 
        {
            quat qv(0, v[0], v[1], v[2]);
            quat inv(w, -x, -y, -z);
            quat result = (*this) * qv * inv;
            return vec3(result.x, result.y, result.z);
        }

        /**
         * @brief Multiplies two quaternions.
         * @param q The quaternion to multiply with.
         * @return The resulting quaternion.
         */
        quat operator*(const quat& q) const 
        {
            return quat(
                w * q.w - x * q.x - y * q.y - z * q.z,
                w * q.x + x * q.w + y * q.z - z * q.y,
                w * q.y - x * q.z + y * q.w + z * q.x,
                w * q.z + x * q.y - y * q.x + z * q.w
            );
        }

        /**
         * @brief Constructs a quaternion from Euler angles.
         * @param e The Euler angles in radians.
         * @return The quaternion corresponding to the Euler angles.
         */
        static quat fromEuler(const vec3& e) 
        {
            float cx = cos(e[0] * 0.5f);
            float cy = cos(e[1] * 0.5f);
            float cz = cos(e[2] * 0.5f);
            float sx = sin(e[0] * 0.5f);
            float sy = sin(e[1] * 0.5f);
            float sz = sin(e[2] * 0.5f);

            return quat(
                cx * cy * cz + sx * sy * sz,
                sx * cy * cz - cx * sy * sz,
                cx * sy * cz + sx * cy * sz,
                cx * cy * sz - sx * sy * cz
            );
        }

        /**
         * @brief Converts the quaternion to Euler angles.
         * @return The Euler angles in radians.
         */
        vec3 toEuler() const 
        {
            vec3 e;

            // roll (x)
            float sinr_cosp = 2 * (w * x + y * z);
            float cosr_cosp = 1 - 2 * (x * x + y * y);

            e[0] = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y)
            float sinp = 2 * (w * y - z * x);

            if (std::abs(sinp) >= 1) 
                e[1] = std::copysign(M_PI / 2, sinp);
            else 
                e[1] = std::asin(sinp);

            // yaw (z)
            float siny_cosp = 2 * (w * z + x * y);
            float cosy_cosp = 1 - 2 * (y * y + z * z);

            e[2] = std::atan2(siny_cosp, cosy_cosp);

            return e;
        }
    };
    
} // namespace titan


#endif // TITAN_QUATERNION_HPP