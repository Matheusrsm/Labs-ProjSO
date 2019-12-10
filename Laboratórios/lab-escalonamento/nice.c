#include "types.h"
#include "user.h"
#include "param.h"

int
main(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    printf(2, "Você deve usar assim: nice pid [prioridade]\n");
    exit();
  }

  // // validar se o pid existe
  int pid = atoi(argv[1]);

  // query priority
  if (argc == 3) {
    int newpriority = atoi(argv[2]);
    if (newpriority > 31 || newpriority < 0) {
      printf(2, "a prioridade deve ir de 0 a 31\n");
      exit();
    }
    int oldpriority = setpriority(pid, newpriority);
    if (oldpriority < 0) {
      printf(2, "não foi possivel mudar a prioridade\n");
      exit();
    }

    printf(2, "Mudou a prioridade de %d pra %d\n", oldpriority, newpriority);
  } else {
    int currentpriority = getpriority(pid);
    if (currentpriority < 0) {
      printf(2, "could not get priority\n");
      exit();
    }
    printf(2, "pid %d tem prioridade de %d\n", pid, currentpriority);
  }
  exit();

}
