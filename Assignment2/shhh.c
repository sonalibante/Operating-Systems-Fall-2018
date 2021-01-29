#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void clear (int array1[]);

int main() {
    char *iPath, *oPath, *argv[20], buf[80], n, *p;
    int m, status, inword, continu,i;

   // int start[20];

    int inputRedirectFlag, outputRedirectFlag;

    /* variables for piping */
    int count, pipes;
    pid_t pid;

    /* pipes */
    int pipe1[2], pipe2[2];

    /* required container for handling arguments */
    int array1[20] = { 0 };

    while (1) {

        inword = m = continu = count = pipes = pid = 0;

        p = buf;

        /* redirection flags reset */
        inputRedirectFlag = outputRedirectFlag = 0;

        /* shell prompt */
        printf("\nshhh> ");

        /* command parsing */
        while ((n = getchar()) != '\n' || continu)
        {
            if (n == ' ') {
                if (inword)
                {
                    inword = 0;
                    *p++ = 0;
                }
            }
            else if (n == '\n')
                continu = 0;
            else if (n == '\\' && !inword)
                continu = 1;
            else {
                if (!inword)
                {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                }
                else
                    *p++ = n;
            }
        } /* end of command parsing */

        *p++ = 0;
        argv[m] = 0;

        /* user wishes to terminate program */
        if (strcmp(argv[0], "exit") == 0)
            exit(0);

        /* manage redirection */
        while (argv[count] != 0) {
            if (strcmp(argv[count], "|") == 0) {
                argv[count] = 0;
                array1[pipes + 1] = count + 1;
                ++pipes;
            }
            else if (strcmp(argv[count], "<") == 0) {
                iPath = strdup(argv[count + 1]); /* copy string argument (file string) */
                argv[count] = 0;
                argv[count + 1] = 0;
                inputRedirectFlag = 1;
            }
            else if (strcmp(argv[count], ">") == 0) {
                oPath = strdup(argv[count + 1]); /* copy string argument (file string) */
                argv[count] = 0;
                argv[count + 1] = 0;
                outputRedirectFlag = 1;
            }
            else {
                array1[count] = count;
            }

            ++count;
        } /* end of redirection management */
        int index;
        /* execute commands [<= in for-loop; n pipes require n+1 processes] */
        for (index = 0; index <= pipes; ++index) {
            if (pipes > 0 && index != pipes) { /* if user has entered multiple commands with '|' */
                pipe(pipe2); /* no pipe(l_pipe); r_pipe becomes next child's l_pipe */
            }

            /* switch-statement for command execution */
            switch (pid = fork()) {
                /* fork() error */
                case -1: perror("fork failed");
                         break;

                case 0: /* child process manages redirection and executes */
                       if ((index == 0) && (inputRedirectFlag == 1)) {
                           int inputFileDescriptor = open(iPath, O_RDONLY , 0400);
                           if (inputFileDescriptor == -1) {
                               perror("input file failed to open\n");
                               return(EXIT_FAILURE);
                           }
                           close(0);
                           dup(inputFileDescriptor);
                           close(inputFileDescriptor);
                       } /* end of input redirection management */

                       if ((index == pipes) && (outputRedirectFlag == 1)) {
                           int outputFileDescriptor = open(oPath, O_WRONLY | O_CREAT, 0755);
                           if (outputFileDescriptor < 0) {
                               perror("output file failed to open\n");
                               return(EXIT_FAILURE);
                           }
                           close(1);
                           dup(outputFileDescriptor);
                           close(outputFileDescriptor);
                       } /* end of output redirection management */

                        /* manage pipes if (a) first child process, (b) middle child process, or (c) third/final child process */
                        if (pipes > 0) {
                            if (index == 0){ /* first child process */
                                close(1);
                                dup(pipe2[1]);
                                close(pipe2[1]);
                                close(pipe2[1]);
                            }
                            else if (index < pipes) { /* middle child process */
                                close(0);
                                dup(pipe1[0]);
                                close(pipe1[0]);
                                close(pipe1[1]);
                                close(1);
                                dup(pipe2[1]);
                                close(pipe2[0]);
                                close(pipe2[1]);
                            }
                            else { /* third/final child process */
                                close(0);
                                dup(pipe1[0]);
                                close(pipe1[0]);
                                close(pipe1[1]);
                            }
                        }

                       /* execute command */
                       execvp(argv[array1[index]], &argv[array1[index]]);

                       /* if execvp() fails */
                       perror("execution of command failed\n");

                       break;

                default: /* parent process manages the pipes for child process(es) */
                        if (index > 0) {
                            close(pipe1[0]);
                            close(pipe1[1]);
                        }
                        pipe1[0] = pipe2[0];
                        pipe1[1] = pipe2[1];

                        /* parent waits for child process to complete */
                        wait(&status);

                        break;
            } /* end of switch-statement for command execution */
        } /* end of loop for all pipes */

        // clear all executed commands
        for (i = 0; i < 20; ++i) {
            argv[i] = 0;
        }
    }
}

void clear (int array1[]){
    // clear argument container
    int i;
    for (i = 0; i < 20; ++i) {
        array1[i] = 0;
    }
}
