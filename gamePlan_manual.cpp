#include<stdio.h>
void gamePlan2(){
	int a[4]={442,433,352,532};
	int i , j;
	
	printf("\nchoose one of these game plan");
	printf("\n1.442\n2.433\n3.352\n4.532\n");
	scanf("%d",&i);
	int t = a[i-1];
	printf("\nwhich one do you want to do?");
	printf("\n1.manual player choosing");
	printf("\n2.automatic player choosing by their ability\n");
	scanf("%d",&j);
	if(j==2)
	{
	////////////gamePlan1	
	}
	if(j==1)
	{
		//show();   int tabe gadval players va zamin bazi ro be user neshan midahad  
		int num1 , num2 ;
		for(int c=1;c-2;)
		{	
			printf("\n set player's numebr to change thair position\n");
			scanf("%d%d",&num1,&num2);
			//show();
			printf("\nDo you have more changes?(1.yes/2.no)\n");
			scanf("%d",&c);
		}
	}
	
	
}




int main(){
	
gamePlan2();	
}
