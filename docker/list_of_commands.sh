#!/bin/bash
set -e

# directory path constants
export TEST_SUITE="/ProjectDir/testSuite"
export TEST_TARGET="/ProjectDir/target/UFiT"
export TEST_OUTPUT="/ProjectDir/testOutput"
export TEST_INPUT="/ProjectDir/testInput"
export ADDONS="/ProjectDir/testSuite/addons"
export GTEST2HTML_PATH="/ProjectDir/gtest2html"
export GTEST_OUTPUT="xml:$TEST_OUTPUT/gtest_report.xml"

echo "==< Starting UFiT Test Suite Pipeline >=="

# 1. Run preliminary steps
cd "$TEST_TARGET"
echo "> Preparing spherical example"
python3 Prepare_Spherical_Example.py

# 2. Run UFiT 
if [ -f "$TEST_INPUT/ufit.dat" ]; then
    echo "> Found ufit.dat in testInput. Copying to target..."
    cp "$TEST_INPUT/ufit.dat" "$TEST_TARGET/"
    
    echo "> Running UFIT"
    cd "$TEST_TARGET"
    ./Run_UFiT -c ufit.dat
else
    echo "> WARNING: No ufit.dat found in testInput. Running with default CLI parameters"
    
    echo "> Running UFIT"
    cd "$TEST_TARGET"
    ./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf
fi

# Temporary debug version:
echo "> Starting TestHub..."
"$TEST_SUITE/build/TestHub" "$TEST_TARGET/" > "$TEST_OUTPUT/testhub_output.txt" 2>&1 || echo "> TestHub CRASHED with exit code $?"

#"$TEST_SUITE/build/TestHub" "$TEST_TARGET/" > "$TEST_OUTPUT/testHub_results.txt"

# 4. Generate reports (GTest to HTML)
echo "> Running GTest2HTML for report generation"
if [ -f "$TEST_OUTPUT/gtest_report.xml" ]; then
    echo "> Generating HTML Report..."
    python3 $ADDONS/gtest2html.py "$TEST_OUTPUT/gtest_report.xml" "$TEST_OUTPUT/gtest_report.html"
fi

echo "> Profiling the profile data using gprof and valgrind (& callgrind)"

cd "$TEST_TARGET"
pwd

echo "> [SKIP] Valgrind Memcheck"
# echo "> [UNSKIP] Valgrind Memcheck"
# valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --verbose \
# --log-file="$TEST_OUTPUT/valgrindMemcheck.txt" \
# ./Run_UFiT -c ufit.dat

#echo "> [SKIP] Valgrind Callgrind"
echo "> [UNSKIP] Valgrind Callgrind"
valgrind --tool=callgrind --callgrind-out-file=$TEST_OUTPUT/valgrindCallgrind.txt \
--collect-jumps=yes \
./Run_UFiT -c ufit.dat

#echo "> [SKIP] Valgrind Massif"
echo "> [UNSKIP] Valgrind Massif"
valgrind --tool=massif \
--massif-out-file="$TEST_OUTPUT/valgrindMassif.txt" \
./Run_UFiT -c ufit.dat

# 2.2) Profiling phase: gprof and gcov: '-p' argument

# echo "> Make UFiT with profiling"
pwd
make FFLAGS="-O0 -fopenmp -pg -fprofile-arcs -ftest-coverage"
./Run_UFiT -c ufit.dat

# 2.3) Customising phase: change python codes to work with current setup
#    ! [IMPORTANT]: this phase is due to the docker image has no UI to show graphics
#    !               however should be omitted once the UFiT modules are changed

# echo "> Comment out line to view 3D model with mlab"
# sed -i 's|mlab.view|#mlab.view|' Visualize_Spherical_Example3D.py

# sed -i 's|from mayavi import mlab|from mayavi import mlab\nmlab.options.offscreen = True|' Visualize_Spherical_Example3D.py
# sed -i 's|plt.show()|plt.savefig("Dipole_Example.png")|' Dipole_Example.py
# sed -i 's|plt.show()|#plt.show()|' HMI_Example.py
# sed -i 's|/change/this/path|./|' HMI_Example.py
# sed -i 's|/change/this/path|./|' Dipole_Example.py

# echo "> Dipole Example"
# python3 Dipole_Example.py

# here the CLI program should be ran to produce accurate code coverage data
# ./Run_UFiT -c ufit.dat
# ./Run_UFiT -testWrongFlag 123

#echo "> [SKIP] Gprof profiler"
echo "> [UNSKIP] Gprof profiler"

gprof ./Run_UFiT gmon.out > $TEST_OUTPUT/gprofile.txt

#echo "> [SKIP] Gcov profiler"
echo "> [UNSKIP] Gcov profiler"
gcov *.F90
lcov --gcov-tool gcov --capture --directory . --output-file coverage.info
genhtml --output-directory html coverage.info
mv html $TEST_OUTPUT/
mv coverage.info $TEST_OUTPUT/gcov_coverage.txt
mv $TEST_OUTPUT/html $TEST_OUTPUT/codeCoverageHTML

# 2.4) Profiling phase: plotting results

#echo "> [SKIP] Plot profiling scores: gprof, callgrind, memcheck, massif"
echo "> [UNSKIP] Plot profiling scores: gprof, callgrind, memcheck, massif"

python3 $ADDONS/gprof2dot.py $TEST_OUTPUT/gprofile.txt | dot -Tpng -o $TEST_OUTPUT/gprofDiagram.png
python3 $ADDONS/gprof2dot.py --format=callgrind $TEST_OUTPUT/valgrindCallgrind.txt | dot -Tpng -o $TEST_OUTPUT/callgrindDiagram.png
python3 $ADDONS/massifPlotter.py $TEST_OUTPUT/valgrindMassif.txt $TEST_OUTPUT/massifDiagram.png
python3 $ADDONS/memcheckPlotter.py $TEST_OUTPUT/valgrindMemcheck.txt $TEST_OUTPUT/memcheckDiagram.png

echo "> [SKIP] Visualize Spherical Example"
#python3 Visualize_Spherical_Example.py
[ -f Spherical_Example.png ] && mv Spherical_Example.png $TEST_OUTPUT/Spherical_Example.png

#./Run_UFiT -g 1 -pp -nb -sf -b Example.bin -i Example2.inp -o Example2.flf

echo "> [SKIP] Visualize 3D Spherical Example"
#python3 Visualize_Spherical_Example3D.py
[ -f Spherical_Example3D.png ] && mv Spherical_Example3D.png $TEST_OUTPUT/Spherical_Example3D.png

echo "> [SKIP] HMI Example"
#python3 HMI_Example.py
[ -f HMI_Example.png ] && mv HMI_Example.png $TEST_OUTPUT/HMI_Example.png


# 4) Versions phase: log every 3rd Party Software's version

echo "> Start logging software versions\n"

echo "> Logging software versions\n"
echo "--Software versions--" > "$TEST_OUTPUT/version.log"
{
    gfortran --version | head -n 1
    g++ --version | head -n 1
    make --version | head -n 2
    python3 --version
    pip --version || echo "pip not found"
    git --version || echo "git not found"
    gprof --version | head -n 1
    gcov --version | head -n 1
    lcov --version || echo "lcov not found"
    valgrind --version || echo "valgrind not found"
    #tex --version || echo "tex not found"
    dot -V 2>&1 || echo "Graphviz not found"
} >> "$TEST_OUTPUT/version.log"

echo "> Logging Python package versions\n"
echo "--Python package versions--" >> "$TEST_OUTPUT/version.log"
pip freeze >> "$TEST_OUTPUT/version.log"
echo "--END OF FILE--" >> "$TEST_OUTPUT/version.log"
echo "==< Test Suite Pipeline Finished >=="