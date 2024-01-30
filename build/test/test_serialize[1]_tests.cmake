add_test( Serialize.SaveLoad /home/rabahlemaici/Bureau/FIles-and-proccess/build/bin/test_serialize [==[--gtest_filter=Serialize.SaveLoad]==] --gtest_also_run_disabled_tests)
set_tests_properties( Serialize.SaveLoad PROPERTIES WORKING_DIRECTORY /home/rabahlemaici/Bureau/FIles-and-proccess/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( test_serialize_TESTS Serialize.SaveLoad)
