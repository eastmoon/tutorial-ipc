#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

// Declare struct and class
struct pid_buffer {
    pid_t producer;
    pid_t consumer;
};


// Declare function
void handleSignals(int signum) {
    switch(signum) {
        case SIGINT:
            printf("\nYou pressed CTRL+C \n");
            printf("Now reverting SIGINT signal to default action\n");
            signal(SIGINT, SIG_DFL);
        break;
        case SIGQUIT:
            printf("\nYou pressed CTRL+\\ \n");
        break;
        default:
            printf("\nReceived signal number %d\n", signum);
        break;
   }
}

void registSignals(int signum) {
    if(signal(signum, handleSignals) == SIG_ERR){
        perror("signal regist errror");
        exit(EXIT_FAILURE);
    }
}

void modifySignals(int signum) {
    struct sigaction act;
    act.sa_handler = handleSignals;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if(sigaction(signum, &act, NULL) < 0){
        perror("signal modify errror");
        exit(EXIT_FAILURE);
    }
}

// Execute entry-point
int main()
{
    // setting signal handler
    registSignals(SIGINT);
    modifySignals(SIGQUIT);
    registSignals(SIGTERM);

    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    const int message_size = sizeof(pid_buffer);
    int shmid = shmget(key, message_size, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    pid_buffer* message = (pid_buffer*) shmat(shmid, (void*)0, 0);

    // retrieve current process id
    message->producer = getpid();

    // show shared memory data
    sleep(1);
    printf("Data from memory:\nP: %d\nC: %d\n", message->producer, message->consumer);

    // Send signal to current process
    raise(SIGINT);

    // sleep 5s
    sleep(5);

    //detach from shared memory
    shmdt(message);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
