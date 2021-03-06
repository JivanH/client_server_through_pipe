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
#define CLIENT_COUNT 10

pthread_t client_threads[CLIENT_COUNT] = {0};


void startup_server() {
	key_t key = 9874;
	
	int shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if (shmid < 0) {
		printf("Cannot shmget\n");
		exit(1);
	}

	char* shm = shmat(shmid, NULL, 0);

	 if (shm == (char *) -1) {
	 perror("shmat");
	 exit(1);
	 }
	 char up_message[] = "server is on";
 	 memcpy(shm, up_message, sizeof(up_message));	
}


void* client(void* args) {

	char* child_pipe = (char*) args;


	printf("In client function `%s`\n", child_pipe);




	free(child_pipe);
}


int create_pipe() {
	char *messages_from_server = "/tmp/registration";
        mkfifo(messages_from_server, 0666);
        int fd = open(messages_from_server, O_RDWR);
	return fd;
}

void start_to_lisen() {

	int fd = create_pipe();
	int connected_client_count = 0;

	char client_pid[BUFSIZE];
	while(read(fd, client_pid, 4)) {

		if (connected_client_count < CLIENT_COUNT) {
			char* child_pipe = (char*)malloc(BUFSIZE);"/tmp/client_";
			sprintf(child_pipe, "/tmp/client_%s", client_pid); 

			pthread_create(&client_threads[connected_client_count], NULL, 
				       client, child_pipe);


			pthread_join(client_threads[connected_client_count], NULL);

		} else {
			printf("Already enogh\n");
		}

	}
}

/*
void *serve_client_1 (void *arg)
{
 int* reg = (int*)arg;
 char *s;
 
 int shmid_from_server_to_client1;
 key_t key_client1;
 char *server_client1;
 key = 5874;
 shmid_from_server_to_client1 = shmget(key_client1, SHSIZE, IPC_CREAT | 0666);
 
  
 if (shmid_from_server_to_client1 < 0)
 {
   perror("shmget");
   exit(1);
 }
 
 server_client1 = shmat(shmid_from_server_to_client1, NULL, 0);
 
 if (server_client1 == (char *) -1)
 {
   perror("shmat");
   exit(1);
 }
 
 while(1)
 {
  if ( *shm_1 == '1')
  {
   printf("dd");
   if(reg[0] == '0')
   {
    reg[0] = '1';
    memcpy(server_client1,"OK",sizeof("OK"));
    memcpy(shm_1,"\0",1);
   }
   else
   {
    memcpy(server_client1,"YOU ARE ALREADY REGISTERED!",sizeof("YOU ARE ALREADY REGISTERED!"));
    memcpy(shm_1,"\0",1);
   }
  
  }  
  else if ( *shm_1 == '2')
  {
  
  }
  else 
  {
  }
 }
}
*/

int main(int argc, char* argv[])
{

	startup_server();
	start_to_lisen();
	
}
