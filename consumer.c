#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define SHM_KEY 0x1234

struct item {
    int id;
    int quantity;
    int price;
};

struct shmseg {
   int in;
   int out;
   struct item buffer[BUFFER_SIZE];
};

int main(int argc, char *argv[]) {
   int shmid, numtimes;
   struct shmseg *shmp;
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }

   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }

   struct item next_consumed;
   for (numtimes = 0; numtimes < 50; numtimes++) {
       while (shmp->in == shmp->out) {
            printf("Waiting products to be produced\n");
            sleep(1);
            continue;
       }

       next_consumed = shmp->buffer[shmp->out];
       shmp->out = (shmp->out + 1) % BUFFER_SIZE;

        sleep(1);
        printf("Consumed product id: %d\n",
                     next_consumed.id);
   }

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   return 0;
}
