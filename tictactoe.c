#include<stdio.h>
#include<stdlib.h>

#define SIZE 5
typedef struct tttnodetag
{
    int rn,cn;
    char val;
    struct tttnodetag *next,*down;
} node;

typedef struct rowdatatag
{
    int rn;
    node* rowlist;
    struct rowdatatag *down;
} rowdata;

typedef struct coldatatag
{
    int cn;
    node* collist;
    struct coldatatag *next;
} coldata;

void createtable(rowdata* r,coldata* c)
{
    int i=0;
    for(i=1;i<SIZE;i++)
    {
        rowdata *r1=(rowdata*)malloc(sizeof(rowdata));
        r1->rn=i;
        r->down=r1;
        //printf("%d\n",r->rn);
        r=r->down;
    }
    r->down=NULL;
    for(i=1;i<SIZE;i++)
    {
        coldata *c1=(coldata*)malloc(sizeof(coldata));
        c1->cn=i;
        c->next=c1;
       // printf("%d\n",c->cn);
        c=c->next;
    }
    c->next=NULL;
}

void createentries(rowdata *r,coldata* c)
{
    rowdata* r1=r;
    coldata* c1=c;
    node * t,*prev=NULL;
    int rn=0,i;
    while(r!=NULL)
    {
        prev=NULL;
        for(i=SIZE-1;i>=0;i--)
        {

            t=(node *)malloc(sizeof(node));
            t->rn=rn;
            t->cn=i;
            t->next=prev;
            t->down=NULL;
            prev=t;
           // printf("rn:%d,cn:%d\n",t->rn,t->cn);
        }
        r->rowlist=t;
        r=r->down;
        rn++;
    }
    r=r1;
    c=c1;
    t=r->rowlist;
        while(c!=NULL)
        {
            c->collist=t;
            t=t->next;
            c=c->next;
           // printf("collist n=%d\n",c->cn);
        }
        prev=r->rowlist;
        r=r->down;
        t=r->rowlist;
        while(r!=NULL)
        {
           // printf("rn=%d\n",prev->rn);
            while(prev!=NULL)
            {
              //  printf("entered second while\n");
                prev->down=t;
                prev=prev->next;
                t=t->next;
            }
            prev=r->rowlist;
            r=r->down;
            if(r!=NULL)
            {
                t=r->rowlist;
            }
        }
}

void initialise(rowdata *r,coldata* c)
{
    node * t;
   while(r!=NULL)
   {
       t=r->rowlist;
       while(t!=NULL)
       {
           //printf("rn=%d cn=%d\n",t->rn,t->cn);
          t->val='-';
           t=t->next;
       }
      // printf("\n");
       r=r->down;
   }
}

int update(rowdata *r,coldata* c,int rown,int coln,char x)
{
    int retval=1;
    while(r->rn!=rown)
    {
        r=r->down;
    }
    node*t=r->rowlist;
    while(c->cn!=coln)
    {
        t=t->next;
        c=c->next;
    }
    if(t->val!='-')
    {
       retval=0;
       printf("invalid move\n Enter again\n");
    }
    else
    {
    t->val=x;
    }
    return(retval);
}

int chkrow(rowdata *r,coldata* c,int rown)
{
    while(r->rn!=rown)
    {
        r=r->down;
    }
    node *t=r->rowlist;
    char s=t->val;
    int f=1;
    t=t->next;
    while((t!=NULL)&&(f==1))
    {
        //printf("%c\n",t->val);
        if(t->val!=s)
        {
            f=0;
        }
        t=t->next;
    }
    return(f);
}

int chkcol(rowdata *r,coldata* c,int coln)
{
    while(c->cn!=coln)
    {
        c=c->next;
    }
    node *t=c->collist;
    char s=t->val;
    int f=1;
    t=t->down;
    while((t!=NULL)&&(f==1))
    {
        if(t->val!=s)
        {
            f=0;
        }
        t=t->down;
    }
    return(f);
}

int chkd1(rowdata *r,coldata* c)
{
    node * t=r->rowlist;
    char s=t->val;
    int f=1;
    t=t->next;
    t=t->down;
    while((t!=NULL)&&(f==1))
    {
       if(t->val!=s)
        {
            f=0;
        }
        t=t->next;
        if(t!=NULL)
        {
          t=t->down;
        }
    }
    return(f);
}

int chkd2(rowdata *r,coldata* c)
{
     node * t=r->rowlist;
     char a[SIZE];
     int f=1;
     int k=0;
   while(r!=NULL)
   {
       t=r->rowlist;
       while(t!=NULL)
       {
           if((t->rn)+(t->cn)==SIZE-1)
           {
              a[k]=t->val;
              k++;
           }
           t=t->next;
       }

       r=r->down;
   }
   int i=0;
   for(i=0;i<k;i++)
   {
       if(a[0]!=a[i])
       {
           f=0;
       }
   }
   return(f);
}

int continuegame(rowdata *r,coldata* c,int rown,int coln)
{
    int p=0,retval;
    p=chkrow(r,c,rown);   //return 1 if row is full
   // printf("r\n");
    if(p==0)
    {
        p=chkcol(r,c,coln);
        //printf("c\n");
        if(p==0)
        {
            if(rown==coln)
            {
               p=chkd1(r,c);
              // printf("d1\n");
            }
            if(rown+coln==SIZE-1)
             {
                p=chkd2(r,c);
               // printf("d2\n");
             }
        }
    }
    if(p==0)
    {
        retval=1;   //continues
    }
    else
    {
        retval=0;    //game ends
    }
    return(retval);

}

void printgamerw(rowdata *r,coldata* c)
{
   node * t;
   while(r!=NULL)
   {
       t=r->rowlist;
       while(t!=NULL)
       {
           //printf("rn=%d cn=%d\n",t->rn,t->cn);
           printf("%c  ",t->val);
           t=t->next;
       }
       printf("\n");
       r=r->down;
   }
}

void printgamecw(rowdata *r,coldata* c)
{
    node * t;
   while(c!=NULL)
   {
       t=c->collist;
       while(t!=NULL)
       {
           printf("rn=%d cn=%d\n",t->rn,t->cn);
           t=t->down;
       }
       c=c->next;
   }
}

int main()
{
    rowdata* r=(rowdata *)malloc(sizeof(rowdata));
    coldata* c=(coldata *)malloc(sizeof(coldata));
    r->rn=0;
    c->cn=0;
void createtable(rowdata* r,coldata* c);
void createentries(rowdata *r,coldata* c);
void initialise(rowdata *r,coldata* c);
void printgamerw(rowdata *r,coldata* c);
void printgamecw(rowdata *r,coldata* c);
int update(rowdata *r,coldata* c,int rown,int coln,char x);


int continuegame(rowdata *r,coldata* c,int rown,int coln);
    int chkrow(rowdata *r,coldata* c,int rown);
    int chkcol(rowdata *r,coldata* c,int coln);
    int chkd1(rowdata *r,coldata* c);
    int chkd2(rowdata *r,coldata* c);

createtable(r,c);
createentries(r,c);
initialise(r,c);
//printgamerw(r,c);
//printgamecw(r,c);

printf("player 1 plays with 'x'\n");
printf("player 2 plays with 'o'\n");
int i=1,p=1,f=0;
int rown,coln;
while((i<SIZE*SIZE)&&(p==1))
{
    f=1;
    printgamerw(r,c);
    if(i%2==1)
    {
        printf("player 1\n");
        printf("enter row number, col number of the 'x' you want to place\n");
        scanf("%d%d",&rown,&coln);
        f=update(r,c,rown,coln,'x');
    }
    else
    {
        printf("player 2\n");
        printf("enter row number, col number of the 'o' you want to place\n");
        scanf("%d%d",&rown,&coln);
        f=update(r,c,rown,coln,'o');
    }
    if(f==0)
    {
        i--;
    }
    if(i>4)
    {
    p=continuegame(r,c,rown,coln);
    }   //p=1 continue .p=0.someone wins
    if(p==0)
    {
        printgamerw(r,c);
       if(i%2==1)
       {
           printf("player 1 wins\n");
       }
       else
       {
           printf("player 2 wins\n");
       }
    }

    i++;

}
if(i==SIZE*SIZE)
{
    printf("draw game");
}
return(0);
}
