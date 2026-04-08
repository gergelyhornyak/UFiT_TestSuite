#!/bin/bash
set -e

# --- Paths ---
export TEST_SUITE="/ProjectDir/testSuite"
export TEST_TARGET="/ProjectDir/target/UFiT"
export TEST_OUTPUT="/ProjectDir/testOutput"
export TEST_INPUT="/ProjectDir/testInput"
export ADDONS="/ProjectDir/testSuite/addons"
export GTEST2HTML="/ProjectDir/testSuite/addons/gtest2Html"
export CONFIG_FILE="/ProjectDir/scripts/testSheet.cfg"
# GTest output env var needs to be set in order to produce xml file
export GTEST_OUTPUT="xml:$TEST_OUTPUT/gtest_report.xml"

# --- Helper Function to check Config ---
is_on() {
    grep -qi "^$1=ON" "$CONFIG_FILE"
}

echo "==< Starting UFiT Pipeline >=="

# --- 1. Preliminary Steps ---

echo "> Preparing spherical example..."
cd "$TEST_TARGET"
python3 Prepare_Spherical_Example.py


# --- 2. Main UFiT Execution ---
if is_on "RUN_UFIT"; then
    cd "$TEST_TARGET"
    if [ -f "$TEST_INPUT/ufit.dat" ]; then
        echo "> Running UFiT with provided ufit.dat"
        cp "$TEST_INPUT/ufit.dat" .
        ./Run_UFiT -c ufit.dat
    else
        echo "> Running UFiT with default parameters"
        ./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf
    fi
fi

# --- 3.1. TestHub ---
if is_on "RUN_TESTHUB"; then
    echo "> Starting TestHub"
    "$TEST_SUITE/build/TestHub" "$TEST_TARGET/" > "$TEST_OUTPUT/testhub_output.txt" 2>&1 || echo "> TestHub CRASHED with exit code $?"
fi

# 3.2. Generate reports (GTest to HTML)
if is_on "GENERATE_GTEST_REPORT"; then
    echo "> Running GTest2HTML for report generation"
    if [ -f "$TEST_OUTPUT/gtest_report.xml" ]; then
        mkdir -p "$TEST_OUTPUT/htmlReport"
        python3 $GTEST2HTML/gtest2html.py "$TEST_OUTPUT/gtest_report.xml" "$TEST_OUTPUT/htmlReport/gtest_report.html"
        
    fi
fi

# --- 4. Profiling (Valgrind) ---
if is_on "VALGRIND_MEMCHECK"; then
    echo "> Valgrind Memcheck"
    valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --verbose --log-file="$TEST_OUTPUT/valgrindMemcheck.txt" ./Run_UFiT -c ufit.dat
fi

if is_on "VALGRIND_CALLGRIND"; then
    echo "> Valgrind Callgrind"
    valgrind --tool=callgrind --callgrind-out-file="$TEST_OUTPUT/valgrindCallgrind.txt" --collect-jumps=yes ./Run_UFiT -c ufit.dat
fi

if is_on "VALGRIND_MASSIF"; then
    echo "> Valgrind Massif"
    valgrind --tool=massif --massif-out-file="$TEST_OUTPUT/valgrindMassif.txt" ./Run_UFiT -c ufit.dat
fi

# --- 5. Recompile & Coverage ---
if is_on "GENERATE_GCOV"; then
    echo "> Recompiling for coverage"
    cd "$TEST_TARGET"
    make FFLAGS="-O0 -fopenmp -pg -fprofile-arcs -ftest-coverage"
    ./Run_UFiT -c ufit.dat
  
    echo "> Generating GCOV and LCOV reports"
    gprof ./Run_UFiT gmon.out > "$TEST_OUTPUT/gprofile.txt"
    gcov *.F90
    lcov --gcov-tool gcov --capture --directory . --output-file coverage.info
    genhtml -o "$TEST_OUTPUT/codeCoverageHTML" coverage.info
    mv html $TEST_OUTPUT/
    mv $TEST_OUTPUT/html $TEST_OUTPUT/codeCoverageHTML
    mv coverage.info $TEST_OUTPUT/gcov_coverage.txt
fi

# --- 6. Plotting ---
if is_on "PLOT_DIAGRAMS"; then
    echo "> Generating diagrams"
    python3 $ADDONS/gprof2dot.py $TEST_OUTPUT/gprofile.txt | dot -Tpng -o $TEST_OUTPUT/gprofDiagram.png
    python3 $ADDONS/gprof2dot.py --format=callgrind $TEST_OUTPUT/valgrindCallgrind.txt | dot -Tpng -o $TEST_OUTPUT/callgrindDiagram.png
    python3 $ADDONS/massifPlotter.py $TEST_OUTPUT/valgrindMassif.txt $TEST_OUTPUT/massifDiagram.png
    python3 $ADDONS/memcheckPlotter.py $TEST_OUTPUT/valgrindMemcheck.txt $TEST_OUTPUT/memcheckDiagram.png
fi

# --- 7. Version Logging ---
if is_on "LOG_VERSIONS"; then
    echo "> Logging software versions"
    {
        gfortran --version | head -n 1
        python3 --version
        valgrind --version
        gprof --version | head -n 1
        gcov --version | head -n 1
        lcov --version || echo "lcov not found"
        dot -V 2>&1 || echo "Graphviz not found"

    } > "$TEST_OUTPUT/version.log"
fi

echo "==< Pipeline Finished >=="