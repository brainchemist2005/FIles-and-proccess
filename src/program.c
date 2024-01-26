#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Simulation de bogue, ne rien modifier ici.
 */

static int bug_id = -1;
static int bug_max = 3;
static const char* bug_file = ".bug_id.bin";

int init_program() {
  bug_id = 0;
  struct stat status;
  if (stat(bug_file, &status) == 0) {
    int fd = open(bug_file, O_RDWR);
    if (fd < 0) {
      perror("open");
      return -1;
    }
    if (read(fd, &bug_id, sizeof(bug_id)) < 0) {
      perror("read");
      return -1;
    }
    bug_id = (bug_id + 1) % (bug_max + 1);
    close(fd);
  }

  int fd = open(bug_file, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd < 0) {
    perror("open");
    return -1;
  }
  if (write(fd, &bug_id, sizeof(bug_id)) < 0) {
    perror("read");
    return -1;
  }

  return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
void bug(int num_restart) {
  if (bug_id >= bug_max) {
    return;
  }
  fprintf(stderr, "bug %d\n", bug_id);
  fflush(stderr);

  if (bug_id == 0) {
    volatile int* x = NULL;
    *x = 42;
    (void)x;
  } else if (bug_id == 1) {
    volatile int i = 1;
    volatile int j = i / 0;
    (void)j;
  } else if (bug_id == 2) {
    kill(getpid(), SIGKILL);
  } else {
    if (num_restart == 0) {
      fprintf(stderr, "KABOUM BADABOUM!\n");
      exit(255);
    }
    // otherwise no bug
  }
}
#pragma GCC diagnostic pop
