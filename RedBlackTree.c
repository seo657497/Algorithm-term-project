#include "RedBlackTree.h"

//tree를 초기화
void RBinit(RBtree * rbtree){
	rbtree->num = 0;
	rbtree->root = NULL;
}

//node의 key값 반환
int Getkey(Node * node){
	return (node->col * MAXROW) + node->row; //key는 열*100 + 열
}

//주어진 노드의 조부모 반환
Node * GrandParent(Node * node){
	if (node != NULL && node->parent != NULL)
		return node->parent->parent;
	else
		return NULL;
}

//주어진 노드의 삼촌 반환
Node * Uncle(Node * node){
	Node * g = GrandParent(node);

	if (g == NULL)
		return NULL;
	else if (node->parent = g->left)
		return g->right;
	else
		return g->left;

}

//주어진 인자로 노드 생성
Node * SetNode(int col, int row){
	Node * newNode = (Node *)malloc(sizeof(Node));

	newNode->col = col;
	newNode->row = row;
	newNode->color = RED;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

//주어진 노드를 기준으로 왼쪽회전
void LRotate(Node * node){
	Node * r = node->right;
	Node * p = node->parent;

	if (r->left != NULL)
		r->left->parent = node;

	node->right = r->left;
	node->parent = r;
	r->left = node;
	r->parent = p;

	if (p != NULL){
		if (p->left == node)
			p->left = r;
		else
			p->right = r;
	}
}

//주어진 노드를 기준으로 오른쪽회전
void RRotate(Node * node){
	Node * l = node->left;
	Node * p = node->parent;

	if (l->right != NULL)
		l->right->parent = node;

	node->left = l->right;
	node->parent = l;
	l->right = node;
	l->parent = p;

	if (p != NULL){
		if (p->left == node)
			p->left = l;
		else
			p->right = l;
	}
}

void RBDelete(RBtree * rbtree, Node * delNode){

}

//이미 tree에 존재하는 key를 입력하면 -1을 반환
int RBInsert(RBtree * rbtree, Node * newNode){
	Node * cur; //삽입할 위치
	int key = Getkey(newNode);

	if (rbtree->root == NULL){
		newNode->color = BLACK;
		rbtree->root = newNode;
	}
	else{
		cur = rbtree->root;

		while (1){
			if (Getkey(cur) > key)
				cur = cur->left;
			else if (Getkey(cur) < key)
				cur = cur->right;
			else //이미 존재하는 key값
				return -1;

			if (cur->left == NULL && cur->right == NULL){ //트리의 종점까지 다다른 상황이면 bewNode를 삽입해준다.
				if (Getkey(cur) > key)
					cur->left = newNode;
				else if (Getkey(cur < key))
					cur->right = newNode;
				else //이미 존재하는 key 값
					return -1;

				newNode->parent = cur;

				break;
			}
		}
	}

	InsertCase1(rbtree, newNode);

	rbtree->num++;
	return;
}

//삽입하려는 위치가 root일 경우
void InsertCase1(RBtree * rbtree, Node * newNode){
	if (newNode->parent == NULL)
		newNode->color = BLACK;
	else
		InsertCase2(rbtree, newNode);
}

//삽입하려는 위치의 부모노드가 BLACK인 경우
void InsertCase2(RBtree * rbtree, Node * newNode){
	if (newNode->parent->color == BLACK)
		return;
	else
		InsertCase3(rbtree, newNode);
}

//부모노드와 삼촌노드가 모두 RED인 경우
void InsertCase3(RBtree * rbtree, Node * newNode){
	Node * u = Uncle(newNode);
	Node * g = GrandParent(newNode);

	//부모와 삼촌 노드를 BLACK으로 변경하고, 조부모 노드를 RED로 변경한다. 이후 조부모 노드에 대해 Insert를 진행한다
	if ((u != NULL) && (newNode->parent != NULL) && (u->color == RED) && (newNode->parent->color == RED)){
		newNode->parent->color = BLACK;
		u->color = BLACK;
		g->color = RED;

		InsertCase1(rbtree, g);
	}
	else
		InsertCase4(rbtree, newNode);
}

void InsertCase4(RBtree * rbtree, Node * newNode){

}

void RBPrint(RBtree * rbtree){

}


void RBSearch(RBtree * rbtree, Node * searchNode){

}
