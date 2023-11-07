#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
 
#define MAXSIZE  27
 
void die(char *s)
{
    perror(s);  // s is error
    exit(1);
}
 
int main()
{
    int shmid;
    key_t key;
    char *shm, *s;
 
    key = 5679;
 
    if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
        die("shmget");
 
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
        die("shmat");
 
    s = shm;   // address of the shared memory segment
 
    for (char c = 'a'; c <= 'z'; c++)
        *s++ = c;

    printf("\n\nServer is Ready!!\n\nNow data is available on shared memory!!\n");

    while (*shm != '*')
        sleep(1);

    printf("\n\nServer Terminated!!!\n\n");
    exit(0);
}
