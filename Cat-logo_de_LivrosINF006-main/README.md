# Catálogo de Livros (C + front end)

O programa em C guarda os livros e faz as 4 ordenações (preço e nome, crescente e decrescente).
O front end é uma página HTML que só mostra o resultado.

## Ver a página (sem instalar nada)
Dê dois cliques em `frontend/index.html`. O `dados.js` já vem gerado.

## Rodar no terminal (como antes)
```
gcc -I. backend/src/main.c backend/src/Functions/*.c -o main
./main
```

## Atualizar a página depois de mudar o C
```
./main --web
```
Isso recria `frontend/dados.js` com as listas ordenadas pelas funções em C.
(No Windows: `main.exe --web`.)
