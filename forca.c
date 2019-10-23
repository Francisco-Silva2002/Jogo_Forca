#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"

//gera um numero aleatorio entre 1 e 'maximo'
int geraAleatorio(int maximo)
{
    time_t t;
    int n=0;
    srand((unsigned) time(&t));
    n = (rand() % maximo)+1;
    return n;
}

/* função retira: retira elemento da lista */
NoSecreto* retira (NoSecreto* l, char v[31]) {
    NoSecreto* ant = NULL; /* ponteiro para elemento anterior */
    NoSecreto* p = l; /* ponteiro para percorrer a lista*/
    /* procura elemento na lista, guardando anterior */
    while (p != NULL && strcmp(v, p->palavra) != 0) {
        ant = p;
        p = p->prox;
    }
    /* verifica se achou elemento */
    if (p == NULL)
        return l; /* não achou: retorna lista original */
    /* retira elemento */
    if (ant == NULL) {
    /* retira elemento do inicio */
        l = p->prox;
    }
    else {
    /* retira elemento do meio da lista */
        ant->prox = p->prox;
    }
    free(p);
    return l;
}

NoSecreto * inicializaListaSecreta()
{
    return NULL;
}

NoSecreto * inserePalavraSecreta(NoSecreto *l,char word[31],char subject[100])
{
    NoSecreto * novo;
    novo = (NoSecreto *) malloc(sizeof(NoSecreto));
    novo->status=0;
    strcpy(novo->assunto,subject);
    strcpy(novo->palavra,word);
    novo->prox = l;
    l=novo;
    return l;
}

void imprimeListaSecreta(NoSecreto *l)
{
    for(NoSecreto *p=l; p!=NULL; p=p->prox)
    {
        printf("%d) %-30s\t%s\n", p->status,p->palavra,p->assunto);
    }
}

NoSecreto * carregaListaArquivo(NoSecreto * l, char nomeArq[255])
{
    const char ch[2]=";";
    char * token;
    int status;
    char palavra[31];
    char assunto[101];
    char * linha[1024];
    FILE * fWords;

    fWords = fopen(nomeArq,"r");
    if(fWords==NULL){
        printf("Falha ao acessar base de dados!!!\n\n");
        exit(0);
    }
    while(fgets(linha,1024,fWords))
    {
        token = strtok(linha,ch);
        if(token!=NULL)
        {
             strcpy(palavra,token);
        }
        token=strtok(NULL,ch);
        if(token!=NULL)
        {
            strcpy(assunto,token);
        }
        l = inserePalavraSecreta(l,palavra, assunto);
    }

    fclose(fWords);
    return l;
}

//
int tamanhoListaSecreta(NoSecreto *l)
{
    int n=0;
    for(NoSecreto *p=l;p!=NULL;p=p->prox,n++);
    return n;
}

int temPalavraNaoUsada(NoSecreto *l)
{
    NoSecreto *p;
    for(p=l;p!=NULL;p=p->prox){
        if(p->status==0) return 1;
    }
    return 0;
}

NoSecreto * sorteiaPalavra(NoSecreto *l)
{
    int tam = tamanhoListaSecreta(l);
    int aleatorio=0;
    int tentativas = 0;
    NoSecreto * p;

    while(temPalavraNaoUsada(l)){
        aleatorio = geraAleatorio(tam);
        p = retornaPalavraPos(l,aleatorio);
        if(p->status==0){
            p->status = 1;
            return p;
        }
    }
    return NULL;
}

//retorna a palavra que está na posicao 'pos' da lisata secreta
NoSecreto * retornaPalavraPos(NoSecreto *l, int pos)
{
    int n=1;
    NoSecreto *p;
    for(p=l; p!=NULL; p=p->prox)
    {
        if(n==pos) break;
        n++;
    }
    return p;
}

void libera (NoSorteada* l)
{
    NoSorteada* p = l;
    while (p != NULL) {
        NoSorteada* t = p->proximo;
        free(p);
        p = t;
    }
}

NoSorteada * inicializaPalavraSecreta(){
    return NULL;
}

NoSorteada* insereLetra(NoSorteada* l, char c){
    NoSorteada* novo;
    novo = (NoSorteada*) malloc(sizeof(NoSorteada));
    novo->letra = c;
    novo->descoberta = 0;
    novo->proximo = l;
    l = novo;
    return l;
}

NoSorteada* inverteP(NoSorteada* l){
    NoSorteada* temp = inicializaPalavraSecreta();
    for(NoSorteada* p=l;p!=NULL;p=p->proximo){
        NoSorteada* novo;
        novo = (NoSorteada*) malloc(sizeof(NoSorteada));
        novo->letra = p->letra;
        novo->proximo = temp;
        novo->descoberta = 0;
        temp = novo;
    }

    return temp;
}

NoSorteada* transformaPalavraEmLista(NoSorteada* l, char palavra[31]){
    l = inicializaPalavraSecreta();
    for(int a=0;a<strlen(palavra); a++){
        l = insereLetra(l, palavra[a]);
    }

    l = inverteP(l);
    return l;
}

void imprimeForca(NoSorteada* l){
    for(NoSorteada* p=l;p!=NULL;p=p->proximo){
        if(p->descoberta == 0){
            printf("_ ");
        } else{
            printf("%c ", p->letra);
        }
    }
}

void imprimePalavraSorteada(NoSorteada* l){
    for(NoSorteada* p=l;p!=NULL;p=p->proximo){
		printf("%c ", p->letra);
    }
}

int verificarLetra(NoSorteada* l, char r){
    int acertou = 0; // 0 se nao tiver a letra
    for(NoSorteada* p=l;p!=NULL;p=p->proximo){
        if(p->letra == r){
            p->descoberta = 1;
            acertou = 1; // 1 se tiver a letra
        }
    }
    return acertou;
}

int acertouPalavra(NoSorteada* l){
    int qnt = 0, desc = 0;
    for(NoSorteada* p =l; p!=NULL;p=p->proximo){
        qnt++;
        if(p->descoberta == 1)
            desc++;
    }

    if(qnt == desc)
        return 1;
    return 0;
}

void adicionaLetra(char* lista, char letra, int tam){
    if(tam == 1)
		lista[0] = letra;
    else
		lista[tam] = letra;
}

int buscaLetra(char* lista, char letra, int tam){

    for(int i=0;i<tam;i++){
		if(lista[i] == letra){
			return 1;
		}
    }
    return 0;
}
