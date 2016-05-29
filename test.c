#include "RedBlackTree.h"

int main(void){
	int n,col,row;
	int key;
	RBtree * rbtree = (RBtree *)malloc(sizeof(RBtree));
	Node * temp;

	RBinit(rbtree);
	
	scanf("%d", &n);

	for (; n > 0; n--){
		scanf("%d %d", &col, &row);
		temp=SetNode(col, row);
		RBInsert(rbtree,temp);
	}
	
	RBTest_Print(rbtree->root);


	printf("\nkey : ");
	scanf("%d", &key);

	if (RBSearch(rbtree, key) == NULL)
		printf("찾는 key가 없음\n");
	else
		printf("검색 성공!\n");
	
}