#ifndef TITAN_HPP
#define TITAN_HPP

#include <cfloat>

#include "titan/basics/mat.hpp"
#include "titan/basics/mat3.hpp"
#include "titan/basics/mat4.hpp"

#include "titan/basics/vec.hpp"
#include "titan/basics/vec3.hpp"
#include "titan/basics/vec4.hpp"

#include "titan/graphics/camera.hpp"
#include "titan/graphics/rotation.hpp"
#include "titan/graphics/translation.hpp"
#include "titan/graphics/decompose.hpp"
#include "titan/graphics/quaternion.hpp"

#include "titan/linalg/basics.hpp"
#include "titan/linalg/eigen.hpp"

namespace titan {
    using real = float;
}

#endif // TITAN_HPP