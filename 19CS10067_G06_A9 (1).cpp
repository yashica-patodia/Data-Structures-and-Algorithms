/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment
*/

#include<iostream>
#include<stdio.h>
#define MAX_SIZE 100
using namespace std;
typedef struct Job
{
	int jobid;
	int starttime;
	int joblength;
	int remlength;
	
}Job;

typedef struct _heap
{
	Job list[MAX_SIZE];
	int numJobs;
}heap;
bool comp(Job a,Job b)
{
	if(a.remlength<b.remlength)
		return 1;
	else if(a.remlength>b.remlength)
		return 0;
	else
	{
		if(a.jobid<b.jobid)
			return 1;
		return 0;
	}
}
bool comp2(Job a,Job b)
{
	if(a.starttime<b.starttime)
		return 1;
	else if(a.starttime>b.starttime)
		return 0;
	else
	{
		if(a.jobid<b.jobid)
			return 1;
		return 0;
	}
}
//PART 1
void initHeap(heap *H)
{
	H->numJobs=0;

}

void insertJob(heap *H ,Job a)
{
	(H->numJobs)++;
	//cout<<H->numJobs<<"p "<<endl;
	H->list[H->numJobs]=a;
	int n=H->numJobs;
	int par=n/2;
	int ind=n;
	while(par!=0 && comp(H->list[ind],H->list[par]))
	{
		swap(H->list[ind],H->list[par]);
		ind=par;
		par=par/2;
	}
}
void min_heapify(heap *H,int ind)//This fucntion is used to implement the extractMinJob
{
	int mn=ind;
	int left=2*ind;
	int right=2*ind+1;
	int n=H->numJobs;
	if(left<=n && comp(H->list[left],H->list[mn]))
	{
		mn=left;
	}
	if(right<=n && comp(H->list[right],H->list[mn]))
	{
		mn=right;
	}
	if(mn!=ind)
	{
		swap(H->list[mn],H->list[ind]);
		min_heapify(H,mn);
	}
}
int extractMinJob(heap *H,Job *j)
{
	if(H->numJobs==0)
	{
		
		return -1;
	}
	int n=H->numJobs;
	(H->numJobs)--;
	(*j)=H->list[1];
	swap(H->list[1],H->list[n]);
	min_heapify(H,1);
	return 0;
}
void countsort(Job *jb,int lb,int n)
{
	int mx=-1;
	for(int i=1;i<=n;i++)
	{
		if(jb[i].starttime>mx)
			mx=jb[i].starttime;

	}
	Job *ans;
	ans=new Job[n+2];
	int *count;
	count=new int[mx+2];
	for(int i=0;i<=mx;i++)
		count[i]=0;
	for(int i=0;i<n;i++)
		++count[jb[i+1].starttime];
	for(int i=1;i<=mx;i++)
	{
		count[i]+=count[i-1];

	}
	for(int i=n;i>=1;i--)
	{
		ans[count[jb[i].starttime]]=jb[i];
		--count[jb[i].starttime];
	}
	for(int i=1;i<=n;i++)
	{
		jb[i]=ans[i];
		//cout<<jb[i].jobid<<" "<<jb[i].starttime<<endl;
	}
	//cout<<endl;
}
//PART 2
void scheduler(Job *jb,int n)
{
	heap *H;
	H=(heap*)malloc(sizeof(heap));
	initHeap(H);
	countsort(jb,1,n);

	int sysclock =0;
	int cnt=0;
	
	int *indexfind;
	indexfind=new int[n+2];
	//for each job id it tells me at which position it is present in the jb array
	for(int i=1;i<=n;i++)
	{
		indexfind[jb[i].jobid]=i;
	}
	int *firste;
	firste=new int[n+2];
	for(int i=1;i<=n;i++)
		firste[i]=-1;//it stores the arrival time for the job otherwise initilaized at -1

	cout<<"Jobs scheduled at each timestep are:"<<endl;
	int mx=-1;
	int mintime=jb[1].starttime;
	for(int i=0;i<mintime;i++)
		cout<<-1<<" ";

		int i=1;
	while(1)
	{
		while(i<=n && jb[i].starttime==sysclock)//Inserting in the heap if the start time matches with the system clock
		{
			insertJob(H,jb[i]);
			i++;
		}
		
		Job bb;
		int ind;
		//the minimum in the heap will be executed and hence extracting the min job
		
			
			int k=extractMinJob(H,&bb);

			if(k!=-1)//if not empty
			{
				
				cout<<bb.jobid<<" ";//Printing the job id
			
				// }
				ind=indexfind[bb.jobid];//Finding the position at which it occurs in the jb array
				if(firste[ind]==-1)//If not yet started then initializing with the first time
				{
					firste[ind]=sysclock;
					
				}
				jb[ind].remlength--;

			
		
		if(jb[ind].remlength==0)//Ig rem length =0 then increasing the count to mark the finishing of the process
		{
			cnt++;
		}
		else
		{
			insertJob(H,jb[ind]);//Otherwise inserting it again int the heap
		}
	}
	
		sysclock++;//Increasing the time 
		if(cnt==n)
		{	//mx=sysclock-1;	//Loop out condition
			break;
		}	



	}
	
	cout<<endl;
	double sum=0;
	for(int i=1;i<=n;i++ )
	{
		sum+=1.0*(firste[i]-jb[i].starttime);//Calculating the turnaround time

	}
	double ans=sum/n;
	cout<<"Average Turnaround Time is  ";
	cout<<ans<<endl;


}
int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	cout<<"Enter the no of jobs(n): "<<endl;
	int n;
	cin>>n;
	cout<<"Enter the jobs:"<<endl;
	
	Job *jb;
	jb=new Job[n+2];
	for(int i=1;i<=n;i++)
	{
		int aa,b,c;
		cin>>aa>>b>>c;
		Job a;
		a.jobid=aa;
		a.starttime=b;
		a.joblength=c;
		a.remlength=c;
		jb[i]=a;
	}
	//debug Heap
	// heap *H;
	// H=(heap*)malloc(sizeof(heap));
	// initHeap(H);
	// for(int i=1;i<=n;i++)
	// {
	// 	insertJob(H,jb[i]);

	// }
	// for(int i=1;i<=n;i++)
	// {
	// 	Job jj;
	// 	int  k=extractMinJob(H,&jj);
	// 	cout<<H->numJobs<<"yp"<<k<<endl;

	// 	cout<<jj.jobid<<" "<<jj.starttime<<endl;
	// }
	// Job pp;
	// cout<<H->numJobs<<"yp"<<extractMinJob(H,&pp)<<endl;

	scheduler(jb,n);

}	