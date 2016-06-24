#include<stdio.h>
#include<cs50.h>
#include<math.h>
int main(void)
{
    long int y=0,p=0;
    float c;
    printf("Change owed?\n");
    scanf("%f",&c);
    c=c*100;
    y=round(c);
    printf("%ld=Money in cents\n",y);
    printf("\ntest");
    if(y>25)
    {
        y=y%25;
        p=y/25;
        printf("test2");
    }
    else
    {
        printf("test3");
    }
 
    while(y&&y<=24)
    {
        p=(y/10)+p;
        y=y%10;
    }
    while(y&&y<=9)
    {
        p=(y/5)+p;
        y=y%5;
    }
    while(y>=1&&y<5)
    {
        p=(y/1)+p;
    }
    printf("%ld",p);
}
