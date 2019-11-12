//Determining whether ace is 1 or 11
int detAce(void){
}

//real number of the card
int* cardInfo(void) {
	int i;
	int *saveCardNum;

	for(i=0;i<(N_CARDSET*N_CARD);i++)

		do{
		{
		if (i%N_MAX_CARDNUM ==0)
			CardTray[i]=1;				//function determining whether ace should be 1 or11	
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
		}
			saveCardNum=CardTray;

		}while(i>=N_CARDSET*N_CARD);
			return CardTray[i];	

}
