#include <stdio.h>
#include <gmp.h>


void CharConverter(int compt){ 
	FILE* File = NULL; 
	File = fopen("decrypt.txt", "r"); 
	int test; 
	int i; 
	char buff; 
	char buff2; 
	rewind(File); 
	for (i = 0; i < compt; i++){ 
		buff = fgetc(File); 
		buff2 = fgetc(File); 
		test = ((buff-48)*10)+(buff2-48);
	//	printf("buff:%d\nbuff2:%d\n", buff, buff2);
		buff = (test+55); 
		printf("%c", buff); 
	} 
	printf("\n"); 
}


int main (){
	FILE* fInput = NULL;
	FILE* fOutput = NULL;

	int i = 0;

	char strIn; 

	mpz_t module;
	mpz_init (module);
	mpz_t private;
	mpz_init (private);
	mpz_t buffer;
	mpz_init (buffer);
	mpz_t Output;
	mpz_init (Output);

	mpz_t FiddyF;
	mpz_init (FiddyF);
	mpz_set_ui(FiddyF, 55);

	printf("Insert private key: ");
	gmp_scanf ("%Zd", &private);
	printf("Module: ");
	gmp_scanf("%Zd", &module);

	fInput = fopen ("output.txt", "r");
	fOutput = fopen ("decrypt.txt", "w");

	mpz_inp_str(buffer, fInput, 0);
	mpz_powm (Output, buffer, private, module);
	mpz_out_str(fOutput, 0, Output);

	rewind(fInput);
	//Count the number of letter in file
	while (strIn != EOF){
		strIn = fgetc(fInput);
		i++;
	}
	i = (i/4)-1;
	fclose(fOutput);
	printf("Decrypted text:\n");
	CharConverter(i);


	printf("Decryption finished!\n");
	return 0;
}
