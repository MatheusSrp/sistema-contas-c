# Sistema de Manutenção de Contas

Projeto desenvolvido para a disciplina de **PIF (Programação Imperativa e Funcional)** — CESAR School.

Sistema de gerenciamento de contas bancárias em linguagem C, utilizando arquivo binário com registros de tamanho fixo e acesso direto via `fseek()`.

---

## Funcionalidades

| Opção | Descrição |
|-------|-----------|
| 1 | Cadastrar novo cliente em uma posição específica |
| 2 | Consultar cliente pelo número da conta |
| 3 | Atualizar saldo de um cliente |
| 4 | Listar todos os clientes ativos |
| 5 | Encerrar conta (soft delete) |
| 6 | Rebobinar leitura do arquivo com `rewind()` e relistar |
| 7 | Encerrar o programa |

---

## Estrutura do Registro

Cada cliente é armazenado como um registro de tamanho fixo no arquivo binário:

```c
typedef struct {
    int   conta;       // número único da conta
    char  nome[100];   // nome do titular
    float saldo;       // saldo atual
    int   ativo;       // 1 = ativo, 0 = encerrado
} Cliente;
```

---

## Decisões Técnicas

### Arquivo binário com tamanho fixo
Todos os registros têm o mesmo tamanho (`sizeof(Cliente)`), o que permite calcular o offset de qualquer posição e acessá-la diretamente com `fseek()`, sem precisar percorrer o arquivo inteiro.

### Acesso direto com `fseek()`
Para cadastrar ou sobrescrever um registro em uma posição específica:
```c
fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);
```

### `ftell()` para gravar no lugar certo
Ao percorrer o arquivo em busca de um cliente (atualizar/encerrar), a posição é salva com `ftell()` **antes** do `fread()`. Após localizar o registro, o ponteiro volta para aquela posição com `fseek()` e o registro é sobrescrito com `fwrite()`.

### Soft delete com campo `ativo`
Encerrar uma conta não apaga o registro do arquivo — apenas define `ativo = 0`. Isso preserva o espaço no arquivo e permite que a posição seja reutilizada futuramente. Registros com `ativo = 0` são ignorados nas listagens e consultas.

### Abertura do arquivo
```c
FILE *arquivo = fopen("contas.bin", "r+b"); // abre se existir
if (arquivo == NULL) {
    arquivo = fopen("contas.bin", "w+b");   // cria se não existir
}
```
Essa estratégia evita apagar dados existentes ao reabrir o programa.

---

## Como Compilar e Executar

**Pré-requisito:** GCC instalado.

```bash
gcc main.c -o main
./main        # Linux/macOS
.\main        # Windows
```

---

## Arquivos do Repositório

```
.
├── main.c        # código-fonte principal
├── .gitignore    # ignora arquivos binários gerados
└── README.md     # este arquivo
```

> O arquivo `contas.bin` gerado em tempo de execução **não é versionado** (listado no `.gitignore`).