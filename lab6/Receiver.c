// cs21b2023 L DEVANSH
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define shm_size 100

int main() {
    int x, shmid;
    key_t key = 20232023;
    int *shm, *s;
    
    if((shmid = shmget(key, shm_size, 0666)) < 0) {     // create shared memory
        printf("Error in shmget \n");
        exit(1);
    }
    
    if((shm = shmat(shmid, NULL, 0)) == (int *) -1) {   // attach share memory to receiver
        printf("Error in shmat \n");
        exit(1);
    }
    
    for(s = shm; *s != 0; s++) {
        printf(" %d ",*s);
    }
    
    for(x = 27;x<52;x++) {
        *s++ = x;
    }
    
    *s = 0;
    
    *shm = '#';         // sender will be in sleep until this step
    
    return 0;
}