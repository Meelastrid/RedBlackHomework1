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

	while (root != nullptr) {
		if (root->intkey > max)
			max = root->intkey;
		root = root->next;
	}
	return max;
}

int		find_size(s_node *root) {
	int i = 0;

	while (root != nullptr) {
		i++;
		root = root->next;
	}
	return i;
}

s_node *node_at(s_node *root, int at) {
	for (int i = 0; i < at; ++i)
		root = root->next;
	return root;
}

void countSort(s_node *root) {
	int size = find_size(root);
	cout << "Size: " << size << endl;
	int output[size + 1];
	int max = find_range(root);
	cout << "Range: " << max << endl;
	int count[max + 1];     //create count array (max+1 number of elements)

	for (int i = 0; i <= max; i++)
		count[i] = 0;     //initialize count array to all zero
//
	for (int i = 0; i < size; i++)
		count[node_at(root, i)->intkey]++;     //increase number count in count array.
//
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];     //find cumulative frequency
//
	for (int i = size - 1; i >= 0; i--) {
		output[count[node_at(root, i)->intkey]] = node_at(root, i)->intkey;
		count[node_at(root, i)->intkey] -= 1; //decrease count for same numbers
	}
//
	for (int i = 1; i <= size; ++i)
		cout << output[i] << endl;
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

		// defining type of the key (post, short etc...) meaning that every line after first will be the same key type
		if (key.length() == 6)
			key_type = "post";
		else if (my_key >= 0 && my_key <= 65535)
			key_type = "short";

		// adding whatever key type to list
		if (key.length() == 6 || (my_key >= 0 && my_key <= 65535))
			ft_lstadd_back(&root, ft_lstnew(my_key, value));
	}

	countSort(root);

	file.close();
	return 0;
}
