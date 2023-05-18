#include<math.h>
#include<iostream>
#include<bits/stdc++.h>
#define N 4
using namespace std;

double T = 1;
double Tmin = .0001;
double alpha = 0.9;
int numIterations = 10;

double getscore(int c,int n,int p,int qk, double d[N][N], int *sch)
{
      //suppose p divides n
        double sum=0;
        for(int k=0;k<qk*p;k=k+qk)
        {
            for(int i=k;i<k+qk;i++)
            {
                for(int j=i+1;j<k+qk;j++)
                {
                    if(sch[i] && sch[j])
                    sum=sum+1-d[sch[i]-1][sch[j]-1];
                }
            }
            for(int i=k;i<k+qk;i++)
            {
                for(int j=k+qk;j<p*qk;j++)
                {
                    if(sch[i] && sch[j])
                    sum=sum+c*d[sch[i]-1][sch[j]-1];
                }
            }

        }
    return sum;
}

int main()
{

 cout<<"enter number of papers\n";
 int n;
 cin>>n;
 cout<<"enter number of parallel sessions\n";
 int p, k;
 cin>>p;
 cout<<"enter max number of papers per session\n";
 cin>>k;
 int c;
 cout<<"enter value of constant c\n";
 cin>>c;
 cout<<"enter the matrix of distances\n";

 double d[N][N];
 for(int i=0;i<n;i++)
 {
     for(int j=0;j<n;j++)
     {
         cin>>d[i][j];
     }
 }

int z=0,y=1,x=0,sch[p*k];

for(int e=0;e<n;e++)
{
    sch[e]=e+1;
}
for(int e=n;e<p*k;e++)
{
    sch[e]=0;
}

double currscore;
random_shuffle(&sch[0], &sch[n-1]);

cout<<"schedule is \n";
for(z=0;z<p*k;z++)
{
    cout<<" "<<sch[z]<<endl;
}
currscore= getscore(c,n,p,k,d,sch);

random_shuffle(&sch[0], &sch[p*k-1]);

cout<<"currscore: "<<currscore<<endl;

double newscore = getscore(c,n,p,k,d,sch);
 while (T > Tmin) {

            for (int i=0;i<numIterations;i++){

                if (newscore>currscore){
                   currscore=newscore;
                }
                else
                {
                    double ap = exp( (newscore-currscore)/T);
                    if (ap > (((double) rand() / (INT_MAX)) + 1))
                        currscore=newscore;
                }

                random_shuffle(&sch[0], &sch[p*k-1]);
                newscore = getscore(c,n,p,k,d,sch);

            }

            T *= alpha; // Decreases T, cooling phase
        }

cout<<currscore<< " is new score"<<endl;

cout<<"schedule is \n";
for(z=0;z<p*k;z++)
{

    if(z%k==0)
    {
        cout<<endl;
    }

    cout<<" "<<sch[z];

}

}


