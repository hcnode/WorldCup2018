#include<stdio.h>

void table(){
	int i=0,j=0;
	int counter=0;
	char teamTable[32][15]={"  Argentina  ","  Australia  ","   Belgium   ","    Brazil   ","   Colombia  ","  Costa Rica ","   Croatia   ","   Denmark   ","    Egypt    ","   England   ","    France   ","   Germany   ","   Iceland   ","     Iran    ","    Japan    ","    Korea    ","    Mexico   ","   Morocco   ","   Nigeria   ","    Panama   ","     Peru    ","    Poland   ","   Portugal  ","    Russia   "," Saudi Arabia ","   Senegal   ","    Serbia   ","    Spain    ","    Sweden   "," Switzerland ","   Tunisia   ","   Uruguay   "};
	// 1st
	for(i=0;i<16;i++)
	{
		for(j=0;j<1;j++)
		{
			printf("---------------\n");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("---------------\n");	
		}
		if(i%2==0){
		printf("              |\n");
		printf("              |\n");
		printf("              |\n");
		}
		else
		{	
		printf("\n");
		printf("\n");
		printf("\n");
		}
		
	}
	
	/////////////2nd
for(i=0;i<16;i++)
	{
		for(j=0;j<1;j++)
		{	
			if(i%4==0||i%4==3)
			{
			printf("---------------\n");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("---------------\n");	
			}
			else
			{
			printf("---------------              |\n");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|              |\n");
			printf("---------------              |\n");	
			}
		}
		if(i%2==0){
		printf("              |");
			printf("---------------\n");
			printf("              |");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("              |");
			printf("---------------\n");	
	
		}
		else
		{
		if(counter%2==0)
		{
		printf("                             |\n");
		printf("                             |\n");
		printf("                             |\n");
		}
		else
		{
		printf("\n");
		printf("\n");
		printf("\n");
		}
		counter++;
		}		
}
////////3rd
for(i=0;i<16;i++)
	{
		for(j=0;j<1;j++)
		{	
			if(i%4==0||i%4==3)
			{
			printf("---------------\n");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("---------------\n");	
			}
			else
			{
			printf("---------------              |\n");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|              |\n");
			printf("---------------              |\n");	
			}
		}
		if(i%2==0){
		printf("              |");
			printf("---------------\n");
			printf("              |");
			printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("              |");
			printf("---------------\n");	
	
		}
		else
		{
		if(i%4==1)
		{
			if(counter%2==0)
			{
			printf("                             |");
				printf("---------------\n");
			printf("                             |");
				printf("|");
			printf("%s",teamTable[i]);
			printf("|\n");
			printf("                             |");
			printf("---------------\n");	
			}
			else
			{
			printf("\n");
			printf("\n");
			printf("\n");
			}
			counter++;	
			
		}
		else
		{
			if(counter%2==0)
			{
			printf("                             |\n");
			printf("                             |\n");
			printf("                             |\n");
			}
			else
			{
			printf("\n");
			printf("\n");
			printf("\n");
			}
			counter++;
		}
		}		
}


}



int main(){
	table();
}
