/* Imię nazwisko: Jakub Kuciński
 * Numer indeksu: 309881
 *
 * Oświadczam, że:
 *  - rozwiązanie zadania jest mojego autorstwa,
 *  - jego kodu źródłowego dnie będę udostępniać innym studentom,
 *  - a w szczególności nie będę go publikować w sieci Internet.
 *
 * Q: Czemu procedura printf nie jest wielobieżna, a snprintf jest?
 * A: Procedura printf używa wspólnego globalnego bufora, stąd przerwanie jej wykonanie i wykonanie innego printfa spowoduje pofragmentowanie tekstu. Procedura snprintf używa lokalnego bufora,
 * dzięki czemu jej wywołanie może zostać przerwane i wykonane inne, bez obawy przed pofragmentowaniem tekstu.
 */

#define _GNU_SOURCE
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <unistd.h>
#include <sys/mman.h>

void handler(int sig, siginfo_t *info, void *ucontext)
{
  char buffer [300];
  int cx = -1;
  int kod = info->si_code;
  ucontext_t *ut = (ucontext_t *)ucontext;
  if (kod == 1)
  {
    cx = snprintf(buffer, 300, "Adres powodujacy blad odwolania: %p\nTyp bledu: MAPERR\nAdres wierzcholka stosu: 0x%llx \nAdres instukcji powodujacej blad: 0x%llx \n", info->si_addr,  ut->uc_mcontext.gregs[REG_RSP], ut->uc_mcontext.gregs[REG_RIP]);
  }
  else
  {
    if (kod == 2)
    {
      cx = snprintf(buffer, 300, "Adres powodujacy blad odwolania: %p\nTyp bledu: ACCERR\nAdres wierzcholka stosu: 0x%llx \nAdres instukcji powodujacej blad: 0x%llx \n", info->si_addr,  ut->uc_mcontext.gregs[REG_RSP], ut->uc_mcontext.gregs[REG_RIP]);
    }
  }
  int n;
  if (cx >= 0 && cx < 300)
    n = write(2, buffer, strlen(buffer));
  n = write(2, "\nbacktrace:\n", 12);
  void *buffer2[300];
  int calls = backtrace(buffer2, sizeof(buffer2) / sizeof(void *));
  backtrace_symbols_fd(buffer2, calls, 2);
  if (n == -1)
    exit(EXIT_FAILURE);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) 
{
  struct sigaction newhandler;
  sigemptyset(&(newhandler.sa_mask));
  newhandler.sa_sigaction = &handler;
  newhandler.sa_flags = SA_SIGINFO;
  sigaction(SIGSEGV, &newhandler, NULL);
  if(argc == 2 && strcmp(argv[1],"--maperr") == 0)
  {
    char *adres = mmap(NULL, 8, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    munmap(adres, 8);
    (*adres) = 0;
  }
  else
  {
    if(argc == 2 && strcmp(argv[1],"--accerr") == 0)
    {
      char *adres = mmap(NULL, 8, PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
      (*adres) = 0;
    }
  }
  return EXIT_SUCCESS;
}
