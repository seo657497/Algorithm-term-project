#include "RedBlackTree.h"


void RBinit(RBtree * rbtree){
	rbtree->num = 0;
	rbtree->root = NULL;
}

void Getkey(Node * node){
	return (node->col * 100) + node->row; //key´Â ¿­*100 + ¿­
}

Node * SetNode(int col, int row){
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->col = col;
	newNode->row = row;

	return newNode;
}

void RBDelete(RBtree * rbtree, Node delNode){

}


void RBInsert(RBtree * rbtree, Node newNode){

}

void RBPrint(RBtree * rbtree){

}


void RBSearch(RBtree * rbtree, Node searchNode){

}
