#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t mutex;
sem_t acorda_pombo;
sem_t proximo_usuario;

int contPostIt = 0;

#define N 20

void dorme_aleatorio()
{
    sleep(rand() % 3+1);
}

void leva_mochila_ate_B_e_volta()
{
    sleep(rand() % 3+1);
}

void ColaPostIt()
{
    printf("Post-it colado\n");
}

void *pombo() 
{
    while(1)
    {   sem_wait(&acorda_pombo);/*Bloqueia o pombo até que a Mochila esteja cheia,
                                ou seja, até que a variável "contPostIt" seja == 20 */ 
        leva_mochila_ate_B_e_volta();//Faz a thread dormir de 1 a 3 segundos      
        contPostIt = 0;             
        sem_post(&proximo_usuario);//Libera o usuário após o esvaziamento da mochila     
        for (int i=0; i<N; i++)     
        {       
            printf("Enviando carta %d\n", i+1);     
        }    
    }
}

void *usuario()
{

    while(1)
    {
        sem_wait(&mutex);//Permite que um usuário entre e bloqueia o resto     
        dorme_aleatorio();//Faz a thread dormir de 1 a 3 segundos     
        ColaPostIt();//Imprime na tela "Post-it colado"     
        contPostIt++;     
        if (contPostIt == N)     
        {       
            printf("Mochila cheia\n");   
            sem_post(&acorda_pombo);//Acorda o pombo
            sem_wait(&proximo_usuario);/*Bloqueia o usuário até que o pombo 
                                        tenha esvaziado a variável "contPostIt"*/
        }
        sem_post(&mutex); //Libera o próximo usuário  
    }
}


int main()
{
    srand(time(NULL)); //

    int i = 0;
    int quantidade_usuarios; //Variavel que será usada para definir a quantidade de threads criadas

    //Inicialização dos semáfros que serão usados nas funções
    sem_init(&mutex, 0 , 1); 
    sem_init(&acorda_pombo, 0, 0);
    sem_init(&proximo_usuario, 0, 0);

    //Scaneia a entrada do usuário, que define a quantidade de threads a serem criadas
    printf("Escolha uma quantidade de usuarios:\n");
    scanf("%d", &quantidade_usuarios);

    //Cria e aloca espaço para as threads do usuário e pombo
    pthread_t *usuarios = malloc(sizeof(pthread_t) * quantidade_usuarios);
    pthread_t thread_pombo;

    //Instancia a thread pombo
    pthread_create(&thread_pombo, NULL, pombo, NULL);
    
    //Instancia as threads do usuario 
    for(i = 0; i < quantidade_usuarios; i++)
        pthread_create(&usuarios[i], NULL, usuario, NULL);
    
    /*Para a main, fazendo com que a execução desta só continue
    após o termino da execução das threads*/
    for(i = 0; i < quantidade_usuarios; i++)
        pthread_join(usuarios[i],NULL);

    pthread_join(thread_pombo,NULL);

}
