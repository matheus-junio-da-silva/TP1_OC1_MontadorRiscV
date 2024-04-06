#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para traduzir a instrução lw
void translate_lw(char *operands, char *binary) {
    int rd, offset, rs1;
    sscanf(operands, "x%d, %d(x%d)", &rd, &offset, &rs1);

    // Monta o código binário no formato correto
    sprintf(binary, "%07d%05d%03d%05d%012d", 0b0000011, rs1, 0b010, rd, offset);
}

// Função para traduzir a instrução sw
void translate_sw(char *operands, char *binary) {
    int rs2, offset, rs1;
    sscanf(operands, "x%d, %d(x%d)", &rs2, &offset, &rs1);

    // Monta o código binário no formato correto
    sprintf(binary, "%07d%05d%05d%03d%07d%011d", 0b0100011, offset & 0b11111, rs1, 0b010, rs2, (offset >> 5) & 0b1111111);
}

// Função para traduzir a instrução xor
void translate_xor(char *operands, char *binary) {
    int rd, rs1, rs2;
    sscanf(operands, "x%d, x%d, x%d", &rd, &rs1, &rs2);

    // Monta o código binário no formato correto
    sprintf(binary, "%07d%05d%05d%03d%05d%07d", 0b0110011, rs2, rs1, 0b100, rd, 0b0000000);
}

// Função para traduzir a instrução addi
void translate_addi(char *operands, char *binary) {
    int rd, rs1, imm;
    sscanf(operands, "x%d, x%d, %d", &rd, &rs1, &imm);

    // Monta o código binário no formato correto
    sprintf(binary, "%012d%05d%03d%05d%07d", imm, rs1, 0b000, rd, 0b0010011);
}

// Função para traduzir a instrução bne
void translate_bne(char *operands, char *binary) {
    int rs1, rs2, offset;
    sscanf(operands, "x%d, x%d, %d", &rs1, &rs2, &offset);

    // Monta o código binário no formato correto
    sprintf(binary, "%012d%05d%05d%03d%07d", offset, rs2, rs1, 0b001, 0b1100011);
}

// Função para traduzir a instrução add
void translate_add(char *operands, char *binary) {
    int rd, rs1, rs2;
    sscanf(operands, "x%d, x%d, x%d", &rd, &rs1, &rs2);

    // Monta o código binário no formato correto
    sprintf(binary, "%07d%05d%05d%03d%05d%07d", 0b0000011, rs2, rs1, 0b000, rd, 0b0000000);
}

// Função para traduzir a instrução sll
void translate_sll(char *operands, char *binary) {
    int rd, rs1, shamt;
    sscanf(operands, "x%d, x%d, %d", &rd, &rs1, &shamt);

    // Monta o código binário no formato correto
    sprintf(binary, "%05d%05d%03d%05d%07d", shamt, rs1, 0b001, rd, 0b0000000);
}

int main(int argc, char *argv[]) {
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
    printf("Arquivo de entrada aberto com sucesso.\n");
    char linha[100]; // Tamanho arbitrário para a linha

    // Se o número de argumentos for igual a 4, significa que o usuário passou um arquivo de saída
    FILE *saida = NULL;
    if (argc == 4) {
        saida = fopen(argv[3], "w");
        printf("ola 1\n");
        if (saida == NULL) {
            printf("Erro ao abrir o arquivo de saída.\n");
            perror("fopen");
            printf("Valor de argv[3]: %s\n", argv[3]); // Adicionando print para verificar o valor de argv[3]
            fclose(entrada);
            return 1;
        }
    }
    printf("Arquivo de saída aberto com sucesso.\n");
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        printf("Linha lida: %s", linha); // Print para verificar cada linha do arquivo de entrada
        
        // Verifica se a linha não está vazia
        if (strlen(linha) > 0) {
            char *opcode = strtok(linha, " "); // Separa o opcode da linha
            char *operands = strtok(NULL, "\n"); // Separa os operandos da linha
            
            // Traduza a instrução para código binário
            if (opcode != NULL && operands != NULL) {
                printf("Opcode: %s\n", opcode);
                printf("Operandos: %s\n", operands);
                char binary[32];
                
                // Traduza a instrução para código binário
                if (strcmp(opcode, "add") == 0) {
                    printf("Traduzindo instrução 'add'\n"); 
                    translate_add(operands, binary);
                } else if (strcmp(opcode, "sll") == 0) {
                    printf("Traduzindo instrução 'sll'\n"); 
                    translate_sll(operands, binary);
                } else if (strcmp(opcode, "lw") == 0) {
                    printf("Traduzindo instrução 'lw'\n"); 
                    translate_lw(operands, binary);
                } else if (strcmp(opcode, "sw") == 0) {
                    printf("Traduzindo instrução 'sw'\n"); // Print para verificar que a instrução 'sw' está sendo traduzida
                    translate_sw(operands, binary);
                } else if (strcmp(opcode, "xor") == 0) {
                    printf("Traduzindo instrução 'xor'\n"); // Print para verificar que a instrução 'xor' está sendo traduzida
                    translate_xor(operands, binary);
                } else if (strcmp(opcode, "addi") == 0) {
                    printf("Traduzindo instrução 'addi'\n"); // Print para verificar que a instrução 'addi' está sendo traduzida
                    translate_addi(operands, binary);
                } else if (strcmp(opcode, "bne") == 0) {
                    printf("Traduzindo instrução 'bne'\n"); // Print para verificar que a instrução 'bne' está sendo traduzida
                    translate_bne(operands, binary);
                }

                // Se o arquivo de saída estiver definido, escreva no arquivo, caso contrário, imprima no terminal
                if (saida != NULL) {
                    printf("Escrevendo no arquivo de saída: %s\n", binary);
                    fprintf(saida, "%s\n", binary);
                  
                } else {
                    printf("%s\n", binary);
                }
            }
        }
    }
    fclose(entrada);
    if (saida != NULL) {
        fclose(saida);
    }
    return 0;
}
