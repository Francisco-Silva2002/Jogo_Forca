#ifndef FORCA_H_INCLUDED
#define FORCA_H_INCLUDED

/* definição de uma Macro para limpeza do console */
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

struct noSecreto{
    int status;
    char palavra[31];
    char assunto[101];
    struct noSecreto * prox;
};

struct noSorteada{
    char letra;
    int descoberta;
    struct noSorteada * proximo;
};

typedef struct noSecreto NoSecreto;
typedef struct noSorteada NoSorteada;

int geraAleatorio(int maximo);
NoSecreto * inicializaListaSecreta();
NoSecreto * carregaListaArquivo(NoSecreto *l, char nomeArq[255]);
void imprimeListaSecreta(NoSecreto *l);
NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100]);
NoSecreto * sorteiaPalavra(NoSecreto *l);
int temPalavraNaoUsada(NoSecreto *l);

//retorna no tamanho da lista, para saber o intervalo de valores para gerar uma posicao
//aleatoria, para sortear uma palavra secreta
int tamanhoListaSecreta(NoSecreto *l);

//retorna a palavra que esteja em uma dada posição na lista de palavras secretas
NoSecreto * retornaPalavraPos(NoSecreto *l, int pos);
NoSecreto* retira (NoSecreto* l, char v[31]);

void libera (NoSorteada* l);
NoSorteada * inicializaPalavraSecreta();
NoSorteada* insereLetra(NoSorteada* l, char c);
NoSorteada* inverteP(NoSorteada* l);
NoSorteada* transformaPalavraEmLista(NoSorteada* l, char palavra[31]);
int verificarLetra(NoSorteada* l, char r);
int acertouPalavra(NoSorteada* l);
#endif // FORCA_H_INCLUDED
