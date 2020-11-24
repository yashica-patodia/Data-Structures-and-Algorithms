/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment
*/

#include<iostream>
#include<string.h>
#include<stdio.h>
#define LEN 10000
using namespace std;
typedef struct pai
{
	int x;
	int y;
}pai;

typedef struct node
{
	int val;
	node *next;
}node;
typedef struct hashing
{
	int key;
	
	struct node *list;
	struct hashing *next;
}hashing;
typedef struct Hashtable
{
	int S;
	hashing **A;
	hashing **B;
}Hashtable;
int findhash(int val,int S)
{
	return (val%S);
}
Hashtable inittable(int S)
{
	Hashtable T;
	T.S=S;
	T.A=(hashing**)malloc(sizeof(hashing *)*S);
	T.B=(hashing**)malloc(sizeof(hashing *)*S);
	for(int i=0;i<S;i++)
	{
		
		T.A[i]=NULL;
		T.B[i]=NULL;
		(T.A[i])->key=-1;
		(T.B[i])->key=-1;
	
	}
	return T;
}
void append(int value, node **head_ptr){
    node *newnode = new node;
    newnode->val = value;
    newnode->next =NULL;
    if(*head_ptr == NULL){
        *head_ptr = newnode;
        return;
    }
    node *it = *head_ptr;
    while(it->next != NULL){
        it=it->next;
    }
    it->next = newnode;
    return;
}
void insertpair(Hashtable H ,int Y,int P)
{
	int val1=findhash(Y,H.S);
	hashing *curr=(H.B[val1]);
	 while(curr->next!=NULL && curr->key != Y){
        curr = curr->next;
    }
    if(curr->key==Y){
        append(P, &(curr->list));
    }
    else{
        curr->next = new hashing;
        curr = curr->next;
        curr->key = Y;
        curr->list = NULL;
        curr->next = NULL;
        append(P, &(curr->list));
    }
    int val2=findhash(P,H.S);
	hashing *cur=(H.A[val2]);
	 while(cur->next!=NULL && cur->key != P){
        cur = cur->next;
    }
    if(cur->key==P){
        append(Y, &(cur->list));
    }
    else{
        cur->next = new hashing;
        cur = cur->next;
        curr->key = P;
        cur->list = NULL;
        cur->next = NULL;
        append(Y, &(cur->list));
    }
   
    return;

}
void removeY(Hashtable H,int Y)
{
	 int key = findhash(Y,S);
    hashf *curr = (H.A[key]).next;
    hashf *prev = curr;
    while(curr!=NULL && curr->key != Y){
        prev = curr;
        curr = curr->next;
    }
    node *temp = curr->list;
    while(temp!=NULL){
        int key1 = findhash(temp->val,S);
        int port_num = temp->value;
        hashf *curr = (H.A[key1]);
        hashf *prev = curr;
        while(curr->key != port_num){
            prev = curr;
            curr = curr->next;
        }

        //delete_element(&(curr->list), counter_party);
         node *it = curr->list;
	    node *prev = it;
	    if(curr->list==NULL){
	        //cout<<"Empty list"<<endl;
	        return;
	    }
	    if(it->val == num){
	        curr->list = it->next;
	        free(it);
	        return;
	    }
	    while(it->value != num){
	        prev = it;
	        it = it->next;
	    }
	    prev->next = it->next;
	    free(it);
        if(curr->list == NULL){
            if(prev==curr){
                H.A[key].next = curr->next;
            }
            else{
                prev->next = curr->next;
            }
            free(curr);
        }
        temp = temp->next;
    }
    if(prev==curr){
        H.A[key].next = curr->next;
    }
    else{
        prev->next = curr->next;
    }
    free(curr);
    return;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int S;
	cin>>S;
	int test;
	cin>>test;
	Hashtable H;
	H=inittable(S);
	for(int i=1;i<=test;i++)
	{
		//cout<<"hi"<<endl;
		char ch;
		cin>>ch;
		if(ch=='+')
		{
			int Y,P;
			cin>>Y>>P;
			insertpair(H,Y,P);
		}
		if(ch=='-')
		{
			int Y;
			cin>>Y;
			H=removeY(H,Y);
		}
	}

	for(int i=0;i<S;i++)
	{
		
		hashing *temp;
		temp=H.B[i];
		
		if(temp==NULL)
		{
			cout<<"p"<<" "<<i<<" ";
			cout<<-1<<" "<<-1<<endl;
			continue;
		}
		int val=temp->key;
		hashing *curr=temp->next;
		while(curr!=NULL)
		{
			cout<<"p"<<" "<<i<<" ";
			cout<<val<<" "<<curr->val<<endl;
			curr=curr->next;
		}
		// 

	}

	for(int i=0;i<S;i++)
	{
		
		hashing *temp;
		temp=H.A[i];
		
		if(temp==NULL)
		{
			cout<<"c"<<" "<<i<<" ";
			out<<-1<<" "<<-1<<endl;
			continue;
		}
		int val=temp->key;
		hashing *curr=temp->next;
		while(curr!=NULL)
		{
			cout<<"c"<<" "<<i<<" ";
			cout<<val<<" "<<curr->val<<endl;
			curr=curr->next;
		}
		
	}


}	
	