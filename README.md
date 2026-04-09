# Organizador de Finanças

## 📋 Descrição do Projeto

Sistema de gerenciamento desenvolvido em **C++** para controle de finanças compartilhadas e organização de atividades em grupo. O projeto foca em algoritmos de divisão proporcional e persistência de dados em arquivos de texto.

## 🛠️ Especificações Técnicas

- **Linguagem:** C++ (Padrão Procedural).
- **Estruturas:** `structs` aninhadas para gerenciamento de dados complexos.
- **Busca:** Implementação customizada de busca de substring com normalização de caracteres (`tolower`).
- **Persistência:** Manipulação de arquivos com as bibliotecas `cstdio` e `cstring`.

## 📈 Lógica Matemática: Divisão de Gastos

A divisão não é feita de forma igualitária (divisão simples), mas sim **proporcional**. 
A fórmula aplicada no código é:
`Gasto Individual = (Saldo Pessoal / Saldo Total do Grupo) * Gasto Total Previsto`

## 🚀 Funcionalidades Atuais

- **Divisão Proporcional de Gastos**: Algoritmo que distribui custos de forma justa, baseada no saldo individual de cada membro.
- **Busca Inteligente (Case-Insensitive)**: Sistema de localização de usuários que ignora a diferença entre letras maiúsculas e minúsculas (ex: "Joao" encontra "JOÃO").
- **Gestão de Tarefas Dinâmica**: Controle de afazeres individuais com suporte a descrições detalhadas e marcação de status (Concluída/Pendente).
- **Persistência de Dados (I/O)**: Sistema automático de salvamento e carregamento via arquivo `dados.txt`.
- **UX no Terminal**: Tratamento de buffer de teclado para suportar entradas com espaços (nomes compostos e frases).

## 🛠️ Como Usar

1. **Compilar:**
   ```bash
   g++ main.cpp -o organizador
   ```

2. **Executar:**
   ```bash
   ./organizador
   ```

3. **Menu:**
   - 1: Cadastro de pessoas
   - 2: Gerenciamento financeiro (total)
   - 3: Gerenciamento de tarefas
   - 4: Sair

## 📁 Estrutura do Projeto
- `main.cpp`: Código principal
- `README.md`: Esta documentação
- `licenca.md`: Licença do projeto

## 🤝 Contribuições
Sinta-se à vontade para abrir issues ou pull requests! Fork o repo e contribua com as tarefas pendentes.

## 📄 Licença
MIT License - veja [licenca.md](licenca.md).

