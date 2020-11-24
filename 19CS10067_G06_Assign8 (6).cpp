/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment
*/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<climits>
#define LEN 10000
typedef long long int lli;
using namespace std;



typedef struct STACK
{
    int head;
    struct STACK *next;
}STACK;
void init(STACK *s)
{
	 int   	p=-1;
    s->head = p;
    s->next = NULL;
}
int isempty(STACK s)
{
    return (s.head== -1 );
}
void push(STACK *s, int p)
{
   
    STACK *temp;
    temp=(STACK*)malloc(sizeof(STACK));
    temp->head = s->head;
    temp->next = s->next;
    s->head = p;
    s->next = temp;
}
int pop(STACK *s)
{
    int ret = s->head;
    (*s) = (*(s->next));
    return ret;
}


lli prpath(STACK st,int n,int fx,int fy)
{
	STACK st2;
	init(&st2);
	int cap=0;
	//cout<<"ho"<<endl;
	
	while(!isempty(st))
	{
		
		int p=pop(&st);//As thwe points are stored from destination to source in the stack st I am using another stack to reverse the sequence
		push(&st2,p);
		cap++;
		

	}
	//cout<<"("<<jx<<","<<jy<<")"<<",";//printing in the required format
	for(int i=0;i<cap-1;i++)
	{
		int p=pop(&st2);
		cout<<"("<<p/n<<","<<p%n<<")"<<", ";


	}
	
	cout<<"("<<fx<<","<<fy<<")"<<endl;//printing for the last point
	return cap;

}
bool coor(int x,int y,int n)
{
	if(x>=0 && x<n && y>=0  && y<n)
		return true;
	return false;
}
void dfs2(int **arr,int **vis,STACK s,int n,int x,int y,int fx,int fy,bool *ret,int dx[4],int dy[4],int *f )
{
	int pnt=x*n+y;
	//cout<<isempty(s)<<"  hi"<<x<<" "<<y<<endl;
	push(&s,pnt);
	if(x==fx && y==fy &&(*f)==0)
	{
		(*f)=1;
		
		(*ret)= true;
		lli cap=prpath(s,n,fx,fy);
		cout<<"The Number of Blocks traversed are:"<<cap<<endl;
		//exit(0);
		return;

	}
	vis[x][y]=1;

	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(coor(xx,yy,n) && vis[xx][yy]==0  && arr[xx][yy]<=arr[x][y])
		{
			//cout<<"ji  "<<xx<<" "<<yy<<endl;
			dfs2(arr,vis,s,n,xx,yy,fx,fy,ret,dx,dy,f);
		}

	}
	int yp;
	
	 yp=pop(&s);
	
	//cout<<yp/n<<" "<<yp%n<<"sad"<<endl;

}

void dfs(int **arr,int **vis,STACK s,int n,int x,int y,int fx,int fy,bool *ret,int dx[4],int dy[4],lli tm )
{
	int pnt=x*n+y;
	//cout<<isempty(s)<<"  hi"<<x<<" "<<y<<endl;
	push(&s,pnt);
	if(x==fx && y==fy)
	{
		(*ret)= true;
		//exit(0);
		return;

	}
	vis[x][y]=1;

	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(coor(xx,yy,n) && vis[xx][yy]==0  && arr[xx][yy]<=arr[x][y] && arr[x][y]<=tm)
		{
			//cout<<"ji  "<<xx<<" "<<yy<<endl;
			dfs(arr,vis,s,n,xx,yy,fx,fy,ret,dx,dy,tm);
		}

	}
	int yp;
	
	 yp=pop(&s);
	
	//cout<<yp/n<<" "<<yp%n<<"sad"<<endl;

}

bool check(int tm,int **a,int n,int sx,int sy,int fx,int fy)
{
	int **b;
	b=new int *[n];
	for(int i=0;i<n;i++)
		b[i]=new int[n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=0;
		}


	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=max(a[i][j],tm);
		}
	}
	int **vis;
	vis=new int *[n];
	for(int i=0;i<n;i++)
		vis[i]=new int[n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			vis[i][j]=0;
	}
	STACK s;
	init(&s);
	bool ret;
	ret=false;
	int dx[4]={-1,0,1,0};
	int dy[4]={0,1,0,-1};
	dfs(b,vis,s,n,sx,sy,fx,fy,&ret,dx,dy,tm);
	for(int i=0;i<n;i++)
	{
		free(b[i]);
		free(vis[i]);
	}
	free(b);
	free(vis);
	if(ret==true)
		return true;
	else
		return false;


}

void findMin(lli **arr,int **vis,int *x,int *y,int n)
{
	int i,j;
	lli mx=INT_MAX;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(vis[i][j]==0 && arr[i][j]<mx)
			{
				mx=arr[i][j];
				(*x)=i;
				(*y)=j;
			}
		}
	}
}
void leastTimeDijkstra(int **a,int n,int sx,int sy,int fx,int fy)
{
	
	lli **tme;
	tme=new lli *[n];
	for(int i=0;i<n;i++)
		tme[i]=new lli[n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			tme[i][j]=1e15;
		}
	}
	int **vis;
	vis=new int *[n];
	for(int i=0;i<n;i++)
		vis[i]=new int[n];



	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			vis[i][j]=0;
	}
	int **par;
	par=new int *[n];
	for(int i=0;i<n;i++)
		par[i]=new int[n];

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			par[i][j]=-1;
	}

	tme[sx][sy]=a[sx][sy];
	lli p=a[sx][sy];
	int dx[4]={-1,0,1,0};
	int dy[4]={0,1,0,-1};
	
	for(int i=0;i<n*n-1;i++)
	{
		int x,y;
		findMin(tme,vis,&x,&y,n);
		vis[x][y]=1;
		p=a[x][y];
		for(int j=0;j<4;j++)
		{
			int xx=x+dx[j];
			int yy=y+dy[j];
			if(coor(xx,yy,n) && vis[xx][yy]==0 && max(p,1ll*a[xx][yy])<tme[xx][yy])
			{
				tme[xx][yy]=max(p,1ll*a[xx][yy]);
				a[xx][yy]=tme[xx][yy];
			}
		}
	}
	cout<<"Minimum time take is using leastTimeDijkstra "<<a[fx][fy]<<endl;





}

int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	int **a;
	a=new int *[n];
	for(int i=0;i<n;i++)
		a[i]=new int[n];
	lli mx=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];
			mx=max(mx,1ll*a[i][j]);
		}


	}
	int sx,sy,fx,fy;
	cin>>sx>>sy>>fx>>fy;
	lli lb=a[sx][sy],ub=mx+1,ans,mm;
	while(lb<=ub)
	{
		mm=lb+(ub-lb)/2;
		if(check(mm,a,n,sx,sy,fx,fy))
		{
			ub=mm-1;
			ans=mm;

		}
		else
			lb=mm+1;
	}
	cout<<"Minimum time taken is  "<<ans<<endl;
	cout<<"The path to reach from ("<<sx<<","<<sy<<") to ("<<fx<<","<<fy<<") is  " ;
	int **b;
	b=new int *[n];
	for(int i=0;i<n;i++)
		b[i]=new int[n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=0;
		}


	}
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			b[i][j]=max(1ll*a[i][j],1ll*ans);
			
		}
		
	}
	int **vis;
	vis=new int *[n];
	for(int i=0;i<n;i++)
		vis[i]=new int[n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			vis[i][j]=0;
	}
	STACK s;
	init(&s);
	bool ret;
	ret=false;
	int dx[4]={-1,0,1,0};
	int dy[4]={0,1,0,-1};
int f=0;
	dfs2(b,vis,s,n,sx,sy,fx,fy,&ret,dx,dy,&f);

	//Bonus Question in the other code
	leastTimeDijkstra(a,n,sx,sy,fx,fy);

	
	


}	