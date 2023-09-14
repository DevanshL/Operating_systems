// L DEVANSH CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    // pipe creation btw parent to child & child to grandchild
    
    int pc_pipe[2];
    int cgc_pipe[2];
    char str1[300];
    char str2[300];
    int s;
    int i=0;
    pid_t pid1,pid2;
    
    // pipe for parent and child check created or not..
    
    if(pipe(pc_pipe) == -1)
    {
        printf("Pipe failed to create \n");
        exit(1);
    }
    
    printf("Enter string to send from parent to child : ");
    while((s = getchar())!='\n')
    {
        if(i<300-1)
        {
            str1[i] = s;
            i++;
        }
        else
        {
            fprintf(stderr,"Length exceeded \n");
            exit(1);
        }
    }
    
    str1[i] = '\0';
    
    // now for fork() creation
    
    pid1 = fork();
    
    if(pid1 == -1)
    {
        printf("Fork failed to create");
        exit(1);
    }
    
    if(pid1 == 0)  // child process
    {
        close(pc_pipe[1]);    // close write for parent-child pipe
        
        read(pc_pipe[0],str1,300);
        
        printf("child id : %d\n",getpid());
        printf("parent id : %d\n",getppid());
        
        // for communication between child and grandchild
        if(pipe(cgc_pipe) == -1)
        {
        printf("Pipe failed to create \n");
        exit(1);
        }
        
        i=0;  // reset counter
        
        printf("Enter string to send from granchild to child : ");
        while((s = getchar())!='\n')
        {
            if(i<300-1)
            {
                str2[i] = s;
                i++;
            }
            else
            {
                fprintf(stderr,"Length exceeded \n");
                exit(1);
            }
        }
        
    str2[i] = '\0';             
    
    pid2 = fork();
    
    if(pid2 == -1)
    {
        printf("Fork failed to create");
        exit(1);
    }
    
    if(pid2 == 0)  // grandchild process
    {
        close(cgc_pipe[0]);   // close read of child-grandchild
        
        write(cgc_pipe[1],str2,strlen(str2)+1);
        
        printf("grandchild id : %d\n",getpid());
        printf("Child id : %d\n",getppid());
        
        close(cgc_pipe[1]);  // close write of child-grandchild
        exit(1);
    }
    
    else   // child process
    {
        close(cgc_pipe[1]);    // close write of child-grandchild
        read(cgc_pipe[0],str2,300);
        
        close(cgc_pipe[0]);   // close read of child-grandchild
        
        int l1 = strlen(str1);
        int l2 = strlen(str2);
        
        printf("the child prints the difference in lengths of the two messages : %d\n",abs(l1-l2));
        exit(1);
    }
    } 
    else  // parent process
    {
        close(pc_pipe[0]);  // close read  for parent-child
        write(pc_pipe[1],str1,strlen(str1)+1);
        close(pc_pipe[1]);
        wait(NULL);
        
                            // pid of parent....
                            // printf("pid of parent : %d\n",getpid());
        exit(1);
    }
    
    
    return 0;
}