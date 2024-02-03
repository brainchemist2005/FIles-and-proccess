#include <gtest/gtest.h>

/*
 * Tester la sérialisation de struct simulation
 *
 * Visualiser le contenu du fichier: hexdump -C
 */

#include "serialize.h"

// Utiliser ce fichier pour enregistrer le test
static const char* k_test_file = "test.bin";

TEST(Serialize, SaveLoad) {
  // TODO
  struct state s1 {
    11, 22, 33
  };
  struct state s2;
  save_state(&s1,k_test_file);
  load_state(&s2,k_test_file);
  EXPECT_EQ(s1.points_inside, s2.points_inside);
  EXPECT_EQ(s1.points_total, s2.points_total); 
  EXPECT_EQ(s1.num_restart + 1, s2.num_restart); 
}
