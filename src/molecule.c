#include "molecule.h"

#include <float.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double randf(double x1, double x2) {
  double range = x2 - x1;
  double scale = ((double)rand()) / RAND_MAX;
  return x1 + scale * range;
}

const struct point k_origin = {0, 0, 0};

void init_point(struct point* p) { *p = k_origin; }

double distance(struct point* p1, struct point* p2) {
  double dx = p2->x - p1->x;
  double dy = p2->y - p1->y;
  double dz = p2->z - p1->z;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

void set_point(struct point* p, double x, double y, double z) {
  p->x = x;
  p->y = y;
  p->z = z;
}

void set_point_spherical(struct point* p, double r, double theta, double phi) {
  p->x = r * sin(theta) * cos(phi);
  p->y = r * sin(theta) * sin(phi);
  p->z = r * cos(theta);
}

void init_sphere(struct sphere* s) {
  init_point(&s->center);
  s->radius = 1.0;
}

struct molecule* make_molecule(int n) {
  struct molecule* m = malloc(sizeof(struct molecule));
  m->atoms = malloc(sizeof(struct sphere) * n);
  m->num_atoms = n;
  for (int i = 0; i < n; i++) {
    init_sphere(&m->atoms[i]);
  }
  return m;
}

void free_molecule(struct molecule* m) {
  free(m->atoms);
  free(m);
}

void print_molecule(FILE* fd, struct molecule* m) {
  fprintf(fd, "molecule num_atoms: %d\n", m->num_atoms);
  for (int i = 0; i < m->num_atoms; i++) {
    struct sphere* s = &m->atoms[i];
    fprintf(fd, "  atome %d %f (%f,%f,%f)\n",  //
            i,                                 //
            s->radius,                         //
            s->center.x,                       //
            s->center.y,                       //
            s->center.z);
  }
}

void init_box(struct box* b) {
  b->coord_min.x = DBL_MAX;
  b->coord_min.y = DBL_MAX;
  b->coord_min.z = DBL_MAX;

  b->coord_max.x = DBL_MIN;
  b->coord_max.y = DBL_MIN;
  b->coord_max.z = DBL_MIN;

  b->is_empty = 1;
}

// fusionne b dans main
void box_merge(struct box* main, struct box* b) {
  if (b->is_empty) {
    return;
  }
  main->is_empty = 0;

  // min corner
  if (b->coord_min.x < main->coord_min.x) main->coord_min.x = b->coord_min.x;
  if (b->coord_min.y < main->coord_min.y) main->coord_min.y = b->coord_min.y;
  if (b->coord_min.z < main->coord_min.z) main->coord_min.z = b->coord_min.z;

  // max corner
  if (b->coord_max.x > main->coord_max.x) main->coord_max.x = b->coord_max.x;
  if (b->coord_max.y > main->coord_max.y) main->coord_max.y = b->coord_max.y;
  if (b->coord_max.z > main->coord_max.z) main->coord_max.z = b->coord_max.z;
}

void box_add_sphere(struct box* b, struct sphere* s) {
  struct box tmp = {.coord_min = {.x = s->center.x - s->radius,   //
                                  .y = s->center.y - s->radius,   //
                                  .z = s->center.z - s->radius},  //
                    .coord_max = {.x = s->center.x + s->radius,   //
                                  .y = s->center.y + s->radius,   //
                                  .z = s->center.z + s->radius},  //
                    .is_empty = 0};
  box_merge(b, &tmp);
}

void box_add_molecule(struct box* b, struct molecule* m) {
  for (int i = 0; i < m->num_atoms; i++) {
    box_add_sphere(b, &m->atoms[i]);
  }
}

double box_volume(struct box* b) {
  if (b->is_empty) {
    return 0.0;
  }
  return (b->coord_max.x - b->coord_min.x) *  //
         (b->coord_max.y - b->coord_min.y) *  //
         (b->coord_max.z - b->coord_min.z);
}

void print_box(FILE* fd, struct box* b) {
  fprintf(fd, "AABB is_empty: %d\n", b->is_empty);
  fprintf(fd, "AABB volume: %f\n", box_volume(b));
  if (b->is_empty) {
    return;
  }
  fprintf(fd, "AABB coord_min: (%f,%f,%f)\n", b->coord_min.x, b->coord_min.y, b->coord_min.z);
  fprintf(fd, "AABB coord_max: (%f,%f,%f)\n", b->coord_max.x, b->coord_max.y, b->coord_max.z);
}

int molecule_contains_point(struct molecule* m, struct point* p) {
  for (int i = 0; i < m->num_atoms; i++) {
    struct sphere* s = &m->atoms[i];
    if (distance(p, &s->center) < s->radius) {
      return 1;
    }
  }
  return 0;
}

void box_random_point(struct point* p, struct box* b) {
  p->x = randf(b->coord_min.x, b->coord_max.x);
  p->y = randf(b->coord_min.y, b->coord_max.y);
  p->z = randf(b->coord_min.z, b->coord_max.z);
}

struct molecule* make_molecule_ch4() {
  // Créer molécule CH4 (5 atomes)
  struct molecule* m = make_molecule(5);

  // atome central C
  double rc = 1.0;
  double rh = 0.5;
  struct sphere* s1 = &m->atoms[0];
  s1->center = k_origin;
  s1->radius = rc;

  // atome H au dessus
  struct sphere* s2 = &m->atoms[1];
  s2->radius = rh;
  set_point_spherical(&s2->center, s1->radius, 0.0, 0.0);

  // atomes H du bas, espacés de 180 degrés
  struct sphere* s3 = &m->atoms[2];
  s3->radius = rh;
  set_point_spherical(&s3->center, s1->radius, 3 * M_PI_4, 0.0);

  struct sphere* s4 = &m->atoms[3];
  s4->radius = rh;
  set_point_spherical(&s4->center, s1->radius, 3 * M_PI_4, M_PI * 1.0 / 3.0);

  struct sphere* s5 = &m->atoms[4];
  s5->radius = rh;
  set_point_spherical(&s5->center, s1->radius, 3 * M_PI_4, M_PI * 2.0 / 3.0);
  return m;
}
