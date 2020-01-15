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
    int id_da_conta;
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

float ler_numero(int, int);
char menu_principal(void);
char submenu_contas(void);
char submenu_servicos(void);
char submenu_projeto(void);
void ler_dados_conta(conta[], int);
void mostrar_dados_conta(conta[], int);
void ler_dados_servico(servico[], int);
void mostrar_dados_servico(servico[], int);
void ler_dados_projeto(projeto[],int);
void mostrar_dados_projeto(projeto[],int);
int voltar_atras(void);
char confirmar_saida(void);

int main() {
    char op;
    char resposta;
    conta vetor_conta[NUM_MAX_CONTAS];
    int num_contas = 0;
    servico vetor_servico[NUM_MAX_SERVICOS];
    int num_servicos = 0;
    int num_projetos = 0;
    projeto vetor_projeto[NUM_MAX_PROJETOS];

    do {
        op = menu_principal();

        switch(op) {
        case '1':
            printf("\n\tSUB-MENU - CONTAS\n");
            char submenu_conta_op;
            char resposta_submenu_conta;

            do {
                submenu_conta_op = submenu_contas();

                switch(submenu_conta_op) {
                case '1':
                    printf("\n\tRegistar contas\n");

                    ler_dados_conta(vetor_conta, num_contas);
                    num_contas++;

                    break;
                case '2':
                    printf("\n\tConsultar contas\n");

                    mostrar_dados_conta(vetor_conta, num_contas);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");
                    //menu_principal();
                    break;
                case '0':
                    resposta_submenu_conta = confirmar_saida();

                    if (resposta_submenu_conta == 'S' || resposta_submenu_conta == 's'){
                        printf("\nA sair... \n");
                        return 0;
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_conta_op != '0');

            break;
        case '2':
            printf("\n\tSUB-MENU - PROJETOS\n");
            char submenu_projeto_op;
            char resposta_submenu_projeto;

            do {
                submenu_projeto_op = submenu_projeto();

                switch(submenu_projeto_op) {
                case '1':
                    printf("\n\tRegistar projetos\n");

                    ler_dados_projeto(vetor_projeto, num_projetos);
                    num_projetos++;

                    break;
                case '2':
                    printf("\n\tConsultar projetos\n");

                   mostrar_dados_projeto(vetor_projeto,num_projetos);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");
                    //menu_principal();
                    break;
                case '0':
                    resposta_submenu_projeto = confirmar_saida();

                    if (resposta_submenu_conta == 'S' || resposta_submenu_conta == 's'){
                        printf("\nA sair... \n");
                        return 0;
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_conta_op != '0');

            break;
        case '3':
            printf("\n\tSUB-MENU - SERVICOS\n");
            char submenu_servico_op;
            char resposta_submenu_servico;

            do {
                submenu_servico_op = submenu_servicos();

                switch(submenu_servico_op) {
                case '1':
                    printf("\n\tRegistar servicos\n");

                    ler_dados_servico(vetor_servico, num_servicos);
                    num_servicos++;

                    break;
                case '2':
                    printf("\n\tConsultar consultar\n");

                    mostrar_dados_servico(vetor_servico, num_servicos);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");

                    break;
                case '0':
                    resposta_submenu_servico = confirmar_saida();

                    if (resposta_submenu_servico == 'S' || resposta_submenu_servico == 's'){
                        printf("\nA sair... \n");
                        return 0;
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_servico_op != '0');

            break;
        case '4':
            printf("\n\tSUB-MENU - CUSTOS\n");

            break;
        case '5':
            printf("\n\tEstatisticas\n");
            break;
        case '6':
            printf("\n\tGravar dados\n");
            //gravar_dados_ficheiro(estudantes, num_estudantes);
            break;
        case '7':
            printf("\n\tLer dados\n");
            //num_estudantes = ler_dados_ficheiro(estudantes);
            break;
        case '0':
            resposta = confirmar_saida();

            if (resposta == 'S' || resposta == 's'){
                printf("A sair... \n");
                return 0;
            }

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
        printf(" 1 - CONTAS\n");
        printf(" 2 - PROJETOS\n");
        printf(" 3 - SERVICOS\n");
        printf(" 4 - CUSTOS\n");
        printf(" 5 - ESTATISTICAS\n");
        printf(" 6 - GRAVAR EM FICHEIRO\n");
        printf(" 7 - LER FICHEIRO\n");
        printf(" 0 - Sair\n");
        printf("\n\tSelecione uma opcao -> ");
        scanf(" %c", &op);
    } while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '7' && op != '0');

    return op;
}

char submenu_contas(void) {
    char op;

    do {
            printf("|------- Menu de Opcoes --------|\n");
            printf("|*******************************|\n");
            printf("|1 - Registar dados de contas   |\n");
            printf("|2 - Mostrar dados de contas    |\n");
            printf("|3 - Voltar atras               |\n");
            printf("|0 - Sair                       |\n");
            printf("|------------------------------ |\n");
        scanf(" %c", &op);
    } while(op != '1' && op != '2' && op != '3' && op != '0');

    return op;
}

char submenu_servicos(void) {
    char op;

    do {
            printf("|-------- Menu de Opcoes --------|\n");
            printf("|******************************* |\n");
            printf("|1 - Registar servico            |\n");
            printf("|2 - Mostrar servicos registrados|\n");
            printf("|3 - Voltar atras                |\n");
            printf("|0 - Sair                        |\n");
            printf("|--------------------------------|\n");
        scanf(" %c", &op);
    } while(op != '1' && op != '2' && op != '3' && op != '0');

    return op;
}

char submenu_projeto(void) {
    char op;

        do {
            printf("|------- Menu de Opcoes --------|\n");
            printf("|*******************************|\n");
            printf("|1 - Registar dados do projeto  |\n");
            printf("|2 - Mostrar dados do projeto   |\n");
            printf("|3 - Voltar atras               |\n");
            printf("|0 - Sair                       |\n");
            printf("|------------------------------ |\n");
            printf("\n\tSelecione uma opcao -> ");
            scanf(" %c", &op);
        } while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '0');

	return op;
}

float ler_numero(int lim_inf, int lim_sup) {
    float num;

    do {
        scanf("%f", &num);
    } while(num < lim_inf || num > lim_sup);

    return num;
}

void ler_dados_conta(conta c_vetor[], int c_numero) {
    c_vetor[c_numero].id_conta = c_numero;

    printf("\nIntroduza a designacao da conta: ");
    scanf("%s", c_vetor[c_numero].designacao_conta);

    printf("\nIntroduza a plataforma do fornecedor de servicos: ");
    scanf("%s", c_vetor[c_numero].plataforma_fornecedor_servicos);

    printf("\nIntroduza a organizacao: ");
    scanf("%s", c_vetor[c_numero].organizacao);

    printf("\nIntroduza o dominio: ");
    scanf("%s", c_vetor[c_numero].dominio);

    printf("\nIntroduza o saldo da conta: ");
    c_vetor[c_numero].saldo_conta = ler_numero(0, 100000000);
}

void mostrar_dados_conta(conta c_vetor[], int c_numero) {
    for(int i = 0; i<c_numero;i++) {
        printf("\n\nID da conta: %d", c_vetor[i].id_conta);
        printf("\nDesignacao de conta: %s", c_vetor[i].designacao_conta);
        printf("\nPlataforma: %s", c_vetor[i].plataforma_fornecedor_servicos);
        printf("\nOrganizacao: %s", c_vetor[i].organizacao);
        printf("\nDominio: %s", c_vetor[i].dominio);
        printf("\nSaldo da conta: %.2f\n", c_vetor[i].saldo_conta);
    }
}

/*

typedef struct {
    int id_servico;
    char designacao_servico[30];
    char tipo_servico[30];
    char unidade_medida[30];
    float custo_unidade;
} servico;

*/

void ler_dados_servico(servico s_vetor[], int s_numero) {
    s_vetor[s_numero].id_servico = s_numero;

    printf("\nIntroduza a designacao do servico: ");
    scanf("%s", s_vetor[s_numero].designacao_servico);

    printf("\nIntroduza o tipo de servico: ");
    scanf("%s", s_vetor[s_numero].tipo_servico);

    printf("\nIntroduza a unidade de medida: ");
    scanf("%s", s_vetor[s_numero].unidade_medida);

    printf("\nIntroduza o custo por unidade: ");
    s_vetor[s_numero].custo_unidade = ler_numero(0, 100000000);
}

void mostrar_dados_servico(servico s_vetor[], int s_numero) {
    for(int i = 0; i<s_numero;i++) {
        printf("\n\nID do servico: %d", s_vetor[i].id_servico);
        printf("\nDesignacao do servico: %s", s_vetor[i].designacao_servico);
        printf("\nTipo de servico: %s", s_vetor[i].tipo_servico);
        printf("\nUnidade de medida: %s", s_vetor[i].unidade_medida);
        printf("\nCusto por unidade: %.2f\n", s_vetor[i].custo_unidade);
    }
}

void ler_dados_projeto(projeto p_vetor[], int p_numero){

    int id_conta;

    printf("\nIndique o numero da conta qual o projeto esta associado a: ");
    id_conta = ler_numero(0,5);
    p_vetor[p_numero].id_da_conta = id_conta;

    printf("\nIndique o nome do projeto: ");
    scanf("%s", p_vetor[p_numero].nome_projeto);

    printf("\nIndique a divisao/equipa: ");
    scanf("%s", p_vetor[p_numero].equipa_projeto);

    printf("\nIndique a data: ");
    printf("\n*>.> Exemplo 12022020, 12=dia, 02=mes, 2020=ano <.<*");
   // p_vetor.data_projeto = ler_numero(01012019,32139999); //tipo aqui a data mais pequena e a maior possivel neste ano
}

void mostrar_dados_projeto(projeto p_vetor[], int p_numero) {
    for(int i = 0; i<p_numero;i++) {
        printf("\n\nID do projeto: %d", p_vetor[i].id_projeto);
        printf("\nConta Associada: %d", p_vetor[i].id_da_conta);
        printf("\nNome do projeto: %s", p_vetor[i].nome_projeto);
        printf("\nDivisao/Equipa: %s", p_vetor[i].equipa_projeto);
        // printf("\nData: %s", p_vetor[i].data_projeto); ignorei para testes
        printf("\n\n\n");
    }
}

char confirmar_saida(void) {
    char resposta;

    printf("\nQuer mesmo sair? (S/N): ");
    scanf(" %c", &resposta);

    return resposta;
}
