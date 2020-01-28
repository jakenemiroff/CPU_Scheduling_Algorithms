#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

//declare and assign global variables
int x = 20, y = 10, z = 0;

//create function to add x and y and store the result in z
//to be used by the thread
void* add() {
	
	z = x + y;

	return NULL;
}

int main()  {

	//declare pid which will be used by fork
    pid_t pid;
	
	//create process
	pid = fork();
	
	if (pid < 0) {
		
		printf("fork unsuccessful");
		exit(1);
	}

	//if pid is equal to 0, it is a child process
	if (pid == 0) {
		
		//execute sum of x and y, store result in z
        z = x + y;
	}

	//if pid is greater than 0, it is a parent process
	if (pid > 0) {
		
		//wait for child to execute
        wait(NULL);

        printf("in parent process, the value of z is: %d\n", z);
		
		//define a thread id
		pthread_t tid;
		
		//create thread using tid and void* function above
		pthread_create(&tid, NULL, add, NULL);
		
		//wait for thread to terminate
		pthread_join(tid, NULL);
			
		printf("in parent after thread, the value of z is: %d\n", z);
	}	
}
