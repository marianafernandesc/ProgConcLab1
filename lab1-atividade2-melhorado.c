/*
Disciplina: Programação Concorrente
Professora: Silvana Rossetto
Estudante: Mariana Fernandes Cabral
DRE: 121060838
Laboratório: 1
Atividade: 2

*/

#include <stdio.h>
#include <pthread.h>

/*Criando vetor de escopo global*/
int vetor[10000];
int nthreads;

/*Criando funcao que multiplica o conteudo do vetor por 2*/
void *multiplicarpor2 (void *thread_id){ 
    int idt = *(int *) thread_id;
    printf("Thread %d executando.\n", idt);
    for (int n = idt; n < 10000; n+=nthreads) { 
        vetor[n] = n*2; 
    //    printf("n = %d", vetor[n]);

    } 
    pthread_exit(NULL); 
}

/*
void *multiplicarpor2v1 (void *thread_id){ 
    for (int m = 0; m < 10000; m+=2) { 
        vetor[m] = m*2; 
    }
    pthread_exit(NULL); 
}

void *multiplicarpor2v2 (void *thread_id){ 
    for (int n = 1; n < 10000; n+=2) { 
        vetor[n] = n*2; 
    } 
    pthread_exit(NULL); 
}
*/

/*funcao verificar_vetor verifica se o conteudo de cada 
posicao do vetor foi multiplicado por 2*/
int verificar_vetor (){ 
    for (int z = 0; z < 10000; z++) { 
        if (vetor[z] != z*2){
            printf("Erro no vetor[%d]=%d.\n", z, vetor[z]); 
            return 1; 
        } 
    }
    printf("Tudo certo! Tarefa de multiplicar por 2 realizada com sucesso.\n");
    return 0;
}

int main() { 
    nthreads = 2;
    /*criando vetor de threads do tipo pthread_t*/
    pthread_t threads[nthreads];
    int id[nthreads];

    /*variável verificar checa o retorno de verificar_vetor*/ 
    int verificar; 

    /*inicializacao do vetor*/
    for (int k = 0; k < 10000; k++) { 
        vetor[k] = k; 
    } 

    /*criacao das threads com uma realizando a funcao
    da multiplicacao em posicoes pares e outra realizando
    a funcao da multiplicacao em posicoes impares.*/
    /*
    int num;
    num = 0;
    */
    for(int m = 0; m < 2; m++){
        id[m] = m;
        if(pthread_create(&threads[m], NULL, multiplicarpor2, (void *) &id[m])){
            printf("Erro ao criar thread.\n");
        }
    }
    /*
    pthread_create(&threads[0], NULL, multiplicarpor2v1, (void *) num);

    num = 1; 
    pthread_create(&threads[1], NULL, multiplicarpor2v2, (void *) num);
    */

    for (int i = 0; i < 2; i++) { 
        pthread_join(threads[i], NULL); 
    }

    /*verificacao das multiplicacoes*/
    verificar = verificar_vetor();

    return 0;
}