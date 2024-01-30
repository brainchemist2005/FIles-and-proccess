#include "serialize.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: sauvegarder la structure state dans le fichier spécifié.
int save_state(struct state* s, const char* filename) {

  FILE *file;

  file = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | O_BINARY);

  if (file_descriptor == -1) {
    perror("An error occurred creating the file");
    exit(EXIT_FAILURE);
  }

  printf("%ld %ld\n", s->points_total, s->points_inside);

  // Write the struct members to the file using write
  write(file_descriptor, &(s->points_inside), sizeof(long));
  write(file_descriptor, &(s->points_total), sizeof(long));
  write(file_descriptor, &(s->num_restart), sizeof(int));

  // Close the file
  close(file_descriptor);
  return 0;
}

// TODO: charger la structure state depuis le fichier passé en argument.
int load_state(struct state* s, const char* filename) {
  // Incrémenter ne nombre de redémarrage, ne pas modifier.
  s->num_restart++;
  return 0;
}