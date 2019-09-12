/*
Alunos: Pedro Victor Andrade Alves
        Francisco Kennedi
Projeto: Gerenciador de processos
*/
#include <signal.h> // definição dos sinais de interrupções
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int op = 0;
char op2 = 'r';
char nome_p; 
int PID = 0;
bool refresh = true;

//string nome_processos;

int main(){
	
	printf("Inicio do gerenciador de processos\n\n");
	while(1){
		refresh = true;
		while(refresh){
			system("clear");
			//system("ps -a -l\n\n ");
			system("ps -e -o s,pid,uname,cmd,pmem,pcpu --sort=-pmem,-pcpu | head -20");
			printf("Digite 'm' para ver o menu e 'r' para dar refresh: ");
			
			scanf("%c", &op2);		 	
			if(op2 == 'm'){
				refresh = false;
				op2 = 'r';
			}
			
					
		}
		printf("Digite: 1 - Filtar | 2 - Pausar | 3 - Continuar | 4 - Matar | 5 - Muda prioridade | 6 - Escolher CPU\n");
		printf("Insira a operação:\n");
		scanf("%i", &op);
		
		printf("\n");
		
		switch(op){
    
	      	    	case 1:
				printf("Digite o nome do processo: \n\n");
				//scanf("%s", &nome_p);
				//system("ps aux | grep %s", nome_p);
				break;
		    	case 2:
				printf("Digite o PID do processo: \n\n");
				scanf("%d", &PID);
				kill(PID, SIGSTOP);
				break;
		    	case 3:
				printf("Digite o PID do processo: \n\n");
				scanf("%d", &PID);
				kill(PID, SIGCONT);
				break;
	      	    	case 4:
				printf("Digite o PID do processo: \n\n");
				scanf("%d", &PID);
				kill(PID, SIGKILL);
				break;
		    	case 5:
				
				break;
		    	case 6:
				break;
		}		
	   
		
		system("clear");
			
	}
	exit (0);
}
