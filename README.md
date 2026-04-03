# Organizador de Finanças

## 📋 Descrição do Projeto

O **Organizador de Finanças** é um aplicativo console em C++ para gerenciamento financeiro e de tarefas em grupo (ex: família, roommates, equipe). Permite cadastrar pessoas com suas contribuições financeiras, visualizar totais, adicionar/visualizar tarefas por pessoa e salvar dados em arquivo.

**Funcionalidades Implementadas:**
- Cadastro de pessoas com valores de dinheiro pessoal (soma total calculada)
- Visualização do dinheiro total disponível
- Gerenciamento de tarefas: adicionar ou listar por pessoa (busca por nome)
- Salvamento automático de dados em `dados.txt`
- Menu interativo simples

**Próximos Passos (baseado em TODO.md original):**
1. Calcular dinheiro após gastos possíveis
2. Listar pessoas com posse de dinheiro
3. Listar gastos possíveis
4. Dividir dinheiro pelos gastos
5. Imprimir resultados
6. Listar e imprimir tarefas (geral/por pessoa)
7. Mostrar tarefas por pessoa + dinheiro gasto
8. Salvar dados avançados

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

