#include "simulation.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "program.h"

void simulate_montecarlo(FILE* logfile,             //
                         struct state* sim,         //
                         struct molecule* mol,      //
                         unsigned long num_points,  //
                         progress_t callback) {
  struct point tmp_point;
  struct box aabb;

  // generateur de nombre aleatoire deterministe
  srand(0);

  init_box(&aabb);
  box_add_molecule(&aabb, mol);

  if (sim->points_total == 0) {
    fprintf(logfile, "Starting from scratch...\n");
  } else {
    fprintf(logfile, "Restarting...\n");
  }

  unsigned long ten_percent = 10 * num_points / 100 + 1;
  while (sim->points_total < num_points) {
    box_random_point(&tmp_point, &aabb);
    int is_inside = molecule_contains_point(mol, &tmp_point);
    sim->points_inside += is_inside;
    sim->points_total++;
    if (sim->points_total % ten_percent == 0) {
      double vol = compute_volume(sim, mol);
      unsigned long percent = sim->points_total * 100 / num_points;
      fprintf(logfile, "progression: %ld%% volume: %f\n", percent, vol);
      if (callback) {
        callback(sim, mol);
      }
      /*
       * Simulation d'un bogue fatal. Ne pas modifier.
       */
       bug(sim->num_restart);
    }
  }
}

double compute_volume(struct state* sim, struct molecule* mol) {
  struct box aabb;

  // make sure the box is up-to-date
  init_box(&aabb);
  box_add_molecule(&aabb, mol);

  double vol = box_volume(&aabb);
  double final_volume = vol * sim->points_inside / sim->points_total;
  return final_volume;
}
