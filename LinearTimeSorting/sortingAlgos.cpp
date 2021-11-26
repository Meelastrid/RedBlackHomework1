#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct	s_node {
	string key;
	string value;
	s_node *next;
};

struct arrWrap {
	int size;
	int *arr;
	arrWrap(int sizeOfArray) {
		size = sizeOfArray;
		arr = new int[size];
	}
};

using namespace std;

arrWrap *countingSort(int initialArray[], int arraySize, int numberRange)
{
	int newArray[numberRange];
	arrWrap *ar = new arrWrap(arraySize);

	for(int i = 0; i != arraySize; ++i)
		++newArray[initialArray[i]];

	for(int i = 1; i != numberRange; ++i)
		newArray[i] = newArray[i] + newArray[i - 1];

	int temp;
	int temp1;
	for(int i = 0; i != arraySize; ++i)
	{
		temp = initialArray[i];
		temp1 = newArray[temp]--;
		ar->arr[temp1 - 1] = initialArray[i];
	}
	return ar;
}

//void 	parse(t_node node) {
//
//}

int 	main(void) {
//	string str;
//	ifstream file("input.txt");
//	s_node *nod = malloc(sizeof(s_node));
//
//	nod->value = "";
//	nod->key = "";
//
//	// создать массив интов, когда узнаю количество строк
//	while (getline(file, str)) {
//		if (str.compare("") == 0) 	//skipping empty lines
//			continue;
//		parse_lines(str, nod);
//		cout << str << endl;
//	}

	int initialArray[4] = {4, 10, 2, 10};
	int arraySize = 4;
	int numberRange = 11;


	arrWrap *our;
	our = countingSort(initialArray, arraySize, numberRange);

	for (int i = 0; i < arraySize; i++)
		cout << our->arr[i] << endl;
//	file.close();
	return 0;
}
