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

    # Termina o programa
    li a7, 10           # Carrega o código de saída do sistema (exit)
    ecall               # Chama o sistema operacional para encerrar o programa

