#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include <math.h>
char teamNames[480]={};
char teamNamesandNums[32][40]={};
int matchTable[4][8]={{1324,1323,1311,1101,1104,1312,1303,1322},{4225,2328,4202,3313,2330,2517,4520,3426},{3409,4418,2121,2307,3106,3329,3431,2105},{2132,3214,3308,4419,4327,4216,2310,4215}};
int groupTable[4][8]={};//////this ganna update after one proceed
char selectedTeam[25]={};
int gPlan[32][15]={};
int exitt=0;
int proceed=0;
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
	int wins;
	int losses;
	int draws;
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
void sortTotalPoints(int totalpoint[][2]);
void sortGroups(teams_node * headt);
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
void printGroupTable(int groupTable[][8]);
void totalPointNULL(int totalpoint[][2]);
void groupTableNULL();
void startNewWorldCup();
void loadRecentWorldCup();
void mainMenu(player_node *headp,teams_node * headt);
void loadGrouping(teams_node * head_teams);
void loadPlayersInformationFirstTime();
void playerReadInfo(player_node *pp);
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
void matchControllerGroups(player_node * headp,teams_node * headt,int v);
/////////////////
int goalNumber(double attackPower1, double defencePower2);
int winer(int goal1,int goal2);/////////////////////////////////////to do ***********
int goalzan( int tarkib);
int passgoal(int tarkib);
teams_node * searchTeamForGrouping(teams_node * head_team,const char * teamName);
void writegPlans_MatchTable_selectedTeam();
void writeTeamsInfo(teams_node * headt);
void readgPlans_MatchTable_selectedTeam();
void readTeamsInfo(teams_node * headt);
void updateAllPlayersOutGameFormFitness(player_node * headp,teams_node * headt,const char * teamName1,const char * teamName2);
void updateFormWinnerLoss(player_node * headp,teams_node * headt,const char * teamName,int winner);
void updateFormGoalZan(player_node * headp,teams_node * headt,const char * teamName);
void updateFormGoalKhor(player_node * headp,teams_node * headt,const char * teamName);
void updateIfCleanSheet(player_node * headp,teams_node * headt,const char * teamName);
void fixture();
void mainTable(teams_node * headt);

int main()
{
	srand((unsigned)time(NULL));
	////////////////splash screen
	//clock_t clockk0=clock();
	//while(clock()<clockk0+2000);
	//splash();
	//clockk0=clock();
	//while(clock()<clockk0+3000);
	//system("cls");
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
				loadRecentWorldCup();
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

void loadRecentWorldCup()
{
	FILE *proceeds=fopen("Proceeds.txt","r");
	if(proceeds)
	{
		fscanf(proceeds,"%d",&proceed);
		fclose(proceeds);
		proceeds=NULL;
		FILE *managment1=fopen("teamNames.txt","r");
		char line[5000]={};
		int team=0;
		int i=0;
		while(i<32)
		{
			fscanf(managment1,"%s",teamNamesandNums[i]);
			i++;
		}
		fclose(managment1);
		managment1=NULL;
		////////head of player here !!!!!!!!!!!!!!!!!!!
		player_node *head_player=(player_node *)calloc(1,sizeof(player_node));
		teams_node * head_teams=(teams_node *)calloc(1,sizeof(teams_node));
		playerReadInfo(head_player);
		loadGrouping(head_teams);
		readTeamsInfo(head_teams);
		readgPlans_MatchTable_selectedTeam();
		sortGroups(head_teams);
		mainMenu(head_player,head_teams);
	}
	
}
void startNewWorldCup()
{
	proceed=0;
	/*FILE *result = fopen("ResultOfGroupingGames.txt","w");
	fclose(result);
	result=NULL;												VERY IMPORTANT
	FILE *teamsInfo = fopen("teamsInfo.txt","w");
	fclose(teamsInfo);
	teamsInfo=NULL;
	*/
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
				worldCupnewGrouping=0;
				loadGrouping(head_teams);
				a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				exitt=1;
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
	
	if(!exitt)
	{
	loadGrouping(head_teams);
	selectTeamsToManagement();
	FILE *managment=fopen("teamNames.txt","r");
	int i=0;
	while(i<32)
	{
		fscanf(managment,"%s",teamNamesandNums[i]);
		i++;
	}
	loadPlayersInformationFirstTime(head_player);
	doSkills(head_teams,head_player);
	gamePlan(head_player,head_teams);
	setTempPosts(head_player,head_teams);
	mainMenu(head_player,head_teams);
	//playerWriteInfo(head_player);
	//writegPlans_MatchTable_selectedTeam();
	//readgPlans_MatchTable_selectedTeam();
	}
	
	if(!exitt)
	{
		customization(head_player,head_teams);
		//playerWriteInfo(head_player);
		//writegPlans_MatchTable_selectedTeam();
	}
	
	//if(!exitt)
	//matchControllerGroups(head_player,head_teams);
	
}
void mainMenu(player_node *headp,teams_node * headt)
{
	player_node * pp=(player_node *)calloc(1,sizeof(player_node));
	teams_node * pt=(teams_node *)calloc(1,sizeof(teams_node));
	pp=headp;
	pt = headt;
	int a=1;
	int v=0;
	while(a)
	{
		system("cls");
		puts("\t\t\t\t\t ======= Main Menu =======");
		puts("\n\n");
		puts("\t\tEnter what do you want :");
		puts("\t\t\tlineup\n\t\t\ttable\n\t\t\tfixture\n\t\t\tproceed (number of proceeds)\n\t\t\tsave\n\t\t\texit");
		char *n=(char *)calloc(15,sizeof(char));
		scanf("%s",n);
		if (strcmp(n,"lineup")==0 || strcmp(n,"table")==0 ||strcmp(n,"fixture")==0 || strcmp(n,"proceed")==0  || strcmp(n,"save")==0  || strcmp(n,"exit")==0)
		{
			if(strcmp(n,"lineup")==0)
			{
				system("cls");
				customization(pp,pt);
				//a=0;
			}
			else if(strcmp(n,"table")==0)
			{
				system("cls");	
				mainTable(pt);
				//a=0;
			}
			else if(strcmp(n,"fixture")==0)
			{
				system("cls");
				fixture();
				//a=0;
			}
			else if(strcmp(n,"proceed")==0)
			{
				int w=1;
				scanf("%d",&v);
				while (w)
				{
					if(v<8 && v >0)
					{
						system("cls");
						matchControllerGroups(pp,pt,v);
						w=0;
					}
					else
					{
						printf("proceed needs a 0<number<8 !!!!!");
					}
				}
				
			}
			else if(strcmp(n,"save")==0)
			{
				system("cls");
				playerWriteInfo(pp);
				writeTeamsInfo(pt);
				writegPlans_MatchTable_selectedTeam();
				//a=0;
			}
			else if(strcmp(n,"exit")==0)
			{
				system("cls");
				exitt=1;
				a=0;
			}
		}
		else
		{
			puts("Choose your order from list please!");
		}
		free(n);
		n=NULL;
		
	}
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
				exitt=1;
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
				exitt=1;
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
	if(exitt==0)
	{
		
	
	system("cls");
	printf("\n\n\t\t\t\t ====Customization Substitution form====");
	printf("\n\n\n\tEnter What do you want : (write 'exit' to close the program)");
	printf("\n\n\t1.I don't want Substitutions.");
	printf("\t\t\t2.Change my players in game\n ");
	}
	///////////////save gPlan and balloting
	char np=0;
	if(exitt==0)
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
				puts("Enter any key to continue . . .");
				np=getchar();
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
				exitt=1;
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
		scanf("%d%d",&x,&y);
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
		printf("\n\t\t%3d-%-25s | Skill : %3d | Form : %3d | Fitness : %3d | Main Post : %s | Post : %s |",ppp->number,ppp->name,ppp->skill,ppp->form,ppp->fitness,ppp->mainPost,ppp->tempPost);
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
				printf("\n\t\t%2d-%-25s | Skill : %3d | Form : %3d | Fitness : %3d | Main Post : %s | Post : %s |",ppp->number,ppp->name,ppp->skill,ppp->form,ppp->fitness,ppp->mainPost,ppp->tempPost);
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
	printtable();
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
		free(teamName);
		teamName=NULL;
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
	teams_node *pt=(teams_node *)calloc(1,sizeof(teams_node));///////////////////////*****************
	pt=head_teams;
	//////////////////teams info grouping and ... from file ***********
	teamsReadInfofromGlobal(tt,pt);
	///loadGroupingInfo
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
	clock_t clockk0=0;
	puts("=========================================================================================================================");
	puts("=========================================================================================================================");
	puts("");
	puts("");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("WW           WW           WW    OOOOOOOOOO    RRRRRRRRRR    LL         DDDDDDDD       CCCCCCCCC  UU      UU   PPPPPPPPPP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("  WW       WW  WW        WW     OO      OO    RR      RR    LL         DD      D      CC         UU      UU   PP      PP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("   WW     WW     WW     WW      OO      OO    RR     RR     LL         DD       D     CC         UU      UU   PP      PP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("    WW   WW       WW   WW       OO      OO    RRRRRRRR      LL         DD      D      CC         UU      UU   PPPPPPPPP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("     WW WW         WW WW        OO      OO    RR     RR     LL         DD     D       CC         UU      UU   PP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("      WW             WW         OOOOOOOOOO    RR      RR    LLLLLLLL   DDDDDDD        CCCCCCCCC  UUUUUUUUUU   PP");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("");
	puts("");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("=========================================================================================================================");
	puts("");
	puts("");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                        2222222222222   0000000000000  11   8888888888888");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                                   22   00         00  11   88         88");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                                   22   00         00  11   88         88");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                        2222222222222   00         00  11   8888888888888");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                        22              00         00  11   88         88");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                        22              00         00  11   88         88");
	clockk0=clock();
	while(clock()<clockk0+300);
	puts("                        2222222222222   0000000000000  11   8888888888888");
	clockk0=clock();
	while(clock()<clockk0+300);
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
void fixture()
{
	system("cls");
	FILE *results=fopen("ResultOfGroupingGames.txt","r");
	char line[2000]={};
	int counter=0;
	int r=0;
	int j=0;
	int t=0;
	for(int f=0;fgets(line,2000,results)!=NULL;f++)
	{
		counter=0;
		r=0;
		char *strTemp=(char *)calloc (30,sizeof(char));
		strcpy(strTemp,"q");
		for(int g=0;strcmp(strTemp,"");g++)
		{
			strcpy(strTemp,"");
			fscanf(results,"%s",strTemp);
			if(counter == 5&&(strcmp(strTemp,"A")==0 || strcmp(strTemp,"B")==0 ||strcmp(strTemp,"C")==0 ||strcmp(strTemp,"D")==0 ||strcmp(strTemp,"E")==0 ||strcmp(strTemp,"F")==0 ||strcmp(strTemp,"G")==0 ||strcmp(strTemp,"H")==0))
			{
				counter=0;
			}
			
			if(counter ==0&&strcmp(strTemp,""))
			{
				printf("\t\t\t\t\t\t%s\n",strTemp);
				r=1;
			}
			if(counter ==1 && strcmp(strTemp,""))
			printf("\t\t\t\t\t\t%-16s",strTemp);
			if(counter ==2 && strcmp(strTemp,""))
			printf("  %s",strTemp);
			if(counter ==3 && strcmp(strTemp,""))
			printf(" VS %s",strTemp);
			if(counter ==4&&strcmp(strTemp,""))
			printf("  %16s\n",strTemp);////
			if(counter ==5&&strcmp(strTemp,""))
			printf("\t\t\t\t\t\tGoal Scorer :%s.",strTemp);
			if(counter ==6&&strcmp(strTemp,""))
			printf("%s\n",strTemp);
			if(counter ==7&&strcmp(strTemp,""))
			printf("\t\t\t\t\t\tAssist :%s.",strTemp);
			if(counter ==8&&strcmp(strTemp,""))
			{
				printf("%s\n",strTemp);
				counter=4;
			}
			counter++;
		}
		//////A Russia 1 0 SaudiArabia 9 F.Smolov 8 D.Glushakov 
		free(strTemp);
		strTemp=NULL;
	}
	puts("Enter any key to continue . . .");
	char *temp=(char *)calloc(10,sizeof(char));
	scanf("%s",temp);
	fclose(results);
	results=NULL;
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
		sprintf(integer_string, "\n%d %s %d %s %s %s %d %d %d %d %d", p->number,p->name,p->age,p->nation,p->mainPost,p->tempPost,p->skill,p->form,p->fitness,p->goals,p->passGoals);
		strcat(playersInformations, integer_string); 
		p = p->next;
	}
	fprintf(playersdata,"%s",playersInformations);
	fclose(playersdata);
	playersdata=NULL;
}
void playerReadInfo(player_node *pp)
{
		
	FILE *playersdata=fopen("recentWorldCupPlayersInfo.txt","r");
	player_node *p = (player_node*)calloc(1,sizeof(player_node));
	p=pp;
	char tempString[150]={};
	int counter=0;
	for(int i=0;fgets(tempString,150,playersdata)!=NULL && counter!=32;i++)
	{
		
		fscanf(playersdata, "%d%s%d%s%s%s%d%d%d%d%d", &p->number,p->name,&p->age,p->nation,p->mainPost,p->tempPost,&p->skill,&p->form,&p->fitness,&p->goals,&p->passGoals);
		p->next = (player_node *)calloc(1, sizeof(player_node));
		p = p->next;
	}
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
void writegPlans_MatchTable_selectedTeam()
{
	FILE *write = fopen("plansInfo.txt","w");
	char *gplans_matchTable_selectedTeamInformations=(char *)calloc (2000,sizeof(char));
	char integer_string[30]={};
	for(int i=0;i<32;i++){
		for(int j=0;j<15;j++)
		{
			char integer_string[30]={};
			sprintf(integer_string, "%d ",gPlan[i][j]);
			strcat(gplans_matchTable_selectedTeamInformations, integer_string); 
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<8;j++)
		{
			char integer_string[30]={};
			sprintf(integer_string, "%d ",matchTable[i][j]);
			strcat(gplans_matchTable_selectedTeamInformations, integer_string);
		}
	}
	////64 digit
	strcat(gplans_matchTable_selectedTeamInformations, selectedTeam);
	fprintf(write,"%s",gplans_matchTable_selectedTeamInformations);
	fclose(write);
	write=NULL;
}
void writeTeamsInfo(teams_node * headt)
{
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	pt =headt;
	FILE *teamsInfo = fopen("teamsInfo.txt","w");
	char *TeamInformations=(char *)calloc (2000,sizeof(char));
	char tempString[80]={};
	while(pt)
	{
		sprintf(tempString, "\n%s %s %d %s %d %d %d %d %d %d %d",pt->teamName,pt->group,pt->state,pt->confed,pt->seed,pt->pointOfteam,pt->goalsRecev,pt->goalsScoerds,pt->wins,pt->losses,pt->draws);
		strcat(TeamInformations, tempString);
		pt=pt->next;
	}
	fprintf(teamsInfo,"%s",TeamInformations);
	fclose(teamsInfo);
	teamsInfo=NULL;
}
void readTeamsInfo(teams_node * headt)
{
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	pt =headt;
	FILE *teamsInfo = fopen("teamsInfo.txt","r");
	char tempString[100]={};
	int counter=0;
	for(int i=0;fgets(tempString,100,teamsInfo)!=NULL && counter!=32;i++)
	{
		fscanf(teamsInfo,"%s%s%d%s%d%d%d%d%d%d%d",pt->teamName,pt->group,&pt->state,pt->confed,&pt->seed,&pt->pointOfteam,&pt->goalsRecev,&pt->goalsScoerds,&pt->wins,&pt->losses,&pt->draws);
		counter++;
		pt->next=(teams_node *)calloc(1,sizeof(teams_node));
		pt = pt -> next;
	}
	fclose(teamsInfo);
	teamsInfo=NULL;	
}
void readgPlans_MatchTable_selectedTeam()
{
	FILE *read = fopen("plansInfo.txt","r");
	char teamName[30]={};
	for(int q=0;q<32;q++){
		for(int w=0;w<15;w++)
		{
			fscanf(read,"%d",&gPlan[q][w]);
		}
	}
	for(int q=0;q<4;q++){
		for(int w=0;w<8;w++)
		{
			fscanf(read,"%d",&matchTable[q][w]);
		}
	}
	fscanf(read,"%s",teamName);
	strcpy(selectedTeam,teamName);
	fclose(read);
	read=NULL;
}
void matchControllerGroups(player_node * headp,teams_node * headt,int proc)
{
	FILE *proceeds=fopen("Proceeds.txt","r");
	fscanf(proceeds,"%d",&proceed);
	fclose(proceeds);
	proceeds=NULL;
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	teams_node * ppt = (teams_node *)calloc(1,sizeof(teams_node));
	pt =headt;
	pp = headp;
	int goalsofTeam1=0;
	int goalsofTeam2=0;
	int golzanNum=0;
	int passGoalNum=0;
		////////////////writing on file result Of grouping games
		FILE *results=fopen("ResultOfGroupingGames.txt","a");
		char *resultsInformation=(char *)calloc (1500,sizeof(char));
		//sortGroups(pt);
		//strcat(resultsInformation,"\n");
		char tempStr[40]={};
		int t=0;
		int j=0;
		int x = proceed;
		int n = proc;
		/////////////////
	for(int f=0;n!=0;f++)
	{
	if(x==0)
	{
		
		x++;
		FILE *results=fopen("ResultOfGroupingGames.txt","a");
		char *resultsInformation=(char *)calloc (1500,sizeof(char));
		//sortGroups(pt);
		strcat(resultsInformation,"\n");
		char tempStr[40]={};
		for(int i=-1;j<32;t++,j+=2)
		{
			if(t%2==0)
			{
				i++;
			}
		goalsofTeam1=goalNumber(gPlan[matchTable[j%4][i]%100-1][13],gPlan[matchTable[(j+1)%4][i]%100-1][12]);
		goalsofTeam2=goalNumber(gPlan[matchTable[(j+1)%4][i]%100-1][13],gPlan[matchTable[j%4][i]%100-1][12]);
		printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[j%4][i]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(j+1)%4][i]%100-1],goalsofTeam2);
		///////update from and fitness all players of two teams that thay are in game ----> for two teams -10 fitness is in game OK
		///############################### form & fitness is Update ########################
		updateAllPlayersOutGameFormFitness(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
		//////winner +5 form all of players is in game ////  loser -1 form all of players in game
		//////teams that have no receved goals goaler +5 foem & all of Deffenders +3 form
		if(goalsofTeam1==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		}
		else if(goalsofTeam2==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
		}
		
		if(goalsofTeam1!=goalsofTeam2)
		{
			if(goalsofTeam1>goalsofTeam2)
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
				ppt->losses++;
			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->losses++;
			}
			
		}
		else
		{
			ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],2);
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1],2);
		}
		ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam1;
		ppt->goalsRecev+=goalsofTeam2;
		ppt= search_team(pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam2;
		ppt->goalsRecev+=goalsofTeam1;
		///////////////////////////////
		sprintf(tempStr,"%s ",ppt->group);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[j%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam1);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam2);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		//group teamname1 goalsofTeam1 goalsofTeam2 teamname2 golzan1 passgoal1 golzane2 passgole2
		///////////////////////////////
		while(goalsofTeam1)
		{
			
			golzanNum=goalzan(gPlan[matchTable[j%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[j%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam1--;
		
		}
		while(goalsofTeam2)
		{
			golzanNum=goalzan(gPlan[matchTable[(j+1)%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[(j+1)%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+1)%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+1)%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[(j+1)%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam2--;
		}
		if(j<30)
		strcat(resultsInformation,"\n");
		fprintf(results,"%s",resultsInformation);
		strcpy(resultsInformation,"");	
		}
		fclose(results);
		results=NULL;
		//writeTeamsInfo(pt);
		//playerWriteInfo(pp);
		sortGroups(pt);
		//start_Proceed++;
	}
	else if (x==1)
	{
		x++;
		FILE *results1=fopen("ResultOfGroupingGames.txt","a");
		char *resultsInformation=(char *)calloc (1500,sizeof(char));
		strcat(resultsInformation,"\n");
		char tempStr[40]={};
		//////proceed2
		j=-1;
		t=0;
		for(int i=-1;t<16;t++,j+=1)
		{
			if(t%2==0)
			{
				i++;
				j++;
			}
		
		
		goalsofTeam1=goalNumber(gPlan[matchTable[j%4][i]%100-1][13],gPlan[matchTable[(j+2)%4][i]%100-1][12]);
		goalsofTeam2=goalNumber(gPlan[matchTable[(j+2)%4][i]%100-1][13],gPlan[matchTable[j%4][i]%100-1][12]);
		printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[j%4][i]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(j+2)%4][i]%100-1],goalsofTeam2);
		///////update from and fitness all players of two teams that thay are in game ----> for two teams -10 fitness is in game OK
		///############################### form & fitness is Update ########################
		updateAllPlayersOutGameFormFitness(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
		//////winner +5 form all of players is in game ////  loser -1 form all of players in game
		//////teams that have no receved goals goaler +5 foem & all of Deffenders +3 form
		if(goalsofTeam1==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		}
		else if(goalsofTeam2==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
		}
		
		if(goalsofTeam1!=goalsofTeam2)
		{
			if(goalsofTeam1>goalsofTeam2)
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
				ppt->losses++;
			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->losses++;
			}
			
		}
		else
		{
			ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			ppt= search_team(pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],2);
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1],2);
		}
		ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam1;
		ppt->goalsRecev+=goalsofTeam2;
		ppt= search_team(pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam2;
		ppt->goalsRecev+=goalsofTeam1;
		///////////////////////////////
		sprintf(tempStr,"%s ",ppt->group);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[j%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam1);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam2);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		//group teamname1 goalsofTeam1 goalsofTeam2 teamname2 golzan1 passgoal1 golzane2 passgole2
		///////////////////////////////
		while(goalsofTeam1)
		{
			
			golzanNum=goalzan(gPlan[matchTable[j%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[j%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam1--;
		
		}
		while(goalsofTeam2)
		{
			golzanNum=goalzan(gPlan[matchTable[(j+2)%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[(j+2)%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+2)%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+2)%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[(j+2)%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam2--;
			}
			if(j<22)
			strcat(resultsInformation,"\n");
			fprintf(results,"%s",resultsInformation);
			strcpy(resultsInformation,"");
			
			
		}
		fclose(results);
		results=NULL;
		//writeTeamsInfo(pt);
		//playerWriteInfo(pp);
		sortGroups(pt);
		//start_Proceed++;
	}
	else if (x==2)
	{
		x++;
		FILE *results1=fopen("ResultOfGroupingGames.txt","a");
		char *resultsInformation=(char *)calloc (1500,sizeof(char));
		
		strcat(resultsInformation,"\n");
		char tempStr[40]={};
		
		t=0;
		j=0;
		for(int i=-1;t<16;t++,j+=2)
		{
			if(t%2==0)
			{
				i++;
			}
		
		
		goalsofTeam1=goalNumber(gPlan[matchTable[j%4][i]%100-1][13],gPlan[matchTable[(j+3)%4][i]%100-1][12]);
		goalsofTeam2=goalNumber(gPlan[matchTable[(j+3)%4][i]%100-1][13],gPlan[matchTable[j%4][i]%100-1][12]);
		printf ("\nteam1 = %s   %d   VS    team2= %s  %d",teamNamesandNums[matchTable[j%4][i]%100-1],goalsofTeam1,teamNamesandNums[matchTable[(j+3)%4][i]%100-1],goalsofTeam2);
		///////update from and fitness all players of two teams that thay are in game ----> for two teams -10 fitness is in game OK
		///############################### form & fitness is Update ########################
		updateAllPlayersOutGameFormFitness(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
		//////winner +5 form all of players is in game ////  loser -1 form all of players in game
		//////teams that have no receved goals goaler +5 foem & all of Deffenders +3 form
		if(goalsofTeam1==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		}
		else if(goalsofTeam2==0)
		{
			updateIfCleanSheet(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
		}
		
		if(goalsofTeam1!=goalsofTeam2)
		{
			if(goalsofTeam1>goalsofTeam2)
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
				ppt->losses++;
			}
			else
			{
				ppt= search_team(pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
				ppt->pointOfteam+=3;
				ppt->wins++;
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1],1);
				updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],0);
				ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
				ppt->losses++;
			}
			
		}
		else
		{
			ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			ppt= search_team(pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
			ppt->pointOfteam+=1;
			ppt->draws++;
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1],2);
			updateFormWinnerLoss(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1],2);
		}
		ppt= search_team(pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam1;
		ppt->goalsRecev+=goalsofTeam2;
		ppt= search_team(pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
		ppt->goalsScoerds+=goalsofTeam2;
		ppt->goalsRecev+=goalsofTeam1;
		///////////////////////////////
		sprintf(tempStr,"%s ",ppt->group);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[j%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam1);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%d ",goalsofTeam2);
		strcat(resultsInformation,tempStr);
		sprintf(tempStr,"%s ",teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
		strcat(resultsInformation,tempStr);
		//group teamname1 goalsofTeam1 goalsofTeam2 teamname2 golzan1 passgoal1 golzane2 passgole2
		///////////////////////////////
		while(goalsofTeam1)
		{
			
			golzanNum=goalzan(gPlan[matchTable[j%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[j%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[j%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[j%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam1--;
		
		}
		while(goalsofTeam2)
		{
			golzanNum=goalzan(gPlan[matchTable[(j+3)%4][i]%100-1][11]);
			passGoalNum=passgoal(gPlan[matchTable[(j+3)%4][i]%100-1][11]);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+3)%4][i]%100-1][golzanNum],teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
			ppp->goals+=1;
			if(ppp->form<99)
			ppp->form+=2;
			updateFormGoalZan(pp,pt,teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
			updateFormGoalKhor(pp,pt,teamNamesandNums[matchTable[j%4][i]%100-1]);
			//printf("\ngoal Zan :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			ppp=search_playerNumber_teams(pp,gPlan[matchTable[(j+3)%4][i]%100-1][passGoalNum],teamNamesandNums[matchTable[(j+3)%4][i]%100-1]);
			ppp->passGoals+=1;
			if(ppp->form<100)
			ppp->form+=1;
			//printf("\npass Goale :%d.%s",ppp->number,ppp->name);
			sprintf(tempStr,"%d %s ",ppp->number,ppp->name);
			strcat(resultsInformation,tempStr);
			goalsofTeam2--;
			}
			if(j<30)
			strcat(resultsInformation,"\n");
			fprintf(results,"%s",resultsInformation);
			strcpy(resultsInformation,"");
			
			
		}
		fclose(results);
		results=NULL;
		//writeTeamsInfo(pt);
		//playerWriteInfo(pp);
		sortGroups(pt);
	}
		
	n--;
	}
	FILE *proceedss=fopen("Proceeds.txt","w");
	fprintf(proceedss,"%d",proceed+proc);
	fclose(proceedss);
}

void updateAllPlayersOutGameFormFitness(player_node * headp,teams_node * headt,const char * teamName1,const char * teamName2)
{
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	pt = headt;
	ppp=pp;
	while (ppp && pp)
	{
		ppp=search_post_temp(pp,"N",teamName1);
		if(ppp)
		{
			ppp->fitness=100;
			if(ppp->form>1)
			ppp->form-=2;
			pp=ppp->next;
		}
		
	}
	pp=headp;
	ppp=pp;
	while (ppp && pp)
	{
		ppp=search_post_temp(pp,"N",teamName2);
		if(ppp)
		{
			ppp->fitness=100;
			if(ppp->form>1)
			ppp->form-=2;
			pp=ppp->next;
		}
	}
	
}
void updateFormWinnerLoss(player_node * headp,teams_node * headt,const char * teamName,int winner)
{
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	pt = headt;
	ppp=pp;
	if(winner)
	{
		///////goaler
		ppp=search_post_temp(pp,"G",teamName);
		if(ppp->fitness>10)
		ppp->fitness-=10;
		if(ppp->form<96)
		ppp->form+=5;
		pp=headp;
		ppp=pp;
		//////def
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"D",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=5;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"M",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=5;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"A",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=5;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
	}
	else if (winner==0)
	{
		///////goaler
		ppp=search_post_temp(pp,"G",teamName);
		if(ppp->fitness>10)
		ppp->fitness-=10;
		if(ppp->form>0)
		ppp->form-=1;
		pp=headp;
		ppp=pp;
		//////def
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"D",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form>0)
				ppp->form-=1;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"M",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form>0)
				ppp->form-=1;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"A",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form>0)
				ppp->form-=1;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		
	}
	else if(winner==2)
	{
		ppp=search_post_temp(pp,"G",teamName);
		if(ppp->fitness>10)
		ppp->fitness-=10;
		if(ppp->form<96)
		ppp->form+=2;
		pp=headp;
		ppp=pp;
		//////def
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"D",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=2;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"M",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=2;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		while (ppp && pp)
		{
			ppp=search_post_temp(pp,"A",teamName);
			if(ppp)
			{
				if(ppp->fitness>10)
				ppp->fitness-=10;
				if(ppp->form<96)
				ppp->form+=2;
				pp=ppp->next;
			}
		}
		pp=headp;
		ppp=pp;
		
	}
	
	
}
void updateFormGoalZan(player_node * headp,teams_node * headt,const char * teamName)
{
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	pt = headt;
	ppp=pp;
	while (ppp && pp)
	{
		ppp=search_post_temp(pp,"A",teamName);
		if(ppp)
		{
			if(ppp->form<99)
			ppp->form+=2;
			pp=ppp->next;
		}
	}
	
}
void updateIfCleanSheet(player_node * headp,teams_node * headt,const char * teamName)
{
	
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	pt = headt;
	ppp=pp;
	ppp=search_post_temp(pp,"G",teamName);
	if(ppp->form<96)
	ppp->form+=5;
	pp=headp;
	pt = headt;
	ppp=pp;
	while (ppp && pp)
	{
		ppp=search_post_temp(pp,"D",teamName);
		if(ppp)
		{
			if(ppp->form<98)
			ppp->form+=3;
			pp=ppp->next;
		}
	}
	
}
void updateFormGoalKhor(player_node * headp,teams_node * headt,const char * teamName)
{
	player_node * pp = (player_node *)calloc(1,sizeof(player_node));
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	player_node * ppp = (player_node *)calloc(1,sizeof(player_node));
	pp=headp;
	pt = headt;
	ppp=pp;
	ppp=search_post_temp(pp,"G",teamName);
	if(ppp->form>2)
	ppp->form-=3;
	pp=headp;
	ppp=pp;
	while (ppp && pp)
	{
		ppp=search_post_temp(pp,"D",teamName);
		if(ppp)
		{
			if(ppp->form>1)
			ppp->form-=2;
			pp=ppp->next;
		}
	}
	
}
void showResultOfGroupGames()
{
	
}
void sortGroups(teams_node * headt)
{
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	teams_node * ppt= (teams_node *)calloc(1,sizeof(teams_node));
	pt = headt;
	int totalpoint[4][2]={};
	groupTableNULL();
	totalPointNULL(totalpoint);
	//totalpoint[j][0]--->number of team totalpoint[j][1] ---->totalpoint
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<4;j++)
		{
		ppt=search_team(pt,teamNamesandNums[matchTable[j][i]%100-1]);
		totalpoint[j][0]=matchTable[j][i]%100-1;
		totalpoint[j][1]=ppt->pointOfteam*10000 + (ppt->goalsScoerds - ppt->goalsRecev)*100 +ppt->goalsScoerds;
		
		}
		sortTotalPoints(totalpoint);
		for(int r=0;r<4;r++)
		{
			groupTable[r][i]=totalpoint[r][0];
		}
	}
	printGroupTable(groupTable);
}
void groupTableNULL()
{
	for(int i=0;i<4;i++)
	{
		for (int j=0;j<8;j++)
		{
			groupTable[i][j]=0;
		}
	}
}
void totalPointNULL(int totalpoint[][2])
{
	for(int i=0;i<4;i++)
	{
		for (int j=0;j<2;j++)
		{
			totalpoint[i][j]=0;
		}
	}
}
void printGroupTable(int groupTable[][8])
{
	puts("");
	for(int i=0;i<4;i++)
	{
		for (int j=0;j<8;j++)
		{
			printf("%2d ",groupTable[i][j]);
		}
		puts("");
	}
}
void mainTable(teams_node * headt)
{
	teams_node * pt = (teams_node *)calloc(1,sizeof(teams_node));
	teams_node * ppt = (teams_node *)calloc(1,sizeof(teams_node));
	pt = headt;
	ppt=pt;
	/*
	typedef struct teams{
	char teamName[15];
	char group[2];
	int state;
	char confed[15];
	int seed;
	int pointOfteam;
	int goalsRecev;
	int goalsScoerds;
	int wins;
	int losses;
	int draws;
	struct teams *next;
}teams_node;
*/
	puts("\t\t\t\t\t ===== Main Table =====");
	puts("==============================================================================================================================");
	printf(" Group |        Team Name        | Games | Wins | Draws | Losses | Goals Scoerd | Goals Receved | Goal Difference | Score \n");
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<4;j++)
		{
			ppt=search_team(pt,teamNamesandNums[groupTable[j][i]]);
			printf("%-7s|%-25s|%-7d|%-6d|%-7d|%-8d|%-14d|%-15d|%-17d|%-7d\n",ppt->group,ppt->teamName,ppt->wins + ppt->losses + ppt->draws ,ppt->wins , ppt->draws , ppt->losses , ppt->goalsScoerds , ppt->goalsRecev,ppt->goalsScoerds-ppt->goalsRecev,ppt->pointOfteam);
		}
		puts("==============================================================================================================================");
	}
	puts("Enter any key to continue . . .");
	char *temp=(char *)calloc(10,sizeof(char));
	scanf("%s",temp);
}
void sortTotalPoints(int totalpoint[][2])
{
	int temp1=0,temp2=0;
	for(int i=0;i<4;i++)
	{
		for (int j=0;j<3;j++)
		{
			if(totalpoint[j][1]<totalpoint[j+1][1])
			{
				temp1=totalpoint[j][1];
				temp2=totalpoint[j][0];
				totalpoint[j][1]=totalpoint[j+1][1];
				totalpoint[j][0]=totalpoint[j+1][0];
				totalpoint[j+1][1]=temp1;
				totalpoint[j+1][0]=temp2;
			}
		}
	}
	
}
