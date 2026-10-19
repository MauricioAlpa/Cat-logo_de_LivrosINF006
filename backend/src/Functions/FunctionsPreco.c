#include <backend/headers/FunctionsPreco.h>

void ordenaPrecoAscendente(livros lista[], int tamLista){
    
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

    void ordenaPrecoDecrescente(livros lista[], int tamLista){
    
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
