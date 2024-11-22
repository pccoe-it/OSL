#include<stdio.h>
typedef struct 
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int end_time;
    int waiting_time;
    int turn_around_time;
}Process;


void sortByArrivalTime(Process p[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].arrival_time > p[j+1].arrival_time ||(p[j].arrival_time==p[j+1].arrival_time && p[j].burst_time > p[j+1].burst_time)){
                Process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void sortTheProcessByProcesNo(Process p[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].pid > p[j+1].pid){
                Process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

int findTheNextProcess(Process p[],int current_time,int completed[],int n){
    int minBurstTime=1e9;
    int index=-1;

    for(int i=0;i<n;i++){
        if(!completed[i] && p[i].arrival_time <= current_time && p[i].remaining_time < minBurstTime){
            minBurstTime=p[i].remaining_time;
            index=i;
        }
    }
    return index;
}

int main(){
   
    int n;
    printf("Enter the number of process : ");
    scanf("%d",&n);

    Process p[n];
    int completed[n];
    int is_started[n];
    printf("\nEnter the Arrival time and Burst time of each process\n");
    for(int i=0;i<n;i++){
        printf("Process %d : ",i+1);
        p[i].pid=i+1;
        scanf("%d %d",&p[i].arrival_time,&p[i].burst_time);
        completed[i]=0;//no process is completed initially
        is_started[i]=0;
        p[i].remaining_time=p[i].burst_time;
    }

    sortByArrivalTime(p,n);

    int completed_count=0;
    float total_turn_around_time=0,total_waiting_time=0;
    int current_time=0;

    while(completed_count < n){
        int index=findTheNextProcess(p,current_time,completed,n);
        if(index!=-1){
            if(!is_started[index]){
                is_started[index]=1;
                p[index].start_time=current_time;
            }
           
            p[index].remaining_time--; current_time++;
            if(p[index].remaining_time==0){
                p[index].end_time=current_time;

                p[index].waiting_time=p[index].end_time-p[index].arrival_time-p[index].burst_time;
                p[index].turn_around_time=p[index].end_time- p[index].arrival_time;

                total_turn_around_time+=p[index].turn_around_time;
                total_waiting_time+=p[index].waiting_time;
                completed_count++;
                completed[index]=1;
            }
        }else{
            current_time++;
        }
    }

    sortTheProcessByProcesNo(p,n);

    printf("\nProcess\tArrival\tBurst\tstart\tEnd\tWaiting\tTurnaround\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].start_time,p[i].end_time,p[i].waiting_time,p[i].turn_around_time);
    }

    printf("\nAverage Waiting Time : %.2f\n",total_waiting_time/n);
    printf("Average Turn Around Time : %.2f\n",total_turn_around_time/n);
    
    return 0;
}