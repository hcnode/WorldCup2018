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
player_node *search(player_node *head,const char* teamName)
{
	player_node *p = head;
	while (p != NULL) {
		if (strcmp(p->nation,teamName)==0)
			return p;
		p = p->next;
	}
	return NULL;
}
void printList(player_node *head) 
{
	player_node *p = head;
	for (int i=0;;i++) {
		if(p != NULL) {	
		if(i!=0)
			{
				printf("%s ", p->nation);
				puts("");
			}
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
//	gamePlan(head_players);
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
