#include<iostream>
class Node {
public:
	int key;
	int height;
	Node* left;
	Node* right;
};
int max(int x,int y) {
	return (x > y) ? x : y;
}
int height(Node* node) {
	if (node == NULL)return 0;
	return 1 + max(height(node->left), height(node->right));
}
int getbalance(Node* root) {
	return root->left->height - root->right->height;
}
Node* left_rotation(Node* node) {
	Node* new_root = node->left;
	new_root->right = node;
	new_root->height = 1 + max(height(new_root->left), height(new_root->right));
	return new_root;
}
Node* right_rotation(Node* node) {
	Node* new_root = node->right;
	new_root->left = node;
	new_root->height = 1 + max(height(new_root->left), height(new_root->right));

	return new_root;
}
Node* insert(Node* root,int key) {
	if (root == NULL) {
		Node* node = new Node;
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 0;
		return node;
	}
	if (root->key > key) {
		root->left = insert(root->left, key);
	}
	else if(root->key < key){
		root->right = insert(root->right, key);
	}
	root->height = height(root);

	int balance = getbalance(root);

	if (balance < -1 && root->right->key < key) {//RR
		return right_rotation(root);
	}
	else if (balance > 1 && root->left->key > key) {//LL
		return left_rotation(root);
	}
	else if (balance < -1 && root->right->key < key) {//RL
		root->right = left_rotation(root->right);
		return right_rotation(root);
	}
	else if (balance > 1 && root->left->key > key) {//LR
		root->left = right_rotation(root->left);
		return left_rotation(root);
	}
}
void print(Node* node) {
	if (node != NULL) {
		print(node->left);
		printf("%d ", node->key);
		print(node->right);
	}
}
int main() {
	int n,key;
	scanf_s("%d ", &n);
	Node* root = NULL;
	for (int i = 0; i < n; i++) {
		scanf_s("%d ", &key);
		root = insert(root,key);
	}
	print(root);
}