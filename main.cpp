#include <stdio.h>
#include <cstring>
#include <cctype>
#include <ctype.h>

struct dinheiro {
    float pessoal;
    float gastos;
    float total;
    float gastoTotal;
};

struct atividades {
    char nome[100];
    char descricao[200];
    char tipo;
    bool concluida;
    bool monetaria;
    float valor;
};

struct responsaveis {
   char nome[200];
   struct dinheiro dinheiro;
   struct atividades tarefas[100];
   bool cadastroCompleto;
   int totalTarefas;
   int id;
   
};

struct responsaveis pessoas[100];
struct dinheiro dinheiro;

int QtdPessoas;
// salvar dados no arquivo

void salvarDados() {
    FILE *arquivo = fopen("dados.txt", "w");

    if (arquivo == NULL) { // verificar se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < QtdPessoas; i++) {

        if (pessoas[i].cadastroCompleto) {

            fprintf(arquivo, "Nome: %s\n", pessoas[i].nome); // salvar o nome da pessoa
            fprintf(arquivo, "Dinheiro Pessoal: %.2f\n", pessoas[i].dinheiro.pessoal); // salvar o dinheiro pessoal da pessoa
            fprintf(arquivo, "Gastos: %.2f\n", pessoas[i].dinheiro.gastos); // salvar os gastos da pessoa
            fprintf(arquivo, "Total de tarefas: %d\n", pessoas[i].totalTarefas); // salvar o total de tarefas da pessoa
            for (int f = 0; f < pessoas[i].totalTarefas; f++) { // salvar as tarefas da pessoa
                fprintf(arquivo, "Tarefa %d: %s\n", f + 1, pessoas[i].tarefas[f].nome); // salvar o nome da tarefa
                fprintf(arquivo, "Descrição: %s\n", pessoas[i].tarefas[f].descricao); // salvar a descrição da tarefa
                fprintf(arquivo, "Tipo: %s\n", pessoas[i].tarefas[f].monetaria ? "Monetária" : "Não monetária"); // salvar o tipo da tarefa
                fprintf(arquivo, "Status: %d\n", pessoas[i].tarefas[f].concluida); // salvar o status da tarefa (1 para concluída, 0 para pendente)
            }
            fprintf(arquivo, "-------------------------\n");
        }
    }
    
    fprintf(arquivo, "Total de dinheiro: %.2f\n", dinheiro.total);
    fprintf(arquivo,"Total de gastos: %.2f\n", dinheiro.gastoTotal);
    fprintf(arquivo, "-------------------------\n");
    
    fclose(arquivo);
}

// atualizar o valor total do dinheiro com base no dinheiro pessoal de cada pessoa

void atualizarValorTotal(){

    dinheiro.total = 0;
    for (int i = 0; i < QtdPessoas; i++) {
        dinheiro.total += pessoas[i].dinheiro.pessoal;
    }
}

// Cadastro

bool contemTexto(const char *str, const char *sub) {
    if (!str || !sub) {
        return false;
    }

    int lenStr = strlen(str);
    int lenSub = strlen(sub);

    if (lenSub > lenStr) {
        return false;
    }
    
    for (int i = 0; i <= lenStr - lenSub; i++) {
        for (int j = 0; j < lenSub; j++) {
            if (tolower((unsigned char)str[i + j]) != tolower((unsigned char)sub[j])) {
                break;
            }
            if (j == lenSub - 1) {
                return true;
            }
        }
        return false;
        
    }

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
            scanf(" %199[^\n]", pessoas[i].nome);
            getchar();
            printf("Digite a quantidade de dinheiro: ");
            scanf("%f", &pessoas[i].dinheiro.pessoal);
            getchar();
            pessoas[i].id = i;
            pessoas[i].cadastroCompleto = true;
        }
    } else  {
        int novaQtdPessoas;
        printf("Digite a quantidade de pessoas novas: ");
        scanf("%d", &novaQtdPessoas);

        for (int i = QtdPessoas; i < QtdPessoas + novaQtdPessoas; i++) {
            printf("Digite o nome da pessoa: ");
            scanf(" %199[^\n]", pessoas[i].nome);
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
    
    atualizarValorTotal();
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
        scanf(" %99[^\n]", nomeBusca);
        getchar();

        printf("\n");
        printf("Buscando por %s ... \n", nomeBusca);

        for (int i=0; i < QtdPessoas; i++) {
            if (contemTexto(pessoas[i].nome, nomeBusca)) {
                printf("Pessoa encontrada: %s\n", pessoas[i].nome);
                return i; 
            }
        }
    }
    return -1;  
    
}

void verCadastros() {
    int idPessoa;
    int opcao;
    printf("Deseja acessar qual funcionalidade? \n");
    printf("1. Ver cadastro pessoal\n");
    printf("2. Ver todos os cadastros\n");
    printf("3. Sair\n");
    scanf(" %d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
        idPessoa = buscarCadastro();
        if (idPessoa != -1) {
            printf("Nome: %s\n", pessoas[idPessoa].nome);
            printf("Dinheiro pessoal: %.2f\n", pessoas[idPessoa].dinheiro.pessoal);
            printf("Gastos: %.2f\n", pessoas[idPessoa].dinheiro.gastos);
            printf("Número de tarefas: %d\n", pessoas[idPessoa].totalTarefas);
        } else {
            printf("Pessoa não encontrada!\n");
        }
        break;
    case 2:
        for (int i = 0; i < QtdPessoas; i++) {
            printf("Nome: %s\n", pessoas[i].nome);
            printf("Dinheiro pessoal: %.2f\n", pessoas[i].dinheiro.pessoal);
            printf("Gastos: %.2f\n", pessoas[i].dinheiro.gastos);
            printf("Número de tarefas: %d\n", pessoas[i].totalTarefas);
            printf("-------------------------\n");
        }
        break;
    case 3:
        printf("Saindo...\n");
        break;
        
    default:
        printf("Opção inválida!\n");
        break;
    }
}

void modificarCadastro() {
    int idPessoa = buscarCadastro();
    int opcao;

    printf("O que deseja alterar no cadastro de %s?\n", pessoas[idPessoa].nome);
    printf("1. Nome\n");
    printf("2. Quantidade de dinheiro\n");
    scanf(" %d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
        printf("Digite o novo nome para %s: ", pessoas[idPessoa].nome);
        scanf(" %199[^\n]", pessoas[idPessoa].nome);
        getchar();
        break;
    case 2:
        printf("Digite a nova quantidade de dinheiro para %s: ", pessoas[idPessoa].nome);
        scanf("%f", &pessoas[idPessoa].dinheiro.pessoal);
        getchar();
        break;
    
    default:
        printf("Opção inválida!\n");
        break;
    }


    if (idPessoa != -1) {
        printf("Digite o novo nome para %s: ", pessoas[idPessoa].nome);
        scanf(" %199[^\n]", pessoas[idPessoa].nome);
        getchar();
        printf("Digite a nova quantidade de dinheiro para %s: ", pessoas[idPessoa].nome);
        scanf("%f", &pessoas[idPessoa].dinheiro.pessoal);
        getchar();
        atualizarValorTotal();
        printf("Cadastro modificado com sucesso!\n");
    } else {
        printf("Pessoa não encontrada!\n");
    }
}

void gerenciarCadastros() {
    int opcao;
    printf("Deseja acessar qual funcionalidade? \n");
    printf("1. Ver cadastro\n");
    printf("2. Modificar cadastro\n");
    printf("3. Sair\n");
    scanf(" %d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            verCadastros();
            break;
        case 2:
            modificarCadastro();
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

// Financeiro

void calcularGastos(){
    atualizarValorTotal();
    float gastoTotal;
    printf("Digite o valor total de gastos: ");
    scanf("%f", &gastoTotal);
    getchar();

    // Dividir o gasto total pelo número de pessoas para obter o valor que cada pessoa deve contribuir
    for (int i = 0; i < QtdPessoas; i++) {
        if(dinheiro.total > 0) {
            pessoas[i].dinheiro.gastos = (pessoas[i].dinheiro.pessoal / dinheiro.total) * gastoTotal;
            printf("%s deve contribuir com: %.2f\n", pessoas[i].nome, pessoas[i].dinheiro.gastos);
        } else {
            printf("Não é possível calcular os gastos. Pois não há valor registrado\n");
            break;
        }
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

// Tarefas

void verTarefas() {
    int idPessoa;
    int opcao;

    printf("Deseja acessar qual funcionalidade? \n");
    printf("1. Tarefas individuais\n");
    printf("2. Todas as tarefas\n");
    printf("3. Sair\n");
    scanf(" %d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
        // Tarefas individuais
        idPessoa = buscarCadastro();
        if (idPessoa != -1) {
            printf("Tarefas de %s:\n", pessoas[idPessoa].nome);
            for (int f = 0; f < pessoas[idPessoa].totalTarefas; f++) {
                printf("- %s\n", pessoas[idPessoa].tarefas[f].nome);
                printf("  Descrição: %s\n", pessoas[idPessoa].tarefas[f].descricao);   
                printf("  Tipo: %s\n", pessoas[idPessoa].tarefas[f].monetaria ? "Monetária" : "Não monetária");
                if (pessoas[idPessoa].tarefas[f].concluida) {
                    printf("  Status: Concluída\n");
                } else {
                    printf("  Status: Pendente\n");   
                }
            }
        } else {
            printf("Pessoa não encontrada!\n");
        }

    break;
    
    case 2:
        // Todas as tarefas
        for (int i = 0; i < QtdPessoas; i++) {
                printf("Tarefas de %s:\n", pessoas[i].nome);
                for (int f = 0; f < pessoas[i].totalTarefas; f++) {
                    printf("- %s\n", pessoas[i].tarefas[f].nome);
                    printf("  Descrição: %s\n", pessoas[i].tarefas[f].descricao);   
                    printf("  Tipo: %s\n", pessoas[i].tarefas[f].monetaria ? "Monetária" : "Não monetária");
                    if (pessoas[i].tarefas[f].concluida) {
                        printf("  Status: Concluída\n");
                    } else {
                        printf("  Status: Pendente\n");   
                    }
                }
            }
    break;

    case 3:
        printf("Saindo...\n");
    break;

    default:
        printf("Opção inválida!\n");
        break;
    }
}

void adicionarTarefas() {
    int idPessoa = buscarCadastro();

    if (idPessoa != -1) {

        int tarefas = pessoas[idPessoa].totalTarefas;

        if (tarefas <= 100) {
            char monetaria;
            printf("A tarefa é monetária? (s/n): ");
            scanf(" %c", &monetaria);
            getchar();

            switch (tolower(monetaria)) {
            case 's':
                
                printf("Digite a tarefa para %s: ", pessoas[idPessoa].nome);
                scanf(" %99[^\n]", pessoas[idPessoa].tarefas[tarefas].nome);
                getchar();

                printf("Está tarefa tem uma descrição? (s/n): ");
                char temDescricao;
                scanf(" %c", &temDescricao);
                getchar();

                if (tolower(temDescricao) == 's') {
                    printf("Digite a descrição da tarefa: ");
                    scanf(" %199[^\n]", pessoas[idPessoa].tarefas[tarefas].descricao);
                    getchar();
                } else {
                    strcpy(pessoas[idPessoa].tarefas[tarefas].descricao, "Nenhuma");
                }

                printf("Digite a estimativa do valor associado à tarefa: ");
                scanf("%f", &pessoas[idPessoa].dinheiro.gastos);
                getchar();
                pessoas[idPessoa].tarefas[tarefas].concluida = false;
                pessoas[idPessoa].totalTarefas++;
                printf("Tarefa adicionada com sucesso!\n");
                pessoas[idPessoa].tarefas[tarefas].monetaria = true;

                break;
            case 'n':
                
                printf("Digite a tarefa para %s: ", pessoas[idPessoa].nome);
                scanf(" %99[^\n]", pessoas[idPessoa].tarefas[tarefas].nome);
                getchar();
                printf("Está tarefa tem uma descrição? (s/n): ");
                char temDescricao2;
                scanf(" %c", &temDescricao2);
                getchar();

                if (tolower(temDescricao2) == 's') {
                    printf("Digite a descrição da tarefa: ");
                    scanf(" %199[^\n]", pessoas[idPessoa].tarefas[tarefas].descricao);
                    getchar();
                } else {
                    strcpy(pessoas[idPessoa].tarefas[tarefas].descricao, "Nenhuma");
                }

                pessoas[idPessoa].tarefas[tarefas].concluida = false;
                pessoas[idPessoa].totalTarefas++;
                printf("Tarefa adicionada com sucesso!\n");                    
                pessoas[idPessoa].tarefas[tarefas].monetaria = false;

                break;
            default:
                printf("Opção inválida! Tarefa não adicionada.\n");
                break;
            }
            
        }
    }
    
}

void mudarTarefas() {
    int idPessoa = buscarCadastro();

        if (idPessoa != -1) {
            int tarefas = pessoas[idPessoa].totalTarefas;
            if (tarefas > 0) {
                printf("Tarefas de %s:\n", pessoas[idPessoa].nome);
                for (int f = 0; f < tarefas; f++) {
                    printf("%d. %s\n", f + 1, pessoas[idPessoa].tarefas[f].nome);
                }
                int tarefaEscolhida;
                printf("Digite o número da tarefa que deseja modificar: ");
                scanf("%d", &tarefaEscolhida);
                getchar();

                if (tarefaEscolhida > 0 && tarefaEscolhida <= tarefas) {
                    int opcao;
                    printf("O que deseja modificar na tarefa?\n");
                    printf("1. Nome\n");
                    printf("2. Descrição\n");
                    scanf("%d", &opcao);
                    getchar();

                    switch (opcao) {
                        case 1:
                            printf("Digite o novo nome para a tarefa: ");
                            scanf(" %99[^\n]", pessoas[idPessoa].tarefas[tarefaEscolhida - 1].nome);
                            getchar();
                            printf("Tarefa modificada com sucesso!\n");
                        break;
                        case 2:
                            printf("Digite a nova descrição para a tarefa: ");
                            scanf(" %199[^\n]", pessoas[idPessoa].tarefas[tarefaEscolhida - 1].descricao);
                            getchar();
                            printf("Tarefa modificada com sucesso!\n");
                        break;  
                        default:
                            printf("Opção inválida! Tarefa não modificada.\n");
                        break;
                    }

                } else {
                    printf("Número de tarefa inválido!\n");
                }
            } else {
                printf("%s não tem tarefas cadastradas.\n", pessoas[idPessoa].nome);
            }
        }
}

void statusTarefas() {
    int idPessoa = buscarCadastro();

    if (idPessoa != -1) {
        int tarefas = pessoas[idPessoa].totalTarefas;
        if (tarefas > 0) {
            printf("Tarefas de %s:\n", pessoas[idPessoa].nome);
            for (int f = 0; f < tarefas; f++) {
                printf("%d. %s\n", f + 1, pessoas[idPessoa].tarefas[f].nome);
            }
            int tarefaEscolhida;
            printf("Digite o número da tarefa que deseja marcar como concluída: ");
            scanf("%d", &tarefaEscolhida);
            getchar();

            if (tarefaEscolhida > 0 && tarefaEscolhida <= tarefas) {
                if(pessoas[idPessoa].tarefas[tarefaEscolhida - 1].monetaria) {
                    printf("informe o valor gasto na tarefa: ");
                    scanf("%f", &pessoas[idPessoa].dinheiro.gastos);
                    getchar();
                    dinheiro.gastoTotal += pessoas[idPessoa].dinheiro.gastos;
                }
                pessoas[idPessoa].tarefas[tarefaEscolhida - 1].concluida = true;
                printf("Tarefa marcada como concluída!\n");
            } else {
                printf("Número de tarefa inválido!\n");
            }
        } else {
            printf("%s não tem tarefas cadastradas.\n", pessoas[idPessoa].nome);
        }
    }
        
}

void tarefas() {
    int opcao;
    printf("Deseja acessar qual funcionalidade\n");
    printf("1. Ver tarefas\n");
    printf("2. Adicionar tarefas\n");
    printf("3. Modificar tarefas\n");
    printf("4. Marcar tarefa como concluída\n");
    printf("5. Sair\n");
    scanf(" %d", &opcao);
    getchar();
    
    switch (opcao) {
    case 1:
        verTarefas();
        break;
    case 2:
        adicionarTarefas();
        break;
    case 3:
        mudarTarefas();
        break;
    case 4:
        statusTarefas();
        break;
    case 5:
        printf("Saindo...\n");
        break;
    default:
        printf("Opção inválida!\n");
        break;

    }
}

// Sair
void sair() {
    printf("Saindo...\n");
    salvarDados();
}

// Carregar dados do arquivo
void carregarDados() {
    FILE *arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) { //verificar se o arquivo existe
        printf("Nenhum arquivo de dados encontrado. Iniciando com dados vazios.\n");
        return;
    }

    char linha[256]; // buffer para ler as linhas do arquivo
    int pessoaIndex = -1;
    int tarefaAtual = -1;

    while (fgets(linha, sizeof(linha), arquivo)) { //ler o arquivo linha por linha
        if (strncmp(linha, "Nome: ", 6) == 0) { //verificar se a linha começa com "Nome: "
            pessoaIndex++;
            sscanf(linha, "Nome: %[^\n]", pessoas[pessoaIndex].nome); //extrair o nome da pessoa
            pessoas[pessoaIndex].cadastroCompleto = true;
            tarefaAtual = -1; //resetar o índice da tarefa para a nova pessoa
        } else if (strncmp(linha, "Dinheiro Pessoal: ", 18) == 0) { //verificar se a linha começa com "Dinheiro Pessoal: "
            sscanf(linha, "Dinheiro Pessoal: %f", &pessoas[pessoaIndex].dinheiro.pessoal); //extrair o dinheiro pessoal da pessoa
        } else if (strncmp(linha, "Gastos: ", 8) == 0) { //verificar se a linha começa com "Gastos: "
            sscanf(linha, "Gastos: %f", &pessoas[pessoaIndex].dinheiro.gastos); //extrair os gastos da pessoa
        } else if (strncmp(linha, "Total de dinheiro: ", 19) == 0) { //verificar se a linha começa com "Total de dinheiro: "
            sscanf(linha, "Total de dinheiro: %f", &pessoas[pessoaIndex].dinheiro.total); //extrair o total de dinheiro
        } else if (strncmp(linha, "Total de tarefas: ", 18) == 0) { //verificar se a linha começa com "Total de tarefas: "
            sscanf(linha, "Total de tarefas: %d", &pessoas[pessoaIndex].totalTarefas); //extrair o total de tarefas da pessoa
        } else if (strncmp(linha, "Tarefa ", 7) == 0) { //verificar se a linha começa com "Tarefa "
            tarefaAtual++;
            sscanf(linha, "Tarefa %*d: %[^\n]", pessoas[pessoaIndex].tarefas[tarefaAtual].nome); //extrair a descrição da tarefa
        } else if (strncmp(linha, "Descrição: ", 11) == 0) { //verificar se a linha começa com "Descrição: "
            sscanf(linha, "Descrição: %[^\n]", pessoas[pessoaIndex].tarefas[tarefaAtual].descricao); //extrair a descrição da tarefa
        } else if (strncmp(linha, "Tipo: ", 6) == 0) { //verificar se a linha começa com "Tipo: "
            char tipo[20];
            sscanf(linha, "Tipo: %[^\n]", tipo); //extrair o tipo da tarefa
            pessoas[pessoaIndex].tarefas[tarefaAtual].monetaria = (strcmp(tipo, "Monetária") == 0); //definir se a tarefa é monetária
        } else if (strncmp(linha, "Status: ", 8) == 0) { //verificar se a linha começa com "Status: "
            int status;
            sscanf(linha, "Status: %d", &status); //extrair o status da tarefa
            pessoas[pessoaIndex].tarefas[tarefaAtual].concluida = (status == 1); //definir se a tarefa está concluída ou pendente
        }
    }

    QtdPessoas = pessoaIndex + 1;

    fclose(arquivo);
    atualizarValorTotal();
}

// Função principal
int main() {
    carregarDados();

    int opcao;
    do {
        printf("Bem-vindo ao sistema de gerenciamento financeiro e de tarefas!\n");
        printf("\n");
        printf("1. Cadastro de pessoas\n");
        printf("2. Gerenciamento de cadastros\n");
        printf("3. Gerenciamento financeiro\n");
        printf("4. Gerenciamento de tarefas\n");
        printf("5. Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            cadastro();
            break;
        case 2:
            gerenciarCadastros();
            break;
        case 3:
            financia();
            break;
        case 4:
            tarefas();
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }

        salvarDados();
    } while (opcao != 4);
    
}
