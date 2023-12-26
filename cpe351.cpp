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

// this variable will be used to count the number of processes
int countP = 0;
// here i defined the number of procesess a program can execute at a time
const int noOfProcesses = 50;
// here i created an array that will store information about the processes 
process processArr[noOfProcesses];

// I wrote a funtion that will display the details about processes being executed 
 void displayProcesses()
 {
    for(int i=0; i<countP; i++)
    {
        cout<<"Process " << i+1 <<endl;
        cout<<"Burst Time: " << processArr[i].burstTm << endl;
        cout<<"Arrival Time: " << processArr[i].arrivalTm << endl;
        cout<<"Priority: " << processArr[i].priority << endl;
    }
 } 
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
