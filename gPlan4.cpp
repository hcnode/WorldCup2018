#include<stdio.h>
#include<stdlib.h>
int updateGamePlan(int ){
int stop=0;
int i,j;
int ability=0;
int gPlan_i=0;

//////////////goalkeeper
gPlan[gPlan_i][12]=0;
gPlan[gPlan_i][13]=0;
	stop=1;
		j=0;
		while(stop)
		{
			p=search_post(pp,"G",order);
		
			if(!p)
			{
				stop=0;
			}
			if(strcmp(p->mainPost,"G")==0)
			{
				ability=doAbility(p->skill,p->form,p->fitness);
				gPlan[gPlan_i][12]+=ability*2;
			}
			else
			{
				if(strcmp(p->mainPost,"D")==0)
				{
					ability=((p->skill)*0.3)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability*2;
				}
					if(strcmp(p->mainPost,"M")==0)
				{
					ability=((p->skill)*0.2)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability*2;
				}
					if(strcmp(p->mainPost,"A")==0)
				{
					ability=((p->skill)*0.2)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability*2;
				}
		
			}
			pp = p->next;	
		}

/////////////////deffend
	stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post(pp,"D",order);
			if(!p)
			{
				stop=0;
			}
				if(strcmp(p->mainPost,"D")==0)
			{
				ability=doAbility(p->skill,p->form,p->fitness);
				gPlan[gPlan_i][12]+=ability;
			}
			else
			{
				if(strcmp(p->mainPost,"G")==0)
				{
					ability=((p->skill)*0.3)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability;
				}
					if(strcmp(p->mainPost,"M")==0)
				{
					ability=((p->skill)*0.7)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability;
				}
					if(strcmp(p->mainPost,"A")==0)
				{
					ability=((p->skill)*0.3)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability;
				}
			
		
			}
				pp = p->next;
		}
		///////////////////Middle
			stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post(pp,"M",order);
			if(!p)
			{
				stop=0;
			}
				if(strcmp(p->mainPost,"M")==0)
			{
				ability=doAbility(p->skill,p->form,p->fitness);
				gPlan[gPlan_i][12]+=ability/2;
				gPlan[gPlan_i][13]+=ability/2;
			}
			else
			{
				if(strcmp(p->mainPost,"G")==0)
				{
					ability=((p->skill)*0.2)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability/2;
					gPlan[gPlan_i][13]+=ability/2;
				}
					if(strcmp(p->mainPost,"D")==0)
				{
					ability=((p->skill)*0.7)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability/2;
					gPlan[gPlan_i][13]+=ability/2;
				}
					if(strcmp(p->mainPost,"A")==0)
				{
					ability=((p->skill)*0.7)+(p->form)+(p->fitness);
					gPlan[gPlan_i][12]+=ability/2;
					gPlan[gPlan_i][13]+=ability/2;
				}
			}
				pp = p->next;
		}
		///////////Atack
			stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post(pp,"A",order);
			if(!p)
			{
				stop=0;
			}
				if(strcmp(p->mainPost,"A")==0)
			{
				ability=doAbility(p->skill,p->form,p->fitness);
				gPlan[gPlan_i][13]+=ability;
			}
			else
			{
				if(strcmp(p->mainPost,"G")==0)
				{
					ability=((p->skill)*0.2)+(p->form)+(p->fitness);
					gPlan[gPlan_i][13]+=ability;
				}
					if(strcmp(p->mainPost,"D")==0)
				{
					ability=((p->skill)*0.3)+(p->form)+(p->fitness);
					gPlan[gPlan_i][13]+=ability;
				}
					if(strcmp(p->mainPost,"M")==0)
				{
					ability=((p->skill)*0.7)+(p->form)+(p->fitness);
					gPlan[gPlan_i][13]+=ability;
				}
			
		
			}
				pp = p->next;
		}


}







int main(){
	
	
	
}
