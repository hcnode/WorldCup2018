#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void drawing(int table[4][8], int checkConf[5][8]);
bool checkend(int table[4][8], int i);
bool checkdrawing(int table[4][8]);

void printt(int table[][8], int m);
void coppyarray(int temp[5][8], int checkConf[5][8] );
int main() {

    int table[4][8] = {0};
    int checkConf[5][8] = {0};
    srand((unsigned) (time(NULL)));
    drawing(table, checkConf);


}
bool checkend(int table[4][8], int satr){
  for(int = 0 ;i<8;i++){
    if(table[satr][i]==0) return false;
  }

  else return true;

}
void printt(int table[][8], int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", table[i][j]);

        }
        puts("");
    }
}
void coppyarray(int temp[5][8], int checkConf[5][8] ){
  for(int i = 0 ;i<5 ;i++){
    for (size_t j = 0; j < 8; j++) {
      temp[i][j]=checkConf[i][j];
    }
  }



}
bool checkdrawing(int table[4][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void drawing(int table[4][8], int checkConf[5][8]) {
    int conf(int team);
    int tempConf[5][8];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            table[4][8] = 0;
        }
    }
    int checkSeed[8] = {0};
    int seed1[8] = {1, 3, 4, 11, 12, 22, 23, 24};
    int seed2[8] = {5, 7, 10, 21, 28, 30, 32, 17};
    int seed3[8] = {6, 8, 9, 13, 14, 26, 29, 31};
    int seed4[8] = {2, 15, 16, 18, 19, 20, 25, 27};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            checkConf[i][j] = 0;
        }
    }


    //step1:
    for (int i = 0; i < 8;) {
        int a = rand() % 8;
        if (checkSeed[a] == 0) {
            checkSeed[a] = 1;
            table[0][i] = seed1[a];
            checkConf[conf(seed1[a])][i]++;
            puts("");
            printt(table , 4);
            puts("");
            printt(checkConf,5);
            puts("");
            i++;
        }
    }


    //step2:
    bool end = false;
    while(end==false){
    coppyarray(tempConf,checkConf);

    for (int i = 0; i < 8; i++) {
        checkSeed[i] = 0;
    }
    //starting step 2
    for (int i = 0; i < 8;) {
        for (i = 0; table[1][i] != 0; i++); //avalin jaye khali
        int a = rand() % 8;
        if (checkSeed[a] == 0) { //team ghablan entekhab nashode
            checkSeed[a] = 1;
            //agar team male orupa bud:
            if (conf(seed2[a]) == 2) {
                while (checkConf[2][i] > 1) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[1][i] = seed2[a];
                checkConf[2][i]++;
                puts("");
                printt(table, 4);
                puts("");
                printt(checkConf, 5);
                puts("");
                i = 0;
            }
                //agar team orupa nabud:
            else {
                while (checkConf[conf(seed2[a])][i] > 0) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[1][i] = seed2[a];
                checkConf[conf(seed2[a])][i]++;
                puts("");
                printt(table, 4);
                puts("");
                printt(checkConf, 5);
                puts("");
                i = 0 ;
            }
        }


    }
    end = checkend(table,1);
  }

    //payan step 2
    for (int i = 0; i < 8; i++) {
        checkSeed[i] = 0;
    }
/*
    //step3

    for (int i = 0; i < 8;) {
        for (i = 0; table[2][i] != 0; i++); //avalin jaye khali
        int a = rand() % 8;
        if (checkSeed[a] == 0) { //team ghablan entekhab nashode
            checkSeed[a] = 1;
            //agar team male orupa bud:
            if (conf(seed3[a]) == 2) {
                while (checkConf[2][i] > 1) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[2][i] = seed3[a];
                checkConf[2][i]++;
            }
                //agar team orupa nabud:
            else {
                while (checkConf[conf(seed3[a])][i] > 0) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[2][i] = seed3[a];
                checkConf[conf(seed3[a])][i]++;
            }
        }

    }
    for (int i = 0; i < 8; i++) {
        checkSeed[i] = 0;
    }

    //step4
    for (int i = 0; i < 8;) {
        for (i = 0; table[3][i] != 0; i++); //avalin jaye khali
        int a = rand() % 8;
        if (checkSeed[a] == 0) { //team ghablan entekhab nashode
            checkSeed[a] = 1;
            //agar team male orupa bud:
            if (conf(seed4[a]) == 2) {
                while (checkConf[2][i] > 1) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[3][i] = seed4[a];
                checkConf[2][i]++;
            }
                //agar team orupa nabud:
            else {
                while (checkConf[conf(seed4[a])][i] > 0) {//agar mojaz be orupa budan nabood
                    i++;
                }//alan mojaz be entekhab ast
                table[3][i] = seed4[a];
                checkConf[conf(seed4[a])][i]++;
            }
        }

    }
    for (int i = 0; i < 8; i++) {
        checkSeed[i] = 0;
    }

*/
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
