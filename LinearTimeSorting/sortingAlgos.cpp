#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string key_type;

struct	s_node {
	unsigned short	intkey;
	string	value;
	s_node	*next;
};

s_node	*ft_lstnew(int key, string value) {
	s_node	*new_elem;

	new_elem = (s_node*)malloc(sizeof(s_node));
	if (new_elem == nullptr)
		return (nullptr);
	new_elem->next = nullptr;
	new_elem->intkey = key;
	new_elem->value = value;
	return new_elem;
}

void	ft_lstadd_back(s_node** myRoot, s_node* p_new) {
	s_node *temp;
	temp = *myRoot;

	if (temp == nullptr) {
		*myRoot = p_new;
		return;
	}
	while (temp->next != nullptr)
		temp = temp->next;
	temp->next = p_new;
}

int 	find_range(s_node *root) {
	int max = root->intkey;
	int min = root->intkey;

	while (root != nullptr) {
		if (root->intkey > max)
			max = root->intkey;
		if (root->intkey < min)
			min = root->intkey;
		root = root->next;
	}
	return max - min;
}

int		find_size(s_node *root) {
	int i = 0;

	while (root != nullptr) {
		i++;
		root = root->next;
	}
	return i;
}


void	countingSort(s_node *root) {
	int numberRange = find_range(root);
	int arraySize = find_size(root);

	cout << "Range: " << numberRange << endl;
	cout << "Size: " << arraySize << endl;

//	int newArray[numberRange];
//
//	for(int i = 0; i != arraySize; ++i)
//		++newArray[initialArray[i]];
//
//	for(int i = 1; i != numberRange; ++i)
//		newArray[i] = newArray[i] + newArray[i - 1];
//
//	int temp;
//	int temp1;
//	for(int i = 0; i != arraySize; ++i)
//	{
//		temp = initialArray[i];
//		temp1 = newArray[temp]--;
//		ar->arr[temp1 - 1] = initialArray[i];
//	}
}


int 	main(void) {
	string	str;
	string	key;
	string	value;
	ifstream	file("input.txt");
	s_node	*root = nullptr;

	// reading and parsing in linked list
	while (getline(file, str)) {
		if (str.compare("") == 0) 	//skipping empty lines
			continue;
		// parsing from input line to node's elements
		stringstream ss(str);
		ss >> key >> value;
		int my_key = stoi(key);

		// defining type of the key (post, short ...) meaning that every line after first will be the same key type
		if (key.length() == 6)
			key_type = "post";
		else if (my_key >= 0 && my_key <= 65535)
			key_type = "short";

		// adding whatever key type to list
		if (key.length() == 6 || (my_key >= 0 && my_key <= 65535))
			ft_lstadd_back(&root, ft_lstnew(my_key, value));
	}

	//sorting list in ascending order (from 0 to n)
	countingSort(root);

	// printing all elements
	while (root != nullptr) {
		cout << root->intkey << " : " << root->value << endl;
		root = root->next;
	}

	file.close();
	return 0;
}
