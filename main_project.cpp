#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include <math.h>
char teamNames[480]={};
char teamNamesandNums[32][40]={};
int matchTable[4][8]={{1324,1323,1311,1101,1104,1312,1303,1322},{4225,2328,4202,3313,2330,2517,4520,3426},{3409,4418,2121,2307,3106,3329,3431,2105},{2132,3214,3308,4419,4327,4216,2310,4215}};
int groupTable[4][8]={};
char selectedTeam[25]={};
int gPlan[32][15]={};
int worldCupnewGrouping=0;
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
void loadPlayersInformationFirstTime(player_node * head_players);
void teamsReadInfofromGlobal(FILE *t,teams_node *p);
void playerWriteInfo(player_node *pp);
player_node * playersReadInfo(FILE *t,player_node *p,const char * teamNamee);
void gamePlan(player_node * head,teams_node *tt);
int doAbility(int skill,int form, int fitness);
void bestPlanForManagment(player_node *pp,int t,int selectedTeam);
void selectTeamsToManagement();
void updateGamePlan(player_node *pp);
void printList(player_node *head);
void bubbleSort(int **a,int n);
player_node *search_post(player_node *head,const char* post,const char* teamName);
player_node *search_teamName(player_node *head,const char* teamName);
player_node *search_post(player_node *head,const char* post,const char* teamName);
player_node *search_post_temp(player_node *head,const char* post,const char* teamName);
player_node *search_playerNumber(player_node *head,int n);
player_node *search_playerNumber_teams(player_node *head,int n,const char *teamName);
player_node *search_teamName_forPlayer(player_node *head,const char* teamName);
teams_node * search_team(teams_node * headt,const char * teamName);
char* append(const char* name,const char* extension);
void splash();
void doSkills(teams_node * head_team,player_node * head_player);
void customization(player_node *headp,teams_node * headt);
void CustomizationManualform(player_node * headp,teams_node * headt);
void showPlayersofUser(player_node * headp);
void changingPlayerofUser(player_node * headp,teams_node *headt);
void doSubstitution(player_node * headp,teams_node * headt,int x,int y);
void printtable();
void startNewWorldCup();
void loadGrouping(teams_node * head_teams);
void loadPlayersInformationFirstTime();
void newGrouping(teams_node * head_team);
int check(int place,int group,int teamNumber);
int checkNULL();
void copyTeams(int teamsOrginal[],int teams[]);
void tableToNULL();
void setTempNull(player_node * head);
void setTempPosts(player_node * pp,teams_node * pt);
void randomizeTeams();
void balloting();
///////////////////matchs
void matchControllerGroups(player_node * headp,teams_node * headt);
/////////////////
int goalNumber(double attackPower1, double defencePower2);
int winer(int goal1,int goal2);/////////////////////////////////////to do ***********
int goalzan( int tarkib);
int passgoal(int tarkib);
teams_node * searchTeamForGrouping(teams_node * head_team,const char * teamName);
int main()
{
	//for delay and show wordcup
	srand((unsigned)time(NULL));
	////////////////splash screen
	clock_t clockk0=clock();
	while(clock()<clockk0+2000);
	splash();
	clockk0=clock();
while(clock()<clockk0+3000);

system("cls");
	////////////////new WorldCup or recent WorldCup?
	printf("\n\n\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.New WorldCup.");
	printf("\t\t\t\t2.Load Recent WorldCup.\n");//////////to do ******************
	int a=1;
	while(a)
	{
		char *n=(char *)calloc(10,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"1")==0 || strcmp(n,"2")==0 ||strcmp(n,"exit")==0)
		{
			if(strcmp(n,"1")==0)
			{

				system("cls");
				startNewWorldCup();
				a=0;
			}
			else if(strcmp(n,"2")==0)
			{
				//loadRecentWorldCup();
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				a=0;
			}
		}
		else
		{
			puts("Choose your number from list please!");
		}
		free(n);
		n=NULL;

	}


}
void startNewWorldCup()
{
	////////head of player here !!!!!!!!!!!!!!!!!!!
	player_node *head_player=(player_node *)calloc(1,sizeof(player_node));
	teams_node * head_teams=(teams_node *)calloc(1,sizeof(teams_node));
	system("cls");
	printf("\n\n\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.New group balloting for WorldCup.");
	printf("\t\t\t\t2.Load the WorldCup's groups.\n");
	int a=1;
	while(a)
	{
		char *n=(char *)calloc(10,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"1")==0 || strcmp(n,"2")==0 ||strcmp(n,"exit")==0)
		{
			if(strcmp(n,"1")==0)
			{

				system("cls");
				worldCupnewGrouping=1;
				loadGrouping(head_teams);
				a=0;
			}
			else if(strcmp(n,"2")==0)
			{
				loadGrouping(head_teams);
				//loadGrouping();
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				a=0;
			}
		}
		else
		{
			puts("Choose your number from list please!");
		}
		free(n);
		n=NULL;
	}
	selectTeamsToManagement();

	loadGrouping(head_teams);/////////*******
	FILE *managment1=fopen("teamNames.txt","r");
	char line[5000]={};
	int team=0;
	int numTeams=1,i=0;
	puts("Enter Number of your team that you want to manage");
	while(numTeams<33)
	{
		fscanf(managment1,"%s",teamNamesandNums[i]);
		printf("%2d.%s\n",numTeams,teamNamesandNums[i]);
		numTeams++;
		i++;
	}
	fclose(managment1);
	managment1=NULL;
	loadPlayersInformationFirstTime(head_player);
	doSkills(head_teams,head_player);
	gamePlan(head_player,head_teams);
	setTempPosts(head_player,head_teams);
	customization(head_player,head_teams);
	playerWriteInfo(head_player);

	matchControllerGroups(head_player,head_teams);
}
void customization(player_node *headp,teams_node * headt)
{
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	teams_node * pt=(teams_node *)calloc(1,sizeof(teams_node));
	pt = headt;
	pp=headp;
	system("cls");
	printf("\n\n\t\t\t\t ====Customization form====");
	printf("\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.Manual GamePlan.");
	printf("\t\t\t\t2.Automatical Best game plan.\n");
	int a=1;
	while(a)
	{
		char *n=(char *)calloc(10,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"1")==0 || strcmp(n,"2")==0 ||strcmp(n,"exit")==0)
		{
			if(strcmp(n,"1")==0)
			{
				system("cls");
				CustomizationManualform(pp,pt);
				a=0;
			}
			else if(strcmp(n,"2")==0)
			{
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				a=0;
			}
		}
		else
		{
			puts("Choose your number from list please!");
		}
		free(n);
		n=NULL;

	}
}
void CustomizationManualform(player_node * headp,teams_node *headt)
{
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	teams_node * pt=(teams_node *)calloc(1,sizeof(teams_node));
	pt = headt;
	pp = headp;

	int gameSystem[4]={442,352,541,433};
	system("cls");
	printf("\n\n\t\t\t\t ====Customization Manual form====");
	printf("\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.4-4-2");
	printf("\t\t2.3-5-2");
	printf("\t\t3.5-4-1");
	printf("\t\t4.4-3-3\n");
	int r=0;
	for(r=0;strcmp(teamNamesandNums[r],selectedTeam);r++);
	int a=1;
	int order=0;
	while(a)
	{
		char *n=(char *)calloc(10,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"1")==0 || strcmp(n,"2")==0 ||strcmp(n,"exit")==0 ||strcmp(n,"3")==0||strcmp(n,"4")==0)
		{
			if(strcmp(n,"1")==0)
			{
				order=1;
				bestPlanForManagment(pp,gameSystem[order-1],r+1);
				setTempNull(pp);
				setTempPosts(pp,pt);
				system("cls");
				a=0;
			}
			else if(strcmp(n,"2")==0)
			{
				order=2;
				bestPlanForManagment(pp,gameSystem[order-1],r+1);
				setTempNull(pp);
				setTempPosts(pp,pt);
				system("cls");
				a=0;
			}
			else if(strcmp(n,"3")==0)
			{
				order=3;
				bestPlanForManagment(pp,gameSystem[order-1],r+1);
				setTempNull(pp);
				setTempPosts(pp,pt);
				system("cls");
				a=0;
			}
			else if(strcmp(n,"4")==0)
			{
				order=4;
				bestPlanForManagment(pp,gameSystem[order-1],r+1);
				setTempNull(pp);
				setTempPosts(pp,pt);
				system("cls");
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				system("cls");
				a=0;
			}
		}
		else
		{
			puts("Choose your number from list please!");
		}
		free(n);
		n=NULL;

	}
	system("cls");
	printf("\n\n\t\t\t\t ====Customization Substitution form====");
	printf("\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.I don't want Substitution.");
	printf("\t\t\t2.Change my players in game\n ");
	a=1;
	while(a)
	{
		char *n=(char *)calloc(10,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"1")==0 || strcmp(n,"2")==0 ||strcmp(n,"exit")==0)
		{
			if(strcmp(n,"1")==0)
			{
				//setTempPosts(pp,pt);
				/////show the players is in game
				system("cls");
				showPlayersofUser(pp);

				a=0;
			}
			else if(strcmp(n,"2")==0)
			{
				/////go to changing players system
				system("cls");
				pp=headp;
				showPlayersofUser(pp);
				pp=headp;
				changingPlayerofUser(pp,pt);
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				system("cls");
				a=0;
			}
		}
		else
		{
			puts("Choose your number from list please!");
		}
		free(n);
		n=NULL;

	}
}
void changingPlayerofUser(player_node * headp,teams_node *headt)
{
	printf("\n\t\t\t\t ====Substitution Mode====");
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	teams_node * pt=(teams_node *)calloc(1,sizeof(teams_node));
	pp=headp;
	pt = headt;
	int a=1;
	char xt[5];
	char yt[5];
	int x=0,y=0;
	int r=0;
	int counter=0;
	for(r=0;strcmp(teamNamesandNums[r],selectedTeam);r++);
	while(a)
	{
		counter=0;
		pp=headp;
		pt = headt;
		printf("\n\t\tTo do Substitution First Choose player is in the plan then Choose player is out of plan please(player's Number in plan / player's Number out of plan)\n");
		scanf("%s",xt);
		scanf("%s",yt);
		//

		for(int i=0;i<5;i++){
			if(isdigit[i]) continue;
			else{
				i = 0;
				printf("\n\t\tTo do Substitution First Choose player is in the plan then Choose player is out of plan please(player's Number in plan / player's Number out of plan)\n");
						scanf("%s",xt);

			}
		}
		x = (int)strtol(xt, (char **)NULL, 10);


		for(int i=0;i<5;i++){
			if(isdigit[i]) continue;
			else{
				i = 0;
				printf("\n\t\tTo do Substitution First Choose player is in the plan then Choose player is out of plan please(player's Number in plan / player's Number out of plan)\n");
						scanf("%s",yt);

			}
		}
		y = (int)strtol(yt, (char **)NULL, 10);
		//
		for(int u=0;u<11;u++)
		{
			if(gPlan[r][u]==x)
			{
				counter++;
			}
		}
		for(int u=0;u<11;u++)
		{
			if(gPlan[r][u]==y)
			{
				counter=2;
			}
		}
		if(counter==1)
		{
			int q=0;
			for(q=0;gPlan[r][q]!=x;q++);
			gPlan[r][q]=y;
			//////////////
			doSubstitution(pp,pt,x,y);
			pp=headp;
			updateGamePlan(pp);
			system("cls");
			pp=headp;
			showPlayersofUser(pp);
		}
		else
		{
			continue;
		}

		///////////////
		printf("\n\t\tDo you have more Substitution?(Yes -> 1 / No -> 0)\n");
		scanf("%d",&a);
	}
}
void doSubstitution(player_node * headp,teams_node * headt,int x,int y)
{
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	teams_node * pt=(teams_node *)calloc(1,sizeof(teams_node));
	pp=headp;
	pt = headt;
	int istrue=0;
	player_node * ppp=(player_node *)calloc(1,sizeof(player_node));
	player_node * pppp=(player_node *)calloc(1,sizeof(player_node));
	char * postt=(char *)calloc(2,sizeof(char));
	////////////////
	int r=0;
	for(r=0;strcmp(teamNamesandNums[r],selectedTeam);r++);
	char *teamName = (char *)calloc(30,sizeof(char));
	strcpy(teamName,selectedTeam);
	/////////////
	ppp=search_playerNumber_teams(pp,x,teamName);
	printf("%s\n",ppp->name);
	pppp=search_playerNumber_teams(pp,y,teamName);
	strcpy(postt,ppp->tempPost);
	strcpy(ppp->tempPost,"N");
	strcpy(pppp->tempPost,postt);
	printf("%s",pppp->name);
	/*
	while(pp && istrue!=2)
	{
		if(strcmp(pp->nation,selectedTeam)==0)
		{
			ppp=search_playerNumber(pp,x);
			printf("%s\n",ppp->name);
			pppp=search_playerNumber(pp,y);
			strcpy(postt,ppp->tempPost);
			strcpy(ppp->tempPost,"N");
			strcpy(pppp->tempPost,postt);
			printf("%s",pppp->name);
			pp= ppp->next;
			istrue=2;
			if(strcmp(pp->nation,selectedTeam)!=0)
			istrue=2;

		}
		else if(istrue==0)
		{
			pp= pp->next;
		}

	}
	*/


}
void showPlayersofUser(player_node * headp)
{

	printf("\t\t\t\t ====Players In Game====");
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	player_node * ppp=(player_node *)calloc(1,sizeof(player_node));
	int counter=0;

	while(pp && counter <11)
	{
		ppp=search_teamName_forPlayer(pp,selectedTeam);
		printf("\n\t\t%3d-%-20s | Skill : %3d | Form : %3d | Fitness : %3d | Main Post : %s | Post : %s |",ppp->number,ppp->name,ppp->skill,ppp->form,ppp->fitness,ppp->mainPost,ppp->tempPost);
		counter++;
		pp= ppp->next;
	}

	pp=headp;
	ppp=NULL;
	int istrue=0;
	printf("\n===========================================================================================================");
	printf("\n\t\t\t\t ====Players Out Game====");
	while(pp && istrue!=2)
	{
		if(strcmp(pp->nation,selectedTeam)==0)
		{
			ppp=search_post_temp(pp,"N",selectedTeam);
			if(ppp)
			{
				printf("\n\t\t%2d-%-20s | Skill : %3d | Form : %3d | Fitness : %3d | Main Post : %s | Post : %s |",ppp->number,ppp->name,ppp->skill,ppp->form,ppp->fitness,ppp->mainPost,ppp->tempPost);
				pp= ppp->next;
				istrue=1;
				if(strcmp(pp->nation,selectedTeam)!=0)
				istrue=2;

			}
			else
			{
				istrue=2;
			}


		}
		else if(istrue==0)
		{
			pp= pp->next;
		}

	}
}
void loadPlayersInformationFirstTime(player_node * head_players)
{
	int teamsNumber=32;
	FILE *teams = fopen("teamNames.txt","r");
	const char * formatt=".txt";
	const char *dir="players\\";
	if (!teams) {
		perror("fopen failed : \nCheck Files and then run program again!");
		return;
	}
	//player_node *head_players = (player_node *)calloc(1, sizeof(player_node));
	player_node *pp =(player_node*)calloc(1,sizeof(player_node));
	pp=head_players;////////////////////////********
	while(teamsNumber)
	{
		char *teamsName=(char *)calloc(15,sizeof(char));
		char *teamNamee=(char *)calloc(15,sizeof(char));
		fscanf(teams,"%s",teamsName);
		strcat(teamNamee,append(append(dir,teamsName),formatt));
		FILE *tp = fopen(teamNamee,"r");

		if (!tp) {
			perror("fopen failed : \nCheck Files and then run program again!");
			return;
		}


		pp=playersReadInfo(tp,pp,teamsName);
		fclose(tp);
		tp=NULL;
		teamsName=NULL;
		teamsNumber--;
	}
}
void newGrouping(teams_node * head_team)
{
	char line[100]={};
	int counter=0;
	teams_node *pt=(teams_node*)calloc(1,sizeof(teams_node));
	pt=head_team;
	teams_node *pd=(teams_node *)calloc(1,sizeof(teams_node));
	/////////do balloting for new grouping
	tableToNULL();
	balloting();
	////////////////
	/*FILE *managment=fopen("teamNames.txt","r");
	int numTeams=1,i=0;
	while(numTeams<33)
	{
		fscanf(managment,"%s",teamNamesandNums[i]);
		numTeams++;
		i++;
	}
	fclose(managment);
	managment=NULL;
	*/
	//////////////////
	/*
	char teamName[15];
	char group[2];
	int state;
	char confed[15];
	int seed;
	int pointOfteam;
	int goalsRecev;
	int goalsScoerds;
	struct teams *next;
	*/
	//matchTable[4][8]
	char *teamName=(char *)calloc(25,sizeof(char));
	//char teamNamesandNums[32][25]={};
	char *statee=(char*)calloc(2,sizeof(char));
		for(int i=0;i<4;i++)
		{

			for(int j=0;j<8;j++)
			{
				strcpy(teamName,teamNamesandNums[matchTable[i][j]%100-1]);
				pd=searchTeamForGrouping(pt,teamName);
				if(j==0)
				strcpy(statee,"A");
				else if(j==1)
				strcpy(statee,"B");
				else if (j==2)
				strcpy(statee,"C");
				else if(j==3)
				strcpy(statee,"D");
				else if(j==4)
				strcpy(statee,"E");
				else if (j==5)
				strcpy(statee,"F");
				else if(j==6)
				strcpy(statee,"G");
				else if(j==7)
				strcpy(statee,"H");
				/////////////////
				strcpy(pd->group,statee);
				pd->state=i+1;
				/////////////////

			}
		}
}
teams_node *searchTeamForGrouping(teams_node * head_team,const char * teamName)
{
	teams_node *p=(teams_node *)calloc(1,sizeof(teams_node));
	p=head_team;
	while(p)
	{
		if(strcmp(p->teamName,teamName)==0)
		{
			return p;
		}
		else
		p=p->next;
	}
	return NULL;
}
void loadGrouping(teams_node * head_teams)
{
	/////////first this ganna run
	FILE *tt =  fopen("players\\teams.txt","r");
	teams_node *head_team= (teams_node *)calloc(1,sizeof(teams_node));
	teams_node *pt=(teams_node *)calloc(1,sizeof(teams_node));///////////////////////*****************
	pt=head_teams;
	//////////////////teams info grouping and ... from file ***********
	teamsReadInfofromGlobal(tt,pt);
	if(worldCupnewGrouping==1)
	newGrouping(pt);
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
		char *postt_temp=(char *)calloc (1,sizeof(char));
		int age;
		fscanf(t,"%d%s%d%s",&num,namee,&age,postt);

		counter++;
		/////////////file of players
		p->number=num;
		strcpy(p->name,namee);
		strcpy(p->mainPost,postt);
		strcpy(p->tempPost,postt_temp);
		p->age=age;

		/////////////our calculations
		strcpy(p->nation,teamNamee);


		////////////
		p->next = (player_node *)calloc(1, sizeof(player_node));
		p = p->next;

		free(namee);
		postt_temp=NULL;
		postt=NULL;
		namee=NULL;
	}
	return p;
}
void teamsReadInfofromGlobal(FILE *t,teams_node *p)///////sould copy this to our grouping system
{
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
void splash()
{
	puts("=========================================================================================================================");
	puts("=========================================================================================================================");
	puts("");
	puts("");
	puts("WW           WW           WW    OOOOOOOOOO    RRRRRRRRRR    LL         DDDDDDDD       CCCCCCCCC  UU      UU   PPPPPPPPPP");
	puts("  WW       WW  WW        WW     OO      OO    RR      RR    LL         DD      D      CC         UU      UU   PP      PP");
	puts("   WW     WW     WW     WW      OO      OO    RR     RR     LL         DD       D     CC         UU      UU   PP      PP");
	puts("    WW   WW       WW   WW       OO      OO    RRRRRRRR      LL         DD      D      CC         UU      UU   PPPPPPPPP");
	puts("     WW WW         WW WW        OO      OO    RR     RR     LL         DD     D       CC         UU      UU   PP");
	puts("      WW             WW         OOOOOOOOOO    RR      RR    LLLLLLLL   DDDDDDD        CCCCCCCCC  UUUUUUUUUU   PP");
	puts("");
	puts("");
	puts("=========================================================================================================================");
	puts("");
	puts("");
	puts("                        2222222222222   0000000000000  11   8888888888888");
	puts("                                   22   00         00  11   88         88");
	puts("                                   22   00         00  11   88         88");
	puts("                        2222222222222   00         00  11   8888888888888");
	puts("                        22              00         00  11   88         88");
	puts("                        22              00         00  11   88         88");
	puts("                        2222222222222   0000000000000  11   8888888888888");
	puts("");
	puts("");
	puts("=========================================================================================================================");
	puts("=========================================================================================================================");

}
char* append(const char* name,const char* extension)
{
	char* name_with_extension;
	name_with_extension =(char *) malloc(strlen(name)+1+4);
	strcpy(name_with_extension, name);
	strcat(name_with_extension, extension);
	return name_with_extension;
}
void selectTeamsToManagement()
{
	FILE *managment=fopen("teamNames.txt","r");
	char line[5000]={};
	int team=0;
	char teamt[5] ={0};
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

//
	while(1)
	{
		//for checking valid arg
		scanf("%s",teamt);
		for(int i=0;i<5;i++){
			if(isdigit[i]) continue;
			else{
				i = 0;
				puts("choose team number from list!!");
						scanf("%s",teamt);

			}
		}
		team = (int)strtol(teamt, (char **)NULL, 10);
		if( team<33 && team>0)
		{
			break;
		}
		else
		{
			puts("choose team number from list!!");
		}
	}
//
/*	while(1)
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
*/
	printf("Your team is : %s", teamNamesandNums[team-1]);
	strcpy(selectedTeam,teamNamesandNums[team-1]);
	return;
}
void balloting()
{
	//srand((unsigned)time(NULL));
	int teamsOrginal[32]={1101,1303,1104,1311,1312,1322,1323,1324,2105,2307,2310,2517,2121,2328,2330,2132,3506,3308,3409,3313,3214,3426,3329,3431,4202,4215,4216,4418,4419,4520,4225,4327};
	int teams[32]={1101,1303,1104,1311,1312,1322,1323,1324,2105,2307,2310,2517,2121,2328,2330,2132,3506,3308,3409,3313,3214,3426,3329,3431,4202,4215,4216,4418,4419,4520,4225,4327};
	int group=0;
	int checkTable=1;
	while(checkTable)
	{
	copyTeams(teamsOrginal,teams);
	tableToNULL();
	int team=0;
	int counter=0;
	for(;counter!=8;)
	{
		team=rand()%8;
		if(matchTable[0][counter]==0&&teams[team]!=0)
		{
			matchTable[0][counter]=teams[team];
			teams[team]=0;
			counter++;
		}

	}
	counter=0;
	int counter2=0;
	for(;counter2!=8;)
	{
		if(matchTable[1][counter]==0)
		{
			team=rand()%8+8;
			if(teams[team]!=0)
			{
			if(check(1,counter,teams[team]))
			{
			matchTable[1][counter]=teams[team];
			teams[team]=0;
			counter2++;
			counter=0;
			}
			else
			{
				counter++;
			}
			}

		}
		else
		{
			counter++;
		}
	}
	counter2=0;
	counter=0;
	for(;counter2!=8;)
	{
		if(matchTable[2][counter]==0)
		{
			team=rand()%8+16;
			if(teams[team]!=0)
			{
			if(check(2,counter,teams[team]))
			{
			matchTable[2][counter]=teams[team];
			teams[team]=0;
			counter2++;
			counter=0;
			}
			else
			{
				counter++;
			}
			}
		}
		else
		{
			counter++;
		}
	}
	counter2=0;
	counter=0;
	for(;counter2!=8;)
	{
		if(matchTable[3][counter]==0)
		{
			team=rand()%8+24;
			if(teams[team]!=0)
			{
			if(check(3,counter,teams[team]))
			{
			matchTable[3][counter]=teams[team];
			teams[team]=0;
			counter2++;
			counter=0;
			}
			else
			{
				counter++;
			}
			}
		}
		else
		{
			counter++;
		}
	}

	checkTable=checkNULL();
}
randomizeTeams();
}
void randomizeTeams()
{
	int counter=0,counter2=0;
	int a=1;
	int y=0;
	int col=0;
	int place1=0,place2=0,place3=0;
	while(counter2!=24)
	{
		place1=matchTable[1][col];
		matchTable[1][col]=0;
		place2=matchTable[2][col];
		matchTable[2][col]=0;
		place3=matchTable[3][col];
		matchTable[3][col]=0;
		a=1;
		counter=0;
		while(a)
		{
			y=rand()%3+1;
			if(matchTable[y][col]==0 && place1!=0)
			{
				matchTable[y][col]=place1;
				place1=0;
				counter++;
			}
			else if(matchTable[y][col]==0 && place2!=0)
			{
				matchTable[y][col]=place2;
				place2=0;
				counter++;

			}
			else if(matchTable[y][col]==0 && place3!=0)
			{
				matchTable[y][col]=place3;
				place3=0;
				counter++;
			}
			if(counter==3)
			{
				col++;
				counter2+=3;
				a=0;
			}


		}



	}
}
void printtable()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++)
		{
			printf("%4d ",matchTable[i][j]);
		}
		puts("");
	}

}
int check(int place,int group,int teamNumber)
{
	int confed=(teamNumber/100)%10;
	int ch=1;
	int counter=0;
	for(int i=place;i>=0;i--)
	{
		if(((matchTable[i][group])/100)%10==confed && confed!=3)
		{
			ch=0;
		}
		else if(((matchTable[i][group])/100)%10==confed && confed==3)
		{
			counter++;

		}
		if(counter>1)
		{
			ch=0;
		}


	}
	return ch;

}
int checkNULL()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(matchTable[i][j]==0)
			{
				return 1;
			}
		}
	}
	return 0;
}
void copyTeams(int teamsOrginal[],int teams[])
{
	for(int i=0;i<32;i++)
	{
		teams[i]=teamsOrginal[i];
	}
}
void tableToNULL()
{

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++)
		{
			matchTable[i][j]=0;
		}
	}
}
void bestPlanForManagment(player_node *pp,int t,int selectedTeam){
	int i,j;
	int ability=0;
	int gPlan_i = selectedTeam-1;
	int f=0;
	int stop =0;
	int n=20;
	int temp_GK=0;
	gPlan[gPlan_i][11]= t;
	gPlan[gPlan_i][13]=0;
	//////////////////////////
	player_node * p=(player_node *)calloc(1,sizeof(player_node));
	player_node *head=(player_node *)calloc(1,sizeof(player_node));
	head=pp;
	//player_node *player=(player_node *)calloc(1,sizeof(player_node));
	char order[25]={};
	strcpy(order,teamNamesandNums[selectedTeam-1]);
	int **a;
	a = (int **)calloc(n, sizeof(int *));

	for (int i = 0; i < n; i++) {
		a[i] = (int *)calloc(2, sizeof(int));
	}
				//golaer//////////////////////////////////////////////////////////////////
	stop =1;
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
				temp_GK = ability;
				gPlan[gPlan_i][0] = p->number;
				//player=p;
				gPlan[gPlan_i][12] = ability*2;
			}
			pp = p->next;
		}

	}
	//strcpy(player->tempPost,"G");
	f++;
	pp=head;
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
			gPlan[gPlan_i][12]+=a[j][0];
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
			gPlan[gPlan_i][12]+=a[i][0]/2;
			gPlan[gPlan_i][13]+=a[i][0]/2;
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
			gPlan[gPlan_i][13]+=a[i][0];
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
}
void gamePlan(player_node *pp,teams_node * pt){
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
	player_node *head=(player_node *)calloc(1,sizeof(player_node));
	head=pp;
	teams_node * pteam=(teams_node *)calloc(1,sizeof(teams_node));
	teams_node *headt=(teams_node *)calloc(1,sizeof(teams_node));
	headt=pt;
	player_node *player=(player_node *)calloc(1,sizeof(player_node));
	char order[20]={};
	while(numteams)
	{
	temp=0;
	u=0;
	f=0;
	counter=0;
	temp_GK=0;
	stop=1;
	if(!pt)
	break;
	strcpy(order,pt->teamName);

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
				player=p;
				gPlan[gPlan_i][12] = ability*2;
			}
			pp = p->next;
		}

	}
	//strcpy(player->tempPost,"G");
	f++;
	pp=head;

	int b[4]={442,433,352,541};
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
	gPlan[gPlan_i][11]= t;

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
			gPlan[gPlan_i][12]+=a[j][0];
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
			gPlan[gPlan_i][12]+=a[i][0]/2;
			gPlan[gPlan_i][13]+=a[i][0]/2;
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
			gPlan[gPlan_i][13]+=a[i][0];
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
		numteams--;
		gPlan[gPlan_i][14]=gPlan_i+1;
		gPlan_i++;
		pt = pt->next;
	}
	//printArrey(gPlan,head,headt);
	setTempNull(head);
	setTempPosts(head,headt);
}
void updateGamePlan(player_node *pp){
		int stop=0;
		int i,j;
		int ability=0;
		int gPlan_i=0;
		int r=0;
		player_node * p=(player_node *)calloc(1,sizeof(player_node));
		player_node *head=(player_node *)calloc(1,sizeof(player_node));
		head=pp;
		player_node *player=(player_node *)calloc(1,sizeof(player_node));
		char order[25]={};
		strcpy(order,selectedTeam);
		for(r=0;strcmp(teamNamesandNums[r],selectedTeam);r++);
		gPlan_i=r;
		//////////////goalkeeper
		gPlan[gPlan_i][12]=0;
		gPlan[gPlan_i][13]=0;
		stop=1;
		j=0;
		while(stop)
		{
			p=search_post_temp(pp,"G",order);

			if(!p)
			{
				stop=0;
				continue;
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
		pp=head;
/////////////////deffend
		stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post_temp(pp,"D",order);
			if(!p)
			{
				stop=0;
				continue;
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
		pp=head;
		///////////////////Middle
		stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post_temp(pp,"M",order);
			if(!p)
			{
				stop=0;
				continue;
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
		pp=head;
		///////////Atack
		stop=1;
		j=0;
		while(stop)
		{
			//search for temp post
			p=search_post_temp(pp,"A",order);
			if(!p)
			{
				stop=0;
				continue;
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
void setTempPosts(player_node * pp,teams_node * pt)
{
	player_node * p=(player_node *)calloc(1,sizeof(player_node));
	player_node *head=(player_node *)calloc(1,sizeof(player_node));
	head=pp;
	teams_node * pteam=(teams_node *)calloc(1,sizeof(teams_node));
	teams_node *headt=(teams_node *)calloc(1,sizeof(teams_node *));
	headt=pt;
	int system=0;
	int def=0,mid=0,att=0,odef=1,omid=0,oatt=0;
	int teamNum=32;
	char order[25]={};
	int i=0;
	int stop=1;
	while(teamNum)
	{
		strcpy(order,pt->teamName);
		system=gPlan[i][11];
		/////////////calculations
		def=system/100;
		mid=((system%100)-(system%10))/10;
		att=system%10;
		odef=1;
		omid=def+1;
		oatt=def+mid+1;
		//////////////////////////////////goaler
		p=search_playerNumber(search_post(pp,"G",order),gPlan[i][0]);
		if(!p)
		{
			stop=0;
		}
		else
		{
			if(strcmp(p->tempPost,"N")==0)
			{
				strcpy(p->tempPost,"G");
			}
			else
			{
				stop=0;
			}

		}
		///////////////////////defenders
		pp=head;
		stop=1;
		while(stop)
		{
			p=search_playerNumber(search_post(pp,"D",order),gPlan[i][odef]);

			if(!p)
			{
				stop=0;
			}
			else
			{

			if(strcmp(p->tempPost,"N")==0)
			{
				strcpy(p->tempPost,"D");
			}
			else
			{
				if(odef!=def)
				odef++;
				else
				{
					stop=0;
				}
			}

			}

		}
		//////////////////midders
		pp=head;
		stop=1;
		while(stop)
		{
			p=search_playerNumber(search_post(pp,"M",order),gPlan[i][omid]);

			if(!p)
			{
				stop=0;
			}
			else
			{

			if(strcmp(p->tempPost,"N")==0)
			{
				strcpy(p->tempPost,"M");
			}
			else
			{
				if(omid!=mid+odef)
				omid++;
				else
				{
					stop=0;
				}
			}

			}

		}
		//////////////////attackers
		pp=head;
		stop=1;
		while(stop)
		{
			p=search_playerNumber(search_post(pp,"A",order),gPlan[i][oatt]);

			if(!p)
			{
				stop=0;
			}
			else
			{

			if(strcmp(p->tempPost,"N")==0)
			{
				strcpy(p->tempPost,"A");
			}
			else
			{
				if(oatt!=10)
				oatt++;
				else
				{
					stop=0;
				}
			}

			}

		}

	pp=head;
	/////////
	teamNum--;
	pt = pt->next;
	i++;
	}

}
player_node *search_teamName(player_node *head,const char* teamName)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
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
teams_node * search_team(teams_node * head,const char * teamName)
{
	teams_node *p = (teams_node*)calloc(1,sizeof(teams_node));
	p=head;
	while (p != NULL) {
		if (strcmp(p->teamName,teamName)==0)
		{
			return p;
		}

		p = p->next;
	}
	return NULL;

}
player_node *search_playerNumber_teams(player_node *head,int n,const char* teamName)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
	while (p != NULL) {
		if(strcmp(p->nation,teamName)==0)
		{
			if (p->number==n)
			{
				return p;
			}
		}
		p = p->next;

	}
	return NULL;

}
player_node *search_teamName_forPlayer(player_node *head,const char* teamName)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
	while (p != NULL) {
		if (strcmp(p->nation,teamName)==0)
		{
			if(strcmp(p->tempPost,"N")!=0)
			return p;
		}

		p = p->next;
	}
	return NULL;
}
player_node *search_post(player_node *head,const char* post,const char* teamName)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
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
player_node *search_post_temp(player_node *head,const char* post,const char* teamName)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
	while (p != NULL) {
		if (strcmp(p->tempPost,post)==0)
		{
			if(strcmp(p->nation,teamName)==0)
			return p;
		}

		p = p->next;
	}
	return NULL;
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
}
player_node *search_playerNumber(player_node *head,int n)
{
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=head;
	while (p != NULL) {
		if (p->number==n)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;

}
int doAbility(int skill,int form, int fitness)
{
	return (skill) + ((fitness)/2) + ((form)*0.3);


}
void setTempNull(player_node * head)
{
	player_node *p = (player_node *)calloc(1,sizeof(player_node));
	p=head;
	char *temp=(char *)calloc(20,sizeof(char));
	while (p != NULL) {
		strcpy(p->tempPost,"N");
		p = p->next;
	}
	return;

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
void doSkills(teams_node * head_team,player_node * head_player)
{
	teams_node *team =(teams_node *)calloc(1,sizeof(teams_node));
	team=head_team;
	player_node * player = (player_node *)calloc(1,sizeof(player_node));
	player=head_player;
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

}
//////////////////////////////////////writes
void playerWriteInfo(player_node *pp)
{
	char *playersInformations=(char *)calloc (70000,sizeof(char));

	FILE *playersdata=fopen("recentWorldCupPlayersInfo.txt","w");
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=pp;
	while (p != NULL) {
		char integer_string[70]={};
		sprintf(integer_string, "\n%d %s %d %s %s %s %d %d %d %d %d\n", p->number,p->name,p->age,p->nation,p->mainPost,p->tempPost,p->skill,p->form,p->fitness,p->goals,p->passGoals);
		strcat(playersInformations, integer_string);
		p = p->next;
	}
	fprintf(playersdata,"%s",playersInformations);
	fclose(playersdata);
	playersdata=NULL;
}
int passgoal(int tarkib){
  int middle = (tarkib/10)%10;
  int a = rand()%middle + 1 ;
  a += tarkib / 100;
  return a;
}

int goalzan(int tarkib){
  int attacker = tarkib%10;
  int a = rand()%attacker + 1 ;
  a += tarkib/100 + (tarkib / 10)%10;
  return a;
}



int goalNumber(double attackPower1, double defencePower2) {
    int m = (int) round(attackPower1 / defencePower2);
    int goals[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double odds[11] = {0};
    double baze[11] = {0};
    int i = 0;
    for (i = 0; goals[i] != m; i++);
    odds[i] = 1000;
    for (int j = i + 1; j < 11; j++) {
        odds[j] = odds[j - 1] * (0.2);
    }
    for (int j = i - 1; j >= 0; j--) {
        odds[j] = odds[j + 1] * (0.3);
    }

    double sum=0;
    baze[0] = odds[0];

    for (int i = 1; i < 11; i++) {
        baze[i] = baze[i - 1] + odds[i];
    }
    sum = baze[10];

    int a = rand()%(int)(round(sum + 1)) ;
    int j = 0;
    for(j=0 ; a>baze[j] ;j++);
    return goals[j];
}
void matchControllerGroups(player_node * headp,teams_node * headt)
{
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	teams_node * ppt = (teams_node *)calloc(1,sizeof(teams_node));
	pt =headt;
	pp = headp;
	int loacalProceed = 0;
	int goalsofTeam1=0;
	int goalsofTeam2=0;
	int golzanNum=0;
	int passGoalNum=0;
		/////////////////////////
		/*
		char teamName[15];
	char group[2];
	int state;
	char confed[15];
	int seed;
	int pointOfteam;
	int goalsRecev;
	int goalsScoerds;
	struct teams *next;
	/////////////
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
	*/
	//char teamNamesandNums[32][25]={};
	//for(loacalProceed = 0;loacalProceed<4;loacalProceed++)
	//if(loacalProceed==1)
	//{
		//(matchTable[0][0]%100,matchTable[1][0]%100);

		for(int y=0; y < 32;y++)
		{
			printf ("\n%s" ,teamNamesandNums[y]);
		}








		// start of proceed 1
		for(int t=0, j=0,i=-1;j<32;t++,j+=2)
		{
			if(t%2==0)
			{
				i++;
			}


		goalsofTeam1=goalNumber(gPlan[matchTable[j%4][i]%100-1][13],gPlan[matchTable[(j+1)%4][i]%100-1][12]);
		goalsofTeam2=goalNumber(gPlan[matchTable[(j+1)%4][i]%100-1][13],gPlan[matchTable[j%4][i]%100-1][12]);
		printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[j%4][i]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(j+1)%4][i]%100-1],goalsofTeam2);
		if(goalsofTeam1!=goalsofTeam2)
		{
			if(goalsofTeam1>goalsofTeam2)
			{
					ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
					ppt->pointOfteam+=3;
			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
				ppt->pointOfteam+=3;
			}

		}
		else
		{
			ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppt->pointOfteam+=1;
		}
		ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam1;
		ppt->goalsRecev+=goalsofTeam2;
		ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam2;
		ppt->goalsRecev+=goalsofTeam1;
		while(goalsofTeam1)
		{

			golzanNum=goalzan(gPlan[matchTable[j%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[j%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->goals+=1;
			printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->passGoals+=1;
			printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			goalsofTeam1--;

		}
		while(goalsofTeam2)
		{
			golzanNum=goalzan(gPlan[matchTable[(j+1)%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[(j+1)%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+1)%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppp->goals+=1;
			printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+1)%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppp->passGoals+=1;
			printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			goalsofTeam2--;
			}

		}




		printf("\n\n\n\n\n\n\n\n\n");



		// start of proceed 2:
		/*
			matchTable[0][0]---->matchTable[2][0]
			matchTable[1][0]---->matchTable[3][0]
			matchTable[0][1]---->matchTable[2][1]
			matchTable[1][1]---->matchTable[3][1]
			matchTable[0][2]---->matchTable[2][2]
			matchTable[1][2]---->matchTable[3][2]
			matchTable[0][3]---->matchTable[2][3]
			matchTable[1][3]---->matchTable[3][3]
			matchTable[0][4]---->matchTable[2][4]
			matchTable[1][4]---->matchTable[3][4]
			matchTable[0][5]---->matchTable[2][5]
			matchTable[1][5]---->matchTable[3][5]
			matchTable[0][6]---->matchTable[2][6]
			matchTable[1][6]---->matchTable[3][6]
			matchTable[0][7]---->matchTable[2][7]
			matchTable[1][7]---->matchTable[3][7]
			matchTable[0][8]---->matchTable[2][8]
			matchTable[1][8]---->matchTable[3][8]
			*/
		for(int i = 0, j = 0, t=0 ;j<7; i++,t++){

				if(t%2==0 && t!=0)
				{
					j++;
				}


			goalsofTeam1=goalNumber(gPlan[matchTable[i%4][j]%100-1][13],gPlan[matchTable[(i+2)%4][j]%100-1][12]);
			goalsofTeam2=goalNumber(gPlan[matchTable[(i+2)%4][j]%100-1][13],gPlan[matchTable[i%4][j]%100-1][12]);
			printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[i%4][j]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(i+2)%4][j]%100-1],goalsofTeam2);
			if(goalsofTeam1!=goalsofTeam2)
			{
				if(goalsofTeam1>goalsofTeam2)
				{
						ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
						ppt->pointOfteam+=3;
				}
				else
				{
					ppt= search_team(pt,teamNamesandNums[matchTable[(i+2)%4][j]%100-1]);
					ppt->pointOfteam+=3;
				}

			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppt->pointOfteam+=1;
				ppt= search_team(pt,teamNamesandNums[matchTable[(i+2)%4][j]%100-1]);
				ppt->pointOfteam+=1;
			}
			ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
			ppt->goalsScoerds+=goalsofTeam1;
			ppt->goalsRecev+=goalsofTeam2;
			ppt= search_team(pt,teamNamesandNums[matchTable[(i+2)%4][j]%100-1]);
			ppt->goalsScoerds+=goalsofTeam2;
			ppt->goalsRecev+=goalsofTeam1;
			while(goalsofTeam1)
			{

				golzanNum=goalzan(gPlan[matchTable[i%4][j]%100-1][11]);
				passGoalNum=passgoal(gPlan[matchTable[i%4][j]%100-1][11]);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[i%4][j]%100-1][golzanNum],teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppp->goals+=1;
				printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[i%4][j]%100-1][passGoalNum],teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppp->passGoals+=1;
				printf("\npass Goale :%d.%s",ppp->number,ppp->name);
				goalsofTeam1--;

			}
			while(goalsofTeam2)
			{
				golzanNum=goalzan(gPlan[matchTable[(i+2)%4][j]%100-1][11]);
				passGoalNum=passgoal(gPlan[matchTable[(i+2)%4][j]%100-1][11]);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[(i+2)%4][j]%100-1][golzanNum],teamNamesandNums[matchTable[(i+2)%4][j]%100-1]);
				ppp->goals+=1;
				printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[(i+2)%4][j]%100-1][passGoalNum],teamNamesandNums[matchTable[(i+2)%4][j]%100-1]);
				ppp->passGoals+=1;
				printf("\npass Goale :%d.%s",ppp->number,ppp->name);
				goalsofTeam2--;
				}
		}
		printf("\n\n\n\n\n\n\n\n\n");
		// start of proceed 3
		 /*
		matchTable[0][0]---->matchTable[3][0]
		matchTable[1][0]---->matchTable[2][0]
		matchTable[0][1]---->matchTable[3][1]
		matchTable[1][1]---->matchTable[2][1]
		matchTable[0][2]---->matchTable[3][2]
		matchTable[1][2]---->matchTable[2][2]
		matchTable[0][3]---->matchTable[3][3]
		matchTable[1][3]---->matchTable[2][3]
		matchTable[0][4]---->matchTable[3][4]
		matchTable[1][4]---->matchTable[2][4]
		matchTable[0][5]---->matchTable[3][5]
		matchTable[1][5]---->matchTable[2][5]
		matchTable[0][6]---->matchTable[3][6]
		matchTable[1][6]---->matchTable[2][6]
		matchTable[0][7]---->matchTable[3][7]
		matchTable[1][7]---->matchTable[2][7]
		matchTable[0][8]---->matchTable[3][8]
		matchTable[1][8]---->matchTable[2][8]
		*/
		for(int i = 0, j = 0, t=0 ;j<7; i++,t++){
			int k = 0;
			if(t%2==0){
				k = 3;
			}
			else{
				k = 1;
			}
				if(t%2==0 && t!=0)
				{
					j++;
				}


			goalsofTeam1=goalNumber(gPlan[matchTable[i%4][j]%100-1][13],gPlan[matchTable[((i+k)%4)][j]%100-1][12]);
			goalsofTeam2=goalNumber(gPlan[matchTable[(i+k)%4][j]%100-1][13],gPlan[matchTable[i%4][j]%100-1][12]);
			printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[i%4][j]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(i+k)%4][j]%100-1],goalsofTeam2);
			if(goalsofTeam1!=goalsofTeam2)
			{
				if(goalsofTeam1>goalsofTeam2)
				{
						ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
						ppt->pointOfteam+=3;
				}
				else
				{
					ppt= search_team(pt,teamNamesandNums[matchTable[(i+k)%4][j]%100-1]);
					ppt->pointOfteam+=3;
				}

			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppt->pointOfteam+=1;
				ppt= search_team(pt,teamNamesandNums[matchTable[(i+k)%4][j]%100-1]);
				ppt->pointOfteam+=1;
			}
			ppt= search_team(pt,teamNamesandNums[matchTable[i%4][j]%100-1]);
			ppt->goalsScoerds+=goalsofTeam1;
			ppt->goalsRecev+=goalsofTeam2;
			ppt= search_team(pt,teamNamesandNums[matchTable[(i+k)%4][j]%100-1]);
			ppt->goalsScoerds+=goalsofTeam2;
			ppt->goalsRecev+=goalsofTeam1;
			while(goalsofTeam1)
			{

				golzanNum=goalzan(gPlan[matchTable[i%4][j]%100-1][11]);
				passGoalNum=passgoal(gPlan[matchTable[i%4][j]%100-1][11]);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[i%4][j]%100-1][golzanNum],teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppp->goals+=1;
				printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[i%4][j]%100-1][passGoalNum],teamNamesandNums[matchTable[i%4][j]%100-1]);
				ppp->passGoals+=1;
				printf("\npass Goale :%d.%s",ppp->number,ppp->name);
				goalsofTeam1--;

			}
			while(goalsofTeam2)
			{
				golzanNum=goalzan(gPlan[matchTable[(i+k)%4][j]%100-1][11]);
				passGoalNum=passgoal(gPlan[matchTable[(i+k)%4][j]%100-1][11]);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[(i+k)%4][j]%100-1][golzanNum],teamNamesandNums[matchTable[(i+k)%4][j]%100-1]);
				ppp->goals+=1;
				printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
				ppp=search_playerNumber_teams(pp,gPlan[matchTable[(i+k)%4][j]%100-1][passGoalNum],teamNamesandNums[matchTable[(i+k)%4][j]%100-1]);
				ppp->passGoals+=1;
				printf("\npass Goale :%d.%s",ppp->number,ppp->name);
				goalsofTeam2--;
				}
		}

		//printf("%s :   %d - %s :     %d",teamNamesandNums[matchTable[0][0]%100-1],goalsofTeam1,teamNamesandNums[matchTable[1][0]%100-1],goalsofTeam2);
		//ppp=search_teamName(pp,teamNamesandNums[matchTable[0][0]%100-1]);
		//
		/*
		matchTable[0][0]---->matchTable[1][0]
		matchTable[2][0]---->matchTable[3][0]
		matchTable[0][1]---->matchTable[1][1]
		matchTable[2][1]---->matchTable[3][1]
		matchTable[0][2]---->matchTable[1][2]
		matchTable[2][2]---->matchTable[3][2]
		matchTable[0][3]---->matchTable[1][3]
		matchTable[2][3]---->matchTable[3][3]
		matchTable[0][4]---->matchTable[1][4]
		matchTable[2][4]---->matchTable[3][4]
		matchTable[0][5]---->matchTable[1][5]
		matchTable[2][5]---->matchTable[3][5]
		matchTable[0][6]---->matchTable[1][6]
		matchTable[2][6]---->matchTable[3][6]
		matchTable[0][7]---->matchTable[1][7]
		matchTable[2][7]---->matchTable[3][7]
	}
	if(loacalProceed==2)
	{
	/*
		matchTable[0][0]---->matchTable[2][0]
		matchTable[1][0]---->matchTable[3][0]
		matchTable[0][1]---->matchTable[2][1]
		matchTable[1][1]---->matchTable[3][1]
		matchTable[0][2]---->matchTable[2][2]
		matchTable[1][2]---->matchTable[3][2]
		matchTable[0][3]---->matchTable[2][3]
		matchTable[1][3]---->matchTable[3][3]
		matchTable[0][4]---->matchTable[2][4]
		matchTable[1][4]---->matchTable[3][4]
		matchTable[0][5]---->matchTable[2][5]
		matchTable[1][5]---->matchTable[3][5]
		matchTable[0][6]---->matchTable[2][6]
		matchTable[1][6]---->matchTable[3][6]
		matchTable[0][7]---->matchTable[2][7]
		matchTable[1][7]---->matchTable[3][7]
		matchTable[0][8]---->matchTable[2][8]
		matchTable[1][8]---->matchTable[3][8]
		*/
		/*
	}
	if(loacalProceed==3)
	{
		matchTable[0][0]---->matchTable[3][0]
		matchTable[1][0]---->matchTable[2][0]
		matchTable[0][1]---->matchTable[3][1]
		matchTable[1][1]---->matchTable[2][1]
		matchTable[0][2]---->matchTable[3][2]
		matchTable[1][2]---->matchTable[2][2]
		matchTable[0][3]---->matchTable[3][3]
		matchTable[1][3]---->matchTable[2][3]
		matchTable[0][4]---->matchTable[3][4]
		matchTable[1][4]---->matchTable[2][4]
		matchTable[0][5]---->matchTable[3][5]
		matchTable[1][5]---->matchTable[2][5]
		matchTable[0][6]---->matchTable[3][6]
		matchTable[1][6]---->matchTable[2][6]
		matchTable[0][7]---->matchTable[3][7]
		matchTable[1][7]---->matchTable[2][7]
		matchTable[0][8]---->matchTable[3][8]
		matchTable[1][8]---->matchTable[2][8]*/
		/*
	}
	if(loacalProceed==4)
	{
		matchTable[0][0]---->matchTable[1][0]
		matchTable[2][0]---->matchTable[3][0]
		matchTable[0][1]---->matchTable[1][1]
		matchTable[2][1]---->matchTable[3][1]
		matchTable[0][2]---->matchTable[1][2]
		matchTable[2][2]---->matchTable[3][2]
		matchTable[0][3]---->matchTable[1][3]
		matchTable[2][3]---->matchTable[3][3]
		matchTable[0][4]---->matchTable[1][4]
		matchTable[2][4]---->matchTable[3][4]
		matchTable[0][5]---->matchTable[1][5]
		matchTable[2][5]---->matchTable[3][5]
		matchTable[0][6]---->matchTable[1][6]
		matchTable[2][6]---->matchTable[3][6]
		matchTable[0][7]---->matchTable[1][7]
		matchTable[2][7]---->matchTable[3][7]
		matchTable[0][8]---->matchTable[1][8]
		matchTable[2][8]---->matchTable[3][8]
	}
	*/

}
