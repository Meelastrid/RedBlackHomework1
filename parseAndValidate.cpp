#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;
void handleError(string errorMsg);

struct MyNode
{
    string key;
    unsigned long long value;
};

int total_words(string &str){
    stringstream ss(str);
    int count = 0;
    while(!ss.eof())
    {
        string s;
        ss >> s;
        ++count;
    }
   return count;
}

bool isEnglishAlpha(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return true;
    else
        return false;
}

void keyValidation(string key) {
    if (key.size() > 256)
       handleError("Too long key. Need to be up to 256");
    for (int i = 0; i < key.size(); i++)
        if (!isEnglishAlpha(key[i]))
            handleError("Wrong key format. Keys can consist only English letters");
}

void parseString(string &str, string &sign, MyNode &tempNode, unsigned int numberOfWords) {
    string tempValue;

    if(numberOfWords == 3)
    {
        stringstream ss(str);
        ss >> sign;
        if(sign.size() == 1 && sign[0] == '+')
            ss >> tempNode.key >> tempValue;   
    }
    else if(numberOfWords == 2)
    {
        stringstream ss(str);
        ss >> sign;
        if(sign.size() == 1 && sign[0] == '-')
            ss >> tempNode.key;
    }
    else if(numberOfWords == 1)
    {
        stringstream ss(str);
        ss >> tempNode.key;
    }
    tempNode.value = atoi(tempValue.c_str());
}
