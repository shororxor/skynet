namespace titan
{

inline mat::mat(int r, int c) : rows(r), cols(c), data(r * c, 0.0f) {}

inline mat::mat(std::initializer_list<float> values) : data(values) {}

inline mat::mat(std::vector<float>& values) : data(values) {}

inline mat::mat(std::initializer_list<std::initializer_list<float>> values)
    : rows(values.size()), cols(values.begin()->size()), data(rows * cols, 0.0f) 
{
    int i, j = 0;

    for (const auto& row : values) 
    {
        j = 0;
        for (float val : row) 
        {
            data[j * rows + i] = val;
            j++;
        }
        i++;
    }  
}

inline mat::mat(std::vector<std::vector<float>>& values)
    : rows(values.size()), cols(values.begin()->size()), data(rows * cols, 0.0f)
{
    int i = 0;

    for (int col = 0; col < cols; ++col) 
    {
        for (int row = 0; row < rows; ++row) 
        {
            data[i++] = values[row][col];
        }
    }
}

inline float& mat::operator()(int row, int col) 
{
    return data[col * rows + row];
}

inline const float& mat::operator()(int row, int col) const 
{
    return data[col * rows + row];
}

inline mat mat::operator+(const mat& other) const
{
    if (rows != other.rows || cols != other.cols)
        std::cerr << "Matrix dimensions must match for addition.\n";

    mat result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) 
        result.data[i] = data[i] + other.data[i];
    return result;
}

inline mat mat::operator-(const mat& other) const
{
    mat result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) 
        result.data[i] = data[i] - other.data[i];
    return result;
}

inline mat mat::operator*(const mat& other) const 
{
    if (cols != other.rows)
    {
        std::cerr << "Matrix dimensions do not match for multiplication.\n";
    }

    mat result(rows, other.cols);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < other.cols; ++j) 
        {
            for (int k = 0; k < cols; ++k) 
            {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

inline vec mat::operator*(const vec& other) const
{
    if (cols != other.size())
        std::cerr << "Matrix and vector size mismatch\n";

    vec result(rows);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result[i] += (*this)(i, j) * other[j];

    return result;
}

inline mat mat::operator*(float scalar) const 
{
    mat result(rows, cols);

    for (size_t i = 0; i < rows * cols; ++i) 
    {
        result.data[i] = data[i] * scalar;
    }

    return result;
}

inline const float* mat::raw() const 
{
    return data.data();
}

inline mat mat::identity(int rows, int cols)
{
    mat I(rows, cols);
    for (int i = 0; i < rows; ++i)
        I(i, i) = 1.0f;
    return I;
}

inline mat mat::transpose() const 
{
    mat t(cols, rows);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            t(j, i) = (*this)(i, j);
    return t;
}

inline mat mat::inverse_gauss() const
{
    if (rows == cols)
    {
        std::cerr << "Matrix must be square to compute the inverse\n";
    }
    
    mat aug = *this;
    mat inv = identity(rows, cols);
    
    for (int i = 0; i < rows; ++i)
    {
        int pivot = i;

        for (int k = i + 1; k < rows; ++k)
        {
            if (std::abs(aug(k, i)) > std::abs(aug(pivot, i)))
            {
                pivot = k;
            }
        }
        
        if (pivot != i)
        {
            for (int j = 0; j < rows; ++j)
            {
                std::swap(aug(i, j), aug(pivot, j));
                std::swap(inv(i, j), inv(pivot, j));
            }
        }
        
        if (aug(i, i) == 0.0f)
        {
            std::cerr << "Matrix is singular and cannot be inverted\n";
        }
        
        float norm = aug(i, i);

        for (int j = 0; j < rows; ++j)
        {
            aug(i, j) /= norm;
            inv(i, j) /= norm;
        }
        
        for (int k = 0; k < rows; ++k)
        {
            if (k != i)
            {
                float factor = aug(k, i);
                
                for (int j = 0; j < rows; ++j)
                {
                    aug(k, j) -= factor * aug(i, j);
                    inv(k, j) -= factor * inv(i, j);
                }
            }
        }
    }
    
    return inv;
}

inline void mat::lu_decomposition(mat& L, mat& U) const
{
    L = identity(rows, cols);
    U = *this;
    
    for (int i = 0; i < rows; ++i)
    {
        for (int j = i + 1; j < rows; ++j)
        {
            float factor = U(j, i) / U(i, i);

            L(j, i) = factor;
            
            for (int k = i; k < rows; ++k)
            {
                U(j, k) -= factor * U(i, k);
            }
        }
    }
}

inline mat mat::inverse_lud() const
{
    if (rows != cols)
    {
        std::cerr << "Matrix is singular and cannot be inverted";
    }

    mat inv(rows, cols);
    mat L(rows, cols);
    mat U(rows, cols);

    lu_decomposition(L, U);
    
    for (int i = 0; i < rows; ++i)
    {
        mat e = identity(rows, cols);
        mat tmp(rows, cols);
        
        for (int j = 0; j < rows; ++j)
        {
            tmp(j, i) = e(j, i);

            for (int k = 0; k < j; ++k)
            {
                tmp(j, i) -= L(j, k) * tmp(k, i);
            }

            tmp(j, i) /= L(j, j);
        }
        
        for (int j = rows - 1; j >= 0; --j)
        {
            inv(j, i) = tmp(j, i);

            for (int k = j + 1; k < rows; ++k)
            {
                inv(j, i) -= U(j, k) * inv(k, i);
            }

            inv(j, i) /= U(j, j);
        }
    }
    return inv;
}

inline void mat::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


} // namespace titan