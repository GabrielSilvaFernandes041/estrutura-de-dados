#include <stdio.h>    // Inclui a biblioteca padrão de entrada e saída (printf, scanf, etc.)
#include <stdlib.h>   // Inclui a biblioteca para alocação dinâmica de memória (malloc, calloc, free)
#include <string.h>   // Inclui a biblioteca para manipulação de strings (strcspn)

#define MAX_STRING 100      // Define uma constante de 100 para o tamanho das strings
#define MAX_LIVROS 50       // Define o limite máximo de 50 livros no sistema
#define MAX_EMPRESTIMOS 30  // Define o limite máximo de 30 empréstimos ativos

// Objeto de cadsatro 
typedef struct {
    char    nome[MAX_STRING];    // Vetor de caracteres para o título do livro
    char    autor[MAX_STRING];   // Vetor de caracteres para o nome do autor
    char    editora[MAX_STRING]; // Vetor de caracteres para o nome da editora
    int     edisao;              // Variável inteira para o número da edição
    int     disponivel;          // Flag: 1 para Disponível | 0 para Indisponível

} livros; // Define o nome da estrutura como 'livros'

typedef struct{
    int livroID; // Armazena o índice (ID) do livro que foi emprestado

    char nomeusuario[MAX_STRING]; // Armazena o nome da pessoa que realizou o empréstimo
} emprestimo; // Define o nome da estrutura como 'emprestimo'

void limparBuffer(void) // Função para limpar o rastro do '\n' no buffer do teclado
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê os caracteres restantes até encontrar o fim da linha
}

int main(){

    livros      *biblioteca;       // Ponteiro que será usado para o array dinâmico de livros
    emprestimo  *emprestimosLista; // Ponteiro que será usado para o array dinâmico de empréstimos

    // Aloca memória para os livros e inicializa tudo com zero (calloc)
    biblioteca          = (livros*) calloc (MAX_LIVROS, sizeof(livros));
    // Aloca memória para a lista de empréstimos (malloc)
    emprestimosLista    = (emprestimo*)malloc (MAX_EMPRESTIMOS * sizeof(emprestimo));    

    if (biblioteca == NULL || emprestimosLista == NULL){ // Verifica se a alocação falhou
        printf("Erro ao alocar memória!!"); // Exibe mensagem de erro de memória
        return 1; // Encerra o programa com código de erro
    }

    // Mostra que as opções do programa
    int opcoes;              // Variável para armazenar a escolha do menu pelo usuário
    int indexLivros         = 0; // Contador de livros cadastrados atualmente
    int totalEmprestimos    = 0; // Contador de empréstimos realizados


    do { // Inicia o laço de repetição do menu principal
    printf(" \n//------------------------- \n");
    printf("Bem vindo ao sistema de cadrasto de livros \n");
    printf("A baixo está como funciona o sistema \n");
    printf("1 - Cadastrar um novo livro \n");
    printf("2 - Mostra todos os livros cadastrados \n");
    printf("3 - Sistema de emprestimo de livros \n");
    printf("4 - Mostra livros emprestados \n");
    printf("0 - Sair do Sistema \n");
    printf("Digie sua opção: ");
    scanf("%d", &opcoes); // Lê a opção numérica do usuário
    printf("//------------------------- \n");

    limparBuffer(); // Limpa o buffer para evitar erros no próximo input de texto

   
        switch (opcoes) // Estrutura de decisão baseada na opção escolhida
        {

            case(1):{ // Caso o usuário escolha cadastrar um novo livro
                printf("\n //------------------------- \n");

                if (indexLivros < MAX_LIVROS){ // Verifica se ainda há espaço no array de livros
                    
                    printf("Cadastrando livro %d de %d \n", indexLivros + 1, MAX_LIVROS); // Informa o progresso

                    printf("Livro: ");
                    fgets(biblioteca[indexLivros].nome, MAX_STRING, stdin); // Lê o nome do livro com espaços
                    biblioteca[indexLivros].nome[strcspn(biblioteca[indexLivros].nome, "\n")] = '\0'; // Remove o '\n' do final
                    
                    printf("Autor: ");
                    fgets(biblioteca[indexLivros].autor, MAX_STRING, stdin); // Lê o autor do livro
                    biblioteca[indexLivros].autor[strcspn(biblioteca[indexLivros].autor, "\n")] = '\0'; // Remove o '\n' do final
                    
                    printf("Editora: ");
                    fgets(biblioteca[indexLivros].editora, MAX_STRING, stdin); // Lê a editora
                    biblioteca[indexLivros].editora[strcspn(biblioteca[indexLivros].editora, "\n")] = '\0'; // Remove o '\n' do final

                    biblioteca[indexLivros].disponivel = 1; // Define o status inicial como disponível (1)

                    printf("Edição: ");
                    scanf("%d", &biblioteca[indexLivros].edisao); // Lê o número da edição
                    
                    

                    limparBuffer(); // Limpa o buffer após o scanf do número

                    indexLivros ++; // Incrementa o contador de livros cadastrados
                } else {
                    printf("Maximo de livros cadastrado!!"); // Avisa se o limite de 50 livros foi atingido
                }

                printf("\n //------------------------- \n");
            }break; // Sai do case 1
            
            case(2):{ // Caso o usuário escolha mostrar os livros
                printf(" \n//------------------------- \n");
                if (indexLivros != 0){ // Verifica se existe ao menos um livro no sistema
                    printf("Livros cadastrados \n");

                    for (int i = 0; i < indexLivros; i++){ // Percorre o array até a quantidade cadastrada

                        printf("\n");

                        printf("Livro: %s \n",     biblioteca[i].nome);    // Exibe o nome
                        printf("Autor: %s \n",     biblioteca[i].autor);   // Exibe o autor
                        printf("Editora: %s \n",    biblioteca[i].editora); // Exibe a editora
                        printf("Edição: %d \n",    biblioteca[i].edisao);  // Exibe a edição
                        
                        printf("\n");
                    }
                }
                else { printf("Nenhum livro cadastrado!! \n"); } // Caso a biblioteca esteja vazia

                printf("//------------------------- \n");
                printf("\n");
            }break; // Sai do case 2

            case(3):{ // Caso o usuário escolha o sistema de empréstimo
                printf(" \n//------------------------- \n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS){ // Verifica se atingiu 30 empréstimos
                    printf("Limite de emprestimos atingido!! \n");
                    break; // Interrompe a operação de empréstimo
                } else {
                    if (indexLivros > 0) { printf("Livros disponiveis: \n"); } // Cabeçalho se houver livros
                    int disponiveis = 0; // Contador auxiliar local


                    for (int i = 0; i < indexLivros; i++){ // Percorre os livros para ver quais estão livres
                        if (biblioteca[i].disponivel == 1){ // Se o campo for 1, o livro pode ser emprestado
                            printf("ID: %d - Livro: %s \n", i, biblioteca[i].nome); // Mostra o ID (índice) e nome
                            disponiveis++; // Incrementa contador de itens disponíveis
                        }
                    }

                    if (disponiveis == 0){ // Se percorreu tudo e não achou nenhum livre
                        printf("Nenhum livro disponivel para emprestimo!! \n");
                    } else {
                        int idLivro; // Variável para capturar a escolha do usuário

                        printf("Quem deseja pegar o livro emprestado?");
                        fgets(emprestimosLista[totalEmprestimos].nomeusuario, MAX_STRING, stdin); // Lê o nome do usuário
                        emprestimosLista[totalEmprestimos].nomeusuario[strcspn(emprestimosLista[totalEmprestimos].nomeusuario, "\n")] = '\0'; // Limpa o '\n'

                        printf("Digite o ID do livro que deseja emprestar: ");
                        scanf("%d", &idLivro); // Lê o ID desejado

                        limparBuffer(); // Limpa o buffer após o scanf

                        // Passando o parametro do livro emprestado para o objeto do usuario no qual pegou emprestado
                        emprestimosLista[totalEmprestimos].livroID = idLivro; // Registra qual ID de livro este empréstimo refere-se
                    

                        if (idLivro < 0 || idLivro >= indexLivros){ // Validação de segurança do ID digitado
                            printf("ID inválido!! \n");
                        } else {
                            if (biblioteca[idLivro].disponivel == 1){ // Verifica novamente se o livro está livre
                                biblioteca[idLivro].disponivel = 0;   // Marca o livro como Indisponível (0)
                                totalEmprestimos++;                    // Incrementa o contador global de empréstimos
                                printf("Emprestimo realizado com sucesso!! \n");
                            } else {
                                printf("ID invalido ou livro indisponivel!! \n"); // Erro caso o livro já esteja fora
                            }
                        }
                    }
                }   
                printf("//------------------------- \n");

            }break; // Sai do case 3

            case(4):{ // Caso o usuário queira ver o relatório de empréstimos
                printf(" \n//------------------------- \n");
                
                if (totalEmprestimos == 0){ // Se o contador for zero
                    printf("Nenhum Livro emprestado!!! \n");

                    printf("//------------------------- \n");
                    break;
                } else if (totalEmprestimos > 0){ // Se houver empréstimos registrados
                    printf("Livros emprestados \n");

                    // Loop ue mostra todos os livros emprestados
                    for (int i = 0; i < totalEmprestimos; i++){ // Percorre a lista de empréstimos ativos
                        
                        int idLivro = emprestimosLista[i].livroID; // Recupera o ID salvo para buscar na biblioteca

                        printf("Usuário - %s | Livro - %s \n", // Imprime o nome do usuário e o nome do livro via ID
                            emprestimosLista[i].nomeusuario,
                            biblioteca[idLivro].nome
                        ); 
                    }
                }

                printf("//------------------------- \n");

            }break; // Sai do case 4

            case(0):{ // Caso o usuário queira sair

                // Retirar espaço alocado de memoria caso saiam do sistema 
                free(biblioteca);        // Libera a memória alocada para os livros
                free(emprestimosLista);  // Libera a memória alocada para os empréstimos

                
                printf("Memoria liberada!! \n"); // Confirmação de limpeza

                printf("Nunca é um adeus!! \n"); // Mensagem de despedida
                return 0; // Encerra o programa com sucesso
                
            }
            break; // Break apenas por boa prática (não alcançado devido ao return)

            default:{ // Caso digite qualquer número fora de 0-4
                printf("Erro, opção não identificada!!! \n");
                printf("Tente novamente!! \n"); 
            }
            break; // Sai do default
        }
    } while (opcoes != 0); // Continua repetindo enquanto a opção não for 0
}