#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/stl_bind.h"
#include "pybind11/chrono.h"
#include <pybind11/complex.h>
#include "pybind11/functional.h"

#include "mat.hpp"
#include "mat3.hpp"
#include "mat4.hpp"

#include "vec.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

using namespace titan;
namespace py = pybind11;

PYBIND11_MODULE(titan, handle)
{
    handle.doc() = "This is titan math library";

    py::class_<mat>(handle, "mat")

        .def(py::init<int, int>())
        .def(py::init<std::vector<float>&>())
        .def(py::init<std::vector<std::vector<float>>&>())
       
        .def("__call__", py::overload_cast<int, int>(&mat::operator(), py::const_), py::return_value_policy::reference)
        .def("__add__", &mat::operator+)
        .def("__sub__", &mat::operator-)
        .def("__mul__", py::overload_cast<const mat&>(&mat::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec&>(&mat::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&mat::operator*, py::const_))

        .def_static("identity", &mat::identity)
        .def("transpose", &mat::transpose)
        .def("inverse_gauss", &mat::inverse_gauss)
        .def("inverse_lud", &mat::inverse_lud)
        .def("lu_decomposition", &mat::lu_decomposition)
        .def("log", &mat::log);


    py::class_<mat3>(handle, "mat3")

        .def(py::init<std::vector<float>&>())

        .def("__call__", py::overload_cast<int, int>(&mat3::operator(), py::const_), py::return_value_policy::reference)
        .def("__add__", &mat3::operator+)
        .def("__sub__", &mat3::operator-)

        .def("__mul__", py::overload_cast<const mat&>(&mat3::operator*, py::const_))
        .def("__mul__", py::overload_cast<const mat3&>(&mat3::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec3&>(&mat3::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&mat3::operator*, py::const_))

        .def_static("identity", &mat3::identity)
        .def("transpose", &mat3::transpose)
        .def("determinant", &mat3::determinant)
        .def("inverse", &mat3::inverse)
        .def("log", &mat3::log);


    py::class_<mat4>(handle, "mat4")

        .def(py::init<std::vector<float>&>())

        .def("__call__", py::overload_cast<int, int>(&mat4::operator(), py::const_), py::return_value_policy::reference)
        .def("__add__", &mat4::operator+)
        .def("__sub__", &mat4::operator-)

        .def("__mul__", py::overload_cast<const mat&>(&mat4::operator*, py::const_))
        .def("__mul__", py::overload_cast<const mat4&>(&mat4::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec4&>(&mat4::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&mat4::operator*, py::const_))

        .def_static("identity", &mat4::identity)
        .def("transpose", &mat4::transpose)
        .def("determinant", &mat4::determinant)
        .def("inverse", &mat4::inverse)
        .def("log", &mat4::log);

    py::class_<vec>(handle, "vec")

        .def(py::init<std::vector<float>&>())
        .def(py::init<int, float>(), py::arg("size"), py::arg("value") = 0.0f)

        .def("__getitem__", [](vec &v, int i) -> float&  { return v[i]; })
        .def("__setitem__", [](vec &v, int i, float val) { v[i] = val;  })
        .def("__len__", [](const vec &v) { return v.size(); })
        .def("__add__", &vec::operator+)
        .def("__sub__", &vec::operator-)

        .def("__mul__", py::overload_cast<const mat&>(&vec::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec&>(&vec::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&vec::operator*, py::const_))

        .def("size", &vec::size)
        .def("dot", &vec::dot)
        .def("log", &vec::log);

    py::class_<vec3>(handle, "vec3")

        .def(py::init<std::vector<float>&>())
        .def(py::init<float, float, float>())

        .def("__getitem__", [](vec3 &v, int i) -> float&  { return v[i]; })
        .def("__setitem__", [](vec3 &v, int i, float val) { v[i] = val;  })
        .def("__len__", [](const vec3 &v) { return 3; })
        .def("__add__", &vec3::operator+)
        .def("__sub__", &vec3::operator-)

        .def("__mul__", py::overload_cast<const mat&>(&vec3::operator*, py::const_))
        .def("__mul__", py::overload_cast<const mat3&>(&vec3::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec3&>(&vec3::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&vec3::operator*, py::const_))

        .def("dot", &vec3::dot)
        .def("cross", &vec3::cross)
        .def("normalized", &vec3::normalized)
        .def("length", &vec3::length)
        .def("log", &vec3::log);

    py::class_<vec4>(handle, "vec4")

        .def(py::init<std::vector<float>&>())
        .def(py::init<const vec3&, float>(), py::arg("v"), py::arg("w") = 1.0f)
        .def(py::init<float, float, float, float>(), py::arg("x"), py::arg("y"), py::arg("z"), py::arg("w") = 1.0f)

        .def("__getitem__", [](vec4 &v, int i) -> float&  { return v[i]; })
        .def("__setitem__", [](vec4 &v, int i, float val) { v[i] = val;  })
        .def("__len__", [](const vec4 &v) { return 3; })
        .def("__add__", &vec4::operator+)
        .def("__sub__", &vec4::operator-)

        .def("__mul__", py::overload_cast<const mat&>(&vec4::operator*, py::const_))
        .def("__mul__", py::overload_cast<const mat4&>(&vec4::operator*, py::const_))
        .def("__mul__", py::overload_cast<const vec4&>(&vec4::operator*, py::const_))
        .def("__mul__", py::overload_cast<float>(&vec4::operator*, py::const_))

        .def("dot", &vec4::dot)
        .def("normalized", &vec4::normalized)
        .def("length", &vec4::length)
        .def("log", &vec4::log);
}