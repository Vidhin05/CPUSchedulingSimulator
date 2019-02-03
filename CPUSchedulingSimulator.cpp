#include<iostream>
#include <fstream>
#include<string.h>
#include<vector>
//#include<bits/stdc++.h>

using namespace std;

struct proccess{
	string PID;
	int arrival_time;
	int burst_time;
	proccess(){
		PID = "";
		arrival_time = 0;
		burst_time = 0;
	}
};

int main(int argc, char** argv){

  //FCFS
  if(strcmp(argv[2], "FCFS") == 0){
    std::ifstream infile(argv[1]);
    cout << "Scheduling algorithm: FCFS" << endl;
    cout << "Chosen input file is " << argv[1] << endl;
    cout << "==================================================================\n";

    int time = 0;
    int total_processes = 0;
    int pid, arrival_time, burst_time;
    float t_time = 0.0, w_time = 0, r_time = 0;
    int burst_total = 0;

    //Process Order
    while (infile >> pid >> arrival_time >> burst_time){
      total_processes++;
      burst_total += burst_time;

      while(time < arrival_time){
        cout << "<system time " << time << "> CPU idle" << endl;
        time++;
      }

      for(int i = 0; i<burst_time; i++){
        cout << "<system time " << time << "> Process " << pid <<" is running" << endl;
        time++;
      }
      t_time += time - arrival_time;
      w_time = t_time - burst_total;

      cout << "<system time " << time << "> Process " << pid <<" is finished.......\n";
    }
    cout << "<system time " << time << "> All processes finished....................\n";

    //Statistics
    t_time /= total_processes;
    w_time /= total_processes;
    r_time = w_time;
    cout << "============================================================\n";
    cout << "Average waiting time: " << w_time <<endl;
    cout << "Average response time: " << r_time <<endl;
    cout << "Average turnaround time: " << t_time <<endl;
    cout << "============================================================\n";
  }






  //SJF
  else if(strcmp(argv[2], "SJF") == 0){
    std::ifstream infile(argv[1]);
    cout << "Scheduling algorithm: SJF" << endl;
    cout << "Chosen input file is " << argv[1] << endl;
    cout << "==================================================================\n";
    int i = 0, n = 0, min, k = 1, btime = 0, wt[20], tt[20], ta = 0, sum = 0;
    int pid[20], burst_time[20], arrival_time[20];
    float w_time = 0, t_time = 0;
    while(infile >> pid[i] >> arrival_time[i] >> burst_time[i]){
      n++; i++;
    }

    // Sorting by Arrival Time
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        if(arrival_time[i]<arrival_time[j]){
          swap(pid[i], pid[j]);
          swap(arrival_time[i], arrival_time[j]);
          swap(burst_time[i], burst_time[j]);
        }
      }
    }

    // Arranging the table according to Burst time, Execution time and Arrival Time
    //Arrival time <= Execution time
    for(int j=0; j<n; j++){
      btime = btime+burst_time[j];
      min = burst_time[k];
      for(int i=k; i<n; i++){
        if (btime >= arrival_time[i] && burst_time[i] < min){
          swap(pid[i], pid[k]);
          swap(arrival_time[i], arrival_time[k]);
          swap(burst_time[i], burst_time[k]);
        }
      }
      k++;
    }

    wt[0] = 0;
    for(int i=1; i<n; i++){
      sum += burst_time[i-1];
      wt[i] = sum - arrival_time[i];
      w_time += wt[i];
    }

    w_time /= n;
    for(int i=0; i<n; i++){
      ta += burst_time[i];
      tt[i] = ta - arrival_time[i];
      t_time += tt[i];
    }

    t_time /= n;
    float r_time = w_time;
    int time = 0;
    for(int i = 0; i < n; i++){
      while(time < arrival_time[i]){
        cout << "<system time " << time << "> CPU idle" << endl;
        time++;
      }
      for(int j = 0; j < burst_time[i]; j++){
        cout << "<system time " << time << "> Process " << pid[i] <<" is running\n";
        time++;
      }
      cout << "<system time " << time << "> Process " << pid[i] <<" is finished.......\n";
    }

    cout << "<system time " << time << "> All processes finished...................." << endl;
    //Statistics
    cout << "============================================================\n";
    cout << "Average waiting time: " << w_time <<endl;
    cout << "Average response time: " << r_time <<endl;
    cout << "Average turnaround time: " << t_time <<endl;
    cout << "============================================================\n";
  }






  //RR
  else if(strcmp(argv[2], "RR") == 0){
    cout << "Scheduling algorithm: RR" << endl;
    cout << "Chosen input file is " << argv[1] << endl;
    cout << "==================================================================\n";

    int quantum_time = atoi(argv[3]);
    int i, n = 0, time, remain, temps = 0, w_time = 0, t_time = 0;
    cout << "Quantum of time is " << quantum_time <<".\n";

    // Reading the data of the processes from the file
    ifstream fin (argv[1]);
    if (fin.is_open()){
      vector<int> at, bt, rt, pid;
      string buffer, temp;

      //Creating a vector of proccesses
      vector<proccess> jobs;

      //Getting the processes from the file
      while (!fin.eof()){
        getline(fin, buffer);

        //Whenever you encounter a blank line, just ignore it
        if (!buffer.empty()){
          proccess P;

          //Now parsing the buffer to get PID, arrival time and burst time
          int i = 0;

          //First reading the PID
          for (i = 0; buffer[i] != ' '; i++){
            P.PID.push_back(buffer[i]);
            pid.push_back(buffer[i]);
          }
          i++;
          temp = "";

          //Then reading the Arrival Time
          for (; buffer[i] != ' '; i++){
            temp.push_back(buffer[i]);
          }
          P.arrival_time = atoi(temp.c_str());
          at.push_back(atoi(temp.c_str()));
          i++;
          temp = "";

          //Then reading the Burst Time
          for (; buffer[i] != '\0'; i++){
            temp.push_back(buffer[i]);
          }
          n++;
          P.burst_time = atoi(temp.c_str());
          jobs.push_back(P);
          bt.push_back(atoi(temp.c_str()));
          rt.push_back(atoi(temp.c_str()));
        }
      }
      fin.close();
      remain = n;
      //cout<<"\n\nProcess\t:Turnaround Time:Waiting Time\n\n";
      for(time = 0, i = 0; remain!=0;){
        if(rt[i]<=quantum_time && rt[i]>0){
          time += rt[i];
          //Addition using shorthand operators
          rt[i] = 0;
          temps = 1;
        }
        else if(rt[i]>0){
          rt[i] -= quantum_time;
          //Subtraction using shorthand operators
          time += quantum_time;
          //Addition using shorthand operators
        }
        if(rt[i]==0 && temps==1){
          remain--;
          //Desplaying the result of wating, turn around time:
          //printf("Process{%d}\t:\t%d\t:\t%d\n",i+1,time-at[i],time-at[i]-bt[i]);
          //cout<<endl;

          w_time += time-at[i]-bt[i];
          t_time += time-at[i];
          temps=0;
        }
        if(i == n-1) i = 0;
        else if(at[i+1] <= time) i++;
        else i=0;
      }
      w_time /= n;
      t_time /= n;
      //Processing
      int total_processes = jobs.size();
      int running_time = 1, quantum_number = 1, has_burst_zero = 0;
      vector<int> flag(jobs.size());
      float r_time = 0.0;
      bool isIdle = true;
      //Tells if the CPU was sitting Idle in a particular time quantum_time
      //Continue until each proccess' burst time becomes equal to zero
      while (has_burst_zero != total_processes){
        isIdle = true;
        for (int i = 0; i<total_processes; i++){
          if (jobs[i].arrival_time < running_time && jobs[i].burst_time > 0){
            if(flag[i] == 0){
              r_time += running_time - jobs[i].arrival_time;
              flag[i] = 1;
            }
            cout << "<system time "<< quantum_number*quantum_time << "> Process " << jobs[i].PID <<" is running\n";
            jobs[i].burst_time -= quantum_time;
            running_time += quantum_time;
            quantum_number++;
            isIdle = false;
            if (jobs[i].burst_time <= 0) {
              has_burst_zero++;
              cout << "<system time "<< (quantum_number*quantum_time) + jobs[i].burst_time << "> Process " << jobs[i].PID <<" is finished.......\n";
            }	//Increment size by one
          }
        }
        if(isIdle){
          cout << "<system time "<< quantum_number*quantum_time << "> CPU idle\n";
          quantum_number++;
          running_time += quantum_time;
        }
      }
      r_time /= n;
      cout << "<system time "<< quantum_number*quantum_time << "> All processes finished....................\n";
      cout << "============================================================\n";
      cout << "Average waiting time: " << w_time <<endl;
      cout << "Average response time: " << r_time <<endl;
      cout << "Average turnaround time: " << t_time <<endl;
      cout << "============================================================\n";
    } 
  }
  return 0;
}
