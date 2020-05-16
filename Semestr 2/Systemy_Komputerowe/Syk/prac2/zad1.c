/* Imię nazwisko: Jakub Kuciński
 * Numer indeksu: 309881
 *
 * Oświadczam, że:
 *  - rozwiązanie zadania jest mojego autorstwa,
 *  - jego kodu źródłowego dnie będę udostępniać innym studentom,
 *  - a w szczególności nie będę go publikować w sieci Internet.
 *
 * Q: Zdefiniuj proces "zombie".
 * A: Proces zombie jest to proces, który zakończył działanie, ale jego rodzic nie odebrał jeszcze informacji o zakończeniu działania tego procesu (wait()).
 * Zasoby procesu są zwalaniane, ale pozostaje jego wpis w tablicy procesów, zawierający między innymi PID, status zakończenia oraz statystyki użycia zasobów.
 * Gdy rodzic wykona wait(), wpis w tablicy zostaje usunięty. Jeśli rodzic zakończy działanie, bez wykonania wait(), to proces zombie zostanie zaadopotwany przez init, który wykona wait().
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1],"--bury") == 0)
  {
    struct sigaction newhandler;
    newhandler.sa_handler = SIG_IGN;
    sigemptyset(&(newhandler.sa_mask));
    newhandler.sa_flags = 0;
    sigaction(SIGCHLD, &newhandler, NULL);
  }

  switch (fork())
  {
  case -1:
    printf("Blad forkowania");
    return EXIT_FAILURE;
  case 0:
    exit(0);
  default:
    sleep(1);
  }

  pid_t id = fork();
  char *newargv[] = { "ps" };
  char *newenviron[] = { NULL };
  int t;

  switch (id)
  {
  case -1:
    printf("Blad forkowania");
    return EXIT_FAILURE;
  case 0:
    execve("/bin/ps", newargv, newenviron);
    break;
  default:
    waitpid(id, &t, 0);
  }
  
  return EXIT_SUCCESS;
}
