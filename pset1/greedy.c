#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
int amount = 0;
float change = 0;

do {
    printf("How much change is owed?\n");
    change = round(100*GetFloat());
}
while(change<0);


while (change-25 >=0) {
    change = change-25;
    amount++;
}

while (change-10 >=0) {
    change = change-10;
    amount++;
}

while (change-5 >=0) {
    change = change-5;
    amount++;
}

while (change-1 >=0) {
    change = change-1;
    amount++;
}

printf("%d\n", amount);
}
