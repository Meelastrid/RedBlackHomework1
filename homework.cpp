#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct MyNode
{
    string key;
    unsigned long long value;
};

void handleError(string errorMsg) {
    std::cerr << errorMsg << endl;
    exit(1);
}

int total_words(char *str){
   int count = 0;
   int temp = 0;
   while (*str){
      if (*str == ' ' || *str == '\n' || *str == '\t'){
         temp = 0;
      }
      else if(temp == 0){
         temp = 1;
         count++;
      }
      ++str;
   }
   return count;
}

void insertElement(std::vector<MyNode> &dictionary, MyNode tempNode) {
}

void deleteElement(std::vector<MyNode> &dictionary, MyNode tempNode) {
}

bool searchElement(std::vector<MyNode> dictionary, MyNode tempNode) {

}

void parse(string &str, char &sign, MyNode &tempNode, int numberOfWords) {
    if (numberOfWords == 3) {
    }
}



int main() {
    int numberOfWords;
    MyNode tempNode;
    char sign;
    string str;

    std::vector<MyNode> dictionary;

    while (std::getline(cin, str)) {
        if (str[0] == '\0')
            break;
        if((numberOfWords = total_words(&(str[0]))) > 3)
            handleError("Too many arguments");


        if (numberOfWords == 3 && sign == '+') {
            insertElement(dictionary, tempNode);
        }
        else if (numberOfWords == 2) {
            deleteElement(dictionary, tempNode);
        }
        else if (numberOfWords == 1) {
            searchElement(dictionary, tempNode);
        }
        else
            handleError("Unexpected error!!!");
    }
    return 0;
}