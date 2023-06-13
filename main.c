#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int codigo;
    char descricao[50];
    int qtd_estoque;
    float preco;
} Produto;

typedef struct {
    Produto *produtos;
    int *quantidades;
    int quantidade;
    int tamanho;
} Loja;

typedef struct {
    int codigo;
    Produto produto;
    int quantidade;
} ItemCarrinho;

typedef struct {
    int codigo;
    ItemCarrinho *itens;
    int quantidade;
    int tamanho;
    float totalCompra;
} Pedido;

void inicializarLoja(Loja *loja, int tamanhoInicial) {
    loja->produtos = (Produto*)malloc(tamanhoInicial * sizeof(Produto));
    loja->quantidades = (int*)malloc(tamanhoInicial * sizeof(int));
    loja->quantidade = 0;
    loja->tamanho = tamanhoInicial;
}

void redimensionarLoja(Loja *loja) {
    int novoTamanho = loja->tamanho * 2;
    loja->produtos = (Produto*)realloc(loja->produtos, novoTamanho * sizeof(Produto));
    loja->quantidades = (int*)realloc(loja->quantidades, novoTamanho * sizeof(int));
    loja->tamanho = novoTamanho;
}

void cadastrarProduto(Loja *loja) {
    if (loja->quantidade == loja->tamanho) {
        redimensionarLoja(loja);
    }

    Produto novoProduto;
    printf("----------------------\n");
    printf("\nCodigo: ");
    scanf("%d", &novoProduto.codigo);
    printf("Descricao: ");
    scanf(" %[^\n]", novoProduto.descricao);
    printf("Quantidade em estoque: ");
    scanf("%d", &novoProduto.qtd_estoque);
    printf("Preco: ");
    scanf("%f", &novoProduto.preco);

    loja->produtos[loja->quantidade] = novoProduto;
    loja->quantidades[loja->quantidade] = novoProduto.qtd_estoque;
    loja->quantidade++;
    system("cls");

    printf("Produto cadastrado com sucesso!\n");

}

void imprimirProduto(Produto produto) {
    printf("Codigo: %d\n", produto.codigo);
    printf("Descricao: %s\n", produto.descricao);
    printf("Quantidade em estoque: %d\n", produto.qtd_estoque);
    printf("Preco: %.2f\n", produto.preco);
}

void alterarProduto(Loja *loja) {
    int codigo;
    printf("Digite o codigo do produto a ser alterado: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < loja->quantidade; i++) {
        if (loja->produtos[i].codigo == codigo) {
            Produto produto;
            printf("Novo codigo: ");
            scanf("%d", &produto.codigo);
            printf("Nova descricao: ");
            scanf(" %[^\n]", produto.descricao);
            printf("Nova quantidade em estoque: ");
            scanf("%d", &produto.qtd_estoque);
            printf("Novo preco: ");
            scanf("%f", &produto.preco);

            loja->produtos[i] = produto;
            loja->quantidades[i] = produto.qtd_estoque;
            
            system("cls");
            printf("Produto alterado com sucesso!\n");
            return;
        }
    }
    system("cls");
    printf("Produto nao encontrado.\n");
}

void excluirProduto(Loja *loja) {
    int codigo;
    printf("Digite o codigo do produto a ser excluido: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < loja->quantidade; i++) {
        if (loja->produtos[i].codigo == codigo) {
            // Mover o último produto para a posição atual
            loja->produtos[i] = loja->produtos[loja->quantidade - 1];
            loja->quantidades[i] = loja->quantidades[loja->quantidade - 1];
            loja->quantidade--;
            system("cls");

            printf("Produto excluido com sucesso!\n");
            return;
        }
    }
    system("cls");
    printf("Produto nao encontrado.\n");
}

void consultarProduto(Loja loja) {
    int codigo;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < loja.quantidade; i++) {
        if (loja.produtos[i].codigo == codigo) {
            imprimirProduto(loja.produtos[i]);
            return;
        }
    }
    system("cls");
    printf("Produto nao encontrado.\n");
}

void listarProdutos(Loja loja) {
    int i;
    for (i = 0; i < loja.quantidade; i++) {
        imprimirProduto(loja.produtos[i]);
        printf("----------------------\n");
    }
}

void gerenciarProdutos(Loja *loja) {
    int opcao;
    do {
        printf("\n----- Menu Gerenciar Produtos -----\n");
        printf("1) Incluir\n");
        printf("2) Alterar\n");
        printf("3) Excluir\n");
        printf("4) Consultar\n");
        printf("5) Listar\n");
        printf("6) Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(loja);
                break;
            case 2:
                alterarProduto(loja);
                break;
            case 3:
                excluirProduto(loja);
                break;
            case 4:
                consultarProduto(*loja);
                break;
            case 5:
            	system("cls");
                listarProdutos(*loja);
                break;
            case 6:
            	system("cls");
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
            	system("cls");
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);
}

void adicionarProdutoCarrinho(Pedido *pedido, Loja loja) {
    int codigo;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < loja.quantidade; i++) {
        if (loja.produtos[i].codigo == codigo) {
            int quantidade;
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidade);

            if (quantidade <= 0 || quantidade > loja.quantidades[i]) {
                printf("Quantidade invalida. Verifique o estoque.\n");
                return;
            }

            ItemCarrinho item;
            item.codigo = codigo;
            item.produto = loja.produtos[i];
            item.quantidade = quantidade;

            pedido->itens[pedido->quantidade] = item;
            pedido->quantidade++;
            pedido->totalCompra += item.produto.preco * quantidade;

            // Atualizar a quantidade em estoque do produto
            loja.quantidades[i] -= quantidade;
            
    		system("cls");
            printf("Produto adicionado ao carrinho com sucesso!\n");
            return;
        }
    }
    system("cls");
    printf("Produto nao encontrado.\n");
}

void exibirCarrinho(Pedido pedido) {
	system("cls");
    printf("\n----- Carrinho de Compras -----\n");

    if (pedido.quantidade == 0) {
        printf("Carrinho vazio.\n");
    } else {
        int i;
        for (i = 0; i < pedido.quantidade; i++) {
            ItemCarrinho item = pedido.itens[i];
            printf("Codigo: %d\n", item.produto.codigo);
            printf("Descricao: %s\n", item.produto.descricao);
            printf("Quantidade: %d\n", item.quantidade);
            printf("Preco: %.2f\n", item.produto.preco);
            printf("----------------------\n");
        }
        printf("Total da compra: %.2f\n", pedido.totalCompra);
    }
}

void excluirProdutoCarrinho(Pedido *pedido, Loja *loja) {
    int codigo;
    printf("Digite o codigo do produto a ser excluido: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < pedido->quantidade; i++) {
        if (pedido->itens[i].codigo == codigo) {
            ItemCarrinho item = pedido->itens[i];

            // Mover o último item do carrinho para a posição atual
            pedido->itens[i] = pedido->itens[pedido->quantidade - 1];
            pedido->quantidade--;
            pedido->totalCompra -= item.produto.preco * item.quantidade;

            // Atualizar a quantidade em estoque do produto
            int j;
            for (j = 0; j < loja->quantidade; j++) {
                if (loja->produtos[j].codigo == item.codigo) {
                    loja->quantidades[j] += item.quantidade;
                    break;
                }
            }
            
			system("cls");
            printf("Produto excluido do carrinho com sucesso!\n");
            return;
        }
    }   
	system("cls");
    printf("Produto nao encontrado no carrinho.\n");
}

void alterarQuantidadeCarrinho(Pedido *pedido, Loja *loja) {
    int codigo;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    int i;
    for (i = 0; i < pedido->quantidade; i++) {
        if (pedido->itens[i].codigo == codigo) {
            int novaQuantidade;
            printf("Digite a nova quantidade: ");
            scanf("%d", &novaQuantidade);

            if (novaQuantidade <= 0 || novaQuantidade > loja->quantidades[i]) {
            	system("cls");
                printf("Quantidade invalida. Verifique o estoque.\n");
                return;
            }

            ItemCarrinho item = pedido->itens[i];
            pedido->totalCompra -= item.produto.preco * item.quantidade;
            pedido->totalCompra += item.produto.preco * novaQuantidade;
            pedido->itens[i].quantidade = novaQuantidade;

            // Atualizar a quantidade em estoque do produto
            loja->quantidades[i] += item.quantidade - novaQuantidade;
            
			system("cls");
            printf("Quantidade do produto no carrinho alterada com sucesso!\n");
            return;
        }
    }
	system("cls");
    printf("Produto nao encontrado no carrinho.\n");
}

void esvaziarCarrinho(Pedido *pedido, Loja *loja) {
    if (pedido->quantidade == 0) {
    	system("cls");
        printf("Carrinho ja esta vazio.\n");
        return;
    }

    int i;
    for (i = 0; i < pedido->quantidade; i++) {
        ItemCarrinho item = pedido->itens[i];

        // Atualizar a quantidade em estoque do produto
        int j;
        for (j = 0; j < loja->quantidade; j++) {
            if (loja->produtos[j].codigo == item.codigo) {
                loja->quantidades[j] += item.quantidade;
                break;
            }
        }
    }

    pedido->quantidade = 0;
    pedido->totalCompra = 0;
    
	system("cls");
    printf("Carrinho esvaziado com sucesso!\n");
}

int gerarCodigoPedido() {
    srand(time(NULL));
    return rand();
}

void finalizarPedido(Pedido *pedido, Loja *loja) {
    if (pedido->quantidade == 0) {
    	system("cls");
        printf("Impossivel finalizar o pedido. Carrinho vazio.\n");
        return;
    }

    int codigoPedido = gerarCodigoPedido();
    system("cls");
    printf("Pedido finalizado! Codigo do pedido: %d\n", codigoPedido);

    // Deduzir a quantidade comprada do estoque da loja
    int i, j;
    for (i = 0; i < pedido->quantidade; i++) {
        ItemCarrinho item = pedido->itens[i];
        
        for (j = 0; j < loja->quantidade; j++) {
            if (loja->produtos[j].codigo == item.codigo) {
                if (loja->produtos[j].qtd_estoque < item.quantidade) {
                    printf("Quantidade insuficiente em estoque para o produto %d.\n", item.codigo);
                    continue;
                }
                
                loja->produtos[j].qtd_estoque -= item.quantidade;
                break;
            }
        }
    }

    pedido->quantidade = 0;
    pedido->totalCompra = 0;
}

void gerenciarPedido(Loja *loja) {
    Pedido pedido;
    pedido.itens = (ItemCarrinho*)malloc(loja->tamanho * sizeof(ItemCarrinho));
    pedido.quantidade = 0;
    pedido.tamanho = loja->tamanho;
    pedido.totalCompra = 0;

    int opcao;
    do {
        printf("\n----- Menu Gerenciar Pedido -----\n");
        printf("1) Adicionar produto\n");
        printf("2) Consultar Carrinho de Compras\n");
        printf("3) Excluir produto do carrinho\n");
        printf("4) Alterar quantidade do produto no carrinho\n");
        printf("5) Esvaziar Carrinho de Compras\n");
        printf("6) Finalizar Pedido\n");
        printf("7) Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        

        switch (opcao) {
            case 1:
                adicionarProdutoCarrinho(&pedido, *loja);
                break;
            case 2:
                exibirCarrinho(pedido);
                break;
            case 3:
                excluirProdutoCarrinho(&pedido, loja);
                break;
            case 4:
                alterarQuantidadeCarrinho(&pedido, loja);
                break;
            case 5:
                esvaziarCarrinho(&pedido, loja);
                break;
            case 6:
                finalizarPedido(&pedido, loja);
                break;
            case 7:
            	system("cls");
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
            	system("cls");
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 7);

    free(pedido.itens);
}

void menuPrincipal(Loja *loja) {
    int opcao;
    do {
        printf("\n----- Menu Principal -----\n");
        printf("1) Gerenciar Produtos\n");
        printf("2) Gerenciar Pedido\n");
        printf("3) Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        system("cls");

        switch (opcao) {
            case 1:
                gerenciarProdutos(loja);
                break;
            case 2:
                gerenciarPedido(loja);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);
}

int main() {
    Loja loja;
    inicializarLoja(&loja, 10);

    menuPrincipal(&loja);

    free(loja.produtos);
    free(loja.quantidades);

    return 0; 
}

