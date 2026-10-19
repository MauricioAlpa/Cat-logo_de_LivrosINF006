// Servidor web do Catalogo de Livros.
// Nao ordena nada: recebe o pedido da pagina, chama o programa em C
// (catalogo) com execFile e devolve o resultado em JSON.
// Sem dependencias externas: usa apenas modulos nativos do Node.js.

const http = require("http");
const fs = require("fs");
const path = require("path");
const { execFile } = require("child_process");

const PORTA = process.env.PORT || 3000;
const RAIZ = path.join(__dirname, "..");
const PUBLIC = path.join(__dirname, "public");
const EXE = path.join(RAIZ, process.platform === "win32" ? "catalogo.exe" : "catalogo");
const FONTES = [
  path.join(RAIZ, "backend", "src", "main.c"),
  path.join(RAIZ, "backend", "src", "Functions", "FunctionsNome.c"),
  path.join(RAIZ, "backend", "src", "Functions", "FunctionsPreco.c"),
];

const CRITERIOS = ["nome", "preco"];
const ORDENS = ["asc", "desc"];

// Compila o backend em C se o executavel ainda nao existir.
function garantirExecutavel(callback) {
  if (fs.existsSync(EXE)) return callback(null);
  console.log("Executavel nao encontrado. Compilando o backend em C...");
  execFile("gcc", ["-I", RAIZ, ...FONTES, "-o", EXE], (erro, _out, stderr) => {
    if (erro) return callback(new Error("Falha ao compilar o C: " + (stderr || erro.message)));
    console.log("Compilado com sucesso.");
    callback(null);
  });
}

// Chama o programa em C e converte a saida "nome;preco" em objetos.
function ordenarComC(criterio, ordem, callback) {
  execFile(EXE, [criterio, ordem], (erro, stdout, stderr) => {
    if (erro) return callback(new Error(stderr.trim() || erro.message));
    const livros = stdout
      .split("\n")
      .filter((linha) => linha.includes(";"))
      .map((linha) => {
        const i = linha.lastIndexOf(";");
        return { nome: linha.slice(0, i), preco: parseFloat(linha.slice(i + 1)) };
      });
    callback(null, livros);
  });
}

function responderJSON(res, status, corpo) {
  res.writeHead(status, { "Content-Type": "application/json; charset=utf-8" });
  res.end(JSON.stringify(corpo));
}

const servidor = http.createServer((req, res) => {
  const url = new URL(req.url, "http://localhost");

  // API: GET /api/ordenar?criterio=nome|preco&ordem=asc|desc
  if (url.pathname === "/api/ordenar") {
    const criterio = url.searchParams.get("criterio");
    const ordem = url.searchParams.get("ordem");
    if (!CRITERIOS.includes(criterio) || !ORDENS.includes(ordem)) {
      return responderJSON(res, 400, { erro: "Parametros invalidos." });
    }
    return garantirExecutavel((erroCompilacao) => {
      if (erroCompilacao) return responderJSON(res, 500, { erro: erroCompilacao.message });
      ordenarComC(criterio, ordem, (erro, livros) => {
        if (erro) return responderJSON(res, 500, { erro: erro.message });
        responderJSON(res, 200, {
          comando: `catalogo ${criterio} ${ordem}`,
          livros,
        });
      });
    });
  }

  // Pagina: serve o index.html
  if (url.pathname === "/" || url.pathname === "/index.html") {
    return fs.readFile(path.join(PUBLIC, "index.html"), (erro, dados) => {
      if (erro) {
        res.writeHead(500);
        return res.end("Erro ao carregar a pagina.");
      }
      res.writeHead(200, { "Content-Type": "text/html; charset=utf-8" });
      res.end(dados);
    });
  }

  res.writeHead(404);
  res.end("Nao encontrado.");
});

servidor.listen(PORTA, () => {
  console.log(`Servidor rodando em http://localhost:${PORTA}`);
});
