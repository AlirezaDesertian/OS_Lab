#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    int arr[10] = {1,4,7,10,2,6,8,3,5,12};

    pid_t pid = fork();

    if (pid > 0) {
        // Parent
        close(pipe1[0]); 
        write(pipe1[1], arr, sizeof(arr));
        close(pipe1[1]); 

        close(pipe2[1]); 
        int result[2];
        read(pipe2[0], result, sizeof(result));
        close(pipe2[0]);

        printf("Sum = %d\n", result[0]);
        printf("Even Count = %d\n", result[1]);

        wait(NULL);
    } 
    else {
        // Child
        close(pipe1[1]); 
        int recv[10];
        read(pipe1[0], recv, sizeof(recv));
        close(pipe1[0]);

        int sum = 0, even = 0;
        for (int i = 0; i < 10; i++) {
            sum += recv[i];
            if (recv[i] % 2 == 0) even++;
        }

        close(pipe2[0]);
        int result[2] = {sum, even};
        write(pipe2[1], result, sizeof(result));
        close(pipe2[1]);
    }

    return 0;
}
