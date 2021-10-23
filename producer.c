#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include<string.h>

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
   time_t t;
   srand((unsigned) time(&t));
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

   /* Transfer blocks of data from buffer to shared memory */
   struct item next_produced;
   printf("\n");
   for (numtimes = 0; numtimes < 50; numtimes++) {
        while (((shmp->in + 1) % BUFFER_SIZE) == shmp->out) {
            printf("Waiting products to be consumed\n");
            sleep(1);
            continue;
        }

        next_produced.id = shmp->in;
        next_produced.quantity = (rand() % 100) + 1;
        next_produced.price = (rand() % 100) + 1;

        shmp->buffer[shmp->in] = next_produced;
        shmp->in = (shmp->in + 1) % BUFFER_SIZE;

        printf("Produced product id: %d\n",
                     next_produced.id);
   }

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
   return 0;
}
