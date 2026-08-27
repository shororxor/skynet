#ifndef TITAN_VEC_HPP
#define TITAN_VEC_HPP
    
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

namespace titan
{
    struct mat;

    struct vec 
    {
        std::vector<float> data;

        /**
         * @brief Constructor to initialize a vector with a given size and optional value.
         * @param size The size of the vector.
         * @param value The initial value for all elements (default is 0.0f).
         */
        vec(int size, float value = 0.0f);

        /**
         * @brief Constructs a vec object from an initializer list of float values.
         * @param values An initializer list containing float values to initialize the vec object.
         */
        vec(std::initializer_list<float> values);

        /**
         * @brief Constructs a vec object from a vector of float values.
         * @param values A vector of float values to initialize the vec object.
         */
        vec(std::vector<float>& values);

        /**
         * @brief Accessor for vector elements (non-const version).
         * @param i Index of the element to access.
         * @return Reference to the element at the specified index.
         */
        float& operator[](int i);

        /**
         * @brief Accessor for vector elements (const version).
         * @param i Index of the element to access.
         * @return Const reference to the element at the specified index.
         */
        const float& operator[](int i) const;

        /**
         * @brief Adds two vectors element-wise.
         * @param other The vector to add.
         * @return A new vector that is the result of the addition.
         * @throws std::runtime_error If the vectors have different sizes.
         */
        vec operator+(const vec& other) const;

        /**
         * @brief Subtract two vectors element-wise.
         * @param other The vector to substract.
         * @return A new vector that is the result of the substraction.
         * @throws std::runtime_error If the vectors have different sizes.
         */
        vec operator-(const vec& other) const;

        /**
         * @brief Multiplies the vector by a matrix.
         * 
         * This function performs the multiplication of the current vector with the given matrix.
         * It assumes that the number of elements in the vector matches the number of rows in the matrix.
         * 
         * @param other The matrix to multiply with the vector.
         * @return A new vector that is the result of the multiplication.
         * @throws std::runtime_error if the dimensions of the vector and matrix do not match.
         */
        vec operator*(const mat& other) const;

        /**
         * @brief Computes the dot product of two vectors.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float value.
         * @throws std::runtime_error If the vectors have different sizes.
         */
        float operator*(const vec& other) const;

        /**
         * @brief Multiplies the vector by a scalar.
         * @param scalar The scalar value to multiply with.
         * @return A new vector that is the result of the scalar multiplication.
         */
        vec operator*(float scalar) const;

        /**
         * @brief Returns the size of the data.
         * @return The size of the data as a float.
         */
        float size() const;

        /**
         * @brief Returns a pointer to the raw data array.
         * @return A constant pointer to the first element of the data array.
         */
        const float* raw() const;

        /**
         * @brief Computes the dot product of two vectors.
         * @param other The vector to compute the dot product with.
         * @return The dot product as a float value.
         * @throws std::runtime_error If the vectors have different sizes.
         */
        float dot(const vec& other) const;

        /**
         * @brief Logs the vector to the console.
         */
        void log() const;
    };

} // namespace titan

#include "mat.hpp"
#include "vec.inl"

#endif // TITAN_VEC_HPP