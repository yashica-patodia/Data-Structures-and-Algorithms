#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef struct node
{
	int data;
	struct node *add;
}node;//declaring structs
int n;
void traverse_from_front_to_end(node *head)
{
	node *fr=head;//initializing first
	node *sec=head->add;//initializingsecond
	cout<<fr->data<<",";//printing
	if(n!=2)
	cout<<sec->data<<" ,";//printing
else
	cout<<sec->data<<" ";
	node *disp=NULL;
	for(int i=0;i<n-2;i++)//run n-2 times
	{
		disp=(node*)(((ll)fr)^((ll)sec->add));//finding the address
		if(i!=n-3)
		cout<<disp->data<<", ";
	else
		cout<<disp->data<<" ";
		fr=sec;//changing 
		sec=disp;
	}
	cout<<endl;
}
void traverse_from_end_to_front(node *head)
{
	node *fr=head;//initializing first
	node *sec=head->add;//initializingsecond
	cout<<fr->data<<",";//printing
	//cout<<sec->data<<" ,";//printing
	if(n!=2)
	cout<<sec->data<<" ,";//printing
else
	cout<<sec->data<<" ";
	node *disp=NULL;
	for(int i=0;i<n-2;i++)//run n-2 times
	{
		disp=(node*)(((ll)fr)^((ll)sec->add));//finding the address
		if(i!=n-3)
		cout<<disp->data<<", ";
	else
		cout<<disp->data<<" ";
		fr=sec;//changing 
		sec=disp;
	}
	cout<<endl;

}
void reverse(node **head, node **tail)
{

	node *temp = *head;//reversing the head and tail will reverse the linked lists
	*head=*tail;
	*tail=temp;
}
void alternate(node **head, node **tail)
{
	

	// //temp2=tail;
	// node *first=*head;
	// node *last=*tail;
	// first->add=last;
	// node *curr=first->add;
	// node *prev=first;
	// node *nx=head->add;
	// int c=1;
	// for(int i=1;i<n-1;i++)
	// {
	// 	curr->add=(node*)(((ll)prev)^((ll)nx));
	// 	prev=curr;
	// 	curr=nx;
	// 	if(c%2==1)
	// 	{
	// 		nx=last->add;

	// 	}



	// }
	node *curr=*head;
	node *last1=*tail;
	node *prev=NULL;
	node *last2=NULL;
	node *temp1=NULL,*temp2=NULL;
	//so basically making the array altrnatively till curr!=last1 and initializing the address accordingly
	while(curr!=last1)
	{
		temp1=(node*)(((ll)curr->add)^((ll)prev));
		temp2=(node*)(((ll)last1->add)^((ll)last2));
		if(temp2==curr)
			break;
		curr->add=(node*)(((ll)prev)^((ll)last1));
		last1->add=(node*)(((ll)curr)^((ll)temp1));
		node *yp=(node*)(((ll)curr)^((ll)temp1->add));
		temp1->add=(node*)(((ll)yp)^((ll)last1));
		yp=(node*)(((ll)last1)^((ll)temp2->add));
		temp2->add=(node*)(((ll)last2)^((ll)yp));
		prev=last1;//re initializing the values
		curr=temp1;
		last1=temp2;
		last2=NULL;
		*tail=temp2;
	}

	

}

// void alternate(node **head, node **tail)
// {

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	
	
	cin>>n;
	 node *head=(node *)malloc(sizeof(node));//dynamic allocation of memory
	 int arr[n];
	 for(int i=0;i<n;i++)
	 	cin>>arr[i];
	 if(n==1)
	 {
	 	cout<<"Doubly linked list traversed from front to end: "<<arr[0]<<endl;
	 	cout<<"Doubly linked list traversed from end to front: "<<arr[0]<<endl;
	 	cout<<"Reversed doubly linked list traversed from front to end: "<<arr[0]<<endl;
	 	cout<<"Alternated doubly linked list traversed from front to end: "<<arr[0]<<endl;
	 	return 0;
	 	
	 }
	 // if(n==1)
	 // {


	 // }

	head->data=arr[0];
	head->add=NULL;

	node *prev=NULL;
	
	node *curr=head;
	node *nx=NULL;
	for(int i=1;i<n;i++)
	{
		int p=arr[i];
		nx=(node*)malloc(sizeof(node));//dynamic allocation of memory
		nx->data=p;
		curr->add=(node*)(((ll)prev)^((ll)nx));//storing the address
		prev=curr;
		curr=nx;

	}
	nx->add=prev;
	node *tail=nx;
	//calling the functions

	cout<<"Doubly linked list traversed from front to end: ";
	traverse_from_front_to_end(head);
	cout<<endl;
	cout<<"Doubly linked list traversed from end to front: ";
	traverse_from_end_to_front(tail);
	cout<<endl;
	reverse(&head,&tail);
	cout<<"Reversed doubly linked list traversed from front to end: ";
	traverse_from_front_to_end(head);
	cout<<endl;
	alternate(&head,&tail);
	cout<<"Alternated doubly linked list traversed from front to end: ";
	traverse_from_front_to_end(head);




}