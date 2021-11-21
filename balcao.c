#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "balcao.h"


int main(int argc, char* argv[])
{
        int i;
	char* n = getenv("MAXCLIENTES");
	char* m = getenv("MAXMEDICOS");

        do{
        char str[50], ans[50];

        printf("Sintomas: ");
        fgets(str,50,stdin);
        str[strlen(str)-1] = '\0';

        if(strcmp(str,"#fim")==0){
        	exit(0);

        }

        int cp[2]; // Child > Parent
        int pc[2]; // Parent > Child

        if (pipe(cp) == -1)
        {
                printf("Não foi possível criar o pipe \n");
                exit(1);
        }
        if (pipe(pc) == -1)
        {
                printf("Não foi possível criar o pipe \n");
                exit(1);
        }

        int id = fork();
        if (id == -1)
        {
                printf("Não foi possível de fazer fork");
                exit(2);
        }

        if (id == 0) //processo filho
        {
                close(STDIN_FILENO);
                dup(pc[0]);

                close(STDOUT_FILENO);
                dup(cp[1]);

                close(cp[1]);
                close(pc[0]);
                close(cp[0]);
                close(pc[1]);

                execlp("./classificador", "./classificador", NULL);

        }
        else //processo pai
        {
                close(pc[0]);
                write(pc[1], str, strlen(str) + 1);
                close(pc[1]);

                read(cp[0], ans, 50);

                close(cp[0]);
                close(cp[1]);

                printf("%s", ans);

                for(i=0;ans[i]!='\n';i++) //elimina erro que faz classificador dar print a mais do que uma linha
		{
                        ans[i] = '\0';

                }
                wait(NULL);
        }

        }while(1);


        exit(0);

}
