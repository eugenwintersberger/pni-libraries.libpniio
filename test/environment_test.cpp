#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

int main()
{
    std::string path_value(std::getenv("PATH"));

    std::ofstream stream("test_environment.txt");
    stream<<"PATH = "<<path_value<<std::endl;
    stream.close();


    return 0;
}
