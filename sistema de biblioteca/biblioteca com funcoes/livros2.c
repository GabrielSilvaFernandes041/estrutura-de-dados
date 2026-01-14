#include <stdio.h>  // Biblioteca padrão para entrada e saída de dados, como printf e scanf
#include <stdlib.h> // Biblioteca para gerenciamento de memória dinâmica e controle de processos
#include <string.h> // Biblioteca para manipulação de cadeias de caracteres (strings)

#define max_livros 50      // Define o limite máximo de livros que podem ser armazenados no sistema
#define max_string 100     // Define o tamanho máximo para qualquer campo de texto (nome, autor, etc.)
#define max_emprestimos 10 // Define o limite máximo de registros de empréstimos ativos

// Variável responsável por pegar algumas informações importantes do livro
// Sendo essas informações: Nome, Autor, Editora e Edição
typedef struct { // Define o modelo de dados (estrutura) para representar um livro
    char nome[max_string];      // Vetor de caracteres para armazenar o título do livro
    char autor[max_string];     // Vetor de caracteres para armazenar o nome do autor do livro
    char editora[max_string];   // Vetor de caracteres para armazenar o nome da editora
    int edicao;                 // Inteiro para registrar o número da edição do exemplar
    int disponivel;             // Flag inteira: 1 indica que o livro está na estante, 0 indica que foi emprestado
} livros; // Nome do tipo definido pela estrutura

// Variável responsável por pegar informações do empréstimo ao usuário
// Sendo essas informações: Nome do Usuário e o id do livro no qual o usuário pegou emprestado
typedef struct { // Define o modelo de dados para registrar quem pegou qual livro
    char nomeUsuario[max_string];   // Armazena o nome da pessoa que solicitou o empréstimo
    int idLivro;                    // Armazena o índice (ID) correspondente ao livro no array 'biblioteca'
} emprestimoLista; // Nome do tipo definido pela estrutura

// Limpa o buffer do scanf e do fgets
void limparBuffer(void){ // Função utilitária para limpar caracteres residuais no buffer do teclado
    int c; // Variável para armazenar temporariamente cada caractere lido
    while ((c = getchar()) != '\n' && c != EOF); // Consome caracteres até encontrar uma nova linha ou fim de arquivo
}

livros             *biblioteca; // Ponteiro global que será usado para o array dinâmico de livros
emprestimoLista     *emprestimo; // Ponteiro global que será usado para o array dinâmico de empréstimos

// Variável global
int global_totalEmprestimo = 0; // Contador que monitora a quantidade atual de empréstimos realizados

// Funções responsáveis por cadastrar cada passo do livro
// Sendo eles: Nome do Livro, Nome do Autor, Nome da Editora, Edição e Se ele está disponível para empréstimo ou não
void cadastraLivro(int* _indexLivro){ // Função que recebe a referência do contador de livros para adicionar um novo
    printf(" \n---------------------------------------- \n"); // Divisor visual no terminal
    printf("Sistema de cadastro de Livros \n"); // Cabeçalho do formulário
    
    // Cadastre o Nome do Livro
    printf("Nome do livro: "); // Prompt para o usuário
    fgets(biblioteca[*_indexLivro].nome, max_string, stdin); // Lê o nome do livro garantindo captura de espaços
    biblioteca[*_indexLivro].nome[strcspn(biblioteca[*_indexLivro].nome, "\n")] = '\0'; // Remove o caractere de nova linha '\n' lido pelo fgets

    // Cadastre o nome do autor
    printf("Nome do Autor: "); // Prompt para o autor
    fgets(biblioteca[*_indexLivro].autor, max_string, stdin); // Lê o autor do livro
    biblioteca[*_indexLivro].autor[strcspn(biblioteca[*_indexLivro].autor, "\n")] = '\0'; // Remove a quebra de linha final

    // Cadastre o nome da Editora
    printf("Nome da Editora: "); // Prompt para a editora
    fgets(biblioteca[*_indexLivro].editora, max_string, stdin); // Lê a editora do livro
    biblioteca[*_indexLivro].editora[strcspn(biblioteca[*_indexLivro].editora, "\n")] = '\0'; // Remove a quebra de linha final

    // Cadastre a edição do livro
    printf("Edição do Livro: "); // Prompt para edição
    scanf("%d", &biblioteca[*_indexLivro].edicao); // Lê o número inteiro da edição

    // Define que o livro cadastrado tem o valor de disponivel = 1. Significando que ele pode ser emprestado
    biblioteca[*_indexLivro].disponivel = 1; // Inicializa o livro como disponível no sistema

    // Define o id do próximo livro a ser cadastrado
    (*_indexLivro) ++; // Incrementa o contador de livros através do ponteiro recebido

    printf("---------------------------------------- \n"); // Divisor visual

    limparBuffer(); // Limpa o buffer para evitar problemas em futuras leituras de strings
}

void mostraLivrosCadastrado(int* _indexLivro){ // Função para exibir todos os livros registrados
    printf(" \n---------------------------------------- \n"); // Divisor visual
    printf("Sistema de mostrar livros cadastrados \n"); // Cabeçalho da listagem

    if (*_indexLivro > 0){ // Verifica se há pelo menos um livro cadastrado
        // Pega o valor armazenado no endereço de _indexLivro
        for(int i = 0; i < *_indexLivro; i++){ // Percorre o array 'biblioteca' do índice 0 até o total cadastrado
            // Mostra todos os livros cadastrados até agora
            // Mostrando o livro, seus autores, sua editora e sua edição

            printf("\nLivro: %s \n", biblioteca[i].nome); // Imprime o título do exemplar
            printf("Autor: %s \n", biblioteca[i].autor); // Imprime o autor do exemplar
            printf("Editora: %s \n", biblioteca[i].editora); // Imprime a editora do exemplar

            printf("Edição: %d \n", biblioteca[i].edicao); // Imprime o número da edição

            // Detector se está disponível ou não
            char _disponivel[max_string]; // String temporária para traduzir o status booleano
            if (biblioteca[i].disponivel == 1) { strcpy(_disponivel, "Sim"); } // Se 1, o texto é "Sim"
            else { strcpy(_disponivel, "Não"); } // Se 0, o texto é "Não"

            printf("Disponível: %s\n", _disponivel); // Exibe o status de disponibilidade para o usuário
        }

        printf("---------------------------------------- \n"); // Divisor visual
    }
    else { // Caso não existam livros cadastrados
        printf(" \n---------------------------------------- \n"); // Divisor visual
        printf("Nenhum livro cadastrado!!"); // Mensagem de aviso
        printf(" \n---------------------------------------- \n"); // Divisor visual
    }
}

void emprestimoLivro(int* _indexLivro){ // Função para processar a saída de um livro para um usuário
    printf(" \n---------------------------------------- \n"); // Divisor visual
    printf("Sistema de empréstimo de livros \n"); // Cabeçalho da operação

    // Verifica se ainda pode pedir empréstimo
    if (global_totalEmprestimo < max_emprestimos){ // Impede a operação se o limite de 10 empréstimos foi atingido
        int _disponivel = 0; // Contador auxiliar para livros aptos a empréstimo

        // Mostra livros disponíveis
        for (int i = 0; i < *_indexLivro; i ++){ // Varre todos os livros cadastrados no sistema

            // Define o ID de cada livro
            // Passa o Nome e o ID de cada livro de acordo com a quantidade de livros cadastrados e só mostra livros disponíveis para empréstimos
            emprestimo[i].idLivro = i; // Sincroniza o ID com o índice atual (uso didático no loop)
            
            int _idLivro = emprestimo[i].idLivro; // Variável auxiliar para identificar o livro

            // Seção de disponível ou não
            char _disponivelString[max_string]; // Tradução do status de disponibilidade
            if (biblioteca[_idLivro].disponivel == 1) { strcpy(_disponivelString, "Sim"); } else { strcpy(_disponivelString, "Não"); } // Verifica se pode emprestar

            // Mostra o nome do livro, o ID e se ele está disponível para empréstimo
            printf("Livro: %s - ID: %d - Disponível: %s\n", biblioteca[_idLivro].nome, _idLivro, _disponivelString); // Lista o catálogo

            _disponivel++; // Incrementa contador de livros processados
            
        }
        
            if (_disponivel != 0){ // Se existem livros cadastrados

                int _idLivroSelection; // Variável para armazenar a escolha do ID pelo usuário

                if (_disponivel > global_totalEmprestimo){ // Lógica interna para permitir novos empréstimos
                    // Usa-se a variável global_totalEmprestimo para definir os array de empréstimo
                    // Pois primeiro o array começará no 0 igual à variável e ao final do empréstimo será incrementado um novo valor
                    // Fazendo com que o array de empréstimo ande para frente e possa ser incrementado um novo local de empréstimo
                                
                    printf("Quem está pegando o livro: "); // Solicita o nome do cliente
                    fgets(emprestimo[global_totalEmprestimo].nomeUsuario, max_string, stdin); // Captura o nome do usuário
                    emprestimo[global_totalEmprestimo].nomeUsuario[strcspn(emprestimo[global_totalEmprestimo].nomeUsuario, "\n")] = '\0'; // Limpa o '\n'

                    printf("Informe o ID do livro que será emprestado: "); // Solicita o ID numérico
                    scanf("%d", &_idLivroSelection); // Lê a seleção do usuário

                    if (_idLivroSelection < *_indexLivro){ // Valida se o ID escolhido existe no sistema
                        // Verifica se o livro escolhido já está emprestado
                        if (biblioteca[_idLivroSelection].disponivel == 1){ // Se o livro estiver na estante
                            biblioteca[_idLivroSelection].disponivel = 0; // Altera o status para emprestado (0)
                            emprestimo[global_totalEmprestimo].idLivro = _idLivroSelection; // Registra qual livro foi pego no log de empréstimos
                            printf("Livro emprestado com sucesso!! \n"); // Mensagem de sucesso
                            
                            // Aumenta a quantidade de empréstimo realizada
                            global_totalEmprestimo ++; // Incrementa o total global para apontar para a próxima posição do array
                        } else { printf("Livro fora do sistema ou já foi emprestado! \n"); } // Erro de disponibilidade
                    
                        limparBuffer(); // Limpa o buffer para a próxima operação
                    } else { // Caso o ID digitado não exista
                        printf("Livro não encontrado! \n"); // Mensagem de erro de ID
                    }
                } else { printf("Todos os livros foram emprestados! \n"); } // Erro se não houver estoque disponível

            } else { printf("Nenhum livro cadastrado! \n"); } // Erro se a biblioteca estiver vazia
        

    } else { printf("Máximo de empréstimos realizados!"); } // Erro se o limite de transações for atingido

    printf("---------------------------------------- \n"); // Divisor visual
}

void mostraEprestimo(){ // Função para listar os empréstimos ativos e seus respectivos usuários
    printf(" \n---------------------------------------- \n"); // Divisor visual
    printf("Sistema de mostrar livros emprestados \n"); // Cabeçalho do relatório

    if (global_totalEmprestimo == 0){ // Verifica se existem registros na lista de empréstimos
        printf("Nenhum livro emprestado! \n"); // Informa lista vazia
    }
    else { // Se houver registros
        printf("Livros emprestados: \n"); // Título da lista

        for (int i = 0; i < global_totalEmprestimo; i ++){ // Percorre o histórico de empréstimos realizados
            // Mostra o ID, o livro e quem pegou emprestado
            int _idLivro = emprestimo[i].idLivro; // Recupera o ID do livro para buscar o nome na biblioteca

            printf("Usuário: %s - Livro: %s - ID: %d \n", emprestimo[i].nomeUsuario, biblioteca[_idLivro].nome, _idLivro); // Imprime o relatório
        }
    }

    printf("---------------------------------------- \n"); // Divisor visual
}

int main(){ // Função de entrada principal do programa

    int opcoes; // Variável para armazenar a escolha do menu pelo usuário
    int indexLivro = 0; // Variável local que conta quantos livros estão cadastrados

    // Alocação dinâmica de memória:
    biblioteca = (livros *)             calloc (max_livros, sizeof(livros)); // Aloca espaço para 50 livros, limpando a memória com zeros
    emprestimo = (emprestimoLista *)    malloc (max_emprestimos * sizeof(emprestimoLista)); // Aloca espaço para 10 empréstimos

    do { // Inicia o laço de repetição do menu principal
        printf(" \n---------------------------------------- \n"); // Estética do menu
        printf("Bem-vindo ao sistema de cadastro de livros \n"); // Boas-vindas
        printf("Abaixo está como funciona o sistema \n"); // Instruções
        printf("1 - Cadastrar um novo livro \n"); // Menu 1
        printf("2 - Mostrar todos os livros cadastrados \n"); // Menu 2
        printf("3 - Sistema de empréstimo de livros \n"); // Menu 3
        printf("4 - Mostrar livros emprestados \n"); // Menu 4
        printf("0 - Sair do Sistema \n"); // Menu 0
        printf("Digite sua opção: "); // Prompt de escolha
        scanf("%d", &opcoes); // Lê a opção escolhida
        printf("---------------------------------------- \n"); // Estética do menu

        limparBuffer(); // Garante que o buffer esteja limpo para as funções que serão chamadas


        switch (opcoes) // Estrutura de controle para direcionar a execução baseada na opção
        {
            case (1):{ // Caso o usuário escolha cadastrar
                cadastraLivro(&indexLivro); // Passa o endereço de indexLivro para ser alterado dentro da função
            }
            break; // Sai do switch
            
            case(2):{ // Caso escolha mostrar cadastrados
                mostraLivrosCadastrado(&indexLivro); // Passa o endereço para leitura na função
            }
            break; // Sai do switch

            case(3):{ // Caso escolha emprestar
                emprestimoLivro(&indexLivro); // Chama a lógica de empréstimo
            }break; // Sai do switch

            case(4):{ // Caso escolha ver empréstimos
                mostraEprestimo(); // Chama a exibição de logs de empréstimo
            }break; // Sai do switch

            case(0):{ // Caso escolha encerrar
                free(biblioteca); // Libera a memória alocada dinamicamente para os livros (evita memory leak)
                free(emprestimo); // Libera a memória alocada dinamicamente para os empréstimos

                printf("Memória liberada!! \n"); // Feedback de segurança
                printf("Até logo!! \n"); // Mensagem de encerramento

                return 0; // Finaliza o programa retornando 0 ao sistema operacional
            }break; // Fim do caso 0

            default: // Caso o usuário digite um número não listado no menu

            break; // Simplesmente ignora e volta ao loop
        }
    } while(opcoes != 0); // O loop continua rodando enquanto a opção for diferente de zero
}