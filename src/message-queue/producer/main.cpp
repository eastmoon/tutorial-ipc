// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#define MAX 10

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgsnd to send message
    message.mesg_type = 1;
    strcpy( message.mesg_text, "Hi, message queue! send to channel 1!" );
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data send is : %s \n", message.mesg_text);

    // msgsnd to send message
    message.mesg_type = 2;
    strcpy( message.mesg_text, "Hi, message queue! send to channel 2!" );
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data send is : %s \n", message.mesg_text);

    // Wait 2 s
    sleep(2);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
