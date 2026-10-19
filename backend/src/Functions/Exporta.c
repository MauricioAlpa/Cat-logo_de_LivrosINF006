#include <backend/headers/Exporta.h>
#include <backend/headers/FunctionsNome.h>
#include <backend/headers/FunctionsPreco.h>

void imprimeLivros(livros lista[], int qtd){
    for(int i = 0; i < qtd; i++){
        printf("\n========\n");
        printf("%s\n", lista[i].nome);
        printf("%.2f\n", lista[i].preco);
        printf("========\n");
    }
}

/* Escreve o texto entre aspas, protegendo " e \ para nao quebrar o JS. */
static void escreveTexto(FILE *f, const char *s){
    fputc('"', f);
    for(; *s; s++){
        if(*s == '"' || *s == '\\') fputc('\\', f);
        fputc(*s, f);
    }
    fputc('"', f);
}

static void escreveLista(FILE *f, const char *chave, livros lista[], int qtd, int ultimo){
    fprintf(f, "  %s: [\n", chave);
    for(int i = 0; i < qtd; i++){
        fprintf(f, "    { nome: ");
        escreveTexto(f, lista[i].nome);
        fprintf(f, ", preco: %.2f }%s\n", lista[i].preco, i < qtd - 1 ? "," : "");
    }
    fprintf(f, "  ]%s\n", ultimo ? "" : ",");
}

int exportaWeb(livros lista[], int qtd, const char *caminho){
    FILE *f = fopen(caminho, "w");
    if(f == NULL) return 1;

    /* Cada ordenacao trabalha numa copia, para uma nao atrapalhar a outra. */
    livros copia[MAX_livros];

    fprintf(f, "// Arquivo gerado pelo programa em C (main.c --web). Nao edite na mao.\n");
    fprintf(f, "const CATALOGO = {\n");

    memcpy(copia, lista, qtd * sizeof(livros));
    ordenaPrecoAscendente(copia, qtd);
    escreveLista(f, "precoCrescente", copia, qtd, 0);

    memcpy(copia, lista, qtd * sizeof(livros));
    ordenaPrecoDecrescente(copia, qtd);
    escreveLista(f, "precoDecrescente", copia, qtd, 0);

    memcpy(copia, lista, qtd * sizeof(livros));
    ordenaNomeCrescente(copia, qtd);
    escreveLista(f, "nomeCrescente", copia, qtd, 0);

    memcpy(copia, lista, qtd * sizeof(livros));
    ordenaNomeDecrescente(copia, qtd);
    escreveLista(f, "nomeDecrescente", copia, qtd, 1);

    fprintf(f, "};\n");
    fclose(f);
    return 0;
}
