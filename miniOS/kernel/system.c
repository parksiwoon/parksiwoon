#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PROCESSES 10

void minisystem()
{
    printf("minisystem\n");
}

void uppercase(){
    char *upper_input = readline("변환할 문자열을 입력하세요: ");
    if (upper_input) {  // NULL 체크
        for (int i = 0; upper_input[i]; i++) {
            upper_input[i] = toupper(upper_input[i]);
        }
        printf("대문자 변환 결과: %s\n", upper_input);
        free(upper_input);  // 할당된 메모리 해제
    } else {
        printf("입력 오류 또는 취소되었습니다.\n");
    }
}

typedef struct Process{
    int arrival_time;
    int burst_time;
    int remaining_time;
}Process;

int rr(){
    int num_processes;
    int time_slice;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes (up to %d):",MAX_PROCESSES);
    scanf("%d",&num_processes);

    for(int i=0; i<num_processes; i++){
        printf("Enter arrival time for process %d:",i+1);
        scanf("%d",&processes[i].arrival_time);
        printf("Enter burst time for process %d:",i+1);
        scanf("%d",&processes[i].burst_time);
        processes[i].remaining_time=processes[i].burst_time;
    }
    printf("Enter time slice: ");
    scanf("%d",&time_slice);

    int current_time=0;
    int completed_processes=0;

    printf("\n Round Robin Scheduling:\n");

    while (completed_processes<num_processes){
        for(int i=0; i<num_processes; i++){
            if(processes[i].remaining_time>0){
                if(processes[i].remaining_time>time_slice){
                    printf("Time %d: Process %d is running\n", current_time,i+1);
                    current_time+=time_slice;
                    processes[i].remaining_time-=time_slice;
                }
                else{
                    printf("Time %d: Process %d is completed\n", current_time,i+1);
                    current_time+=processes[i].remaining_time;
                    processes[i].remaining_time=0;
                    completed_processes++;
                        
                }
            }
        }
    }
    return 0;
}
        