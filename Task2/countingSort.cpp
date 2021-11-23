#include <iostream>

using namespace std;

void countingSort(int initialArray[], int arraySize, int numberRange) 
{

    int newArray[numberRange] = {};

    for(int i = 0; i != arraySize; ++i)
    {
        ++newArray[initialArray[i]];
    }

    for(int i = 1; i != numberRange; ++i)
    {
        newArray[i] = newArray[i] + newArray[i - 1];
    }

    int temp;
    int temp1;
    int result[arraySize] = {};
    for(int i = 0; i != arraySize; ++i)
    {
        temp = initialArray[i];
        temp1 = newArray[temp]--;
        result[temp1] = initialArray[i];
    }
    for(int i : newArray)
    cout << i << endl;
}

int     main() 
{

    int initialArray[4] = {4, 10, 2, 10};
    int arraySize = 4;
    int numberRange = 6;
    countingSort(initialArray, arraySize, numberRange);    
}