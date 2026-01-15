# Projeto de Estrutura de Dados - Faculdade

Este projeto foi desenvolvido como parte das atividades da disciplina de **Estrutura de Dados** da faculdade. O objetivo principal é aplicar na prática os conceitos aprendidos em aula, como **ponteiros, passagem de parâmetros por função, modularização e alocação dinâmica de memória**, utilizando a linguagem **C**.

---

## O que estou aprendendo

Durante o desenvolvimento deste projeto, venho aplicando e consolidando os seguintes conceitos:

- **Ponteiros:** manipulação de endereços de memória e acesso direto a variáveis.
- **Passagem de parâmetros por função:** compreensão da diferença entre passagem por valor e por referência.
- **Modularização:** separação do código em funções e arquivos para melhor organização e reaproveitamento.
- **Alocação dinâmica de memória:** uso de `malloc`, `calloc` e `free` para gerenciar memória de forma eficiente.
- **Estruturas (`struct`) e arrays:** para organização de dados complexos, como cadastro de livros.

---

## Sobre o código

Um dos principais arquivos do projeto é o `cadastro_de_livros2.c`, que exemplifica todo o aprendizado:

- Permite **cadastrar livros**, armazenando informações como:
  - Nome
  - Autor
  - Editora
  - Edição
  - Disponibilidade
- Utiliza **ponteiros** para manipulação de dados dentro das funções.
- Aplica **modularização**, separando funções de cadastro, listagem e manipulação dos livros.
- Faz **alocação dinâmica de memória**, garantindo que a memória seja utilizada apenas quando necessário.
- Demonstra **passagem de parâmetros por referência**, permitindo modificar os dados diretamente nas funções.

O código foi pensado para ser **didático e funcional**, servindo como uma base para exercícios futuros e projetos mais complexos de estrutura de dados.

---

## Como executar

1. Clone este repositório:
   ```bash
   git clone https://github.com/SEU_USUARIO/NOME_DO_PROJETO.git

2. Acesse o diretório do projeto
   ```bash
   cd NOME_DO_PROJETO
3. Compile o código:
   ```bash
   gcc livros2.c -o cadastro
4. Execute:
    ```bash
   ./cadastro
