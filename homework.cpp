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

void handleError(string errorMsg) {
	cerr << errorMsg << endl;
	exit(1);
}

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
			handleError("Wrong key format. Keys can consist only from English letters");
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