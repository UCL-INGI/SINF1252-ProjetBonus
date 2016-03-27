typedef struct semProcess {
    pthread_mutex_t mutex;
    struct semProcess next;
} sem_process_t;

typedef struct mySem {
    int value;
    int capacity;
    sem_process_t *head;
} mysem_t;

int mysem_init(mysem_t *sem, unsigned int value);
int mysem_wait(mysem_t *sem);
int mysem_post(mysem_t *sem);
int mysem_close(mysem_t *sem);
