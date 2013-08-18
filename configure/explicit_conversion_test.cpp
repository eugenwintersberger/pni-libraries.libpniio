#include<iostream>

class test_t
{
    public:
    explicit operator bool () const { return true; }
};

int main(int argc,char **argv)
{
    test_t test;
    return 0;
}
