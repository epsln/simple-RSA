#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>



long int Premier(){
	long int ligne = 0;
	const int MAX = 5902412 , MIN = 0;
	FILE* fichierNombres = NULL;

	int i = 0;
	long int prems;//li with prime number
	char line [15];//array with the prime number
	fichierNombres = fopen ("nombres.txt", "r");  
	ligne = (rand() % (MAX - MIN + 1)) + MIN;//Random number chosen with a time seed
	printf("LIGNE : %li\n", ligne);

	while (fgets(line, sizeof line, fichierNombres) != NULL){//Get line and put it in a array
		if (i == ligne){
			sscanf(line, "%li", &prems);//Put array in lli
			return prems;
			fclose(fichierNombres);
		}

		else
			i++;
	}
	fclose(fichierNombres);
	return -1;
}

void CharConverter(int compt){
	FILE* File = NULL;
	File = fopen("output.txt", "r");
	int test;
	int i;
	char buff;
	char buff2;
	rewind(File);
	for (i = 0; i < compt; i++){
		buff = fgetc(File);
		buff2 = fgetc(File);
		test = ((buff-48)*10)+(buff2-48);
		buff = (test+55);
		printf("%c", buff);
	}
	printf("\n");
}


int main (){
	FILE* fInput = NULL;
	FILE* fOutput = NULL;

	char input ='A';

	unsigned long long int swapPrems;
	unsigned long long int swapPrems2;

	int compt=0;

	mpz_t Prems;
	mpz_init (Prems);

	mpz_t Prems2;
	mpz_init (Prems2);

	mpz_t module;
	mpz_init (module);
	mpz_t phi;
	mpz_init (phi);

	mpz_t Buffer;
	mpz_init (Buffer);
	mpz_t Buffer2;
	mpz_init (Buffer2);

	mpz_t One;
	mpz_init (One);
	mpz_set_ui(One, 1);

	mpz_t exposant;
	mpz_init (exposant);
	mpz_set_ui(exposant, 65537);

	mpz_t eDechifrement;
	mpz_init (eDechifrement);

	mpz_t Output;
	mpz_init(Output);

	srand(time(NULL));

	swapPrems = Premier();
	mpz_set_ui(Prems, swapPrems);
	gmp_printf("Prems = %Zd\n", Prems);	 

	swapPrems2 = Premier();
	mpz_set_ui(Prems2, swapPrems2);	
	gmp_printf("Prems 2 = %Zd\n", Prems2);

	mpz_mul (module, Prems, Prems2);
	mpz_sub (Buffer, Prems, One);
	mpz_sub (Buffer2, Prems2, One);
	mpz_mul (phi, Buffer, Buffer2);

	mpz_invert(eDechifrement, exposant, phi);

	gmp_printf("PHI : %Zd\nMODULE : %Zd\nEXPOSANT DE CHIFFREMENT : %Zd\nEXPOSANT DE DECHIFREMENT : %Zd \n", phi, module, exposant, eDechifrement);		
	//TODO : The message must be < module else lost info, crypt message by block
	fInput = fopen ("input.txt", "r");
	fOutput = fopen("output.txt", "w+");
	mpz_set_ui(Buffer, 0);
	while ((input = fgetc(fInput)) != EOF){ 
		if (input == ' ' || input == 10){
			continue;
		}
		printf("Letter : %c\n", input);
		input=input-55;
		fprintf(fOutput, "%d", input);
		printf("%d\n", input);
		compt++;
	}
	fclose(fOutput);
	fOutput = fopen("output.txt", "r");
	if ((mpz_inp_str(Buffer, fOutput,10))==0){
		printf("Nothing\n");
		exit(-1);
	}
	gmp_printf("Clear: %Zd\n", Buffer);
	mpz_powm (Output, Buffer, exposant, module);
	gmp_printf("Encrypted: %Zd\n", Output);
	mpz_out_str (fOutput, 0, Output);
	printf("Encryption Finished\n");



	return 0;
}

