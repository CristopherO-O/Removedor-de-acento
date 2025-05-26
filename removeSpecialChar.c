#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALAVRA 100
#define MAX_LINHA 1000

void normalizar(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
        // Substituição manual de alguns acentos e cedilha
        unsigned char c = (unsigned char)*src;

        switch (c) {
            case 'á': case 'à': case 'ã': case 'â': *dst = 'a'; break;
            case 'é': case 'ê':                  *dst = 'e'; break;
            case 'í':                            *dst = 'i'; break;
            case 'ó': case 'ô': case 'õ':        *dst = 'o'; break;
            case 'ú': case 'ü':                  *dst = 'u'; break;
            case 'ç':                            *dst = 'c'; break;

            case 'Á': case 'À': case 'Ã': case 'Â': *dst = 'A'; break;
            case 'É': case 'Ê':                    *dst = 'E'; break;
            case 'Í':                              *dst = 'I'; break;
            case 'Ó': case 'Ô': case 'Õ':          *dst = 'O'; break;
            case 'Ú': case 'Ü':                    *dst = 'U'; break;
            case 'Ç':                              *dst = 'C'; break;

            case '"': src++; continue;
            case ',': src++; continue;

            default:
                *dst = *src; break;
        }

        src++;
        dst++;
    }
    *dst = '\0';
}

int main() {
    FILE *entrada = fopen("entrada.txt", "r");
    FILE *saida = fopen("saida.txt", "w");

    if (!entrada || !saida) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), entrada);

    char *token = strtok(linha, ",");
    while (token != NULL) {
        char palavra[MAX_PALAVRA];
        strncpy(palavra, token, MAX_PALAVRA);
        palavra[MAX_PALAVRA - 1] = '\0';

        if (palavra[0] == '"') memmove(palavra, palavra + 1, strlen(palavra));
        int len = strlen(palavra);
        if (len > 0 && palavra[len - 1] == '"') palavra[len - 1] = '\0';

        normalizar(palavra);
        fprintf(saida, "%s\n", palavra);

        token = strtok(NULL, ",");
    }

    fclose(entrada);
    fclose(saida);

    printf("CONCLUIDO\n");
    return 0;
}