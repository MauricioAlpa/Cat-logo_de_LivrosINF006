#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <backend/headers/structs.h>
#include <backend/headers/FunctionsNome.h>
#include <backend/headers/FunctionsPreco.h>

/* Uso: catalogo <nome|preco> <asc|desc>
 * Saida: uma linha por livro, no formato  nome;preco
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <nome|preco> <asc|desc>\n", argv[0]);
        return 1;
    }

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

    const char *criterio = argv[1];
    const char *ordem    = argv[2];

    if (strcmp(criterio, "nome") == 0 && strcmp(ordem, "asc") == 0) {
        ordenaNomeCrescente(lista, MAX_livros);
    } else if (strcmp(criterio, "nome") == 0 && strcmp(ordem, "desc") == 0) {
        ordenaNomeDecrescente(lista, MAX_livros);
    } else if (strcmp(criterio, "preco") == 0 && strcmp(ordem, "asc") == 0) {
        ordenaPrecoAscendente(lista, TAMLISTA);
    } else if (strcmp(criterio, "preco") == 0 && strcmp(ordem, "desc") == 0) {
        ordenaPrecoDecrescente(lista, TAMLISTA);
    } else {
        fprintf(stderr, "Argumentos invalidos. Use: nome|preco  asc|desc\n");
        return 1;
    }

    for (int i = 0; i < TAMLISTA; i++) {
        printf("%s;%.2f\n", lista[i].nome, lista[i].preco);
    }
    return 0;
}
