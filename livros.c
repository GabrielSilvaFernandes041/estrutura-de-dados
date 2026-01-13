#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 30

// Objeto de cadsatro 
typedef struct {
    char    nome[MAX_STRING];
    char    autor[MAX_STRING];
    char    editora[MAX_STRING];
    int     edisao;
    int     disponivel; // 1 - Disponivel | 0 - Indisponivel

} livros;

typedef struct{
    int livroID; // Id do livro emprestado

    char nomeusuario[MAX_STRING]; // Nome da pessoa que pegou o livro emprestado
} emprestimo;

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){

    livros      *biblioteca;
    emprestimo  *emprestimosLista;

    biblioteca          = (livros*) calloc (MAX_LIVROS, sizeof(livros));
    emprestimosLista    = (emprestimo*)malloc (MAX_EMPRESTIMOS * sizeof(emprestimo));    

    if (biblioteca == NULL || emprestimosLista == NULL){
        printf("Erro ao alocar memória!!");
        return 1;
    }

    // Mostra que as opções do programa
    int opcoes;
    int indexLivros         = 0;
    int totalEmprestimos    = 0;


    do {
    printf(" \n//------------------------- \n");
    printf("Bem vindo ao sistema de cadrasto de livros \n");
    printf("A baixo está como funciona o sistema \n");
    printf("1 - Cadastrar um novo livro \n");
    printf("2 - Mostra todos os livros cadastrados \n");
    printf("3 - Sistema de emprestimo de livros \n");
    printf("4 - Mostra livros emprestados \n");
    printf("0 - Sair do Sistema \n");
    printf("Digie sua opção: ");
    scanf("%d", &opcoes);
    printf("//------------------------- \n");

    limparBuffer();

   
        switch (opcoes)
        {

            case(1):{ // Cadastra um novo livro
                printf("\n //------------------------- \n");

                if (indexLivros < MAX_LIVROS){
                    
                    printf("Cadastrando livro %d de %d \n", indexLivros + 1, MAX_LIVROS);

                    printf("Livro: ");
                    fgets(biblioteca[indexLivros].nome, MAX_STRING, stdin);
                    biblioteca[indexLivros].nome[strcspn(biblioteca[indexLivros].nome, "\n")] = '\0';
                    
                    printf("Autor: ");
                    fgets(biblioteca[indexLivros].autor, MAX_STRING, stdin);
                    biblioteca[indexLivros].autor[strcspn(biblioteca[indexLivros].autor, "\n")] = '\0';
                    
                    printf("Editora: ");
                    fgets(biblioteca[indexLivros].editora, MAX_STRING, stdin);
                    biblioteca[indexLivros].editora[strcspn(biblioteca[indexLivros].editora, "\n")] = '\0';

                    biblioteca[indexLivros].disponivel = 1; // Define o livro como disponivel

                    printf("Edição: ");
                    scanf("%d", &biblioteca[indexLivros].edisao);
                    
                    

                    limparBuffer();

                    indexLivros ++;
                } else {
                    printf("Maximo de livros cadastrado!!");
                }

                printf("\n //------------------------- \n");
            }break;
            
            case(2):{ // Mostra todos os livros cadastrados
                printf(" \n//------------------------- \n");
                if (indexLivros != 0){
                    printf("Livros cadastrados \n");

                    for (int i = 0; i < indexLivros; i++){

                        printf("\n");

                        printf("Livro: %s \n",     biblioteca[i].nome);
                        printf("Autor: %s \n",     biblioteca[i].autor);
                        printf("Editora: %s \n",    biblioteca[i].editora);
                        printf("Edição: %d \n",    biblioteca[i].edisao);
                        
                        printf("\n");
                    }
                }
                else { printf("Nenhum livro cadastrado!! \n"); }

                printf("//------------------------- \n");
                printf("\n");
            }break;

            case(3):{ // Sistema de emprestimo de livros
                printf(" \n//------------------------- \n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS){
                    printf("Limite de emprestimos atingido!! \n");
                    break;
                } else {
                    if (indexLivros > 0) { printf("Livros disponiveis: \n"); }
                    int disponiveis = 0;


                    for (int i = 0; i < indexLivros; i++){
                        if (biblioteca[i].disponivel == 1){
                            printf("ID: %d - Livro: %s \n", i, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0){
                        printf("Nenhum livro disponivel para emprestimo!! \n");
                    } else {
                        int idLivro;

                        printf("Quem deseja pegar o livro emprestado?");
                        fgets(emprestimosLista[totalEmprestimos].nomeusuario, MAX_STRING, stdin);
                        emprestimosLista[totalEmprestimos].nomeusuario[strcspn(emprestimosLista[totalEmprestimos].nomeusuario, "\n")] = '\0';

                        printf("Digite o ID do livro que deseja emprestar: ");
                        scanf("%d", &idLivro);

                        limparBuffer();

                        // Passando o parametro do livro emprestado para o objeto do usuario no qual pegou emprestado
                        emprestimosLista[totalEmprestimos].livroID = idLivro; // Passa o ID do livro no qual pegou emprestado
                    

                        if (idLivro < 0 || idLivro >= indexLivros){
                            printf("ID inválido!! \n");
                        } else {
                            if (biblioteca[idLivro].disponivel == 1){
                                biblioteca[idLivro].disponivel = 0;
                                totalEmprestimos++;
                                printf("Emprestimo realizado com sucesso!! \n");
                            } else {
                                printf("ID invalido ou livro indisponivel!! \n");
                            }
                        }
                    }
                }   
<<<<<<< HEAD
                
=======

>>>>>>> 0337a46a1a1279f0a873e3f695c7e98260951fbd
                printf("//------------------------- \n");

            }break;

            case(4):{ // Mostra todos os emprestimos realizados
                printf(" \n//------------------------- \n");
                
                if (totalEmprestimos == 0){
                    printf("Nenhum Livro emprestado!!! \n");

                    printf("//------------------------- \n");
                    break;
                } else if (totalEmprestimos > 0){
                    printf("Livros emprestados \n");

                    // Loop ue mostra todos os livros emprestados
                    for (int i = 0; i < totalEmprestimos; i++){ // Quantia de livros emprestados
                        
                        int idLivro = emprestimosLista[i].livroID;

                        printf("Usuário - %s | Livro - %s \n",
                            emprestimosLista[i].nomeusuario,
                            biblioteca[idLivro].nome
                        ); 
                    }
                }

                printf("//------------------------- \n");

            }break;

            case(0):{ // Sair do sistema

                // Retirar espaço alocado de memoria caso saiam do sistema 
                free(biblioteca);
                free(emprestimosLista);

                
                printf("Memoria liberada!! \n");

                printf("Nunca é um adeus!! \n");
                return 0;
                
            }
            break;

            default:{
                printf("Erro, opção não identificada!!! \n");
                printf("Tente novamente!! \n"); 
            }
            break;
        }
    } while (opcoes != 0);
}