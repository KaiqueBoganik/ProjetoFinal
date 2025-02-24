#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//windows-msvc-x64
#define V 'X'
#define M '.'
#define MAXL 100
#define MAXC 100
#define TAM 50
#define A 'O'


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
#define TEMPO 100
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
void jogaJogoVida(Tab *tabuleiro , int spawnInvasora);

void inicBloco(Tab *tabuleiro, int xInic, int yInic , int tipo);
void inicBote(Tab *tabuleiro, int xInic, int yInic , int tipo);
void inicBlinker(Tab *tabuleiro, int xInic, int yInic, int tipo);
void inicSapo(Tab *tabuleiro, int xInic, int yInic, int tipo);
void inicGlider(Tab *tabuleiro, int xInic, int yInic);
void inicLWSS(Tab *tabuleiro, int xInic, int yInic);
void inicAleat(Tab *tabuleiro, int xInic, int yInic);

//Atencao!!!! Nas etapa 1b de desenvolvimento vc pode  alterar esse prot�tipo, sua respectiva chamada e defini��o
int menuInicJogo(Tab *tabuleiro);
void alocaMatriz(Tab *tabuleiro);
void freeMatriz(Tab *tabuleiro);
void ajustarPosicao(Tab *tabuleiro, int *xInic, int *yInic, int linhas, int colunas);
void lerArquivo(Tab *tabuleiro, char *nomeArquivo, int xInic, int yInic);
void invasao(Tab *tabuleiro);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////// In�cio da parte a ser alterada na etapa 1b   ///////////////////////////////////

int main()
{

    Tab tabuleiro;
    int continuar = 1, escolha, opcaoInicio, opcaoTab, opcaoCiclos, op , spawnInvasora;

    printf("Deseja inciar a simulação?\nDigite:\n(1)Sim(2)Não\n");
    scanf("%d", &opcaoInicio);

    if(opcaoInicio == 1)
    {
        printf("Digite o tamanho horizontal do tabuleiro:\n");
        scanf("%d", &tabuleiro.dim1);

        while(tabuleiro.dim1 <= 1)
        {
            printf("Digite um tamanho válido\n");
            scanf("%d", &tabuleiro.dim1);
        }

        printf("Digite o tamanho vertical do tabuleiro:\n");
        scanf("%d", &tabuleiro.dim2);

        while(tabuleiro.dim2 <= 1)
        {
            printf("Digite um tamanho válido\n");
            scanf("%d", &tabuleiro.dim2);
        }

        alocaMatriz(&tabuleiro);

        printf("Digite quantos ciclos deseja ver:\n");
        scanf("%d", &tabuleiro.ciclosVida);

        while(tabuleiro.ciclosVida <= 0)
        {
            printf("Digite um valor de ciclos válido\n");
            scanf("%d", &tabuleiro.ciclosVida);
        }

        spawnInvasora = rand() % tabuleiro.ciclosVida;

        while(continuar)
        {
            op = menuInicJogo(&tabuleiro);
            printf("iniciando jogo com opcao %d\n\n", op);
            DORME(TEMPO);
            jogaJogoVida(&tabuleiro , spawnInvasora);

            printf("Deseja continuar jogando?\n(1)Sim(2)Não\n");
            scanf("%d", &escolha);

            if(escolha == 2)
            {
                continuar = 0;
                printf("Encerrado\n");
            }

            if(escolha == 1)
            {
                printf("Deseja alterar o tamanho do tabuleiro?\n(1)Sim(2)Não\n");
                scanf("%d", &opcaoTab);

                while(opcaoTab < 1 || opcaoTab > 2)
                {
                    printf("Opcao Inválida. Digite novamente:\n");
                    scanf("%d", &opcaoTab);
                }

                if(opcaoTab == 1)
                {
                    printf("Digite o tamanho horizontal do tabuleiro:\n");
                    scanf("%d", &tabuleiro.dim1);
                    while(tabuleiro.dim1 <= 1)
                    {
                        printf("Digite um tamanho válido\n");
                        scanf("%d", &tabuleiro.dim1);
                    }

                    printf("Digite o tamanho vertical do tabuleiro:\n");
                    scanf("%d", &tabuleiro.dim2);
                    while(tabuleiro.dim2 <= 1)
                    {
                        printf("Digite um tamanho válido\n");
                        scanf("%d", &tabuleiro.dim2);
                    }

                }


                printf("Deseja mudar a quantidade de ciclos?\n(1)Sim(2)Não\n");
                scanf("%d", &opcaoCiclos);

                while(opcaoCiclos < 1 || opcaoCiclos > 2)
                {
                    printf("Digite uma opção válida.\n");
                    scanf("%d", &opcaoCiclos);
                }

                if(opcaoCiclos == 1)
                {
                    printf("Digite quantas vezes deseja ver:\n");
                    scanf("%d", &tabuleiro.ciclosVida);

                    while(tabuleiro.ciclosVida == 0)
                    {
                        printf("Digite um valor de ciclos válido\n");
                        scanf("%d", &tabuleiro.ciclosVida);
                    }
                }
            }
        }
    }

    else
        printf("Encerrando programa\n");

    if(tabuleiro.m != NULL)
        freeMatriz(&tabuleiro);

    return 0;
}

void alocaMatriz(Tab *tabuleiro)
{
    int i;
    tabuleiro->m = (char**)malloc(tabuleiro->dim1 * sizeof(char*));
    if(tabuleiro->m == NULL)
    {
        printf("Não foi possível alocar\n");
        exit(1);
    }

    for(i = 0 ; i < tabuleiro->dim1 ; i++)
    {
        tabuleiro->m[i] = (char*)malloc(tabuleiro->dim2 * sizeof(char));
        if(tabuleiro->m[i] == NULL)
        {
            printf("Não foi possível alocar\n");
            exit(1);
        }
    }

}

void freeMatriz(Tab *matriz)
{
    int i;

    for(i = 0 ; i < matriz->dim1 ; i++)
    {
        free(matriz->m[i]);
    }

    free(matriz->m);
}

void ajustarPosicao(Tab *tabuleiro, int *xInic, int *yInic, int linhas, int colunas)
{
    if (*xInic + linhas > tabuleiro->dim1)
    {
        *xInic = tabuleiro->dim1 - linhas;
    }

    if (*xInic < 0)
    {
        *xInic = 0;
    }

    if (*yInic + colunas > tabuleiro->dim2)
    {
        *yInic = tabuleiro->dim2 - colunas;
    }

    if (*yInic < 0)
    {
        *yInic = 0;
    }
}

void lerArquivo(Tab *tabuleiro, char *nomeArquivo, int xInic, int yInic)
{
    FILE *arquivo;
    char linha[100], *separa;
    int linhaTab = 0, colunaTab , i = 0 , j , linhasPadrao = 0 , colunasPadrao = 0;

    arquivo = fopen(nomeArquivo, "r");

    if(!arquivo)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(linhaTab < tabuleiro->dim1) 
    {
      if(!fgets(linha, sizeof(linha), arquivo))
      {
        break;
      }
      
      linhasPadrao++;
      colunasPadrao = 0;

      separa = strtok(linha, ",");

      while(separa) 
      {
          colunasPadrao++;
          separa = strtok(NULL, ",");
      }
    }

    ajustarPosicao(tabuleiro, &xInic, &yInic, linhasPadrao, colunasPadrao);

    rewind(arquivo);

    limpaMatriz(tabuleiro);

    while(linhaTab < tabuleiro->dim1)
    {
        if(!fgets(linha, sizeof(linha), arquivo))
        {
          break;
        }

        j = 0;  
        separa = strtok(linha, ",");

        while(separa)
        {
            colunaTab = atoi(separa);
            if(colunaTab >= 0 && colunaTab < tabuleiro->dim2)
            {
                tabuleiro->m[xInic + i][yInic + j] = V;
            }
            separa = strtok(NULL, ",");
            j++;
        }
        linhaTab++;
        i++;
    }

    fclose(arquivo);
}

void invasao(Tab *tabuleiro)
{
    int padrao , posXinimigo , posYinimigo , tipo = 2;
    srand(time(NULL));

    padrao = 3; 
    posXinimigo = rand() % tabuleiro->dim1;
    posYinimigo = rand() % tabuleiro->dim2;


    switch(padrao)
    {
        case 1:inicBloco(tabuleiro,posXinimigo, posYinimigo , tipo);break;
        case 2:inicBote(tabuleiro,posXinimigo, posYinimigo, tipo);break;
        case 3:inicBlinker(tabuleiro,posXinimigo, posYinimigo, tipo);break;
        case 4:inicSapo(tabuleiro,posXinimigo, posYinimigo, tipo);break;
        case 5:inicGlider(tabuleiro,posXinimigo, posYinimigo);break;
        case 6:inicLWSS(tabuleiro,posXinimigo, posYinimigo);break;
        case 7:inicAleat(tabuleiro,posXinimigo, posYinimigo); break;
    }

    printf("Invasão Começou!");
}


int menuInicJogo(Tab *tabuleiro)
{
    int opcao, xInic, yInic , tipo = 1;
    char nomeArquivo[100];

    limpaMatriz(tabuleiro);

    printf("Qual padrão deseja executar?\n");
    printf("(1)Bloco\n(2)Bote\n(3)Blinker\n(4)Sapo\n(5)Glider\n(6)LWSS\n(7)Padrão aleatorio\n(8)Ler arquivo de dados.\nEntre com a opcao: ");
    scanf("%d", &opcao);

    while(opcao < 1 || opcao > 8)
    {
        printf("Opção inválida. Digite novamenete\n");
        scanf("%d", &opcao);
    }

        printf("Digite a linha inicial:\n");
        scanf("%d", &xInic);

        while(xInic < 0 || xInic >= tabuleiro->dim1)
        {
            printf("Posição inválida. Digite novamente.\n");
            printf("Digite a linha inicial novamente\n");
            scanf("%d", &xInic);
        }

        printf("Digite a coluna inicia:\n");
        scanf("%d", &yInic);

        while(yInic < 0 || yInic >= tabuleiro->dim2)
        {
            printf("Posição inválida. Digite novamente.\n");
            printf("Digite a coluna inicial novamente\n");
            scanf("%d", &yInic);
        }

 
    switch(opcao)
    {
        case 1:inicBloco(tabuleiro,xInic, yInic , tipo);break;
        case 2:inicBote(tabuleiro,xInic, yInic, tipo);break;
        case 3:inicBlinker(tabuleiro,xInic, yInic, tipo);break;
        case 4:inicSapo(tabuleiro,xInic, yInic, tipo);break;
        case 5:inicGlider(tabuleiro,xInic, yInic);break;
        case 6:inicLWSS(tabuleiro,xInic, yInic);break;
        case 7:inicAleat(tabuleiro,xInic, yInic); break;
        case 8: printf("Digite o nome do arquivo:\n");
            scanf("%s", nomeArquivo);
            lerArquivo(tabuleiro, nomeArquivo, xInic, yInic);
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

void imprimeMatriz(Tab *matriz)
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

void copiaMatriz(Tab *mAnterior, Tab *mAtual)
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

int verificarVivos(Tab *matriz, int i, int j)
{
    int vivos = 0;

    if(j + 1 < matriz->dim2 && (matriz->m[i][j + 1] == V || matriz->m[i][j + 1] == A))
        vivos++;

    if(j - 1 >= 0 && (matriz->m[i][j - 1] == V || matriz->m[i][j - 1] == A))
        vivos++;

    if(i + 1 < matriz->dim1 && (matriz->m[i + 1][j] == V || matriz->m[i + 1][j] == A))
        vivos++;

    if(i - 1 >= 0 && (matriz->m[i - 1][j] == V || matriz->m[i - 1][j] == A))
        vivos++;

    if(i - 1 >= 0 && j - 1 >= 0 && (matriz->m[i - 1][j - 1] == V || matriz->m[i - 1][j - 1] == A))
        vivos++;

    if(i - 1 >= 0 && j + 1 < matriz->dim2 && (matriz->m[i - 1][j + 1] == V || matriz->m[i - 1][j + 1] == A))
        vivos++;

    if(i + 1 < matriz->dim1 && j - 1 >= 0 && (matriz->m[i + 1][j - 1] == V || matriz->m[i + 1][j - 1] == A))
        vivos++;

    if(i + 1 < matriz->dim1 && j + 1 < matriz->dim2 && (matriz->m[i + 1][j + 1] == V || matriz->m[i + 1][j + 1] == A))
        vivos++;

    return vivos;
}

void atualizaTabuleiro(Tab *mAtual, Tab *mAnterior)
{
    int i, j, vivos;

    for(i = 0 ; i < mAnterior->dim1 ; i++)
    {
        for(j = 0 ; j < mAnterior->dim2 ; j++)
        {
            vivos = verificarVivos(mAnterior, i, j);

            if (mAnterior->m[i][j] == V || mAnterior->m[i][j] == A)
            {
                if (vivos < 2 || vivos > 3)
                {
                    mAtual->m[i][j] = M;
                }

                else
                {
                    mAtual->m[i][j] = mAnterior->m[i][j];
                }
            }

            else
            {
                if(vivos == 3)
                {
                    if(mAnterior->m[i][j] == A)
                    {
                        mAtual->m[i][j] = A;
                    }

                    else
                        mAtual->m[i][j] = V;
                }
                else
                {
                    mAtual->m[i][j] = M;
                }
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FIM da Parte a ser completada ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


void jogaJogoVida(Tab *tabuleiro , int spawnInvasora)
{
    Tab mAnterior;
    int c;

    mAnterior.dim1 = tabuleiro->dim1;
    mAnterior.dim2 = tabuleiro->dim2;

    alocaMatriz(&mAnterior);

    system(LIMPATELA);
    imprimeMatriz(&mAnterior);
    DORME(TEMPO);

    for(c=1; c <= tabuleiro->ciclosVida; c++)
    {
        if(c == spawnInvasora)
        {   
            printf("A invasão começou\n");
            invasao(tabuleiro);
        }
        copiaMatriz(&mAnterior, tabuleiro);

        atualizaTabuleiro(tabuleiro, &mAnterior);

        system(LIMPATELA);
        imprimeMatriz(tabuleiro);
        // getchar();
        DORME(TEMPO);
    }

    freeMatriz(&mAnterior);

}

////////////////////////////////////////////////
void limpaMatriz(Tab *tabuleiro)
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
void inicBloco(Tab *tabuleiro, int xInic, int yInic , int tipo)
{
   
    char padrao[2][2];
    int i, j , populacao;

    if(tipo == 1)
    {
        populacao = V;
    }

    else if(tipo == 2)
    {
        populacao = A;
    }

    else
    {
        populacao = M;
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            padrao[i][j] = populacao;
        }
    }

    ajustarPosicao(tabuleiro, &xInic, &yInic, 2, 2);

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if(xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
                tabuleiro->m[xInic + i][yInic + j] = padrao[i][j];
        }
    }
}

////////////////////////////////////////////////
void inicBote(Tab *tabuleiro, int xInic, int yInic , int tipo)
{
    int i,j , populacao;

    if(tipo == 1)
    {
        populacao = V;
    }

    else if(tipo == 2)
    {
        populacao = A;
    }

    else
    {
        populacao = M;
    }

    char padrao[3][3] = {{populacao, populacao , M} , {populacao, M , populacao} , {M , populacao , M}};

    ajustarPosicao(tabuleiro, &xInic, &yInic, 3, 3);

    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];
        }
    }
}
////////////////////////////////////////////////
void inicBlinker(Tab *tabuleiro, int xInic, int yInic, int tipo) 
{
    char padrao[1][3];
    int i, j, populacao;

    if (tipo == 1) 
    {
        populacao = V; 
    } 
    
    else if (tipo == 2) 
    {
        populacao = A; 
    } 
    
    else 
    {
        populacao = M; 
    }

  
    char padraoBlinker[1][3] = {{populacao, populacao, populacao}};

    for(i = 0; i < 1; i++) 
    {
        for(j = 0; j < 3; j++) 
        {
            padrao[i][j] = padraoBlinker[i][j];
        }
    }

    ajustarPosicao(tabuleiro, &xInic, &yInic, 1, 3);

    for(i = 0; i < 1; i++) 
    {
        for(j = 0; j < 3; j++) 
        {
            if(xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2) 
                tabuleiro->m[xInic + i][yInic + j] = padrao[i][j];
        }
    }
}



////////////////////////////////////////////////
void inicSapo(Tab *tabuleiro, int xInic, int yInic, int tipo)
{
    int i,j , populacao;

    if(tipo == 1)
    {
        populacao = V;
    }

    else if(tipo == 2)
    {
        populacao = A;
    }

    else
    {
        populacao = M;
    }

    char padrao[2][4] = {{M , populacao , populacao , populacao} , {populacao, populacao , populacao , M}};
    ajustarPosicao(tabuleiro, &xInic, &yInic, 2, 4);

    for(i = 0; i < 2; i++)
    {
        for(j = 0 ; j < 4; j++)
        {
            if(xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];
        }
    }
}



////////////////////////////////////////////////
void inicGlider(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[3][3]= {{V,V,V},{V,M,M},{M,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 3, 3);

    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];
        }
    }
}

////////////////////////////////////////////////
void inicLWSS(Tab *tabuleiro, int xInic, int yInic)
{
    char padrao[4][5]= {{M,V,M,M,V},{V,M,M,M,M},{V,M,M,M,V},{V,V,V,V,M}};
    int i,j;

    ajustarPosicao(tabuleiro, &xInic, &yInic, 4, 5);

    for(i = 0; i < 3; i++)
    {
        for(j = 0 ; j < 3; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
                tabuleiro->m[xInic+i][yInic+j]=padrao[i][j];
        }
    }
}

void inicAleat(Tab *tabuleiro, int xInic, int yInic)
{
    int i, j, estado;
    srand(time(NULL));

    ajustarPosicao(tabuleiro, &xInic, &yInic, 5, 5);

    for(i = 0 ; i < 5 ; i++)
    {
        for(j = 0 ; j < 5 ; j++)
        {
            if (xInic + i < tabuleiro->dim1 && yInic + j < tabuleiro->dim2)
            {
                estado = rand() % 2;

                if(estado == 1)
                    tabuleiro->m[xInic + i][yInic + j] = V;

                else
                    tabuleiro->m[xInic + i][yInic + j] = M;
            }
        }

    }
}