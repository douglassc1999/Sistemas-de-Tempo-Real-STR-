/*
Alunos: Pedro Victor Andrade Alves
        Francisco Kennedi

Projeto: Gerenciador de processos
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int op = 0;
string nome_processos;

int main(){
	printf("Inicio do gerenciador de processos\n\n");
	system("ps -a\n\n");
	printf("Digite: 1 - Filtar | 2 - Pausar | 3 - Continuar | 4 - Matar | 5 - Mudar prioridade | 6 - Escolher CPU\n");
	printf("Insira a operação:\n");
	scanf("%d", &op);
	printf("\n");
	
	switch(op){
	    
      	    case 1:
		printf("Digite o nome do processo: \n\n");
		
		break;
	    case 2:
		break;
	    case 3:
		break;
      	    case 4:
		break;
	    case 5:
		break;
	    case 6:
		break;
	}
		
			
	exit (0);
}

