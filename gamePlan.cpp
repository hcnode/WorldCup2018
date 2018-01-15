#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int n = 10;
void bubbleSort(int **a,int n);
int gamePlan(){
	int ** a;
	int temp=0;
	int u=0;
	int counter=0;
	int gKeeper = 0;
	int temp_GK =0;
	int ability=0;
	for(;p!=NULL;)
	{
		//giving p id	
		ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;

		if(temp<ability)
		{
			temp_GK = ability ;
			gKeeper = p->number;
		}
	}
	int b[4]={442,433,352,532};
	int t=0;
	int j=0;
	int n=0;
	int c=0;
	for(c=0;c<4;c++)
	{
		counter=0;
		//n ro az barname migirim
		
	t=b[c];
	
	
	
	a =(int **) calloc(n, sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		a[i] =(int *) calloc(2, sizeof(int));
	}
				//deffending/////////////////////////////////////////////////////////////////////////\
				
			//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
		
		for(int i=0;i<(t/100);i++)
		{
			counter+=a[i][0];
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////// n ra az barname migirim  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		

	a = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++) {
		a[i] = (int *)calloc(2, sizeof(int));
	}
				//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
		for(int i=0;i<((t%100)-(t%10));i++)
		{
			counter+=a[i][0];
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////// n ra az barname migirim  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

	a =(int **) calloc(n, sizeof(int *));	
	for (int i = 0; i < n; i++) {
		a[i] =(int *) calloc(2, sizeof(int));
	}
				//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
		for(int i=0;i<(t%10);i++)
		{
			counter+=a[i][0];
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		////////////////////////////////////////////////////////////////////////////////////////////
		if(temp<counter)
		{
			temp = counter;
			u = c;
		}
	
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	t=b[u];
	a = (int **)calloc(n, sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		a[i] = (int *)calloc(2, sizeof(int));
	}
				//deffending/////////////////////////////////////////////////////////////////////////\
				
			//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
		for(int i=0;i<(t/100);i++)
		{
			counter+=a[i][0];
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////	
	////////////////////////////// n ra az barname migirim  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		

	a =(int **) calloc(n, sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		a[i] =(int *) calloc(2, sizeof(int));
	}
				//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
		for(int i=0;i<((t%100)-(t%10));i++)
		{
			counter+=a[i][0];
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////// n ra az barname migirim  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		

	a = (int **)calloc(n, sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		a[i] = (int*)calloc(2, sizeof(int));
	}
				//p ro az barname migirim		
		for(j = 0;p!=NULL;j++)
		{
			ability = (p->skill) + ((p->fitness)/2) + (((p->form)*3)/10) ;
			a[j][0]=ability;
			a[j][1]=p->number;
				//p ro az barname migirim
		}
		bubbleSort(a,n);
	
}






int main(){
	srand(time(NULL));
	gamePlan();
}

void bubbleSort(int **a,int n)
{
	  int i, j;
int temp;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(a[j][0]<a[j+1][0])
            {
				temp=a[j][0];
				a[j][0]=a[j+1][0];
				a[j+1][0]=temp;
				temp = a[j][1];
				a[j][1]=a[j+1][1];
				a[j+1][1]=temp;
            }
        }
    }
}
