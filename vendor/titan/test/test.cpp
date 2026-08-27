#include "titan/titan.hpp"

using namespace titan;

int main()
{
    mat4 A = {
        1, 2, 3, 6,
        5, 2, 3, 2,
        9, 10, 7, 9,
        9, 10, 7, 9,
    };

    A.log();
}