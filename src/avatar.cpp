#include "avatar.h"
#include <iostream>

Avatar::Avatar()
{
}

int Avatar::OnExecute() {
    std::cout << "OnExecute" << std::endl;
    return 0;
}
