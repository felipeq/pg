/*
Input

Na wejœcie programu podana zostanie pewna iloœæ poleceñ. Ka¿de z poleceñ sk³ada siê ze znaku i liczby rozdzielonych spacj¹. Istniej¹ dwa typy poleceñ: I n oraz O n. Poszczególne komendy zostan¹ rozdzielone znakiem nowej linii.

Output

Na wyjœciu maj¹ siê pojawiæ rezultaty wczytywanych z wejœcia poleceñ:
I n - wstaw n do drzewa lub nie rób nic, jeœli ten wyraz ju¿ jest w drzewie; nic nie drukuj; (ju¿ zrobione)
O n - wypisz wierzcho³ki z poddrzewa ukorzenionego w n w kolejnoœci inorder, rozdzielaj¹c je spacjami; jeœli poddrzewo nie istnieje, wypisz "-"

Example

Input:
I 9
I 14
I 6
I 4
I 7
O 5
O 9
O 14
I 13
O 14

Output:
-
4 6 7 9 14 
14
13 14
*/
#include <cstdio>
#include <iostream.h>
using namespace std; 
class Node
{
public:
        Node *left, *right, *parent;
        int key;
        Node(int key) : left(NULL), right(NULL), key(key)
        { }
};
int inorder(Node *N)
{
    if (N->left!=NULL) inorder(N->left);
    cout << N->key << " ";
    if (N->right!=NULL) inorder(N->right);  
}
int minkey( Node *N)
{
    if (N->left==NULL)
    return N->key;
    else
        minkey(N->left);
}
void insert(Node *N, int key)
{
        if(N->key == key)
                return;
        if(N->key < key)
                if(N->right)
                        insert(N->right, key);
                else
                        N->right = new Node(key);
        else
                if(N->left)
                        insert(N->left, key);
                else
                        N->left = new Node(key);
}
 
Node* search(Node *N, int key)
{
        if(N == NULL)
                return NULL;
        if(N->key == key)
                return N;
        if(N->key < key)
                return search(N->right, key);
        return search(N->left, key);
}
 
int main()
{
        char cmd;
        int key;
        Node *root = NULL, *out;
 
        while(scanf("%c %d\n", &cmd, &key) > 0)
        {
                if(cmd == 'I')
                        if(root)
                                insert(root, key);
                        else
                                root = new Node(key);      
                if(cmd == 'M')
                {
                       out = search(root, key);
                       if(search(root,key)==NULL)
                       cout << "-" << endl;
                       else
                       {
                           cout << minkey(out) << endl;
                       }
                }
                if( cmd == 'O')
                {
                    out = search(root, key);
                    if (search(root, key)==NULL)
                       cout << "-" << endl;
                    else
                    {
                  //      sprytny(out);
                        inorder(out);
                    }
                    
                }
                // tu nale¿y dopisaæ pozosta³e funkcje
        }
        return 0;
}
