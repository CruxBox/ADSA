#include<stdio.h>

enum color {red,black};

typedef struct Node{
	int val;
	int col;
	node* parent;
	node* left;
	node* right;
}node;

node* root = NULL;

void setColor(node* x, int col){
	x->col = col;
}
int getColor(node* x){
	return x->col;
}
void fixinsert();

node* makenode(int val){
	node* temp = malloc(sizeof(node));
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
			grandparent->left = left;
	}
	else root = right;

	parent->parent = right;

}


void fixinsert(node* ptr){

	while(getColor(ptr)==red && ptr!=root && getColor(parent)==red){
	node* parent = ptr->parent;
	node* grandparent = parent->parent;

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
				//right rotate the grandparent and swap colors of g and p
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
				}
				//left rotate the grandparent and swap colors of g and p
			}	
		}
	}
	setColor(root,black);
}

void insert(node* subroot, node* x){

	if(subroot == NULL) subroot = x;
	else if(subroot->val >= x->val){
		insert(subroot->left, x);
		subroot->left->parent = subroot;
		fixinsert(ptr);
	}
	else if(subroot->val <x->val){
		insert(subroot->right, x);
		subroot->right->parent = subroot;
		fixinsert(ptr);
	}
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
}
