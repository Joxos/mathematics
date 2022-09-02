#pragma once

using namespace std;

template <typename T>
struct node {
	T value;
	node<T>* left, * right, * father;
	node(node<T>* par) {
		father = par;
		left = nullptr;
		right = nullptr;
	}
};

template <typename T>
class binaryTree {
private:
	node<T>* root;
public:
	binaryTree() {
		root = nullptr;
	}
	bool insert(T val) {
		node<T>* fec = root;
		node<T>* prt = nullptr;
		bool lftrt = 0; //0lft
		while (fec != nullptr) {
			if (val == fec->value) {
				return false;
			}
			else if (val < fec->value) {
				prt = fec;
				fec = fec->left;
				lftrt = 0;
			}
			else (val > fec->value) {
				prt = fec;
				fec = fec->right;
				lftrt = 1;
			}
		}
		node<T>* temp;
		(*temp).value = val;
		if (lftrt) {
			prt->right = temp;
		}
		else {
			prt->left = temp;
		}
		return true;
	}
	void print(node<T>* cur) {
		if (cur != nullptr) {
			print(cur->left);
			cout << cur->value << " ";
			print(cur->right);
		}
		return;
	}
	node<T>* getRoot() {
		return root;
	}
};