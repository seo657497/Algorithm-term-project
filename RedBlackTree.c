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
	else if (node->parent == g->left)
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
	Node * p; //cur의 부모노드
	int key = Getkey(newNode);

	if (rbtree->root == NULL){
		newNode->color = BLACK;
		rbtree->root = newNode;
		rbtree->num++;
		return 0;
	}
	else{
		cur = rbtree->root;

		while (1){
			if (Getkey(cur) > key){
				p = cur;
				cur = cur->left;
			}
			else if (Getkey(cur) < key){
				p = cur;
				cur = cur->right;
			}
			else //이미 존재하는 key값
				return -1;

			if (cur == NULL){ //트리의 종점까지 다다른 상황이면 bewNode를 삽입해준다.
				if (Getkey(p) > key)
					p->left = newNode;
				else if (Getkey(p) < key)
					p->right = newNode;
				else //이미 존재하는 key 값
					return -1;

				newNode->parent = p;

				break;
			}
		}
	}

	InsertCase1(rbtree, newNode);

	rbtree->num++;
	return 0;
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
//부모노드가 BLACK인 경우는 이미 case2에서 다루었으므로 여기서는 부모노드가 RED임을 가정할 수 있다.
void InsertCase3(RBtree * rbtree, Node * newNode){
	Node * u = Uncle(newNode);
	Node * g = GrandParent(newNode);

	//부모와 삼촌 노드를 BLACK으로 변경하고, 조부모 노드를 RED로 변경한다. 이후 조부모 노드에 대해 Insert를 진행한다
	if ((u != NULL) && (u->color == RED)){
		newNode->parent->color = BLACK;
		u->color = BLACK;
		g->color = RED;

		InsertCase1(rbtree, g);
	}
	else
		InsertCase4(rbtree, newNode);
}


/*
 부모노드가 RED이고 삼촌노드가 BLACK인 경우에는
 newNode가 부모노드의 오른쪽 자식이며 부모노드는 조부모 노드의 왼쪽 자식인 경우와 (1)
 newNode가 부모노드의 왼쪽 자식이며 조부모 노드의 오른쪽 자식인 경우 2가지를 다루게된다. (2) 
 부모노드를 기준으로 (1)의 경우엔 왼쪽 회전을 해주고 (2)의 경우엔 오른쪽 회전을 하여 newNode와 부모노드의 역할을 바꿔준뒤에 case5로 넘긴다.
 부모노드와 삼촌노드가 모드 RED인 경우는 case3에서 다루었으므로 여기서는 부모노드가 RED 삼촌노드가 BLACK임을 가정할 수 있다.
 */
void InsertCase4(RBtree * rbtree, Node * newNode){
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if ((newNode == p->right) && (p == g->left)){ //(1)의 경우
		LRotate(p);
		newNode = newNode->left; //변경된 위치의 p노드를 지정
	}
	else if ((newNode == p->left) && (p == g->right)){ //(2)의 경우
		RRotate(p);
		newNode = newNode->right; //변경된 위치의 p노드를 지정
	}

	InsertCase5(rbtree,newNode);
}

/*
부모노드가 RED이고 삼촌노드가 BLACK이며
newNode가 부모노드의 오른쪽 자식이며 부모노드는 조부모 노드의 오른쪽 자식인 경우와(1)
newNode가 부모노드의 왼쪽 자식이며 부모노드는 조부모 노드의 왼쪽 자식인 경우 2가지를 다루게 된다(2)
조부모 노드를 RED로, 부모노드를 BLACK으로 변경한뒤에 
조부모 노드를 기준으로 (1)의 경우엔 왼쪽 회전을 (2)의 경우엔 오른쪽 회전을 해준다.
이로써 RBtree의 모든 특성을 만족하게 된다.
*/
void InsertCase5(RBtree * rbtree, Node * newNode){
	Node * g = GrandParent(newNode);
	Node * p = newNode->parent;

	if (g != NULL)
	    g->color = RED;

	p->color = BLACK;

	if (newNode == p->right){//(1)의 경우
		LRotate(g);

		if (rbtree->root == g) //루트노드가 변경된 경우
			rbtree->root = p;
	}
	else{ //(2)의 경우 
		RRotate(g);

		if (rbtree->root == g) //루트노드가 변경된 경우
			rbtree->root = p;
	}
}

void RBPrint(RBtree * rbtree){

}

//rbtree에서 key값을 갖는 노드를 찾는다.
//노드를 검색하는데 성공할 경우 그 노드의 주소값 반환
//검색에 실패할 경우(key값을 갖는 노드가 없는 경우) NULL반환
Node * RBSearch(RBtree * rbtree, int key){
	Node * cur = rbtree->root;

	while (1){
		if (Getkey(cur) == key)
			return cur;
		else if (Getkey(cur) > key)
			cur = cur->left;
		else
			cur = cur->right;

		if (cur == NULL)
			return NULL;
	}

}

//디버깅을 위한 용도 임시 프린트, preorder형식
//제출 시엔 삭제
void RBTest_Print(Node * node){
	if (node == NULL)
		return;
	
	printf("%d(%d) ", Getkey(node), node->color); //key(색)
	
	RBTest_Print(node->left);
	RBTest_Print(node->right);
}
