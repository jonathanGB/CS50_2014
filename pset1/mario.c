#include <stdio.h>
#include <cs50.h>

int main(void) {
    int n = 0;
    int h = 2;
    
    do {
        printf("Pick the height of the pyramid: \n");
        n = GetInt();
    }
    while (n<0 || n>23);
    
       int s = n-1;
   
   
    for (int i = 0 ; i<n ; i++) {
        
         for (int j = s; j>0 ; j--) {
                printf(" ");
         }
           
         for (int k = h; k>0 ; k--) {
                printf("#");
         }
           
           printf("\n");
           s--;
           h++;
    }
   
}
