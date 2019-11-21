#include <stdio.h>
#include <stdlib.h>
#include "header.h"





//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users
int ifBJack[N_MAX_USER+1];				//save '1' if player, dealer blackjack

//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag
int endturn=0;								//end each player's turn
int roundIndex = 0;							//roundnumber

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

int initialCardInfo(void)
{
	int i;
	
	for (i=0;i<(N_CARDSET*N_CARD);i++)
		CardTray[i]=i;
	
	return CardTray[i];
}


//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	
	int i=cardnum;
	int n=N_MAX_CARDNUM;


	if (i%n==0)
		return 1;				
	else if (i%n == 1)
		return 2;
	else if (i%n == 2)
		return 3;
	else if (i%n == 3)
		return 4;
	else if (i%n == 4)
		return 5;
	else if (i%n == 5)
		return 6;
	else if (i%n == 6)
		return 7;
	else if (i%n == 7)
		return 8;
	else if (i%n == 8)
		return 9;
	else 
		return 10;

}


//print the card information (e.g. DiaA)
int printCard(int cardnum){

	int i=(N_MAX_CARDNUM*N_CARDSET);
	int n=getCardNum(cardnum);
	
	if (cardnum/i==0)
	{
		if (cardnum%i==0)
			printf("Dia A\t");	
		else if(cardnum%i==10)
			printf("Dia J\t");
		else if(cardnum%i==11)
			printf("Dia Q\t");
		else if(cardnum%i==12)
			printf("Dia K\t");
		else
			printf("Dia %d\t", n);
	}
	else if (cardnum/i==1)
		{
		if (cardnum%i==0)
			printf("Hrt A\t");
		else if(cardnum%i==10)
			printf("Hrt J\t");
		else if(cardnum%i==11)
			printf("Hrt Q\t");
		else if(cardnum%i==12)
			printf("Hrt K\t");
		else
			printf("Hrt %d\t", n);
	}
	else if (cardnum/i==2)
			{
		if (cardnum%i==0)
			printf("Spd A\t");
		else if(cardnum%i==10)
			printf("Spd J\t");
		else if(cardnum%i==11)
			printf("Spd Q\t");
		else if(cardnum%i==12)
			printf("Spd K\t");
		else
			printf("Spd %d\t", n);
	}
	else
	{
		if (cardnum%i==0)
			printf("Clb A\t");
		else if(cardnum%i==10)
			printf("Clb J\t");
		else if(cardnum%i==11)
			printf("Clb Q\t");
		else if(cardnum%i==12)
			printf("Clb K\t");
		else
			printf("Clb %d\t", n);
	}
	return;

}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	
	initialCardInfo();
	
	int i,n;
	int temp;
	int *cardmix = CardTray;				//in order to randomly mix cards

	for(i=0;i<(N_CARDSET*N_CARD);i++)
	{
		n=rand()%(N_CARDSET*N_CARD);		//haven't solved overlapping prob.
		temp=cardmix[i];
		cardmix[i]=cardmix[n];
		cardmix[n]=temp;				
		
	}
	return 0;
}

//get one card from the tray_get&increase card index number gradually
int pullCard(void) {
	
	cardIndex++;
	
	if (cardIndex>=N_CARDSET*N_CARD)
	{
		gameEnd=1;					//no card left
		return gameEnd;
	}
	else
	{
		printf("(%i)", CardTray[cardIndex-1]);
		return CardTray[cardIndex-1];
	}
	
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
	

	printf("----------BETTING STEP----------\n" );
	
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
		n=rand()%(N_MAX_BET)+1;
		bet[i]=n;
		printf("player%i bets $%i(out of $%i)\n", i, bet[i] , dollar[i]);
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
	printf("-->Dealer	: 	X\t");	
	printCard(cardhold[n_user][1]);
	printf("\n-->You		:	");	
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);	

	for(i=1;i<n_user;i++)
	{
			printf("\n-->Player%i	:	",i);	
			printCard(cardhold[i][0]);
			printCard(cardhold[i][1]);	

	}	
}


int getAction(void){
	
	printf("Action? (0 - go, others - stay) :");
	
	if (getIntegerInput()!= 0)
	{
		printf("(sum:%i)", cardSum[0]);
		endturn++;
	}	
	else
	{
		return ;
	}
}

void printUserCardStatus(int user, int cardcnt) {
	
	int i;
	
	if(cardcnt==1)
	{
		if (user==0)
		{
			printf("\n\n>>>my turn!-------------------");
		}
		else if (user<n_user)
		{
			printf("\n\n>>>player%i turn!-------------------", user);
		}
		else
		{
			printf("\n\n>>> dealer turn! -------------------");
		}	
	}
	
	printf("\n   -> card : ");

	for (i=0;i<=cardcnt;i++)
	{
		printCard(cardhold[user][i]);
	}
		printf("\t ::: ");
}

int calcStepResult(int user, int cardcnt) {					//overflow or player blackjack ->calculate dollar left
	
	//calculate current cardSum
	int i;
	
	cardSum[user]=0;		//initialize cardSum
	for(i=0;i<=cardcnt;i++)
	{
		cardSum[user]+=getCardNum(cardhold[user][i]);		//add all cardholds when this function works
		if (getCardNum(cardhold[user][i])==1)				//determine number of Ace
		{
			if ( (21-cardSum[user]) >= 10 )	
			{			
				cardSum[user]=cardSum[user]+10;
			
				if( cardSum[user]>21 )
				{
					cardSum[user]=cardSum[user]-10;
				}
			}
		}
	}
	
	
	//decide action by usertypes
	if (user!=0)	//not your turn,  player&dealer's turn
		{
			if (cardSum[user]<17)
			{
				printf("GO!");
				cardhold[user][cardcnt+1]=pullCard();	//get card from tray
			}
			else if(cardSum[user]>21)					//if cardsum -> overflow
			{
				printf("DEAD!(sum:%i)", cardSum[user]);	
			
				if(user<n_user)
				{
					dollar[user]-=bet[user];				//lose 
					printf("	-$%i (%i)", bet[user], dollar[user]);
				}
				return ;
			}
			else					//over 17 under(equal) 21
			{
				printf("STAY!(sum:%i)", cardSum[user]);
				
				if(cardSum[user]==21)
				{
					if (cardcnt==1)
					{
						ifBJack[user]=1;
						printf("BLACKJACK!");
						if(user<n_user)						//player blackjack
						{				
							dollar[user]+=(2*bet[user]);		//blackjack -> win &earn twice
						}
					
					}
				/*	else
					{
						if(user<n_user)
						{
							dollar[user]+=bet[user];		//not blackjack but earn betting
						}
					}
					/*
					for(i=0; i<n_user;i++)
						if(cardSum[i]==21 && cardcnt!=1)		//non-blackjack players lose
						{
							dollar[user]-=bet[user];	
						}
					*/
				}
				
				endturn++;		//end player's turn	
			}
		}
	else		// your turn
		{
			if (cardSum[0]==21)
			{	
				if(cardcnt==1)		//when you did nothing after initial card offering
				{
					ifBJack[user]=1;
					printf("BLACKJACK!");
					dollar[user]+=(2*bet[user]);	//blackjack ->win, you earn more money
				}
				else
				{
					printf("STAY!");	//end turn when your cardSum gets 21 & not blackjack
					endturn++;
				}
			}
			else if (cardSum[0]>21)
			{
				printf("DEAD!(sum: %i)", cardSum[0]);	//you die;
				dollar[user]-=bet[user];				//you lose money
				printf("	-$%i (%i)", bet[user], dollar[user]);	
			}
			
		}	//if cardSum[0]<21 end calcStepResult and go to getAction
				
		return ;
}





int checkResult(void){			//how to deal with overflow??_unsolved 
	
	int i;
	
	printf("\n[[[[[[dealer's result is........%i]]]]]]\n", cardSum[n_user]);
	printf("\n----result of ROUND %i---------------------------\n", roundIndex);	
	for(i=0;i<n_user;i++)
	{
			
		if (cardSum[n_user]>21)		//dealer overflow
		{	
			
				if(cardSum[i]<21)	//player not overflow
		 		{
	 				dollar[i]+=bet[i];
		 		}
				else if (cardSum[i]==21 && ifBJack[i]==0)
				{
	 				dollar[i]+=bet[i];
				}
		}
		
	
		else if (cardSum[n_user]<21)		//dealer not overflow & not 21
		{		
			if(cardSum[i]<cardSum[n_user])	//player lose
		 	{
	 			dollar[i]-=bet[i];
	 		}
			else if (cardSum[i]>=cardSum[n_user])	//player win
			{
				if(cardSum[i]!=21)
				{
	 				dollar[i]+=bet[i];			
				}
				else if	(cardSum[i]==21)
				{
					if(ifBJack[i]==0)
					{
						dollar[i]+=bet[i];
					}		
				}		
			}
		}
		else if (cardSum[n_user]==21)			//dealer 21 
		{
			if (ifBJack[n_user]==1)				//dealer blackjack
			{
				if(cardSum[i]<=21 && ifBJack[i]==0)
				{
					dollar[i]-=bet[i];		
				}
			}
			else								//dealer not blackjack
			{
				if(cardSum[i]==21 && ifBJack[i]==0)	//player 21 but not blackjack
				{
					dollar[i]+=bet[i];
				}
				else if(cardSum[i]<21)			//player less than 21
				{
					dollar[i]-=bet[i];
				}
			}
				
		}
	}
	
	for(i=0;i<n_user;i++)
	{
		if (i==0)
		{
			if((cardSum[i]==cardSum[n_user]) || (cardSum[i]==21 && ifBJack[n_user]==0) || cardSum[n_user]>21)
			{
				printf("\n  -> your result:	win (%i)\n", dollar[i]);
			}
			else if (cardSum[i]>21)
			{
				printf("\n  -> your result: lose due to overflow (%i)\n", dollar[i]);
			}
			else if(cardSum[i]<cardSum[n_user] && cardSum[n_user]<=21)
			{
				printf("\n  ->your result: lose (%i)\n", dollar[i]);
			}
			else
			{
				printf("wrong!%i \n");
			}
		}
		else
		{
			if (cardSum[i]>21)
			{
				printf("\n  ->%ith result	: lose due to overflow (%i)\n", i, dollar[i]);
			}
			else if(cardSum[i]<cardSum[n_user] && cardSum[n_user]<=21)
			{
				printf("\n  ->%ith result	: lose (%i)\n", i, dollar[i]);
			}
			else
			{
				printf("\n  ->%ith result	: win (%i)\n", i, dollar[i]);
			}
		}
	}
	
	
		for(i=0;i<n_user;i++)
	{
		ifBJack[i]=0;
	}
				
	return;
}


/*		
	if(cardSum[n_user]==21)
	{
		printf("you lose");
	}
	else if (cardSum[n_user]>21)
	{
		printf("you win");
	}
	else
	{
		if (cardSum[0]<cardSum[n_user])
		{	
			printf("you lose");
		}
		else
		{
			printf("you win");	
		}
	}
	gameEnd++;
}


*/
/*

int checkWinner(int roundIndex) {
	roundIndex++;	
}

*/

int main(int argc, char *argv[]) {
	
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	
	for(i=0; i<n_user ; i++) 
	{	
		dollar[i]=N_DOLLAR;
	}
	
	//2. card tray
	mixCardTray();

	for (i=0;i<52;i++)
		printf("card %i : %i\n", i, CardTray[i]);

	//Game start --------
	do {roundIndex++;
		printf("-------------------------------------------\n" );
		printf("----------ROUND %i (cardIndex:%i)----------\n", roundIndex, cardIndex);	
		printf("-------------------------------------------\n" );
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		

		//each player's turn
		for (i=0;i<=n_user;i++) //each player
		{
			int cardcnt=1;
			cardSum[i]=0; 
			while (cardSum[i]<21 && (endturn==0))		//do until the player dies or player says stop
			{
				printUserCardStatus(i, cardcnt);	//print current card status 
				calcStepResult(i, cardcnt);			//check the card status 
				
				if ((i==0) && cardSum[i]<21 && (endturn==0))			//my turn & cardSum over 21-> my turn end
				{	
					getAction();				//GO? STOP? 
					cardhold[i][cardcnt+1]=pullCard(); 	
				}	//(user!=0)->end
				
				cardcnt++;
			}
			endturn=0;									//initialize endturn for next player 
		}
		
		
		//result
		checkResult();
		
	
}while(gameEnd == 0);
	
	/*
	checkWinner();
	*/	
			
		return 0;

}
