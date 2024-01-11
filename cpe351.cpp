#include <iostream>
include<string>
include<fstream>
#include <sstream>
using namespace std;

// I defined the process. Because the process has a burst time, arrival time and priority, 
// I created a structure to hold these data under the process
 struct process
 {
    int index;
    double burstTm;
    double arrivalTm;
    double priority;
    struct process* next;
 };

int simulatorMainMenu();
int schedulingMethods();
void diplayOutput();
struct process *createprocess(int,double, double, double);
void insertBack(struct process *,int,double, double, double);
struct process *FCFS(struct process *);
struct process *SJFNonPreemptive(struct process *);
void swap(struct process *,struct process *);
struct process *SJFPreemptive(struct process *, struct process *);
struct process *priorityNonPreemptive(struct process *);
int count(struct process *);
struct process * readFromFile(struct process *);
void writeToFile();

struct process *methodChoosen = NULL;
// this variable will be used to count the number of processes
int countP = 0;
string method;
string mode;
int quantum;


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
void diplayOutput() {
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

void swap(struct process *currentprocess,struct process *nextprocess) 
{
   
    double tempburstTm;
    double temparrivalTm;
    double temppriority;
    int tempindex;

    //swap process index
    tempindex = currentprocess->index;
    currentprocess->index = nextprocess->bindex;
    nextprocess->index = tempindex;
    //swap burst time
    tempburstTm = currentprocess->burstTm;
    currentprocess->burstTm = nextprocess->burstTm;
    nextprocess->burstTm = tempburstTm;
    //swap arrival time
    temparrivalTm = currentprocess->arrivalTm;
    currentprocess->arrivalTm = nextprocess->arrivalTm;
    nextprocess->arrivalTm = temparrivalTm;
    //swap priority
    temppriority = currentprocess->priority;
    currentprocess->priority = nextprocess->priority;
    nextprocess->priority = temppriority;
}

//function to count processes
int count(struct process *currentprocess)
{
	int p=0;
	while(currentprocess!=NULL)
	{
		p++;
		currentprocess=currentprocess->next;
	}
	return p;	
}
//create a new process that will represent the creation of a new process in the linked list
struct process *createprocess(int index,double burstTm, double arrivalTm, double priority) {
    struct process *temp = (struct process *) malloc(sizeof(process));
    if(temp != NULL)
    {
        temp->index = index;
        temp->burstTm = burstTm;
        temp->arrivalTm = arrivalTm;
        temp->priority = priority;
        temp->next = NULL;
    }
    return temp;
}

//function to insert a process into the linked list
void insertBack(struct process *header,int index, double burstTm, double arrivalTm, double priority )
{
    struct process *temp = createprocess(index,burstTm,arrivalTm,priority);
    struct process *headertemp;
    if (header == NULL)
    {
        header = temp;
        return header;
    }
    headertemp=header;

    while(headertemp->next != NULL)
        headertemp=headertemp->next;
    headertemp->next = temp;
    return header;
}
struct process *FCFS(struct process *currentprocess) 
{
    //First we will sort the Arrival time, the process that has the least arrival time is executed first
    struct process *nextprocess = NULL;
    double completionTm = 0;
        while (currentprocess != NULL) 
        {
            nextprocess = currentprocess->next;
            while (nextprocess != NULL) 
            {
                //If the currentprocess arrival time is greater than nextprocess arrival time, we will swap the processes
                if (currentprocess->arrivalTm > nextprocess->arrivalTm) 
                {
                    //swap processes
			        swap(currentprocess,nextprocess);
                }
                //Move to the next process in the list
                nextprocess = nextprocess->next;
            }

            //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            sum += waitingTM;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
        }
        if (count(currentprocess) != 0)
        {
            avgTm= sum/count(currentprocess);
        }
        else 
        {
            avgTm = 0;
        }
        if(currentprocess == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

    
}
struct process *SJFNonPreemptive(struct process *currentprocess)
{
    struct process *nextprocess = NULL;
    double completionTm = 0;
 
    while (currentprocess != NULL) 
        {
            nextprocess = currentprocess->next;
            while (nextprocess != NULL) 
            {
                //If the currentprocess arrival time is greater than nextprocess arrival time, we will swap the processes
                if (currentprocess->arrivalTm > nextprocess->arrivalTm) 
                {
                    //swap processes
			        swap(currentprocess,nextprocess);
                }
                //Move to the next process in the list
                nextprocess = nextprocess->next;
            }

            //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            sum += waitingTM;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
        }
    while (currentprocess != NULL) 
        {
            nextprocess = currentprocess->next;
            if (nextprocess != NULL) 
            {
                //If the currentprocess burst time is greater than nextprocess burst time, we will swap the processes
                if (currentprocess->burstTm > nextprocess->burstTm) 
                {
                    //swap processes
                        swap(currentprocess,nextprocess);
                }
                //Move to the next process in the list
                nextprocess = nextprocess->next;
            }
             //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            sum += waitingTM;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
        }
        if (count(currentprocess) != 0)
        {
            avgTm= sum/count(currentprocess);
        }
        else 
        {
            avgTm = 0;
        }
        if(currentprocess == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

}
struct process *SJFPreemptive(struct process *currentprocess, struct process *header)
 {
    struct process *nextprocess = NULL;
    struct process *processWaitingList = NULL;
    struct process *processWaitingListCurrentprocess = NULL;
    struct process *previousprocess = NULL;

    while (currentprocess != NULL) 
    {
        nextprocess = currentprocess->next;

        if (nextprocess != NULL) 
        {
            // If the process that arrived recently has a shorter burst time than the currently running process,
            // allocate the CPU to the newly arrived process, and the currently running process will wait in the process waiting list
            if (nextprocess->burstTm < currentprocess->burstTm) 
            {
                if (processWaitingList == NULL) 
                {
                    processWaitingList = currentprocess;
                    processWaitingList->next = NULL;
                } 
                else 
                {
                    processWaitingListCurrentprocess = processWaitingList;
                    while(processWaitingListCurrentprocess->next != NULL) 
                    {
                        processWaitingListCurrentprocess = processWaitingListCurrentprocess->next;
                    }
                    processWaitingListCurrentprocess->next = currentprocess;
                    currentprocess->next = NULL;
                }
                
                // update the process waiting list
                if (previousprocess == NULL) 
                {
                    header = nextprocess;
                } 
                else 
                {
                    previousprocess->next = nextprocess;
                }
                nextprocess->next = NULL;
            }
        } 
        else 
        {
            // update the remaining burst time of the process
            currentprocess->burstTm -= nextprocess->burstTm;
        }
        previousprocess = currentprocess;
        currentprocess = nextprocess;
    }

    if(currentprocess == NULL)
    {
        cout<<"The list is empty"<<endl;
    }

}

struct process *priorityNonPreemptive(struct process *currentprocess)
{
    struct process *nextprocess = NULL;
    double completionTm = 0;
 
    while (currentprocess != NULL) 
        {
            nextprocess = currentprocess->next;
            while (nextprocess != NULL) 
            {
                //If the currentprocess arrival time is greater than nextprocess arrival time, we will swap the processes
                if (currentprocess->arrivalTm > nextprocess->arrivalTm) 
                {
                    //swap processes
			        swap(currentprocess,nextprocess);
                }
                //Move to the next process in the list
                nextprocess = nextprocess->next;
            }

            //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            sum += waitingTM;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
        }
    while (currentprocess != NULL) 
        {
            nextprocess = currentprocess->next;
            if (nextprocess != NULL) 
            {
                //If the currentprocess burst time is greater than nextprocess burst time, we will swap the processes
                if (currentprocess->priority > nextprocess->priority) 
                {
                    //swap processes
                        swap(currentprocess,nextprocess);
                }
                //Move to the next process in the list
                nextprocess = nextprocess->next;
            }
             //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            sum += waitingTM;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
        }
        if (count(currentprocess) != 0)
        {
            avgTm= sum/count(currentprocess);
        }
        else 
        {
            avgTm = 0;
        }
        if(currentprocess == NULL)
        {
            cout<<"The list is empty"<<endl;
        }

}
struct process * readFromFile(struct process *header,char *argv[])
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

        process = insertBack(process,x,, y[0], y[2] ,y[4]);
        x++;
    } 
    inputFile.close();
	return header;  
}

void writeToFile()
{
	ofstream writeFile(argv[4]);

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

int main(int argc, char *argv[])
{ 
    //command line arguments check
    if (argc != 5 || string(argv[1]) != "-f" || string(argv[3]) != "-o") 
    {
        cout<<"Please enter the correct command argument"<< endl;
        return 1;    
    }

    int choice1;
    int choice2;
    int a=0;
    int x;
    int y;
    struct process *currentprocess = NULL;

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
                        currentprocess = readFromFile(currentprocess);
                        FCFS(currentprocess);
                        methodChoosen = FCFS(currentprocess);
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
                                currentprocess = readFromFile(currentprocess);
							    SJFNonPreemptive(currentprocess);
                                methodChoosen = SJFNonPreemptive(currentprocess);
                                method = "SJF";                    
							}
							break;
							case 2:
							{
                                currentprocess = readFromFile(currentprocess);
					            SJFPreemptive(currentprocess);	
                                methodChoosen = SJFPreemptive(currentprocess);		
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
                                currentprocess = readFromFile(currentprocess);
								priorityNonPreemptive(currentprocess);
                                methodChoosen = priorityNonPreemptive(currentprocess);
                                method = "Priority";                 
							}
							break;
							case 2:
							{
                                currentprocess = readFromFile(currentprocess);
								SJFPreemptive(currentprocess);	
                                methodChoosen = priorityPreemptive(currentprocess);		
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
                        currentprocess = readFromFile(currentprocess);
                        roundRobin(currentprocess);
                        methodChoosen = roundRobin(currentprocess);
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
                if(methodChoosen=FCFS(currentprocess))
                {
                    mode = "OFF";
                }
                if(methodChoosen=SJFNonPreemptive(currentprocess))
                {
                    mode = "OFF";
                }
                if(methodChoosen=SJFPreemptive(currentprocess))
                {
                    mode = "ON";
                }
                if(methodChoosen=priority(currentprocess))
                {
                    mode = "OFF";
                }
                if(methodChoosen=priorityPreemptive(currentprocess))
                {
                    mode = "ON";
                }
                cout<<"The mode is "<<mode<<endl;
               
            }
            break;

            case 3:
            {
                diplayOutput();
            }
            break;

            case 4:
            {
                writeToFile();
                exit(0);
            }
            break;
            
            default:
            cout<<"choose a valid number between 1 and 4";
            break;

        }
    }
}

