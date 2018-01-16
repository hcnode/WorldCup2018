#include<stdio.h>
#include<string.h>
void table2(int n){
	
		int i=0,j=0;
	int counter=0;
	int x=0,y=0;
	char teamTable[32][15]={"  Argentina  ","  Australia  ","   Belgium   ","    Brazil   ","   Colombia  ","  Costa Rica ","   Croatia   ","   Denmark   ","    Egypt    ","   England   ","    France   ","   Germany   ","   Iceland   ","     Iran    ","    Japan    ","    Korea    ","    Mexico   ","   Morocco   ","   Nigeria   ","    Panama   ","     Peru    ","    Poland   ","   Portugal  ","    Russia   "," Saudi Arabia ","   Senegal   ","    Serbia   ","    Spain    ","    Sweden   "," Switzerland ","   Tunisia   ","   Uruguay   "};
	
	char teamBoard[32][5][15];
	for(i = 0;i<45;i++){
		for(j=0;j<5;j++){
			strcpy(teamBoard[i][j],"0");
		}
	}
	for(j=0;j<n;j++)
	{
		if(j==0)
		{
			for(i=0;i<32;i+=2)
			{
				strcpy(teamBoard[i][j],teamTable[(14)-1]);					
			}
		}
		if(j==1)
		{
			for(i=1;i<32;i+=4)
			{
				strcpy(teamBoard[i][j],teamTable[(14)-1]);					
			}
		}
		if(j==3)
		{
			for(i=4;i<32;i+=7)
			{
				strcpy(teamBoard[i][j],teamTable[(14)-1]);					
			}
		}
		if(j==4)
		{
			for(i=8;i<32;i+=15)
			{
				strcpy(teamBoard[i][j],teamTable[(14)-1]);					
			}
		}
	}
	for(i =0;i<32;i++)
	{
	//	printf("\n");
		for(j=0;j<5;j++)
		{
			
			if(strcmp(teamBoard[i][j],"0")!=0)
			{
			printf("|");
			printf("%s",teamBoard[i][j]);
			printf("|");
			}
			if(strcmp(teamBoard[i][j],"0")==0)
			{
			printf("               ");
			}
		}
		printf("\n");	
	}	
}


int main(){
	table2(2);
}
