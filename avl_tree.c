#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

inline int max(int a, int b)
{

	return (a > b)?a:b;
}

struct node
{
	int data;
	struct node *prev;
	struct node *left;
	struct node *right;
};

struct node* alloc(int x, struct node *p)
{
	struct node *tmp;

	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = x;
	tmp->prev = p;
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

int height(struct node *curr) {
	if (curr == NULL) {

		return 0;
	}

	return (max(height(curr->left), height(curr->right)) + 1);
}

bool is_left(struct node *curr)
{
	if (curr == NULL) {
		
		return false;
	}

	if (curr->prev == NULL) {

		return false;
	}

	if (curr->prev->left == curr) {

		return true;
	}

	return false;
}

void llrotate(struct node *curr, struct node **root)
{
	struct node *tmp;

	tmp = NULL;

	if (curr->right != NULL) {
		tmp = curr->right->left;
	}

	if (curr->prev != NULL) {
		if(is_left(curr) == true) {
			curr->prev->left = curr->right;
			curr->prev->left->prev = curr->prev;
			curr->prev = curr->prev->left;
		} else {
			curr->prev->right = curr->right;
			curr->prev->right->prev = curr->prev;
			curr->prev = curr->prev->right;
		}
		curr->prev->left = curr;
	} else {
		*root = curr->right;
		curr->prev = curr->right;
		curr->prev->left = curr;
		curr->prev->prev = NULL;
	}

	curr->right = tmp;
	if (curr->right != NULL) {
		curr->right->prev = curr;
	}

	return;
}

void rrrotate(struct node *curr, struct node **root)
{
	struct node *tmp;
	struct node *l;

	tmp = NULL;
	l = curr->left;

	if (l != NULL) {
		tmp = l->right;
	}

	l->prev = curr->prev;

	if (curr->prev != NULL) {
		if (is_left(curr) == true) {
			l->prev->left = l;
		} else {
			l->prev->right = l;
		}
	} else {
		*root = l;
	}

	l->right = curr;
	curr->prev = l;

	curr->left = tmp;
	if (tmp != NULL) {
		tmp->prev = curr;
	}

	return;
}

void lrrotate(struct node *curr, struct node **root)
{
	llrotate(curr->left, root);
	rrrotate(curr, root);

	return;
}

void rlrotate(struct node *curr, struct node **root)
{
	rrrotate(curr->right, root);
	llrotate(curr, root);
	
	return;
}

void rec_check(struct node *curr, struct node **root, int x)
{
	int hl; // height of left subtree
	int hr; // height of right subtree
	int bf; // balance factor of current node

	if (curr == NULL) {

		return;
	}

	hl = height(curr->left);
	hr = height(curr->right);

	bf = hl - hr;

	if (abs(bf) > 1) {
		if (x < curr->data) { // left
			if (x < curr->left->data) { // left
				printf("\nRight Rotate (%d)\n", curr->data);
				rrrotate(curr, root);
			} else { //right
				printf("\nLR Rotate (%d)\n", curr->data);
				lrrotate(curr, root);
			}
		} else { // right
			if (x < curr->right->data) { // left
				printf("\nRL Rotate (%d)\n", curr->data);
				rlrotate(curr, root);
			} else { // right
				printf("\nLeft Rotate (%d)\n", curr->data);
				llrotate(curr, root);
			}
		}
		
		return;
	} /*else {
		rec_check(curr->prev, root, x);
	}*/
	rec_check(curr->prev, root, x);

	return;
}

void insert(struct node **root, int x)
{
	if (*root == NULL) {
		*root = alloc(x, NULL);

		return;
	}

	struct node *curr;
	struct node *prev;

	curr = *root;
	prev = NULL;
	
	while (curr != NULL) {
		prev = curr;
		if (x == curr->data) {

			return;
		}
		if (x < curr->data) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}
	
	if (x < prev->data) {
		prev->left = alloc(x, prev);
		curr = prev->left;
	} else {
		prev->right = alloc(x, prev);
		curr = prev->right;
	}

	rec_check(curr, root, x);

	return;
}

void inorder_t(struct node *curr)
{
	if (curr == NULL) {

		return;
	}
	inorder_t(curr->left);
	printf("%d ", curr->data);
	inorder_t(curr->right);

	return;
}

void preorder_t(struct node *curr)
{
	if (curr == NULL) {

		return;
	}

	printf("%d ", curr->data);
	preorder_t(curr->left);
	preorder_t(curr->right);

	return;
}

int main()
{
	int n;
	int x;
	int i;
	struct node *root;

	root = NULL;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &x);
		insert(&root, x);
	}

	printf("\nPreorder traversal:\n\t");
	preorder_t(root);
	printf("\n");

	return 0;
}
/* Test case 1:
9
15 20 24 10 13 7 30 36 25
* Test case 2:
13
14 4 3 2 9 7 10 21 15 18 28 26 30
*/
