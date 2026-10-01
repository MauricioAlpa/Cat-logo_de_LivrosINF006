#include <backend/headers/FunctionsNome.h>

void ordenaNomeCrescente(livros lista[], int qtdLivros){
    for(int i = 0; i < qtdLivros - 1; i++){
        for(int j = i + 1; j < qtdLivros; j++){
            if(strcmp(lista[i].nome, lista[j].nome) > 0){
                livros temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    for(int i = 0; i < qtdLivros; i++){
        printf("\n========\n");
        printf("%s\n", lista[i].nome);
        printf("%.2f\n", lista[i].preco);
        printf("========\n");
    }
}

void ordenaNomeDecrescente(livros lista[], int qtdLivros){
    for(int i = 0; i < qtdLivros - 1; i++){
        for(int j = i + 1; j < qtdLivros; j++){
            if(strcmp(lista[i].nome, lista[j].nome) < 0){
                livros temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    for(int i = 0; i < qtdLivros; i++){
        printf("\n========\n");
        printf("%s\n", lista[i].nome);
        printf("%.2f\n", lista[i].preco);
        printf("========\n");
    }
}