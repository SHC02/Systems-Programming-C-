/*
 * @author Sehyun Cho
 * Panther ID: 6284494
 * 
 * I affirm that I wrote this program myself without any help from other people
 * or sources from the internet.
 *
 * This program will provide a multithread solution to the circuit-satisfiability
 * problem which will compute for what combinations of input values will the circuit
 * output the value 1.
 * Creating 6 threads and divide the 65536 test cases among them.
 * For example, if p = 6, each thread would be responsible for roughly 65336/6 number of
 * iterations.
 * The test cases must be allocated in a cyclic fashion one by one.
 * If a thread finds a combination that satisfies the circuit, it should print out
 * the combination, along with the thread id(0~5).
 * In the end, the main thread should print out the total number of combinations that
 * satisfy this circuit.
 * Mutex should be used to update the total by each thread.
 */

// Import headers
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

//declare  number of thread as 6	
#define NUM_THREADS 6

// declaration of sharables
pthread_mutex_t lock_x;
int count = 0;

// declare thread structure
typedef struct _thread_data_t
{
	int tid;
}thread_data_t;

//check circuit function
int check_circuit (int id, int z) {
  int v[16];        /* Each element is a bit of z */
  int i;

  for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);
  if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) {
    printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", id,
	    v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
	    v[10],v[11],v[12],v[13],v[14],v[15]);
 
    return 1;
  } else return 0;
}

void *thr_func(void *arg)
{
	// declare variables 
	int p = 6;
	int i;
	thread_data_t *data = (thread_data_t *)arg;

	// Meet the condition of 65536/6 iterations 
	for(i = data -> tid; i < 65536; i+= p)
	{
		// get mutex before modifying count
		// update mutex each thread
		pthread_mutex_lock(&lock_x);
		count += check_circuit(data -> tid, i);
		pthread_mutex_unlock(&lock_x);
	}
	pthread_exit(NULL);
}

// Main function
int main (int argc, char *argv[])
{
  // Declare varaibles
  int i;
  int rc;
  pthread_t thr[NUM_THREADS];
  thread_data_t thr_data[NUM_THREADS];

  // initialize mutex protecting 'count'
  pthread_mutex_init(&lock_x, NULL);

  // create threads
  for(i = 0; i < NUM_THREADS; i++)
  {
	  // get tid as iterating, thread id is number between 0 and 5(p-1)
	  thr_data[i].tid = i;

	  // coverage as if errors occur
	  if((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i])))
	  {
		  fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
		  return EXIT_FAILURE;
	  }
  }

  // blocking until all threads work complete
  for(i = 0; i < NUM_THREADS; i++)
  {
	  pthread_join(thr[i], NULL);
  }

  //print solutions
  printf ("There are %d solutions\n", count);
  
  // end program with success
  return EXIT_SUCCESS;
}
