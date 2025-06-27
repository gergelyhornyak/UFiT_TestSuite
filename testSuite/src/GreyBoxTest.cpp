#include "testSuiteHeader.hpp"

//#define CONFIG_MAIN  

TEST(TestGBTUFiTCommandLine, TestCorrectInputFile) {

    int expectedExitCode = 0;
    printf("TEST NAME: correct input file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    EXPECT_NO_THROW(std::system(command.c_str()));
}

TEST(TestGBTUFiTCommandLine, TestMissingInputFile) {

    int expectedExitCode = 28416;
    printf("TEST NAME: missing input file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestWrongInputFile) {

    int expectedExitCode = 28416;
    printf("TEST NAME: wrong input file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitInput.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestCorrectBFile) {

    int expectedExitCode = 0;
    printf("TEST NAME: correct B file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestMissingBFile) {

    int expectedExitCode = 28672;
    printf("TEST NAME: missing B file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestWrongBFile) {

    int expectedExitCode = 28672;
    printf("TEST NAME: wrong B file \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufitbfile.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestInvalidCLA) {

    int expectedExitCode = 0;
    printf("TEST NAME: invalid CLA \n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -test 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode = std::system(command.c_str());
    EXPECT_EQ(exitCode, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode << "\n";
}

TEST(TestGBTUFiTCommandLine, TestSequentialRun) {

    int expectedExitCode = 0;
    printf("TEST NAME: run program twice, consequitively\n");
    std::string command = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "ufit_dipole.flf";
    printf("CMD: %s\n",command.c_str());
    int exitCode01 = std::system(command.c_str());
    int exitCode02 = std::system(command.c_str());
    EXPECT_EQ(exitCode01, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode01 << "\n";
    EXPECT_EQ(exitCode02, expectedExitCode) << "Program did not execute successfully, exit code: " << exitCode02 << "\n";
}

// g++ BlackBoxTest.cpp -o BBT -O3 -lgtest -lgtest_main && mv BBT ../target_copy/UFiT && cd ../target_copy/UFiT && ./BBT
// g++ GreyBoxTest.cpp -o GBT2 -O3 -lgtest -lgtest_main && ./GBT2

