#ifndef TP1_MOL_H_
#define TP1_MOL_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct point {
  double x;
  double y;
  double z;
};

struct sphere {
  struct point center;
  double radius;
};

struct molecule {
  struct sphere* atoms;
  int num_atoms;
};

struct box {
  struct point coord_min;
  struct point coord_max;
  int is_empty;
};

double randf(double x1, double x2);

// Point API
extern const struct point k_origin;
void init_point(struct point* p);
double distance(struct point* p1, struct point* p2);
void set_point(struct point* p, double x, double y, double z);
void set_point_spherical(struct point* p, double r, double theta, double phi);

// Sphere API
void init_sphere(struct sphere* s);

// Molecule API
struct molecule* make_molecule(int n);
void free_molecule(struct molecule* m);
void print_molecule(FILE* fd, struct molecule* m);
int molecule_contains_point(struct molecule* m, struct point* p);

// Axis Aligned Bounding Box API
void init_box(struct box* b);
void print_box(FILE* fd, struct box* b);
void box_merge(struct box* main, struct box* b);
void box_add_sphere(struct box* b, struct sphere* s);
void box_add_molecule(struct box* b, struct molecule* m);
void box_random_point();
double box_volume(struct box* b);

// Create CH4 molecule
struct molecule* make_molecule_ch4();

#ifdef __cplusplus
}
#endif

#endif
