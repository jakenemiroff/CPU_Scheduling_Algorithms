#include "processQueue.h"

//function implementing the first come first serve algorithm
void firstComeFirstServe(Queue *queue, FILE *fp) {

    Node *temp = queue->front;

    int waitingTime = 0;
    float totalWaitingTime = 0;

    int denominator = queue->size;

    fprintf(fp, "Ready Queue %d Applying FCFS Scheduling:\n\n", queue->queueIndex);

    fprintf(fp, "Order of selection by CPU:\n");

    printf("Ready Queue %d Applying FCFS Scheduling:\n\n", queue->queueIndex);

    printf("Order of selection by CPU:\n");

    while (temp != NULL) {

        fprintf(fp, "p%d ", temp->name);

        printf("p%d ", temp->name);

        temp = temp->next;
    }

    fprintf(fp, "\n");
    fprintf(fp, "\n");
    
    printf("\n");
    printf("\n");

    temp = queue->front;

    fprintf(fp, "Individual waiting times for each process:\n");
    
    printf("Individual waiting times for each process:\n");
    
    while (temp != NULL) {

        fprintf(fp, "p%d = %d\n", temp->name, waitingTime);
        
        printf("p%d = %d\n", temp->name, waitingTime);

        totalWaitingTime += waitingTime;
        waitingTime += temp->duration;

        temp = temp->next;
    }

    float averageWaitingTime = totalWaitingTime / denominator;

    fprintf(fp,  "\n");
    fprintf(fp, "Average waiting time for Queue %d: %0.1f\n", queue->queueIndex, averageWaitingTime);
    fprintf(fp, "\n");

    printf("\n");
    printf("Average waiting time for Queue %d: %0.1f\n", queue->queueIndex, averageWaitingTime);
    printf("\n");
}

//function implementing the shortest job first algorithm
void shortestJobFirst(Queue *queue, FILE *fp) {

    Queue *sortedQueue = sortQueue(queue);

    Node *temp = sortedQueue->front;

    int waitingTime = 0;
    float totalWaitingTime = 0;

    int denominator = sortedQueue->size;

    fprintf(fp, "Ready Queue %d Applying SJF Scheduling:\n\n", sortedQueue->queueIndex);

    fprintf(fp, "Order of selection by CPU:\n");
    
    printf("Ready Queue %d Applying SJF Scheduling:\n\n", sortedQueue->queueIndex);

    printf("Order of selection by CPU:\n");

    while (temp != NULL) {

        fprintf(fp, "p%d ", temp->name);
        printf("p%d ", temp->name);

        temp = temp->next;
    }

    fprintf(fp, "\n");
    fprintf(fp, "\n");
    printf("\n");
    printf("\n");

    temp = sortedQueue->front;

    fprintf(fp, "Individual waiting times for each process:\n");
    printf("Individual waiting times for each process:\n");
    
    while (temp != NULL) {

        fprintf(fp, "p%d = %d\n", temp->name, waitingTime);
        printf("p%d = %d\n", temp->name, waitingTime);

        totalWaitingTime += waitingTime;
        waitingTime += temp->duration;

        temp = temp->next;
    }

    float averageWaitingTime = totalWaitingTime / denominator;

    fprintf(fp, "\n");
    fprintf(fp, "Average waiting time for Queue %d: %0.1f\n", sortedQueue->queueIndex, averageWaitingTime);
    fprintf(fp, "\n");
    
    printf("\n");
    printf("Average waiting time for Queue %d: %0.1f\n", sortedQueue->queueIndex, averageWaitingTime);
    printf("\n");

    freeQueueSpace(sortedQueue);
}

//helper function to determine whether a given node is in a given array
//will return that node if it exists else returning null
Node * arrayContainsNode(Node * arr, int index, int name){
    
    for (int i = 0; i < index; i++) {

        if (arr[i].name == name)
            
            return &arr[i];
    }

    return NULL;
}

//helper function to determine whether a given no is in a given queue
bool queueContainsNode(Queue * queue, Node * node) {
    
    Node * temp = queue->front;
    
    while (temp != NULL) {
    
        if (temp == node) {

            return true;
        }
        
        temp = temp->next;
    }

    return false;
}

//function to implement the round robin algorithm
void roundRobin(Queue *queue, FILE *fp) {
    
    Queue *roundRobinQueue = createQueue();
    Node overTimeQuantum[queue->size];

    int index = 0;

    fprintf(fp, "Ready Queue %d Applying RR Scheduling:\n\n", queue->queueIndex);
    printf("Ready Queue %d Applying RR Scheduling:\n\n", queue->queueIndex);

    fprintf(fp, "Order of selection by CPU:\n");
    printf("Order of selection by CPU:\n");

    //make sure queue is not empty
    while (queue->front != NULL) {

        Node *temp = deQueue(queue);
        int wait;
        
        fprintf(fp, "p%d ", temp->name);
        printf("p%d ", temp->name);

        //section to handle case where duration of node is less than time quantum
        if (temp->duration <= queue->timeQuantum) {
            
            wait = temp->duration;
            
            Node *isin = arrayContainsNode(overTimeQuantum, index, temp->name);
            
            if (isin == NULL) {

                enQueueNode(roundRobinQueue, temp);
            }

            else {

                isin->duration += wait;
                enQueueNode(roundRobinQueue, isin);
            }
        } 
        
        //section to handle case where duration of node is greater than time quantum
        else {
            
            temp->duration = temp->duration - queue->timeQuantum;
            wait = queue->timeQuantum;
            
            Node * isin = arrayContainsNode(overTimeQuantum, index, temp->name);
            
            if(isin == NULL){
            
                overTimeQuantum[index].duration = 0;
                overTimeQuantum[index].next = NULL;
                overTimeQuantum[index++].name = temp->name;
            }

            enQueueNode(queue, temp);
        }

        //used to calculate the turnaround time
        for (int i = 0; i < index; i++) {

            if (!queueContainsNode(roundRobinQueue, &overTimeQuantum[i]))  {
                
                overTimeQuantum[i].duration += wait;
            }
        }   
    }

    fprintf(fp, "\n\nTurnaround times for each process: \n");
    printf("\n\nTurnaround times for each process: \n");

        Node * temp = roundRobinQueue->front;
        
        while(temp != NULL){
            
            fprintf(fp, "p%d = %d\n", temp->name, temp->duration);
            printf("p%d = %d\n", temp->name, temp->duration);
            
            temp = temp->next;
        }
    
    free(roundRobinQueue);
    fprintf(fp, "\n");       
    printf("\n");       
}

//main function used to simulate the three algorithms above
int main (int argc, char* argv[]) {

  	if (argc != 2) {

		printf("invalid number of arguments\n");
		exit(1);
	}

	else {

		char const* const inputFileName = argv[1];

        char const* const outputFileName = "cpu_scheduling_output_file.txt";
    
		FILE *inputFile = fopen(inputFileName, "r");

		if (inputFile == NULL) {
			
            perror("failed to open file");
			exit(1);
		}

        //originally open output file for writing
        FILE *outputFile = fopen(outputFileName, "w");

        if (outputFile == NULL) {
            
            perror("failed to open file for writing");
        }
        
 		char line[256]; //assuming the length of a line in the input file is no greater than 256

		while (fgets(line, sizeof(line), inputFile)) {

            Queue *queue = createQueue();

            buildQueue(queue, line);

            firstComeFirstServe(queue, outputFile);

            shortestJobFirst(queue, outputFile);

            roundRobin(queue, outputFile);

            freeQueueSpace(queue);

            fclose(outputFile);

            //after text has been added, open output fle for appending
            outputFile = fopen(outputFileName, "a");
		}
        
        fclose(outputFile);

		fclose(inputFile);
	}
	   
	return 0;
}
