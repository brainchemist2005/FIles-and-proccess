enable_testing()

add_executable(test_serialize
  test_serialize.cpp
)
target_link_libraries(test_serialize
  core
  GTest::gtest_main
)

add_executable(test_molecule
  test_molecule.cpp
)
target_link_libraries(test_molecule
  core
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_serialize)
gtest_discover_tests(test_molecule)

configure_file(test_autorestart.sh.in test_autorestart.sh)

add_test(NAME test_autorestart
  COMMAND test_autorestart.sh
)
