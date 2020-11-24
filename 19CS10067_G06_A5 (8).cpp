/* Name-Yashica Patodia
 * Roll No-19CS10067
 * Group-G6
 * Assignment 5 
*/

/* Defination of subproblem used:
	SUBPROBLEM
	-----------
 I have defined dp(i,j) as the maximum probability of the success of the reaction with i reactions and j units of catalysts 
 

 1)When the number of catalysts is zero   , it is given e(i,0)=0 so dp(i,0)=0 1<=i<=N
 2)When the number of reactions is more than the units of catalysts then dp(i,j)=0 ,i>j, 1<=i<=N 
 3)When the number of reactions is 0 then the probabilistic success rate is 1 dp(0,j)=0 0<=j<=C
 4)When the number of reaction is 1  then dp(1,j)=e(1,j) 1<=j<=C, because if there is only one reaction then all the components
  must be assigned to it as it is given that the e(i,j) values is non-decreasing .

 Hence the Base Cases
       ----------------
	 1) dp(0,0)=1 
     2) dp(i,0)=0 for 1<=i<=N
     3) dp(0,j)=1 for 1<=j<=C
     4) dp(1,j)=e(1,j)  1<=j<=C
     5) dp(i,j)=0 for i>j , 1<=i<=N ,1<=j<=C
       
	  

Recursive Defination
-------------------
dp(i,j) ={1<=k<=j max{dp(i-1,j-k)*e(i,k)}}	2<=i<=N ,i<=j<=C
dp(i,j)=1 if(i==0)
dp(i,j)=0 if(j==0 && j<i)


ANSWER
-------
dp(N,C)
For storing the number of components assigned to each reaction I am using a backdp[i][j] which stores the number of catalyst assigned when there are i
 reactions and j catalysts for maximum probabilistic success


*/
#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;
int main()
{
	int N,C;//N -Number of reactions C-Units of catalyst

	 ifstream in;//Reading files through files API Handling in c++
	 in.open("input.txt");
	 in>>N>>C;
	 double **e;
	 int  **backdp;
	 double **dp;
	 e=(double**)malloc((N+1)*sizeof(double));
	 backdp=(int**)malloc((N+1)*sizeof(int));
	 dp=(double**)malloc((N+1)*sizeof(double));

		for(int i=0;i<=N;i++)
		{
			e[i]=(double*)malloc((C+1)*sizeof(double));
			backdp[i]=(int*)malloc((C+1)*sizeof(int));
			dp[i]=(double*)malloc((C+1)*sizeof(double));
		}
		for(int i=0;i<=N;i++)
		{
			backdp[i][0]=0;//When the number of catalysts is 0 then for the ith reaction people assigned 0
			e[i][0]=0;
		}
		for(int i=0;i<=C;i++)
		{
			backdp[0][i]=0;// When the number of reaction is 0 then for the i  catalyst units people assigned 0
			e[0][i]=0;
		}
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=C;j++)
			{
				in>>e[i][j];
				backdp[i][j]=0;
			}
		}
		
		
		//Using bottom -up approach
		//Finding ans for smaller subproblems and then going to dp[n,k] ,hence going from bottom to top
		//Time complexity of the code is N*C*C

		dp[0][0]=1;//Base case 1
		for(int i=0;i<=C;i++)//Base case 2
			dp[0][i]=1;
		for(int i=0;i<=N;i++)//Base case 3
			dp[i][0]=0;
		for(int i=1;i<=C;i++)//Base Case 4
		{
			dp[1][i]=e[1][i];
			backdp[1][i]=i;//When there is a single reaction then the i catalyst should all be assigned to it becuase we have to use at least one catalyst for all reaction
		}
		for(int i=2;i<=N;i++)
		{
			for(int j=1;j<=C;j++)
			{
				if(i>j)
				{
					dp[i][j]=0;//Base Case 5
					backdp[i][j]=0;
					continue;
				}
				if(i==j)//when the number of reaction is equal to the number of catalyst unit then each reaction must be assigned a single catalyst
				{
					dp[i][j]=dp[i-1][j-1]*e[i][1];
					backdp[i][j]=1;
					continue;
				}
				double mm=0;
				
				for(int k=1;k<j;k++)
				{
					if(dp[i-1][j-k]*e[i][k]>mm)
					{

						mm=dp[i-1][j-k]*e[i][k];
						backdp[i][j]=k;
						

					}



				}
				dp[i][j]=mm;

			}
		}

		in.close();
		ofstream out;//Creating output.txt file and printing the output there
		out.open("output.txt");
		out<<"The maximum success probability : ";
		//out<<fixed<<setprecision(6)<<dp[N][C]<<endl;
		out<<dp[N][C]<<endl;

		// Finding the number of units of catalyst assigned to a particular reaction 

		int tot=C;
		int *cat;
		cat=(int*)malloc((N+1)*sizeof(int));
		for(int i=N;i>=1;i--)
		{
			cat[i]=backdp[i][tot];
			tot-=cat[i];
		}
		for(int i=1;i<=N;i++)
		{
			out<<"reaction "<<i<<" :  "<<cat[i]<<endl;
		}
		out<<endl;
		out.close();





	
}
