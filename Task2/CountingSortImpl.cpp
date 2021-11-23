#include <string>
#include <iostream>
#include <sstream>

void countingSort(int initialArray[], int arraySize, int numberRange)

using namespace std;

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

int	main(void) {
	string str;
	ifstream file("input.txt");
	int numberOfWords;
	while (getline(file, str)) {
		if (str[0] == '\0')
			break;
		numberOfWords = total_words(str);
		if (numberOfWords != 2)
			break;

	}
	return (0);
}
