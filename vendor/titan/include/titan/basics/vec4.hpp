#ifndef TITAN_VEC4_HPP
#define TITAN_VEC4_HPP
    
#include <array>
#include <cmath>
#include <iostream>

namespace titan
{
    struct mat;
    struct mat4;
    struct vec3;

    struct vec4 
    {
        std::array<float, 4> data;

        /**
         * @brief Default constructor. Initializes the vector to (0.0, 0.0, 0.0, 1.0).
         */
        vec4();

        /**
         * @brief Constructor with explicit x, y, z, and optional w components.
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         * @param w The w component of the vector (default is 1.0).
         */
        vec4(float x, float y, float z, float w = 1.0f);

        /**
         * @brief Constructor from a vec3 and optional w component.
         * @param v A vec3 containing x, y, z components.
         * @param w The w component of the vector (default is 1.0).
         */
        vec4(const vec3& v, float w = 1.0f);

        /**
         * @brief Constructs a vec4 object from an initializer list of float values.
         * @param values An initializer list containing three float values representing the x, y, and z components of the vector.
         */
        vec4(std::initializer_list<float> values);

        /**
         * @brief Constructs a vec4 object from a vector of float values.
         * @param values A reference to a vector of float values used to initialize the vec4 object.
         */
        vec4(std::vector<float>& values);

        /**
         * @brief Subscript operator for accessing vector components.
         * @param i The index of the component to access (0 for x, 1 for y, 2 for z, 3 for w).
         * @return A reference to the component at the specified index.
         */
        float& operator[](int i);

        /**
         * @brief Const subscript operator for accessing vector components.
         * @param i The index of the component to access (0 for x, 1 for y, 2 for z, 3 for w).
         * @return A const reference to the component at the specified index.
         */
        const float& operator[](int i) const;

        /**
         * @brief Adds two vectors component-wise.
         * @param other The vector to add to this vector.
         * @return A new vec4 representing the component-wise sum.
         */
        vec4 operator+(const vec4& other) const;

        /**
         * @brief Substract two vectors component-wise.
         * @param other The vector to add to this vector.
         * @return A new vec4 representing the component-wise sum.
         */
        vec4 operator-(const vec4& other) const;

        /**
         * @brief Multiplies the vec4 by a matrix and returns the resulting vector.
         * @param other The matrix to multiply with the current vector.
         * @return A new vector that is the result of the matrix-vector multiplication.
         */
        vec operator*(const mat& other) const;

        
        /**
         * @brief Multiplies this vec4 by a mat4 and returns the resulting vec4.
         * @param other The mat4 to multiply with this vec4.
         * @return A new vec4 that is the result of the matrix-vector multiplication.
         */
        vec4 operator*(const mat4& other) const;

        /**
         * @brief Computes the dot product of this vector with another vector.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float.
         */
        float operator*(const vec4& other) const;

        /**
         * @brief Multiplies the vector by a scalar.
         * @param scalar The scalar value to multiply the vector by.
         * @return A new vec4 representing the scaled vector.
         */
        vec4 operator*(float scalar) const;

        /**
         * @brief Provides raw access to the underlying data.
         * @return Pointer to the raw data array.
        */
        float* raw();

        /**
         * @brief Zero out all data in array
        */
        void zero();

        /**
         * @brief Computes the dot product of this vector with another vector.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float.
         */
        float dot(const vec4& other) const;

        /**
         * @brief Returns a normalized version of the vector.
         * @return A normalized vec4 if the length is greater than zero, otherwise the original vec4.
         */
        vec4 normalized() const;

        /**
         * @brief Computes the length (magnitude) of the vector.
         * @return The length of the vector as a float.
         */
        float length() const;

        /**
         * @brief Logs the vector's components to the standard output.
         */
        void log() const;
    };

} // namespace titan

#include "mat.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.inl"

#endif // TITAN_VEC4_HPP