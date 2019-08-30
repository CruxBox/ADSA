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
	x->col = col;
}
int getColor(node* x){
	return x->col;
}
void fixinsert();

node* makenode(int val){
	node* temp = (node*)malloc(sizeof(node));
	temp->col = red;
	temp->val = val;
	temp->parent = temp->right = temp->left = NULL;
	return temp;
}
void left_rotate(node* parent){
	node* right = parent->right;
	node* right_left = right->left;

	node* grandparent = parent->parent;
	
	parent->right = right_left;
	
	if(right_left != NULL){
		right_left->parent = parent;	
	}

	right->parent = grandparent;
	
	if(grandparent != NULL){
		if(parent == grandparent->right){
			grandparent->right = right;
		}
		else
			grandparent->left = right;
	}
	else root = right;

	parent->parent = right;

}

void right_rotate(node* ptr){

node* left = ptr->left;
node* g_grandparent = ptr->parent;
node* left_right = left->right;

left->parent = g_grandparent;
if(g_grandparent != NULL)
{
	if(g_grandparent->right == ptr)
		g_grandparent->right = left;
	else 
		g_grandparent->left = left;
}
ptr->left = left_right;
ptr->parent = left;
left->right = ptr;
left_right->parent = ptr;

}


void fixinsert(node* ptr){

	node* parent = ptr->parent;
	node* grandparent = parent->parent;

	while(getColor(ptr)==red && ptr!=root && getColor(parent)==red){

		if(parent == grandparent->left){
			node* uncle = grandparent->right;
			if(getColor(uncle) == red){
				setColor(uncle,black);
				setColor(parent,black);
				setColor(grandparent,red);
				ptr=grandparent;
			}
			else{
				if(ptr == parent->right){
					//left rotate the parent and change pointers
					left_rotate(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				//right rotate the grandparent,swao colors of g and p and change ptr
				swap(&grandparent->col, &parent->col);
				right_rotate(grandparent);
				ptr = parent;
			}
		}
		else{
		node* uncle = grandparent->left;
			if(getColor(uncle) == red){
				setColor(uncle,black);
				setColor(parent,black);
				setColor(grandparent,red);
				ptr=grandparent;
			}
			else{
				if(ptr == parent->left){
					//right rotate the parent and change pointers
					right_rotate(parent);
					ptr = parent;
					parent = parent->left;
				}
				//left rotate the grandparent and swap colors of g and p and change ptr
				swap(&grandparent->col, &parent->col);
				left_rotate(grandparent);
				ptr = parent;
			}	
		}
	node* parent = ptr->parent;
	node* grandparent = parent->parent;
	}
	setColor(root,black);
}

void insert(node* subroot, node* x){

	if(subroot == NULL) subroot = x,fixinsert(subroot);
	else if(subroot->val > x->val){
		insert(subroot->left, x);
		subroot->left->parent = subroot;
	}
	else if(subroot->val <x->val){
		insert(subroot->right, x);
		subroot->right->parent = subroot;
	}
}
void inorder(node* root){
	if(root == NULL) return ;
	inorder(root->left);
	printf("val: %d, col: %d\n",root->val,root->col);
	inorder(root->right);
}

int main(){
	int n;
	scanf("%d",&n);
	int a;
	node* temp;
	for(int i=0;i<n;i++){
		scanf("%d",&a);
		temp = makenode(a);
		insert(root,temp);
	}

	inorder(root);
}
