// L DEVANSH CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int p1[2],p2[2];
    char str[300];
    char rev_str[300];
    pid_t pid;
    int s;
    int i=0;
    
    // check pipe created or not
    if(pipe(p1) == -1 || pipe(p2) == -1)
    {
        fprintf(stderr,"Pipe failed to create \n");
        return 1;
    }
    
    printf("Enter the string : ");
    while((s = getchar())!='\n')   // end of line
    {
        if(i<300)
        {
            str[i] = s;
            i++;
        }
        else
        {
            fprintf(stderr,"Length exceeded \n");
            exit(1);
        }
    }
    
    str[i] = '\0';
    
    pid = fork();
    
    if(pid<0)
    {
        printf("Fork failed to create \n");
        exit(1);
    }
    
    if(pid == 0)  // child process
    {
        close(p1[1]);  // write of p1(parent)
        close(p2[0]);   // read of p2(child)
        
        read(p1[0],str,300);
        
        // reverse in child to send to parent
        int l = strlen(str);
        for(int i=0;i<l/2;i++)
        {
            char t = str[i];
            str[i] = str[l-i-1];
            str[l-i-1] = t;
        }
        
        // now send to parent through p2
        write(p2[1],str,strlen(str)+1);
        close(p1[0]);
        close(p2[1]);
        exit(1);
    }
    else    /// parent process
    {
        close(p1[0]);  // read of p1(parent)
        close(p2[1]);   // write of p2(child)
        
        write(p1[1],str,strlen(str)+1);
        wait(NULL);
        
        read(p2[0],rev_str,300);
        printf("Reversed string : %s\n",rev_str);
        
        close(p1[1]);
        close(p2[0]);
        exit(1);
    }
    
    return 0;
}