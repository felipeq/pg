#include <stdio.h>
#include <iostream.h>
using namespace std;
 
        enum { CMD_LENGTH, CMD_PRINT, CMD_ERROR } ecmd;
 
        struct Elem {
                int key;
                Elem* next;
                                Elem* prev;
                Elem(Elem* e, int k) : next(e), prev(e), key(k) { }
        };
 
        char cmd;
        int n;
        bool isEmptyStack;
        Elem *first, *last;
 
 
int parseEnum(char cmd) {
                 return cmd == 'L' ? CMD_LENGTH :
                cmd == 'P' ? CMD_PRINT :
                CMD_ERROR;
}
void Dodaj(int key)
{
    Elem *temp;
	temp=new Elem(NULL,key);
	if (!first) {first=temp;last=temp; return;}
	else
	{
		last->next=temp;
		temp->prev=last;
		last=temp;
	}
}
Elem *search(int key)
{
        if(!first) return NULL;
        Elem *tmp = first;
        while(tmp->key != key && tmp != last) tmp = tmp->next;
        if (tmp->key == key) return tmp;
        else return NULL;
}
 
 
 
void printAll() {
        if(!first || isEmptyStack) printf("-\n");       
        else {
                Elem *tmp = first;
                if (first==last) { cout << tmp->key<< endl; return; }
                while(tmp != last) {
                        printf("%d->", tmp->key);
                        tmp = tmp->next;
                }
                printf("%d\n", last->key);
        }
}
 
int totalLength()
{
        if(!first) return 0;
        int len(1);
        Elem *tmp = first;
    	if (first==last) return 1;
        while(tmp->next != last) { tmp = tmp->next; len++; }
        return len+1;
}
 
int main()
{
        isEmptyStack  = true;
        while(scanf("%c", &cmd) > 0) {
			
                switch (parseEnum(cmd))
                {                       
 
                case CMD_LENGTH:
                                        printf("%d\n", totalLength());
                                        break;
 
                case CMD_PRINT:
                                        printAll();
                                        break;
                        
                case CMD_ERROR:
                                
                                        break;
                }
 			if (cmd=='U')
 			{
				int k;
				cin >> k;
				isEmptyStack=false;
				Dodaj(k);
			}
        }
        return 0;
}
