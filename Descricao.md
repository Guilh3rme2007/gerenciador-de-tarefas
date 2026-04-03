# 📊 Organizador de Finanças e Tarefas em C++

Este é um sistema robusto desenvolvido em **C++** focado no gerenciamento financeiro e de produtividade para grupos (famílias, colegas de quarto ou equipes). O projeto destaca o uso de estruturas de dados personalizadas, manipulação de arquivos para persistência e uma lógica matemática para divisão proporcional de custos.



## 🚀 Funcionalidades Principais

* **Gerenciamento Financeiro Inteligente**: Cadastro de saldo pessoal e cálculo automático de contribuição baseada em divisão proporcional (quem possui maior saldo assume uma fatia maior dos gastos).
* **Controle de Tarefas Dinâmico**: Adição, visualização, modificação e alteração de status (concluída/pendente) de tarefas por integrante.
* **Persistência de Dados**: Sistema de salvamento e carregamento automático via arquivo `dados.txt`, garantindo que as informações não sejam perdidas ao fechar o programa.
* **Busca Otimizada**: Localização de cadastros por nome ou parte dele utilizando busca de substring (`strstr`).

## 🛠️ Tecnologias e Conceitos Aplicados

* **Linguagem**: C++ (padrão C-style para manipulação de memória e strings).
* **Estruturas de Dados**: Uso de `structs` aninhadas para organizar informações de pessoas, finanças e atividades.
* **Manipulação de Arquivos**: Implementação de leitura/escrita com `fopen`, `fprintf`, `fgets` e `sscanf`.
* **Lógica de Negócio**: Algoritmo de divisão proporcional de gastos.

## 📂 Estrutura do Código

```cpp
struct responsaveis {
   char nome[100];
   struct dinheiro dinheiro; // Dados de saldo e gastos
   char tarefas[100][200];   // Matriz para múltiplas tarefas
   int totalTarefas;         // Controle de índice
   // ...
};
```

## 📈 Próximos Passos (Roadmap)

* [ ] Implementação de Interface Gráfica (GUI) utilizando **Qt** ou **ImGui**.
* [ ] Sistema de categorias de gastos (fixos vs. variáveis).
* [ ] Exportação de relatórios em formato CSV para Excel.
* [ ] Criptografia básica para proteção dos dados financeiros no arquivo TXT.

## 🤝 Como Contribuir

1.  Faça um **Fork** do projeto.
2.  Crie uma **Branch** para sua modificação (`git checkout -b feature/nova-funcionalidade`).
3.  Abra um **Pull Request** detalhando as melhorias.

---
**Desenvolvido por Guilherme**.