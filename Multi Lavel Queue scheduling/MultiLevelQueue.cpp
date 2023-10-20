//#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
#define push push_back

//Class for Process and Gantt Chart
class Process
{
public:
    string name;
    int arrival_time, burst_time, queue, turn_around_time, response_time, waiting_time, service_time;
    bool finished;
};
class GanttChart
{
public:
    int process_id,start_time,finish_time;
    string schedule;
};

//Varibale, Object and Vector declaration
int totalTime=0, quantum=3, n=4, countProcess=0, idleTime=0;
string tempLine;
vector<int> queue1;

vector<Process> process;
Process processObject;

vector<GanttChart> chart;
GanttChart chartObjet;

void readFileProcess()
{
    int i=0;
    ifstream readFile("Input.txt");
    getline(readFile,tempLine);
    // cout<<tempLine<<"\n";
    while(readFile>>processObject.name>>processObject.arrival_time>>processObject.burst_time>>processObject.queue)
    {
        processObject.finished= false;
        processObject.turn_around_time= 0;
        processObject.waiting_time= 0;
        processObject.response_time= -1;
        processObject.service_time= processObject.burst_time;
        process.push(processObject);
        // cout<<process[i].name<<"\t"<<process[i].arrival_time<<"\t"<<process[i].burst_time<<"\t"<<process[i].queue<<"\t"<<"\n";
        // i++;
    }
    readFile.close();
    n= process.size();
}
void processDetails()
{
    ofstream writeFile("Output.txt", ios::app);
    cout<<tempLine<<"\n"; 
    //write into file
    writeFile<<tempLine<<"\n";
    for(int id=0;id<n;id++)
    {
        cout<<process[id].name<<"\t"<<process[id].arrival_time<<"\t"<<process[id].burst_time<<"\t"<<process[id].queue<<"\n";
        //write into file
        writeFile<<process[id].name<<"\t"<<process[id].arrival_time<<"\t"<<process[id].burst_time<<"\t"<<process[id].queue<<"\n";
    }
    writeFile.close();
}

// bool compareProcessQueue(Process p1, Process p2) 
// { 
//     return (p1.queue < p2.queue);
// }
bool compareProcessTime(Process p1, Process p2) 
{ 
    if(p1.arrival_time == p2.arrival_time)
    {
        return (p1.queue < p2.queue);
    }
    else
    {
        return (p1.arrival_time < p2.arrival_time);
    }
} 

void ganttChart()
{
    ofstream writeFile("Output.txt", ios::app);
    cout<<"\n\t------Gantt Chart--------\n\n";
    cout<<"Name\tQueue\tST\tFT\n";
    //write into file
    writeFile<<"\n\t------Gantt Chart--------\n\n";
    writeFile<<"Sl\tName\tQueue\tST\tFT\n";
    int length= chart.size();
    for(int i=0; i<length; i++)
    {
        cout<<i+1<<"\t"<<process[chart[i].process_id].name<<"\t"<<chart[i].schedule<<"\t"<<chart[i].start_time<<"\t"<<chart[i].finish_time<<"\n";
        //write into file
        writeFile<<i+1<<"\t"<<process[chart[i].process_id].name<<"\t"<<chart[i].schedule<<"\t"<<chart[i].start_time<<"\t"<<chart[i].finish_time<<"\n";
    }
    writeFile.close();
}
void performance()
{
    ofstream writeFile("Output.txt", ios::app);
    int totalWait= 0, totalResponse= 0, totalService= 0; 
    cout<<"\n\t------Performance-------\n\n";
    cout<<"Name\tAT\tBT\tQueue\tTAT\tWT\tRT\tTotalTime\n";
    //write into file
    writeFile<<"\n\t------Performance-------\n\n";
    writeFile<<"Name\tAT\tBT\tQueue\tTAT\tWT\tRT\tTotalTime\n";
    for(int id=0; id<n; id++)
    {
        cout<<process[id].name<<"\t"<<process[id].arrival_time<<"\t"<<process[id].service_time<<"\t"<<process[id].queue;
        cout<<"\t"<<process[id].turn_around_time<<"\t"<<process[id].waiting_time<<"\t"<<process[id].response_time<<"\t"<<totalTime<<"\n";
        //write into file
        writeFile<<process[id].name<<"\t"<<process[id].arrival_time<<"\t"<<process[id].service_time<<"\t"<<process[id].queue;
        writeFile<<"\t"<<process[id].turn_around_time<<"\t"<<process[id].waiting_time<<"\t"<<process[id].response_time<<"\t"<<totalTime<<"\n";
        totalWait+= process[id].waiting_time;
        totalResponse+= process[id].response_time;
        totalService+= process[id].turn_around_time;
    }
    cout<<"\nCPU utilization: "<<fixed<<setprecision(2)<<(totalTime-idleTime)*100.00/totalTime<<" %";
    cout<<"\nThroughput: "<<fixed<<setprecision(2)<<n*100.00/totalTime<<" %";
    cout<<"\nAvg TurnAroundTime: "<<totalService*1.00/n;
    cout<<"\nAvg WaitingTime: "<<totalWait*1.00/n;
    cout<<"\nAvg ResponseTime: "<<totalResponse*1.00/n<<"\n";
    //write into file
    writeFile<<"\nCPU utilization: "<<fixed<<setprecision(2)<<(totalTime-idleTime)*100.00/totalTime<<" %";
    writeFile<<"\nThroughput: "<<fixed<<setprecision(2)<<n*100.00/totalTime<<" %";
    writeFile<<"\nAvg TurnAroundTime: "<<totalService*1.00/n;
    writeFile<<"\nAvg WaitingTime: "<<totalWait*1.00/n;
    writeFile<<"\nAvg ResponseTime: "<<totalResponse*1.00/n<<"\n";
    writeFile.close();
}
int processArrived(int id)
{
    for( ; id<n ; id++)
    {
        if(process[id].arrival_time>totalTime)
        {
            return -1;
        }
        if(process[id].arrival_time<=totalTime && process[id].queue==1 && !process[id].finished)
        {
            queue1.push(id);
            return id;
        }
    }
    return -2;
}
int roundRobin(int pid)
{
    // cout<<"\nRound Robin\n";
    countProcess=0;
    while(!queue1.empty() && countProcess<queue1.size())
    {
        if(process[queue1[countProcess]].burst_time >= quantum)
        {
            if(process[queue1[countProcess]].response_time == -1)
            {
                process[queue1[countProcess]].response_time= totalTime - process[queue1[countProcess]].arrival_time;
            }
            chartObjet.process_id= queue1[countProcess];
            chartObjet.start_time= totalTime;
            // cout<<chartObjet.process_id<<"\t"<<chartObjet.start_time<<"\n";
            totalTime+= quantum;
            chartObjet.finish_time= totalTime;
            chartObjet.schedule= "RR";
            chart.push(chartObjet);
            // cout<<chartObjet.process_id<<"\t"<<chartObjet.finish_time<<"\n";
            // cout<<"\n\t\t"<<chartObjet.process_id<<"\n";
            process[queue1[countProcess]].burst_time-=quantum;
            if(process[queue1[countProcess]].burst_time ==0 )
            {
                process[queue1[countProcess]].turn_around_time= totalTime - process[queue1[countProcess]].arrival_time;
                process[queue1[countProcess]].finished=true;
                queue1.erase(queue1.begin()+countProcess);
                // cout<<"\n-----RoundRobin1-----\n";
            }            
        }
        else
        {
            if(process[queue1[countProcess]].response_time == -1)
            {
                process[queue1[countProcess]].response_time= totalTime - process[queue1[countProcess]].arrival_time;
            }
            chartObjet.process_id= queue1[countProcess];
            chartObjet.start_time= totalTime;
            // cout<<chartObjet.process_id<<"\t"<<chartObjet.start_time<<"\n";
            totalTime+= process[queue1[countProcess]].burst_time;
            chartObjet.finish_time= totalTime;
            chartObjet.schedule= "RR";
            chart.push(chartObjet);
            // cout<<chartObjet.process_id<<"\t"<<chartObjet.finish_time<<"\n";
            // cout<<"\n\t\t"<<chartObjet.process_id<<"\n";
            process[queue1[countProcess]].burst_time=0;
            process[queue1[countProcess]].turn_around_time= totalTime - process[queue1[countProcess]].arrival_time;
            process[queue1[countProcess]].finished=true;
            queue1.erase(queue1.begin()+countProcess);
            // cout<<"\n-----RoundRobin2-----\n";
        }
        if(pid != -1)
        {
            pid = processArrived(pid+1);
        }
        if(countProcess+1 == queue1.size())
        {
            countProcess= 0;
        }
        else
        {
            countProcess+= 1;
        }
    }
    return 1;
}
int firstComeFisrtServe(int pid)
{
    // cout<<"\nFCFS\n";
    chartObjet.process_id= pid;
    chartObjet.start_time= totalTime;
    // cout<<chartObjet.process_id<<"\t"<<chartObjet.start_time<<"\n";
    process[pid].response_time= totalTime - process[pid].arrival_time;
    int currentTime = totalTime , temp= 10;
    totalTime+= process[pid].burst_time;
    int needRoundRobinId = processArrived(pid+1);
    if(needRoundRobinId !=-1 && needRoundRobinId !=-2)
    {
        totalTime = process[needRoundRobinId].arrival_time;
        chartObjet.finish_time= totalTime;
        chartObjet.schedule= "FCFS";
        chart.push(chartObjet);
        // cout<<chartObjet.process_id<<"\t"<<chartObjet.finish_time<<"\n";
        // cout<<"\n\t\t"<<chartObjet.process_id<<"\n";
        process[pid].burst_time-= totalTime-currentTime;
        // cout<<"\n-----FCFS1-----\n";
        temp= roundRobin(needRoundRobinId);
        chartObjet.process_id= pid;
        chartObjet.start_time= totalTime;
        cout<<chartObjet.process_id<<"\t"<<chartObjet.start_time<<"\n";
        totalTime+= process[pid].burst_time;
        process[pid].burst_time=0;
        chartObjet.finish_time= totalTime;
        chartObjet.schedule= "FCFS";
        chart.push(chartObjet);
        // cout<<chartObjet.process_id<<"\t"<<chartObjet.finish_time<<"\n";
        // cout<<"\n\t\t"<<chartObjet.process_id<<"\n";
        // cout<<"\n\t\t"<<temp<<"\n";
    }
    if(process[pid].burst_time!=0)
    {
        chartObjet.finish_time= totalTime;
        chartObjet.schedule= "FCFS";
        chart.push(chartObjet);
        // cout<<chartObjet.process_id<<"\t"<<chartObjet.finish_time<<"\n";
    }
    process[pid].turn_around_time= totalTime - process[pid].arrival_time;
    process[pid].burst_time=0;
    process[pid].finished=true;
    // cout<<"\n\t\t"<<chartObjet.process_id<<"\n";
    // cout<<"\n-----FCFS2-----\n";
    // cout<<"\n\t\t"<<temp<<"\n";
    return 2;
}

int main()
{
    int temp=0;
    ofstream writeFIle("Output.txt", ios::app);
    cout<<"----Multi level Queue----"<<"\n";
    //write into file
    writeFIle<<"----Multi level Queue----"<<"\n";
    writeFIle.close();
    readFileProcess();
    processDetails();
    // sort(process.begin(), process.end(), compareProcessQueue);
    sort(process.begin(), process.end(), compareProcessTime);

    for(int id=0;id<n;id++)
    {
        if(process[id].arrival_time>totalTime)
        {
            idleTime+= process[id].arrival_time - totalTime;
            totalTime= process[id].arrival_time;
            --id;
        }
        else if(process[id].arrival_time<=totalTime && process[id].queue==1 && !process[id].finished)
        {
            queue1.push(id);
            temp= roundRobin(id);
        }
        else if(process[id].arrival_time<=totalTime && process[id].queue==2 && !process[id].finished)
        {
            temp= firstComeFisrtServe(id);
        }
        // else if(process[id].finished)
        // {
        //     temp= -1;
        // }
        else
        {
            ;
        }
        process[id].waiting_time= process[id].turn_around_time - process[id].service_time;
        // cout<<"\n\t\t"<<temp<<"\t\t"<<id<<"\n";
        // temp= 0;
    }
    ganttChart();
    performance();
    // cout<<"\n------Performance-------\n";
    // cout<<"Name  burst_time  totalTime queue\n";
}