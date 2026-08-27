namespace titan
{

inline vec3::vec3() : data{0.0f, 0.0f, 0.0f} {}

inline vec3::vec3(float x, float y, float z) : data{x, y, z} {}

inline vec3::vec3(const float* vec) {
    data[0] = vec[0];
    data[1] = vec[1];
    data[2] = vec[2];
}

inline vec3::vec3(vec4& vec) {
    data[0] = vec[0];
    data[1] = vec[1];
    data[2] = vec[2];
}

inline vec3::vec3(std::initializer_list<float> values)
{
    int i = 0;
    for (auto val : values)
        data[i++] = val;
}

inline vec3::vec3(std::vector<float>& values) 
{
    int i = 0;
    for (auto val : values)
        data[i++] = val;
}

inline float& vec3::operator[](int i) { return data[i]; }

inline const float& vec3::operator[](int i) const { return data[i]; }

inline vec3 vec3::operator+(const vec3& other) const 
{
    return vec3(data[0] + other[0], data[1] + other[1], data[2] + other[2]);
}

inline vec3 vec3::operator-(const vec3& other) const 
{
    return vec3(data[0] - other[0], data[1] - other[1], data[2] - other[2]);
}

inline vec vec3::operator*(const mat& other) const
{
    vec result(other.cols);

    for (size_t j = 0; j < other.cols; ++j)
    {
        result[j] = data[0] * other(0, j) + 
                    data[1] * other(1, j) + 
                    data[2] * other(2, j);
    }
    return result;
}

inline vec3 vec3::operator*(const mat3& other) const
{
    return vec3(
        data[0] * other(0,0) + data[1] * other(1,0) + data[2] * other(2,0),
        data[0] * other(0,1) + data[1] * other(1,1) + data[2] * other(2,1),
        data[0] * other(0,2) + data[1] * other(1,2) + data[2] * other(2,2)
    );
}

inline float vec3::operator*(const vec3& other) const
{
    return data[0] * other[0] + data[1] * other[1] + data[2] * other[2]; 
}

inline vec3 vec3::operator*(float scalar) const 
{
    return vec3(data[0] * scalar, data[1] * scalar, data[2] * scalar);
}

inline vec3 vec3::operator^(const vec3& other) const
{
    return vec3(
        data[1] * other[2] - data[2] * other[1],
        data[2] * other[0] - data[0] * other[2],
        data[0] * other[1] - data[1] * other[0]
    );
}

inline vec3 vec3::operator-() const
{
    return vec3(-data[0], -data[1], -data[2]);
}

inline float* vec3::raw()
{
    return data.data();
}

inline void vec3::zero()
{
    data[0] = 0.0f;
    data[1] = 0.0f;
    data[2] = 0.0f;
}

inline float vec3::dot(const vec3& other) const 
{
    return data[0] * other[0] + data[1] * other[1] + data[2] * other[2];
}

inline vec3 vec3::cross(const vec3& other) const 
{
    return vec3(
        data[1] * other[2] - data[2] * other[1],
        data[2] * other[0] - data[0] * other[2],
        data[0] * other[1] - data[1] * other[0]
    );
}

inline vec3 vec3::normalized() const 
{
    float length = std::sqrt(dot(*this));
    return (length > 0) ? (*this * (1.0f / length)) : *this;
}

inline float vec3::length() const
{
    return std::sqrt(dot(*this));
}

inline void vec3::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "vec3(" << data[0] << ", " << data[1] << ", " << data[2] << ")\n";
}

} // namespace titan