#include "AVL.h"
#include <iostream>

AVL* AVL::insertNode(AVL* r, int key)
{
	return nullptr;
}

int max(int a, int b) {

	if (a < b) {
		return b;
	}
	else {
		return a;
	}

}

int getHeight(AVL* r) {

	if (r == nullptr) {
		return 0;
	}
	else {
		return 0;
		//return max(r->left)
		//return max(height(node.L), height(node.R))
	}
}

void inOrder(AVL* r) {

	if (r == nullptr) {
		return;
	}
	else {

		inOrder(r->left);

		std::cout << r->data << " ";

		inOrder(r->right);
	}
}


void preOrder(AVL* r) {

	if (r == nullptr) {
		return;
	}
	else {


		std::cout << r->data << " ";

		preOrder(r->left);
		preOrder(r->right);
	}
}

//created an insertion method to add to the tree
AVL* insertNode(AVL* r, int key) {

	//if root is pointed at null make first node
	if (r == nullptr) {
		return(new AVL(key));
	}
	if (r->data == key) {
		return r;
	}
	//if data is less than first node insert to the left of the tree
	if (key < r->data) {
		r->left = insertNode(r->left, key);
		//height++;
	}
	//if data is more then the node insert to the tight of the tree
	else if (key > r->data) {
		r->right = insertNode(r->right, key);
		//height++;
	}
	return r;

}


//random main method
int main() {
	AVL* t = new AVL(5);

	insertNode(t, 10);
	insertNode(t, 6);
	insertNode(t, 2);
	insertNode(t, 2);
	insertNode(t, 8);
	insertNode(t, 8);

	//preOrder(t);

	inOrder(t);



}

