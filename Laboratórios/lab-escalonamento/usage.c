#include "types.h"
#include "user.h"
#include "param.h"

int
main(int argc, char **argv) {
  if (argc < 2) {
    printf(2, "Você deve usar assim: usage pid...\n");
    exit();
  }

  int i;
  
  // validar se o pid existe
  
  for (i = 1; i < argc; ++i) {
    int pid = atoi(argv[i]);
    printf(2, "usage %d was %d times\n", pid, getusage(pid));
  }
  exit();

}
