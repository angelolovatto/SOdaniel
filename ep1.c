# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unist.h>


# define QUANTUM 1

typedef struct {
    double t0;
    char nome[128];
    double dt;
    double deadline;
} processo;



FILE *in;
FILE *out;
processo *listaproc;
int N = 2;
int size = 0;
pthread_mutex_t mutex;

void FCFS () {
	int i;
	clock_t tf, tini;
	pthread_t procs[];
	pthread_mutex_init(&mutex, NULL);

	procs = malloc (sizeof (pthread_t) * size);

	for (i = 0; i < size; i++) {
		pthread_create (&procs[i], NULL, lostimeFCFS, listaproc[i].dt);
		pthread_join(procs[i], NULL);
		tf = clock ();
		fprintf (out, "%s", listaproc[i].nome);
		fprintf(out, " %lf", tf);
		fprintf(out, "%lf\n", tf - listaproc[i].t0);
	}

	pthread_exit (NULL);
	pthread_mutex_destroy(&mutex);
	    
}

void lostimeFCFS (double time) {
	double i = 0;

	while (i < time) {
		pthread_mutex_lock (&mutex);
		sleep (QUANTUM);
		i = i + QUANTUM;
		pthread_mutex_unlock (&mutex);
	}
}

void redimensiona () {
    N *= 2;
    listaproc = realloc (listaproc, N * sizeof (processo));
}

void readFile () {
    listaproc = malloc (N * sizeof (processo));
    
    while (fscanf (in, "%lf %s %lf %lf", &listaproc[size].t0, listaproc[size].nome, &listaproc[size].dt, &listaproc[size].deadline) != 0) {
        size++;
        if (size == N) redimensiona ();
    }

}

int main (int argc, char **argv) {
    int escalonador = atoi (argv[1]);
    char *entrada   = argv[2];
    char *saida     = argv[3];
    
    in = fopen (entrada, "r");
    out = fopen (saida, "w");

    readFile ();

    switch (escalonador) {
        case 1:
            FCFS ();
    }

    return 0;
}
