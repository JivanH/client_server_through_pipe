#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <libgen.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>


#define SHSIZE 100
#define BUFSIZE 100
#define CLINET_COUNT 10


int connect_to_pipe() {
        char *registration_pipe = "/tmp/registration";
        mkfifo(registration_pipe, 0666);
        int fd = open(registration_pipe, O_RDWR);
        if (fd == -1) {
                printf("Cannot open regisration pipe. error %s", strerror(errno));
                exit(1);
        }

        return fd;
}



void registration() {

        int pid = getpid();
        int reg_fd = connect_to_pipe();


        char pid_str[BUFSIZE];
        sprintf(pid_str, "%d", pid);
        write(reg_fd, pid_str, sizeof(pid_str));
        printf("Client registered with pid %d\n", pid);

}


int main(int argc, char* argv[])
{
       registration();       
}
