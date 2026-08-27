#ifndef TITAN_VEC3_HPP
#define TITAN_VEC3_HPP
    
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>


namespace titan
{
    struct vec4;
    struct mat;
    struct mat3;

    struct vec3 
    {
        std::array<float, 3> data;

        /**
         * @brief Default constructor initializes the vector to zero.
         */
        vec3();

        /**
         * @brief Constructor to initialize the vector with given x, y, z values.
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         * @param z The z-component of the vector.
         */
        vec3(float x, float y, float z);
        
        /**
         * @brief Constructor to initialize the vector with given x, y, z values.
         * @param vec the array of float v
         */
        vec3(const float* vec);
        
        /**
         * @brief Constructor to initialize the vector with given vec4
         * @param vec The vec4 will drop last element to become vec3
         */
        vec3(vec4& vec);

        /**
         * @brief Constructs a vec3 object from an initializer list of float values.
         * @param values An initializer list containing three float values representing the x, y, and z components of the vector.
         */
        vec3(std::initializer_list<float> values);

        /**
         * @brief Constructs a vec3 object from a vector of float values.
         * @param values A reference to a vector of float values used to initialize the vec3 object.
         */
        vec3(std::vector<float>& values);

        /**
         * @brief Accessor for vector elements (non-const version).
         * @param i Index of the element to access (0 for x, 1 for y, 2 for z).
         * @return Reference to the element at the specified index.
         */
        float& operator[](int i);

        /**
         * @brief Accessor for vector elements (const version).
         * @param i Index of the element to access (0 for x, 1 for y, 2 for z).
         * @return Const reference to the element at the specified index.
         */
        const float& operator[](int i) const;

        /**
         * @brief Adds two vectors element-wise.
         * @param other The vector to add.
         * @return A new vector that is the result of the addition.
         */
        vec3 operator+(const vec3& other) const;

        /**
         * @brief Subtracts another vector from this vector element-wise.
         * @param other The vector to subtract.
         * @return A new vector that is the result of the subtraction.
         */
        vec3 operator-(const vec3& other) const;

        /**
         * @brief Multiplies the vec3 by a matrix and returns the resulting vector.
         * @param other The matrix to multiply with the current vector.
         * @return A new vector that is the result of the matrix-vector multiplication.
         */
        vec operator*(const mat& other) const;
        
        /**
         * @brief Multiplies this vec3 by a mat3 and returns the resulting vec3.
         * @param other The mat3 to multiply with this vec3.
         * @return A new vec3 that is the result of the matrix-vector multiplication.
         */
        vec3 operator*(const mat3& other) const;

        /**
         * @brief Computes the dot product of two vectors.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float value.
         */
        float operator*(const vec3& other) const;

        /**
         * @brief Multiplies the vector by a scalar.
         * @param scalar The scalar value to multiply with.
         * @return A new vector that is the result of the scalar multiplication.
         */
        vec3 operator*(float scalar) const;

        /**
         * @brief Computes the cross product of two vectors.
         * @param other The vector to compute the cross product with.
         * @return A new vector that is the result of the cross product.
         */
        vec3 operator^(const vec3& other) const;

        /**
         * @brief inverse of this vector
         * @return A new vec3 that is inverse of this vector
         */
        vec3 operator-() const;

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
         * @brief Computes the dot product of two vectors.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float value.
         */
        float dot(const vec3& other) const;

        /**
         * @brief Computes the cross product of two vectors.
         * @param other The vector to compute the cross product with.
         * @return A new vector that is the result of the cross product.
         */
        vec3 cross(const vec3& other) const;

        /**
         * @brief Normalizes the vector to have a length of 1.
         * @return A new vector that is the normalized version of the current vector.
         */
        vec3 normalized() const;

        /**
         * @brief Computes the length (magnitude) of the vector.
         * @return The length of the vector as a float.
         */
        float length() const;

        /**
         * @brief Logs the vector to the console.
         */
        void log() const;
    };

} // namespace titan

#include "vec4.hpp"
#include "mat.hpp"
#include "mat3.hpp"
#include "vec3.inl"


#endif // TITAN_VEC3_HPP