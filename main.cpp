#include <stdio.h>
#include <cstring>
#include <cctype>
/*
1 Pegar a quantidade de dinheiro
1.1 calcular o valor do dinheiro apos posiveis gastos
2 Listar a quantidade de pessoas que tem a posse do dinheiro
3 Listar os posiveis gastos
3 Dividir o dinheiro pelos gastos
4 Imprimir o resultado
5 Listar as tarefas
6 Imprimir as tarefas
7 Listar as tarefas por pessoa
8 Imprimir as tarefas por pessoa
9 Listar as tarefas por pessoa e o dinheiro gasto por cada pessoa
10 Imprimir as tarefas por pessoa e o dinheiro gasto por cada pessoa
11 salvar os dados em um arquivo
*/
struct dinheiro {
    float pessoal;
    float gastos;
    float total;
};

struct responsaveis {
   char nome[100];
   struct dinheiro dinheiro;
   char tarefas[100][200];
   bool cadastroCompleto;
   int totalTarefas;
   int id;
};

struct tarefas {
    char nome[100];
    char descricao[200];
    int idResponsavel;
    int idTarefa;
    char tipo;
    bool concluida;
};

struct responsaveis pessoas[100];
struct dinheiro dinheiro;
struct tarefas atividades[100];

int QtdPessoas;

void salvarDados() {
    FILE *arquivo = fopen("dados.txt", "w");

    if (arquivo == NULL) { // verificar se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < QtdPessoas; i++) {

        if (pessoas[i].cadastroCompleto) {

            fprintf(arquivo, "Nome: %s\n", pessoas[i].nome);
            fprintf(arquivo, "Dinheiro Pessoal: %.2f\n", pessoas[i].dinheiro.pessoal);
            fprintf(arquivo, "Gastos: %.2f\n", pessoas[i].dinheiro.gastos);
            fprintf(arquivo, "Total de dinheiro: %.2f\n", pessoas[i].dinheiro.total);
            fprintf(arquivo, "Total de tarefas: %d\n", pessoas[i].totalTarefas);
            for (int f = 0; f < pessoas[i].totalTarefas; f++) {
                fprintf(arquivo, "Tarefa %d: %s\n", f + 1, pessoas[i].tarefas[f]);
            }
            fprintf(arquivo, "-------------------------\n");
        }
    }

    fclose(arquivo);
}

void carregarDados() {
    FILE *arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) { //verificar se o arquivo existe
        printf("Nenhum arquivo de dados encontrado. Iniciando com dados vazios.\n");
        return;
    }

    char linha[256]; // buffer para ler as linhas do arquivo
    int pessoaIndex = -1;

    while (fgets(linha, sizeof(linha), arquivo)) { //ler o arquivo linha por linha
        if (strncmp(linha, "Nome: ", 6) == 0) { //verificar se a linha começa com "Nome: "
            pessoaIndex++;
            sscanf(linha, "Nome: %[^\n]", pessoas[pessoaIndex].nome); //extrair o nome da pessoa
            pessoas[pessoaIndex].cadastroCompleto = true;
        } else if (strncmp(linha, "Dinheiro Pessoal: ", 18) == 0) { //verificar se a linha começa com "Dinheiro Pessoal: "
            sscanf(linha, "Dinheiro Pessoal: %f", &pessoas[pessoaIndex].dinheiro.pessoal);
        } else if (strncmp(linha, "Gastos: ", 8) == 0) { //verificar se a linha começa com "Gastos: "
            sscanf(linha, "Gastos: %f", &pessoas[pessoaIndex].dinheiro.gastos);
        } else if (strncmp(linha, "Total de dinheiro: ", 19) == 0) { //verificar se a linha começa com "Total de dinheiro: "
            sscanf(linha, "Total de dinheiro: %f", &pessoas[pessoaIndex].dinheiro.total);
        } else if (strncmp(linha, "Total de tarefas: ", 18) == 0) { //verificar se a linha começa com "Total de tarefas: "
            sscanf(linha, "Total de tarefas: %d", &pessoas[pessoaIndex].totalTarefas);
        } else if (strncmp(linha, "Tarefa ", 7) == 0) { //verificar se a linha começa com "Tarefa "
            int tarefaIndex;
            sscanf(linha, "Tarefa %d: %[^\n]", &tarefaIndex, pessoas[pessoaIndex].tarefas[tarefaIndex - 1]); //extrair a descrição da tarefa
        }
    }

    QtdPessoas = pessoaIndex + 1;

    fclose(arquivo);
}

void cadastro() {

    if (QtdPessoas >= 100) {
        printf("Limite de pessoas atingido!\n");
        return;
    } else if (QtdPessoas == 0) {
        printf("Digite a quantidade de pessoas: ");
        scanf("%d", &QtdPessoas);
        getchar();

        for (int i = 0; i < QtdPessoas; i++) {
            printf("Digite o nome da pessoa: ");
            scanf("%s", pessoas[i].nome);
            getchar();
            printf("Digite a quantidade de dinheiro: ");
            scanf("%f", &pessoas[i].dinheiro.pessoal);
            getchar();
            dinheiro.total += pessoas[i].dinheiro.pessoal;
            pessoas[i].id = i;
            pessoas[i].cadastroCompleto = true;
        }
    } else  {
        int novaQtdPessoas;
        printf("Digite a quantidade de pessoas novas: ");
        scanf("%d", &novaQtdPessoas);

        for (int i = QtdPessoas; i < QtdPessoas + novaQtdPessoas; i++) {
            printf("Digite o nome da pessoa: ");
            scanf("%s", pessoas[i].nome);
            getchar();
            printf("Digite a quantidade de dinheiro: ");
            scanf("%f", &pessoas[i].dinheiro.pessoal);
            getchar();
            dinheiro.total += pessoas[i].dinheiro.pessoal;
            pessoas[i].id = i;
            pessoas[i].cadastroCompleto = true;
        }
        QtdPessoas += novaQtdPessoas;
        
    }
    
    salvarDados();
}

int buscarCadastro(){
    
    char nomeBusca[100];
    
    if (QtdPessoas == 0) {
        printf("Nenhuma pessoa cadstrada\n");
        return -1;
    } 
    else {
        printf("\n");
        printf("Digite o nome (ou parte dele) do contato: ");
        scanf("%49[^\n]", nomeBusca);
        getchar();

        printf("\n");
        printf("Buscando por %s ... \n", nomeBusca);

        for (int i=0; i < QtdPessoas; i++) {
            if (strstr(pessoas[i].nome, nomeBusca) != NULL){
                printf("Pessoa encontrada: %s\n", pessoas[i].nome);
                return i; 
            }
        }
    }
    return -1;  
    
}

void calcularGastos(){
    float gastoTotal;
    printf("Digite o valor total de gastos: ");
    scanf("%f", &gastoTotal);
    getchar();

    // Dividir o gasto total pelo número de pessoas para obter o valor que cada pessoa deve contribuir
    for (int i = 0; i < QtdPessoas; i++) {
        pessoas[i].dinheiro.gastos = (pessoas[i].dinheiro.pessoal / dinheiro.total) * gastoTotal;
        printf("%s deve contribuir com: %.2f\n", pessoas[i].nome, pessoas[i].dinheiro.gastos);
    }
}

void verificarSaldo(){
    int idPessoa = buscarCadastro();
    printf("Saldo pessoal de %s é de:\n", pessoas[idPessoa].nome);
    printf("Dinheiro pessoal: %.2f\n", pessoas[idPessoa].dinheiro.pessoal);
    printf("Gastos: %.2f\n", pessoas[idPessoa].dinheiro.gastos);
    printf("Saldo restante: %.2f\n", pessoas[idPessoa].dinheiro.pessoal - pessoas[idPessoa].dinheiro.gastos);
}

void financia() {
    int opcao;
    printf("\nDinheiro total: %.2f\n", dinheiro.total);

    do {
        printf("Deseja acessar qual funcionalidade? \n");
        printf("1. Calcular gastos\n");
        printf("2. Verificar saldo pessoal\n");
        printf("3. Sair\n");
        scanf(" %d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
            calcularGastos();
            break;
            case 2:
            verificarSaldo();
            break;
            case 3:
            printf("Saindo...\n");
            break;
            default:
            printf("Opção inválida!\n");
            break;
        }
        
    } while (opcao != 3);
    
}

void tarrefas() {
    char opcao;
    printf("Deseja (V)er, (A)dicionar, (M)udar tarefas ou (S)tatus: \n");
    scanf(" %c", &opcao);
    getchar();
    
    if(tolower(opcao) == 'v') {
        for (int i = 0; i < QtdPessoas; i++) {
            printf("Tarefas de %s:\n", pessoas[i].nome);
            for (int f = 0; f < pessoas[i].totalTarefas; f++) {
                printf("- %s\n", pessoas[i].tarefas[f]);   
            }
        }
    } else if (tolower(opcao) == 'a') {
        int idPessoa = buscarCadastro();

        if (idPessoa != -1) {
            int tarefas = pessoas[idPessoa].totalTarefas;
            if (tarefas <= 100) {
                printf("Digite a tarefa para %s: ", pessoas[idPessoa].nome);
                scanf(" %99[^\n]", pessoas[idPessoa].tarefas[tarefas]);
                getchar();
                atividades[tarefas].concluida = false;
                pessoas[idPessoa].totalTarefas++;
                printf("Tarefa adicionada com sucesso!\n");
            }
        }
    } else if (tolower(opcao) == 'm') {
        int idPessoa = buscarCadastro();

        if (idPessoa != -1) {
            int tarefas = pessoas[idPessoa].totalTarefas;
            if (tarefas > 0) {
                printf("Tarefas de %s:\n", pessoas[idPessoa].nome);
                for (int f = 0; f < tarefas; f++) {
                    printf("%d. %s\n", f + 1, pessoas[idPessoa].tarefas[f]);
                }
                int tarefaEscolhida;
                printf("Digite o número da tarefa que deseja modificar: ");
                scanf("%d", &tarefaEscolhida);
                getchar();

                if (tarefaEscolhida > 0 && tarefaEscolhida <= tarefas) {
                    printf("Digite a nova descrição para a tarefa: ");
                    scanf(" %99[^\n]", pessoas[idPessoa].tarefas[tarefaEscolhida - 1]);
                    getchar();
                    printf("Tarefa modificada com sucesso!\n");
                } else {
                    printf("Número de tarefa inválido!\n");
                }
            } else {
                printf("%s não tem tarefas cadastradas.\n", pessoas[idPessoa].nome);
            }
        }
    } else if (tolower(opcao) == 's') {
        int idPessoa = buscarCadastro();

        if (idPessoa != -1) {
            int tarefas = pessoas[idPessoa].totalTarefas;
            if (tarefas > 0) {
                printf("Tarefas de %s:\n", pessoas[idPessoa].nome);
                for (int f = 0; f < tarefas; f++) {
                    printf("%d. %s\n", f + 1, pessoas[idPessoa].tarefas[f]);
                }
                int tarefaEscolhida;
                printf("Digite o número da tarefa que deseja marcar como concluída: ");
                scanf("%d", &tarefaEscolhida);
                getchar();

                if (tarefaEscolhida > 0 && tarefaEscolhida <= tarefas) {
                    atividades[tarefaEscolhida - 1].concluida = true;
                    printf("Tarefa marcada como concluída!\n");
                } else {
                    printf("Número de tarefa inválido!\n");
                }
            } else {
                printf("%s não tem tarefas cadastradas.\n", pessoas[idPessoa].nome);
            }
        }
    } else {
        printf("Opção inválida!\n");
    }
    salvarDados();
}

void sair() {
    printf("Saindo...\n");
    salvarDados();
}

int main() {
    carregarDados();

    int opcao;
    do {
        printf("Bem-vindo ao sistema de gerenciamento financeiro e de tarefas!\n");
        printf("\n");
        printf("1. Cadastro de pessoas\n");
        printf("2. Gerenciamento financeiro\n");
        printf("3. Gerenciamento de tarefas\n");
        printf("4. Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastro();
            break;
        case 2:
            financia();
            break;
        case 3:
            tarrefas();
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 4);
    
}

