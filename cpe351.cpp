#include <iostream>
using namespace std;

// I defined the process. Because the process has a burst time, arrival time and priority, 
// I created a structure to hold these data under the process
 struct process
 {
    double burstTm;
    double arrivalTm;
    double priority;
 };
// linked list node to store process information
struct node {
    process data;
    struct node* next;
};


int simulatorMainMenu(string ,string);
int schedulingMethods();
void diplayOutput(string ,string);
struct node *createNode(double, double double);
void insertAfter(struct node *,double, double double);
struct node *FCFS(struct node *);

// this variable will be used to count the number of processes
int countP = 0;
//Menu 
 int simulatorMainMenu(string method, string mode) {
    int choice1;
    cout <<"           "<< "CPU Scheduler Simulator"<<"             "<<endl;
    cout << "1) Scheduling Method (" <<method<< ")" <<endl;
    cout << "2) Preemptive Mode (" <<mode<< ")" << endl;
    cout << "3) Show result" <<endl;
    cout << "4) End program" <<endl;
    cout << "Option > ";
    cin >> choice1;
    return choice1;
}

int schedulingMethods() {
    int choice2;
    cout <<"           "<< "CPU Scheduling Methods"<<"             "<<endl;
    cout << "1) None: None of scheduling method chosen " <<endl;
    cout << "2) First Come, First Serve Scheduling " <<endl;
    cout << "3) Shortest-Job-First Scheduling" <<endl;
    cout << "4) Priority Scheduling" <<endl;
    cout << "5) Round-Robin Scheduling" <<endl;
    cout << "Choose One Of The Following Scheduling Methods: "<<endl;
    cin >> choice2;
    return choice2;
}
void diplayOutput(method, mode) {
    cout << "Scheduling Method: " << method << " - " << mode <<endl;
    cout << "Process Waiting Times:" <<endl;

    // the following loop will display the waiting time for each process
    for (int i = 0; i < countP; i++) 
    {
    cout << "P" << i + 1 << ": " << waitingTm << " ms" <<endl;
    }
    // To calculate the average waiting time, we first have to find the total waiting time
    double totalWaitingTm = 0;
    for (int i = 0; i < countP; i++) 
    {
        totalWaitingTM += waitingTm;
    }
    double avgWaitingTm = totalWaitingTm / countP;
    cout << "Average Waiting Time: " << avgWaitingTm << " ms" <<endl;
 }
//create a new node that will represent the creation of a new process in the linked list
struct node *createNode(double burstTm, double arrivalTm, double priority) {
    struct node *temp = (struct node *) malloc(sizeof(node));
    if(temp != NULL)
    {
    temp->burstTm = burstTm;
    temp->arrivalTm = arrivalTm;
    temp->priority = priority;
    temp->next = NULL;
    }
    return temp;
}

//function to insert a process into the linked list
void insertAfter(struct node *afterNode,double burstTm, double arrivalTm, double priority )
{
     struct node * temp = createNode(burstTm,arrivalTm,priority);
     temp->next = afterNode->next;
     afterNode->next = temp;
     countP++;
}
struct node *FCFS(struct node *currentNode) 
{
    //First we will sort the Arrival time, the process that has the least arrival time is executed first
    struct node *nextNode = NULL;
    double tempburstTm;
    double temparrivalTm;
    double temppriority;
        if (currentNode != NULL) 
        {
            nextNode = currentNode->next;
            if (nextNode != NULL) 
            {
                //If the currentNode arrival time is greater than nextNode arrival time, 
                //we will swap the processes, meaning we have to swap the burst time, arrival time and priority
                if (currentNode->arrivalTm > nextNode->arrivalTm) 
                {
                    //swap burst time
                    tempburstTm = currentNode->burstTm;
                    currentNode->burstTm = nextNode->burstTm;
                    nextNode->burstTm = tempburstTm;
                    //swap arrival time
                    temparrivalTm = currentNode->arrivalTm;
                    currentNode->arrivalTm = nextNode->arrivalTm;
                    nextNode->arrivalTm = temparrivalTm;
                    //swap priority
                    temppriority = currentNode->priority;
                    currentNode->priority = nextNode->priority;
                    nextNode->priority = temppriority;

                }
                //Move to the next node in the list
                nextNode = nextNode->next;
            }
            //Move to the next node in the list
            currentNode = currentNode->next;
        }
        else if(currentNode == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

        //calculate the waiting time
        double waitingTM = 0;
        waitingTm += currentNode->burstTm;

}
