#include "processQueue.h"

//function to create an empty queue
Queue* createQueue() { 
    
    //allocate space for the queue
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    
    //initialize queue
    queue->front = queue->rear = NULL; 
    queue->size = 0;
    
    return queue; 
}

//function to create a node containing a duration value
Node* createNode(Queue* queue, int value) {
    
    Node *newNode;

    newNode = (Node*) malloc(sizeof(Node));

    newNode->duration = value;
    newNode->name = ++(queue->size);

    newNode -> next = NULL;

    return newNode;
}

//function to add a node to the queue, first allocating space, then calling function enqueueNode
void enQueue(Queue *queue, int value) {
    
    Node *newNode = createNode(queue, value);
    
    enQueueNode(queue, newNode);
}

//function to add a node to the queue
void enQueueNode(Queue *queue, Node* newNode) {
   
    if (queue->front == NULL) {

        queue->front = queue->rear = newNode;
    }
    
    else {

        queue->rear -> next = newNode;
        queue->rear = newNode;
        newNode->next = NULL;
   }
}

//function to enque nodes in a sorted fashion by their duration times
void sortedEnqueueNode(Queue *queue, Node* newNode) {

    if (queue->front == NULL) {
        
        queue->front = queue->rear = newNode;
    }
    
    else {
        
        Node *temp = queue->front;
        Node *previousNode = NULL;
        
        while (temp != NULL) 
            
            if (temp->duration <= newNode->duration) {
                
                previousNode = temp;
                temp = temp->next;
            }
            
            else {
                
                break;
            }
            

        if (temp ==  NULL) {
            
            queue->rear -> next = newNode;
            queue->rear = newNode;
        } 

        else if (previousNode == NULL) {
            
            newNode->next = temp;
            queue->front = newNode;

        } 
        
        else {

            previousNode->next = newNode;
            newNode->next = temp;
        }
   }

}

//function to remove the first node in the queue
Node* deQueue(Queue *queue) {

    Node *temp = NULL;

    if(queue->front == NULL) {

        printf("\nUnable to deQueue empty queue\n");
    }

    else {
      
        temp = queue->front;
      
        queue->front = queue->front -> next;

   }
   return temp;

}

//function to display the contents of the queue
void display(Queue *queue) {
   
    if(queue->front == NULL) {

        printf("\nUnable to display contents of empty queue\n");
    }

    else {

        Node *temp = queue->front;
    
        while (temp != NULL) {
        
            printf("%d--->",temp->duration);
            temp = temp -> next;
        }
      
        printf("NULL\n");
    }
}

//function to parse each line read from the cpu_scheduling_input_file,
//enqueue nodes with duration time
void buildQueue(Queue *queue ,char line[]) {

    char *ch = NULL;
    ch = strtok(line, " ");

    int i = 0;

    while (ch != NULL) {
        ch = strtok(NULL, " ");
        
        if (i < 3){
            
            ++i;
            
            if (i == 1) {

                queue->queueIndex = atoi(ch);
            }

            if (i == 3) {

                queue->timeQuantum = atoi(ch);
            }

        } 
        
        else if (ch != NULL){ 

                ch = strtok(NULL, " ");

                enQueue(queue, atoi(ch));
            }
    }
}

//function to sort a given queue by duration times
Queue *sortQueue(Queue *queue) {

    Node *temp = queue->front;
    
    Queue *newQueue = createQueue();

    newQueue->queueIndex = queue->queueIndex;
    newQueue->timeQuantum = queue->timeQuantum;
    
    while (temp != NULL) {

        Node *node = createNode(newQueue, temp->duration);

        sortedEnqueueNode(newQueue, node);
    
        temp = temp->next;
    }

    return newQueue; 
}

//function to free space allocated to the given queue and it's nodes
void freeQueueSpace(Queue* queue) {

    while (queue->front != NULL) {
        Node *temp = deQueue(queue);
        free(temp);
    }

    free(queue);
}