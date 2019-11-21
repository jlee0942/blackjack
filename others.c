#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern int getIntegerInput(void);
extern int n_user;
extern int dollar[N_MAX_USER];
extern int bet[N_MAX_USER];


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
