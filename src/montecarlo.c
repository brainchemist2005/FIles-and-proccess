#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "molecule.h"
#include "program.h"
#include "simulation.h"

// Constante du nom de fichier pour enregistrer la progression
static const char* k_state_file = "state.bin";

// TODO: définir une fonction de rappel pour sauvegarder la progression. Passer cette fonction comme
// dernier argument à simulate_montecarlo()
int save_progress_callback(struct state* sim, struct molecule* mol) {
  save_state(sim, "../backup_file");
  return 0;
}

int main() {
  // initialisation du programme, ne pas modifier
  setvbuf(stdout, NULL, _IONBF, 0);
  if (init_program() < 0) {
    return -1;
  }

  struct state* sim = malloc(sizeof(struct state));
  struct molecule* mol = make_molecule_ch4();

  sim->points_inside = 0;
  sim->points_total = 0;
  sim->num_restart = 0;

  load_state(sim,"../backup_file");

  // TODO: charger la dernière sauvegarde du fichier

  // Imprime les information sur la simulation
  print_molecule(stdout, mol);
  {
    struct box tmp_box;
    init_box(&tmp_box);
    box_add_molecule(&tmp_box, mol);
    print_box(stdout, &tmp_box);
  }

  unsigned long num_points = (1UL << 20);
  simulate_montecarlo(stdout, sim, mol, num_points, save_progress_callback);

  double final_volume = compute_volume(sim, mol);
  fprintf(stdout, "Molecule volume: %f\n", final_volume);
  fprintf(stdout, "Simulation completed with success!\n");

  // TODO: supprimer le fichier d'état en cas de succès. Le calcul recommencera du début.
  unlink("../backup_file");

  return 0;
}
