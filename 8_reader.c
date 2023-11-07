#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex; // global mutex semaphore
sem_t wrt; //wrt semaphore

int data = 0 ;
int rcount = 0;  // readcount is a simple variable

void *reader(void *arg){
    pthread_mutex_lock(&mutex);
    rcount = rcount + 1;
    if(rcount==1)
    sem_wait(&wrt);  //wait
    pthread_mutex_unlock(&mutex);
    printf("Data read by the reader%d is %d\n",*((int *)arg),data);  //this fucntion call takes value of data variable and thread id. thread id is a argument,u can see in reader funcion defination
    sleep(1);
    pthread_mutex_lock(&mutex);
    rcount = rcount - 1;
    if(rcount==0)
    sem_post(&wrt);  //signal i.e releases wrt 
    pthread_mutex_unlock(&mutex); // signal i.e releases mutex
}
void *writer(void *arg){
    sem_wait(&wrt);
    data++;
    printf("Data writen by the writer%d is %d\n",*((int *)arg),data);
    sleep(1);
    sem_post(&wrt);  // signal i.e releases wrt
}

int main()
{
int wn,rn,b; //writer count , reader count , buffer size

pthread_t rtid[100],wtid[100]; // no. of reader threads ,no. of writer threads

pthread_mutex_init(&mutex, NULL); //this line initializes the mutex variable .

sem_init(&wrt,0,1); // initializes the semaphore variable wrt with value 1

printf("Enter No. of Writer: ");
scanf("%d",&wn);
printf("Enter No. of Reader: ");
scanf("%d",&rn);

int arr[]={1,2,3,4,5,6,7,8,9,10};
for(int i=0;i<wn;i++)  // creates writer threads and stores their id's in wtid array
{
pthread_create(&wtid[i],NULL,writer,(void *)&arr[i]);   // calling function writer
}

for(int i=0;i<rn;i++) //creates reader threads and stores their id's in rtid array
{
pthread_create(&rtid[i],NULL,reader,(void *)&arr[i]);  // calling function reader
}

for(int i=0;i<wn;i++)  // all writers execute their execution and they are terminated from critical section and we store null .
{  // so multiple writes cha problem appear hota nhii
pthread_join(wtid[i],NULL);
}

for(int i=0;i<rn;i++)  //all readers read data and they get terminated.
{  // so we avoid reader writer problem
pthread_join(rtid[i],NULL);
}

return 0;
}
