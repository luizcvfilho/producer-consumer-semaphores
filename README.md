# Lab8 - Programação Concorrente

Este repositório contém um arquivo `.c` desenvolvido para o laboratório 8 da disciplina de Programação Concorrente.

## Arquivos

1. **prime-count.c**:
Recebe três valores N, M e C como argumento no momento da execução. O programa então fará a contagem de quantos números primos existem até o número N, de maneira concorrente, utilizando o padrão produtor/consumidor, usando um buffer de tamanho M, com C consumidores.

## Como Compilar

Para compilar o arquivo, utilize o `gcc` no terminal. Execute os seguintes comandos:

```bash
gcc -o prime-count.exe prime-count.c -Wall -lm
```

## Como Executar

Após a compilação, execute o programa com o comando abaixo:

### Executar `prime-count.c`

N = número limite para verificações de primos
M = tamanho do buffer
C = quantidade de consumidores a serem utilizados

```bash
./prime-count N M C
```

## Conclusão

Pude observar que o tempo de execução não variou muito com relação ao tamanho do buffer ou a quantidade de consumidores, o que eu imaginei que ocorreria. Com baixas alterações sendo observadas. Como esperado, os valores de tempo alteravam substancialmente conforme alterado o tamanho de N.
