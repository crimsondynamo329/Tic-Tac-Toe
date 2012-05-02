#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#define CHILD	"./TTT_core/TTT", "./TTT_core/TTT", "--gui", NULL
#define PARENT	"wish", "wish", "./TTT_TK/ttt_gui.tcl", NULL

int main(int argc, const char* argv[])
{
  pid_t pid;
  int fd[2];

  pipe(fd);
  // fd[0] = parent stdin
  // fd[1] = child stdout

  pid = fork();

  if (pid == 0)
    {
      // child process
      close (fd[0]);
      dup2(fd[1], 1);
      execlp("./TTT_core/TTT", "./TTT_core/TTT", "--gui", NULL);
      perror("execlp child");
      exit(1);
    } else if ( pid < 0 )
    {
      perror("fork");
      close(fd[0]);
      close(fd[1]);
      close(fd[2]);
      close(fd[3]);
      exit(1);
    } else {
    // parent process
    close(fd[1]);
    dup2(fd[0], 0);
    execlp("wish", "wish", "./TTT_TK/ttt_gui.tcl", NULL);
    perror("execlp parent");
    exit(1);
  }

  return EXIT_SUCCESS;
}
