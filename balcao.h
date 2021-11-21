
typedef struct
{
	char nome[10];
	char especialidade[15];

}medico;

typedef struct
{
	char nome[10];
	char especialidade[15];
	int prioridade;
	int lugar; //lugar na fila (1 a MAXFILA)

}cliente;

#define MAXFILA	5 //número máximo permitido de pessoas por fila
#define MAXESPS 5 //número máximo de especialidades
