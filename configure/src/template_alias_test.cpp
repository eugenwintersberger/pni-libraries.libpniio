#include<iostream>

template<typename A,typename B> class Template1
{};

template<typename U> using Template2 = Template1<double,U>;

int main(int argc,char **argv)
{
    Template2<int> test; 
    return 0;
}
