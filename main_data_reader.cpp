#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
char teamNames[480]={};
typedef struct players{
	int number;
	char name[20];
	int age;
	char nation[20];
	char mainPost[1];
	char tempPost[1];
	int skill;
	int form;
	int fitness;
	int goals;
	int passGoals;
	int yellowCard;
	int redCard;
	
	struct players *next;
}player_node;
typedef struct teams{
	char teamName[15];
	char group[1];
	int state;
	char confed[15];
	int seed;
	int pointOfteam;
	int goalsRecev;
	int goalsScoerds;
	struct teams *next;
}teams_node;
void teamsReadInfofromGlobal(FILE *t,teams_node *p);
player_node * playersReadInfo(FILE *t,player_node *p,const char * teamNamee);
int gamePlan(player_node * head);
void printList(player_node *head);
void doSkills(teams_node * head_team,player_node * head_player)
{
	teams_node *team = head_team;
	player_node * player = head_player;
	player_node * headPlayer=(player_node *)calloc(1,sizeof(player_node));
	headPlayer=head_player;
	int a=1;
	while(a)
	{
		if(team)
		{
			while (player != NULL) {
			if (strcmp(player->nation,team->teamName)==0)
			{
				if(team->seed==1)
				{	
					int t=rand()%5+1;
					if(t ==1||t ==2)
					player->skill= rand()%21 +80;
						if(t ==3||t ==4)
					player->skill= rand()%21 +60;
						if(t ==5)
					player->skill= rand()%21 +40;
						if(0)
					player->skill= rand()%21 +20;
				}
				if(team->seed==2)
				{
					int t=rand()%5+1;
					if(t ==1)
					player->skill= rand()%21 +80;
						if(t ==3||t ==2)
					player->skill= rand()%21 +60;
						if(t ==5||t ==4)
					player->skill= rand()%21 +40;
						if(0)
					player->skill= rand()%21 +20;
				}
				if(team->seed==3)
				{
					int t=rand()%5+1;
					if(t ==1)
					player->skill= rand()%21 +80;
						if(t ==2)
					player->skill= rand()%21 +60;
						if(t ==5||t ==4)
					player->skill= rand()%21 +40;
						if(t == 3)
					player->skill= rand()%21 +20;
				}
				if(team->seed==4)
				{
					int t=rand()%5+1;
					if(0)
					player->skill= rand()%21 +80;
						if(t ==1)
					player->skill= rand()%21 +60;
						if(t ==5||t==4)
					player->skill= rand()%21 +40;
						if(t == 3||t==2)
					player->skill= rand()%21 +20;
				}
				player->fitness=100;
				player->form=80;
				player = player->next;
			}
			else
			{
				team = team->next;
			}
			
		
		
		}
	
	
		team = team->next;
		}
		else
		{
			a=0;
		}
		
	}
	printList(headPlayer);
}
player_node *search_teamName(player_node *head,const char* teamName)
{
	player_node *p = head;
	while (p != NULL) {
		if (strcmp(p->nation,teamName)==0)
		{
			printf("%s",p->name);
			return p;
		}
			
		p = p->next;
	}
	return NULL;
}
player_node *search_post(player_node *head,const char* post,const char* teamName)
{
	player_node *p = head;
	while (p != NULL) {
		if (strcmp(p->mainPost,post)==0)
		{
			if(strcmp(p->nation,teamName)==0)
			return p;
		}
			
		p = p->next;
	}
	return NULL;
}
void printList(player_node *head) 
{
	player_node *p = head;
	for (int i=0;;i++) {
		if(p != NULL) {	
			printf("\n %s -- %d ", p->name,p->skill);
			p = p->next;
		} else {
			break;
		}
	}
	puts("");
}
char* append(const char* name,const char* extension)
{
	char* name_with_extension;
	name_with_extension =(char *) malloc(strlen(name)+1+4); /* make space for the new string (should check the return value ...) */
	strcpy(name_with_extension, name); /* copy name into the new var */
	strcat(name_with_extension, extension);
	return name_with_extension;
}
void bubbleSort(int **a,int n);
int doAbility(int skill,int form, int fitness);
int doAbility(int skill,int form, int fitness)
{
	return (skill) + ((fitness)/2) + ((form)*0.3);

		
}
int gamePlan(player_node *pp,teams_node * pt){
	int gPlan[32][15]={};
	int ** a;
	int temp=0;
	int u=0;
	int counter=0;
	int temp_GK =0;
	int ability=0;
	int f=0;
	int stop=1;
	int numteams=32;
	int gPlan_i=0;
	player_node * p=(player_node *)calloc(1,sizeof(player_node));
	player_node *head=pp;
	teams_node * pteam=(teams_node *)calloc(1,sizeof(teams_node));
	teams_node *headt=pt;
	char order[20]={};
	while(numteams)
	{
	strcpy(order,pt->teamName);
	if(strcmp(order,NULL))
	break;
	//scanf("%s",order);
	
	while(stop)
	{
		p=search_post(pp,"G",order);
		
		if(!p)
		{
			stop=0;
		}
		else
		{
			
			ability=doAbility(p->skill,p->form,p->fitness);
			if(temp_GK<ability)
			{
				temp_GK = ability ;
				gPlan[gPlan_i][0] = p->number;
			}
			pp = p->next;	
		}
		
	}
	f++;
	pp=head;

	int b[4]={442,433,352,532};
	int t=0;
	int j=0;
	int n=20;
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
				/////player->post=="D"
			//p ro az barname migirim
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
		counter=0;
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
	gPlan[11]= t;
	
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
		
			gPlan[f]=a[j][1];
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
			gPlan[f]=a[i][1];
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
			gPlan[f]=a[i][1];
			f++;
		}
		for (int i = 0; i < n; i++)
		{
		free(a[i]);
		a[i] = NULL;
		}
		free(a);
		a = NULL;
		numteams--;
		pt = pteam->next;
	}
	
}
void bubbleSort(int **a,int n)
{
	int i, j;
	int temp=0;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
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
}////////////////////////////////////////////main
int main()
{
	srand(time(NULL));
	
	int teamsNumber=32;
	///////////teams
	FILE *tt =  fopen("players\\teams.txt","r");
	teams_node *head_team= (teams_node *)calloc(1,sizeof(teams_node));
	teams_node *pt=head_team;
	teamsReadInfofromGlobal(tt,pt);
	//////////////players;
	FILE *teams = fopen("teamNames.txt","r");
	const char * formatt=".txt";
	const char *dir="players\\";
	if (!teams) {
		perror("fopen failed");
		return 0;
	}
	player_node *head_players = (player_node *)calloc(1, sizeof(player_node));
	player_node *pp = head_players;
	while(teamsNumber)
	{
		char *teamsName=(char *)calloc(15,sizeof(char));
		char *teamNamee=(char *)calloc(15,sizeof(char));
		fscanf(teams,"%s",teamsName);
		strcat(teamNamee,append(append(dir,teamsName),formatt));
		FILE *tp = fopen(teamNamee,"r");
		
		if (!tp) {
			perror("fopen failed");
			return 0;
		}
		
		
		pp=playersReadInfo(tp,pp,teamsName);
		fclose(tp);
		tp=NULL;
		teamsName=NULL;
		teamsNumber--;
	}
	doSkills(head_team,head_players);
	gamePlan(head_players,head_team);
	printList(head_players);
}
void teamsReadInfofromGlobal(FILE *t,teams_node *p)///////sould copy this to our grouping system
{
	/*char teamName[15];
	char group[1];
	int state;
	char confed[15];
	int seed;
	*/
	char line[100]={};
	int counter=0;
	const char * space=" ";
	
	for(int i=0;fgets(line,100,t)!=NULL;i++)
	{
		char *namee=(char *)calloc (20,sizeof(char));
		char groupp[1]={};
		int statee;
		char *confidd=(char *)calloc (15,sizeof(char));
		int seedd;
		fscanf(t,"%s%s%d%s%d",namee,groupp,&statee,confidd,&seedd);
		
		counter++;
		/////////////file of teams
		strcpy(p->teamName,namee);
		strcpy(p->group,groupp);
		p->state=statee;
		strcpy(p->confed,confidd);
		p->seed=seedd;
		/////////////our calculations
		strcat(teamNames,append(namee,space));
		//strcat(teamNames,space);
		
		
		
		////////////
		namee=NULL;
		confidd=NULL;
		p->next = (teams_node *)calloc(1, sizeof(teams_node));
		p = p->next;
		
	}
	FILE *set=fopen("teamNames.txt","w");
	fprintf(set,"%s",teamNames);
	fclose(set);
	set=NULL;
}
player_node * playersReadInfo(FILE *t,player_node *p,const char * teamNamee)
{
	char line[100]={};
	int counter=0;
	
	//////this ganna change
	
	for(int i=0;fgets(line,100,t)!=NULL;i++)
	{
		
		int num;
		char *namee=(char *)calloc (25,sizeof(char));
		char *postt=(char *)calloc (1,sizeof(char));
		int age;
		fscanf(t,"%d%s%d%s",&num,namee,&age,postt);
		
		counter++;
		/////////////file of players
		p->number=num;
		strcpy(p->name,namee);
		strcpy(p->mainPost,postt);
		p->age=age;
		
		/////////////our calculations
		strcpy(p->nation,teamNamee);             	
		
		
		////////////
		p->next = (player_node *)calloc(1, sizeof(player_node));
		p = p->next;
		
		free(namee);
		postt=NULL;
		namee=NULL;
	}
	return p;
}
