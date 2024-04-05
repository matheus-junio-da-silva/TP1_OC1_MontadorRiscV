#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para traduzir a instrução lw
void translate_lw(char *operands, char *binary) {
    int rd, offset, rs1;
    sscanf(operands, "x%d, %d(x%d)", &rd, &offset, &rs1);

    sprintf(binary, "0000000%d%d%d0000011", offset, rs1, rd);
}

// Função para traduzir a instrução sw
void translate_sw(char *operands, char *binary) {
    int rs2, offset, rs1;
    sscanf(operands, "x%d, %d(x%d)", &rs2, &offset, &rs1);

    sprintf(binary, "0000000%d%d%d0100011", offset, rs1, rs2);
}

// Função para traduzir a instrução xor
void translate_xor(char *operands, char *binary) {
    int rd, rs1, rs2;
    sscanf(operands, "x%d, x%d, x%d", &rd, &rs1, &rs2);

    sprintf(binary, "0000000%d%d%d0010011", rs2, rs1, rd);
}

// Função para traduzir a instrução addi
void translate_addi(char *operands, char *binary) {
    int rd, rs1, imm;
    sscanf(operands, "x%d, x%d, %d", &rd, &rs1, &imm);

    sprintf(binary, "%011d%d%d0010011", imm, rs1, rd);
}

// Função para traduzir a instrução bne
void translate_bne(char *operands, char *binary) {
    int rs1, rs2, offset;
    sscanf(operands, "x%d, x%d, %d", &rs1, &rs2, &offset);

    sprintf(binary, "%011d%d%d1100011", offset, rs2, rs1);
}


// Fun��o para traduzir a instru��o add
void translate_add(char *operands, char *binary) {
    int rd, rs1, rs2;
    sscanf(operands, "x%d, x%d, x%d", &rd, &rs1, &rs2);

    sprintf(binary, "0000000%d%d%d0000011", rs2, rs1, rd);
}

// Fun��o para traduzir a instru��o sll
void translate_sll(char *operands, char *binary) {
    int rd, rs1, shamt;
    sscanf(operands, "x%d, x%d, %d", &rd, &rs1, &shamt);

    sprintf(binary, "0000000%d%d%d0010011", shamt, rs1, rd);
}

int main(int argc, char *argv[]) {
    /*if (argc != 2) {
        printf("Uso: %s arquivo_entrada.asm\n", argv[0]);
        return 1;
    }*/

    if (argc != 2 && argc != 4) {
        printf("Uso:\n");
        printf("Para exibir no terminal: %s arquivo_entrada.asm\n", argv[0]);
        printf("Para salvar em um arquivo: %s arquivo_entrada.asm -o arquivo_saida.bin\n", argv[0]);
        return 1;
    }

    printf("Nome do arquivo: %s\n", argv[1]);

    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        perror("fopen");
        printf("Valor de argv[1]: %s\n", argv[1]); // Adicionando print para verificar o valor de argv[1]
        return 1;
    }

    char linha[100]; // Tamanho arbitrário para a linha

    // Se o número de argumentos for igual a 4, significa que o usuário passou um arquivo de saída
    FILE *saida = NULL;
    if (argc == 4) {
        saida = fopen(argv[3], "w");
        if (saida == NULL) {
            printf("Erro ao abrir o arquivo de saída.\n");
            perror("fopen");
            printf("Valor de argv[3]: %s\n", argv[3]); // Adicionando print para verificar o valor de argv[3]
            fclose(entrada);
            return 1;
        }
    }

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        printf("Linha lida: %s", linha); // Print para verificar cada linha do arquivo de entrada
        
        /*
        char opcode[10], operands[50];
        sscanf(linha, "%s %[^\n]", opcode, operands);
        */
        // Verifica se a linha não está vazia
        if (strlen(linha) > 0) {
            char *opcode = strtok(linha, " "); // Separa o opcode da linha
            char *operands = strtok(NULL, "\n"); // Separa os operandos da linha
            
            // Traduza a instrução para código binário
            if (opcode != NULL && operands != NULL) {
                printf("Opcode: %s\n", opcode);
                printf("Operandos: %s\n", operands);
                char binary[32];
                // Adicione aqui a lógica para traduzir a instrução para código binário
                // Traduza a instrução para código binário
                if (strcmp(opcode, "add") == 0) {
                    //char binary[32];
                    printf("Traduzindo instrução 'add'\n"); // Print para verificar que a instrução 'add' está sendo traduzida
                    
                    translate_add(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "sll") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'sll'\n"); // Print para verificar que a instrução 'sll' está sendo traduzida
                    
                    translate_sll(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "lw") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'lw'\n"); // Print para verificar que a instrução 'lw' está sendo traduzida
                            
                    translate_lw(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "sw") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'sw'\n"); // Print para verificar que a instrução 'sw' está sendo traduzida
                            
                    translate_sw(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "xor") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'xor'\n"); // Print para verificar que a instrução 'xor' está sendo traduzida
                            
                    translate_xor(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "addi") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'addi'\n"); // Print para verificar que a instrução 'addi' está sendo traduzida
                            
                    translate_addi(operands, binary);
                    printf("%s\n", binary);
                } else if (strcmp(opcode, "bne") == 0) {
                    char binary[32];
                    printf("Traduzindo instrução 'bne'\n"); // Print para verificar que a instrução 'bne' está sendo traduzida
                            
                    translate_bne(operands, binary);
                    printf("%s\n", binary);
                }

                // Se o arquivo de saída estiver definido, escreva no arquivo, caso contrário, imprima no terminal
                if (saida != NULL) {
                    fprintf(saida, "%s\n", binary);
                } else {
                    printf("%s\n", binary);
                }

        // Adicione outros casos para as instruções suportadas
            }
           /* 
        // Dentro do loop principal
        printf("Opcode: %s\n", opcode);
        printf("Operandos: %s\n", operands);
        */

        
        }
    }
    fclose(entrada);
    if (saida != NULL) {
        fclose(saida);
    }
    return 0;
}