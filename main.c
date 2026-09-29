#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <string.h>
#define TAMLISTA 20
#define MAX_livros 20

int main()
{
    livros lista[TAMLISTA] = {
        {39.90, "Dom Casmurro"},
        {45.50, "O Cortico"},
        {32.90, "Memorias Postumas de Bras Cubas"},
        {49.90, "Grande Sertao: Veredas"},
        {29.90, "Capitaes da Areia"},
        {35.90, "Vidas Secas"},
        {42.90, "A Hora da Estrela"},
        {54.90, "O Senhor dos Aneis"},
        {59.90, "Harry Potter e a Pedra Filosofal"},
        {44.90, "O Hobbit"},
        {38.90, "1984"},
        {41.90, "A Revolucao dos Bichos"},
        {36.90, "O Pequeno Principe"},
        {47.90, "Orgulho e Preconceito"},
        {52.90, "Crime e Castigo"},
        {39.90, "O Diario de Anne Frank"},
        {43.90, "It: A Coisa"},
        {34.90, "Coraline"},
        {48.90, "O Codigo Da Vinci"},
        {37.90, "Percy Jackson e o Ladrao de Raios"}
    };

    void ordenaPrecoMenor(livros lista[], int tamLista){
    
    for(int i = 0; i < tamLista; i++){
        for(int j = 0; j < tamLista - i - 1; j++){
            livros aux;
            if(lista[j].preco > lista[j + 1].preco){
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }

        for(int i = 0; i < tamLista; i++){
            printf("\n========\n");
            printf("\n%s\n", lista[i].nome);
            printf("\n%.2f\n", lista[i].preco);
            printf("\n========\n");
        }
    }

    void ordenaPrecoMaior(livros lista[], int tamLista){
    
        for(int i = 0; i < tamLista; i++){
            for(int j = 0; j < tamLista - i - 1; j++){
                livros aux;
                if(lista[j].preco < lista[j + 1].preco){
                    aux = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = aux;
                }
            }
        }

        for(int i = 0; i < tamLista; i++){
            printf("\n========\n");
            printf("\n%s\n", lista[i].nome);
            printf("\n%.2f\n", lista[i].preco);
            printf("\n========\n");
            }
    }

    void ordenaNomeCrescente(livros lista[], int qtdLivros){

    
    livros temp[50];

    for(int i = 0; i < MAX_livros - 1; i++){

        for(int j=i+1; j < MAX_livros - i ; j++){
    
            if(strcmp(lista[i].nome, lista[j].nome) > 0)
            {
                temp[i] = lista[j];
                lista[j] = lista[i];
                lista[i] = temp[i];
            }
    
            
        }

    }

    for(int i = 0; i < MAX_livros; i++){
        printf("\n========\n");
        printf("\n%s\n", lista[i].nome);
        printf("\n%.2f\n", lista[i].preco);
        printf("\n========\n");
    }

}

void ordenaNomeDecrescente(livros lista[], int qtdLivros){

    
    livros temp[50];

    for(int i = 0; i < MAX_livros - 1; i++){

        for(int j=i+1; j < MAX_livros - i ; j++){
    
            if(strcmp(lista[i].nome, lista[j].nome) < 0)
            {
                temp[i] = lista[j];
                lista[j] = lista[i];
                lista[i] = temp[i];
            }
    
            
        }

    }

    for(int i = 0; i < MAX_livros; i++){
        printf("\n========\n");
        printf("\n%s\n", lista[i].nome);
        printf("\n%.2f\n", lista[i].preco);
        printf("\n========\n");
    }

}

    printf("\nORDENA DECRESCENTE\n");
    ordenaPrecoMenor(lista, TAMLISTA);
    printf("\nORDENA CRESCENTE\n");
    ordenaPrecoMaior(lista, TAMLISTA);
    printf("Ordena nome crescente: ");
    ordenaNomeCrescente(lista, MAX_livros);
    printf("Ordena nome decrescente: ");
    ordenaNomeDecrescente(lista, MAX_livros);

}
