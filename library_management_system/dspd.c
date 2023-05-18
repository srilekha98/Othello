#include<stdio.h>
#include <string.h>
#define LEN 50
#define NOFREC 55
struct book_tag
{
    int yop;  //year of publiction
    int noc;   //no.of copies
    char author[LEN];
    char name[LEN];

};

struct pop_author
{
    char aut[LEN];
    int tnoc;  //total no of copies
};
enum statuscode{FAILURE,SUCCESS};

void swap(struct book_tag book[],int p1,int p2) //check if such structure swap works
{
struct book_tag temp;
temp.noc=book[p1].noc;
book[p1].noc=book[p2].noc;
book[p2].noc=temp.noc;

temp.yop=book[p1].yop;
book[p1].yop=book[p2].yop;
book[p2].yop=temp.yop;

strcpy(temp.name,book[p1].name);
strcpy(book[p1].name,book[p2].name);
strcpy(book[p2].name,temp.name);

strcpy(temp.author,book[p1].author);
strcpy(book[p1].author,book[p2].author);
strcpy(book[p2].author,temp.author);
}


void initialise(struct book_tag book[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        book[i].yop=0;
        book[i].noc=0;
        book[i].name[0]='\0';
        book[i].author[0]='\0';
    }
}

int insert(struct book_tag book[],int n,char name[],char author[],int yop,int noc)
{
 int f=1;
 int found=0,fi;  //fi=free index
 int i=0;
 while((i<n) && (found==0))
 {
     if((strcmp(book[i].name,name)==0)&&(strcmp(book[i].author,author))==0)
     {
         found=1;
         book[i].yop=yop;
         book[i].noc=noc;
     }
     else
     {
         i++;
     }
 }
 if(found==0)
 {
    fi=-1;
    i=0;
    while((i<n)&&(fi==-1))
    {
        if(book[i].noc==0)
        {
            fi=i;
        }
        else
        {
            i++;
        }
    }
     if(fi>-1)
     {
         strcpy(book[i].name,name);
         strcpy(book[i].author,author);
         book[i].noc=noc;
         book[i].yop=yop;
     }
     else
     {
         f=0;
     }
 }
 return(f);
}

int del(struct book_tag book[],int n,char name[],char author[])
{
 int f=1;
 int found=0,i=0;
 while((i<n)&& !found)
 {
     if((strcmp(book[i].name,name)==0)&&(strcmp(book[i].author,author)==0))
     {
         found=1;
     }
     else
     {
         i++;
     }
 }
 if(found==0)
 {
    f=0;
 }
 else
 {
        book[i].yop=0;
        book[i].noc=0;
        book[i].name[0]='\0';
        book[i].author[0]='\0';
 }
 return(f);
}

int nofrecs(struct book_tag book[],int n)
{
    int i,ct=0;
    for(i=0;i<n;i++)
    {
        if(book[i].noc!=0)
        {
            ct++;
        }
    }
    return(ct);
}

int isempty(struct book_tag book[],int n)
{
    int i=0,flag=1;
    for(i=0;i<n && flag==1;i++)
    {
        if(book[i].noc!=0)
        {
            flag=0;
        }
    }
    return(flag);
}

int isfull(struct book_tag book[],int n)
{
    int i=0,flag=1;
    for(i=0;i<n && flag==1;i++)
    {
        if(book[i].noc==0)
        {
            flag=0;
        }
    }
    return(flag);
}

void top_author(struct book_tag book[],int n,char name[])
{
    int max=0,pos=-1,i;
    for(i=0;i<n;i++)
    {
        if(strcmp(book[i].name,name)==0)
        {
            if(book[i].noc>max)
            {
                max=book[i].noc;
                pos=i;
            }
        }
    }
    if(pos!=-1)
    {
        printf("max no.of copies for %s book is by the author %s\n",name,book[pos].author);
    }
    else
    {
        printf("no such book found.\n");
    }

}

void kth_pop_book(struct book_tag book[],int n,int k)
{
    n=n-1;
    while((k>1)&&(n>=0))
    {
       if(book[n].noc!=book[n-1].noc)
       {
           k--;
           n--;
       }
       else
       {
           n--;

       }
    }
    printf("kth popular book(s) are\n");
    printf("%s\n",book[n].name);
    while(book[n].noc==book[n-1].noc)
    {
       printf("%s\n",book[n-1].name);
       n--;
    }

}

void ini_list(struct pop_author list[],int n)
{
    int i;
    for(i=0;i<n;i++)
  {
      list[i].aut[0]='\0';
      list[i].tnoc=0;
  }
}

void most_pop_author(struct book_tag book[],struct pop_author list[],int n)
{
  int i,j,k=1;
  strcpy(list[0].aut,book[0].author);
  for(i=0;i<n;i++)
  {
      for(j=0;j<k;j++)
      {
          if(strcmp(book[i].author,list[j].aut)==0)
          {
              list[j].tnoc=list[j].tnoc+book[i].noc;
              j=k+5;
          }
      }
      if(j==k)
      {
         strcpy(list[j].aut,book[i].author);
         list[j].tnoc=book[i].noc;
         k++;
      }
  }
  int max=0,pos=-1;
  for(i=1;i<k;i++)
  {
      if(list[i].tnoc>max)
      {
          max=list[i].tnoc;
          pos=i;
      }
  }
  if(pos!=-1)
  {
      printf("the most popular author is %s with total no.of copies %d\n",list[pos].aut,max);
  }
  else
  {
      printf("Failed to find him/her.");
  }
}

void least_pop_aut(struct book_tag book[],struct pop_author list[],int n,int kt,int p)
{
      int i,j,k=1,flag=1;
  strcpy(list[0].aut,book[0].author);
  for(i=0;i<n;i++)
  {
      flag=1;
      for(j=0;(j<k)&&(flag==1);j++)
      {
          if(strcmp(book[i].author,list[j].aut)==0)
          {
       flag=0;
      }
  }
  if(flag==1)
  {
      strcpy(list[k].aut,book[i].author);
      k++;
  }

}
int ct=0,nb=0;
printf("the least popular authors are:\n");
for(i=0;i<k;i++)
{
    ct=0;
    nb=0;
    for(j=0;j<n;j++)
    {
        if(strcmp(list[i].aut,book[j].author)==0)
        {
            nb++;
            if(book[j].noc<p)
            {
             ct++;
            }
        }
    }
    if(ct>=((kt*nb)/100.0))
    {
        printf("%s\n",list[i].aut);
    }
}
}

    void sort(struct book_tag book[],int n)
    {
        int i,j,flag=1;
        for(i=0;i<n && flag==1;i++)
        {
            flag=0;
            for(j=0;j<n-1-i;j++)
            {
                if(book[j].noc>book[j+1].noc)
                {
                    swap(book,j,j+1);
                    flag=1;
                }
            }
        }

    }

void sortname(struct book_tag u[],int lo,int hi)
    {
        int i,j,flag=1;
        for(i=lo;i<=hi && flag==1;i++)
        {
            flag=0;
            for(j=lo;j<=hi-1-i;j++)
            {
                if(strcmp(u[j].name,u[j+1].name)>0)
                {
                    swap(u,j,j+1);
                    flag=1;
                }
            }
        }

    }

void sort2key(struct book_tag u[],int n)
{
   int i,j,flag=1,lo=0,hi=0;
        for(i=0;i<n && flag==1;i++)
        {
            flag=0;
            for(j=0;j<n-1-i;j++)
            {
                if(strcmp(u[j].author,u[j+1].author)>0)
                {
                    swap(u,j,j+1);
                    flag=1;
                }
            }
        }
        for(i=0;i<n-1;i++)
        {
            while(strcmp(u[i].author,u[i+1].author)==0)
                {
                    hi=i+1;
                    i++;
                }
                sortname(u,lo,hi);
                lo=hi+1;
        }
}

void diff(struct book_tag l1[],int s1,struct book_tag l2[],int s2)
{
    int i,j,flag=0;
    s1--;
    for(i=0;i<s2;i++)
    {
        flag=1;
        for(j=0;(j<s1)&&(flag==1);j++)
        {
            if((strcmp(l2[i].author,l1[j].author)==0)&&(strcmp(l2[i].name,l1[j].name)==0))
            {
               swap(l1,j,s1);
               s1--;
               flag=0;

            }
        }
    }
    s1++;
    sort2key(l1,s1);
    printf("difference of both lists after sorting is\n");
    for(i=0;i<s1;i++)
    {
        printf("%s %s %d %d\n",l1[i].name,l1[i].author,l1[i].yop,l1[i].noc);
    }

}


int main()
{
    int c=0;           //c is choice
    struct book_tag book[NOFREC];
    struct pop_author list[NOFREC];
    int i,ct,f,k,p,kt,s1,s2;

    void initialise(struct book_tag book[],int n);
    int insert(struct book_tag book[],int n,char name[],char author[],int yop,int noc);
    int del(struct book_tag book[],int n,char name[],char author[]);
    int nofrecs(struct book_tag book[],int n);
    int isempty(struct book_tag book[],int n);
    int isfull(struct book_tag book[],int n);
    void top_author(struct book_tag book[],int n,char name[]);
    void kth_pop_book(struct book_tag book[],int n,int k);
    void ini_list(struct pop_author list[],int n);
    void most_pop_author(struct book_tag book[],struct pop_author list[],int n);
    void least_pop_aut(struct book_tag book[],struct pop_author list[],int n,int kt,int p);
    void diff(struct book_tag l1[],int s1,struct book_tag l2[],int s2);

        struct book_tag temp;
        temp.yop=0;
        temp.noc=0;
        temp.name[0]='\0';
        temp.author[0]='\0';

    initialise(book,NOFREC);

    //readong data from file
    FILE* fp;
    fp=fopen("data.txt","r");
    for(i=0;i<NOFREC;i++)
    {
        fscanf(fp,"%s%s%d%d",book[i].name,book[i].author,&book[i].yop,&book[i].noc);
    }
    fclose(fp);

    //int partition(struct book_tag book[],int lo,int hi,int x);
   // void quicksort(struct book_tag book[],int lo, int hi);
    void swap(struct book_tag book[],int p1,int p2);
    void sort(struct book_tag book[],int n);
    void sort2key(struct book_tag u[],int n);
    void sortname(struct book_tag u[],int lo,int hi);

    printf("enter 1-insert or update\n 2-delete\n 3-display no.of records \n 4- check if list is empty \n 5-check if list is full\n 6- to display top most book's author\n 7- to display most popular author\n 8- to display kth popular book\n 9-to display least popular author\n 10-union of 2 lists\n 11-difference of lists\n 12-to exit\n");
    scanf("%d",&c);
    while(c!=12)
    {
        switch(c)
        {
        case 1:
            printf("enter all details of record to be inserted or updated\n");
            scanf("%s%s%d%d",temp.name,temp.author,&temp.yop,&temp.noc);
            f=insert(book,NOFREC,temp.name,temp.author,temp.yop,temp.noc);
            if(f==1)
            {
                printf("list updated.\n");
            }
            else
            {
                printf("failed to update.\n");
            }
            break;
        case 2:
            printf("enter the name of book n author name whose record has to be deleted\n");
            scanf("%s%s",temp.name,temp.author);
            f=del(book,NOFREC,temp.name,temp.author);
            if(f==1)
            {
                printf("entry deleted.\n");
            }
            else
            {
                printf("entry not found.\n");
            }
            break;
        case 3:
            ct=nofrecs(book,NOFREC);
            printf("the no of active records are %d\n",ct);
            break;
        case 4:
            f=isempty(book,NOFREC);
            if(f==1)
            {
                printf("list is empty\n");
            }
            else
            {
                printf("list is not empty\n");
            }
            break;
        case 5:
            f=isfull(book,NOFREC);
            if(f==1)
            {
                printf("list is full\n");
            }
            else
            {
                printf("list is not full\n");
            }
            break;
        case 6:
            printf("enter the name of the book\n");
            scanf("%s",temp.name);
            top_author(book,NOFREC,temp.name);
            break;
        case 7:
            ini_list(list,NOFREC);
            most_pop_author(book,list,NOFREC);
            break;
        case 8:
            printf("enter k to find kth popular books\n");
            scanf("%d",&k);
            sort(book,NOFREC);
          // quicksort(book,0,NOFREC);

         /*   for(i=0;i<NOFREC;i++)
            {
                printf("%d\n",&book[i].noc);
            } */
            kth_pop_book(book,NOFREC,k);
            break;
        case 9:
            printf("enter k and p to find least popular authors.\n");
            scanf("%d%d",&kt,&p);
            ini_list(list,NOFREC);
            least_pop_aut(book,list,NOFREC,kt,p);
            break;
        case 10:
            {
            printf("enter size of frst list\n");
            scanf("%d",&s1);
            printf("enter size of 2nd list\n");
            scanf("%d",&s2);
            struct book_tag u[s1+s2];
            initialise(u,s1+s2);
            printf("enter details-name,author,yop,noc of first list\n");
            for(i=0;i<s1;i++)
            {
               scanf("%s%s%d%d",u[i].name,u[i].author,&u[i].yop,&u[i].noc);
            }
            printf("enter details-name,author,yop,noc of second list\n");
            for(i=0;i<s2;i++)
            {
               scanf("%s%s%d%d",temp.name,temp.author,&temp.yop,&temp.noc);
               insert(u,s1+s2,temp.name,temp.author,temp.yop,temp.noc);
            }
            sort2key(u,s1+s2);
            printf("union of both lists after sorting(first with respect to authors and then with respect to names) is\n");
            for(i=0;i<s1+s2;i++)
            {
                if(u[i].noc!=0)
                {
                 printf("%s %s %d %d\n",u[i].name,u[i].author,u[i].yop,u[i].noc);
                }
            }
            }
            break;
        case 11:
            {
            printf("enter size of frst list\n");
            scanf("%d",&s1);
            printf("enter size of 2nd list\n");
            scanf("%d",&s2);
            struct book_tag l1[s1];
            struct book_tag l2[s2];
            initialise(l1,s1);
            initialise(l2,s2);
            printf("enter details-name,author,yop,noc of first list\n");
            for(i=0;i<s1;i++)
            {
               scanf("%s%s%d%d",l1[i].name,l1[i].author,&l1[i].yop,&l1[i].noc);
            }
            printf("enter details-name,author,yop,noc of second list\n");
            for(i=0;i<s2;i++)
            {
               scanf("%s%s%d%d",l2[i].name,l2[i].author,&l2[i].yop,&l2[i].noc);
            }
            diff(l1,s1,l2,s2);
            }
            break;
        default:
            printf("wrong input.try again");
            break;
        }

        printf("enter 1-insert or update\n 2-delete\n 3-display no.of records \n 4- check if list is empty \n 5-check if list is full\n 6- to display top most book's author\n 7- to display most popular author\n 8- to display kth popular book\n 9-to display least popular author\n10-union of lists\n 11-difference of lists\n 12-to exit\n");
        scanf("%d",&c);
    }
    //updating the text file
    fp=fopen("data.txt","w");
    for(i=0;i<NOFREC;i++)
    {
        fprintf(fp,"%s %s %d %d \n",book[i].name,book[i].author,book[i].yop,book[i].noc);
    }
    fclose(fp);
    return(0);
}
