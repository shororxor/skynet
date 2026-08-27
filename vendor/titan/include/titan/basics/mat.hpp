#ifndef TITAN_MAT_HPP
#define TITAN_MAT_HPP

#include <array>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace titan
{
    struct vec;

    struct mat 
    {
        int rows, cols;
        std::vector<float> data;

        /**
         * @brief Constructor to initialize a matrix with given dimensions and zero values.
         * @param r Number of rows.
         * @param c Number of columns.
         */
        mat(int r, int c);

        /**
         * @brief Constructor to initialize a matrix with given dimensions and initial values.
         * @param r Number of rows.
         * @param c Number of columns.
         * @param values Initial values to populate the matrix.
         */
        mat(std::initializer_list<float> values);
        mat(std::vector<float>& values);

        /**
         * @brief Constructs a matrix from a list of initializer lists.
         * 
         * This constructor initializes a matrix with the given values. Each initializer list
         * represents a row in the matrix. All rows must have the same number of columns.
         * 
         * @param values A list of initializer lists where each inner list represents a row of the matrix.
         * @return None
         */
        mat(std::initializer_list<std::initializer_list<float>> values);
        mat(std::vector<std::vector<float>>& values);

        /**
         * @brief Accessor for matrix elements (non-const version).
         * @param row Row index.
         * @param col Column index.
         * @return Reference to the element at the specified row and column.
         */
        float& operator()(int row, int col);

        /**
         * @brief Accessor for matrix elements (const version).
         * @param row Row index.
         * @param col Column index.
         * @return Const reference to the element at the specified row and column.
         */
        const float& operator()(int row, int col) const;

        /**
         * @brief Matrix addition.
         * @param other The matrix to subtract.
         * @return The result of the matrix addition.
         */
        mat operator+(const mat& other) const;

        /**
         * @brief Matrix subtraction.
         * @param other The matrix to subtract.
         * @return The result of the matrix subtraction.
         */
        mat operator-(const mat& other) const;

        /**
         * @brief Multiplies the current matrix with another matrix.
         * @param other The matrix to multiply with.
         * @return A new matrix that is the result of the multiplication.
         * @throws std::runtime_error If the dimensions do not match for multiplication.
         */
        mat operator*(const mat& other) const;

        /**
         * @brief Multiplies this vector with another vector.
         * @param other The vector to multiply with.
         * @return The result of the vector multiplication.
         */
        vec operator*(const vec& other) const;

        /**
         * @brief Multiplies the current matrix with a scalar.
         * @param scalar The scalar value to multiply with.
         * @return A new matrix that is the result of the scalar multiplication.
         */
        mat operator*(float scalar) const;

        /**
         * @brief Provides raw access to the underlying data.
         * @return Pointer to the raw data array.
         */
        const float* raw() const;

        /**
         * @brief Creates an identity matrix of size rows x cols.
         * @return An identity matrix.
         */
        static mat identity(int rows, int cols);

        /**
         * @brief Computes the transpose of the matrix.
         * @return A new matrix that is the transpose of the current matrix.
         */
        mat transpose() const;

        /**
         * @brief Computes the inverse of a square matrix.
         * 
         * This function uses Gaussian elimination with partial pivoting to compute
         * the inverse of a square matrix. The matrix must be square (i.e., have the
         * same number of rows and columns) to have an inverse.
         * 
         * @tparam R The number of rows in the matrix.
         * @tparam C The number of columns in the matrix.
         * @return A matrix that is the inverse of the original matrix.
         * @throws std::runtime_error if the matrix is singular and cannot be inverted.
         */
        mat inverse_gauss() const;

        /**
         * @brief Performs LU decomposition of the matrix.
         * 
         * This function decomposes the matrix into a lower triangular matrix (L) 
         * and an upper triangular matrix (U) such that the original matrix is 
         * the product of L and U.
         * 
         * @param L Reference to the matrix where the lower triangular matrix will be stored.
         * @param U Reference to the matrix where the upper triangular matrix will be stored.
         * 
         * @return void
         */
        void lu_decomposition(mat& L, mat& U) const;
        
        /**
         * @brief Computes the inverse of the matrix using LU decomposition.
         * 
         * This function performs LU decomposition on the matrix and then uses
         * forward and backward substitution to compute the inverse.
         * 
         * @return A matrix that is the inverse of the original matrix.
         */
        mat inverse_lud() const;

        /**
         * @brief Logs the matrix to the console.
         */
        void log() const;
    };

} // namespace titan

#include "vec.hpp"
#include "mat.inl"

#endif // TITAN_MAT_HPP