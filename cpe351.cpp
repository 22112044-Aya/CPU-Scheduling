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
