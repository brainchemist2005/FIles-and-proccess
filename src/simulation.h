#ifndef TP1_SIM_H_
#define TP1_SIM_H_

#include <stdio.h>

#include "molecule.h"

#ifdef __cplusplus
extern "C" {
#endif

struct state {
  unsigned long points_inside;  // nombre de points à l'intérieur
  unsigned long points_total;   // nombre de points généré total jusqu'à maintenant
  int num_restart;              // nombre de fois que le programme a été redémarré
};

// fonction de rappel pour la progression
typedef int (*progress_t)(struct state*, struct molecule*);

void simulate_montecarlo(FILE* logfile,             //
                         struct state* sim,         //
                         struct molecule* mol,      //
                         unsigned long num_points,  //
                         progress_t callback);

double compute_volume(struct state* sim,  //
                      struct molecule* mol);

int save_state(struct state* s, const char* filename);
int load_state(struct state* s, const char* filename);

#ifdef __cplusplus
}
#endif

#endif
