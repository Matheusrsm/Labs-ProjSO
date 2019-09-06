#include "xeu_utils/StreamParser.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <utility>

using namespace xeu_utils;
using namespace std;

vector< pair<pid_t,Command> > jobs;

void wait_process(pid_t pid) {
  waitpid(pid, NULL, 0);
  int i = 0;
  while(i < jobs.size()){
    if(jobs[i].first == pid) {
      jobs.erase(jobs.begin() + i);
      break;
    }
    i++;
  }
}

pid_t exec(Command cm) {
  pid_t pid = fork();
  if(pid == 0) {
    execvp(cm.filename(), cm.argv());
    string err;
    switch (errno) {
      case ENOENT:
        err = "Command not found -> ";
        break;
      
      default:
        err = "Could not execute -> ";
        break;
    }
    cerr << "ERROR: " << err << cm.filename() << endl;
    exit(1);
  }
  return pid;
}

bool exit(const vector<Command> cms) {
  for (int i = 0; i < cms.size(); i++)
    if (!strcmp(cms[i].filename(), "exit")) return false;
  
  return true;
}

void xjobs() {
  for (auto job : jobs)
    cout << "pid: " << job.first << " | command: " << " " << job.second.repr() << endl;
}

int main() {

  auto cms = StreamParser().parse().commands();

  while (exit(cms)) {
    Command cm = cms[0];

    if (!strcmp(cm.filename(), "xjobs")) {
      xjobs();
    } else if (!strcmp(cm.filename(), "bg")) {
      auto bgCm = Command();
      auto args = vector<string>(cm.args());
      
      args.erase(args.begin());

      for (auto arg : args) bgCm.add_arg(arg);

      pid_t pid = exec(bgCm);
      jobs.push_back(make_pair(pid, bgCm));
      //thread t(wait_process, pid);
      //t.detach();
    } else {
      pid_t pid = exec(cm);
      waitpid(pid, NULL, 0);
    }

    wait(NULL);
    cms = StreamParser().parse().commands();
  }

  return 0;
}
