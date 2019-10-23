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
    char* letrasUsadas = (char*) malloc(255*sizeof(char));
    int qntLetrasUsadas = 0;
    int erros;
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
    printf("Voce tem 10 tentativas para acertar a palavra!");
    Sleep(3000);

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

				if(tentativas == 0){
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
					op = 0;
					break;
                }

                printf("DICA: %s\n\n", dica);
                imprimeForca(palavraSorteada);
                printf("\n\nTentativas Restantes: %i", tentativas);
                printf("\nDigite o seu palpite: ");
                scanf("%c", &palpite);
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
                        printf("Essa letra ja foi usada!");
                        setbuf(stdin, NULL);
                        Sleep(1000);
                        continue;
                    }
				}

                setbuf(stdin, NULL);
                if(verificarLetra(palavraSorteada, palpite) == 0){
                    printf("\nNao ha essa letra");
                    tentativas--;
                    Sleep(1000);
                    continue;
                }
                if(acertouPalavra(palavraSorteada) == 1){
                    CLEAR_SCREEN;
                    imprimeForca(palavraSorteada);
                    letrasUsadas[0] = '\0';
                    qntLetrasUsadas = 0;
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

