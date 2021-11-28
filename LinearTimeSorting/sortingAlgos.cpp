#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string key_type;

struct	s_node {
	unsigned short	intkey;
	string	value;
	s_node	*next;
};

s_node	*ft_lstnew(unsigned short key, string value) {
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

string find_in_root_value_under_n(s_node *root, int key)
{
	while (root != nullptr) {
		if (root->intkey == key) {
			root->intkey = -1;
			return root->value;
		}
		root = root->next;
	}
	return "nullptr";
}

void countSort(s_node *root) {
	int size = find_size(root);
	int output[size + 1];
	int max = find_range(root);
	int count[max + 1];

	for (int i = 0; i <= max; i++)
		count[i] = 0;
	for (int i = 0; i < size; i++)
		count[node_at(root, i)->intkey]++;
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];
	for (int i = size - 1; i >= 0; i--) {
		output[count[node_at(root, i)->intkey]] = node_at(root, i)->intkey;
		count[node_at(root, i)->intkey] -= 1;
	}

	s_node *result = nullptr;
	string str;
	for (int i = 1; i <= size; ++i) {
		str = find_in_root_value_under_n(root, output[i]);
		s_node *pnew = ft_lstnew(output[i], str);
		ft_lstadd_back(&result, pnew);
	}


	for (int i = 0; i < size; ++i)
		cout << node_at(result, i)->intkey << node_at(result, i)->value << endl;

}

int 	main(void) {
	string	str;
	string	key = "";
	string	value = "";
	ifstream	file("input.txt");
	s_node	*root = nullptr;

	// reading and parsing in linked list
	while (getline(file, str)) {
		if (str.compare("") == 0) 	//skipping empty lines
			continue;
		// parsing from input line to node's elements
		stringstream ss(str);
		ss >> key >> value;
		unsigned short my_key = stoi(key);

		// adding whatever key type to list
//		if (key.length() == 6 || (my_key >= 0 && my_key <= 65535))
		ft_lstadd_back(&root, ft_lstnew(my_key, value));
	}


//	countSort(root);



	file.close();
	return 0;
}
