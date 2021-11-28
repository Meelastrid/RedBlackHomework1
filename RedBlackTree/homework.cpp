#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct TempNode {
	string sign;
	string key;
	unsigned long long value;
};

struct Node {
	string data;
	unsigned long long value;
	Node *parent;
	Node *left;
	Node *right;
	int color;
};

typedef Node *NodePtr;

class RedBlackTree {
private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = "";
		node->value = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	NodePtr searchTreeHelper(NodePtr node, string key) {
		if (node == TNULL) {
			cout << "NoSuchWord" << endl;
			return node;
		} else if (key.compare(node->data) == 0) {
			cout << "OK: " << node->value << endl;
			return node;
		}

		if (key.compare(node->data) < 0) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	NodePtr checkBeforeInsert(NodePtr node, string key) {
		if (node == TNULL) {
			return node;
		} else if (key.compare(node->data) == 0) {
			cout << "Exist" << endl;
			return node;
		}

		if (key.compare(node->data) < 0) {
			return checkBeforeInsert(node->left, key);
		}
		return checkBeforeInsert(node->right, key);
	}

	void deleteFix(NodePtr x) {
		NodePtr s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->right->color == 0) {
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				s = x->parent->left;
				if (s->color == 1) {
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == 0) {
					s->color = 1;
					x = x->parent;
				} else {
					if (s->left->color == 0) {
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

	void rbTransplant(NodePtr u, NodePtr v) {
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void finalNodeDeletion(NodePtr node, string key) {
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL) {
			if (node->data.compare(key) == 0) {
				z = node;
			}

			if (node->data.compare(key) <= 0) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			cout << "NoSuchWord" << endl;
			return;
		}
		cout << "OK" << endl;
		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		} else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		} else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) {
			deleteFix(x);
		}
	}

	void insertFix(NodePtr k) {
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left;
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

public:
	RedBlackTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	NodePtr searchTree(string k) {
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(string key, unsigned long long value) {
		if (checkBeforeInsert(this->root, key) != TNULL) {
			return;
		}
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->value = value;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data.compare(x->data) < 0) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data.compare(y->data) < 0) {
			y->left = node;
		} else {
			y->right = node;
		}
		cout << "OK" << endl;
		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		insertFix(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	void deleteNode(string data) {
		finalNodeDeletion(this->root, data);
	}
};

void handleError(string errorMsg) {
	cerr << errorMsg << endl;
	exit(1);
}

int total_words(string str){
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

void parseString(string &str, string &sign, TempNode &tempNode, int numberOfWords) {
	string tempValue;

	for (int i = 0; i < str.length(); ++i) {
		str[i] = std::tolower(str[i]);
	}

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

	char *endp;
	tempNode.value = std::strtoull(tempValue.c_str(), &endp, 10);
}

int main() {
	int numberOfWords;
    string sign;
    string str;
    std::ifstream file("input.txt");
	struct TempNode tempNode;
	RedBlackTree bst;

	while (getline(file, str)) {

		numberOfWords = total_words(str);
		if (numberOfWords > 3 || numberOfWords == 0) {
			handleError("Wrong number of arguments");
		}
		parseString(str, sign, tempNode, numberOfWords);
		keyValidation(tempNode.key);

		if (numberOfWords == 3 && sign.compare("+") == 0) {
			bst.insert(tempNode.key, tempNode.value);
		}
        else if (numberOfWords == 2 && sign.compare("-") == 0) {
			bst.deleteNode(tempNode.key);
		}
        else if (numberOfWords == 1) {
			bst.searchTree(tempNode.key);
		}
	}
	file.close();
    return 0;
}