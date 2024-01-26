#include <gtest/gtest.h>
#include <math.h>

#include "molecule.h"

/*
 * Test des molécules, ne rien changer ici.
 */

TEST(Molecule, PointDistance) {
  struct point p1 {
    1.0, 2.0, 3.0
  };
  struct point p2 {
    11.0, 22.0, 33.0
  };
  EXPECT_DOUBLE_EQ(distance(&p1, &p2), sqrt(1400.0));
}

TEST(Molecule, Box) {
  struct box b1;
  init_box(&b1);
  EXPECT_DOUBLE_EQ(box_volume(&b1), 0.0);

  struct sphere s;
  s.radius = 5.0;
  s.center = (struct point){1, 2, 3};
  box_add_sphere(&b1, &s);

  // print_box(stdout, &b1);
  EXPECT_DOUBLE_EQ(b1.coord_min.x, -4);
  EXPECT_DOUBLE_EQ(b1.coord_min.y, -3);
  EXPECT_DOUBLE_EQ(b1.coord_min.z, -2);
  EXPECT_DOUBLE_EQ(b1.coord_max.x, 6);
  EXPECT_DOUBLE_EQ(b1.coord_max.y, 7);
  EXPECT_DOUBLE_EQ(b1.coord_max.z, 8);
  EXPECT_DOUBLE_EQ(box_volume(&b1), 1000.0);
}

TEST(Molecule, RandomRange) {
  srand(0);
  double x1 = -10;
  double x2 = 100;
  for (int i = 0; i < (1 << 10); i++) {
    double val = randf(x1, x2);
    EXPECT_GE(val, x1);
    EXPECT_LE(val, x2);
  }
}

TEST(Molecule, ContainsPoint) {
  struct molecule* m1 = make_molecule(1);
  struct point p1;
  struct point p2;
  set_point_spherical(&p1, m1->atoms[0].radius + 0.01, M_PI_4, M_PI_4);
  set_point_spherical(&p2, m1->atoms[0].radius - 0.01, M_PI_4, M_PI_4);

  EXPECT_FALSE(molecule_contains_point(m1, &p1));
  EXPECT_TRUE(molecule_contains_point(m1, &p2));
  free_molecule(m1);
}
