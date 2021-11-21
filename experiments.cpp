#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

int main()
{
    g str;
    ifstream file("bcinput.txt");
    getline(file, str);
    stringstream ss(str);
    int count = 0;
    while(!ss.eof())
    {
        string s;
        ss >> s;
        ++count;
    }
    string sign;
    string key;
    string tempValue;

    if(count == 3)
    {
        stringstream ss(str);
        ss >> sign;
        if(sign.size() == 1 && sign[0] == '+')
            ss >> key >> tempValue;   
    }

    if(count == 2)
    {
        stringstream ss(str);
        ss >> sign;
        if(sign.size() == 1 && sign[0] == '-')
        ss >> key;
    }

    if(count == 1)
    {
        stringstream ss(str);
        ss >> key;
    }

    std::cout << "sign: " << sign << std::endl << "key: " << key << std::endl << "value: " << tempValue << std::endl;

    unsigned long long value = atoi(tempValue.c_str());

}