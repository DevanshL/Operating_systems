#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h> 

# define max 10
struct msg_buffer{
    long msg_type;
    int num[10];
};

int main()
{
    key_t key;
    int msgid;

    struct msg_buffer message;              // access struct elements

    key = ftok("sender_reciever",65);           // port 

    msgid = msgget(key,0666|IPC_CREAT);                 // creation of message id.
    
    // To recieve messages 
    msgrcv(msgid,&message,sizeof(message.num),1,0);         // 1- long msg_type from sender 0- flag

    printf("The recieved numbers are : \n");
    for(int i=0;i<max;i++)
    {
        printf("%d\n",message.num[i]);
    }
    printf("\n");

    printf(" Displays how many odd numbers are there among those numbers and displays them.\n");

    int o_count = 0;
    for (int i = 0 ;i <max ; i++)
    {
        if(message.num[i]%2!=0)
        {
            printf("%d\n",message.num[i]);
            o_count++;
        }
    }
    printf("\n");
    printf("Odd numbers count : %d\n",o_count);
    return 0;
}

