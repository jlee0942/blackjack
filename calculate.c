#include <stdio.h>
#include <stdlib.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17


#define N_MIN_ENDCARD		30



//card tray object
int CardTray[N_CARDSET*N_CARD];
						


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting
int gameEnd = 0; 							//game end flag 


int getAction(void){

	printf("Action? (0 - go, others - stay) :");
	getIntegerInput();

}

void printUserCardStatus(int user, int cardcnt) {
	int i;
	if (user==0)
	{
		printf("\n>>>my turn------------------------!");
	}
	else if (user<n_user)
	{
		printf("\n>>>player%i 's turn------------------------!", user);
	}
	else
	{
		printf("\n>>> dealer turn! ------------------------\n");
	}
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}


int calcStepResult(int user, int cardcnt) {
	cardSum[user]+=cardhold[user][cardcnt];
	
	if (user!=0)
		{
			if (cardSum[user]<17)
			{
				printf("GO!");
				cardcnt++;
				cardhold[user][cardcnt]=pullCard();
			}
			else
			{
				printf("STOP!(sum:%i)", cardSum[user]);
				if (user==n_user)
					printf("[[[[[[dealer's result is........%i]]]]]]", cardSum[user]);						
			}
		}
	else	
		{
			if (cardSum[user]==21)
			{	if(cardcnt==1)
				{
					printf("BLACKJACK!");
				}
				else
					printf("STOP!");	//end turn
			}
			else
			{	
			 	getAction();
			}	
		

}



int checkResult(void){

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

}}
	

