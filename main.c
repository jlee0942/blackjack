#include <stdio.h>
#include <stdlib.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30



//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int i;	
	 
//real number of the card
for(i=0;i<(N_CARDSET*N_CARD);i++)

	do{
	{
	if (i%N_MAX_CARDNUM ==0)
		detAce();							//function determining whether ace should be 1 or11	
	else if (i%N_MAX_CARDNUM == 1)
		CardTray[i]=2;
	else if (i%N_MAX_CARDNUM == 2)
		CardTray[i]=3;
	else if (i%N_MAX_CARDNUM == 3)
		CardTray[i]=4;
	else if (i%N_MAX_CARDNUM == 4)
		CardTray[i]=5;
	else if (i%N_MAX_CARDNUM == 5)
		CardTray[i]=6;
	else if (i%N_MAX_CARDNUM == 6)
		CardTray[i]=7;
	else if (i%N_MAX_CARDNUM == 7)
		CardTray[i]=8;
	else if (i%N_MAX_CARDNUM == 8)
		CardTray[i]=9;
	else 
		CardTray[i]=10 ;
	}}while(i>=N_CARDSET*N_CARD);
	
	return CardTray[i];

}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
		
	printf("%i", CardTray[cardnum]);
			
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i,n;
	int temp;
	int *cardmix = CardTray;				//in order to randomly mix cards

	for(i=0;i<=(N_CARDSET*N_CARD);i++)
	{
		n=rand()%(N_CARDSET*N_CARD);
		temp=cardmix[i];
		cardmix[i]=cardmix[n];
		cardmix[n]=temp;				
		
	}
	return cardmix;
}

//get one card from the tray_get card index number gradually
int pullCard(void) {
	
	cardIndex++;
	
	if (cardIndex>N_CARDSET*N_CARD)
		gameEnd=1;
		return gameEnd;
	else
		return cardIndex-1;
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {

	do{
	
		printf("input the number of players(max:%d):", N_MAX_USER);
		n_user=getIntegerInput();
 
		if(n_user<=0)		//when input isn't integer or less than 1
		{	
			printf("invalid!\n");		
		}
		else if(n_user>5)	//when input exceeds max num
		{
			printf("too many!\n");
		}
	}while((n_user>5)||(n_user<=0));
	printf(" --> card is mixed and put into the tray");
	
	return n_user;
		
}


//betting
int betDollar(void) {

	int i;	//i for func'for' 
	int n;	//n for random betting
	
	printf("-------------BETTING STEP-------------\n" );
	
	do{
		printf("your betting(total :$%i):", dollar[0] );
		bet[0]=getIntegerInput(); 
			if(bet[0]<=0)		//when input isn't integer or less than 1
			{	
				printf("invalid!\n");		
			}
			else if(bet[0]>dollar[0])	//when input exceeds max num
			{
				printf("too many!\n");
			}
	}while((bet[0]<=0)||(bet[0]>dollar[0]));
	

	for (i=1;i<n_user;i++)
	{
		n=rand()%(dollar[i]+1);
		bet[i]=bet[n];
		printf("player%i bets %i(out of $%i)\n", i, bet[i] , dollar[i]);
	}
	
}


//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players(you->user1->user2->dealer->you->user1->...->dealer)
	for (i=0;i<=n_user;i++)
	{
		cardhold[i][0] = pullCard();
	}
	
	for (i=0;i<=n_user;i++)
	{
		cardhold[i][1] = pullCard();
	}

	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
	int i;			//for 'for'
	
	printf("\n---------------CARD OFFERING---------------\n");
	printf("---Dealer	: 	X		%i\n", CardTray(cardhold[n_user][1]));
	printf("-->You		:	%i		%i\n",	CardTray(cardhold[0][0]), CardTray(cardhold[0][1]));	
	
	for(i=1;i<n_user;i++)
	{
			printf("-->Playeri	:	%i		%i\n",	CardTray(cardhold[i][0]), CardTray(cardhold[i][1]));	

	}	
}

int getAction(void) {
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
	

	roundIndex++;

}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	int i;
	
	for(i=0; i<n_user ; i++) 
	{	
		dollar[i]=N_DOLLAR;
	}
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for (i=0;i<=n_user;i++) //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
