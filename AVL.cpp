#include "AVL.h"
#include <iostream>

AVL* AVL::insertNode(AVL* r, int key)
{
	return nullptr;
}

//get larger int function
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
	else { return r->height; }

}

int getBalance(AVL* r) {

	if (r == nullptr) {
		return 0;
	}
	else {
		return (getHeight(r->left) - getHeight(r->right));
	}


	//code found online which shows a different approch
	/*	if (r->left && r->right) {
			return r->left->height - r->right->height;
		}
		else if (r->left && r->right == NULL) {
			return r->left->height;
		}
		else if (r->left == NULL && r->right) {
			return -r->right->height;
		}*/
	}




void inOrder(AVL * r) {

	if (r == nullptr) {
		return;
	}
	else {

		inOrder(r->left);

		std::cout << r->data << " ";

		inOrder(r->right);
	};
};


void preOrder(AVL* r) {

	//if list is empty then return
	if (r == nullptr) {
		return;
	}//else out put data at pointer then  re-exacute
	else {

		//visit data
		std::cout << r->data << " ";

		//traverse
		preOrder(r->left);
		preOrder(r->right);
	};
};

AVL* rightRotate(AVL* r) {


	//comments on leftRotate since this is just a reverse function
	AVL* newr = r->left;
	AVL* subtreechange = newr->right;

	newr->right = r;
	r->left = subtreechange;



	//updating height
	r->height = std::max(getHeight(r->left),
		getHeight(r->right)) +1;
	newr->height = std::max(getHeight(r->left),
		getHeight(r->right)) +1;

	return newr;

};

AVL* leftRotate(AVL* r) 
{


	//set new root
	AVL* newr = r->right;
	//set new subtree
	AVL* subtreechange = newr->left;


	//set left root to old root and shift
	newr->left = r;
	r->right = subtreechange;



	//updating height
	r->height = std::max(getHeight(r->left),
		getHeight(r->right)) +1;
	newr->height = std::max(getHeight(r->left),
		getHeight(r->right)) +1;

	return newr;
};



//created an insertion method to add to the tree
AVL* insertNode(AVL* r, int key) {

	//if root is pointed at null make first node
	if (r == nullptr) {
		return(new AVL(key));
	}

	//no dups
	 if (r->data == key) {
		return r;
	}


	//if data is less than first node insert to the left of the tree
	if (key < r->data) {
		r->left = insertNode(r->left, key);
		//if(r->height > 1)
	}
	//if data is more then the node insert to the tight of the tree
	if (key > r->data) {
		r->right = insertNode(r->right, key);
	}



	//update height
	r->height = 1+ max(getHeight(r->left),getHeight(r->right));
	
	

	//need to check my balance and rotate in needed
	int bf = getBalance(r);

		//std::cout << bf << "\n";
		if (bf > 1 && key < r->left->data) {
			return rightRotate(r);
		};
		if (bf < -1 && key > r->right->data) {
			return leftRotate(r);
		};
		if (bf > 1 && key > r->left->data) {
			r->left = leftRotate(r->left);
			return rightRotate(r);
		};
		if (bf < -1 && key < r->left->data) {
			r->right = rightRotate(r->right);
			return leftRotate(r);
		};

	return r;
}


//returns smallest value
AVL* minValue(AVL* r)
{
	AVL* temp = r;

	while (temp->left != NULL) {
		temp = temp->left;
	}

	return temp;
}

//returns largest value
AVL* maxValue(AVL* r)
{
	AVL* temp = r;

	while (temp->right != NULL) {
		temp = temp->right;
	}

	//displays largest value in tree
	//std::cout <<temp->data << "\n";

	return temp;

}



AVL* deleteNode(AVL* r, int key){

	//null tree
	if (r == NULL) {
		return r;
	}
	//num is lesser than r
	else if (key < r->data) {
		r->left = deleteNode(r->left, key);
	}
	//num is greater than r
	else if (key > r->data) {
		r->right = deleteNode(r->right, key);
	}


	else
	{
		// node with only one child or no child 
		if ((r->left == NULL) || (r->right == NULL))
		{
			AVL* temp = r->left ?
				r->left :
				r->right;
 
			//no children
			if (temp == NULL)
			{
				temp = r;
				r = NULL;
			}

			else {
				*r = *temp;
			}

			//free the temp pointer
			free(temp);
		}
		else
		{
			//grab smallest value
			AVL* temp = minValue(r->right);

			//delete data
			r->data = temp->data;
			r->right = deleteNode(r->right, temp->data);
		}
	}

	// if the tree had only one node return
	if (r == NULL) {
		return r;
	}

	//update height
	r->height = 1 + max(getHeight(r->left),
		getHeight(r->right));

	//get balance factor
	int bf = getBalance(r);

	//code I found online which showed another approch
	//if (bf > 1 && getBalance(r->left) >= 0)
	//	return rightRotate(r);
	//
	//// Left Right Case 
	//if (bf > 1 &&
	//	getBalance(r->left) < 0)
	//{
	//	r->left = leftRotate(r->left);
	//	return rightRotate(r);
	//}
	//
	//// Right Right Case 
	//if (bf < -1 &&
	//	getBalance(r->right) <= 0)
	//	return leftRotate(r);
	//
	//// Right Left Case 
	//if (bf < -1 &&
	//	getBalance(r->right) > 0)
	//{
	//	r->right = rightRotate(r->right);
	//	return leftRotate(r);
	//}



	//rebalance
	if (bf > 1 && key < r->left->data) {
		return rightRotate(r);
	};
	if (bf < -1 && key > r->right->data) {
		return leftRotate(r);
	};
	if (bf > 1 && key > r->left->data) {
		r->left = leftRotate(r->left);
		return rightRotate(r);
	};
	if (bf < -1 && key < r->left->data) {
		r->right = rightRotate(r->right);
		return leftRotate(r);
	};

	return r;
}


//main method for testing
int main() {
	//created tree object
	AVL* t = new AVL(10);

	//fill tree
	t = insertNode(t, 20);
	t = insertNode(t, 30);
	t = insertNode(t, 40);
	t = insertNode(t, 51);
	t = insertNode(t, 25);
	t = insertNode(t, 26);
	t = insertNode(t, 33);
	t = insertNode(t, 44);
	t = insertNode(t, 49);
	t = insertNode(t, 5);
	
	t = deleteNode(t, 50);

	//test tree
	preOrder(t);
	std::cout << "\n";
	inOrder(t);
	std::cout << "\n";


	//That was scary didnt seperate the two cout statements below and thought getBalance was showing 10!!!
	std::cout<<getHeight(t);
	std::cout << "\n";
	std::cout << getBalance(t);
	std::cout << "\n";

	std::cout<<maxValue(t)<< "\n";


}
