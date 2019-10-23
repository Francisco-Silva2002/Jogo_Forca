#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include "forca.c"
#include "forca.h"

void copyright(){
    system("cls");
    printf("=============================================================\n\n");
    printf("JOGO DA FORCA\n");
    printf("Desenvolvido por: \n\t18464 - Francisco Eduardo Pereira Sousa Silva\n");
    printf("\t18457 - Clayton Gabriel Lorizolla\n");
    printf("\t18465 - Gabriel Issac da Silva\n");
    printf("=============================================================\n\n");
}

int limpaTela()
{
puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
return 0;
}

int main(int argc, char *argv[])
{
    /* INÍCIO VARIÁVEIS DE JOGO */
    char dica[101];
    char palpite;
    int op = 1;
    int tentativas = 10;
    NoSorteada * palavraSorteada;
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
    Sleep(3000);
    printf("Voce tem 10 tentativas para acertar a palavra!");

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
            do{
                CLEAR_SCREEN;
                imprimeForca(palavraSorteada);
                printf("\nDICA: %s", dica);
                printf("\nDigite o seu palpite: ");
                scanf("%c", &palpite);
                setbuf(stdin, NULL);
                if(verificarLetra(palavraSorteada, palpite) == 0){
                    printf("\nNao ha essa letra");
                    Sleep(500);
                    continue;
                }
                if(acertouPalavra(palavraSorteada) == 1){
                    CLEAR_SCREEN;
                    imprimeForca(palavraSorteada);

                    printf("\nParabens, voce ganhou!\n\n");

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

                    Sleep(500);
                    printf("\nContinuar?[s/n]: ");
                    if(getchar() == 'n'){
                        op = 0;
                    }
                    setbuf(stdin, NULL);
                    CLEAR_SCREEN;
                    break;
                }
            } while(1);
            //printf("%s - %s\n", sorteada->palavra, dica);

        }else{
            printf("Nao tem palavra disponivel!\n\n");
            break;
        }
        lstSecreta = retira(lstSecreta, sorteada->palavra);
    }while(op);

    printf("Jogo encerrado!");

    return 0;
}

