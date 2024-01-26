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
  EXPECT_EQ(0, 1);
}
