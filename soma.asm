# Exemplo de código assembly para somar dois números

.data
    # Declaração de variáveis
    num1: .word 10       # Primeiro número
    num2: .word 20       # Segundo número
    resultado: .word 0   # Resultado da soma

.text
    # Seção de código
    .globl _start       # Define o ponto de entrada do programa

_start:
    lw t0, num1         # Carrega o primeiro número para o registrador t0
    lw t1, num2         # Carrega o segundo número para o registrador t1
    add t2, t0, t1      # Soma os números e armazena o resultado em t2
    sw t2, resultado    # Armazena o resultado na variável resultado

    # Operações adicionadas
    xor t3, t0, t1      # Faz a operação XOR entre t0 e t1 e armazena o resultado em t3
    addi t4, t0, 5      # Adiciona o valor imediato 5 ao valor de t0 e armazena o resultado em t4
    sll t5, t1, 2       # Desloca o valor de t1 para a esquerda por 2 bits e armazena o resultado em t5
    bne t0, t1, fim     # Se t0 for diferente de t1, salta para o rótulo fim

fim:
    # Termina o programa
    li a7, 10           # Carrega o código de saída do sistema (exit)
    ecall               # Chama o sistema operacional para encerrar o programa
