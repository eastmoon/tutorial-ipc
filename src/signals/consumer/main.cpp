#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

struct pid_buffer {
    pid_t producer;
    pid_t consumer;
};

int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    const int message_size = sizeof(pid_buffer);
    int shmid = shmget(key, message_size, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    pid_buffer* message = (pid_buffer*) shmat(shmid, (void*)0, 0);

    // retrieve current process id
    message->consumer = getpid();

    // show shared memory data
    sleep(1);
    printf("Data from memory:\nP: %d\nC: %d\n", message->producer, message->consumer);

    // Send signal to producer process
    sleep(1);
    if (-1 == kill(message->producer, SIGQUIT)) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    //detach from shared memory
    shmdt(message);

    return 0;
}
