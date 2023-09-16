// L DEVANSH CS21B2023

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h> ///  message queue .

# define max 10

// message sending structure
struct msg_buffer {
    long msg_type;
    int num[10];
};

int main() {
    key_t key;
    int msgid;
    
    struct msg_buffer message;   // by this we access the struct part.

    key = ftok("sender_reciever", 65);  //used to generate a key for accessing a System  IPC 
    
    // msgget creates a message queue and returns its identifier.
    msgid = msgget(key, 0666 | IPC_CREAT);

    if(msgid == -1)
    {
        printf("Data note sent\n");
        exit(1);
    }
    
    message.msg_type = 1; // identifies the msg type.


    printf("Enter the %d numbers:\n", max);
    for (int i = 0; i < max; i++) {
        scanf("%d", &message.num[i]);
    }

    msgsnd(msgid, &message, sizeof(message.num),0);    // send msg   0 -flag  &msg - data
    printf("Data sent to the queue\n");
    
    return 0;
}
