/*
Input

Na wejœcie programu podana zostanie pewna iloœæ poleceñ. Ka¿de z poleceñ sk³ada siê ze znaku i liczby rozdzielonych spacj¹. Istniej¹ dwa typy poleceñ: I n oraz M n. Poszczególne komendy zostan¹ rozdzielone znakiem nowej linii.

Output

Na wyjœciu maj¹ siê pojawiæ rezultaty wczytywanych z wejœcia poleceñ:
I n - wstaw n do drzewa lub nie rób nic, jeœli ten wyraz ju¿ jest w drzewie; nic nie drukuj; (ju¿ zrobione)
M n - wypisz minimalny klucz w poddrzewie ukorzenionym w n lub "-" jeœli wierzcho³ek nie istnieje

Example

Input:
I 9
I 14
I 6
I 4
I 7
M 5
M 9
M 14
I 13
M 14

Output:
-
4
14
13
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
                // tu nale¿y dopisaæ pozosta³e funkcje
        }
        return 0;
}
