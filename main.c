#include <stdio.h>

typedef struct {
    int conta;
    char nome[100];
    float saldo;
    int ativo;
} Cliente;

void cadastrar(FILE *arquivo) {
    int posicao;
    Cliente novo, temp;

    printf("Em qual posicao deseja cadastrar? ");
    scanf("%d", &posicao);


    fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);
    fread(&temp, sizeof(Cliente), 1, arquivo);

    if (temp.ativo == 1) {
        printf("Posicao ocupada!\n");
    } else {
        printf("Nome: ");
        scanf("%s", novo.nome);

        printf("Numero da conta: ");
        scanf("%d", &novo.conta);

        printf("Saldo inicial: ");
        scanf("%f", &novo.saldo);

        novo.ativo = 1;

        fseek(arquivo, posicao * sizeof(Cliente), SEEK_SET);
        fwrite(&novo, sizeof(Cliente), 1, arquivo);
    }
}

void consultar(FILE *arquivo) {
    int conta;
    int achou = 0;
    Cliente temp;

    printf("Numero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);

    while (fread(&temp, sizeof(Cliente), 1, arquivo) == 1) {
        if (conta == temp.conta && temp.ativo == 1) {
            printf("Nome: %s\n", temp.nome);
            printf("Conta: %d\n", temp.conta);
            printf("Saldo: %.2f\n", temp.saldo);
            achou = 1;
            break;
        }
    }
    if (achou == 0){
            printf("Cliente nao encontrado!\n");
        }
}

void atualizar(FILE *arquivo) {
    int conta;
    float saldoNovo;
    int achou = 0;
    Cliente temp;
    
    printf("Numero da conta: ");
    scanf("%d", &conta);

    rewind(arquivo);
    
    while (1) {
        long posicao = ftell(arquivo);
        if (fread(&temp, sizeof(Cliente), 1, arquivo) != 1) {
            break;
        }

        if (conta == temp.conta && temp.ativo == 1) {
            fseek(arquivo, posicao, SEEK_SET);
            printf("Adicione o novo saldo: ");
            scanf("%f", &saldoNovo);
            temp.saldo = saldoNovo;
            fwrite(&temp, sizeof(Cliente), 1, arquivo);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Cliente nao encontrado\n");
    }
}

void exibir(FILE *arquivo) {
    Cliente temp;

    rewind(arquivo);

    printf("Lista dos Clientes:\n");

    while (fread(&temp, sizeof(Cliente), 1, arquivo) == 1) {
        if (temp.ativo == 1) {

            printf("Conta: %d\n", temp.conta);
            printf("Nome: %s\n", temp.nome);
            printf("Saldo: %.2f\n", temp.saldo);
            printf("-------------------------\n");
        }
    }
}

void encerrar(FILE *arquivo) {
    int conta;
    int achou = 0;
    Cliente temp;

    printf("Numero da conta: ");
    scanf("%d", &conta);
    rewind(arquivo);

    while(1) {
        long posicao = ftell(arquivo);
        if (fread(&temp, sizeof(Cliente), 1, arquivo) != 1) {
            break;
        }

        if (conta == temp.conta && temp.ativo == 1) {
            fseek(arquivo, posicao, SEEK_SET);
            temp.ativo = 0;
            fwrite(&temp, sizeof(Cliente), 1, arquivo);
            achou = 1;
            break;
        }

    }
    if (achou == 0) {
        printf("Cliente nao encontrado");
    }
}

int main() {
    int opcao;
    
    FILE *arquivo = fopen("contas.bin", "r+b");
    if (arquivo == NULL) {
        arquivo = fopen("contas.bin", "w+b");
    }
    do
    {
        printf("\n===================================================\n");
        printf("\nBem Vindo!");
        printf("\n1 - Cadastrar\n2 - Consultar Cliente\n3 - Atualizar Saldo\n4 - Exibir Lista\n5 - Cancelar Conta\n6 - Reiniciar leitura(Rewind) e listar \n7 - Encerrar Programa\nSelecione uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
            case 1:
            cadastrar(arquivo);
            break;
    
            case 2:
            consultar(arquivo);
            break;
            
            case 3:
            atualizar(arquivo);
            break;
    
            case 4:
            exibir(arquivo);
            break;
    
            case 5:
            encerrar(arquivo);
            break;
    
            case 6:
            rewind(arquivo);
            exibir(arquivo);
            break;

            case 7:
            printf("Encerrando o sistema. Ate logo!\n");
            break;

            default:
            printf("Opcao invalida. Tente novamente");
            break;
        }
    } while (opcao != 7);

    fclose(arquivo);
    printf("===================================================\n");
    return 0;
}