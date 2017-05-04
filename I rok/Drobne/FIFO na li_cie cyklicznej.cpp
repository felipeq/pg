#include <stdio.h>
 
 
        enum { CMD_LENGTH,
                CMD_PRINT,
                CMD_ERROR
        } ecmd;
 
        struct Elem {
                int key;
                Elem* next;
                Elem(Elem* e, int k) : next(e), key(k) { }
        };
 
        char cmd;
        int n,ilosc,free;
        bool isEmptyQueue;
        Elem *first, *last;
 
 
int parseEnum(char cmd) {
        return cmd == 'L' ? CMD_LENGTH :
                cmd == 'P' ? CMD_PRINT :
                CMD_ERROR;
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
        if(!first || isEmptyQueue) printf("-\n");       
        else {
                Elem *tmp = first;
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
        while(tmp->next != first) { tmp = tmp->next; len++; }
        return len;
}
int main()
{
        isEmptyQueue  = true;
        while(scanf("%c", &cmd) > 0) 
        {
			if (cmd=='D')
			{
				int a;
				scanf("%d",&a);
				if (a<=0) continue;
				for ( int i=0;i<a;i++)
				{
					if (isEmptyQueue == true) { printf("%s","- "); continue; }
					printf("%d",first->key);
					printf("%s"," ");
					if (first->next==last)
					{
						printf("%d",last->key);
						printf("%s"," ");
						a--;
						isEmptyQueue=true;
						first=last=NULL;
						continue;
					}
					first=first->next;
					free++;
				}
				printf("%s","\n");
			}
			if (cmd=='E')
			{
				int a;
				while (scanf("%d", &a))
				{
					Elem *N;
					N=new Elem(NULL,a);
					if (free==0) ilosc++;
					if (free>0) free--;
					if (isEmptyQueue==true)
					{
						first=N;
						N->next=N;
						last=N;
						isEmptyQueue=false;
						continue;
					}
					else
					{
						last->next=N;
						last=N;
						N->next=first;
					}
				}
			}
                switch (parseEnum(cmd))
                {       
                        case CMD_LENGTH:
                                printf("%d\n", ilosc);
                                break;
 
                        case CMD_PRINT:
                                printAll();
                                break;
                        
                        case CMD_ERROR:
                        default:
                                break;
                }
 
        }
        return 0;
}