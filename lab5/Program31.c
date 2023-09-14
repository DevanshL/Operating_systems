// L.DEVANSH

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    int pid=fork();
    if(pid == -1)
    {
        printf("error\n");
        exit(0);
    }
    
    else if(pid==0)
    {
        printf("pid of child =%d\n",getpid());
        printf("parent pid of child = %d\n",getppid());
        printf("return value of fork=%d\n",pid);
        char *args[]={"./Lab5Question42",NULL};
        execvp(args[0],args);
        printf("hello\n");
        printf(" child process\n");
        exit(0);
        
    }
    if(pid>0){
        wait(NULL);
        printf("L.Devansh\n");
        printf("CS21B2023\n");
        printf("IIITDM KANCHEEPURAM\n");
        printf("pid =%d\n",getpid());
        printf("parent pid = %d\n",getppid());
        printf("return value of fork() system call = %d\n",pid);
        
        
        
        
    }
    return 0;
}