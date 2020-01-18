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
#include <string.h>
#include <ctype.h>

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
    int dia, mes, ano;
} data;

typedef struct {
    int id_projeto;
    int id_da_conta;
    char nome_projeto[30];
    char equipa_projeto[30];
    data data_projeto;
} projeto;

typedef struct {
    int id_servico;
    char designacao_servico[30];
    char tipo_servico[30];
    char unidade_medida[30];
    float custo_unidade;
} servico;

typedef struct {
    int hora, minuto;
} horario;

typedef struct {
    int id_do_servico;
    int id_do_projeto;
    data data_inicio;
    data data_fim;
    horario horario_inicio;
    horario horario_fim;
    float quantidade;
    float valor_pago;
} custo;

typedef struct {
    int id_do_projeto;
    int numero_servicos;
} sp_cont;

// Funções para menus e submenus
char menu_principal(void);
char submenu_contas(void);
char submenu_servicos(void);
char submenu_projetos(void);
char submenu_custos(void);

// Funções para ler e mostrar dados
void ler_dados_conta(conta[], int);
void mostrar_dados_conta(conta[], int);
void ler_dados_servico(servico[], int);
void mostrar_dados_servico(servico[], int);
void ler_dados_projeto(projeto[],int, conta[], int);
void mostrar_dados_projeto(projeto[],int);
void ler_dados_custo(custo[],int, servico[], int, projeto[], int, sp_cont[]);
void mostrar_dados_custo(custo[],int);

// Funções auxiliares
float ler_numero(int, int);
char confirmar_saida(void);
int procurar_projeto(projeto[], int, int);
int procurar_servico(servico[], int, int);
int procurar_conta(conta[], int, int);
int validar_data(int, int, int);
void servicos_projeto_cont(sp_cont[], int);

// Funções para Estatísticas
void projeto_mais_servicos(sp_cont[]);
void fornecedor_mais_projetos(projeto[], int);
void servicos_mais_utilizados(custo[], int, servico[], int);
void custo_total_projeto(custo[], int, projeto[], int);
void custo_tipo_servico(custo[], int, servico[], int, projeto[], int);

// Funções para ficheiros
void gravar_dados_ficheiro(conta[], int, projeto[], int, servico[], int, custo[], int, sp_cont[]);
void ler_dados_ficheiro(int[], conta[], projeto[], servico[], custo[], sp_cont[]);


int main() {
    char op;
    char resposta;
    conta vetor_conta[NUM_MAX_CONTAS];
    int num_contas = 0;
    servico vetor_servico[NUM_MAX_SERVICOS];
    int num_servicos = 0;
    projeto vetor_projeto[NUM_MAX_PROJETOS];
    int num_projetos = 0;
    custo vetor_custo[NUM_MAX_CUSTOS];
    int num_custos = 0;
    int vetores_cont[4];

    // Inicialização do vetor com valores -1 em todas as posições.
    sp_cont vetor_sp_cont[NUM_MAX_PROJETOS];
    for(int i = 0; i < NUM_MAX_PROJETOS; i++) {
        vetor_sp_cont[i].id_do_projeto = -1;
    }

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

                        if(num_contas < NUM_MAX_CONTAS) {
                            ler_dados_conta(vetor_conta, num_contas);
                            num_contas++;
                        } else {
                            printf("\nExcedeu o limite de contas!\n");
                        }

                    break;
                case '2':
                    printf("\n\tConsultar contas\n");

                    mostrar_dados_conta(vetor_conta, num_contas);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");

                    submenu_conta_op = '0';

                    break;
                case '0':
                    resposta_submenu_conta = confirmar_saida();

                    if (resposta_submenu_conta == 'S' || resposta_submenu_conta == 's'){
                        printf("\nA sair... \n");
                        op = '0';
                    } else {
                        op = ' ';
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
                submenu_projeto_op = submenu_projetos();

                switch(submenu_projeto_op) {
                case '1':
                    printf("\n\tRegistar projetos\n");

                    if(num_projetos < NUM_MAX_PROJETOS) {
                        ler_dados_projeto(vetor_projeto, num_projetos, vetor_conta, num_contas);
                        num_projetos++;
                    } else {
                        printf("\nExcedeu o limite de projetos!\n");
                    }

                    break;
                case '2':
                    printf("\n\tConsultar projetos\n");

                   mostrar_dados_projeto(vetor_projeto,num_projetos);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");

                    submenu_projeto_op = '0';

                    break;
                case '0':
                    resposta_submenu_projeto = confirmar_saida();

                    if (resposta_submenu_projeto == 'S' || resposta_submenu_projeto == 's'){
                        printf("\nA sair... \n");
                        op = '0';
                    } else {
                        op = ' ';
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_projeto_op != '0');

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

                    if(num_servicos < NUM_MAX_SERVICOS) {
                        ler_dados_servico(vetor_servico, num_servicos);
                        num_servicos++;
                    } else {
                        printf("\nExcedeu o limite de servicos!\n");
                    }

                    break;
                case '2':
                    printf("\n\tConsultar consultar\n");

                    mostrar_dados_servico(vetor_servico, num_servicos);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");

                    submenu_servico_op = '0';

                    break;
                case '0':
                    resposta_submenu_servico = confirmar_saida();

                    if (resposta_submenu_servico == 'S' || resposta_submenu_servico == 's'){
                        printf("\nA sair... \n");
                        op = '0';
                    } else {
                        op = ' ';
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_servico_op != '0');

            break;
        case '4':
            printf("\n\tSUB-MENU - CUSTOS\n");

            char submenu_custo_op;
            char resposta_submenu_custo;

            do {
                submenu_custo_op = submenu_custos();

                switch(submenu_custo_op) {
                case '1':
                    printf("\n\tRegistar custos\n");

                    if(num_custos < NUM_MAX_CUSTOS) {
                        ler_dados_custo(vetor_custo, num_custos, vetor_servico, num_servicos, vetor_projeto, num_projetos, vetor_sp_cont);
                        num_custos++;
                    } else {
                        printf("\nExcedeu o limite de custos!\n");
                    }

                    break;
                case '2':
                    printf("\n\tConsultar consultar\n");

                    mostrar_dados_custo(vetor_custo, num_custos);

                    break;
                case '3':
                    printf("\n\tVoltar atras\n");

                    submenu_custo_op = '0';

                    break;
                case '0':
                    resposta_submenu_custo = confirmar_saida();

                    if (resposta_submenu_custo == 'S' || resposta_submenu_custo == 's'){
                        printf("\nA sair... \n");
                        op = '0';
                    } else {
                        op = ' ';
                    }

                    break;
                default:
                    printf("\nIntroduza uma opcao valida!");
                }
            } while(submenu_custo_op != '0');

            break;
        case '5':
            printf("\nEstatisticas\n");

            printf("\nProjeto com maior numero de servicos: ");
            projeto_mais_servicos(vetor_sp_cont);

            break;
        case '6':
            printf("\nGravar dados\n");

            gravar_dados_ficheiro(vetor_conta, num_contas, vetor_projeto, num_projetos, vetor_servico, num_servicos, vetor_custo, num_custos, vetor_sp_cont);

            break;
        case '7':
            printf("\nLer dados\n");

            ler_dados_ficheiro(vetores_cont, vetor_conta, vetor_projeto, vetor_servico, vetor_custo, vetor_sp_cont);

            num_contas = vetores_cont[0];
            num_projetos = vetores_cont[1];
            num_servicos = vetores_cont[2];
            num_custos = vetores_cont[3];

            break;
        case '0':
            resposta = confirmar_saida();

            if (resposta == 'S' || resposta == 's'){
                printf("A sair... \n");
                op = '0';
            } else {
                op = ' ';
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
        printf(" 0 - SAIR\n");
        printf("\n\tSelecione uma opcao -> ");
        scanf(" %c", &op);
    } while(op < '0' && op > '7');

    return op;
}

char submenu_contas(void) {
    char op;

    do {
        printf("\n|*******************************|\n");
        printf("|1 - Registar dados de contas   |\n");
        printf("|2 - Mostrar dados de contas    |\n");
        printf("|3 - Voltar atras               |\n");
        printf("|0 - Sair                       |\n");
        printf("|------------------------------ |\n");
        scanf(" %c", &op);
    } while(op < '0' && op > '3');

    return op;
}

char submenu_servicos(void) {
    char op;

    do {
        printf("\n|******************************* |\n");
        printf("|1 - Registar servico            |\n");
        printf("|2 - Mostrar servicos registrados|\n");
        printf("|3 - Voltar atras                |\n");
        printf("|0 - Sair                        |\n");
        printf("|--------------------------------|\n");
        scanf(" %c", &op);
    } while(op < '0' && op > '3');

    return op;
}

char submenu_projetos(void) {
    char op;
    do {
        printf("\n|*******************************|\n");
        printf("|1 - Registar dados do projeto  |\n");
        printf("|2 - Mostrar dados do projeto   |\n");
        printf("|3 - Voltar atras               |\n");
        printf("|0 - Sair                       |\n");
        printf("|------------------------------ |\n");
        printf("\n\tSelecione uma opcao -> ");
        scanf(" %c", &op);
    } while(op < '0' && op > '3');

    return op;
}

char submenu_custos(void) {
    char op;
    do {
        printf("\n|*******************************|\n");
        printf("|1 - Registar dados de custos   |\n");
        printf("|2 - Mostrar dados de custos    |\n");
        printf("|3 - Voltar atras               |\n");
        printf("|0 - Sair                       |\n");
        printf("|------------------------------ |\n");
        printf("\n\tSelecione uma opcao -> ");
        scanf(" %c", &op);
    } while(op < '0' && op > '3');

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
    scanf(" %30[^\n]", c_vetor[c_numero].designacao_conta);

    printf("\nIntroduza a plataforma do fornecedor de servicos: ");
    scanf(" %30[^\n]", c_vetor[c_numero].plataforma_fornecedor_servicos);

    printf("\nIntroduza a organizacao: ");
    scanf(" %30[^\n]", c_vetor[c_numero].organizacao);

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
        printf("\nSaldo da conta: %.2f $\n", c_vetor[i].saldo_conta);
    }
}

void ler_dados_servico(servico s_vetor[], int s_numero) {
    char tipo_de_servico[3][30] = {{"armazenamento"}, {"processamento"}, {"extras"}};
    char unidade_de_medida[3][30] = {{"gbyte"}, {"hora"}, {"segundo"}};
    char resposta_servico[30];
    char resposta_unidade[30];
    int resultado_servico = 0;
    int resultado_unidade = 0;

    s_vetor[s_numero].id_servico = s_numero;

    printf("\nIntroduza a designacao do servico: ");
    scanf(" %30[^\n]", s_vetor[s_numero].designacao_servico);

    do {
        printf("\nIntroduza o tipo de servico \n(Processamento, Armazenamento, Extras): ");
        scanf(" %30[^\n]", resposta_servico);

        for(int j = 0; j < 30; j++) {
            resposta_servico[j] = tolower(resposta_servico[j]);
        }

        for(int i = 0; i < 3; i++) {
            if(strcmp(tipo_de_servico[i], resposta_servico) == 0) {
                resultado_servico = 1;
                strcpy(s_vetor[s_numero].tipo_servico, resposta_servico);
            }
        }

        if(resultado_servico == 0) {
            printf("\nTipo de servico invalido!\n");
        }
    } while(resultado_servico != 1);

    do {
        printf("\nIntroduza a unidade de medida \n(Gbyte, Hora, Segundo): ");
        scanf(" %30[^\n]", resposta_unidade);

        for(int j = 0; j < 30; j++) {
            resposta_unidade[j] = tolower(resposta_unidade[j]);
        }

        for(int i = 0; i < 3; i++) {
            if(strcmp(unidade_de_medida[i], resposta_unidade) == 0) {
                resultado_unidade = 1;
                strcpy(s_vetor[s_numero].unidade_medida, resposta_unidade);
            }
        }

        if(resultado_unidade == 0) {
            printf("\nTipo de unidade invalida!\n");
        }
    } while(resultado_unidade != 1);

    printf("\nIntroduza o custo por unidade: ");
    s_vetor[s_numero].custo_unidade = ler_numero(0, 100000000);
}

void mostrar_dados_servico(servico s_vetor[], int s_numero) {
    for(int i = 0; i<s_numero;i++) {
        printf("\n\nID do servico: %d", s_vetor[i].id_servico);
        printf("\nDesignacao do servico: %s", s_vetor[i].designacao_servico);
        printf("\nTipo de servico: %s", s_vetor[i].tipo_servico);
        printf("\nUnidade de medida: %s", s_vetor[i].unidade_medida);
        printf("\nCusto por unidade: %.2f $\n", s_vetor[i].custo_unidade);
    }
}

void ler_dados_projeto(projeto p_vetor[], int p_numero, conta c_vetor[], int c_numero){
    int id_conta, flag = 0;

    p_vetor[p_numero].id_projeto = p_numero;

    printf("\nIndique o numero da conta qual o projeto esta associado a: ");

    id_conta = ler_numero(0,NUM_MAX_CONTAS);
    flag = procurar_conta(c_vetor, c_numero, id_conta);

    if(flag == 1) {
       for(int i = 0; i < c_numero; i++) {
           if(c_vetor[i].id_conta == id_conta) {
               p_vetor[p_numero].id_da_conta = id_conta;
           }
       }

       printf("\nIndique o nome do projeto: ");
       scanf(" %30[^\n]", p_vetor[p_numero].nome_projeto);

       printf("\nIndique a divisao/equipa: ");
       scanf(" %30[^\n]", p_vetor[p_numero].equipa_projeto);

       printf("\nIndique a data de criacao do projeto: \n");
       int validacao = 1;

       do {
           printf("Indique o dia: ");
           int data_dia = ler_numero(1, 31);

           printf("\nIndique o mes: ");
           int data_mes = ler_numero(1, 12);

           printf("\nIndique o ano: ");
           int data_ano = ler_numero(1970, 9999);

           validacao = validar_data(data_dia, data_mes, data_ano);

           if(validacao == 1) {
               p_vetor[p_numero].data_projeto.dia = data_dia;
               p_vetor[p_numero].data_projeto.mes = data_mes;
               p_vetor[p_numero].data_projeto.ano = data_ano;
           }

       } while (validacao != 1);
       
    } else if(flag == 0) {
        printf("\nConta não existente!\n");
    }
}

int validar_data(int dia, int mes, int ano) {
    int resposta = 1;

    if(mes == 2) {
        if(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)) {
            if(dia > 29) {
                printf("\nDia invalido! Ano bissexto!\n");
                resposta = 0;
            }
        } else {
            if(dia > 28) {
                printf("\nDia invalido! Mes de 28 dias!\n");
                resposta = 0;
            }
        }
    } else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if(dia > 30) {
            printf("\nDia invalido! Mes de 30 dias!\n");
            resposta = 0;
        }
    }

    return resposta;
}

void mostrar_dados_projeto(projeto p_vetor[], int p_numero) {
    for(int i = 0; i<p_numero;i++) {
        printf("\n\nID do projeto: %d", p_vetor[i].id_projeto);
        printf("\nConta Associada: %d", p_vetor[i].id_da_conta);
        printf("\nNome do projeto: %s", p_vetor[i].nome_projeto);
        printf("\nDivisao/Equipa: %s", p_vetor[i].equipa_projeto);
        printf("\nData de criação do projeto: %d-%d-%d\n", p_vetor[i].data_projeto.dia, p_vetor[i].data_projeto.mes, p_vetor[i].data_projeto.ano);
    }
}

void ler_dados_custo(custo custo_vetor[], int custo_numero, servico s_vetor[], int s_numero, projeto p_vetor[], int p_numero, sp_cont vsp_cont[]) {
    int id_projeto, id_servico, flag_p, flag_s = 0;
    int custo_unidade_servico;

    printf("\nIntroduza o ID do serviço associado: ");

    id_servico = ler_numero(0, NUM_MAX_SERVICOS);
    flag_s = procurar_servico(s_vetor, s_numero, id_servico);

    if(flag_s == 1) {
        for(int i = 0; i < s_numero; i++) {
            if(s_vetor[i].id_servico == id_servico) {
                custo_vetor[custo_numero].id_do_servico = id_servico;
                custo_unidade_servico = s_vetor[i].custo_unidade;
            }
        }

        printf("\nIntroduza o ID do projeto associado: ");

        id_projeto = ler_numero(0, NUM_MAX_PROJETOS);
        flag_p = procurar_projeto(p_vetor, p_numero, id_projeto);

        if(flag_p == 1) {
            for(int j = 0; j < p_numero; j++) {
                if(p_vetor[j].id_projeto == id_projeto) {
                    custo_vetor[custo_numero].id_do_projeto = id_projeto;
                    servicos_projeto_cont(vsp_cont, id_projeto);
                }
            }

            int validacao_data_inicio = 1;

            do {
                printf("\nIndique a data de INICIO de utilizacao do servico: \n");
                printf("Indique o dia: ");
                int data_dia_inicio = ler_numero(1, 31);

                printf("\nIndique o mes: ");
                int data_mes_inicio = ler_numero(1, 12);

                printf("\nIndique o ano: ");
                int data_ano_inicio = ler_numero(1970, 9999);

                validacao_data_inicio = validar_data(data_dia_inicio, data_mes_inicio, data_ano_inicio);

                if(validacao_data_inicio == 1) {
                    custo_vetor[custo_numero].data_inicio.dia = data_dia_inicio;
                    custo_vetor[custo_numero].data_inicio.mes = data_mes_inicio;
                    custo_vetor[custo_numero].data_inicio.ano = data_ano_inicio;
                }

            } while (validacao_data_inicio != 1);

            printf("\nIndique a hora de INICIO de utilizacao do servico: \n");

            printf("Indique a hora: ");
            custo_vetor[custo_numero].horario_inicio.hora = ler_numero(0, 23);
            printf("Indique o minuto: ");
            custo_vetor[custo_numero].horario_inicio.minuto = ler_numero(0, 59);

            char resposta;
            printf("\nJá possui uma data de FIM de utilização do serviço? (S/N)\n");
            do {
                scanf(" %c", &resposta);

                if(resposta == 'S' || resposta == 's') {
                    int validacao_data_fim = 1;

                    do {
                        printf("\nIndique a data de FIM de utilizacao do servico: \n");
                        printf("Indique o dia: ");
                        int data_dia_fim = ler_numero(1, 31);

                        printf("\nIndique o mes: ");
                        int data_mes_fim = ler_numero(1, 12);

                        printf("\nIndique o ano: ");
                        int data_ano_fim = ler_numero(1970, 9999);

                        validacao_data_fim = validar_data(data_dia_fim, data_mes_fim, data_ano_fim);

                        if(validacao_data_fim == 1) {
                            custo_vetor[custo_numero].data_fim.dia = data_dia_fim;
                            custo_vetor[custo_numero].data_fim.mes = data_mes_fim;
                            custo_vetor[custo_numero].data_fim.ano = data_ano_fim;
                        }

                    } while (validacao_data_fim != 1);

                    printf("\nIndique a hora de FIM de utilizacao do servico: \n");

                    printf("Indique a hora: ");
                    custo_vetor[custo_numero].horario_fim.hora = ler_numero(0, 23);
                    printf("Indique o minuto: ");
                    custo_vetor[custo_numero].horario_fim.minuto = ler_numero(0, 59);

                } else {
                    custo_vetor[custo_numero].data_fim.dia = 0;
                    custo_vetor[custo_numero].data_fim.mes = 0;
                    custo_vetor[custo_numero].data_fim.ano = 0;
                    custo_vetor[custo_numero].horario_fim.minuto = 0;
                    custo_vetor[custo_numero].horario_fim.hora = 0;
                }
            } while(resposta != 'N' && resposta != 'n' && resposta != 's' && resposta != 'S');

            printf("\nIntroduza a quantidade utilizada: ");
            custo_vetor[custo_numero].quantidade = ler_numero(0, 1000000000);

            custo_vetor[custo_numero].valor_pago = custo_vetor[custo_numero].quantidade * custo_unidade_servico;

        } else if(flag_p == 0) {
            printf("\nProjeto nao existente!\n");
        }
    } else if(flag_s == 0) {
        printf("\nServico nao existente!\n");
    }
}

void mostrar_dados_custo(custo custo_vetor[], int custo_numero) {
    for(int i = 0; i<custo_numero;i++) {
        printf("\n\nID do servico: %d", custo_vetor[i].id_do_servico);
        printf("\nID do projeto: %d", custo_vetor[i].id_do_projeto);
        printf("\nData e hora de inicio: %d-%d-%d as %d:%d\n", custo_vetor[i].data_inicio.dia, custo_vetor[i].data_inicio.mes, custo_vetor[i].data_inicio.ano, custo_vetor[i].horario_inicio.hora, custo_vetor[i].horario_inicio.minuto);
        printf("\nData e hora de fim: %d-%d-%d as %d:%d\n", custo_vetor[i].data_fim.dia, custo_vetor[i].data_fim.mes, custo_vetor[i].data_fim.ano, custo_vetor[i].horario_fim.hora, custo_vetor[i].horario_fim.minuto);
        printf("\nQuantidade: %.2f\n", custo_vetor[i].quantidade);
        printf("\nValor pago: %.2f $\n", custo_vetor[i].valor_pago);
    }
}

int procurar_projeto(projeto p_vetor[], int p_numero, int numero) {
    int flag = 0;

    for(int i = 0; i < p_numero; i++) {
        if(p_vetor[i].id_projeto == numero) {
            flag = 1;
        }
    }
    return flag;
}

int procurar_servico(servico s_vetor[], int s_numero, int numero) {
    int flag = 0;

    for(int i = 0; i < s_numero; i++) {
        if(s_vetor[i].id_servico == numero) {
            flag = 1;
        }
    }
    return flag;
}


int procurar_conta(conta c_vetor[], int c_numero, int numero) {
    int flag = 0;

    for(int i = 0; i < c_numero; i++) {
        if(c_vetor[i].id_conta == numero) {
            flag = 1;
        }
    }
    return flag;
}

void servicos_projeto_cont(sp_cont vetor_sp[], int id_projeto) {
    int flag = 0;

    for(int i = 0; i < NUM_MAX_PROJETOS; i++) {
        if (vetor_sp[i].id_do_projeto == id_projeto) {
            vetor_sp[i].numero_servicos++;
            flag = 1;
        }
    }

    if(flag == 0) {
        for(int i = 0; i < NUM_MAX_PROJETOS; i++) {
            if(vetor_sp[i].id_do_projeto == -1 && flag == 0) {
                vetor_sp[i].id_do_projeto = id_projeto;
                vetor_sp[i].numero_servicos = 1;
                flag = 1;
            }
        }
    }
}

void projeto_mais_servicos(sp_cont vetor_sp[]) {
    int maior_numero_servicos, id_projeto, multiplos_maximos = -1;
    for(int i = 0; i < NUM_MAX_PROJETOS; i++) {
        if(i == 0) {
            id_projeto = vetor_sp[i].id_do_projeto;
            maior_numero_servicos = vetor_sp[i].numero_servicos;
        }
        else if (vetor_sp[i].numero_servicos > maior_numero_servicos) {
            id_projeto = vetor_sp[i].id_do_projeto;
            maior_numero_servicos = vetor_sp[i].numero_servicos;
            multiplos_maximos = -1;
        } else if(vetor_sp[i].numero_servicos == maior_numero_servicos) {
            multiplos_maximos = 1;
        }
    }

    if(id_projeto == -1) {
        printf("\nNao existem servicos associados a projetos!\n");
    } else {
        if(multiplos_maximos == -1) {
            printf("\nID do projeto: %d\t Numero de servicos: %d\n", id_projeto, maior_numero_servicos);
        } else {
            printf("\nNão existe um projeto com um numero superior de servicos\n");
        }
    }
}

char confirmar_saida(void) {
    char resposta;

    printf("\nQuer mesmo sair? (S/N): ");
    do {
        fflush(stdin);
        scanf(" %c", &resposta);

        if (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
            printf("\nIndique uma opcao valida: ");
        }

    } while(resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N');

    return resposta;
}

void gravar_dados_ficheiro(conta c_vetor[], int c_numero, projeto p_vetor[], int p_numero, servico s_vetor[], int s_numero, custo custo_vetor[], int custo_numero, sp_cont sp_vetor[]) {
    FILE *ficheiro;

    ficheiro = fopen("dados.dat", "wb");

    if (ficheiro == NULL) {
        printf("Impossivel criar ficheiro.");
    } else {
        fwrite(&c_numero, sizeof(int), 1, ficheiro);
        fwrite(c_vetor, sizeof(conta), c_numero, ficheiro);

        fwrite(&p_numero, sizeof(int), 1, ficheiro);
        fwrite(p_vetor, sizeof(projeto), p_numero, ficheiro);

        fwrite(&s_numero, sizeof(int), 1, ficheiro);
        fwrite(s_vetor, sizeof(servico), s_numero, ficheiro);

        fwrite(&custo_numero, sizeof(int), 1, ficheiro);
        fwrite(custo_vetor, sizeof(custo), custo_numero, ficheiro);

        fwrite(sp_vetor, sizeof(sp_cont), NUM_MAX_PROJETOS, ficheiro);
    }

    fclose(ficheiro);
    printf("\nGravados com sucesso!\n");
}

void ler_dados_ficheiro(int vetores_cont[], conta c_vetor[], projeto p_vetor[], servico s_vetor[], custo custo_vetor[], sp_cont sp_vetor[]) {
    FILE *ficheiro;
    int c_numero, p_numero, s_numero, custo_numero;

    ficheiro = fopen("dados.dat", "rb");

    if (ficheiro == NULL) {
        printf("Impossivel abrir ficheiro.");
    } else {

        fread(&c_numero, sizeof(int), 1, ficheiro);
        fread(c_vetor, sizeof(conta), c_numero, ficheiro);

        fread(&p_numero, sizeof(int), 1, ficheiro);
        fread(p_vetor, sizeof(projeto), p_numero, ficheiro);

        fread(&s_numero, sizeof(int), 1, ficheiro);
        fread(s_vetor, sizeof(servico), s_numero, ficheiro);

        fread(&custo_numero, sizeof(int), 1, ficheiro);
        fread(custo_vetor, sizeof(custo), custo_numero, ficheiro);

        fread(sp_vetor, sizeof(sp_cont), NUM_MAX_PROJETOS, ficheiro);
    }
    fclose(ficheiro);

    vetores_cont[0] = c_numero;
    vetores_cont[1] = p_numero;
    vetores_cont[2] = s_numero;
    vetores_cont[3] = custo_numero;
}
