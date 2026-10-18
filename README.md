# Catalogo de Livros - Ordenacao em C

Ordena um catalogo de livros por **nome** ou **preco**, em ordem **crescente** ou **decrescente**.

- **Backend (C):** `backend/` - algoritmos de ordenacao
- **Frontend (Web):** `frontend/` - servidor Node.js + pagina HTML que chamam o programa em C

## Como compilar o backend (a partir da raiz do projeto)

```bash
gcc -I. backend/src/main.c backend/src/Functions/*.c -o catalogo
```

## Testar so o C no terminal

```bash
./catalogo nome asc      # nome crescente
./catalogo nome desc     # nome decrescente
./catalogo preco asc     # preco crescente
./catalogo preco desc    # preco decrescente
```

## Rodar a interface web

Requer Node.js (nao precisa de `npm install`).

```bash
node frontend/server.js
```

Abra `http://localhost:3000` no navegador. No GitHub Codespaces, clique em
**Open in Browser** na notificacao da porta 3000 (ou na aba **Ports**).

Se o executavel `catalogo` ainda nao existir, o servidor tenta compilar sozinho (precisa do `gcc`).

## Como funciona

```
Navegador (index.html) -> servidor Node (server.js) -> ./catalogo <criterio> <ordem> -> JSON -> tabela
```

## Algoritmos

- Preco: Bubble Sort (`FunctionsPreco.c`)
- Nome: troca por comparacao com `strcmp` (`FunctionsNome.c`)

## Equipe

- (preencher com os nomes)
