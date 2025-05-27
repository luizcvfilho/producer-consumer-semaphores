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

Através da análise das tabelas acima, é possível perceber que para esse problema, quanto maior o número de threads, maior o tempo de execução. Isso se dá por causa do mutex que usamos, que acaba impedindo o trabalho simultâneo das threads em alguns momentos, fazendo com que o custo de tempo para criar elas seja maior do que o tempo que elas economizam realizando as tarefas de maneira simultânea.

Outro detalhe interessante de se observar, é a diferença de tempo entre o algoritmo sequencial e o algoritmo concorrente com apenas uma thread. Visto que o segundo tem um tempo de execução um pouco maior também por causa desse custo para criação da thread.
