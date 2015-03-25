#include <iostream>
#include "avatar.h"

#define WITH_SENSOR true

int main(int argc, char *argv[])
{
	std::cout << "\nThe Avatar Project!" << std::endl;

    CAvatar theAvatar;
    return theAvatar.OnExecute(WITH_SENSOR);
}
