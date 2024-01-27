#include "serialize.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: sauvegarder la structure state dans le fichier spécifié.
int save_state(struct state* s, const char* filename) {

  FILE *file;

  file = fopen(filename, "wb");

  if(file == NULL) {
    printf("An error occured creating the file");
    exit(1);
  }


  fwrite(&(s->points_inside), sizeof(long), 1, file);
  fwrite(&(s->points_total), sizeof(long), 1, file);
  fwrite(&(s->num_restart), sizeof(int), 1, file);

  fclose(file);
  return 0;
}

// TODO: charger la structure state depuis le fichier passé en argument.
int load_state(struct state* s, const char* filename) {
  // Incrémenter ne nombre de redémarrage, ne pas modifier.
  s->num_restart++;
  return 0;
}