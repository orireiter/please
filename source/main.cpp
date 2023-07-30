#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <util.h>

#include <iostream>

#include "please/terminalManager.h"

// int main() {
//   const char* cmd = "vim";
//   char* args[] = {const_cast<char*>(cmd), nullptr};

//   pid_t pid;
//   int master_fd;
//   struct termios term;
//   char buf[1024];

//   if (forkpty(&master_fd, NULL, &term, NULL) == -1) {
//     perror("forkpty");
//     return 1;
//   }

//   pid = fork();
//   if (pid == -1) {
//     perror("fork");
//     return 1;
//   } else if (pid == 0) {
//     // child process
//     close(master_fd);
//     execvp(cmd, args);
//     exit(1);
//   }

//   wait(0);
//   return 0;

//   // parent process
//   while (true) {
//     ssize_t n = read(master_fd, buf, sizeof(buf));
//     if (n <= 0) {
//       break;
//     }
//     write(STDOUT_FILENO, buf, n);
//   }

//   return 0;
// }

int main() {
  TerminalManager pleaseTerminal = TerminalManager();
  pleaseTerminal.start();
  return 0;
};
