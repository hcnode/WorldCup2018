#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char teamNames[480]={};
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
void loadPlayerInfo();
void selectTeamsToManagement();
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
			loadPlayerInfo();
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
	char teamNames[32][25]={};
	int numTeams=1,i=0;
	puts("Enter Number of your team that you want to manage");
	while(numTeams<33)
	{
		fscanf(managment,"%s",teamNames[i]);
		printf("%2d.%s\n",numTeams,teamNames[i]);
		
		
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
	
	printf("Your team is : %s", teamNames[team-1]);
	strcpy(selectedTeam,teamNames[team-1]);
	return;
}
void loadPlayerInfo()
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
	
	///////////////file of points of teams in group games
	
	///////////////file of goals and who and in which game is that
	
	
}
