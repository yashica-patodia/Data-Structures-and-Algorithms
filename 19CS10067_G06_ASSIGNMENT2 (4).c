#include<stdlib.h>
#include "assign2.h"



int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}
void app(Point *arr, int x,int h,int n){
        
        if(n > 0 && arr[n-1].y == h)
            return;
        if(n > 0 && arr[n-1].x == x){
            int maxh = arr[n-1].y;
            int m=n;
            while(m > 0 && arr[m-1].x == x){
                maxh = max(maxh, h);
                Point *pt=(arr+m-1);
                free( pt);
                m--;
            }
           // arr+m=(Point*)malloc(sizeof(Point));
            arr[m].x=x;
            arr[m].y=maxh;
            m++;
            
            return;
        }
       // arr[0]=(Point*)malloc(sizeof(Point));
            arr[0].x=x;
            arr[0].y=h;
        return;
    }
Point *merge(Point *left, Point *right,int m,int n){
       
        int i = 0 , j = 0,p;
      Point *line;
        int x1,x2, h1 = 0, h2 = 0, maxh = 0;
        while(i < m && j < n){
            if(left[i].x < right[j].x){
                x1 = left[i].x;
                h1 = left[i].y;
                maxh = max(h1,h2);
                 p=sizeof(line)/sizeof(int);
                app(line, x1, maxh,p);
                i++;
            }else if(left[i].x > right[j].x){
                x2 = right[j].x;
                h2 = right[j].y;
                maxh = max(h1,h2);
               // int p=sizeof(line)/size(int);
                app(line, x2, maxh,(m+n)*2);
                j++;
            }else{
                x1 = left[i].x;
                h1 = left[i].y;
                h2 = right[j].y;
                maxh = max(h1,h2);
              //  int p=sizeof(line)/size(int);
                app(line, x1, maxh,(m+n)*2);
                i++;
                j++;
            }
            
        }
        
        while(i < m){
        	int p=(m+n)*2;
            app(line, left[i].x, left[i].y,p);
            i++;
        }
        
        while(j < n){
        	//int p=sizeof(line)/size(int);
            app(line, right[j].x, right[j].y,(m+n)*2);
            j++;
        }
        
        return line;
    }
Point *solve(Box boxes[],int lb,int ub,int size)
{
	 Point *ans;//array defined
	 
	 ans=(Point*)malloc(size*2*sizeof(Point));//dynamically allocate
	 int ind=0;
        if(lb > ub)
            return ans;
        if(lb == ub){
            int x = boxes[lb].left, y = boxes[lb].right, h = boxes[lb].ht;//if equal then assign 
            //ans[ind]=(Point*)malloc(sizeof(Point));
            ans[ind].x=x;
            ans[ind++].y=h;
           // ans[ind]=(Point*)malloc(sizeof(Point));
            ans[ind].x=y;
            ans[ind++].y=0;
           //printf( " (%d, %d), ", ans[ind-1].x, ans[ind-1].y);
           //printf("%d%d",) ans[ind].x<<" "<<ans[ind].y<<endl;
            return ans;
        }
        int m = (lb + ub)/2;
        Point  *left = solve(boxes, lb, m,size);//divid part 
        Point  *right = solve(boxes, m+1, ub,size);
        int l1=sizeof(left)/sizeof(left[0]);
        int r1=sizeof(right)/sizeof(right[0]);
        ans = merge(left,right,l1,r1);//merge part
        return ans;
}
Point *findOutLine(Box boxes[],int size,int outputsize)
{
	Point *point_array;
	//point_array=(Point*)malloc(size)
	point_array= solve(boxes,0,size-1,size);
	return point_array;
}
int main()
{
	// 	#ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	// #endif
	// IOS
	
	// int t;
	// cin>>t;
	// for(int i=1;i<=t;i++)
	// {
	// 	cout<<"Case #"<<i<<": ";
	// 	solve();

	// }
	// Box *boxes;
	// boxes=(Box*)malloc(n*sizeof(Box));
	process();

}	