#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

/* ------------------------------- Declaração Structs ------------------------------- */

typedef struct nodoParticipante
{
	int numeroParticipante;
	char nomeParticipante[50];
	
	struct nodoMensagens *mensagensEnviar;
	struct nodoMensagens *mensagensRecebidas;
	
	struct nodoHeaderMensagens *HeaderMensagensEnviar;
	struct nodoHeaderMensagens *HeaderMensagensReceber;
	
	struct nodoParticipante *prox;
	struct nodoParticipante *ant;
	
}Participante;

typedef struct nodoToken
{
	int numeroParticipante;
	char nomeParticipante[50];
	int leu;
	
	struct nodoParticipante *prox;
}Token;

typedef struct nodoHeaderMensagens
{
	
	struct nodoMensagens *inicio;
	struct nodoMensagens *fim;
	
}Header_Mensagens;

typedef struct nodoMensagens
{
	char conteudo[150];
	struct nodoMensagens *prox;
	struct nodoMensagens *ant;
}Mensagens;

/* ---------------------------------------------------------------------------------- */


/* ------------------------------- Declaração Funções ------------------------------- */

void envia_msg(Participante **participante); //falta concluir

void apresentacao();

int Menu();									 // faltam funções de 1 a 10


/* ---------------------------------------------------------------------------------- */

int main(){

	locale('',LC_ALL);
	int escolhaMenu = Menu();
	
	while(escolhaMenu!=0)
	{
		switch(escolhaMenu)
		{
			case 1:
				envia_msg();
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
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case Default:
				printf("\n Digite uma opção existente!");
				break;
		}
		escolhaMenu = Menu;
		
	}
	
	printf("\n Obrigado por utilizar o programa!");
	printf("\n Programa desenvolvido por: Adriano Gomes da Silva");
	printf("\n Versão XX.XX.XX");





}



void apresentacao()
{
	printf("\n");
	printf(" /*---------------------------------------------*/");
	printf("\n / Seja Bem-vindo Ao Programa Rede Token Ring \n");
}



int Menu()
{
	int escolha;
	
	printf("\n");
	printf(" /*---------------------------------------------*/\n");
	printf(" 1- \n");
	printf(" 2- \n");
	printf(" 3- \n");
	printf(" 4- \n");
	printf(" 5- \n");
	printf(" 6- \n");
	printf(" 7- \n");
	printf(" 8- \n");
	printf(" 9- \n");
	printf(" 10- \n");
	printf(" 0- \n");
	printf("\n Digite a opção que desejas escolher:");
	
	escolha = getch();
	
	return escolha;
	
}


void envia_msg(Participante **participante)
{
	char Mensagem[150];
	int loop=1;
	Mensagens *novaMensagem = (Mensagens *)malloc(sizeof(Mensagens));
	
	while(loop==1)
	{
		printf("\n Digite a mensagem que deseja enviar: ")
		scanf("%[\n]", Mensagem);
		strcpy(novaMensagem->conteudo,Mensagem);
		novaMensagem->ant = Participante->mensagensEnviar;
		novaMensagem->prox = NULL;
		participante->HeaderMensagensEnviar->fim->ant->prox = novaMensagem;
		
		
	}
	
	
	
}



