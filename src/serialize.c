#include "serialize.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: sauvegarder la structure state dans le fichier spécifié.
int save_state(struct state* s, const char* filename) {
  return 0;
}

// TODO: charger la structure state depuis le fichier passé en argument.
int load_state(struct state* s, const char* filename) {
  // Incrémenter ne nombre de redémarrage, ne pas modifier.
  s->num_restart++;
  return 0;
}
