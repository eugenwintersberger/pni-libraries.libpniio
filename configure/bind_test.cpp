#include<iostream>
#include<functional>

void func(double x)
{
    std::cout<<x<<std::endl;
}

int main(int argc,char **argv)
{
    auto f = std::bind(func,double(102.3));
    f();

    return 0;
}
