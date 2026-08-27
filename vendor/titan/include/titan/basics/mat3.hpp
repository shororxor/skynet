#ifndef TITAN_MAT3_HPP
#define TITAN_MAT3_HPP

#include <array>
#include <iostream>
#include <iomanip>

namespace titan
{
    struct mat;
    struct vec3;

    /**
     * @brief A 3x3 matrix class.
     */
    struct mat3 
    {
        std::array<float, 9> data;

        /**
         * @brief Default constructor. Initializes all elements to 0.
         */
        mat3();

        /**
         * @brief Constructor with initializer list.
         * @param values Initial values for the matrix.
         */
        mat3(std::initializer_list<float> values);
        mat3(std::vector<float>& values);

        /**
         * @brief Access element at (row, col).
         * @param row Row index.
         * @param col Column index.
         * @return Reference to the element at (row, col).
         */
        float& operator()(int row, int col);

        /**
         * @brief Access element at (row, col) (const version).
         * @param row Row index.
         * @param col Column index.
         * @return Const reference to the element at (row, col).
         */
        const float& operator()(int row, int col) const;

        /**
         * @brief Matrix addition.
         * @param other The matrix to subtract.
         * @return The result of the matrix addition.
         */
        mat3 operator+(const mat3& other) const;

        /**
         * @brief Matrix subtraction.
         * @param other The matrix to subtract.
         * @return The result of the matrix subtraction.
         */
        mat3 operator-(const mat3& other) const;

        /**
         * @brief Matrix multiplication with a general matrix.
         * @param other The matrix to multiply with.
         * @return The result of the matrix multiplication.
         */
        mat operator*(const mat& other) const;
        
        /**
         * @brief Matrix multiplication.
         * @param other The matrix to multiply with.
         * @return The result of the matrix multiplication.
         */
        mat3 operator*(const mat3& other) const;

        /**
         * @brief Multiply the matrix by a vector.
         * @param vec The vector to multiply with.
         * @return The result of the matrix-vector multiplication.
         */
        vec3 operator*(const vec3& other) const;

        /**
         * @brief Scalar multiplication.
         * @param scalar The scalar to multiply with.
         * @return The result of the scalar multiplication.
         */
        mat3 operator*(float scalar) const;

        /**
         * @brief Get raw pointer to the matrix data.
         * @return Pointer to the matrix data.
         */
        float* raw();

        /**
         * @brief Get the vec3 column of matrix
         * @param index of the desired column
         * @return return the column of matrix
         */
        vec3 col(int index) const;

        /**
         * @brief Creates an identity matrix.
         * @return An identity matrix.
         */
        static mat3 identity();

        /**
         * @brief Transpose the matrix.
         * @return The transposed matrix.
         */
        mat3 transpose() const;

        /**
         * @brief Calculate the determinant of the matrix.
         * @return The determinant of the matrix.
         */
        float determinant() const;

        /**
         * @brief Calculate the inverse of the matrix.
         * @return The inverse of the matrix.
         * @throws std::runtime_error if the matrix is singular.
         */
        mat3 inverse() const;

        /**
         * @brief Log the matrix to the standard output.
         */
        void log() const;
    };

} // namespace titan

#include "mat.hpp"
#include "vec3.hpp"
#include "mat3.inl"

#endif // TITAN_MAT3_HPP