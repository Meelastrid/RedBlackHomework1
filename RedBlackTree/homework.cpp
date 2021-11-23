#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

enum Colors {
	RED,
	BLACK
};

struct TempNode {
	string sign;
	string key;
	unsigned long long value;
};

typedef struct MyNode
{
	Colors color;
    string key;
    unsigned long long value;
	struct MyNode *parent;
	struct MyNode *right;
	struct MyNode *left;

	MyNode(Colors color, string key, unsigned long long value, struct MyNode *parent, struct MyNode *right, struct
			MyNode *left) {
		this->color = color;
		this->key = key;
		this->value = value;
		this->parent = parent;
		this->right = right;
		this->left = left;
	}
} Node;

Node *leaf;
leaf = new Node(RED, 0, 0, 0, leaf, leaf);
Node *root = leaf;

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

void insertElement(MyNode tempNode) {
    std::cout << "insertion operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
}

void deleteElement(MyNode tempNode) {
    std::cout << "deletion operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
}

bool searchElement(MyNode tempNode) {
    std::cout << "searching operation:" << endl << "key: " << tempNode.key << std::endl << "value: " << tempNode.value << endl << endl;
    return true;
}

int main() {
    unsigned int numberOfWords;
    string sign;
    string str;
	TempNode tempNode;
    std::ifstream file("bcinput.txt");

	cout << "addres of NIL is: " << endl;

    while (std::getline(file, str)) {
        if (str[0] == '\0')
            break;
        numberOfWords = total_words(str);
        if (numberOfWords > 3 || numberOfWords == 0)
            handleError("Wrong number of arguments");
        parseString(str, sign, tempNode, numberOfWords);
        keyValidation(tempNode.key);

        if (numberOfWords == 3 && sign[0] == '+')
            insertElement(tempNode);
        else if (numberOfWords == 2 && sign[0] == '-')
            deleteElement(tempNode);
        else if (numberOfWords == 1)
            searchElement(tempNode);
        else
            handleError("Unexpected error!!!");
    }
    return 0;
}