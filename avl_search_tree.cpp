#include<iostream>
using namespace std;
class node {
	public:
	node *prev;
	int info, depth;
	node *c1, *c2;
	node(){
		prev=NULL;
		c1=NULL;
		c2=NULL;
		depth=0;
	}
} *head=NULL, *left_low=NULL, *right_low=NULL;

class tree
{
	public:
	void insert1(int info)
	{
		head = new node;
		head->depth=1;
		head->info=info;
		head->prev=NULL;
	}
	
/*
 * These are rotation functions called by rotationControl().
 */	
	void llRotate(node *curr)
	{
		node *tmp=curr->c1;
		tmp->prev=curr->prev;
		curr->prev=tmp;
		curr->c1=tmp->c2;
		tmp->c2=curr;
	}
	
	void rrRotate(node *curr)
	{
		node *tmp=curr->c2;
		tmp->prev=curr->prev;
		curr->prev=tmp;
		curr->c2=tmp->c1;
		tmp->c1=curr;
	}
	
	void lrRotate(node *curr)
	{
		node *tmp1=curr->c1, *tmp2=tmp1->c2;
		tmp2->prev=curr->prev;
		tmp1->c2=tmp2->c1; tmp1->c2->prev=tmp1;
		curr->c1=tmp2->c2; curr->c1->prev=curr;
		tmp2->c1=tmp1; tmp2->c1->prev=tmp2;
		tmp2->c2=curr; tmp2->c2->prev=tmp2;
		if(curr==head)
		head=tmp2;
	}
	
	void rlRotate(node *curr)
	{
		node *tmp1=curr->c2, *tmp2=tmp1->c1;
		tmp2->prev=curr->prev;
		tmp1->c1=tmp2->c2; tmp1->c1->prev=tmp1;
		curr->c2=tmp2->c1; curr->c2->prev=curr;
		tmp2->c1=curr; tmp2->c1->prev=tmp2;
		tmp2->c2=tmp1; tmp2->c2->prev=tmp2;
		if(curr==head)
		head=tmp2;
	}

/*
 * This function calculates the depth of the children of each node,
 *  from the newly inserted position and stores them in l and r. 
 * Then it checks if difference of l and r lie b/w -1 and 1.
 * If yes, then, curr->depth is calculated, and calls itself on curr->prev
 * 														(if curr->prev!=NULL).
 * If not, rotationControl() is called on curr position, and returns.
 */
	void calcDepth(node *curr)
	{
		int l=0, r=0, d=0;
		if(curr==NULL)return;
		if(curr->c1==NULL&&curr->c2==NULL)	   /*if curr has no children, 
												*	i.e., curr is a leaf
												*/
		{
			curr->depth=1;
			calcDepth(curr->prev);
			return;
		}
		if(curr->c1!=NULL) //check next condition only if curr has left child
		{
			if(curr->c1->depth==0) /* 
								* if c1->depth not yet calculated, or reset by 
								* traverse()
								*/ 
			{
				calcDepth(curr->c1);
				//l=curr->c1->depth;
			}
			/*else //if c1 has depth
			l=curr->c1->depth;
			* I directly access depth for calculating d, now
			* */
			
		}
		
		if(curr->c2!=NULL) //check next condition only if curr has right child
		{
			if(curr->c2->depth==0) /* 
								* if c2->depth not yet calculated, or reset by 
								* traverse()
								*/
			{
				calcDepth(curr->c2);
				//r=curr->c2->depth;
			}
			/*else //if c2 has depth
			 * * I directly access depth for calculating d, now
			* 
			r=curr->c2->depth; do nothing*/
		}
		d=(curr->c1->depth)-(curr->c2->depth);
		if(!((d>=-1)&&(d<=1)))
		{
			rotationControl(curr);
			return;
		}
		else
		{
			curr->depth=(l>r)?(l+1):(r+1);
			if(l==r)curr->depth=l+1;
			if(curr->prev!=NULL) //if curr is not the head
			calcDepth(curr->prev);
		}
	}
	
	
/*
 * This function is meant to be called from calcDepth() if difference of two
 * subtrees' depths is not b/w -1 and 1. This function if called with the node 
 * which is to be rotated as an argument.
 * This function looks two nodes deep to decide rotation to be used
 * 	Find greater of the two children of current node(also, use 0 if no child)
 * 		i. if left, check:
 * 			 check for greater of the two children of the left child
 * 				if left, llRotate(curr)
 * 				if right, lrRotate(curr)
 * 		ii. if right, check:
 * 			 check for greater of the two children of the child
 * 				if left, rlRotate(curr)
 * 				if right, rrRotate(curr)
 * 
 */
	void rotationControl(node *curr)
	{
		int l=0, r=0, ll=0, lr=0, rl=0, rr=0;
		//Finding nodes which exist, and keeping the depths for further use
		if(curr->c1!=NULL)//if c1 exists
		{
			l=curr->c1->depth;
			if(curr->c1->c1!=NULL) //if left of left exists
			ll=curr->c1->c1->depth;
			if(curr->c1->c2!=NULL) //if right of left exists
			lr=curr->c1->c2->depth;
		}
		if(curr->c2!=NULL)//if c2 exists
		{
			r=curr->c2->depth;
			if(curr->c2->c1!=NULL) //if left of right exists
			rl=curr->c2->c1->depth;
			if(curr->c2->c2!=NULL) //if right of right exists
			rr=curr->c2->c2->depth;
		}
		
		//Now, time to decide rotation
		if(l>r) //if depth of left child > right child
		{
			if(ll>lr) //if depth of left sub-child > right sub-child
			llRotate(curr);
			else //if depth of right sub-child > left sub-child
			lrRotate(curr);
		}
		else //if depth of right child > left child
		{
			if(rl>rr) //if depth of left sub-child > right sub-child
			rlRotate(curr);
			else //if depth of right sub-child > left sub-child
			rrRotate(curr);
		}
	}
	
	void insert(int info)
	{
		if (head==NULL)
		{ 
			cout<<"Empty tree! Creating head first...\n";
			insert1(info);
			cout<<info<<" Inserted to head\n";
			return;
		}
		node *curr=head;
		while(curr!=NULL)
		{
			if(curr->info<info)	
			{
				if(curr->c2!=NULL)curr=curr->c2;
				else //means empty, and pos found
				{
					curr->c2=new node;
					curr->c2->info=info;
					curr->c2->prev=curr;
					curr=curr->c2;
					calcDepth(curr);
					break;
				}
			}
			else if(curr->info>info) 
			{
				if(curr->c1!=NULL)curr=curr->c1;
				else //means empty, and pos found
				{
					curr->c1=new node;
					curr->c1->info=info;
					curr->c1->prev=curr;
					curr=curr->c1;
					calcDepth(curr);
					break;
				}
			}
			else if(curr->info==info)return;
		};
				
		traverse();
		return;
	}
/*
 * This recursive function can be used for traversing the tree, inorder 
 */
	void traverse(node *c=head)
	{
		if(c==head) //meaning, new traversal of tree
		cout<<"\n";
		if(c==NULL)		//i.e., end of sub-tree reached... base case
		{
			//cout<<" ";
			return;
		}
		if(c->c1==NULL&&c->c2==NULL) //i.e., end of sub-tree reached... :>
		{
			cout<<" "<<c->info; 
			return;
		}
		traverse(c->c1);
		cout<<" "<<c->info;
		c->depth=0;
		traverse(c->c2);
	}
};
int main()
{
	tree a;
	a.insert(64); a.insert(1); a.insert(14); a.insert(3); a.insert(0);
	//a.insert(141);
	//a.insert(4); a.insert(5); a.insert(6);
	return 0;
}