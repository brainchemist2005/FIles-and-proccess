#include "serialize.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: sauvegarder la structure state dans le fichier spécifié.
int save_state(struct state* s, const char* filename) {

  int file;

  file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if (file == -1) {
    perror("An error occurred creating the file");
    exit(EXIT_FAILURE);
  }

  printf("HELLOOOOO%ld %ld\n", s->points_total, s->points_inside);

  // Write the struct members to the file using write
  write(file, &(s->points_inside), sizeof(long));
  write(file, &(s->points_total), sizeof(long));
  write(file, &(s->num_restart), sizeof(int));

  // Close the file
  close(file);
  return 0;
}

// TODO: charger la structure state depuis le fichier passé en argument.
int load_state(struct state* s, const char* filename) {
  // Incrémenter ne nombre de redémarrage, ne pas modifier.
  s->num_restart++;
  return 0;
}
