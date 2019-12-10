#include "types.h"
#include "stat.h"
#include "user.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

typedef struct  {
  enum procstate state;
  int pid;
  int ppid ;
  int priority; 
  int usage;
  char name[16];
} proc;

#define MAX_PROC 10

void swap (proc* p1, proc* p2) {
  proc temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

// ordena desconsiderando o 0.
void bubbleSort(proc *v, int n){ 
    if (n < 1)return; 
 
    for (int i=0; i<n; i++) 
        if (v[i].pid > v[i+1].pid && v[i+1].pid > 0) 
            swap(&v[i], &v[i+1]);  
    bubbleSort(v, n-1); 
} 

void sort(proc ptable[MAX_PROC]) {
    bubbleSort(ptable, MAX_PROC - 1);
}

int
main(int argc, char *argv[]){  
  proc ptable[MAX_PROC];
  proc *p;
  int err;
  
  err = getptable(10*sizeof(proc),&ptable);
  if(err !=0)
    printf(1,"Error getting ptable");
  
  sort(ptable);

  p = &ptable[0];
  printf(1, "NAME\tPID\tPRIORITY\tSTATE\t\tPPID\tUSAGE\n");
  while(p != &ptable[MAX_PROC-1] && p->state != UNUSED){
    printf(1,"%s\t", p->name);
  	printf(1,"%d\t",p->pid);
    printf(1,"%d\t",p->priority);
  	switch(p->state){
  	case UNUSED:
  		printf(1,"\t%s ", "UNUSED");
  		break;
  	case EMBRYO:
  		printf(1,"\t%s ", "EMBRYO");
  		break;
  	case SLEEPING:
  		printf(1,"\t%s ", "SLEEPING");
  		break;
  	case RUNNABLE:
  		printf(1,"\t%s ", "RUNNABLE");
  		break;
  	case RUNNING:
  		printf(1,"\t%s ", "RUNNING");
  		break;
  	case ZOMBIE:
  		printf(1,"\t%s ", "ZOMBIE");
  		break;
  	} 
    if (p->pid == 1) {
        printf(1,"\tNE");
    } else {
        printf(1,"\t%d",p->ppid);
    }
  	p++;
    printf(1,"\t%d\n",p->usage);
  }
  	  
  exit();
}