#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
int goalNumber(double attackPower1, double defencePower2);

int main() {
    srand(time(NULL));
    for (int i=0;i<100;i++)
    printf("%d\n" , goalNumber(6000,3000));
}

int goalNumber(double attackPower1, double defencePower2) {
    int m = (int) round(attackPower1 / defencePower2);
    int goals[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double odds[11] = {0};
    double baze[11] = {0};
    int i = 0;
    for (i = 0; goals[i] != m; i++);
    odds[i] = 1000;
    for (int j = i + 1; j < 11; j++) {
        odds[j] = odds[j - 1] * (0.2);
    }
    for (int j = i - 1; j >= 0; j--) {
        odds[j] = odds[j + 1] * (0.3);
    }

    double sum;
    baze[0] = odds[0];

    for (int i = 1; i < 11; i++) {
        baze[i] = baze[i - 1] + odds[i];
    }
    sum = baze[10];

    int a = rand()%(int)(round(sum + 1)) ;
    int j = 0;
    for(j=0 ; a>baze[j] ;j++);
    return goals[j];
}