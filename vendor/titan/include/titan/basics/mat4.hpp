#ifndef TITAN_MAT4_HPP
#define TITAN_MAT4_HPP

#include <array>
#include <iostream>
#include <iomanip>

namespace titan
{
    struct mat;
    struct vec3;
    struct vec4;

    struct mat4 
    {
        std::array<float, 16> data;

        /**
         * @brief Default constructor initializes the matrix to zero.
         */
        mat4();

        /**
         * @brief Constructor to initialize the matrix with given values.
         * @param values Initial values to populate the matrix.
         */
        mat4(std::initializer_list<float> values);
        mat4(std::vector<float>& values);

        /**
         * @brief Accessor for matrix elements (non-const version).
         * @param row Row index (0 to 3).
         * @param col Column index (0 to 3).
         * @return Reference to the element at the specified row and column.
         */
        float& operator()(int row, int col);

        /**
         * @brief Accessor for matrix elements (const version).
         * @param row Row index (0 to 3).
         * @param col Column index (0 to 3).
         * @return Const reference to the element at the specified row and column.
         */
        const float& operator()(int row, int col) const;

        /**
         * @brief Matrix addition.
         * @param other The matrix to subtract.
         * @return The result of the matrix addition.
         */
        mat4 operator+(const mat4& other) const;

        /**
         * @brief Matrix subtraction.
         * @param other The matrix to subtract.
         * @return The result of the matrix subtraction.
         */
        mat4 operator-(const mat4& other) const;

        /**
         * @brief Multiplies this matrix by another matrix.
         * @param other The matrix to multiply with this matrix.
         * @return The result of the matrix multiplication.
         */
        mat operator*(const mat& other) const;
    
        /**
         * @brief Multiplies the current matrix with another matrix.
         * @param other The matrix to multiply with.
         * @return A new matrix that is the result of the multiplication.
         */
        mat4 operator*(const mat4& other) const;

        /**
         * @brief Multiplies the current matrix with a 4D vector.
         * @param other The 4D vector to multiply with.
         * @return A new 4D vector that is the result of the multiplication.
         */
        vec4 operator*(const vec4& other) const;

        /**
         * @brief Multiplies the current matrix with a 3d vector.
         * @param other The 3d vector to multiply with.
         * @return A new 3d vector that is the result of the multiplication.
         */
        vec3 operator*(const vec3& other) const;

        /**
         * @brief Multiplies the current matrix with a list of 3d vectors.
         * @param other The list of 3d vectors to multiply with.
         * @return a new list of 3d vectors after multiplication
         */
        std::vector<vec3> operator*(const std::vector<vec3>& list) const;

        /**
         * @brief Multiplies the current matrix with a scalar.
         * @param scalar The scalar value to multiply with.
         * @return A new matrix that is the result of the scalar multiplication.
         */
        mat4 operator*(float scalar) const;

        /**
         * @brief Provides raw access to the underlying data.
         * @return Pointer to the raw data array.
         */
        float* raw();

        /**
         * @brief Get the vec4 column of matrix
         * @param index of the desired column
         * @return return the column of matrix
         */
        vec4 col(int index) const;

        /**
         * @brief Creates an identity matrix.
         * @return A new 4x4 identity matrix.
         */
        static mat4 identity();

        /**
         * @brief Computes the transpose of the matrix.
         * @return A new matrix that is the transpose of the current matrix.
         */
        mat4 transpose() const;

        /**
         * @brief Computes the determinant of the matrix.
         * @return The determinant of the matrix as a mat4 object.
         */
        float determinant() const;

        /**
         * @brief Computes the inverse of the matrix.
         * @return A new matrix that is the inverse of the current matrix.
         * @throws std::runtime_error If the matrix is singular (non-invertible).
         */
        mat4 inverse() const;

        /**
         * @brief Logs the matrix to the console.
         */
        void log() const;
    };


} // namespace titan

#include "mat.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.inl"

#endif // TITAN_MAT4_HPP