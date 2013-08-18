#include <functional>
#include <iostream>

int main(int argc,char **argv)
{
    auto f = [](size_t x) { 
        std::cout<<x<<std::endl;
    };

    f(10);

    return 0;
}
