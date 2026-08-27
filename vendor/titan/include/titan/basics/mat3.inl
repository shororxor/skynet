namespace titan
{

inline mat3::mat3() {
    data.fill(0.0f);
}

inline mat3::mat3(std::initializer_list<float> values)
{
    auto it = values.begin();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            data[j * 3 + j] = *(it++);
}

inline mat3::mat3(std::vector<float>& values)
{
    auto it = values.begin();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            data[j * 3 + i] = *(it++);
}

inline float& mat3::operator()(int row, int col) 
{
    return data[col * 3 + row];
}

inline const float& mat3::operator()(int row, int col) const 
{
    return data[col * 3 + row];
}

inline mat3 mat3::operator+(const mat3& other) const
{
    mat3 result;
    for (int i = 0; i < 9; ++i) 
        result.data[i] = data[i] + other.data[i];
    return result;
}

inline mat3 mat3::operator-(const mat3& other) const 
{
    mat3 result;
    for (int i = 0; i < 9; ++i) 
        result.data[i] = data[i] - other.data[i];
    return result;
}

inline mat mat3::operator*(const mat& other) const
{
    if (other.rows != 3) 
        std::cerr << "Matrix dimensions do not match for multiplication.\n";

    mat result(3, other.cols);

    for (int j = 0; j < other.cols; ++j) 
    {
        result(0, j) = (*this)(0, 0) * other(0, j) + (*this)(0, 1) * other(1, j) + (*this)(0, 2) * other(2, j);
        result(1, j) = (*this)(1, 0) * other(0, j) + (*this)(1, 1) * other(1, j) + (*this)(1, 2) * other(2, j);
        result(2, j) = (*this)(2, 0) * other(0, j) + (*this)(2, 1) * other(1, j) + (*this)(2, 2) * other(2, j);
    }

    return result;
}

inline mat3 mat3::operator*(const mat3& other) const 
{
    mat3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(i, j) = (*this)(i, 0) * other(0, j) +
                           (*this)(i, 1) * other(1, j) +
                           (*this)(i, 2) * other(2, j);
        }
    }
    return result;
}

inline vec3 mat3::operator*(const vec3& other) const 
{
    vec3 result;
    result[0] = (*this)(0, 0) * other[0] + (*this)(0, 1) * other[1] + (*this)(0, 2) * other[2];
    result[1] = (*this)(1, 0) * other[0] + (*this)(1, 1) * other[1] + (*this)(1, 2) * other[2];
    result[2] = (*this)(2, 0) * other[0] + (*this)(2, 1) * other[1] + (*this)(2, 2) * other[2];
    return result;
}

inline mat3 mat3::operator*(float scalar) const 
{
    mat3 result;
    for (int i = 0; i < 9; ++i) result.data[i] = data[i] * scalar;
    return result;
}

inline float* mat3::raw() 
{
    return data.data();
}

inline vec3 mat3::col(int index) const
{
    return vec3((*this)(index, 0), (*this)(index, 1), (*this)(index, 2));
}

inline mat3 mat3::identity() 
{
    mat3 I;
    I(0,0) = 1.0f; I(1,1) = 1.0f; I(2,2) = 1.0f;
    return I;
}

inline mat3 mat3::transpose() const 
{
    mat3 t = *this;
    std::swap(t(0, 1), t(1, 0));
    std::swap(t(0, 2), t(2, 0));
    std::swap(t(1, 2), t(2, 1));
    return t;
}

inline float mat3::determinant() const 
{
    return    (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1))
            - (*this)(0, 1) * ((*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0))
            + (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0));
}

inline mat3 mat3::inverse() const 
{
    float det = determinant();
    if (std::abs(det) < 1e-6) throw std::runtime_error("Matrix is singular");

    mat3 adj;
    adj(0, 0) =  (*this)(1, 1)  * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1);
    adj(0, 1) = -((*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0));
    adj(0, 2) =  (*this)(1, 0)  * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0);

    adj(1, 0) = -((*this)(0, 1) * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 1));
    adj(1, 1) =  (*this)(0, 0)  * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 0);
    adj(1, 2) = -((*this)(0, 0) * (*this)(2, 1) - (*this)(0, 1) * (*this)(2, 0));

    adj(2, 0) =  (*this)(0, 1)  * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 1);
    adj(2, 1) = -((*this)(0, 0) * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 0));
    adj(2, 2) =  (*this)(0, 0)  * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);

    return adj * (1.0f / det);
}

inline void mat3::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < 3; ++i) 
    {
        std::cout << (*this)(i, 0) << " " 
                  << (*this)(i, 1) << " " 
                  << (*this)(i, 2) << "\n";
    }
    std::cout << "\n";
}

} // namespace titan