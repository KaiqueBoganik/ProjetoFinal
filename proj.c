#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//windows-msvc-x64
#define V 'X'
#define M '.'
#define A 'O'
#define MAXL 100
#define MAXC 100
#define TAM 50


// o trecho abaixo define algumas macros
#ifdef __unix__
#include <unistd.h>
#define LIMPATELA "clear"
#define DORME(a) sleep(a)
#define TEMPO 5
#else
#include <Windows.h>
#define LIMPATELA "cls"
#define DORME(a) Sleep(a)
#define TEMPO 1599
#endif

typedef struct tab
{
    char nomeJogo[TAM];
    int ciclosVida;
    int dim1,dim2;
    char **m;

} Tab;

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Inicio dos prototipos ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

//Atencao!!!! Nas etapa 1a de desenvolvimento voce nao deve mudar nenhum dos prototipos abaixo...
void limpaMatriz(Tab *tabuleiro);
void imprimeMatriz(Tab *tabuleiro);
void copiaMatriz(Tab *mAnterior, Tab *mAtual);
void atualizaTabuleiro(Tab *mAtual, Tab *mAnterior);

void jogaJogoVida(Tab *tabuleiro, int invasora);

void inicBloco(Tab *tabuleiro, int xInic, int yInic);
void inicBote(Tab *tabuleiro, int xInic, int yInic);
void inicBlinker(Tab *tabuleiro, int xInic, int yInic);
void inicSapo(Tab *tabuleiro, int xInic, int yInic);
void inicGlider(Tab *tabuleiro, int xInic, int yInic);
void inicLWSS(Tab *tabuleiro, int xInic, int yInic);
void inicAleat(Tab *tabuleiro, int xInic, int yInic);

//Atencao!!!! Nas etapa 1b de desenvolvimento vc pode  alterar esse prot�tipo, sua respectiva chamada e defini��o
int menuInicJogo(Tab *tabuleiro);
void alocaMatriz(Tab *tabuleiro);
void freeMatriz(Tab *tabuleiro);
void ajustarPosicao(Tab *tabuleiro, int *xInic, int *yInic, int linhas, int colunas);
void lerArquivo(Tab *tabuleiro, char *nomeArquivo, int xInic, int yInic);

int verificarInvasores(Tab *matriz, int i, int j);
void criaInvasores(Tab *mAtual, Tab *mAnterior);


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////// In�cio da parte a ser alterada na etapa 1b   ///////////////////////////////////

int main()
{

    Tab tabuleiro;
    int continuar = 1, escolha, opcaoInicio, opcaoTab, opcaoCiclos, op, invasora;

    printf("Deseja iniciar a simulacao?\nDigite:\n(1)Sim (2)Nao\n");
    scanf("%d", &opcaoInicio);//leitura da opcao de inicio

    if(opcaoInicio == 1) //quando a opcao de inicio for 1, o jogo ira começar
    {
        printf("Digite o tamanho horizontal do tabuleiro:\n");
        scanf("%d", &tabuleiro.dim1);//define o tamanho horizontal do tabuleiro

        while(tabuleiro.dim1 <= 1 || tabuleiro.dim1 > 100)//se o tamanho for menor que 1 ou maior que 100, o usuario deve digitar novamente
        {
            printf("Digite um tamanho valido\n");
            scanf("%d", &tabuleiro.dim1);
        }

        printf("Digite o tamanho vertical do tabuleiro:\n");
        scanf("%d", &tabuleiro.dim2);//define o tamanho vertical do tabuleiro

        while(tabuleiro.dim2 <= 1 || tabuleiro.dim2 > 100)//se o tamanho for menor que 1 ou maior que 100, o usuario deve digitar novamente
        {
            printf("Digite um tamanho valido\n");
            scanf("%d", &tabuleiro.dim2);
        }

        alocaMatriz(&tabuleiro); //alocação dinamica do tabuleiro

        printf("Digite quantos ciclos deseja ver:\n");
        scanf("%d", &tabuleiro.ciclosVida);//define a quanidade de ciclos do jogo

        while(tabuleiro.ciclosVida <= 0)// se a quatidade de ciclos for negativa ou igual a zero, o usuario deve digitar novamente
        {
            printf("Digite um valor de ciclos valido\n");
            scanf("%d", &tabuleiro.ciclosVida);
        }

        while(continuar) //enquanto o usuario quiser continuar jogando
        {
            op = menuInicJogo(&tabuleiro);
            printf("iniciando jogo com opcao %d\n\n", op);
            DORME(TEMPO);
            invasora = (rand()%tabuleiro.ciclosVida) + 1;//define um ciclo aleatorio para o aparecimento dos invasores no jogo
            jogaJogoVida(&tabuleiro, invasora);//passa o tabuleiro e o ciclo de invasao para a funcao jogaJogoVida

            printf("Deseja continuar jogando?\n(1)Sim (2)Nao\n");
            scanf("%d", &escolha);//pergunta se o usuario deseja continuar jogando

            if(escolha == 2)//se não, o programa é encerrado
            {
                continuar = 0;//continuar é definido como 0, encerrando o loop
                printf("Encerrado\n");
            }

            if(escolha == 1)//se sim, o jogo continua
            {
                printf("Deseja alterar o tamanho do tabuleiro?\n(1)Sim (2)Nao\n");
                scanf("%d", &opcaoTab);//pergunta se o usuario deseja alterar o tamanho do tabuleiro

                while(opcaoTab < 1 || opcaoTab > 2)//se a opcao for diferente de 1 ou 2, o usuario deve digitar novamente
                {
                    printf("Opcao Invalida. Digite novamente:\n");
                    scanf("%d", &opcaoTab);
                }

                if(opcaoTab == 1)//se a opcao for 1, o usuario pode alterar o tamanho do tabuleiro
                {
                    printf("Digite o tamanho horizontal do tabuleiro:\n");
                    scanf("%d", &tabuleiro.dim1);

                    while(tabuleiro.dim1 <= 1)//se o tamanho for menor que 1, o usuario deve digitar novamente
                    {
                        printf("Digite um tamanho valido\n");
                        scanf("%d", &tabuleiro.dim1);
                    }

                    printf("Digite o tamanho vertical do tabuleiro:\n");
                    scanf("%d", &tabuleiro.dim2);

                    while(tabuleiro.dim2 <= 1)
                    {
                        printf("Digite um tamanho valido\n");
                        scanf("%d", &tabuleiro.dim2);
                    }

                }

                printf("Deseja mudar a quantidade de ciclos?\n(1)Sim (2)Nao\n");
                scanf("%d", &opcaoCiclos);//pergunta se o usuario deseja alterar a quantidade de ciclos

                while(opcaoCiclos < 1 || opcaoCiclos > 2)
                {
                    printf("Digite uma opçao valida.\n");
                    scanf("%d", &opcaoCiclos);
                }

                if(opcaoCiclos == 1)// se sim, o usuario pode alterar a quantidade de ciclos
                {
                    printf("Digite quantas vezes deseja ver:\n");
                    scanf("%d", &tabuleiro.ciclosVida);

                    while(tabuleiro.ciclosVida == 0)//se a quantidade de ciclos for igual a zero, o usuario deve digitar novamente
                    {
                        printf("Digite um valor de ciclos válido\n");
                        scanf("%d", &tabuleiro.ciclosVida);
                    }
                }
            }
        }
    }

    else//se a opcao de inicio for 2, o programa é encerrado
        printf("Encerrando programa\n");

    if(tabuleiro.m != NULL)//se a matriz do tabuleiro for diferente de NULL, a matriz é liberada
        freeMatriz(&tabuleiro);//libera a matriz do tabuleiro

    return 0;
}

void alocaMatriz(Tab *tabuleiro)
{
    int i;
    tabuleiro->m = (char**)malloc(tabuleiro->dim1 * sizeof(char*));
    if(tabuleiro->m == NULL)
    {
        printf("Nao foi possivel alocar\n");
        exit(1);
    }

    for(i = 0 ; i < tabuleiro->dim1 ; i++)
    {
        tabuleiro->m[i] = (char*)malloc(tabuleiro->dim2 * sizeof(char));
        if(tabuleiro->m[i] == NULL)
        {
            printf("Nao foi possivel alocar\n");
            exit(1);
        }
    }

}

void freeMatriz(Tab *matriz)
{
    int i;
    for(i = 0 ; i < matriz->dim1 ; i++)
        free(matriz->m[i]);

    free(matriz->m);
}

void ajustarPosicao(Tab *tabuleiro, int *xInic, int *yInic, int linhas, int colunas) //funcao que ajusta a posicao do padrao se o usuario digiou fora da matriz
{
    if (*xInic + linhas > tabuleiro->dim1)//se a linha inicial mais a quantidade de linhas for maior que a dimensao 1 do tabuleiro, a linha inicial é ajustada
        *xInic = tabuleiro->dim1 - linhas;
    if (*xInic < 0)//se a linha inicial for menor que zero, a linha inicial é ajustada
        *xInic = 0;
    if (*yInic + colunas > tabuleiro->dim2)//se a coluna inicial mais a quantidade de colunas for maior que a dimensao 2 do tabuleiro, a coluna inicial é ajustada
        *yInic = tabuleiro->dim2 - colunas;
    if (*yInic < 0)//se a coluna inicial for menor que zero, a coluna inicial é ajustada
        *yInic = 0;
}

void lerArquivo(Tab *tabuleiro, char *nomeArquivo, int xInic, int yInic) // Funcao para ler o arquivo no caso que o usuario escolher opcao 8
{
    FILE *arquivo;//ponteiro que irá apontar para o arquivo que será lido
    char linha[100], *separa;// vetor que irá armazenar a linha do arquivo e ponteiro que irá separar os valores da linha
    int linhaTab = 0, colunaTab , i = 0 , j , linhasPadrao = 0 , colunasPadrao = 0;

    //abre o arquivo para leitura
    arquivo = fopen(nomeArquivo, "r");

    if(!arquivo)//se não houver nada dentro do arquivo, exibe a mensagem de erro e para a função
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(linhaTab < tabuleiro->dim1)//enquanto a linha do tabuleiro for menor que a dimensão 1 do tabuleiro do arquivo o ciclo continua
    {
      if(!fgets(linha, sizeof(linha), arquivo))//Lê uma inha do arquivo e armazene na vetor linha, se não houver nada para ler, o ciclo é interrompido
      {
        break;
      }

      linhasPadrao++;//conta a quantidade de linhas do padrão
      colunasPadrao = 0;//reinicia o contador de colunas do padrão

      separa = strtok(linha, ",");//separa a string em "sub-strings" sempre que ele encontrar um vírgula na linha

      while(separa)//executara enquanto separa não for NULL
      {
          colunasPadrao++;//conta o número de colunas da padrão atual
          separa = strtok(NULL, ",");
      }
    }

    ajustarPosicao(tabuleiro, &xInic, &yInic, linhasPadrao, colunasPadrao);//chama a função para ajustar a posição do padrão

    rewind(arquivo); //volta o ponteiro para o inicio do arquivo

    limpaMatriz(tabuleiro);//limpa a matriz do tabuleiro, preenchendo todas as células com o valor padrão M

    //lê os dados do arquivo e preenche a matriz do tabuleiro
    while(linhaTab < tabuleiro->dim1)//enquanto a linha do tabuleiro for menor que a dimensão 1 do tabuleiro do arquivo o ciclo continua
    {
        if(!fgets(linha, sizeof(linha), arquivo))//para o looping caso não tenha mais linhas para ler
        {
          break;
        }

        j = 0;//renicia a variáve contadora j
        separa = strtok(linha, ",");//divide a linha em "sub-strings" separadas por víirgula

        while(separa)//executara enquanto separa não for NULL
        {
            colunaTab = atoi(separa);//converte o valor da "sub-string" para inteiro
            if(colunaTab >= 0 && colunaTab < tabuleiro->dim2)//verifica se a posição está dentro dos limites do tabuleiro
            {
                tabuleiro->m[xInic + i][yInic + j] = V;//preenche a matriz do tabuleiro com o valor V
            }
            separa = strtok(NULL, ",");//continua a separar a linha em "sub-strings"
            j++;//avança para a próxima coluna

        }
        linhaTab++;//avança para a proxima linha
        i++;//incrementa o índice linha i
    }

    fclose(arquivo);//fecha o arquivo após a leitura
}

int menuInicJogo(Tab *tabuleiro) // Funcao encarregada de inicia o jogo
{
    int opcao, xInic, yInic;
    char nomeArquivo[100];//vetor que irá armazenar o nome do arquivo

    limpaMatriz(tabuleiro);//limpa a matriz do tabuleiro, preenchendo todas as células com o valor padrão M

    printf("Qual padrao deseja executar?\n");
    printf("(1)Bloco\n(2)Bote\n(3)Blinker\n(4)Sapo\n(5)Glider\n(6)LWSS\n(7)Padrao aleatorio\n(8)Ler arquivo de dados.\nEntre com a opcao: ");
    scanf("%d", &opcao);

    while(opcao < 1 || opcao > 8)//se a opcao for diferente de 1 a 8, o usuario deve digitar novamente
    {
        printf("Opcao invalida. Digite novamente\n");
        scanf("%d", &opcao);
    }

        printf("Digite a linha inicial:\n");
        scanf("%d", &xInic);//leitura da linha inicial

        while(xInic < 0 || xInic >= tabuleiro->dim1)//se a linha inicial for menor que zero ou maior que a dimensão 1 do tabuleiro, o usuario deve digitar novamente
        {
            printf("Posicao invalida. Digite novamente.\n");
            printf("Digite a linha inicial novamente\n");
            scanf("%d", &xInic);
        }

        printf("Digite a coluna inicial:\n");
        scanf("%d", &yInic);//leitura da coluna inicial

        while(yInic < 0 || yInic >= tabuleiro->dim2)//se a coluna inicial for menor que zero ou maior que a dimensão 2 do tabuleiro, o usuario deve digitar novamente
        {
            printf("Posicao invalida. Digite novamente.\n");
            printf("Digite a coluna inicial novamente\n");
            scanf("%d", &yInic);
        }

    switch(opcao)
    {
    case 1:
        inicBloco(tabuleiro,xInic, yInic);
        break;
    case 2:
        inicBote(tabuleiro,xInic, yInic);
        break;
    case 3:
        inicBlinker(tabuleiro,xInic, yInic);
        break;
    case 4:
        inicSapo(tabuleiro,xInic, yInic);
        break;
    case 5:
        inicGlider(tabuleiro,xInic, yInic);
        break;
    case 6:
        inicLWSS(tabuleiro,xInic, yInic);
        break;
    case 7:
        inicAleat(tabuleiro,xInic, yInic);
        break;
        case 8: printf("Digite o nome do arquivo:\n");
                scanf("%s", nomeArquivo);//leitura do nome do arquivo
                lerArquivo(tabuleiro, nomeArquivo, xInic, yInic);//chama a função para ler o arquivo
                break;
    }

    imprimeMatriz(tabuleiro);
    printf("Se a inicializacao estiver correta digite qualquer tecla para iniciar o jogo...");
    while(getchar()!='\n');
    getchar();

    return opcao;

}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Inicio da Parte a ser completada na Etapa 1 /////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void imprimeMatriz(Tab *matriz) //funcao encarregada de fazer a impressao da matriz na tela
{
    int i, j;
    for(i = 0 ; i < matriz->dim1 ; i++)
    {
        for(j = 0 ; j < matriz->dim2 ; j++)
        {
            printf("%c ", matriz->m[i][j]);
        }
        printf("\n");
    }
}

void copiaMatriz(Tab *mAnterior, Tab *mAtual) //funcao encarregada de controlar as geracoes
{
    int i, j;
    for(i = 0 ; i < mAnterior->dim1 ; i++)
    {
        for(j = 0 ; j < mAnterior->dim2 ; j++)
        {
            mAnterior->m[i][j] = mAtual->m[i][j];
        }
    }
}

int verificarVivos(Tab *matriz, int i, int j)  //funcao encarregada de contar as celulas vivas proximas de uma determinada casa
{
    int vivos = 0;

    if (j + 1 < matriz->dim2 && matriz->m[i][j + 1] == V)//verifica se a celula a direita da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (j - 1 >= 0 && matriz->m[i][j - 1] == V)//verifica se a celula a esquerda da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i + 1 < matriz->dim1 && matriz->m[i + 1][j] == V)//verifica se a celula abaixo da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i - 1 >= 0 && matriz->m[i - 1][j] == V)//verifica se a celula acima da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i - 1 >= 0 && j - 1 >= 0 && matriz->m[i - 1][j - 1] == V)//verfia se a celula na diagonal superior esquerda é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i - 1 >= 0 && j + 1 < matriz->dim2 && matriz->m[i - 1][j + 1] == V)//verifica se a celua na diagonal superior direita da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i + 1 < matriz->dim1 && j - 1 >= 0 && matriz->m[i + 1][j - 1] == V)//verifica se a celula na diagonal inferior esquerda da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;
    if (i + 1 < matriz->dim1 && j + 1 < matriz->dim2 && matriz->m[i + 1][j + 1] == V)//verifica se a diagonal inferior direita da casa atual é viva, se for, incrementa o contador de celulas vivas
        vivos++;

    return vivos;//retorna a quantidade de vivos
}


void atualizaTabuleiro(Tab *mAtual, Tab *mAnterior) //funcao encarregada de atualizar o tabuleiro seguindo as regras do jogo
{
    int i, j, raid, vivos;

    for(i = 0 ; i < mAnterior->dim1 ; i++)
    {
        for(j = 0 ; j < mAnterior->dim2 ; j++)
        {
            raid = verificarInvasores(mAnterior, i, j);//chama a função para verificar a quantidade de invasores vivos
            vivos = verificarVivos(mAnterior, i, j);//chama a função para verfificar a quantidade de celulas vivas

            if (mAnterior->m[i][j] == V) //se detectar celula viva, morre de solidao/sobrepopulacao ou não
            {
                if (vivos < 2 || vivos > 3)//se a quantidade de vivos for menor que 2 ou maior que três, a celula morre
                    mAtual->m[i][j] = M;
                else
                    mAtual->m[i][j] = V;//se não, a celula vive
            }

            else //se detetar celula morta, revive se tiver exatamente 3 vivas ao redor
            {
                if (vivos == 3)//se a celula tiver exatemente 3 vizinhas, ela sobrevive
                    mAtual->m[i][j] = V;
                else//se não, morre
                    mAtual->m[i][j] = M;
            }

            if(raid) //If designado para aplicar as regras ás invasoras
            {
                if(mAnterior->m[i][j] == V)
                {
                    if(raid > 2 || raid < 4)//se tiver 2-3 invasores ao redor, VIVO vira INVASOR
                        mAtual->m[i][j] = A;
                    else if(vivos > raid)//se a quantidade de vivos ao redor sobrepassa, invasor MORRE
                        mAtual->m[i][j] = M;
                }

                if(mAnterior->m[i][j] == A) //logica das celulas INVASORAS para sobrepopulacao/solidao
                {
                    if (raid < 2 || raid > 3)//se a quantidade de invasoras for menor que 2 ou maior que três, a invasora morre
                        mAtual->m[i][j] = M;
                    else//se não, a invasora vive
                        mAtual->m[i][j] = A;
                }
            }
        }
    }
}
int verificarInvasores(Tab *matriz, int i, int j) //funcao encarregada de contar as celulas invasoras proximas de uma determinada casa
{
    int inv = 0;

    if(j + 1 < matriz->dim2 && matriz->m[i][j + 1] == A)//verifica se existe uma célula à direita e se ela é uma célula invasora.
        inv++;
    if(j - 1 >= 0 && matriz->m[i][j - 1] == A)//verifica se existe uma célula à esquerda e se ela é uma célula invasora.
        inv++;
    if(i + 1 < matriz->dim1 && matriz->m[i + 1][j] == A)//verifica se existe uma célula à acima e se ela é uma célula invasora.
        inv++;
    if(i - 1 >= 0 && matriz->m[i - 1][j] == A)//verifica se existe uma célula abaixo e se ela é uma célula invasora.
        inv++;
    if(i - 1 >= 0 && j - 1 >= 0 && matriz->m[i - 1][j - 1] == A)//verifica se existe uma célula na diagonal superior esquerda e se ela é uma célula invasora.
        inv++;
    if(i - 1 >= 0 && j + 1 < matriz->dim2 && matriz->m[i - 1][j + 1] == A)//verifica se existe uma célula na diagonal superior direita e se ela é uma célula invasora.
        inv++;
    if(i + 1 < matriz->dim1 && j - 1 >= 0 && matriz->m[i + 1][j - 1] == A)//verifica se existe uma célula na diagonal inferior esquerda e se ela é uma célula invasora.
        inv++;
    if(i + 1 < matriz->dim1 && j + 1 < matriz->dim2 && matriz->m[i + 1][j + 1] == A)//verifica se existe uma célula na diagonal inferior direita e se ela é uma célula invasora.
        inv++;

    return inv;//retorna a quantidade de invasoras
}

void criaInvasores(Tab *mAtual, Tab *mAnterior) //funcao encarregada de ativar a invasao no jogo
{
    int i, j, aleat = 1;
    srand(time(NULL));

    for(i = 0 ; i < mAnterior->dim1 ; i++) //loop designado para prencher algumas vivas como invasoras
    {
        for(j = 0 ; j < mAnterior->dim2 ; j++)
        {
            if(aleat > 500)//se o valor aleatório for maior que 500 e a célula for uma célula viva, ela será transformada em uma célula invasora
                if(mAnterior->m[i][j] == V)
                    mAtual->m[i][j] = A;
            aleat = rand() % 999;//gera um novo número aleatório entre 0 e 998 para a próxima iteração.
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FIM da Parte a ser completada ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


void jogaJogoVida(Tab *tabuleiro, int invasora) // Funcao encarregada de utilizar todas as demais funcoes para rodar o jogo
{
    Tab mAnterior; // Declaracao do tabuleiro tipo tab
    int c;

    mAnterior.dim1 = tabuleiro->dim1;//atribui a tamanho horizontal do tabuleiro a matriz anterior
    mAnterior.dim2 = tabuleiro->dim2;//atribui a tamanho vertical do tabuleiro a matriz anterior

    alocaMatriz(&mAnterior);//aloca dinâmicamente a matriz anterior

    system(LIMPATELA);
    imprimeMatriz(&mAnterior);//imprime a matriz anterior
    DORME(TEMPO);

    for(c=1; c <= tabuleiro->ciclosVida; c++)
    {
        copiaMatriz(&mAnterior, tabuleiro);//copia a matriz anteirior
        atualizaTabuleiro(tabuleiro, &mAnterior);//atuaiza a matriz anterior conforme o jogo segue

        if(c == invasora)//quando o numero de ciclo for igual ao ciclo geradado aleatóriamente, a invasao irá começar
        {
            printf("A invasao comecou!!!\n");
            criaInvasores(tabuleiro, &mAnterior);//envia o tabuleiro e a matriz anterior para a funçã cria invasores
            DORME(TEMPO);
        }
        system(LIMPATELA);
        imprimeMatriz(tabuleiro);
        // getchar();
        DORME(TEMPO);
    }

    freeMatriz(&mAnterior);//libera memória da matriz anterior

}

////////////////////////////////////////////////
void limpaMatriz(Tab *tabuleiro) //funcao encarregada de limpar toda matriz dinamica que seja inserida
{
    int i,j;
    for(i = 0 ; i < tabuleiro->dim1 ; i++)
    {
        for(j = 0 ; j < tabuleiro->dim2 ; j++)
        {
            tabuleiro->m[i][j] = M;
        }
    }
}

////////////////////////////////////////////////

//A partir de aqui comecam as funcoes dedicadas para cada padrao que pode ser usado no jogo

void inicBloco(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[2][2] = {{V, V}, {V, V}};
    int i, j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 2, 2);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if(xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic + i][yInic + j] = padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão
        }
    }
}

////////////////////////////////////////////////
void inicBote(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[3][3]= {{V,V,M},{V,M,V},{M,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 3, 3);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão
        }
    }
}
////////////////////////////////////////////////
void inicBlinker(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[1][3] = {{V, V, V}};
    int i, j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 1, 3);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0; i < 1; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic + i][yInic + j] = padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão

        }
    }
}



////////////////////////////////////////////////
void inicSapo(Tab *tabuleiro, int xInic, int yInic)
{

    char padrao[2][4]= {{M,V,V,V},{V,V,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 2, 4);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0; i < 2; i++)
    {
        for(j = 0 ; j < 4; j++)
        {
            if(xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão
        }
    }
}



////////////////////////////////////////////////
void inicGlider(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[3][3]= {{V,V,V},{V,M,M},{M,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 3, 3);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão
        }
    }
}

////////////////////////////////////////////////
void inicLWSS(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[4][5]= {{M,V,M,M,V},{V,M,M,M,M},{V,M,M,M,V},{V,V,V,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 4, 5);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];//se estiver dentro dos limites, o tabuleiro ira receber o padrão
        }
    }
}

void inicAleat(Tab *tabuleiro, int xInic, int yInic)//gera um padrão aleatório
{
    int i, j, estado;
    srand(time(NULL));

    ajustarPosicao(tabuleiro, &xInic, &yInic, 5, 5);//chama a função para ajustar a posição caso o usuario tenha digitado para fora dos limites


    for(i = 0 ; i < 5 ; i++)
    {
        for(j = 0 ; j < 5 ; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)//verifica se a posição está dentro dos limites
            {
                estado = rand() % 2;//gera um número aleatório para definir se a celula será gerada aleatoriamente viva ou morta

                if(estado == 1)//se o estado for igua a 1, a célula aparecera viva
                    tabuleiro->m[xInic + i][yInic + j] = V;

                else//se não, aparecera morta
                    tabuleiro->m[xInic + i][yInic + j] = M;
            }
        }

    }
}
