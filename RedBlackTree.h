#include <stdio.h>
#define RED 1
#define BLACK 0
#define MAXROW 100

//rbtree의 노드
typedef struct _node{
	Node * parent; //부모 노드
	Node * left; //왼쪽 자식 노드
	Node * right; //오른쪽 자식 노드
	char color; //레드면 1, 레드가 아니면 0 

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

int Getkey(Node * node);

Node * GrandParent(Node * node);

Node * Uncle(Node * node);

Node * SetNode(int col, int right);

void LRotate(Node * node);

void RRotate(Node * node);

void RBDelete(RBtree * rbtree, Node * delNode);

int RBInsert(RBtree * rbtree, Node * newNode);
void InsertCase1(RBtree * rbtree, Node * newNode);
void InsertCase2(RBtree * rbtree, Node * newNode);
void InsertCase3(RBtree * rbtree, Node * newNode);
void InsertCase4(RBtree * rbtree, Node * newNode);

void RBPrint(RBtree * rbtree);

void RBSearch(RBtree * rbtree, Node * searchNode);

