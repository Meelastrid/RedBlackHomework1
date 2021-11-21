#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;
struct MyNode
{
    string key;
    unsigned long long value;
};

void parseString(string &str, string &sign, MyNode &tempNode, unsigned int numberOfWords); 
int total_words(string &str);
void keyValidation(string key);


void handleError(string errorMsg) {
    cerr << errorMsg << endl;
    exit(1);
}

void insertElement(std::vector<MyNode> &dictionary, MyNode tempNode) {
    std::cout << "insertion operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
}

void deleteElement(std::vector<MyNode> &dictionary, MyNode tempNode) {
    std::cout << "deletion operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
}

bool searchElement(std::vector<MyNode> dictionary, MyNode tempNode) {
    std::cout << "searching operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
    return true;
}

int main() {
    unsigned int numberOfWords;
    MyNode tempNode;
    string sign;
    string str;
    std::ifstream file("bcinput.txt");

    std::vector<MyNode> dictionary;

    while (std::getline(file, str)) {
        if (str[0] == '\0')
            break;
        numberOfWords = total_words(str);
        if (numberOfWords > 3 || numberOfWords == 0)
            handleError("Wrong number of arguments");
        parseString(str, sign, tempNode, numberOfWords);
        keyValidation(tempNode.key);

        if (numberOfWords == 3 && sign[0] == '+')
            insertElement(dictionary, tempNode);
        else if (numberOfWords == 2 && sign[0] == '-')
            deleteElement(dictionary, tempNode);
        else if (numberOfWords == 1)
            searchElement(dictionary, tempNode);
        else
            handleError("Unexpected error!!!");
    }
    return 0;
}