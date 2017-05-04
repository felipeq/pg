#include <iostream>
#include <string>

using namespace std;


struct Node
{
	int pr;
	string war;
	Node* left,*right,*top;
	int rozmiar;
};
struct Heap
{
	char name;
	Heap *next;
	Node *root;
	Node *last;
};
Heap *first;
Node *NewNode(int pr, string war, int rozmiar, Node *top)
{
	Node *N;
	N=new Node;
	N->pr=pr;
	N->war=war;
	N->left=N->right=NULL;
	N->top=top;
	N->rozmiar=rozmiar;
	return N;
}
Heap *FindHeap(char k)
{
	Heap *temp;
	temp=first;
	for ( int i=0;i<26;i++)
	{
		if (temp->name==k) return temp;
		else temp=temp->next;
	}
}
void IncSize(Node *root)
{
	root->rozmiar++;
	if (root->top!=NULL) IncSize(root->top);
}
void SwapNodes(Node *a,Node *b)
{
	int i=a->pr;
	string ss=a->war;
	a->pr=b->pr;
	a->war=b->war;
	b->pr=i;
	b->war=ss;
}
void Heapify(Node *N)
{
	if (N->top!=NULL && N->top->pr > N->pr)
	{
		SwapNodes(N->top,N);
		Heapify(N->top);
	}
}
void AddToHeap(Heap *CoreHeap, Node* root, Node *N)
{
	if (root->left==NULL)						{ root->left=N;		N->top=root;	IncSize(root);	Heapify(N); return; }
	if (root->left!=NULL && root->right==NULL)	{ root->right=N;	N->top=root;	IncSize(root);	Heapify(N); return; }
	if (root->left->rozmiar==root->right->rozmiar) 
	{
		AddToHeap(CoreHeap, root->left, N);
		return;
	}
	if (root->left->rozmiar>root->right->rozmiar) 
	{
		AddToHeap(CoreHeap, root->right, N);
		return;
	}
	if (root->left->rozmiar<root->right->rozmiar)
	{
		AddToHeap(CoreHeap, root->left, N);
		return;
	}
}
void ShowHeap(Node *root)
{
	cout << root->pr;
	if (root->top!=NULL) {cout << " nalezy do " << root->top->pr << " o wysokosci: " << root->top->rozmiar;
	if (root==root->top->left) cout << " . Z lewej.";
	else cout << " . Z prawej.";}
	cout << endl;
	if (root->left!=NULL)
		ShowHeap(root->left);
	if (root->right!=NULL)
		ShowHeap(root->right);
}
Node *FindLastLeaf(Node* root)
{
	
}
void DeleteMin(Heap* Core)
{
	cout << Core->root->war << endl;
	Node* last=FindLastLeaf(Core->root);

}
int main()
{
	Node *a;
	a=new Node;
	Node *b;
	b=new Node;
	a->pr=2;
	b->pr=3;
	
	first=new Heap;
	first->name='A';
	first->root=NULL;
	Heap *last;
	last=first;
	for ( int i=0;i<26;i++)
	{
		Heap *temp;
		temp=new Heap;
		temp->name=65+i;
		temp->root=NULL;
		if ( i==0)
		{
			first->next=temp;

			continue;
		}
		last->next=temp;
		last=temp;
	}
	last->next=NULL;
	while(true)
	{
		char ins;
		cin >> ins;
		if (ins=='I')	//I k p w - wstawienie elementu (priorytetu p i wartoœci w) do kopca k.
		{
			char k;
			cin >> k;
			int p;
			cin >> p;
			string w;
			cin >> w;
			
			//cout << "Chcesz dodaæ do " << k << " int: " << p << "i string: " << w << endl;
			Heap *choosen=FindHeap(k);
			if (choosen->root==NULL) choosen->root=NewNode(p,w,0,NULL);
			else { AddToHeap(choosen,choosen->root,NewNode(p,w,0,NULL)); }
		}
		if ( ins=='S')
		{
			char k;
			cin >> k;
			ShowHeap(FindHeap(k)->root);
		}
		if (ins=='D')
		{
			char k;
			cin >> k;
			DeleteMin(FindHeap(k));
		}
		
	}
	return 0;
}