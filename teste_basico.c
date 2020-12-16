#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t acorda_pombo;
//sem_t sleep;

int contPostIt = 0;

#define N 20
#define valor_cont 1000
long long contagem = 0;

void dorme_aleatorio()
{
    //sem_post()
}

void leva_mochila_ate_B_e_volta()
{
    sleep(2);
}

void *pombo() 
{
    while(1)
    {
        sem_wait(&acorda_pombo);
        leva_mochila_ate_B_e_volta();
        contPostIt = 0;
        for (int i=0; i<N; i++)
        {
            printf("enviando carta: %d\n", i+1);
        }
    }
}

void *usuario(void *valor)
{
    /*for( ; ; )
    {
        sem_wait(&mutex);
        if(contagem >= valor_cont)
        {
            sem_post(&mutex);
            return NULL;
        }

        else
        { 
            ++contagem;
            printf("%lld\n", contagem);
        }
        sem_post(&mutex);
    }*/
    while(1)
    {
        sem_wait(&mutex);
        //dorme_aleatorio();
        contPostIt++;
        if (contPostIt == N)
        {
            printf("mochila cheia\n");
            sem_post(&mutex);
            sem_post(&acorda_pombo);
            pombo();
        }
        else
            sem_post(&mutex);
    }
}



/*int pombo() 
{
    while(1)
    {
        leva_mochila_ate_B_e_volta();
        for (int i=0; i<N; i++)
        {
            printf("Adic. msg %d\n", i);
        }
    }
}*/

/*void *hello_world(void *valor)
{
    printf("thread 2\n");

    int *num = (int *) valor;
    printf("valor:%d\n", *num);
    return NULL;
}*/

int main()
{
    int i = 0;
    int quantidade_usuarios;

    sem_init(&mutex, 0 , 1);
    sem_init(&acorda_pombo, 0, 0);

    printf("Escolha uma quantidade de ususarios:\n");
    scanf("%d", &quantidade_usuarios);

    pthread_t *usuarios = malloc(sizeof(pthread_t) * quantidade_usuarios);
    pthread_t thread_pombo;

    pthread_create(&thread_pombo, NULL, pombo, NULL);

    for(i = 0; i < quantidade_usuarios; i++)
        pthread_create(&usuarios[i], NULL, usuario, NULL);
    
    for(i = 0; i < quantidade_usuarios; i++)
        pthread_join(usuarios[i],NULL);

    pthread_join(thread_pombo,NULL);

    return EXIT_SUCCESS;
}
