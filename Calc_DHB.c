#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_BITS 32
#define MAX_INPUT 65  // 32 bits + espaços opcionais + null terminator

// Função para validar a entrada binária
int validarBinario(char bin[]) {
    int i;
    for (i = 0; i < strlen(bin); i++) {
        if (bin[i] != '0' && bin[i] != '1') {
            return 0;  // Retorna falso se houver caracteres diferentes de '0' e '1'
        }
    }
    return 1;
}

// Função para validar a entrada decimal
int validarDecimal(char decimal[]) {
    int i;
    for (i = 0; i < strlen(decimal); i++) {
        if (!isdigit(decimal[i])) {
            return 0;  // Retorna falso se houver algo que não seja um dígito
        }
    }
    return 1;
}

// Função para remover espaços da string binária
void removerEspacos(char *str) {
    char *src = str, *dst = str;
    while (*src != '\0') {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';  // Finaliza a nova string sem espaços
}

// Função para exibir resultados em Decimal, Hexadecimal e Binário
void exibirResultados(int decimal) {
    int i;
    printf("\nResultado:\n");
    printf("Decimal: %d\n", decimal);
    printf("Hexadecimal: 0x%X\n", decimal);

    printf("Binário: ");
    for (i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (decimal >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" ");  // Espaço a cada 4 bits
    }
    printf("\n");
}

// Função para validar e converter Hexadecimal para Decimal
int validarEConverterHexadecimal(char hex[]) {
    int decimal;
    for (int i = 0; i < strlen(hex); i++) {
        if (!isxdigit(hex[i])) {
            printf("\nErro: Entrada inválida. Use apenas dígitos hexadecimais.\n");
            return -1;
        }
    }
    decimal = (int)strtol(hex, NULL, 16);
    return decimal;
}

// Função para validar e converter Binário para Decimal
int validarEConverterBinario(char bin[]) {
    int decimal;
    removerEspacos(bin);
    if (!validarBinario(bin)) {
        printf("\nErro: Entrada inválida. Use apenas '0' e '1'.\n");
        return -1;
    }
    decimal = (int)strtol(bin, NULL, 2);
    return decimal;
}

// Função principal
int main() {
	setlocale(LC_ALL, "Portuguese");
    int opcao;
    char entrada[MAX_INPUT];  // Buffer para armazenar a entrada
    char continuar;  // Para controlar o loop

    do {
        // Menu de seleção
        printf("\n============================================\n");
        printf("   Conversor de Números (Decimal, Hex, Bin)  \n");
        printf("============================================\n");

        do {
            printf("\nEscolha o formato de entrada:\n");
            printf("1. Decimal\n");
            printf("2. Hexadecimal\n");
            printf("3. Binário\n");
            printf("--------------------------------------------\n");
            printf("Opção: ");
            scanf("%d", &opcao);

            if (opcao < 1 || opcao > 3) {
                printf("\nErro: Opção inválida! Por favor, escolha entre 1 e 3.\n");
            }
        } while (opcao < 1 || opcao > 3);

        // Tratamento da opção selecionada
        switch(opcao) {
            case 1: {
                int decimal;
                printf("\nDigite o valor Decimal: ");
                scanf("%s", entrada);

                if (!validarDecimal(entrada)) {
                    printf("\nErro: Entrada inválida. Por favor, digite apenas números decimais.\n");
                    break;
                }

                decimal = atoi(entrada);  // Converte para inteiro após validação
                exibirResultados(decimal);
                break;
            }
            case 2: {
                printf("\nDigite o valor Hexadecimal (sem '0x'): ");
                scanf("%s", entrada);

                int decimal = validarEConverterHexadecimal(entrada);
                if (decimal != -1) {
                    exibirResultados(decimal);
                }
                break;
            }
            case 3: {
                printf("\nDigite o valor Binário (máx 32 bits): ");
                scanf(" %[^\n]%*c", entrada);  // Lê a entrada completa, incluindo espaços

                int decimal = validarEConverterBinario(entrada);
                if (decimal != -1) {
                    exibirResultados(decimal);
                }
                break;
            }
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                return 1;
        }

        // Pergunta ao usuário se deseja fazer outra conversão
        printf("\nDeseja fazer outra conversão? (s/n): ");
        scanf(" %c", &continuar);  // O espaço antes de %c é importante para ignorar o caractere de nova linha
    } while (continuar == 's' || continuar == 'S');

    printf("\n\n\n============================================================\n");
    printf("    Programa encerrado! By LOBO NINTENDISTA\n");
    printf("============================================================\n");

    return 0;
}
