// CS21B2023 L DEVANSH

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>

#define shm_size 100

int main() {
    int x, shmid;
    int *shm, *s;
    key_t key = 20232023;
    
    if((shmid = shmget(key, shm_size, IPC_CREAT|0666)) < 0) {       // create shared memory
        printf("Error in shmget \n");
        exit(1);
    }
    
    if((shm = shmat(shmid, NULL, 0)) == (int *) -1) {       //. attach shared memory to sender
        printf("Error in shmat \n");
        exit(1);
    }
    
    s = shm;            // starting pointer (shm) to 's'
    
    for(x = 2;x<27;x++) {
        *s++ = x;
    }
    
    *s = 0;
    
    while(*shm != '#') {
        sleep(1);
        
    }
    
    for(*s;*s!=0;*s++) {
        printf(" %d ",*s);
    }
    
    return 0;
}