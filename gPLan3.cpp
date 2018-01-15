#include<stdio.h>
#include<stdlib.h>
int plan(int t,int gPlan[][15],int orderTeam){
		int i,j;
		int ability=0;
		int gPlan_i = team->number;
		int f=1;
		int stop =0;
		int n=20;
		gPlan[11]= t;
	int **a;
	a = (int **)calloc(n, sizeof(int *));
	
	for (int i = 0; i < n; i++) {
		a[i] = (int *)calloc(2, sizeof(int));
	}
				//deffending/////////////////////////////////////////////////////////////////////////\
				// n deffend ra migirim
		stop=1;
		j=0;
		while(stop)
		{
			p=search_post(pp,"D",order);
		
			if(!p)
			{
				stop=0;
			}
			else
			{
			
			ability=doAbility(p->skill,p->form,p->fitness);
			a[j][0]=ability;
			a[j][1]=p->number;
			j++;
			
			pp = p->next;	
			}
		
		}
		pp=head;
		bubbleSort(a,n);
		
		for(int j = 0;j<(t/100);j++)
		{
		
			gPlan[gPlan_i][f]=a[j][1];
			f++;
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////	
	////////////////////////////// n ra az barname migirim  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
		

		a =(int **) calloc(n, sizeof(int *));
	
		for (int i = 0; i < n; i++) {
			a[i] =(int *) calloc(2, sizeof(int));
		}
				//p ro az barname migirim		
		stop=1;
		j=0;
		while(stop)
		{
			p=search_post(pp,"M",order);
		
			if(!p)
			{
				stop=0;
			}
			else
			{
			
			ability=doAbility(p->skill,p->form,p->fitness);
			a[j][0]=ability;
			a[j][1]=p->number;
			j++;
			
			pp = p->next;	
			}
		
		}
		pp=head;
		bubbleSort(a,n);
		
		for(int i=0;i<((t%100)-(t%10))/10;i++)
		{
			gPlan[gPlan_i][f]=a[i][1];
			f++;
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
		stop=1;
		j=0;
		while(stop)
		{
			p=search_post(pp,"A",order);
		
			if(!p)
			{
				stop=0;
			}
			else
			{
			
			ability=doAbility(p->skill,p->form,p->fitness);
			a[j][0]=ability;
			a[j][1]=p->number;
			j++;
			
			pp = p->next;	
			}
		
		}
		pp=head;
		bubbleSort(a,n);
		
		for(int i=0;i<(t%10);i++)
		{
			gPlan[gPlan_i][f]=a[i][1];
			f++;
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		pt = pteam->next;
	}
int main(){
	
}
