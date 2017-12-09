#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 0x1337
#define SIZE 1000
#define NONE -1
#define CREATE 0
#define VIEW 1
#define REMOVE 2

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};
int main(){
  int desc = semget(KEY, SIZE, IPC_CREAT | IPC_EXCL );
  struct sembuf buf;
  buf.sem_num = 0;
  buf.sem_op = -1;
  buf.sem_flg = SEM_UNDO;
  semop(desc, &buf , 1);
  int mem = shmget(KEY, SIZE, 0600);
  printf("Last entry: %s\n", mem);
  shmdt(mem);
  printf("Input a new line!\n");
  char* newline;
  fgets(newline, sizeof(newline), STDIN);
  char*shm;
  char* s;
  shm = shmat(mem, 0, 0);
  s = shm;
  *s = newline;
  FILE *f = fopen("file", "w");
  fprintf("%s\n", newline);
  fclose(f);
  
  
}
