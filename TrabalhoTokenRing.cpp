#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

/* ------------------------------- Declaração Structs ------------------------------- */

typedef struct nodoParticipante
{
	int numeroParticipante;
	char nomeParticipante[50];
	
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
	int quantasMensagensEnviar;
	int quantasMensagensReceber;
	struct nodoMensagens *inicio;
	struct nodoMensagens *fim;
	
}Header_Mensagens;

typedef struct nodoMensagens
{
	char conteudo[150];
	struct nodoMensagens *prox;
	struct nodoMensagens *ant;
}Mensagens;


typedef struct nodoHeaderParticipantes
{
	int quantidadeParticipantesAtivos;
	struct nodoParticipantes *inicio;
	struct nodoParticipantes *fim;
} Header_Participantes

/* ---------------------------------------------------------------------------------- */


/* ------------------------------- Declaração Funções ------------------------------- */

void envia_msg(Participante **participante); //falta concluir

void apresentacao();

int Menu();									 // faltam funções de 4 a 10

int consulta_msgs_a_enviar(Participante *participante);

int consulta_msgs_recebidas(Participante *participante);

void consulta_participantes(Header_Participantes *headerParticpantes)

/* ---------------------------------------------------------------------------------- */

int main(){
	
	Header_Participantes *headerParticpantes = NULL;
	locale('',LC_ALL);
	int escolhaMenu = Menu();
	
	while(escolhaMenu!=0)
	{
		switch(escolhaMenu)
		{
			case 1:
				envia_msg(&participante);
				break;
			case 2:
				consulta_msgs_a_enviar(participante);
				break;
			case 3:
				consulta_msgs_recebidas(participante);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				void consulta_participantes(headerParticpantes);
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
	printf(" 1- Enviar uma mensagem\n");
	printf(" 2- Consultar mensagens a enviar\n");
	printf(" 3- Consultar mensagens recebidas\n");
	printf(" 4- \n");
	printf(" 5- \n");
	printf(" 6- \n");
	printf(" 7- Consulta Participantes\n");
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
		scanf(" %[\n]", Mensagem);
		strcpy(novaMensagem->conteudo,Mensagem);
		novaMensagem->ant = Participante->mensagensEnviar;
		novaMensagem->prox = NULL;
		participante->HeaderMensagensEnviar->fim->ant->prox = novaMensagem;
		
		printf("\n Deseja enviar outra mensagem? (1/0)");
		scanf("%d", &loop);
	}
	
	
	
}


int consulta_msgs_a_enviar(Participante *participante)
{
	printf("\n Você possui %d mensagens para enviar.", participante->HeaderMensagensEnviar->quantasMensagensEnviar);
	system("pause");
}


int consulta_msgs_recebidas(Participante *participante)
{
	printf("\n Você possui %d mensagens para enviar.", participante->HeaderMensagensEnviar->quantasMensagensReceber);
	system("pause");
}

void consulta_participantes(Header_Participantes *headerParticpantes)
{
	int escolha=1,idBuscar;
	Participantes *ptauxP = headerParticpantes->inicio;
	while(escolha==1)
	{
		printf("\nParticipantes da Rede: ")
		while(ptauxP !=NULL)
		{
			printf("\nParticipante: %s ; ID na rede: %d", ptauxP->nomeParticipante, ptauxP->numeroParticipante);
			ptauxP = ptauxP->prox;
		}
		printf("\n Deseja verificar as informações de algum participante?(1/0)");
		scanf("%d", &escolha);
		if(escolha)
		{
			while(escolha==1)
			{
				ptauxP = headerParticipantes->inicio;
				printf("\n Informe o ID da rede do usuário:\n");
				scanf("%d", &idBuscar);
				if(idBuscar<headerParticipantes->quantidadeParticipantesAtivos && idBuscar>0)
				{
					while(idBuscar!=ptauxP->numeroParticipante)
					{
						ptauxP = ptauxP->numeroParticipante;
					}
					printf("Nome: %s \nID: %d \nMensagens a serem enviadas:%d \n Mensagens recebidas:%d", ptauxP->nomeParticipante, ptauxP->numeroParticipante, ptauxP->HeaderMensagensEnviar->quantasMensagensEnviar, ptauxP->HeaderMensagensReceber->quantasMensagensReceber);
				}
				else
				{
					printf("\n O id de busca excede a quantidade de participantes ativos. \n Deseja tentar novamente?(1/0)");
					scanf("%d",&escolha);
				}
			}
		}
	}
	
}
