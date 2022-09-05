#pragma once
#include <iostream>
#include <queue>
using namespace std;

namespace dataStruct {
	//BinarySearchTree，二分查找树
	//每个节点都大于左子节点，小于右子节点
	//不必要是一棵完全二叉树
	//已经优化为AVL平衡二叉树
	template <typename Key, typename Value>
	class AVL {
	public:
		struct Node {
			Key key;
			Value value;
			Node* left;
			Node* right;
			int n;
			int height;

			Node(Key key, Value value) {
				this->key = key;
				this->value = value;
				n = 1;
				height = 1;
				this->left = nullptr;
				this->right = nullptr;
			}

			Node(const Node* node) {
				this->key = node->key;
				this->value = node->value;
				this->left = node->left;
				this->right = node->right;
				this->n = node->n;
				this->height = node->height;
			}

			~Node() {
				/*
				if (left != nullptr)
					delete left;
				if (right != nullptr)
					delete right;
				*/
			}
		};

		Node* root;
		int __iSize;

		int size(Node* node) {
			if (node == nullptr) {
				return 0;
			}
			return node->n;
		}

		int height(Node* node) {
			if (node == nullptr) {
				return 0;
			}
			return node->height;
		}

		int bf(Node* node) {
			return abs(height(node->left) - height(node->right));
		}

		Node* leftRotation(Node* node) {
			Node* curRight = new Node(node->right);
			__iSize++;
			delete node->right;
			__iSize--;
			node->right = curRight->left;
			curRight->left = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			curRight->height = max(height(curRight->left), height(curRight->right)) + 1;
			return curRight;
		}

		Node* rightRotation(Node* node) {
			Node* curLeft = new Node(node->left);
			__iSize++;
			delete node->left;
			__iSize--;
			node->left = curLeft->right;
			curLeft->right = node;
			node->height = max(height(node->left), height(node->right)) + 1;
			curLeft->height = max(height(curLeft->left), height(curLeft->right)) + 1;
			return curLeft;
		}

		Node* leftRightRotation(Node* node) {
			node->left = leftRotation(node->left);
			return rightRotation(node);
		}

		Node* rightLeftRotation(Node* node) {
			node->right = rightRotation(node->right);
			return leftRotation(node);
		}

		Node* insert(Node* node, Key key, Value value) {
			if (node == nullptr) {
				__iSize++;
				return new Node(key, value);
			}

			if (node->key == key) {
				node->value = value;
			}
			else if (node->key > key) {
				node->left = insert(node->left, key, value);
				if (bf(node) > 1) {
					if (node->left->key > key) {
						node = rightRotation(node);
					}
					if (node->left->key < key) {
						node = leftRightRotation(node);
					}
				}
			}
			else {
				node->right = insert(node->right, key, value);
				if (bf(node) > 1) {
					if (node->right->key < key) {
						node = leftRotation(node);
					}
					if (node->right->key > key) {
						node = rightLeftRotation(node);
					}
				}
			}

			node->n = size(node->left) + size(node->right) + 1;
			node->height = max(height(node->left), height(node->right)) + 1;
			return node;
		}

		bool isContain(Node* node, Key key) {
			if (node == nullptr)
				return false;

			if (node->key == key)
				return true;
			else if (node->key > key)
				return isContain(node->left, key);
			else
				return isContain(node->right, key);
		}

		Value search(Node* node, Key key) {
			if (node == nullptr) {
				return NULL;
			}

			if (node->key == key)
				return node->value;
			else if (node->key > key)
				return search(node->left, key);
			else
				return search(node->right, key);
		}

		void preOrder(Node* node) {
			if (node != nullptr) {
				cout << node->key << endl;
				preOrder(node->left);
				preOrder(node->right);
			}
		}

		void inOrder(Node* node) {
			if (node != nullptr) {
				inOrder(node->left);
				cout << node->key << endl;
				inOrder(node->right);
			}
		}

		void postOrder(Node* node) {
			if (node != nullptr) {
				postOrder(node->left);
				postOrder(node->right);
				cout << node->key << endl;
			}
		}

		void destroy(Node* node) {
			if (node != nullptr) {
				destroy(node->left);
				destroy(node->right);
				delete node;
			}
		}

		void levelOrder(Node* node) {
			queue<Node*> q;
			q.push(root);
			while (!q.empty()) {
				Node* n = q.front();
				q.pop();
				cout << n->key << endl;
				if (n->left != nullptr)
					q.push(n->left);
				if (n->right != nullptr)
					q.push(n->right);
			}
		}

		Node* minimum(Node* node) {
			if (node->left == nullptr)
				return node;
			return minimum(node->left);
		}

		//迭代方式
		Node* minimumI(Node* node) {
			while (node->left != nullptr) {
				node = node->left;
			}
			return node;
		}

		Node* maximum(Node* node) {
			if (node->right == nullptr)
				return node;
			return maximum(node->right);
		}

		//迭代方式
		Node* maximumI(Node* node) {
			while (node->right != nullptr) {
				node = node->right;
			}
			return node;
		}

		Node* removeMin(Node* node) {
			if (node->left == nullptr) {
				Node* ri = node->right;
				delete node;
				__iSize--;
				return ri;
			}

			node->left = removeMin(node->left);
			if (bf(node) > 1) {
				node = rightRotation(node);
			}
			node->n = size(node->left) + size(node->right) + 1;
			node->height = max(height(node->left), height(node->right)) + 1;
			return node;
		}

		//迭代方式（不支持AVL）
		/*
		void removeMinI(Node* node) {
			while (node->left->left != nullptr) {
				node->n--;
				node = node->left;
			}
			Node* ri = node->left->right;
			delete node->left;
			node->n--;
			__iSize--;
			node->left = ri;
		}
		*/

		Node* removeMax(Node* node) {
			if (node->right == nullptr) {
				Node* le = node->left;
				delete node;
				__iSize--;
				return le;
			}

			node->right = removeMax(node->right);
			if (bf(node) > 1) {
				node = leftRotation(node);
			}
			node->n = size(node->left) + size(node->right) + 1;
			node->height = max(height(node->left), height(node->right)) + 1;
			return node;
		}

		//迭代方式（不支持AVL）
		/*
		void removeMaxI(Node* node) {
			while (node->right->right != nullptr) {
				node->n--;
				node = node->right;
			}
			Node* le = node->right->left;
			delete node->right;
			node->n--;
			__iSize--;
			node->right = le;
		}
		*/

		Node* remove(Node* node, Key key) {
			if (node == nullptr) {
				return nullptr;
			}

			if (key < node->key) {
				node->left = remove(node->left, key);
				if (bf(node) > 1) {
					if (key < node->left->key) {
						node = leftRotation(node);
					}
					if (key > node->left->key) {
						node = rightLeftRotation(node);
					}
				}
			}
			else if (key > node->key) {
				node->right = remove(node->right, key);
				if (bf(node) > 1) {
					if (key > node->right->key) {
						node = rightRotation(node);
					}
					if (key < node->right->key) {
						node = leftRightRotation(node);
					}
				}
			}
			else {
				Node* successor = new Node(minimum(node->right));
				__iSize++;

				successor->right = removeMin(node->right);
				successor->left = node->left;

				delete node;
				__iSize--;
				successor->n = size(successor->left) + size(successor->right) + 1;
				return successor;
			}
			node->n = size(node->left) + size(node->right) + 1;
			node->height = max(height(node->left), height(node->right)) + 1;
			return node;
		}

		//使用前驱节点的Hubbard Deletion
		Node* removeP(Node* node, Key key) {
			if (node == nullptr) {
				return nullptr;
			}

			if (key < node->key) {
				node->left = remove(node->left, key);

			}
			else if (key > node->key) {
				node->right = remove(node->right, key);

			}
			else {
				Node* predeccesor = new Node(maximum(node->left));
				__iSize++;

				predeccesor->left = removeMax(node->left);
				predeccesor->right = node->right;

				delete node;
				__iSize--;

				predeccessor = size(predecessor->left) + size(predeccessor->right) + 1;
				return predeccesor;
			}
			node->n = size(n->left) + size(n->right) + 1;
			return node;
		}

		Node* floor(Node* node, Key key) {
			if (node == nullptr) {
				return node;
			}

			if (key < node->key) {
				return floor(node->left, key);
			}
			else if (key == node->key) {
				return node;
			}
			else {
				Node* temp = floor(node->right, key);
				return temp != nullptr ? temp : node;
			}

		}

		Node* ceil(Node* node, Key key) {
			if (node == nullptr) {
				return nullptr;
			}

			if (key > node->key) {
				return floor(node->right, key);
			}
			else if (key == node->key) {
				return node;
			}
			else {
				Node* temp = floor(node->left, key);
				return temp != nullptr ? temp : node;
			}
		}

		int rank(Node* node, Key key) {
			assert(node != nullptr);

			if (key < node->key) {
				return rank(node->left, key);
			}
			else if (key > node->key) {
				return rank(node->right, key) + size(node->left) + 1;
			}
			else {
				return size(node->left) + 1;
			}
		}

		Node* select(Node* node, int rank) {
			assert(node != nullptr);

			if (rank <= size(node->left)) {
				return select(node->left, rank);
			}
			else {
				if (rank == size(node->left) + 1) {
					return node;
				}
				else {
					return select(node->right, rank - size(node->left) - 1);
				}
			}
		}

		AVL() {
			root = nullptr;
			__iSize = 0;
		}

		~AVL() {
			//delete root;
			destroy(root);
		}

		int getSize() {
			return __iSize;
		}

		bool isEmpty() {
			return __iSize == 0;
		}

		AVL& insert(Key key, Value value) {
			root = insert(root, key, value);
			return *this;
		}

		bool isContain(Key key) {
			return isContain(root, key);
		}

		Value operator[](Key key) {
			assert(isContain(key));
			return search(root, key);
		}

		void preOrder() {
			preOrder(root);
		}

		void inOrder() {
			inOrder(root);
		}

		void postOrder() {
			postOrder(root);
		}

		void levelOrder() {
			levelOrder(root);
		}

		Key minimum() {
			assert(__iSize != 0);
			Node* minNode = minimum(root);
			return minNode->key;
		}

		Key maximum() {
			assert(__iSize != 0);
			Node* maxNode = maximum(root);
			return maxNode->key;
		}

		void removeMin() {
			if (root != nullptr) {
				root = removeMin(root);
			}
		}

		void removeMax() {
			if (root != nullptr) {
				root = removeMax(root);
			}
		}

		void remove(Key key) {
			root = remove(root, key);
		}

		Key floor(Key key) {
			if (isEmpty() || minimum() > key) {
				return NULL;
			}
			return floor(root, key)->key;
		}

		Key ceil(Key key) {
			if (isEmpty() || maximum() < key) {
				return NULL;
			}
			return ceil(root, key)->key;
		}

		int rank(Key key) {
			assert(isContain(key));
			return rank(root, key);
		}

		Key select(int rank) {
			assert(rank <= __iSize);
			return select(root, rank)->key;
		}
	};
}

using namespace dataStruct;

template<typename Key>
class _Set {
private:
	AVL<Key, Key> data;
public:
	void init(Key val[], int n) {
		for (int i = 0; i < n; i++) {
			data.insert(val[i], val[i]);
		}
	}
	void display() {
		data.inOrder();
	}
};