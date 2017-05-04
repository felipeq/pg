#include <iostream>
using namespace std;
struct Node
{
	Node *left;
	Node *right;
	Node *top;
	long long int value;
	long long int depth;
};
Node *root;
int h=1;
void Print(Node *root)
{
	if (root->depth==h-1)
	{
		cout << root->value <<"\n";
		return;
	}
	else
	{
		if (root->left!=NULL)
			Print(root->left);
		if (root->right!=NULL)
			Print(root->right);
	}
}
Node *NewNode(Node *root,int k)
{
	Node *N;
	N=new Node;
	N->left=N->right=NULL;
	N->top=root;
	N->value=k;
	N->depth=root->depth;
	N->depth++;
	if (h<=N->depth) h=N->depth;
	return N;
}
void InsertNode(Node *root, int k)
{
	if (k==root->value) return;				// omijamy identyczne
	if (k<root->value && root->left!=NULL)
	{
		InsertNode(root->left,k);
	}
	if (k>root->value && root->right!=NULL)
	{
		InsertNode(root->right,k);
	}
	if (k<root->value && root->left==NULL)	// jeœli idziemy na puste lewo
	{
		root->left=NewNode(root,k);
		return;
	}
	if (k>root->value && root->right==NULL)
	{
		root->right=NewNode(root,k);
		return;
	}

}
int main()
{
	long long int g,k;
	cin >> g;
	root=new Node;
	root->top=root->left=root->right=NULL;

	cin >> k;
	root->value=k;
	root->depth=1;
	g--;

	while (g--)
	{
		cin >> k;
		InsertNode(root,k);
	}

	Print(root);
	return 0;
}
