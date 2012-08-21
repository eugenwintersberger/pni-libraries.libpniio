#include<iostream>
#include<random>

int main(int argc,char **argv)
{

    std::mt19937_64 engine;
    std::uniform_int_distribution<> dist(1,10);

    return 0;
}
