//? Implement a C program to create a message queue by sending a message and then receive the
//? message in reverse via the message queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 100

// Define the message structure
struct message {
    long msg_type;
    char text[MAX_TEXT];
};

// Function to reverse a string
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key
    key = ftok("msgqueuefile", 65);
    
    // Create a message queue and check for errors
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Input a message from the user
    printf("Enter a message: ");
    fgets(msg.text, sizeof(msg.text), stdin);
    msg.text[strcspn(msg.text, "\n")] = 0; // Remove the newline character

    // Set message type for the original message
    msg.msg_type = 1;

    // Send the original message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd failed for original message");
        exit(1);
    }

    printf("Original message sent: %s\n", msg.text);

    // Reverse the message
    reverse_string(msg.text);

    // Set message type for the reversed message
    msg.msg_type = 2;

    // Send the reversed message to the queue
    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd failed for reversed message");
        exit(1);
    }

    printf("Reversed message sent: %s\n", msg.text);

    // Receive the reversed message using msg_type = 2
    struct message received_msg;
    if (msgrcv(msgid, &received_msg, sizeof(received_msg.text), 2, 0) == -1) {
        perror("msgrcv failed for reversed message");
        exit(1);
    }

    printf("Reversed message received: %s\n", received_msg.text);

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
