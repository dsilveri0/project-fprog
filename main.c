/**************************************************
###################################################
|                                                 |
|      Projeto de Fundamentos de Programação      |
|       de David Silvério e Vladyslav Bobko       |
|                                                 |
###################################################
**************************************************/

#include <stdio.h>
#include <stdlib.h>


#define NUM_MAX_CONTAS 5
#define NUM_MAX_PROJETOS 20
#define NUM_MAX_SERVICOS 50
#define NUM_MAX_CUSTOS 200

typedef struct {
    int id_conta;
    char designacao_conta[30];
    char plataforma_fornecedor_servicos[30];
    char organizacao[30];
    char dominio[30];
    float saldo_conta;
} conta;

typedef struct {
    int id_projeto;
    conta id_da_conta;
    char nome_projeto[30];
    char equipa_projeto[30];
    float data_projeto;
} projeto;

typedef struct {
    int id_servico;
    char designacao_servico[30];
    char tipo_servico[30];
    char unidade_medida[30];
    float custo_unidade;
} servico;

typedef struct {
    servico id_do_servico;
    projeto id_do_projeto;
    float datahora_inicio_utilizacao;
    float datahora_fim_utilizacao;
    float quantidade;
    float valor_pago;
} custo;

typedef struct {
   conta d_conta;
   projeto d_projeto;
   servico d_servico;
   custo d_custo;
} dados;

int ler_numero(int, int);
char menu_principal(void);
//char sub_menu(char);
int confirmar_saida(void);
int voltar_atras(void);

//void gravar_dados_ficheiro(dados[], int);
//int ler_dados_ficheiro(dados[]);

void mostrar_dados(conta[], int);
void ler_dados(conta[], int);

int main() {
    int num_contas = 0;
    char op;

    conta conta[NUM_MAX_CONTAS];
    //projeto projeto[NUM_MAX_PROJETOS];
    //servico servico[NUM_MAX_SERVICOS];
    //custo custo[NUM_MAX_CUSTOS];

    do {
	    op = menu_principal();

	    switch(op) {
            case '1':
                printf("Contas\n");

                ler_dados(conta, num_contas);
                num_contas++;

                break;
            case '2':
                printf("\n\tMostrar Contas\n");

                mostrar_dados(conta, num_contas);

                break;
            case '3':
                printf("\n\tServicos\n");

                break;
            case '4':
                printf("\n\tEstatisticas\n");

                break;
            case '5':
                printf("\n\tGravar dados\n");

                //gravar_dados_ficheiro(estudantes, num_estudantes);

                break;
            case '6':
                printf("\n\tLer dados\n");

                //num_estudantes = ler_dados_ficheiro(estudantes);

                break;
            case '0':
                confirmar_saida();

                break;
            default:
                printf("Introduza uma opcao valida!");
       	    }

    } while(op != '0');


    return 0;
}

char menu_principal(void) {
    char op;

        do {
            printf("\n\t----- Menu de Opcoes -----\n\n");
            printf(" 1 - Registar dados de contas\n");
            printf(" 2 - Mostrar dados de contas\n");
            /*
            printf(" 3 - Alterar dados dos estudantes\n");
            printf(" 4 - Estatisticas\n");
            printf(" 5 - Gravar dados no ficheiro binario\n");
            printf(" 6 - Ler dados do ficheiro binario\n");
            */
            printf(" 0 - Sair\n");
            printf("\n\tSelecione uma opcao -> ");
            scanf(" %c", &op);
        } while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '0');

	return op;

}

int ler_numero(int lim_inf, int lim_sup) {
    int num;

    do {
	scanf("%d", &num);
    } while(num < lim_inf || num > lim_sup);

    return num;
}


void ler_dados(conta d_contas[], int num_contas) {

    printf("\nIntroduza o ID de conta: ");
    d_contas[0].id_conta = ler_numero(1, 5000);

    printf("\nIndique a designacao da conta: ");
    scanf("%s", d_contas[0].designacao_conta);

    printf("\nIndique a plataforma: ");
    scanf("%s", d_contas[0].plataforma_fornecedor_servicos);

    printf("\nIndique a organizacao: ");
    scanf("%s", d_contas[0].organizacao);

    printf("\nIndique o dominio: ");
    scanf("%s", d_contas[0].dominio);

    printf("\nIntroduza o saldo de conta: ");
    d_contas[0].saldo_conta = ler_numero(0, 1000000000);

}

void mostrar_dados(conta d_contas[], int num_contas) {
    printf("\nid da conta: %d ", d_contas[0].id_conta);
    printf("\ndesignacao da conta: %s\n", d_contas[0].designacao_conta);
    printf("\nplataforma da conta: %s\n", d_contas[0].plataforma_fornecedor_servicos);
    printf("\norganizacao da conta: %s\n", d_contas[0].organizacao);
    printf("\ndominio da conta: %s\n", d_contas[0].dominio);
    printf("\nsaldo da conta: %.2f\n", d_contas[0].saldo_conta);
}

int confirmar_saida(void) {
    char resposta;

    printf("\nQuer mesmo sair? (S/N): ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's'){
        printf("A sair... \n");
        return 0;
    } else
        main();

    return 0;
}

/* void gravar_dados_ficheiro(t_aluno alunos[], int num_estudantes) {
    FILE *ficheiro;

    ficheiro = fopen("dados.dat", "wb");

    if (ficheiro == NULL) {
        printf("Impossivel criar ficheiro.");
    } else
        fwrite(&num_estudantes, sizeof(int), 1, ficheiro);
        fwrite(alunos, sizeof(t_aluno), num_estudantes, ficheiro);

    fclose(ficheiro);
}

int ler_dados_ficheiro(t_aluno alunos[]) {
    FILE *ficheiro;
    int numero_elementos;

    ficheiro = fopen("dados.dat", "rb");

    if (ficheiro == NULL) {
        printf("Impossivel abrir ficheiro.");
    } else

        //fseek(ficheiro, 0L, SEEK_END);
        //printf("\n%d\n", ftell(ficheiro));
        // Fazer divisão entre ftell e o sizeof do vetor alunos

        fread(&numero_elementos , sizeof(int), 1, ficheiro);
        fread(alunos, sizeof(t_aluno), numero_elementos, ficheiro);

        // fread, 1º parametro recebe & quando é uma variavel normal.
        //(não leva & quando é um vetor na posição 1 nem qunado é o terceiro parametro não leva &.

    fclose(ficheiro);

    return numero_elementos;
} */
