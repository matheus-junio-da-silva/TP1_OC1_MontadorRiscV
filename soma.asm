# Exemplo de c�digo assembly para somar dois n�meros

.data
    # Declara��o de vari�veis
    num1: .word 10       # Primeiro n�mero
    num2: .word 20       # Segundo n�mero
    resultado: .word 0   # Resultado da soma

.text
    # Se��o de c�digo
    .globl _start       # Define o ponto de entrada do programa

_start:
    lw t0, num1         # Carrega o primeiro n�mero para o registrador t0
    lw t1, num2         # Carrega o segundo n�mero para o registrador t1
    add t2, t0, t1      # Soma os n�meros e armazena o resultado em t2
    sw t2, resultado    # Armazena o resultado na vari�vel resultado

    # Termina o programa
    li a7, 10           # Carrega o c�digo de sa�da do sistema (exit)
    ecall               # Chama o sistema operacional para encerrar o programa

