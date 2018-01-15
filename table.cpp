#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void seed1(int table[4][8], int checkconf[5][8]);

void seed2(int table[4][8], int checkconf[5][8]);

void seed3(int table[4][8], int checkconf[5][8]);

void seed4(int table[4][8], int checkconf[5][8]);


bool isitend(int a[8]);

void coppyarray(int temp[5][8], int checkConf[5][8]);

int conf(int team);

int fill(int table[4][8], int seed[8], int temp);

void printt(int table[][8], int m);


int main() {
    int table[4][8] = {0};
    int checkconf[5][8] = {0};
    seed1(table, checkconf);
    seed2(table, checkconf);
    seed3(table, checkconf);
    seed4(table, checkconf);

}

void seed1(int table[4][8], int checkconf[5][8]) {
    int seed[8] = {1, 3, 4, 11, 12, 22, 23, 24};
    int checkseed[8] = {0};
    int temp[8] = {0};
    for (int i = 0; i < 8;) {
        int a = rand() % 8;
        if (checkseed[a] == 0) {
            checkseed[a] = 1;
            temp[i] = seed[a];
            checkconf[conf(seed[a])][i]++;
            i++;
        }
    }
    fill(table, temp, 0);
    printt(table, 4);
    puts("");
    printt(checkconf, 5);
}

void seed2(int table[4][8], int checkconf[5][8]) {

    int seed[8] = {5, 7, 10, 21, 28, 30, 32, 17};

    bool end = false;
    while (end == false) {
        int checkseed[8] = {0};
        int temp[8] = {0};
        int tempcheckconf[5][8] = {0};
        coppyarray(tempcheckconf, checkconf);
        for (int i = 0; i < 8;) {
            for (i = 0; temp[i] != 0; i++); //avalin jaye khali
            int a = rand() % 8;
            if (checkseed[a] == 0) { //team ghablan entekhab nashode
                checkseed[a] = 1;
                //agar team male orupa bud:
                if (conf(seed[a]) == 2) {
                    while (tempcheckconf[2][i] > 1) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[2][i]++;
                    i = 0;
                } else {
                    while (tempcheckconf[conf(seed[a])][i] > 0) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[conf(seed[a])][i]++;
                    i = 0;
                }
            }
        }
        end = isitend(temp);
        if (end == true) { coppyarray(checkconf, tempcheckconf);
            fill(table,temp,1);
        }
    }
    printt(table, 4);
    puts("");
    printt(checkconf, 5);

}

void seed3(int table[4][8], int checkconf[5][8]) {

    int seed[8] = {6, 8, 9, 13, 14, 26, 29, 31};

    bool end = false;
    while (end == false) {
        int checkseed[8] = {0};
        int temp[8] = {0};
        int tempcheckconf[5][8] = {0};
        coppyarray(tempcheckconf, checkconf);
        for (int i = 0; i < 8;) {
            for (i = 0; temp[i] != 0; i++); //avalin jaye khali
            int a = rand() % 8;
            if (checkseed[a] == 0) { //team ghablan entekhab nashode
                checkseed[a] = 1;
                //agar team male orupa bud:
                if (conf(seed[a]) == 2) {
                    while (tempcheckconf[2][i] > 1) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[2][i]++;
                    i = 0;
                } else {
                    while (tempcheckconf[conf(seed[a])][i] > 0) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[conf(seed[a])][i]++;
                    i = 0;
                }
            }
        }
        end = isitend(temp);
        if (end == true) { coppyarray(checkconf, tempcheckconf);
            fill(table,temp,2);
        }
    }
    printt(table, 4);
    puts("");
    printt(checkconf, 5);

}

void seed4(int table[4][8], int checkconf[5][8]) {

    int seed[8] = {2, 15, 16, 18, 19, 20, 25, 27};

    bool end = false;
    while (end == false) {
        int checkseed[8] = {0};
        int temp[8] = {0};
        int tempcheckconf[5][8] = {0};
        coppyarray(tempcheckconf, checkconf);
        for (int i = 0; i < 8;) {
            for (i = 0; temp[i] != 0; i++); //avalin jaye khali
            int a = rand() % 8;
            if (checkseed[a] == 0) { //team ghablan entekhab nashode
                checkseed[a] = 1;
                //agar team male orupa bud:
                if (conf(seed[a]) == 2) {
                    while (tempcheckconf[2][i] > 1) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[2][i]++;
                    i = 0;
                } else {
                    while (tempcheckconf[conf(seed[a])][i] > 0) {
                        i++;
                    }
                    temp[i] = seed[a];
                    tempcheckconf[conf(seed[a])][i]++;
                    i = 0;
                }
            }
        }
        end = isitend(temp);
        if (end == true) { coppyarray(checkconf, tempcheckconf);
            fill(table,temp,3);
        }
    }
    printt(table, 4);
    puts("");
    printt(checkconf, 5);

}


int fill(int table[4][8], int temp[8], int n) {
    for (int i = 0; i < 8; i++) {
        table[n][i] = temp[i];
    }
}


int conf(int team) {
    int CONCAF0[3] = {6, 17, 20};
    int CONMEBOL1[5] = {1, 4, 5, 21, 32};
    int UEFA2[14] = {3, 7, 8, 10, 11, 12, 13, 22, 23, 24, 27, 28, 29, 30};
    int AFC3[5] = {2, 14, 15, 16, 25};
    int CAF4[5] = {9, 18, 19, 26, 31};

    for (int i = 0; i < 3; i++) {
        if (CONCAF0[i] == team) return 0;
    }

    for (int i = 0; i < 5; i++) {
        if (CONMEBOL1[i] == team) return 1;
    }

    for (int i = 0; i < 14; i++) {
        if (UEFA2[i] == team) return 2;
    }

    for (int i = 0; i < 5; i++) {
        if (AFC3[i] == team) return 3;
    }

    for (int i = 0; i < 5; i++) {
        if (CAF4[i] == team) return 4;
    }

}

void printt(int table[][8], int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", table[i][j]);

        }
        puts("");
    }
}

void coppyarray(int temp[5][8], int checkConf[5][8]) {
    for (int i = 0; i < 5; i++) {
        for (size_t j = 0; j < 8; j++) {
            temp[i][j] = checkConf[i][j];
        }
    }
}

bool isitend(int a[8]) {
    for (int i = 0; i < 8; i++) {
        if (a[i] == 0) return false;
    }
    return true;
}
