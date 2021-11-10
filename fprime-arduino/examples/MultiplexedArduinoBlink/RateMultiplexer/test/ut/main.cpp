#include "Tester.hpp"

TEST(Nominal, FwdOperationTest) {
    Arduino::Tester tester;
    tester.testFwdSched();
}
TEST(Nominal2, RateControlTest) {
    Arduino::Tester tester;
    tester.testRateControlPorts();
}//*/
TEST(Nominal1, TopologyInitTest) {
  Arduino::Tester tester;
  tester.testTopologyInit();
}//*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
