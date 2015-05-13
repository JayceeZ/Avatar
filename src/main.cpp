#include <iostream>
#include "avatar.h"

#define WITH_SENSOR true
#define NO_SENSOR false

int main(int argc, char *argv[])
{
    std::cout << "\nAvatar Project - Isoard Jean-Christophe" << std::endl;

    CAvatar theAvatar;
    return theAvatar.OnExecute(WITH_SENSOR);
}
