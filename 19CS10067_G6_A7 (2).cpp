/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment
*/

#include<iostream>
#include<string.h>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#define LEN 10000
using namespace std;
typedef unsigned int ui;
typedef struct _node
{
	int rank;
	struct _node *parent;

}node;


node **makeset(int m,int n)
{
	node **C;
	C=new node*[m];
	for(int i=0;i<m;i++)
		C[i]=new node[n];
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			
			C[i][j].rank=0;
			C[i][j].parent=&(C[i][j]);
		}
	}
	return C;



}
node *findset(node *temp,int i,int j)
{

	if(temp->parent==temp)
		return (temp->parent);
	else
		return (temp->parent=findset(temp->parent,i,j));
}
void mergeset(node *x,node *y,int x1,int y1,int x2,int y2)
{
	node *p1=findset(x,x1,y1);
	node *p2=findset(y,x2,y2);
	if(p1==p2)
		return;
	if(p1->rank==p2->rank)
	{
		p2->parent=p1;
		(p1->rank)++;
	}
	else if(p1->rank>p2->rank)
	{
		p2->parent=p1;
	}
	else
	{
		p1->parent=p2;
	}

}
void findtreasure(node **C,int **H,int **V,int m,int n)
{
	srand(time(0));
	int cnt=1;
	while(cnt<m*n)
	{
		if(rand()%2==0)//Breaking horizontal wall
		{
			int xx=rand()%(m-1);
			int yy=rand()%(n);
			if(H[xx][yy]==0)//not allowed
				continue;
			if(findset(&C[xx][yy],xx,yy)==findset(&C[xx+1][yy],xx+1,yy))//as already in the same set
				continue;
			cnt++;
			mergeset(&C[xx][yy],&C[xx+1][yy],xx,yy,xx+1,yy);
			H[xx][yy]=0;


		}
		else//breaking vertical wall
		{
			int xx=rand()%(m);
			int yy=rand()%(n-1);
			if(V[xx][yy]==0)//not allowed 
				continue;
			if(findset(&C[xx][yy],xx,yy)==findset(&C[xx][yy+1],xx,yy+1))//as already in the same set
				continue;
			cnt++;
			mergeset(&C[xx][yy],&C[xx][yy+1],xx,yy,xx,yy+1);
			V[xx][yy]=0;
		}
			


	}


}
void printgrid(node **C, int **H,int **V,int m,int n)
{
	// cout<<"+   ";
	// for(int i=0;i<n;i++)
	// {
	// 	if(i==n-1)
	// 		cout<<"+";
	// 	else
	// 		cout<<"+---";
	// }
	// cout<<endl;
	// for(int i=0;i<m-1;i++)
	// {
	// 	cout<<"|   ";
	// 	for(int j=0;j<n;j++)
	// 	{
			
			
	// 			if(j==n-1)
	// 				cout<<"| ";
	// 			else
	// 				cout<<"|   ";

			
	// 	}
	// 	cout<<endl;
	// 	cout<<"+---";
	// 	for(int j=0;j<n;j++)
	// 	{
	// 		if(j==n-1)
	// 			cout<<"+";
	// 		else
	// 			cout<<"+---";
	// 	}
	// 	cout<<endl;

	// }
	// for(int i=0;i<n;i++)
	// 	cout<<"|   ";
	// cout<<endl;
	// cout<<"+---";
	// for(int i=0;i<n;i++)
	// {
	// 	if(i!=n-1)
	// 		cout<<"+---";
	// 	else
	// 		cout<<"+";
	// }
	// cout<<endl;

	cout<<"+   ";
	for(int i=0;i<n;i++)
	{
		if(i==n-1)
			cout<<"+";
		else
			cout<<"+---";
	}
	cout<<endl;
	for(int i=0;i<m;i++)
	{
		cout<<"|   ";
		for(int j=0;j<=n-2;j++)
		{

			if(V[i][j]==1)
				cout<<"|   ";
			else
				cout<<"    ";
		}
		if(i!=m-1)
		cout<<"|"<<endl;
	else
		cout<<endl;
		if(i!=m-1)
		{
			//cout<<"+";
			for(int j=0;j<n;j++)
			{
				cout<<"+";
				if(H[i][j]==1)
					cout<<"---";
				else
					cout<<"   ";
			}
			cout<<"+"<<endl;

		}
	}
	cout<<"+";
	for(int j=0;j<n;j++)
		cout<<"---+";
	cout<<endl;




}
int main(int argc,char *argv[])
 {
// 	freopen("input.txt","r",stdin);
// 	freopen("output.txt","w",stdout);

	 int n,m;
	if(argc<=2)
	{
		n=10;
		m=10;
	}
	else
	{
		m=atoi(argv[1]);
		n=atoi(argv[2]);
	}	
	cout<<m<<" "<<n<<endl;
	
	// int nn,mm;
	// while(cin>>mm)
	// {
	// 	m=mm;
	// 	cin>>nn;
	// 	n=nn;
	// }
	//Part 1
	node **C;
	C=makeset(m,n);
	int **H;//Storing an integer array which is 1 if it can be removed and 0 if not allowed to remove
	H=new int*[m-1];
	for(int i=0;i<m-1;i++)
		H[i]=new int[n];
	for(int i=0;i<m-1;i++)
	{
		for(int j=0;j<n;j++)
		{
			H[i][j]=1;//initially all are 1 (Allowed)
		}
	}
	int **V;//Storing an integer array which is 1 if it can be removed and 0 if not allowed to remove
	V=new int*[m];
	for(int i=0;i<m;i++)
		V[i]=new int[n-1];
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			V[i][j]=1;//initially all are 1 (Allowed)
		}
	}


	//Printing graph
	cout<<"Initial Grid"<<endl;
	cout<<endl;
	printgrid(C,H,V,m,n);

	//Part 2
	findtreasure(C,H,V,m,n);
	node *n1=findset(&C[0][0],0,0);
	node *n2=findset(&C[m-1][n-1],m-1,n-1);
	if(n1==n2)
		cout<<"They are in the same set"<<endl;
	else
		cout<<"They are not in the same set"<<endl;
	cout<<endl;
	//Part 3
	cout<<"Final Grid"<<endl;
	cout<<endl;
	printgrid(C,H,V,m,n);



	








}	