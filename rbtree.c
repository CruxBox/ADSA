#include<stdio.h>
#include<stdlib.h>

enum color {red,black};

typedef struct Node{
	int val;
	int col;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
}node;

void swap(int* a, int* b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

node* root = NULL;

void setColor(node* x, int col){
	if(x == NULL) return;
	x->col = col;
}

int getColor(node* x){
	if(x == NULL) return black;
	return x->col;
}

node* makenode(int val){
	node* temp = (node*)malloc(sizeof(node));
	temp->col = red;
	temp->val = val;
	temp->parent = temp->right = temp->left = NULL;
	return temp;
}
void left_rotate(node** parent){

	node* grandparent = (*parent)->parent;
	node* right = (*parent)->right;
	(*parent)->right = right->left;
		
	if(right->left != NULL){
		right->left->parent = *parent;	
	}

	right->parent = grandparent;
	
	if(grandparent != NULL){
		if(*parent == grandparent->right){
			grandparent->right = right;
		}
		else
			grandparent->left = right;
	}
	else root = right;

	right->left = *parent;
	(*parent)->parent = right;

}

void right_rotate(node** ptr){

node* left = (*ptr)->left;
node* grandparent = (*ptr)->parent;
node* left_right = left->right;

left->parent = grandparent;
if(grandparent != NULL)
{
	if(grandparent->right == *ptr)
		grandparent->right = left;
	else 
		grandparent->left = left;
}
(*ptr)->left = left_right;
(*ptr)->parent = left;
left->right = *ptr;

if(left_right!=NULL)
	left_right->parent = *ptr;
}


void fixinsert(node** ptr){

	node* parent = (*ptr)->parent;

	while(getColor(*ptr)==red && *ptr!=root && getColor(parent)==red){

		node* grandparent = parent->parent;
		if(parent == grandparent->left){
			node* uncle = grandparent->right;
			if(getColor(uncle) == red){
				setColor(uncle,black);
				setColor(parent,black);
				setColor(grandparent,red);
				*ptr=grandparent;
			}
			else{
				if(*ptr == parent->right){
					//left rotate the parent and change pointers
					left_rotate(&parent);
					*ptr = parent;
					parent = (*ptr)->parent;
				}
				//right rotate the grandparent,swao colors of g and p and change ptr
				swap(&grandparent->col, &parent->col);
				right_rotate(&grandparent);
				*ptr = parent;
			}
		}
		else{
		node* uncle = grandparent->left;
			if(getColor(uncle) == red){
				setColor(uncle,black);
				setColor(parent,black);
				setColor(grandparent,red);
				*ptr=grandparent;
			}
			else{
				if(*ptr == parent->left){
					//right rotate the parent and change pointers
					right_rotate(&parent);
					*ptr = parent;
					parent = (*ptr)->parent;
				}
				//left rotate the grandparent and swap colors of g and p and change ptr
				swap(&grandparent->col, &parent->col);
				left_rotate(&grandparent);
				*ptr = parent;
			}	
		}
	parent = (*ptr)->parent;
	}
}

void insert(node** subroot, node** x){

	if(*subroot == NULL) (*subroot) = *x;
	else if((*subroot)->val > (*x)->val){
		insert(&(*subroot)->left, x);
		(*subroot)->left->parent = (*subroot);
	}
	else if((*subroot)->val <(*x)->val){
		insert(&(*subroot)->right, x);
		(*subroot)->right->parent = (*subroot);
	}
}
void inorder(node* root){
	if(root == NULL) return ;
	inorder(root->left);
	printf("val: %d, col: %d\n",root->val,root->col);
	inorder(root->right);
}

int main(){
	int num;
	scanf("%d",&num);
	int a;
	node* temp;
	for(int i=0;i<num;i++){
		scanf("%d",&a);
		temp = makenode(a);
		insert(&root,&temp);
		fixinsert(&temp);
		setColor(root,black);
	}

	inorder(root);
}
