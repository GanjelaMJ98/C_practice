#include <stdio.h>
#include <stdlib.h>


struct bstree{
	int key;
	char *value;
	struct bstree* left;
	struct bsrtee* right;
};

struct bstree* bstree_create(int key, char *value){
	struct bstree* new;
	new = (struct bstree*)malloc(sizeof(struct bstree));
	if(new){
		new->key = key;
		new->value = value;
		new->left = NULL;
		new->right = NULL;
	}
	return new;
}

int bstree_add(struct bstree* bst, int key, char * value){
	struct bstree *parent, *new;

	if(!bst) return 0;

	for(parent = bst; bst != NULL;){
		parent = bst;
		if(key > bst->key)
			bst = bst->right;
		else 
			if(key < bst->key)
				bst = bst->left;
			else return 0;
	}

	new = bstree_create(key,value);

	if(key> parent->key)
		parent->right = new;
	else
		parent->left = new;
}

struct bsrtee* bstree_max(struct bstree* bst){  
	if(!bst) 
		return bst;

	while(bst->right != NULL)
		bst = bst->right;

	return bst;
}

struct bstree* bstree_min(struct bstree* bst){
	if(!bst)
		return bst;
	
	while(bst->left != NULL)
		bst = bst->left;
	
	return bst;
}

void print(struct bstree* bst, void *arg){
	printf("%d", bst->key);
	printf("%s", bst->value);
	printf("\n");
}


struct bstree* bstree_search(struct bstree* bst, int key){  
	struct bstree *parent;

	if(!bst) return 0;

	for(parent = bst; bst->key != key;){
		parent = bst;
		if(key > bst->key)
			bst = bst->right;
		else 
			if(key < bst->key)
				bst = bst->left;
			else return 0;
	}
	return bst;
}

void preOrderTravers(struct bstree* root, void (*visit)(struct bstree*, void*), void *params){
	if(root){
		visit(root, params);
		preOrderTravers(root->left, visit, params);
		preOrderTravers(root->right, visit, params);
	}
}


void inOrderTravers(struct bstree* root, void (*visit)(struct bstree*, void*), void *params){
	if(root){
		inOrderTravers(root->left, visit, params);
		visit(root, params);
		inOrderTravers(root->right, visit, params);
	}
}


void postOrderTravers(struct bstree* root, void (*visit)(struct bstree*, void*), void *params){
	if(root){
		postOrderTravers(root->left, visit, params);
		postOrderTravers(root->right, visit, params);
		visit(root, params);
	}
}


int bstree_del(struct bstree* bst, int key){
	struct bstree *parent, *new;

	if(!bst) return 0;

	for(parent = bst; bst->key != key;){
		parent = bst;
		if(key > bst->key)
			bst = bst->right;
		else 
			if(key < bst->key)
				bst = bst->left;
			else return 0;
	}


if(bst->left == NULL && bst->right == NULL){  //если элемент - лист
	if(key> parent->key)
		parent->right = NULL;
	else
		parent->left = NULL;
	free(bst);
}

if(bst->left != NULL && bst->right == NULL){   //если у элемента есть только левая ветка
	bst = bst->left;
	free(bst->left);
}

if(bst->left == NULL && bst->right != NULL){  //если у элемента есть только правая ветка
	bst = bst->right;
	free(bst->right);
}

if(bst->left != NULL && bst->right != NULL){  //если у элемента есть обе ветки
	struct bstree *new;
	new = bstree_min(bst->right);
	bst->key = new->key;
	bst->value = new->value;
	free(bstree_min(bst->right));
	}
}




int main(){
	
	struct bstree* tree = bstree_create(500,"root");

	bstree_add(tree, 400, "left");
	bstree_add(tree, 600, "right");
	bstree_add(tree, 350, "left-left");
	bstree_add(tree, 550, "right-left");
	bstree_add(tree, 700, "right-right");
	bstree_add(tree, 650, "del");
	bstree_add(tree, 750, "max");
	
	inOrderTravers(tree, print, NULL);
	printf("\n");

	
	print(bstree_min(tree), NULL);
	printf("\n");
	
	bstree_del(tree,650);
	

	print(bstree_max(tree), NULL);
	printf("\n");
	
	print(bstree_search(tree,750), NULL);
	printf("\n");

	preOrderTravers(tree, print, NULL);
	printf("\n");
}
