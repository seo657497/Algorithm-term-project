#include <stdio.h>

//rbtree의 노드
typedef struct _node{
	Node * parent; //부모 노드
	Node * left; //왼쪽 자식 노드
	Node * right; //오른쪽 자식 노드
	char redFlag; //레드면 1, 레드가 아니면 0 

	//데이터 필드
	int col;
	int row;
}Node;

//rbtree
typedef struct _rbtree{
	int num; //노드의 갯수

	Node * root;
}RBtree;


void RBinit(RBtree * rbtree);

void Getkey(Node * node);

Node * SetNode(int col, int right);

void RBDelete(RBtree * rbtree, Node delNode);

void RBInsert(RBtree * rbtree, Node newNode);

void RBPrint(RBtree * rbtree);

void RBSearch(RBtree * rbtree, Node searchNode);

