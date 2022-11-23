#include "AVL.h"
#include <iostream>
#include <chrono> //testing and timing
#include <stdlib.h>		// for RNG
#include <time.h>	//for seeding



//get larger int function
int AVL::max(int a, int b) {

	if (a < b) {
		return b;
	}
	else {
		return a;
	}

}

int AVL::getHeight(AVL* r) {
	if (r == nullptr) {
		return 0;
	}
	else { return r->height; }

}

int AVL::getBalance(AVL* r) {

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




void AVL::inOrder(AVL * r) {

	if (r == nullptr) {
		return;
	}
	else {

		inOrder(r->left);

		std::cout << r->data << " ";

		inOrder(r->right);
	};
};


void AVL::preOrder(AVL* r) {

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

AVL* AVL::rightRotate(AVL* r) {


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

AVL* AVL::leftRotate(AVL* r)
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
AVL* AVL::insertNode(AVL* r, int key) {

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

	if (bf > 1 && getBalance(r->left) >= 0) {
		return rightRotate(r);
	}
	
	if (bf > 1 && getBalance(r->left) < 0)
	{
		r->left = leftRotate(r->left);
		return rightRotate(r);
	}
	
	if (bf < -1 && getBalance(r->right) <= 0) 
	{
		return leftRotate(r);
	}
	 
	if (bf < -1 && getBalance(r->right) > 0)
	{
		r->right = rightRotate(r->right);
		return leftRotate(r);
	}

	return r;
}


//returns largest value used for example in report
//AVL* AVL::maxValue(AVL* r)
//{
//	AVL* temp = r;
//
//	while (temp->right != NULL) {
//		temp = temp->right;
//	}
//
//	//displays largest value in tree
//	//std::cout <<temp->data << "\n";
//
//	return temp;
//
//}



AVL* AVL::deleteNode(AVL* r, int key){

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

			AVL* temp = r->right;

			while (temp->left != NULL) {
				temp = temp->left;
			}

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

	//rebalance
	if (bf > 1 && getBalance(r->left) >= 0) {
	return rightRotate(r);
	}

	if (bf > 1 && getBalance(r->left) < 0)
	{
		r->left = leftRotate(r->left);
		return rightRotate(r);
	}

	if (bf < -1 && getBalance(r->right) <= 0)
	{
		return leftRotate(r);
	}

	if (bf < -1 && getBalance(r->right) > 0)
	{
		r->right = rightRotate(r->right);
		return leftRotate(r);
	}


	return r;
}

//main method for testing
int main() {

	////created tree object
	//AVL* t = new AVL(1);
	//AVL* t2 = new AVL(1);
	//AVL* t3 = new AVL(1);
	//AVL* t4 = new AVL(1);
	//AVL* t5 = new AVL(1);
	//

	////fill tree
	//for (int j = 0; j < 5; j++) {

	//	if (j == 0) {
	//		auto begining = std::chrono::high_resolution_clock::now();
	//		for (int i = 1; i < 101; i++) {
	//			t = t -> insertNode(t, i);
	//		}
	//		auto ending = std::chrono::high_resolution_clock::now();
	//		long Amount_time_one = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();
	//		std::cout << Amount_time_one << "\n";
	//	}
	//	if (j == 1) {
	//		auto begining = std::chrono::high_resolution_clock::now();
	//		for (int i = 1; i < 1001; i++) {
	//			t2 = t2 -> insertNode(t2, i);
	//		}
	//		auto ending = std::chrono::high_resolution_clock::now();
	//		long Amount_time_two = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();
	//		std::cout << Amount_time_two << "\n";
	//	}
	//	if (j == 2) {
	//		auto begining = std::chrono::high_resolution_clock::now();
	//		for (int i = 1; i < 10001; i++) {
	//			t3 = t3 -> insertNode(t3, i);
	//		}
	//		auto ending = std::chrono::high_resolution_clock::now();
	//		long Amount_time_three = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();
	//		std::cout << Amount_time_three << "\n";
	//	}
	//	if (j == 3) {
	//		auto begining = std::chrono::high_resolution_clock::now();
	//		for (int i = 1; i < 100001; i++) {
	//			t4 = t4 -> insertNode(t4, i);
	//		}
	//		auto ending = std::chrono::high_resolution_clock::now();
	//		long Amount_time_four = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();
	//		std::cout << Amount_time_four << "\n";
	//	}
	//	if (j == 4) {
	//		auto begining = std::chrono::high_resolution_clock::now();
	//		for (int i = 1; i < 1000001; i++) {
	//			t5 = t5 -> insertNode(t5, i);
	//		}
	//		auto ending = std::chrono::high_resolution_clock::now();
	//		long Amount_time_five = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();
	//		std::cout << Amount_time_five << "\n";
	//	}
	//}
	

	////create random number to delete from tree
	//srand((unsigned)time(NULL));
	//int random = (rand()% 100000);
	////std::cout << random << std::endl;

	////time deleting a int from the tree
	///*auto beginingTwo = std::chrono::high_resolution_clock::now();
	//t = deleteNode(t, random);
	//auto endingTwo = std::chrono::high_resolution_clock::now();
	//long Amount_timeTwo = std::chrono::duration_cast<std::chrono::nanoseconds>(ending - begining).count();

	//std::cout << Amount_timeTwo;*/

	////inOrder(t);
	////std::cout << "\n";

}