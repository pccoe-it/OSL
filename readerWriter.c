#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t sem;
pthread_mutex_t x;

int readcount=0;
int s=5;

void * writef(void * a){
    int r= (long long) a;
    int i=0;

    while(i<3){
        sem_wait(&sem);
        s=s+5;
        printf("Writer %d is writing %d \n",r,s);
        sem_post(&sem);
        sleep(rand()%10);
        i++;
    }
    return NULL;
}

void * readf(void * a){
    int r = (long long) a;
    int i=0;

    while(i<3){
        pthread_mutex_lock(&x);
        readcount++;
        if(readcount==1){
            sem_wait(&sem);
        }
        pthread_mutex_unlock(&x);
        printf("\t\t Reader %d is reading %d \n",r,s);
        pthread_mutex_lock(&x);
        readcount--;
        if(readcount==0){
            sem_post(&sem);
        }
        pthread_mutex_unlock(&x);
        sleep(rand()%10);
        i++;
    }
    return NULL;
}
int main(){

    int op;
    pthread_t reader[5];
    pthread_t writer[5];
    pthread_mutex_init(&x,NULL);
    sem_init(&sem,0,1);

    do{
        printf("Enter your choice\n");
        printf("1.Reader Priority\n");
        printf("2.Exit\n");
        scanf("%d",&op);

        if(op==1)
        {
            for(int i=0;i<3;i++){
                pthread_create(&writer[i],NULL,writef,(void *)(long long)i);
            }
            for(int i=0;i<3;i++){
                pthread_create(&reader[i],NULL,readf,(void *)(long long)i);
            }
            for(int i=0;i<3;i++){
                pthread_join(writer[i],NULL);
            }
            for(int i=0;i<3;i++){
                pthread_join(reader[i],NULL);
            }
        }
        else if(op==2)
        {
            break;
        }

    }
    while(op!=2);

    return 0;

}
