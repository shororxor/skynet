namespace titan
{

inline vec::vec(int size, float value) : data(size, value) {}

inline vec::vec(std::initializer_list<float> values)
{
    for (auto &val : values)
        data.push_back(val);
}

inline vec::vec(std::vector<float>& values) : data(values) {}

inline float& vec::operator[](int i) { return data[i]; }

inline const float& vec::operator[](int i) const { return data[i]; }

inline vec vec::operator+(const vec& other) const 
{
    if (data.size() != other.data.size())
        std::cerr << "Vectors must have the same size for addition.\n";

    vec result(data.size());
    
    for (size_t i = 0; i < data.size(); ++i)
    {
        result[i] = data[i] + other[i];
    }

    return result;
}

inline vec vec::operator-(const vec& other) const 
{
    if (data.size() != other.data.size())
        std::cerr << "Vectors must have the same size for addition.\n";

    vec result(data.size());
    
    for (size_t i = 0; i < data.size(); ++i)
    {
        result[i] = data[i] - other[i];
    }

    return result;
}

inline vec vec::operator*(const mat& other) const
{
    if (data.size() != other.rows)
        std::cerr << "Vector size must match the number of matrix rows for multiplication\n";

    vec result(other.cols);

    for (size_t j = 0; j < other.cols; ++j)
    {
        for (size_t i = 0; i < data.size(); ++i)
        {
            result[j] += data[i] * other(i, j);
        }
    }

    return result;
}

inline float vec::operator*(const vec& other) const
{
    if (data.size() != other.data.size())
        std::cerr << "Vectors must have the same size for dot product.";

    float result = 0.0f;

    for (size_t i = 0; i < data.size(); ++i)
    {
        result += data[i] * other[i];
    }

    return result;
}

inline vec vec::operator*(float scalar) const 
{
    vec result(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        result[i] = data[i] * scalar;
    }

    return result;
}

inline float vec::size() const
{
    return data.size();
}

inline const float* vec::raw() const
{
    return data.data();
}

inline float vec::dot(const vec& other) const 
{
    if (data.size() != other.data.size())
        std::cerr << "Vectors must have the same size for dot product.";

    float result = 0.0f;

    for (size_t i = 0; i < data.size(); ++i)
    {
        result += data[i] * other[i];
    }

    return result;
}

inline void vec::log() const 
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "vec(";
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::cout << data[i] << (i + 1 == data.size() ? ")" : ", ");
    }
    std::cout << "\n";
}

} // namespace titan