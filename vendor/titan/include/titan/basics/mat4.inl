namespace titan
{

inline mat4::mat4() 
{
    data.fill(0.0f);
}

inline mat4::mat4(std::initializer_list<float> values) 
{
    auto it = values.begin();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[j * 4 + i] = *(it++);
}

inline mat4::mat4(std::vector<float>& values) 
{
    auto it = values.begin();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            data[j * 4 + i] = *(it++);
}

inline float& mat4::operator()(int row, int col) 
{
    return data[col * 4 + row];
}

inline const float& mat4::operator()(int row, int col) const 
{
    return data[col * 4 + row];
}

inline mat4 mat4::operator+(const mat4& other) const
{
    mat4 result;
    for (int i = 0; i < 16; ++i) 
        result.data[i] = data[i] + other.data[i];
    return result;
}

inline mat4 mat4::operator-(const mat4& other) const 
{
    mat4 result;
    for (int i = 0; i < 16; ++i) 
        result.data[i] = data[i] - other.data[i];
    return result;
}

inline mat mat4::operator*(const mat& other) const
{
    if (other.rows != 4) 
        std::cerr << "Matrix dimensions do not match for multiplication.\n";

    mat result(4, other.cols);

    for (int j = 0; j < other.cols; ++j) 
    {
        result(0, j) = (*this)(0, 0) * other(0, j) + (*this)(0, 1) * other(1, j) + (*this)(0, 2) * other(2, j) + (*this)(0, 3) * other(3, j);
        result(1, j) = (*this)(1, 0) * other(0, j) + (*this)(1, 1) * other(1, j) + (*this)(1, 2) * other(2, j) + (*this)(1, 3) * other(3, j);
        result(2, j) = (*this)(2, 0) * other(0, j) + (*this)(2, 1) * other(1, j) + (*this)(2, 2) * other(2, j) + (*this)(2, 3) * other(3, j);
        result(3, j) = (*this)(3, 0) * other(0, j) + (*this)(3, 1) * other(1, j) + (*this)(3, 2) * other(2, j) + (*this)(3, 3) * other(3, j);
    }

    return result;
}

inline mat4 mat4::operator*(const mat4& other) const 
{
    mat4 result;
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            result(i, j) = (*this)(i, 0) * other(0, j) +
                            (*this)(i, 1) * other(1, j) +
                            (*this)(i, 2) * other(2, j) +
                            (*this)(i, 3) * other(3, j);
        }
    }
    return result;
}

inline vec4 mat4::operator*(const vec4& other) const
{
    vec4 result;

    result[0] = (*this)(0, 0) * other[0] + (*this)(0, 1) * other[1] + (*this)(0, 2) * other[2] + (*this)(0, 3) * other[3];
    result[1] = (*this)(1, 0) * other[0] + (*this)(1, 1) * other[1] + (*this)(1, 2) * other[2] + (*this)(1, 3) * other[3];
    result[2] = (*this)(2, 0) * other[0] + (*this)(2, 1) * other[1] + (*this)(2, 2) * other[2] + (*this)(2, 3) * other[3];
    result[3] = (*this)(3, 0) * other[0] + (*this)(3, 1) * other[1] + (*this)(3, 2) * other[2] + (*this)(3, 3) * other[3];

    return result;
}

inline vec3 mat4::operator*(const vec3& other) const
{
    vec3 result;

    result[0] = (*this)(0, 0) * other[0] + (*this)(0, 1) * other[1] + (*this)(0, 2) * other[2] + (*this)(0, 3) * 1;
    result[1] = (*this)(1, 0) * other[0] + (*this)(1, 1) * other[1] + (*this)(1, 2) * other[2] + (*this)(1, 3) * 1;
    result[2] = (*this)(2, 0) * other[0] + (*this)(2, 1) * other[1] + (*this)(2, 2) * other[2] + (*this)(2, 3) * 1;

    return result;
}

inline std::vector<vec3> mat4::operator*(const std::vector<vec3>& list) const
{
    std::vector<vec3> result;

    for (const vec3& v : list)
        result.push_back((*this) * v);

    return result;
}

inline mat4 mat4::operator*(float scalar) const 
{
    mat4 result;
    for (int i = 0; i < 16; ++i) result.data[i] = data[i] * scalar;
    return result;
}

inline float* mat4::raw()
{
    return data.data();
}

inline vec4 mat4::col(int index) const
{
    return vec4((*this)(index, 0), (*this)(index, 1), (*this)(index, 2), (*this)(index, 3));
}

inline mat4 mat4::identity() 
{
    mat4 I;
    I(0,0) = 1.0f; I(1,1) = 1.0f; I(2,2) = 1.0f; I(3,3) = 1.0f;
    return I;
}

inline mat4 mat4::transpose() const 
{
    mat4 t = *this;
    std::swap(t(0, 1), t(1, 0));
    std::swap(t(0, 2), t(2, 0));
    std::swap(t(0, 3), t(3, 0));
    std::swap(t(1, 2), t(2, 1));
    std::swap(t(1, 3), t(3, 1));
    std::swap(t(2, 3), t(3, 2));
    return t;
}

inline float mat4::determinant() const 
{
    float det = 0.0f;
    
    det += (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) * (*this)(3, 3) + (*this)(1, 2) * (*this)(2, 3) * (*this)(3, 1) + (*this)(1, 3) * (*this)(2, 1) * (*this)(3, 2)
                          - (*this)(1, 3) * (*this)(2, 2) * (*this)(3, 1) - (*this)(1, 1) * (*this)(2, 3) * (*this)(3, 2) - (*this)(1, 2) * (*this)(2, 1) * (*this)(3, 3));
    det -= (*this)(0, 1) * ((*this)(1, 0) * (*this)(2, 2) * (*this)(3, 3) + (*this)(1, 2) * (*this)(2, 3) * (*this)(3, 0) + (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 2)
                          - (*this)(1, 3) * (*this)(2, 2) * (*this)(3, 0) - (*this)(1, 0) * (*this)(2, 3) * (*this)(3, 2) - (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 3));
    det += (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) * (*this)(3, 3) + (*this)(1, 1) * (*this)(2, 3) * (*this)(3, 0) + (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 1)
                          - (*this)(1, 3) * (*this)(2, 1) * (*this)(3, 0) - (*this)(1, 0) * (*this)(2, 3) * (*this)(3, 1) - (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 3));
    det -= (*this)(0, 3) * ((*this)(1, 0) * (*this)(2, 1) * (*this)(3, 2) + (*this)(1, 1) * (*this)(2, 2) * (*this)(3, 0) + (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 1)
                          - (*this)(1, 2) * (*this)(2, 1) * (*this)(3, 0) - (*this)(1, 0) * (*this)(2, 2) * (*this)(3, 1) - (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 2));
    return det;
}

inline mat4 mat4::inverse() const 
{
    mat4 inv;
    float det;
    int i;

    inv(0, 0) = (*this)(1, 1) * (*this)(2, 2) * (*this)(3, 3) - 
                (*this)(1, 1) * (*this)(2, 3) * (*this)(3, 2) - 
                (*this)(2, 1) * (*this)(1, 2) * (*this)(3, 3) + 
                (*this)(2, 1) * (*this)(1, 3) * (*this)(3, 2) +
                (*this)(3, 1) * (*this)(1, 2) * (*this)(2, 3) - 
                (*this)(3, 1) * (*this)(1, 3) * (*this)(2, 2);

    det = (*this)(0, 0) * inv(0, 0);

    if (std::abs(det) < 1e-6) throw std::runtime_error("Matrix is singular");

    return inv * (1.0f / det);
}

inline void mat4::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < 4; ++i) 
    {
        std::cout << (*this)(i, 0) << " " 
                  << (*this)(i, 1) << " " 
                  << (*this)(i, 2) << " "
                  << (*this)(i, 3) << "\n";
    }
    std::cout << "\n";
}


} // namespace titan