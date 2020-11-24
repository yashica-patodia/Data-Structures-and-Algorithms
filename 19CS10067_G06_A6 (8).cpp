/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Lab Assignment 6
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>


double max(double a,double b)//this returns the maximum of two double values
{
	if(a>b)
		return a;
	return b;
}
/*This function runs a greedy approach with a given gap length L and specific order of
//arrangements of the visited people stored in array a[]
//This returns true if the specific length is possible otherwise it returns false
//The first person in the order is made to visit at that specific  ai(arrival) value (greedily) and
//then subsequent people are made to visit greedily
*/
bool schedule_visits(double arr[][2],double gap,int a[],int l,int r,int n)
{
	///here a[] stores the permutation (ordering of the visits to the grocery shop)
	double vis=arr[a[0]][0];//the first person visits
	for(int i=1;i<n;i++)
	{
		double exp=vis+gap;
		if(exp<=arr[a[i]][1])
		{
			vis=max(arr[a[i]][0],exp);//of the greedy allotment of the subsequent member is less than the b(i) value
			//then continuing otherwise returning false
		}
		else
			return false;//returning false if greedy allotment is more than the b(i) value

	}
	if(vis-arr[a[n-1]][1]<=1e-1)//if b(i) of n-1 is less than the greedy allotment then returning true otherwisr false
		return true;
	return false;
}
/*This function generates all the possible ordering of visiting of people and then uses binary search to find the
maximum gap for that particular arragement.We can use binary search here because the function is monotonic and if a possible
gap G is possible then a gap<G is also possible, so there is Y Y Y Y N N N kind of construct and we need to find the last possible Y*/
 void permute(double arr[][2],int a[],int l,int r,int n,double *res,int final[])
 {
 	
 	if(l==r)//Base case
 	{
 		
 		double lb=0,ub=86400;//max one day is possible
 		double ans=-1,mm;
 		while(abs(lb-ub)>=1e-2)//using binary search 
 		{
 			mm=lb+(ub-lb)/2;//prospective gap on which the greedy will be applied
 			if(schedule_visits(arr,mm,a,0,n-1,n))//checking if true then lower limit becomes mm
 			{
 				lb=mm;
 				ans=mm;
 			}
 			else
 				ub=mm;//if false the upper limit becomes mm
 		}
 		if(*res<ans)//if ans is more than the maximum till now then storing its value and finding the arrangents
 		{
 			*res=ans;
 			for(int i=0;i<n;i++)//Storing the order of visit
 				final[i]=a[i];
 		}
 		(*res)=max((*res),ans);

 		//cout<<endl;
 		return ;
 	}
 	for(int i=l;i<=r;i++)
 	{

 		int temp=a[l];
 		a[l]=a[i];
 		a[i]=temp;//swapping the a[i],a[l] values
 		permute(arr,a,l+1,r,n,res,final);//recursively calling again
 		int temp2=a[l];//backtracking and undo the before changes
 		a[l]=a[i];
 		a[i]=temp2;

 	}
 }
int main()
{
	
	FILE *fp;
	fp=fopen("input1.txt","r");

	int n;//The number of visitors
	fscanf(fp,"%d",&n);
	double arr[n+1][2];//2-d array for storing beginning and end time intervals

	for(int i=0;i<n;i++)
	{
		int x,y;
		fscanf(fp,"%d%d",&x,&y);
		//in>>arr[i][0]>>arr[i][1];
		arr[i][0]=x*60;//converting it to seconds
		arr[i][1]=y*60;//converting it to seconds

	}
	//As the number n<=8 we can do permutaion of all the possible arrangements of people as 8!=40320 <=10^6
	int per[n];
	for(int i=0;i<n;i++)
	{
		per[i]=i;//identity permutation
	}
	fclose(fp);

	FILE *fo;
	fo=fopen("output1.txt","w");
	double res;//Storing the ans in res
	res=-1;
	int final[n];//Stores the final ordering 
	permute(arr,per,0,n-1,n,&res,final);
    double ans=(int)(res+.1);//Rounding off to nearest seconds
	int min=(int)(ans/60);//Finding the number of minutes
	int sec=(int)ans%60;//Finding the number of seconds
	
	fprintf(fo,"%d:%0.2d\n",min,sec);
	for(int i=0;i<n;i++)
		fprintf(fo,"%d ",final[i] );
		
	fprintf(fo, "\n" );
	fclose(fo);


}	