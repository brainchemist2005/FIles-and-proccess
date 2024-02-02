#include "serialize.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: sauvegarder la structure state dans le fichier spécifié.
int save_state(struct state* s, const char* filename) {

  int file_descriptor;

  file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if (file_descriptor != -1) {
    write(file_descriptor, &(s->points_inside), sizeof(long));
    write(file_descriptor, &(s->points_total), sizeof(long));
    write(file_descriptor, &(s->num_restart), sizeof(int));

    // Close the file
    close(file_descriptor);
  }
  return 0;

}

// TODO: charger la structure state depuis le fichier passé en argument.
int load_state(struct state* s, const char* filename) {

  int file_descriptor = open(filename, O_RDONLY);
  if (file_descriptor == -1) {
    perror("Error opening the file");
    return 0;
  }

  read(file_descriptor, &(s->points_inside), sizeof(long));
  read(file_descriptor, &(s->points_total), sizeof(long));
  read(file_descriptor, &(s->num_restart), sizeof(int));

  close(file_descriptor);

  s->num_restart++;
  return 0;

}