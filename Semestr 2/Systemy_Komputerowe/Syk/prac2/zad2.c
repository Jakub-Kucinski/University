/* Imię nazwisko: Jakub Kuciński
 * Numer indeksu: 309881
 *
 * Oświadczam, że:
 *  - rozwiązanie zadania jest mojego autorstwa,
 *  - jego kodu źródłowego dnie będę udostępniać innym studentom,
 *  - a w szczególności nie będę go publikować w sieci Internet.
 *
 * Q: Zdefiniuj proces "sierotę".
 * A: Proces zostaje sierotą, jeśli jego rodzic zakończył działanie przed nim.
 *
 * Q: Co się stanie, jeśli główny proces nie podejmie się roli żniwiarza?
 * A: Jeśli głowny proces nie przyjmie roli żniwiarza, to proces sierota zostanie "zaadoptowany" przez proces init. Gdy sprawdzimy jaki jest PPID sieroty to pokaże się 1, czyli PID initu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

pid_t parent = 0;
pid_t son = 0;
pid_t grandson = 0;


void ps_fork()
{
  int t;
  pid_t ps = fork();
  char *newargv[] = { "ps" ,"-f", NULL};
  char *newenviron[] = { NULL };
  
  switch (ps)
  {
  case -1:
    printf("Blad forkowania");
    break;
  case 0:
    execve("/bin/ps", newargv, newenviron);
    break;
  default:
    waitpid(ps, &t, 0);
  }
}

void proc_grandson()
{
  grandson = getpid();
  setpgid(grandson, parent);
  ps_fork();
  killpg(parent, SIGUSR1);
  pause();
}

void proc_son()
{
  son = getpid();
  grandson = fork();
  
  switch (grandson)
  {
  case -1:
    printf("Blad forkowania");
    break;
  case 0:
    proc_grandson();
    break;
  default:
    pause();
  }
}

void sig_handler_usr1(int signum)
{
  ;
}

int main(void) {
  signal(SIGUSR1, sig_handler_usr1);

  prctl(PR_SET_CHILD_SUBREAPER);
  parent = getpid();
  setpgid(parent, parent);

  son = fork();
  switch (son)
  {
    case -1:
      printf("Blad forkowania");
      return EXIT_FAILURE;
    case 0:
      proc_son();
      exit(0);
    default:
      pause();
  }

  int t;
  kill(son, SIGKILL);
  waitpid(son, &t, 0);
  ps_fork();
  killpg(parent, SIGUSR1);
  return EXIT_SUCCESS;
}
