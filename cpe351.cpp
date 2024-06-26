#include <iostream>
#include<string>
#include<fstream>
#include <sstream>
using namespace std;

struct process
 {
    int index;
    double burstTm;
    double arrivalTm;
    double priority;
    struct process* next;
 };

struct process *createprocess(int,double, double, double);
struct process *insertBack(struct process *,int,double, double, double);
struct process *FCFS(struct process *,ostream&);
struct process *SJFNonPreemptive(struct process *,ostream&);
void swap(struct process *,struct process *);
struct process *priorityNonPreemptive(struct process *, ostream&);
struct process *sortBurstTm(struct process* );
struct process *sortPriority(struct process* );
void readFromOutputFile(char *);


struct process *methodChoosen = NULL;
string method;
string mode;
double waitingTm = 0;
double avgTm=0;
char* finalOutput;

int main(int argc, char *argv[])
{
    //command line arguments check
    if (argc != 5 || string(argv[1]) != "-f" || string(argv[3]) != "-o") 
    {
        cout<<"Please enter the correct command argument"<< endl;
        return 1;    
    }

    ifstream in(argv[2]);
    if(!in.is_open())
    {
        cout << "the input file cannot open"<<endl;
        return 1;
    }

    ofstream out(argv[4]);
    if(!out.is_open())
    {
        cout << "the input file cannot open"<<endl;
        in.close();
        return 1;
    }
  	finalOutput = argv[4];
    char* inputfile = argv[2];

    struct process* currentprocess = NULL;
    char line[2000];
    int a=1;
    char character;
    while(in.getline(line, sizeof(line)))
    {
        istringstream iss (line);
        int y[3];
        iss >>y[0]>>character>>y[1]>>character>>y[2];
        currentprocess = insertBack(currentprocess,a,y[0],y[1],y[2]);
        a++;
    }
    
    int choice1;
    int choice2;
    int x;
    int y;
    do 
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
								method = "SJF Non-Preemptive";
							}
							break;
							case 2:
							{
								method = "SJF Preemptive";
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
								method = "Priority Non-Preemptive";                 
							}
							break;
							case 2:
							{
								method = "Priority Preemptive";              				
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
            	if(method == "NONE")
                {
                    mode = "NONE"; 
                }
                if(method == "FCFS")
                {
                    mode = "OFF"; 
                }
                if(method == "SJF Non-Preemptive")
                {
                    mode = "OFF";
                }
                if(method == "SJF Preemptive")
                {
                    mode = "ON";
                }
                if(method == "Priority Non-Preemptive")
                {
                    mode = "OFF";
                }
                if(method == "Priority Preemptive")
                {
                    mode = "ON";
                }  
				if(method == "Round Robin")
                {
                    mode = "ON";
                }
            }
            break;
            case 3:
            {
                if (method == "SJF Preemptive" || method == "Priority Preemptive" || method == "Round Robin")
                {
                    cout<<"I did not implement this function"<<endl;
                }
                else if (method == "FCFS")
                {

                	FCFS(currentprocess,out);
            	}
            	else if (method == "SJF Non-Preemptive")
                {
                	SJFNonPreemptive(currentprocess,out);
            	}
            	else if (method == "Priority Non-Preemptive")
                {
                	priorityNonPreemptive(currentprocess,out);
            	}
            }
            break;
            case 4:
            {
            	out.close();
                readFromOutputFile(finalOutput);
                exit(0);
            }
            break;
            default:
            cout<<"choose a valid number between 1 and 4";
            break;
            } 
    } while (choice1 <= 4);
    return 0;
}

struct process *createprocess(int index,double burstTm, double arrivalTm, double priority) {
    struct process *temp = (struct process *) malloc(sizeof(process));
        temp->index = index;
        temp->burstTm = burstTm;
        temp->arrivalTm = arrivalTm;
        temp->priority = priority;
        temp->next = NULL;
    return temp;
}

struct process *insertBack(struct process *header,int index, double burstTm, double arrivalTm, double priority )
{
    struct process *temp = createprocess(index,burstTm,arrivalTm,priority);
    struct process *headertemp;
    if (header == NULL)
    {
        return temp;
    }
    headertemp= header;

    while(headertemp->next != NULL)
        headertemp=headertemp->next;
    headertemp->next = temp;
    
    return header;
}

struct process *FCFS(struct process *currentprocess, ostream& output) 
{
    //First we will sort the Arrival time, the process that has the least arrival time is executed first
    struct process *nextprocess = NULL;
    int countP =0;
    double sum =0;
    double completionTm = 0;
    cout << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    output << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    cout << "Process Waiting Times:" <<endl;
    output << "Process Waiting Times:" <<endl;
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
            cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
           
            sum += waitingTm;
            //Move to the next process in the list
            currentprocess = currentprocess->next;
            countP++;
        }
        if (countP > 0)
        {
            avgTm= sum/countP;
        }
        else 
        {
            avgTm = 0;
        }
        cout << "Average Waiting Time: " << avgTm << " ms" <<endl;
        output << "Average Waiting Time: " << avgTm << " ms" <<endl;

    return currentprocess;
}

struct process *SJFNonPreemptive(struct process *currentprocess, ostream& output)
{
    struct process *nextprocess = NULL;
    double completionTm = 0;
    int countP =0;
    double sum =0;
    cout << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    output << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    cout << "Process Waiting Times:" <<endl;
    output << "Process Waiting Times:" <<endl;
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
        cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
        output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
        sum += waitingTm;
        //Move to the next process in the list
        currentprocess = currentprocess->next;
        countP++;
        break;
    }
    currentprocess = sortBurstTm(currentprocess);
    while (currentprocess != NULL) 
    {
        if (nextprocess != NULL) 
        {
	        //calculate the waiting time
	        completionTm += currentprocess->burstTm;
	        waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
	        cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
	        sum += waitingTm;
        }
        else if(nextprocess == NULL)
        {
        	 //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            sum += waitingTm;
		}
        currentprocess = currentprocess->next;
        countP++;
    }
    if (countP > 0)
    {
        avgTm= sum/countP;
    }
    else 
    {
        avgTm = 0;
    }
    cout << "Average Waiting Time: " << avgTm << " ms" <<endl;
    output << "Average Waiting Time: " << avgTm << " ms" <<endl;
	return currentprocess;
}

struct process *priorityNonPreemptive(struct process *currentprocess, ostream& output)
 {
    struct process *nextprocess = NULL;
    double completionTm = 0;
    int countP =0;
    double sum =0;
    cout << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    output << "Scheduling Method: " << method << " - " << "Preemptive "<< mode <<endl;
    cout << "Process Waiting Times:" <<endl;
    output << "Process Waiting Times:" <<endl;
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
        cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
        output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
        sum += waitingTm;
        //Move to the next process in the list
        currentprocess = currentprocess->next;
        countP++;
        break;
    }
    currentprocess = sortPriority(currentprocess);
    while (currentprocess != NULL) 
    {
        if (nextprocess != NULL) 
        {
	        //calculate the waiting time
	        completionTm += currentprocess->burstTm;
	        waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
	        cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
	        sum += waitingTm;
        }
        else if(nextprocess == NULL)
        {
        	 //calculate the waiting time
            completionTm += currentprocess->burstTm;
            waitingTm = completionTm - currentprocess->arrivalTm - currentprocess->burstTm;
            cout << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            output << "P" <<currentprocess->index << ": " << waitingTm << " ms" <<endl;
            sum += waitingTm;
		}
        currentprocess = currentprocess->next;
        countP++;
    }
    if (countP > 0)
    {
        avgTm= sum/countP;
    }
    else 
    {
        avgTm = 0;
    }
    cout << "Average Waiting Time: " << avgTm << " ms" <<endl;
    output << "Average Waiting Time: " << avgTm << " ms" <<endl;
	return currentprocess;
}

void swap(struct process *currentprocess,struct process *nextprocess) 
{
    double tempburstTm;
    double temparrivalTm;
    double temppriority;
    int tempindex;

    //swap process index
    tempindex = currentprocess->index;
    currentprocess->index = nextprocess->index;
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

void readFromOutputFile(char *outputfile)
{
	ifstream output(outputfile);
	if(output.is_open())
	{
		string result;
		while (getline(output,result))
        {
    	    cout<<result<<endl;
        }
	}
}

struct process* sortBurstTm(struct process* currentprocess) 
{
    bool Swap;
    struct process* header;
    do 
    {
        Swap = false;
        header = currentprocess;
        while (header->next != NULL) {
            if (header->burstTm > header->next->burstTm) 
            {
                double tempburstTm;
                double temparrivalTm;
                double temppriority;
                int tempindex;

                //swap process index
                tempindex = header->index;
                header->index = header->next->index;
                header->next->index = tempindex;
                //swap burst time
                tempburstTm = header->burstTm;
                header->burstTm = header->next->burstTm;
                header->next->burstTm = tempburstTm;
                //swap arrival time
                temparrivalTm = header->arrivalTm;
                header->arrivalTm = header->next->arrivalTm;
                header->next->arrivalTm = temparrivalTm;
                //swap priority
                temppriority = header->priority;
                header->priority = header->next->priority;
                header->next->priority = temppriority;
                Swap = true;
            }
            header = header->next;
        }
    } while (Swap);
    return currentprocess;
}
struct process* sortPriority(struct process* currentprocess) 
{
    bool Swap;
    struct process* header;
    do 
    {
        Swap = false;
        header = currentprocess;
        while (header->next != NULL) {
            if (header->priority > header->next->priority) 
            {
				double tempburstTm;
                double temparrivalTm;
                double temppriority;
                int tempindex;

                //swap process index
                tempindex = header->index;
                header->index = header->next->index;
                header->next->index = tempindex;
                //swap burst time
                tempburstTm = header->burstTm;
                header->burstTm = header->next->burstTm;
                header->next->burstTm = tempburstTm;
                //swap arrival time
                temparrivalTm = header->arrivalTm;
                header->arrivalTm = header->next->arrivalTm;
                header->next->arrivalTm = temparrivalTm;
                //swap priority
                temppriority = header->priority;
                header->priority = header->next->priority;
                header->next->priority = temppriority;
                Swap = true;
            }
            header = header->next;
        }
    } while (Swap);
    return currentprocess;
}
