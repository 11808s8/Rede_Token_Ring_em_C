#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include <time.h>

/* ----------------------------- 

	autor:       Adriano Gomes da Silva
	disciplina:  Estrutura de Dados
	orientadora: Helena Graziottin Ribeiro
	horário:     48-49
	
	 ----------------------- */

/* ------------------------------- VARIAVEIS GLOBAIS --------------------------------- */

int inicializouToken=0;
int RodandoToken=0;
int totalMensagensEnviar=0;

/* ----------------------------------------------------------------------------------- */


/* ------------------------------- Declaração Structs ------------------------------- */

typedef struct nodoParticipante		/* -------------------------------- * Participante * */
{
	int numeroParticipante;
	char nomeParticipante[50];
	
	struct nodoHeaderMensagens *HeaderMensagensEnviar;
	struct nodoHeaderMensagens *HeaderMensagensReceber;
	
	struct nodoParticipante *prox;
	struct nodoParticipante *ant;
	
}Participante;



typedef struct nodoHeaderMensagens	/* -------------------------------- * Header Mensagens * */
{
	int quantasMensagens;
	struct nodoMensagens *inicio;
	struct nodoMensagens *fim;
	
}Header_Mensagens;

typedef struct nodoMensagens		/* -------------------------------- * Mensagens * */
{
	char conteudo[150];
	int destinatarioID;
	int emissorID;
	char nomeEmissor[50];
	
	struct nodoMensagens *prox;
}Mensagens;


typedef struct nodoHeaderParticipantes
{
	int quantidadeParticipantesAtivos;
	struct nodoParticipante *inicio;
	struct nodoParticipante *fim;
	
} Header_Participantes;

typedef struct nodoToken /* -------------------------------- * Token * */
{
	int possuiMSG;
	int passouUma;
	int emQualPartEsta;
	int emQualIDEsta;
	
	int ID_emissor;
	int ID_destino;
	int eProprioEmissor;
	char mensagem[150];
}Token;

/* ---------------------------------------------------------------------------------- */


/* ------------------------------- Declaração Funções ------------------------------- */

void envia_msg(Header_Participantes **headerParticipantes); 

void apresentacao();

int Menu();									

void consultaMensagens(Header_Participantes **headerParticipantes, char EouRouL);

void consulta_msgs_a_enviar(Participante *Participante);

void consulta_msgs_recebidas(Participante *Participante);

void consulta_participantes(Header_Participantes *headerParticipantes);

void consulta_participantes_auto(Header_Participantes *headerParticipantes);

void le_msg(Header_Mensagens **HeaderMensagensReceber);

void remove_nodo_inicio(Header_Mensagens **HeaderMensagens); 

void menuIncluirParticipante(Header_Participantes **headerParticipantes);

struct nodoParticipante *buscaParticipantePorId(Header_Participantes **headerParticipantes, int id);

struct nodoParticipante *incluiParticipante(Header_Participantes **headerParticipantes, char nome[50]);

void menuRemoverParticipante(Header_Participantes **headerParticipantes);

void removeParticipante(Header_Participantes **headerParticipantes, Participante **R_part, int id);

struct nodoParticipante* buscaParticipantePorPos(Header_Participantes **headerParticipantes, int pos);

void insere_inic(Header_Mensagens **headerMensagens, Mensagens **mensagem);

/* ----------------------------------------------------------------------------------- */





/*------------------------------- Funções TOKEN --------------------------------------*/

void ativa_rede(Token **token, Header_Participantes **headerParticipantes);

void desativa_rede(Token **token,Header_Participantes **headerParticipantes);

void limpa_token(Token **token);

void roda_token(Token **token, Header_Participantes **headerParticipantes);

void token_mensagem_tela(Token *token);


void consulta_token(Token *token);
/* ---------------------------------------------------------------------------------- */




int main(){
	
	Header_Participantes *headerParticipantes = (Header_Participantes *)malloc(sizeof(Header_Participantes));
	headerParticipantes->quantidadeParticipantesAtivos=0;
	headerParticipantes->inicio = NULL;
	Token *token = (Token *)malloc(sizeof(Token));
	token->possuiMSG = 0;
	char escolhaInicial;
	setlocale(LC_ALL,"");
	apresentacao();
	
	printf("\n Para o programa inicializar, é necessário cadastrar um usuario. \nDeseja fazer isso?(S/N)\n");
	escolhaInicial = toupper(getch());
	
	
	
	
	
	
	if(escolhaInicial=='S')
	{
		menuIncluirParticipante(&headerParticipantes);
		system("cls");
		
		Token *token = NULL;
		int escolhaMenu = Menu();
		
		while(escolhaMenu!=0)
		{
			switch(escolhaMenu)
			{
				case 0:
					break;
				case 1:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						envia_msg(&headerParticipantes);
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 2:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						consultaMensagens(&headerParticipantes, 'E');
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 3:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						consultaMensagens(&headerParticipantes,'R');
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 4:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						if(inicializouToken)
						{
							consultaMensagens(&headerParticipantes,'L');
						}
						else
						{
							printf("\n A rede não fora inicializada. Tente novamente mais tarde");
							system("pause");
						}
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 5:
					menuIncluirParticipante(&headerParticipantes);
					break;
				case 6:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						menuRemoverParticipante(&headerParticipantes);
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 7:
					if(headerParticipantes->quantidadeParticipantesAtivos>0)
					{
						consulta_participantes(headerParticipantes);
						if(RodandoToken)
						{
							roda_token(&token, &headerParticipantes);	
						}
					}
					else
					{
						printf("\n É necessário cadastrar ao menos um participante! (Tente a opção 5 do menu...)");
						system("pause");
					}
					break;
				case 8:
					consulta_token(token);
					break;
				case 9:
					if(!RodandoToken)
					{
						ativa_rede(&token, &headerParticipantes);
						roda_token(&token, &headerParticipantes);
					}
					else
					{
						printf("\n A rede já está funcionando. Nâo é possível ativá-la.");
						system("pause");
					}
						
					break;
				case 10:
					if(RodandoToken)
					{
						desativa_rede(&token, &headerParticipantes);
						roda_token(&token, &headerParticipantes);
					}
					else
					{
						printf("\n A rede não está funcionando. Nâo é possível desativá-la.");
						system("pause");
					}
					break;
				case 11:
					if(RodandoToken)
					{
						if(totalMensagensEnviar)
						{
							while(totalMensagensEnviar!=0)
							{
								roda_token(&token, &headerParticipantes);
							}
							printf("\n Todas as mensagens foram enviadas!");
							system("pause");
						}
						else
						{
							printf("\n A rede não possui nenhuma mensagem para ser enviada.");
							system("pause");
						}
					}
					else
					{
						printf("\n A rede está parada. Ative-a e tente novamente");
						system("pause");
					}
					break;
				 default:
					printf("\n Digite uma opção existente!");
					system("pause");
					break;
			}
			system("cls");
			
			if(RodandoToken)
			{
				roda_token(&token, &headerParticipantes);	
			}
			
			escolhaMenu = Menu();
			
		}
	}
	
	printf("\n Obrigado por utilizar o programa!");
	printf("\n Programa desenvolvido por: Adriano Gomes da Silva");
	printf("\n Versão 210916");
	printf("\n Au Revoir!");




}



void apresentacao()
{
	printf("\n");
	printf(" /*---------------------------------------------*/");
	printf("\n / Seja Bem-vindo Ao Programa Rede Token Ring \n");
	printf(" /*---------------------------------------------*/");
	
}



int Menu()
{
	int escolha;
	
	printf("\n");
	printf("   /*--------------------Menu---------------------*/\n");
	printf("  /*--------------Rede-Token-Ring----------------*/ \n ");
	printf(" /*---------------------------------------------*/\n");
	printf("  1- Enviar uma mensagem\n");
	printf("  2- Consultar mensagens a enviar\n");
	printf("  3- Consultar mensagens recebidas\n");
	printf("  4- Ler Mensagem Recebida\n");
	printf("  5- Inserir um novo participante\n");
	printf("  6- Remover um participante\n");
	printf("  7- Consulta Participantes\n");
	printf("  8- Consultar o Token\n");
	printf("  9- Ativar a rede\n");
	printf("  10- Desativar a rede\n");
	printf("  11- Aguardar o envio de todas as mensagens da rede!\n");
	printf("  0- Sair do programa\n");
	printf("\n Digite a opção que desejas escolher:");
	
	scanf("%d",&escolha);
	
	return escolha;
	
}


void envia_msg(Header_Participantes **headerParticipantes) // Função para envio da mensagem
{
	char Mensagem[150], escolha;
	int loop=1, id, idB;
	Participante *ptaux, *ptbusca;

	
	while(loop==1)
	{
		
		escolha='S';
		while(escolha=='S')
		{
			printf("\n Qual seu ID?");
			scanf("%d", &id);
			
			
			ptaux = buscaParticipantePorId(headerParticipantes,id);
			if(ptaux!=NULL)
			{
				while(loop==1)
				{
					fflush(stdin);
					printf("\n Digite o ID da pessoa para a qual voce deseja enviar a mensagem:");
					scanf("%d", &idB);

						printf("\n Digite a mensagem que deseja enviar: ");
						scanf(" %[^\n]", Mensagem);
						
						Mensagens *novaMensagem = (Mensagens *)malloc(sizeof(Mensagens));
						
						strcpy(novaMensagem->conteudo,Mensagem);
						fflush(stdin);
						strcpy(novaMensagem->nomeEmissor,ptaux->nomeParticipante);
						novaMensagem->destinatarioID = idB;
						novaMensagem->emissorID = id;
						
						insere_inic(&(ptaux)->HeaderMensagensEnviar,&novaMensagem);

						ptaux->HeaderMensagensEnviar->quantasMensagens++;
						loop=0;
						escolha='n';

				}
			}
			else
			{
				escolha='N';
				while(escolha!='S')
				{

					printf("\n Para facilitar sua vida, uma lista dos participantes:");
					consulta_participantes_auto(*headerParticipantes);
					printf("\n Participante não encontrado! Deseja tentar novamente?(S/N)");
					fflush(stdin);
					escolha = toupper(getch());
					if(escolha=='N')
					{
						printf("\n Mensagem não enviada! Retornando ao menu principal\n");
						return;
					}
					else if(escolha!='S')
					{
						printf("\n Digite uma opção válida!");
					}
				}
			}
		}
		totalMensagensEnviar++;
		printf("\n Deseja enviar outra mensagem? (1/0)");
		scanf("%d", &loop);
		
	}
	
	
	
}

void consultaMensagens(Header_Participantes **headerParticipantes, char EouRouL) //menu para funções de consulta a mensagens ('E'nviou, 'R'ecebeu, 'L'er);
{
	int loop=1,id;
	Participante *ptbusca;
	char escolha;
	
	while(loop==1)
	{
		printf("\n Digite seu ID na rede:");
		scanf("%d",&id);
		ptbusca=buscaParticipantePorId(headerParticipantes,id);
		if(ptbusca==NULL)
		{
			printf("\n Para facilitar sua vida, uma lista dos participantes:");
			consulta_participantes_auto(*headerParticipantes);
			printf("\n Deseja tentar novamente?(S/N)");
			fflush(stdin);
			escolha = toupper(getch());
			if(escolha=='N') 
			{
				printf("\n Retornando ao menu principal!");
				system("pause");
				return;
			}
		}
		else loop=0;
	}
	if(EouRouL == 'E')
	{
		consulta_msgs_a_enviar(ptbusca);
	}
	else if(EouRouL == 'R')
	{
		consulta_msgs_recebidas(ptbusca);
	}
	else if(EouRouL == 'L')
	{
		if(ptbusca->HeaderMensagensReceber!=NULL)
		{
			if(ptbusca->HeaderMensagensReceber->quantasMensagens>0)
			{
				le_msg(&(ptbusca->HeaderMensagensReceber));
				
				printf("\n Retornando ao menu principal!");
				system("pause");
				return;
			}
		}
		
		printf("\n Voce ainda não possui nenhuma mensagem para ler!");
		
		printf("\n Retornando ao menu principal!");
		system("pause");
	}
}

void consulta_msgs_a_enviar(Participante *participante) //apenas consulta se existem ou não mensagens a serem enviadas
{
	if(participante->HeaderMensagensEnviar!=NULL)
		printf("\n Você possui %d mensagens para enviar.", participante->HeaderMensagensEnviar->quantasMensagens);
	else
		printf("\n Voce ainda não possui nenhuma mensagem!");
	
	printf("\n Retornando ao menu principal!");
	system("pause");
}


void consulta_msgs_recebidas(Participante *participante)
{
	if(participante->HeaderMensagensReceber!=NULL)
		printf("\n Você possui %d mensagens para ler.", participante->HeaderMensagensReceber->quantasMensagens);
	else
		printf("\n Voce ainda não possui nenhuma mensagem!");
		
	printf("\n Retornando ao menu principal!");
	system("pause");
}

void consulta_participantes(Header_Participantes *headerParticipantes) // Função de exibição com opções adicionais (mostrar id, nome e numero de mensagens a enviar/receber)
{
	int idBuscar,i,qntAtiv=headerParticipantes->quantidadeParticipantesAtivos;
	char escolha='S';
	Participante *ptauxP = headerParticipantes->inicio;
	while(escolha=='S')
	{
		i=0;
		printf("\nParticipantes da Rede: ");
		while(i<qntAtiv)
		{
			printf("\nParticipante: %s ; ID na rede: %d", ptauxP->nomeParticipante, ptauxP->numeroParticipante);
			ptauxP = ptauxP->prox;
			i++;
		}
		printf("\n Deseja verificar as informações de algum participante?(S/N)");
		escolha=toupper(getch());
		if(escolha=='S')
		{
			while(escolha=='S')
			{
				printf("\n Informe o ID da rede do usuário:\n");
				scanf("%d", &idBuscar);
				ptauxP = buscaParticipantePorId(&(headerParticipantes),idBuscar);
				if(ptauxP!=NULL)
				{
					printf("Nome: %s \nID: %d  ", ptauxP->nomeParticipante, ptauxP->numeroParticipante);
					if(ptauxP->HeaderMensagensEnviar!=NULL)
					{
						printf("\nMensagens a serem enviadas:%d", ptauxP->HeaderMensagensEnviar->quantasMensagens);
					}
					if(ptauxP->HeaderMensagensReceber!=NULL)
					{
						printf("\n Mensagens recebidas:%d", ptauxP->HeaderMensagensReceber->quantasMensagens);
					}
				}
				else
				{
					printf("\n O id não existe!");
				}
				printf("\n Deseja pesquisar novamente?(S/N)");
				escolha=toupper(getch());
			}
		}
	}
	
}

void consulta_participantes_auto(Header_Participantes *headerParticipantes) // mesmo que consulta participantes, mas, não possui opções extra.
{
	int idBuscar,i,qntAtiv=headerParticipantes->quantidadeParticipantesAtivos;
	char escolha ='S';
	Participante *ptauxP = headerParticipantes->inicio;

	i=0;
	printf("\nParticipantes da Rede: ");
	while(i<qntAtiv)
	{
		printf("\nParticipante: %s ; ID na rede: %d", ptauxP->nomeParticipante, ptauxP->numeroParticipante);
		ptauxP = ptauxP->prox;
		i++;
	}

}

void le_msg(Header_Mensagens **HeaderMensagensReceber) //apenas mostra o conteudo da mensagem e a destroi
{

	printf("\n Emissor da mensagem: %s", (*HeaderMensagensReceber)->inicio->nomeEmissor);
	printf("\n Id do emissor: %d", (*HeaderMensagensReceber)->inicio->emissorID);
	printf("\n Conteúdo: %s  \n ", (*HeaderMensagensReceber)->inicio->conteudo);
	remove_nodo_inicio(HeaderMensagensReceber);
	(*HeaderMensagensReceber)->quantasMensagens--;
	
	return;
}

void remove_nodo_inicio(Header_Mensagens **HeaderMensagens) // remoção no início de lista simples...
{
	Mensagens *ptaux = (*HeaderMensagens)->inicio;	
	(*HeaderMensagens)->inicio = ptaux->prox;
	free(ptaux);

}

void menuIncluirParticipante(Header_Participantes **headerParticipantes)
{
	
	char nome[50];
	printf("\n Digite o nome do participante que deseja inserir:");
	scanf(" %[^\n]",nome); 
	Participante *ptnovo = incluiParticipante(headerParticipantes, nome);
	
	printf("\n Pronto, participante inserido! Seus dados são:");
	printf("\n Nome: %s \n ID na rede: %d", ptnovo->nomeParticipante, ptnovo->numeroParticipante);
	(*headerParticipantes)->quantidadeParticipantesAtivos++;
	printf("\n Retornando ao menu principal\n");
	system("pause");
}

struct nodoParticipante * incluiParticipante(Header_Participantes **headerParticipantes, char nome[50])
{
	int id; // id gerado é randomico
	srand(time(NULL));
	id = rand() % 100;
	
	Participante *ptnovo = (Participante *)malloc(sizeof (Participante));
	ptnovo->HeaderMensagensEnviar = NULL;
	ptnovo->HeaderMensagensReceber = NULL;
	strcpy(ptnovo->nomeParticipante,nome);
	ptnovo->numeroParticipante = id;
	
	ptnovo->prox = ptnovo;
	ptnovo->ant = ptnovo;
	
	if((*headerParticipantes)->fim==NULL)
	{
		(*headerParticipantes)->inicio=ptnovo;
		(*headerParticipantes)->fim=ptnovo;
	}
	
	if((*headerParticipantes)->inicio!=NULL)
	{
		Participante *ptfim = (*headerParticipantes)->fim;
		
		ptnovo->ant = ptfim;
		ptnovo->prox = (*headerParticipantes)->inicio;
		ptfim->prox = ptnovo;
		
		(*headerParticipantes)->fim= ptnovo;

		
	}
	

	
	return ptnovo;
}

void menuRemoverParticipante(Header_Participantes **headerParticipantes)
{
	int id;
	Participante *ptaux=NULL;
	char escolha='S';
	while(escolha=='S' && ptaux==NULL)
	{
		printf("\n Digite o id do participante que deseja remover:");
		scanf("%d",&id);              // INCLUIR VERIFICAÇOES..............................
		
		ptaux = buscaParticipantePorId(headerParticipantes,id);
		if(ptaux==NULL)
		{
			escolha='J';
			while(escolha!='S' && escolha!='N')
			{

				printf("\n Para facilitar sua vida, uma lista dos participantes:");
				consulta_participantes_auto(*headerParticipantes);
				printf("\n Participante não encontrado! Deseja tentar novamente?(S/N)");
				fflush(stdin);
				escolha = toupper(getch());
				if(escolha!='S' && escolha!='N')
				{
					printf("\n Digite uma opção válida!");
				}
				else if(escolha=='N')
				{
					printf("\n Nenhum participante fora removido! Retornando ao menu principal");
					system("pause");
					return;	// Quebra e retorna ao menu;
				}
				else break;
			}
		}
	}
	
	removeParticipante(headerParticipantes, &ptaux, id);
	
	(*headerParticipantes)->quantidadeParticipantesAtivos--;
	
	printf("\n Pronto, participante removido! ");
	system("pause");
}

void removeParticipante(Header_Participantes **headerParticipantes, Participante **R_part, int id) // remoção
{
	if((*headerParticipantes)->inicio==(*R_part))
	{
		if((*R_part)->prox==(*headerParticipantes)->inicio)
		{
			
			(*headerParticipantes)->inicio = NULL;
			(*headerParticipantes)->fim = NULL;
			
			free(*R_part);
			return;
		}
		
		(*headerParticipantes)->inicio->prox->ant = (*headerParticipantes)->inicio->ant;
		(*headerParticipantes)->inicio = (*headerParticipantes)->inicio->prox;
		(*headerParticipantes)->fim->prox = (*headerParticipantes)->inicio;
		
		free(*R_part);
		
		return;
	}
	if((*headerParticipantes)->fim==(*R_part))
	{
		(*headerParticipantes)->inicio->ant = (*headerParticipantes)->fim->ant;
		(*headerParticipantes)->fim->prox->ant = (*headerParticipantes)->fim->ant;
		(*headerParticipantes)->fim = (*headerParticipantes)->fim->ant;
		free(*R_part);
		return;
	}
	
	(*R_part)->ant->prox = (*R_part)->prox;
	(*R_part)->prox->ant = (*R_part)->ant;
	free(*R_part);
	return;
}

struct nodoParticipante* buscaParticipantePorId(Header_Participantes **headerParticipantes, int id)// busca participante por id
{

	Participante *prossegue = (*headerParticipantes)->inicio;

	int qtdAtivs = (*headerParticipantes)->quantidadeParticipantesAtivos;
	int i=0;
	while(i<qtdAtivs)
	{
		if(prossegue->numeroParticipante==id)
		{
			return prossegue;
		}
		if(prossegue->numeroParticipante==prossegue->prox->numeroParticipante)
		{
			return NULL;
		}
		prossegue = prossegue->prox;
		i++;
	}
	return NULL;
}

struct nodoParticipante* buscaParticipantePorPos(Header_Participantes **headerParticipantes, int pos) // função para buscar o participante por posição
{
	Participante *ptaux = (*headerParticipantes)->inicio;
	int i=0;
	while(i<pos)
	{
		ptaux = ptaux->prox;
		i++;
	}
	return ptaux;
}



void consulta_token(Token *token) // Função menu 'universal' para consultas referentes ao Token.
{
	char init, escolha;
	if(token==NULL)
	{
		printf("\n O token não fora inicializado sequer uma única vez!");
		printf("\n Faça isso na opção ativa rede no menu principal!");
		system("pause");
	}
	else
	{
		if(!RodandoToken)
		{
			printf("\n O token está parado");
		}
		else
		{
			printf("\n O token está ativo!");
		}
		
		if(token->possuiMSG)
		{
			printf("\n O token possui uma mensagem! Deseja le-la?(S/N)");
			escolha = toupper(getch());
			if(escolha=='S')
			{
				token_mensagem_tela(token);
			}
		}
		else
		{
			printf("\n O token não possui mensagem alguma!");
		}
		
		printf("\n Retornando ao menu principal!\n");
		system("pause");
		
	}
}


void token_mensagem_tela(Token *token)
{
	printf("\n ID Emissor: %d", token->ID_emissor);
	printf("\n ID Destino: %d", token->ID_destino);
	printf("\n Conteúdo do Token: %s\n",token->mensagem);

}



void ativa_rede(Token **token, Header_Participantes **headerParticipantes)
{
	if(inicializouToken==0)
	{
		(*token)=(Token *)malloc(sizeof(Token));
		(*token)->emQualPartEsta=0;
		(*token)->possuiMSG=0;
		inicializouToken=1;
	}
	RodandoToken = 1;
	
}

void roda_token(Token **token, Header_Participantes **headerParticipantes) // Função que faz a mensagem passar de nodo em nodo até o destino
{
	Participante *ptaux;
	if((*token)->emQualPartEsta>(*headerParticipantes)->quantidadeParticipantesAtivos) // Se ele estiver acima do numero total de participantes
	{ 									//O controle é resetado para o 0, para verificar depois se passou por ele mesmo ou não.
		(*token)->emQualPartEsta=0;
		return;
	}
	
	if((*token)->possuiMSG==0)
	{
		if((*token)->emQualPartEsta<(*headerParticipantes)->quantidadeParticipantesAtivos) //Se estiver dentro do número total de
		{																		// participantes...

			ptaux = buscaParticipantePorPos(headerParticipantes,(*token)->emQualPartEsta); //busca o participante por posição na lista;

			
			if(ptaux->HeaderMensagensEnviar!=NULL) // Se possuir mensagens para enviar
			{
				if(ptaux->HeaderMensagensEnviar->quantasMensagens>0) // Se o número de mensagens for maior que zero
				{

					strcpy((*token)->mensagem,ptaux->HeaderMensagensEnviar->inicio->conteudo); // copia mensagem para token
					(*token)->ID_destino = ptaux->HeaderMensagensEnviar->inicio->destinatarioID;
					(*token)->ID_emissor = ptaux->HeaderMensagensEnviar->inicio->emissorID;
					(*token)->possuiMSG = 1;
					
					if((*token)->ID_destino == (*token)->ID_emissor) //se for ele mesmo, ativa a checagem 
					{
						(*token)->eProprioEmissor=1;
					}
					else
						(*token)->eProprioEmissor=0; // Se não, desativa e prossegue
					
					
					(*token)->emQualPartEsta ++; // Sempre incrementa essa parte para verificar onde está

					return;
				}
				else
				{
					(*token)->emQualPartEsta ++;

					return;
				}
			}
			else
			{
				(*token)->emQualPartEsta ++;

				return;
			}
		}
		else // ... Senão, zera
		{
			(*token)->emQualPartEsta = 0;

			return;
		}
		
	}
	else if((*token)->possuiMSG==1) // Se possuir mensagem, irá entrar na verificação se é ou não o destino
	{								// Se o destino não existir, retornará erro, senão, entrega a mensagem,
									// retirando da caixa de mensagens a enviar do emissor e colocando em
									// mensagens recebidas do destinatário.
		ptaux = buscaParticipantePorId(headerParticipantes, (*token)->ID_emissor);


		
		Participante *ptaux2;
		
		ptaux2 = buscaParticipantePorPos(headerParticipantes, (*token)->emQualPartEsta);

		
		if(ptaux2!=NULL)
		{

			if(((*token)->ID_emissor==ptaux2->numeroParticipante) && ((*token)->eProprioEmissor==0))
			{

				remove_nodo_inicio(&(ptaux)->HeaderMensagensEnviar);
				ptaux->HeaderMensagensEnviar->quantasMensagens--;
				(*token)->possuiMSG=0;
				totalMensagensEnviar--;
				
				printf("\n /*-------------------- ERRO ---------------------------- */");
				printf("\n /*O destinatario %d não existe! A mensagem será excluída./\n",(*token)->ID_destino);
				 printf(" /*----------------------Obrigado!-----------------------*/\n");
				system("pause");
				
				return;
			}
			else
			{
				
				if ((*token)->ID_destino==ptaux2->numeroParticipante)
				{
					Mensagens *novaMensagem =(Mensagens *)malloc(sizeof(Mensagens));
				
					novaMensagem->destinatarioID = (*token)->ID_destino;
					novaMensagem->emissorID = (*token)->ID_emissor;
					strcpy(novaMensagem->conteudo,(*token)->mensagem);
					strcpy(novaMensagem->nomeEmissor,ptaux->nomeParticipante);
					
					
					remove_nodo_inicio(&(ptaux)->HeaderMensagensEnviar);
					
					insere_inic(&(ptaux2)->HeaderMensagensReceber, &novaMensagem);

					ptaux->HeaderMensagensEnviar->quantasMensagens--;
					
					totalMensagensEnviar--;
					

					ptaux2->HeaderMensagensReceber->quantasMensagens++;
					
					(*token)->possuiMSG=0;
					strcpy((*token)->mensagem,"");
					(*token)->emQualPartEsta++;

					return;
				}
				else
				{

					(*token)->emQualPartEsta++;

					
				}
			}
		}
		else
		{
			(*token)->emQualPartEsta=0;

		}
	}
}

void insere_inic(Header_Mensagens **headerMensagens, Mensagens **mensagem)
{
	if(*headerMensagens==NULL)
	{
		*headerMensagens = (Header_Mensagens *)malloc(sizeof(Header_Mensagens));
		(*headerMensagens)->quantasMensagens=0;
		(*headerMensagens)->inicio= (Mensagens *)malloc(sizeof(Mensagens));
		(*headerMensagens)->inicio =NULL;
	}
	
	Mensagens *ptaux = *mensagem;
	ptaux->prox = (*headerMensagens)->inicio;
	(*headerMensagens)->inicio = ptaux;
}


void desativa_rede(Token **token,Header_Participantes **headerParticipantes)
{
	RodandoToken = 0;
}

