# Catalogo de Livros - Ordenacao em C

Ordena um catalogo de livros por **nome** ou **preco**, em ordem **crescente** ou **decrescente**.

- **Backend (C):** `backend/` - algoritmos de ordenacao
- **Frontend (Python/Tkinter):** `frontend/app.py` - chama o programa em C e exibe o resultado

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

## Rodar a interface

Requer Python 3 (Tkinter ja vem junto no Windows/macOS; no Linux: `sudo apt install python3-tk`).

```bash
python frontend/app.py
```

Se o executavel `catalogo` ainda nao existir, a interface tenta compilar sozinha (precisa do `gcc`).

## Algoritmos

- Preco: Bubble Sort (`FunctionsPreco.c`)
- Nome: troca por comparacao com `strcmp` (`FunctionsNome.c`)
