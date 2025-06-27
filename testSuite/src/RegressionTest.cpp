#include "testSuiteHeader.hpp"

const std::string FORTRAN_EXECUTABLE = ufit_dir_path+ "Run_UFiT";
const std::string OUTPUT_FILE = ufit_dir_path+ "output.bin";
const std::string GOLDEN_FILE = "../goldenFiles/golden_output.bin";
const double PERF_TIME_SECONDS = 2.0;

std::vector<char> readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    return std::vector<char>(std::istreambuf_iterator<char>(file), {});
}

// Test to check binary output matches golden file
TEST(RegressionTest, BinaryOutputMatch) {
    // Run the Fortran program
    int ret = std::system(FORTRAN_EXECUTABLE.c_str());
    ASSERT_EQ(ret, 0) << "Fortran program execution failed";

    // Read both files
    auto goldenData = readBinaryFile(GOLDEN_FILE);
    auto outputData = readBinaryFile(OUTPUT_FILE);

    // Compare byte-by-byte
    ASSERT_EQ(goldenData, outputData) << "Binary output does not match golden file";
}

// Test to check execution time
TEST(RegressionTest, PerformanceBenchmark) {
    auto start = std::chrono::high_resolution_clock::now();
    int ret = std::system(FORTRAN_EXECUTABLE.c_str());
    auto end = std::chrono::high_resolution_clock::now();

    ASSERT_EQ(ret, 0) << "Fortran program execution failed";

    std::chrono::duration<double> elapsed = end - start;
    ASSERT_LE(elapsed.count(), PERF_TIME_SECONDS)
        << "Execution time exceeded benchmark (" << elapsed.count() << "s vs "
        << PERF_TIME_SECONDS << "s)";
}

TEST(RegressionTest, TestUfitDipoleFLF) {
    // diff oldOutput newOutput
    printf("Requires 2 successful run of UFiT to check output files");
    std::string command01 = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "old_ufit_dipole.flf";
    std::string command02 = ufit_dir_path + "Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b " + ufit_dir_path + "ufit_dipole.bin" + " -i " + ufit_dir_path + "ufitdipole.inp" + " -o " + ufit_dir_path + "new_ufit_dipole.flf";
    std::system(command01.c_str());
    std::system(command02.c_str());
    std::ifstream old_output_flf("../target_copy/UFiT/old_ufit_dipole.flf");
    std::ifstream new_output_flf("../target_copy/UFiT/new_ufit_dipole.flf");
    std::string old_output, new_output;
    getline(old_output_flf, old_output);
    getline(new_output_flf, new_output);
    printf("old output_flf length: %d\n",old_output.length());
    printf("new output_flf length: %d\n",new_output.length());
    EXPECT_EQ(old_output,new_output) << "Outputs do not match bitwise \n";
}

