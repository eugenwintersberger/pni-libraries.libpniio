#include<iostream>

enum class T1 {one,two,three};

int main(int argc,char **argv)
{
    if(T1::one==T1::one) 
        std::cout<<"== works"<<std::endl;

    if(T1::one!=T1::two) 
        std::cout<<"!= works"<<std::endl;

    if(T1::one>T1::two)
    {
        std::cout<<">works"<<std::endl;
    }
    
    if(T1::one<T1::two)
    {
        std::cout<<"<works"<<std::endl;
    }
    
    if(T1::one>=T1::two)
    {
        std::cout<<">works"<<std::endl;
    }
    
    if(T1::one<=T1::two)
    {
        std::cout<<"<works"<<std::endl;
    }

    return 0;
}
