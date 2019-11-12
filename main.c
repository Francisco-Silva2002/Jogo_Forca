#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "forca.c"
#include "forca.h"

void copyright(){
    CLEAR_SCREEN;
    printf("=============================================================\n\n");
    printf("JOGO DA FORCA\n");
    printf("Desenvolvido por: \n\t18464 - Francisco Eduardo Pereira Sousa Silva\n");
    printf("\t18457 - Clayton Gabriel Lorizolla\n");
    printf("\t18465 - Gabriel Issac da Silva\n");
    printf("=============================================================\n\n");
}

void menu(){
    CLEAR_SCREEN;
    printf("*********************************");
    printf("\n*\t1 - Configuracoes\t*");
    printf("\n*\t2 - Jogar\t\t*");
    printf("\n*\t0 - Sair\t\t*");
    printf("\n*********************************\n");
}

void desenhaF(int e){
    printf("%c%c%c%c%c%c%c%c%c%c\n", 201,205,205,205,205,205,205,205,205,184);

    printf("%c%c", 186,179);
    cabeca(e);
    printf("\n");
    printf("%c\t",186);
    corpo1(e);
    printf("%c\t",186);
    corpo2(e);
    printf("%c\t", 186);
    //printf("\n");

    pernaesquerda(e);
    pernadireita(e);
    //printf("%c%c\n%c\n%c\n%c\n%c\n%c\n", 186, 179,186,186,186,186,186,186);
    printf("%c%c%c%c%c", 205,205,205,205,205);
}

void cabeca(int e){
    if(e >= 1)
        printf("\t O");
}

void corpo1(int e){
    if(e >= 2){
        if(e>=4){
            bracoesquerdo(e);
        }
        else{
            printf(" ");
        }
        printf("|");
        bracodireito(e);
    }
    else
        printf("\n");
}

void corpo2(int e){
    if(e>=3){
        printf(" |\n");
    }
    else
        printf("\n");
}

void bracoesquerdo(int e){
    if(e>=4)
        printf("/");
    else
        printf("\n");
}

void bracodireito(int e){
    if(e>=5)
        printf("\\\n");
    else
        printf("\n");
}

void pernaesquerda(int e){
    if(e>=6)
        printf("/");
    else
        printf("\n");
}

void pernadireita(int e){
    if(e>=7)
        printf(" \\\n");
    else
        printf("\n");
}

int calculaTentativas(NoSorteada* l){
    int qnt = 0;
    for(NoSorteada* p=l;p!=NULL;p=p->proximo){
        qnt++;
    }

    qnt += 3;
    return qnt;
}

int main(int argc, char *argv[])
{
    /* INÍCIO VARIÁVEIS DE JOGO */
    char dica[101];
    char nome[255] = "Player";
    char palpite;
    int op = 1;
    int itemMenu = 1;
    int tentativas = 0;
    NoSorteada * palavraSorteada;
    char* letrasUsadas = (char*) malloc(255*sizeof(char));
    int qntLetrasUsadas = 0;
    int qntPalp = 0;
    int erros = 0;
    /* FIM VARIÁVEIS DE JOGO */

    NoSecreto * lstSecreta = inicializaListaSecreta();
    char fNameArq[255];
    NoSecreto * sorteada;
    int posSorteada=0;
    int tamanhoLista=0;

    //strcpy(fNameArq,"palavras.dat");

    if(argc>1){
      strcpy(fNameArq,argv[1]);
    }

    printf("Arquivo de dados: %s\n\n",fNameArq);

    copyright();
    getchar();

    while(itemMenu != 0){
        CLEAR_SCREEN;
        if(op == 0)
            break;

        menu();
        scanf("%i", &itemMenu);

        if(itemMenu == 1){
            CLEAR_SCREEN;
            setbuf(stdin,NULL);
            printf("Digite seu nome de usuario: ");
            scanf("%[^\n]s", &nome);
        }

        if(itemMenu == 2)
        {
            lstSecreta = carregaListaArquivo(lstSecreta,fNameArq);
            //imprimeListaSecreta(lstSecreta);
            tamanhoLista = tamanhoListaSecreta(lstSecreta);

            do{
                CLEAR_SCREEN;
                //imprimeListaSecreta(lstSecreta);

                sorteada= sorteiaPalavra(lstSecreta);
                if(sorteada!=NULL){
                    strcpy(dica, sorteada->assunto);
                    palavraSorteada = transformaPalavraEmLista(palavraSorteada, sorteada->palavra);
                    tentativas = calculaTentativas(palavraSorteada);
                    qntPalp = 0;
                    setbuf(stdin, NULL);
                    printf("Voce tem %i tentativas para acertar a palavra!", tentativas);
                    getchar();
                    do{
                        CLEAR_SCREEN;

                        if(tentativas == 0 || erros == 9){
                            letrasUsadas[0] = '\0';
                            qntLetrasUsadas = 0;
                            printf("\nPuxa, voce foi enforcado!\n");
                            printf("A palavra era ");
                            printf("**");
                            imprimePalavraSorteada(palavraSorteada);
                            printf("**\n");

                            printf("    _______________         \n");
                            printf("   /               \\       \n");
                            printf("  /                 \\      \n");
                            printf("//                   \\/\\  \n");
                            printf("\\|   XXXX     XXXX   | /   \n");
                            printf(" |   XXXX     XXXX   |/     \n");
                            printf(" |   XXX       XXX   |      \n");
                            printf(" |                   |      \n");
                            printf(" \\__      XXX      __/     \n");
                            printf("   |\\     XXX     /|       \n");
                            printf("   | |           | |        \n");
                            printf("   | I I I I I I I |        \n");
                            printf("   |  I I I I I I  |        \n");
                            printf("   \\_             _/       \n");
                            printf("     \\_         _/         \n");
                            printf("       \\_______/           \n");
                            erros = 0;
                            getchar();
                            break;
                        }

                        printf("DICA: %s\n\n", dica);
                        desenhaF(erros);
                        imprimeForca(palavraSorteada);
                        printf("\n\nTentativas Restantes: %i", tentativas);
                        tentativas--;
                        printf("\nDigite o seu palpite: ");
                        scanf("%c", &palpite);
                        palpite = tolower(palpite);
                        qntPalp++;
                        if(qntLetrasUsadas == 0){
                            adicionaLetra(letrasUsadas, palpite, 1);
                            qntLetrasUsadas++;
                        }
                        else{
                            if(buscaLetra(letrasUsadas, palpite, qntLetrasUsadas) == 0){
                                adicionaLetra(letrasUsadas, palpite, qntLetrasUsadas);
                                qntLetrasUsadas++;
                            }
                            else{
                                printf("\nEssa letra ja foi usada!");
                                qntPalp--;
                                tentativas++;
                                setbuf(stdin, NULL);
                                getchar();
                                continue;
                            }
                        }

                        setbuf(stdin, NULL);
                        if(verificarLetra(palavraSorteada, palpite) == 0){
                            printf("\nNao ha essa letra");
                            erros++;
                            //tentativas--;
                            getchar();
                            continue;
                        }
                        if(acertouPalavra(palavraSorteada) == 1){
                            CLEAR_SCREEN;
                            imprimeForca(palavraSorteada);
                            letrasUsadas[0] = '\0';
                            qntLetrasUsadas = 0;
                            printf("\nParabens %s, voce acertou minha palavra em %i tentativas!\n\n", nome, qntPalp);

                            printf("       ___________      \n");
                            printf("      '._==_==_=_.'     \n");
                            printf("      .-\\:      /-.    \n");
                            printf("     | (|:.     |) |    \n");
                            printf("      '-|:.     |-'     \n");
                            printf("        \\::.    /      \n");
                            printf("         '::. .'        \n");
                            printf("           ) (          \n");
                            printf("         _.' '._        \n");
                            printf("        '-------'       \n\n");

                            printf("\nContinuar?[s/n]: ");
                            if(getchar() == 'n'){
                                op = 0;
                            }
                            setbuf(stdin, NULL);
                            CLEAR_SCREEN;
                            break;
                        }
                        //tentativas--;
                    } while(1);
                    //printf("%s - %s\n", sorteada->palavra, dica);

                }else{
                    printf("Nao tem palavra disponivel!\n\n");
                    break;
                }
                lstSecreta = retira(lstSecreta, sorteada->palavra);
            }while(op);
        }

        if(itemMenu == 0)
            break;
    }

    CLEAR_SCREEN;
    printf("Jogo encerrado!");

    return 0;
}

