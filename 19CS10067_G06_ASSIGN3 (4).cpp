/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment-3
*/
/*KINDLY USE THIS STATEMENT IN THE COMMAND PROMPT BECAUSE OF STACK ISSUES FOR LARGE INPUTS THE CODE GIVES SEG-FAULT AND USING THE GIVEN 
BELOW STATEMENT WILL INCREASE THE STACK SIZE AND ALLOW THE LARGE INPUT LIKE THE FIRST TEST CASE
g++ -O2 -std=c++11 -Wall -Wl,--stack=268435456 a.cpp -o a.exe */
/* HERE a.cpp is the name of the input file */

#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
typedef struct POINT
{
	int x,y;
	POINT *next;

	
}POINT;
typedef struct 
{
	POINT *Arr;
	int queue_size;
	int start_id;
	int end_id;
	
}QUEUE;
typedef struct STACK
{
	 POINT *head;
	 STACK *next;
	
}STACK;
//int mat[210][210];
//int vis[210][210];
void init(QUEUE **qp,int size)
{
	(*qp)=(QUEUE*)malloc(sizeof(QUEUE));
	(*qp)->Arr=(POINT*)malloc(40000*sizeof(POINT));
	(*qp)->queue_size=size;
	(*qp)->start_id=0;
	(*qp)->end_id=0;

	
}
// typedef struct {
// POINT *Arr ;
// int queue_size, start_id, end_id;
// } QUEUE ;
int isempty(QUEUE *qp)
{
	if(qp->queue_size==0)
		return 1;
	return 0;
}
void enqueue(QUEUE *qp,POINT p)
{
	// POINT temp;
	// //temp=(POINT*)malloc(sizeof(POINT));
	// temp.x=p.x;
	// temp.y=p.y;

	if(qp->queue_size==0)
	{
		//cout<<p.x<<" "<<p.y<<endl;
		qp->Arr[qp->end_id]=p;

		(qp->queue_size)++;
		(qp->end_id)++;
	}
	else
	{
		qp->Arr[qp->end_id]=p;
		(qp->queue_size)++;
		(qp->end_id)++;
	}

}
POINT dequeue(QUEUE *qp)
{
	if(isempty(qp))
	{
		POINT p;
		p.x=-1;
		p.y=-1;
		return p; 
	}
	else
	{
		// POINT temp=qp->Arr[qp->start_id];
		// (qp->start_id)++;
		POINT temp=qp->Arr[qp->start_id];
		for(int i=0;i<qp->end_id;i++)
			qp->Arr[i]=qp->Arr[i+1];
		(qp->end_id)--;
		 (qp->queue_size)--;


		return temp;
	}
}
void init(STACK **s)
{
	(*s)=(STACK *)malloc(sizeof(STACK));
	// POINT p;
	// p.x=-1;
	// p.y=-1;
	(*s)->head=NULL;
	(*s)->next=NULL;
}
int isempty(STACK *s)
{
	if(s->head==NULL)
		return 1;
	return 0;
}
void push(STACK *s,POINT p)
{
	POINT *temp;
	temp=(POINT*)malloc(sizeof(POINT));
	temp->x=p.x;
	temp->y=p.y;
	//cout<<p.x<<" "<<p.y<<endl;
	temp->next=s->head;
	s->head=temp;
}
POINT pop(STACK *s)
{
	POINT *temp;
	temp=s->head;
	int x=temp->x;
	int y=temp->y;
	s->head=s->head->next;
	delete (temp);
	POINT p;
	p.x=x;
	p.y=y;
	//cout<<"pop"<<p.x<<" "<<p.y<<endl;
	return p;
}
bool check(int x,int y,int n,int m,int mat[210][210])
{
	if(x>=0 && x<n && y>=0 && y<m )
	{
		if(mat[x][y]==1)
		return true;
	else
		return false;
	}
	return false;
}
void printgrid(int mat[210][210],int n,int m)
{
	for(int i=0;i<n;i++)//no of rows

	{
		for(int j=0;j<m;j++)//no of cols
		{
			if(mat[i][j]==0)
				cout<<"-";
			else
				cout<<"*";
		}
		cout<<endl;
	}
}
int strategy1(int mat[210][210],int n,int m,int jx,int jy,int fx,int fy)
{
	//If the distance of the destination is more that INT32_MAX this means that there
	//is no path from source to destination so storing the distances
	int dis[n][m];
	int vis[n][m];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
		dis[i][j]=INT32_MAX;//initializing with the maximum value
		vis[i][j]=0;//initializing all to 0/false--->not visited
		}
	}
	QUEUE *q;
	init(&q,0);
	// cout<<isempty(q);
	// cout<<q->queue_size<<endl;
	// POINT yp;
	// yp.x=6;
	// yp.y=7;
	// enqueue(q,yp);
	// cout<<q->queue_size<<endl;
	// POINT p=dequeue(q);
	// //cout<<
	// cout<<p.x<<" "<<p.y<<endl;
	// cout<<q->queue_size<<endl;
	// return 0;
	int dx[4]={-1,0,1,0};//storing he direction vectors to find the neighbours
	int dy[4]={0,1,0,-1};
	POINT src;
	src.x=jx;
	src.y=jy;
	enqueue(q,src);//pushing the source into the queue
	dis[jx][jy]=0;//marking its distance to be 0

	while(!isempty(q))//looping till the queue is empty
	{

		POINT nn=dequeue(q);
		////cout<<nn<<"pop"<<endl;
		//cout<<nn.x<<" "<<nn.y<<"point"<<endl;
		if(nn.x==-1 && nn.y==-1)
			break;
		if(vis[nn.x][nn.y])
			continue;
		vis[nn.x][nn.y]=true;//marking it as visited
		for(int i=0;i<4;i++)
		{
			int xx=nn.x+dx[i];
			int yy=nn.y+dy[i];
			if(check(xx,yy,n,m,mat))//checking if it lies in the range of the grid and it not an unstable point
			{
				if(dis[xx][yy]>dis[nn.x][nn.y]+1)
				{
					dis[xx][yy]=dis[nn.x][nn.y]+1;//finding the minimum distance using bfs
					POINT yp;
					yp.x=xx;
					yp.y=yy;
					enqueue(q,yp);//pushing the element in the queue

				}
			}
		}

	}
	// for(int i=0;i<n;i++)
	// {
	// 	for(int j=0;j<m;j++)
	// 		cout<<dis[i][j]<<" "<<vis[i][j]<<endl;
	// }
	if(dis[fx][fy]<INT32_MAX && vis[fx][fy])
	{
		cout<<"Path Exists"<<endl;//if the minimum distance is less than the max distance inititlazed earlier and the point is visited then a path is possible
		return 1;
	}
	else
	{
		cout<<"Path Does Not  Exists"<<endl;
		return 0;

	}


}
void prpath(STACK *st,int jx,int jy,int fx,int fy)
{
	STACK *st2;
	init(&st2);
	int cap=0;
	while(!isempty(st))
	{
		POINT p=pop(st);//As thwe points are stored from destination to source in the stack st I am using another stack to reverse the sequence
		push(st2,p);
		cap++;
		

	}
	//cout<<"("<<jx<<","<<jy<<")"<<",";//printing in the required format
	for(int i=0;i<cap-1;i++)
	{
		POINT p=pop(st2);
		cout<<"("<<p.x<<","<<p.y<<")"<<", ";


	}
	
	cout<<"("<<fx<<","<<fy<<")"<<endl;//printing for the last point

}
void dfs(int mat[210][210],int n,int m,int jx,int jy,int fx,int fy,STACK *st,POINT p,int vis[210][210],int dx[],int dy[])
{
	push(st,p);
	if(p.x==fx && p.y==fy)//if the destination is reached then printing the path
	{
		prpath(st,jx,jy,fx,fy);
		return ;
	}
	vis[p.x][p.y]=1;//marking it as vivisted 
	
	for(int i=0;i<4;i++)//Finding all the possible neighbours
	{
			int xx=p.x+dx[i];
			int yy=p.y+dy[i];
			POINT temp;
			temp.x=xx;
			temp.y=yy;
			if(check(xx,yy,n,m,mat))//checking if the point is within the array
			{
				if(!vis[xx][yy])
					dfs(mat,n,m,jx,jy,fx,fy,st,temp,vis,dx,dy);//running the dfs again
			}	

	}
	POINT yp=pop(st);//poping the point



}
void strategy2(int mat[210][210],int n,int m,int jx,int jy,int fx,int fy)
{
	STACK *st;
	init(&st);
	// cout<<isempty(st);
	// POINT p;
	// p.x=5;
	// p.y=8;
	// push(st,p);
	// POINT yp=pop(st);
	// cout<<yp.x<<" "<<yp.y<<endl;
	int vis[210][210];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			vis[i][j]=false;//Intializing all the points to be unvisited
		}
	}
	POINT p;
	p.x=jx;
	p.y=jy;
	int dx[4]={-1,0,1,0};//Initializing the direction vectors
	int dy[4]={0,1,0,-1};
	dfs(mat,n,m,jx,jy,fx,fy,st,p,vis, dx, dy);
	

}
int main()
{
	 //freopen("input.txt","r",stdin);
	 //freopen("output.txt","w",stdout);
	int n,m,ust;
	cin>>n>>m>>ust;//Accepting the input 
	int mat[210][210];
	//0 unstable
	//1 stable
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			mat[i][j]=1;
	}
	int xc[ust+1],yc[ust+1];
	for(int i=0;i<ust;i++)
	{
		cin>>xc[i];

	}
	for(int i=0;i<ust;i++)
	{
		cin>>yc[i];

	}
	for(int i=0;i<ust;i++)
	{
		mat[xc[i]][yc[i]]=0;
	}
	int jx,jy,fx,fy;
	cin>>jx>>jy>>fx>>fy;
	cout<<"Grid of stones is:"<<endl;
	printgrid(mat,n,m);//Part 1
	int ans1=strategy1(mat,n,m,jx,jy,fx,fy);//Part 2 and 3
	//cout<<ans1<<" jk"<<endl;
	if(ans1) //If a path exists then printing the path
	strategy2(mat,n,m,jx,jy,fx,fy);//Implementing the Part 4 and 5

	

}	