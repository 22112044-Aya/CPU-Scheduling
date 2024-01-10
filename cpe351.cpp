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


int simulatorMainMenu();
int schedulingMethods();
void diplayOutput();
struct node *createNode(double, double double);
void insertAfter(struct node *,double, double, double);
struct node *FCFS(struct node *);
struct node *SJFNonPreemptive(struct node *);
void swap(struct node *,struct node *);
struct node *SJFPreemptive(struct node *, struct node *);
struct node *priorityNonPreemptive(struct node *);
struct process * readFromFile(struct process *);
void writeToFile();

// this variable will be used to count the number of processes
int countP = 0;
char method;
char mode;
int quantum;
int methodChoosen;

//Menu 
 int simulatorMainMenu() {
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
    cout << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
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

void swap(struct node *currentNode,struct node *nextNode) 
{
   
    double tempburstTm;
    double temparrivalTm;
    double temppriority;

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
struct process * readFromFile(struct process *header)
{
    ifstream inputFile(argv[2]);
    if (!inputFile.is_open())
    {
        cout<< "The input file cannot open "<< endl;
        return 1;
    }
    
    struct process* process=NULL;
    char line[2000];
    int x= count(process);
    while (getline(inputFile, line) != NULL)
    {
        int y[5];
        istringstream iss(line);
        iss >> y[0] >> y[2] >> y[4];

        process = insertAfter(process,x,, y[0], y[2] ,y[4]);
        x++;
    } 
    inputFile.close();
	return header;  
}

struct node *FCFS(struct node *currentNode) 
{
    //First we will sort the Arrival time, the process that has the least arrival time is executed first
    struct node *nextNode = NULL;
    double completionTm = 0;
    double waitingTm = 0;
        while (currentNode != NULL) 
        {
            nextNode = currentNode->next;
            while (nextNode != NULL) 
            {
                //If the currentNode arrival time is greater than nextNode arrival time, we will swap the processes
                if (currentNode->arrivalTm > nextNode->arrivalTm) 
                {
                    //swap processes
			        swap(currentNode,nextNode);
                }
                //Move to the next node in the list
                nextNode = nextNode->next;
            }

            //calculate the waiting time
            completionTm += currentNode->burstTm;
            waitingTm = completionTm - currentNode->arrivalTm - currentNode->burstTm;
            //Move to the next node in the list
            currentNode = currentNode->next;
        }
        else if(currentNode == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

    
}
struct node *SJFNonPreemptive(struct node *currentNode)
{
    struct node *nextNode = NULL;
    double completionTm = 0;
    double waitingTm = 0;  
    if (currentNode != NULL) 
        {
            nextNode = currentNode->next;
            if (nextNode != NULL) 
            {
                //If the currentNode burst time is greater than nextNode burst time, we will swap the processes
                if (currentNode->burstTm > nextNode->burstTm) 
                {
                    //swap processes
                        swap(currentNode,nextNode);
                }
                // if both processes have the same burst time, we will perform FCFS
                else if(currentNode->burstTm == nextNode->burstTm)
                {
                    FCFS(currentNode);
                }
                //Move to the next node in the list
                nextNode = nextNode->next;
            }
            //calculate the waiting time
            completionTm += currentNode->burstTm;
            waitingTm = completionTm - currentNode->arrivalTm - currentNode->burstTm;

            //Move to the next node in the list
            currentNode = currentNode->next;
        }
        else if(currentNode == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

}
struct node *SJFPreemptive(struct node *currentNode, struct node *header)
 {
    struct node *nextNode = NULL;
    struct node *processWaitingList = NULL;
    struct node *processWaitingListCurrentNode = NULL;
    struct node *previousNode = NULL;

    while (currentNode != NULL) 
    {
        nextNode = currentNode->next;

        if (nextNode != NULL) 
        {
            // If the process that arrived recently has a shorter burst time than the currently running process,
            // allocate the CPU to the newly arrived process, and the currently running process will wait in the process waiting list
            if (nextNode->burstTm < currentNode->burstTm) 
            {
                if (processWaitingList == NULL) 
                {
                    processWaitingList = currentNode;
                    processWaitingList->next = NULL;
                } 
                else 
                {
                    processWaitingListCurrentNode = processWaitingList;
                    while(processWaitingListCurrentNode->next != NULL) 
                    {
                        processWaitingListCurrentNode = processWaitingListCurrentNode->next;
                    }
                    processWaitingListCurrentNode->next = currentNode;
                    currentNode->next = NULL;
                }
                
                // update the process waiting list
                if (previousNode == NULL) 
                {
                    header = nextNode;
                } 
                else 
                {
                    previousNode->next = nextNode;
                }
                nextNode->next = NULL;
            }
        } 
        else 
        {
            // update the remaining burst time of the process
            currentNode->burstTm -= nextNode->burstTm;
        }
        previousNode = currentNode;
        currentNode = nextNode;
    }

    if(currentNode == NULL)
    {
        cout<<"The list is empty"<<endl;
    }

}

struct node *priorityNonPreemptive(struct node *currentNode)
 {
    struct node *nextNode = NULL;
    double completionTm = 0;
    double waitingTm = 0;

    if (currentNode != NULL) 
    {
        while (currentNode != NULL) 
        {
            nextNode = currentNode->next;
            if (nextNode != NULL) 
            {
                // If the currentNode priority is greater than nextNode priority, we will swap the processes
                if (currentNode->priority > nextNode->priority) 
                {
                    swap(currentNode, nextNode);
                } 
                else if (currentNode->priority == nextNode->priority) 
                {
                    // If both processes have the same priority,we will perform FCFS
                    FCFS(currentNode);
                }    
                // Move to the next node in the list
                nextNode=nextNode->next;
            }
            //calculate the waiting time
            completionTm += currentNode->burstTm;
            waitingTm = completionTm - currentNode->arrivalTm - currentNode->burstTm;
            
            //Move to the next node in the list
            currentNode = currentNode->next;
        }
    } 
    else if(currentNode == NULL)
        {
            cout<<"The list is empty"<<endl;
        }
}

void writeToFile()
{
	ofstream writeFile("output.txt");

	if (!writeFile) 
    {
		writeFile.open("output.txt");
		writeFile <<displayOutput()<<endl;
		
		writeFile.close(); 
	}
	else 
    {
		writeFile <<diplayOutput()<<endl;
		writeFile.close(); 
	}
}

int main
{ 
    int choice1;
    int choice2;
    int a=0;
    int x;
    int y;

    while (a==0)
    {    
        cout <<"           "<< "CPU Scheduler Simulator"<<"             "<<endl;
        cout << "1) Scheduling Method (" <<method<< ")" <<endl;
        cout << "2) Preemptive Mode (" <<mode<< ")" << endl;
        cout << "3) Show result" <<endl;
        cout << "4) End program" <<endl;
        cout << "Option > ";
        cin >> choice1;
        
        switch(choice1)
        {
            case 1:
            {
               cout <<"           "<< "CPU Scheduling Methods"<<"             "<<endl;
               cout << "1) None: None of scheduling method chosen " <<endl;
               cout << "2) First Come, First Serve Scheduling " <<endl;
               cout << "3) Shortest-Job-First Scheduling" <<endl;
               cout << "4) Priority Scheduling" <<endl;
               cout << "5) Round-Robin Scheduling" <<endl;
               cout << "Choose One Of The Following Scheduling Methods: "<<endl;
               cin >> choice2;
               switch(choice2)
               {
                  case 1:
                  {
                    method = "NONE";         
                  }
                  break;
                        
                  case 2:
                  {
                    FCFS(currentNode);
                    methodChoosen = FCFS(currentNode);
                    method = "FCFS";
                  }
                  break; 
                  case 3:
                  {
                     cout<<"1-> Non Preemtive" << endl;
		     cout<<"2-> Preemtive"<< endl;
	             cout<<"Choose the method you would like yo use for SJF : ";
		     cin>>x;	
		     switch(x)
		     {
		  	case 1:
		  	{
		     	    SJFNonPreemptive(currentNode);
                     	    methodChoosen = SJFNonPreemptive(currentNode);
                     	    method = "SJF";                    
		  	}
		  	break;
		  	case 2:
		  	{
		     	    SJFPreemptive(currentNode);	
                     	    methodChoosen = SJFPreemptive(currentNode);		
                     	    method = "SJF";          				
		  	}
		  	break;
                  	default:
                  	cout<<"choose one of the above methods"<<endl;
                  	break;
                     }
         	 }
                 break;  
                 case 4:
                 {
                 	cout<<"1-> Non Preemtive" << endl;
			cout<<"2-> Preemtive"<< endl;
			cout<<"Choose the method you would like yo use for Priority : ";
			cin>>y;	
			switch(y)
			{
				case 1:
				{
				    priorityNonPreemptive(currentNode);
                                    methodChoosen = priorityNonPreemptive(currentNode);
                                    metod = "Priority";
                                }
				break;
				case 2:
				{
				    SJFPreemptive(currentNode);	
                                    methodChoosen = priorityPreemptive(currentNode);		
                                    method = "Priority";                 				
				}
				break;
                                default:
                                cout<<"choose one of the above methods"<<endl;
                                break;
                        }
                  }
                  break;
                  case 5:
                  {
                     cout<<"Enter the value of the quantum: ":
                     cin>>quantum;
                     roundRobin(currentNode);
                     method = roundRobin(currentNode);
                     method = "Round Robin";   
                  }
                  break;
                  default:
                  cout<<"choose a number between 1 and 5";
                  break;
                  }
            }
            break;
            case 2:
            {
                if(methodChoosen=FCFS(currentNode))
                {
                    mode = "OFF";
                }
                if(methodChoosen=SJFNonPreemptive(currentNode))
                {
                    mode = "OFF";
                }
                if(methodChoosen=SJFPreemptive(currentNode))
                {
                    mode = "ON";
                }
                if(methodChoosen=priority(currentNode))
                {
                    mode = "OFF";
                }
                if(methodChoosen=priorityPreemptive(currentNode))
                {
                    mode = "ON";
                }
                cout<<"The mode is "<<mode<<endl;
               
            }
            break;

            case 3:
            {
                //show result
            }
            break;

            case 4:
            {
                exit(0);
            }
            break;
            
            default:
            cout<<"choose a valid number between 1 and 4";
            break;

        }
    }
}
