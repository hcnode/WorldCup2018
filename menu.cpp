#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char teamNames[480]={};
char teamNamesandNums[32][25]={};
typedef struct players{
	int number;
	char name[20];
	int age;
	char nation[20];
	char mainPost[2];
	char tempPost[2];
	int skill;
	int form;
	int fitness;
	int goals;
	int passGoals;
	
	struct players *next;
}player_node;
typedef struct teams{
	char teamName[15];
	char group[2];
	int state;
	char confed[15];
	int seed;
	int pointOfteam;
	int goalsRecev;
	int goalsScoerds;
	struct teams *next;
}teams_node;
////////////////var
char selectedTeam[25]={};
void loadPlayerInfo(player_node * headp);
void selectTeamsToManagement();
void pointsOfTeamsWrite(teams_node *headt);
void pointsOfTeamsRead(teams_node *head);
int main()
{
	int menuOrder=0;
	
	////////////this is main menu
	printf("Choose one of these options :\n");
	puts("1.a New WorldCup!");
	puts("");
	puts("2.load recent WorldCup");
	scanf("%d",&menuOrder);
	switch(menuOrder)
	{
		case 1: {///////reset the game and read info from files 
		selectTeamsToManagement();
		break;}
		case 2: {
			//loadPlayerInfo(head);
			//////////load all of recent WorldCup from files
			break;
		}
		
	}
	return 0;
}
void selectTeamsToManagement()
{
	FILE *managment=fopen("teamNames.txt","r");
	char line[801]={};
	int team=0;
	char teamNamesandNums[32][25]={};
	int numTeams=1,i=0;
	puts("Enter Number of your team that you want to manage");
	while(numTeams<33)
	{
		fscanf(managment,"%s",teamNamesandNums[i]);
		printf("%2d.%s\n",numTeams,teamNamesandNums[i]);
		
		
		numTeams++;
		i++;
	}
	fclose(managment);
	managment=NULL;
	while(1)
	{
		scanf("%d",&team);
		if( team<33 && team>0)
		{
			break;
		}
		else
		{
			puts("choose team number from list!!");
		}
	}
	
	printf("Your team is : %s", teamNamesandNums[team-1]);
	strcpy(selectedTeam,teamNamesandNums[team-1]);
	return;
}
void loadPlayerInfo(player_node * headp)
{
	FILE *loadplayers = fopen("recentWorldCupPlayersInfo.txt","r");
	if (!loadplayers)
	{
		puts("There is no recent WorldCup!!");
		return;
	}
	
	char line[200]={};
	int counter=0;
	player_node *p=(player_node*)calloc(1,sizeof(player_node));
	p=headp;
	for(int i=0;fgets(line,200,loadplayers)!=NULL&&counter!=1005;i++)
	{
		
		int num;
		char *namee=(char *)calloc (25,sizeof(char));
		char *teamName=(char *)calloc (25,sizeof(char));
		char *postt=(char *)calloc (1,sizeof(char));
		char *postt_temp=(char *)calloc (1,sizeof(char));
		int age,skill,form,fitness,goals,goalpass;
		
		fscanf(loadplayers,"%d%s%d%s%s%s%d%d%d%d%d",&num,namee,&age,teamName,postt,postt_temp,&skill,&form,&fitness,&goals,&goalpass);
		
		counter++;
		/////////////file of players
		p->number=num;
		strcpy(p->name,namee);
		strcpy(p->mainPost,postt);
		strcpy(p->tempPost,postt_temp);
		p->age=age;
		strcpy(p->nation,teamName);             	
		p->skill=skill;
		p->form=form;
		p->fitness=fitness;
		p->goals=goals;
		p->passGoals=goalpass;
		
		////////////
		p->next = (player_node *)calloc(1, sizeof(player_node));
		p = p->next;
		
		free(namee);
		postt=NULL;
		namee=NULL;
	}
	
	fclose(loadplayers);
	loadplayers=NULL;
	////////////////file of teams that the player wants to manage check!
	
	///////////////file of points of teams in group games check!
	
	///////////////file of goals and who and in which game is that
	
	
}
void pointsOfTeamsWrite(teams_node * head)
{
	FILE *pointsOfTeams = fopen("TEAMSPOINTS.txt","w");
	char *pointsOfTeamsInfo=(char *)calloc (350,sizeof(char));
	teams_node *pt = (teams_node*)calloc(1,sizeof(teams_node));
	pt = head;
	while (pt != NULL) {
		char integer_string[15]={};
		sprintf(integer_string, "\n%d %d %d %s %s\n",pt->pointOfteam,pt->goalsRecev,pt->goalsScoerds,pt->teamName,pt->group );
		strcat(pointsOfTeamsInfo, integer_string); 
		pt = pt->next;
	}
	fprintf(pointsOfTeams,"%s",pointsOfTeamsInfo);
	fclose(pointsOfTeams);
	pointsOfTeams=NULL;
	
}
void pointsOfTeamsRead(teams_node *head)
{
	FILE *pointsOfTeams = fopen("TEAMSPOINTS.txt","r");
	teams_node *pt = (teams_node*)calloc(1,sizeof(teams_node));
	pt = head;
	char line[20]={};
	for(int i=0;fgets(line,20,pointsOfTeams)!=NULL;i++)
	{
		
		fscanf(pointsOfTeams,"%d %d %d %s %s",pt->pointOfteam,pt->goalsRecev,pt->goalsScoerds,pt->teamName,pt->group);
		/////////////file of players
		///////////
		
	}
	fclose(pointsOfTeams);
	pointsOfTeams=NULL;
	
}
void playerGoalsWrite(player_node *headp,int isgroupGame,teams_node * headt,int )
{
	///////////first var is : is groupGame?? 1 : 0
	FILE *playersGoals = fopen("PlayersGoals.txt","w");
	char *playersGoalsTXT=(char *)calloc (350,sizeof(char));
	player_node *pp = (player_node*)calloc(1,sizeof(player_node));
	teams_node *pt = (teams_node*)calloc(1,sizeof(teams_node));
	pp = headp;
	pt= headt;
	int numTeams=0;
	while (numTeams<33)
	{
		char * group = (char *)calloc(2,sizeof(char));
		strcpy(group,pt->group);
		while (strcmp(pt->teamName,pp->nation)==0) {
		char integer_string[15]={};
		//sprintf(integer_string, "\n%d %s %d %s %s\n",isgroupGame,group,);//////////what can i do for team? Vs team?		?????
		strcat(playersGoalsTXT, integer_string); 
		pp = pp->next;
		}
		pt->next;
		numTeams++;
	}
	
	fprintf(playersGoals,"%s",playersGoalsTXT);
	fclose(playersGoals);
	playersGoals=NULL;
	
}
void playerGoalsRead(player_node *headp)
{
	/////namayesh dar jadval
}
