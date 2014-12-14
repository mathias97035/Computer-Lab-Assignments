/* 
* File:		tree.c
* Creator: 	Matt Belesiu
* Discription: Tree implementation. Will contain functions to create and
* destroy trees, get data of nodes, get the parents, left or right child
* of any given node, and the ability to assign a left or right node to 
* any existing node. Impelemntation has been tested with treesort.c and 
* huffman.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
/*
 * Desgin of each node in the tree. each node contains an int Data, and 
 * three pointers, a left, right and parent pointer.
 */
struct tree{
	
	int data;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
};

/*
 * createTree will allocate memory for node in the tree to be created.
 * Has the options to assign a left or right node/subtree.
 * O(1);
 */
struct tree  *createTree(int data, struct tree *left, struct tree *right){

	struct tree *tnew = malloc(sizeof(struct tree));
	assert(tnew != NULL);

	tnew->parent = NULL;
	tnew->data = data;
		
	
	tnew->left = left;
	tnew->right = right;
	//checks to see if left node was passed
	if(left != NULL){
		//checks to see if left had a parent
		//if so, then need clear that parent's pointer
		if(left->parent != NULL){
			if(left->parent->right == left)
				left->parent->right = NULL;
			else
				left->parent->left = NULL;
		}
		left->parent = tnew;
	}
	//chekcs to see if right node was passed
	if(right != NULL){
		//chekcs to see if right has a parent
		//if so// then need to clear that parent's pointer
		if(right->parent != NULL){
			if(right->parent->right == right)
				right->parent->right = NULL;
			else
				right->parent->left = NULL;
		}
		right->parent = tnew;
	}
	
	return tnew;
}
/*
 * destroyTree traverses a given tree and dealocates memory in postorder
 * freeing the childern first, then thier parents. Function is recursive
 * O(n)
 */
void destroyTree(struct tree *root){

	if(root != NULL){
		destroyTree(root->left);
		destroyTree(root->right);
		free(root);
	}
}
/*
 * getData returns the data of the given node of the tree
 * O(1)
 */
int getData(struct tree *root){
	
	return root->data;
}
/*
 * getLeft returns the given node's left child's pointer 
 * O(1)
 */
struct tree *getLeft(struct tree *root){
	
	return root->left;
}
/*
 * getRight returns the given node's right child's pointer
 * O(1)
 */
struct tree *getRight(struct tree *root){
	
	return root->right;
}
/*
 * getParent returns the given node's parent's pointer
 * O(1)
 */
struct tree *getParent(struct tree *root){
	
	return root->parent;
}
/*
 * setLeft reassigns the left pointer of a given node with a given new
 * "left" child/subtree
 * O(1)
 */
void setLeft(struct tree *root, struct tree *left){
	//see comments about left assignment in createTree
	if(root->left != NULL)
		root->left->parent = NULL;	

	root->left = left;

	if(left != NULL){
		if(left->parent != NULL){
			if(left->parent->right == left)
				left->parent->right = NULL;
			else
				left->parent->left = NULL;
		}
	left->parent = root;
	}
}
/*
 * setRight reassigns the right pointer of a given node with a given new
 * "right" child/subtree
 * O(1)
 */
void setRight(struct tree *root, struct tree *right){
	//see comments about right assignment in createTree
	
	if(root->right != NULL)	
		root->right->parent = NULL;
	
	root->right = right;

	if(right != NULL){
		if(right->parent != NULL){
			if(right->parent->right == right)
				right->parent->right = NULL;
			else 
				right->parent->left = NULL;
		}
	right->parent = root;
	}
}
