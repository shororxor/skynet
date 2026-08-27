#ifndef TITAN_TRANSLATION_HPP
#define TITAN_TRANSLATION_HPP

#include "vec3.hpp"
#include "constants.hpp"

namespace titan
{
    /**
     * @brief
     * @param
     * @return
     */
    inline mat4 Translate(vec3& p)
    {
        mat4 T = mat4::identity();

        T(0,3) = -p[0];
        T(1,3) = -p[1];
        T(2,3) = -p[2];

        return T;
    }

    inline mat4 Transcale(vec3& p, vec3& s)
    {
        mat4 T;

        T(0,0) = s[0]; 
        T(1,1) = s[1]; 
        T(2,2) = s[2];

        T(0,3) = p[0];
        T(1,3) = p[1];
        T(2,3) = p[2];
        T(3,3) = 1.0f;

        return T;
    }


} // namespace titan


#endif // TITAN_TRANSLATION_HPP