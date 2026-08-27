namespace titan
{

inline vec4::vec4() : data{0.0f, 0.0f, 0.0f, 1.0f} {}

inline vec4::vec4(float x, float y, float z, float w) : data{x, y, z, w} {}

inline vec4::vec4(const vec3& v, float w) : data{v[0], v[1], v[2], w} {}

inline vec4::vec4(std::initializer_list<float> values)
{
    int i = 0;
    for (auto val : values)
        data[i++] = val;
}

inline vec4::vec4(std::vector<float>& values) 
{
    int i = 0;
    for (auto val : values)
        data[i++] = val;
}

inline float& vec4::operator[](int i) { return data[i]; }

inline const float& vec4::operator[](int i) const { return data[i]; }

inline vec4 vec4::operator+(const vec4& other) const 
{
    return vec4(data[0] + other[0], data[1] + other[1], data[2] + other[2], data[3] + other[3]);
}

inline vec4 vec4::operator-(const vec4& other) const 
{
    return vec4(data[0] - other[0], data[1] - other[1], data[2] - other[2], data[3] - other[3]);
}

inline vec vec4::operator*(const mat& other) const
{
    vec result(other.cols);

    for (size_t j = 0; j < other.cols; ++j)
    {
        result[j] = data[0] * other(0, j) + 
                    data[1] * other(1, j) + 
                    data[2] * other(2, j) + 
                    data[3] * other(3, j);
    }
    return result;
}

inline vec4 vec4::operator*(const mat4& other) const
{
    return vec4(
        data[0] * other(0, 0) + data[1] * other(1, 0) + data[2] * other(2, 0) + data[3] * other(3, 0),
        data[0] * other(0, 1) + data[1] * other(1, 1) + data[2] * other(2, 1) + data[3] * other(3, 1),
        data[0] * other(0, 2) + data[1] * other(1, 2) + data[2] * other(2, 2) + data[3] * other(3, 2),
        data[0] * other(0, 3) + data[1] * other(1, 3) + data[2] * other(2, 3) + data[3] * other(3, 3)
    );
}

inline float vec4::operator*(const vec4& other) const
{
    return data[0] * other[0] + data[1] * other[1] + data[2] * other[2] + data[3] * other[3];
}

inline vec4 vec4::operator*(float scalar) const 
{
    return vec4(data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar);
}

inline float* vec4::raw()
{
    return data.data();
}

inline void vec4::zero()
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
    data[3] = 0.0f;
}

inline float vec4::dot(const vec4& other) const 
{
    return data[0] * other[0] + data[1] * other[1] + data[2] * other[2] + data[3] * other[3];
}

inline vec4 vec4::normalized() const
{
    float length = std::sqrt(dot(*this));
    return (length > 0) ? (*this * (1.0f / length)) : *this;
} 

inline float vec4::length() const
{
    return std::sqrt(dot(*this));
}

inline void vec4::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "vec4(" << data[0] << ", " << data[1] << ", " << data[2] << ", " << data[3] << ")\n";
}

} // namespace titan
