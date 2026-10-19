"""Interface grafica (Tkinter) do Catalogo de Livros.

A interface NAO ordena nada: ela chama o programa em C (catalogo) passando
o criterio e a ordem, le a saida (nome;preco por linha) e mostra na tabela.
"""
import os
import shutil
import subprocess
import sys
import tkinter as tk
from tkinter import ttk, messagebox

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
EXE = os.path.join(RAIZ, "catalogo.exe" if os.name == "nt" else "catalogo")
FONTES = [
    os.path.join(RAIZ, "backend", "src", "main.c"),
    os.path.join(RAIZ, "backend", "src", "Functions", "FunctionsNome.c"),
    os.path.join(RAIZ, "backend", "src", "Functions", "FunctionsPreco.c"),
]


def compilar():
    """Compila o backend em C com gcc. Retorna (ok, mensagem)."""
    if shutil.which("gcc") is None:
        return False, "gcc nao encontrado. Instale o GCC (ou MinGW no Windows)."
    cmd = ["gcc", "-I", RAIZ, *FONTES, "-o", EXE]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        return False, r.stderr
    return True, ""


def executar_c(criterio, ordem):
    """Chama o executavel em C e devolve a lista [(nome, preco), ...]."""
    r = subprocess.run([EXE, criterio, ordem], capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(r.stderr.strip() or "Erro ao executar o programa em C.")
    livros = []
    for linha in r.stdout.splitlines():
        if ";" in linha:
            nome, preco = linha.rsplit(";", 1)
            livros.append((nome, float(preco)))
    return livros


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Catalogo de Livros - Ordenacao em C")
        self.geometry("620x560")
        self.minsize(520, 420)

        self.criterio = tk.StringVar(value="nome")
        self.ordem = tk.StringVar(value="asc")

        opcoes = ttk.Frame(self, padding=10)
        opcoes.pack(fill="x")

        f1 = ttk.LabelFrame(opcoes, text="Ordenar por", padding=8)
        f1.pack(side="left", padx=(0, 10))
        ttk.Radiobutton(f1, text="Nome", variable=self.criterio, value="nome").pack(anchor="w")
        ttk.Radiobutton(f1, text="Preco", variable=self.criterio, value="preco").pack(anchor="w")

        f2 = ttk.LabelFrame(opcoes, text="Ordem", padding=8)
        f2.pack(side="left", padx=(0, 10))
        ttk.Radiobutton(f2, text="Crescente", variable=self.ordem, value="asc").pack(anchor="w")
        ttk.Radiobutton(f2, text="Decrescente", variable=self.ordem, value="desc").pack(anchor="w")

        ttk.Button(opcoes, text="Ordenar", command=self.ordenar).pack(side="left", ipadx=12, ipady=6)

        cols = ("pos", "nome", "preco")
        self.tabela = ttk.Treeview(self, columns=cols, show="headings")
        self.tabela.heading("pos", text="#")
        self.tabela.heading("nome", text="Livro")
        self.tabela.heading("preco", text="Preco (R$)")
        self.tabela.column("pos", width=40, anchor="center", stretch=False)
        self.tabela.column("nome", width=380)
        self.tabela.column("preco", width=100, anchor="e", stretch=False)
        sb = ttk.Scrollbar(self, orient="vertical", command=self.tabela.yview)
        self.tabela.configure(yscrollcommand=sb.set)
        sb.pack(side="right", fill="y", padx=(0, 6), pady=(0, 6))
        self.tabela.pack(fill="both", expand=True, padx=(10, 0), pady=(0, 6))

        self.status = tk.StringVar(value="Escolha o criterio e a ordem e clique em Ordenar.")
        ttk.Label(self, textvariable=self.status, padding=(10, 0, 10, 8)).pack(fill="x", side="bottom")

        if not os.path.exists(EXE):
            self.garantir_executavel()
        else:
            self.ordenar()

    def garantir_executavel(self):
        ok, msg = compilar()
        if not ok:
            messagebox.showerror("Backend em C", f"Nao foi possivel compilar:\n\n{msg}")
            self.status.set("Backend nao compilado.")
        else:
            self.ordenar()

    def ordenar(self):
        if not os.path.exists(EXE):
            self.garantir_executavel()
            return
        try:
            livros = executar_c(self.criterio.get(), self.ordem.get())
        except Exception as e:
            messagebox.showerror("Erro", str(e))
            return
        self.tabela.delete(*self.tabela.get_children())
        for i, (nome, preco) in enumerate(livros, 1):
            self.tabela.insert("", "end", values=(i, nome, f"{preco:.2f}"))
        self.status.set(f"Comando: catalogo {self.criterio.get()} {self.ordem.get()}  ({len(livros)} livros)")


if __name__ == "__main__":
    App().mainloop()
