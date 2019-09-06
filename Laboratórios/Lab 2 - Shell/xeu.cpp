#include "xeu_utils/StreamParser.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <utility>
#include <mutex>

using namespace xeu_utils;
using namespace std;

vector< pair<pid_t,Command> > jobs;
mutex xeuMutex;

void * wait_process (void * arg) {

  pid_t pid = (pid_t) (size_t) arg;

  waitpid(pid, NULL, 0);
  int i = 0;
  xeuMutex.lock();
  while(i < jobs.size()){
    if (jobs[i].first == pid) {
      jobs.erase(jobs.begin() + i);
      break;
    }
    i++;
  }
  xeuMutex.unlock();

  pthread_exit(0);
}

void waitProcess(pid_t pid) {
  waitpid(pid, NULL, 0);
  int i = 0;
  xeuMutex.lock();
  while(i < jobs.size()){
    if (jobs[i].first == pid) {
      jobs.erase(jobs.begin() + i);
      break;
    }
    i++;
  }
  xeuMutex.unlock();
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
  xeuMutex.lock();
  for (auto job : jobs)
    cout << "pid: " << job.first << " | command: " << " " << job.second.repr() << endl;
  xeuMutex.unlock();
}

Command getBgCommand(Command cm) {
  
  return cm;
}

int main() {

  auto cms = StreamParser().parse().commands();
  pthread_t thread;
  int i = 0;

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

      xeuMutex.lock();
      jobs.push_back(make_pair(pid, bgCm));
      xeuMutex.unlock();
      
      pthread_create(&thread, NULL, wait_process, (void *) pid);
      
      //thread workerThread(waitProcess, pid);
      //workerThread.detach();
    } else {
      pid_t pid = exec(cm);
      waitpid(pid, NULL, 0);
    }

    wait(NULL);
    cms = StreamParser().parse().commands();
  }

  return 0;
}
