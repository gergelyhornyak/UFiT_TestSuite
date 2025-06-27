#!/bin/bash

# directory path constants
export TEST_SUITE="/ProjectDir/testSuite"
export ADDONS="/addons"
export TEST_TARGET="/ProjectDir/target"
export TEST_TARGET_NAME="UFiT"
export TEST_OUTPUT="/ProjectDir/testOutputs"
export GTEST_PATH="/ProjectDir/googletest"
export GTEST2HTML_PATH="/ProjectDir/gtest2html"
export GTEST_OUTPUT="xml:$TEST_OUTPUT/gtest_report.xml"

# 1) Setup phase: download UFiT, install GTest

cd $TEST_TARGET
# remove existing installation
echo "> clean old UFiT"
rm -rf $TEST_TARGET/$TEST_TARGET_NAME 2> /dev/null

# download, build and install GTEST
echo "> Install GTEST"
git clone https://github.com/google/googletest.git -b v1.16.0 $GTEST_PATH
cd $GTEST_PATH
mkdir build
cd build
cmake .. 
make
make install

# clone target program
echo "> Pull UFiT repo"
git clone https://github.com/Valentin-Aslanyan/UFiT.git $TEST_TARGET/$TEST_TARGET_NAME
cd $TEST_TARGET/$TEST_TARGET_NAME

# 2) Profiling phase: create example data, example runtime data
#                      then run valgrind and gprof

# 2.1) Profiling phase: valgrind: no '-p'

# first round: make without profiling
echo "> Make UFiT without profiling"
make

echo "> Prepare Spherical Example"
python3 Prepare_Spherical_Example.py

echo "> Run UFIT"
./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf

echo "> Profiling the profile data using gprof and valgrind (& callgrind)"

echo "> [UNSKIP] Valgrind Memcheck"
valgrind --leak-check=full --show-leak-kinds=all -s \
--log-file="$TEST_OUTPUT/valgrindMemcheck.txt" \
./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf

echo "> [UNSKIP] Valgrind Callgrind"
valgrind --tool=callgrind --callgrind-out-file=$TEST_OUTPUT/valgrindCallgrind.txt \
--collect-jumps=yes \
./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf

echo "> [UNSKIP] Valgrind Massif"
valgrind --tool=massif \
--massif-out-file="$TEST_OUTPUT/valgrindMassif.txt" \
./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf

# replace with sed inplace adding "-pg" to Makefile
sed -i 's|$(FC) |$(FC) -pg -fprofile-arcs -ftest-coverage |' Makefile
echo "> Extended Makefile with 'pg, fprofile-arcs, ftest-coverage' arguments for profiling"

# 2.2) Profiling phase: gprof and gcov: '-p' argument

# second round: make with profiling
echo "> Make UFiT with profiling"
make

# 2.3) Customising phase: change python codes to work with current setup
#    ! [IMPORTANT]: this phase is due to the docker image has no UI to show graphics
#    !               however should be omitted once the UFiT modules are changed

echo "> Comment out line to view 3D model with mlab"
sed -i 's|mlab.view|#mlab.view|' Visualize_Spherical_Example3D.py

#sed -i 's|from mayavi import mlab|from mayavi import mlab\nmlab.options.offscreen = True|' Visualize_Spherical_Example3D.py
sed -i 's|plt.show()|plt.savefig("Dipole_Example.png")|' Dipole_Example.py
sed -i 's|plt.show()|#plt.show()|' HMI_Example.py
sed -i 's|/change/this/path|./|' HMI_Example.py
sed -i 's|/change/this/path|./|' Dipole_Example.py

echo "> Dipole Example"
python3 Dipole_Example.py

echo "> Run UFIT multiple times"
# here most of the permutation of the CL program should be ran to produce accurate code coverage data
./Run_UFiT
./Run_UFiT -testWrongFlag 123

./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf
./Run_UFiT -g 1 -pp -nb -se -b Example.bin -i Example.inp -o Example.flf
./Run_UFiT -g 1 -pp -nb -sc -b Example.bin -i Example.inp -o Example.flf
./Run_UFiT -g 1 -pp -nb -cs -b Example.bin -i Example.inp -o Example.flf

./Run_UFiT -g 2 -pp -nb -sq -b Example.bin -i Example.inp -o Example.flf
./Run_UFiT -g 2 -pp -nb -se -b Example.bin -i Example.inp -o Example.flf
./Run_UFiT -g 2 -pp -nb -sc -b Example.bin -i Example.inp -o Example.flf

./Run_UFiT -g 1 -pp -nb -sf -b Example.bin -i Example2.inp -o Example2.flf
./Run_UFiT -g 1 -pp -nb -sq -b Example.bin -i Example2.inp -o Example2.flf
./Run_UFiT -g 2 -pp -nb -sf -b Example.bin -i Example2.inp -o Example2.flf
./Run_UFiT -g 0 -pp -nb -sf -b Example.bin -i Example2.inp -o Example2.flf

./Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -se -sf -sq -g 1 -b ufit_dipole.bin -i ufitdipole.inp -o ufit_dipole.flf
./Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -nb -se -sf -sq -g 0 -b ufit_dipole.bin -i ufitdipole.inp -o ufit_dipole_norm.flf
./Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -ic -se -sf -sq -g 1 -b ufit_dipole.bin -i ufitdipole.inp -o ufit_dipole_ic.flf
./Run_UFiT -dl 0.005 -ms 5000 -np 4 -pp -ic -nb -se -sf -sq -g 0 -b ufit_dipole.bin -i ufitdipole.inp -o ufit_dipole_ic_norm.flf

echo "> [UNSKIP] Gprof profiler"
gprof ./Run_UFiT gmon.out > $TEST_OUTPUT/gprofile.txt

echo "> [UNSKIP] Gcov profiler"

gcov *.F90
lcov --gcov-tool gcov --capture --directory . --output-file coverage.info
genhtml --output-directory html coverage.info
mv html $TEST_OUTPUT/
mv coverage.info $TEST_OUTPUT/gcov_coverage.txt
mv $TEST_OUTPUT/html $TEST_OUTPUT/codeCoverageHTML


# 2.4) Profiling phase: plotting results

echo "> [UNSKIP] Plot profiling scores: gprof, callgrind, memcheck, massif"
python3 $TEST_SUITE/$ADDONS/gprof2dot.py $TEST_OUTPUT/gprofile.txt | dot -Tpng -o $TEST_OUTPUT/gprofDiagram.png
python3 $TEST_SUITE/$ADDONS/gprof2dot.py --format=callgrind $TEST_OUTPUT/valgrindCallgrind.txt | dot -Tpng -o $TEST_OUTPUT/callgrindDiagram.png
python3 $TEST_SUITE/$ADDONS/massifPlotter.py $TEST_OUTPUT/valgrindMassif.txt $TEST_OUTPUT/massifDiagram.png
python3 $TEST_SUITE/$ADDONS/memcheckPlotter.py $TEST_OUTPUT/valgrindMemcheck.txt $TEST_OUTPUT/memcheckDiagram.png

echo "> [SKIP] Visualize Spherical Example"
#python3 Visualize_Spherical_Example.py
[ -f Spherical_Example.png ] && mv Spherical_Example.png $TEST_OUTPUT/Spherical_Example.png

./Run_UFiT -g 1 -pp -nb -sf -b Example.bin -i Example2.inp -o Example2.flf

echo "> [SKIP] Visualize 3D Spherical Example"
#python3 Visualize_Spherical_Example3D.py
[ -f Spherical_Example3D.png ] && mv Spherical_Example3D.png $TEST_OUTPUT/Spherical_Example3D.png

echo "> [UNSKIP] HMI Example"
python3 HMI_Example.py
[ -f HMI_Example.png ] && mv HMI_Example.png $TEST_OUTPUT/HMI_Example.png

# 3) Testing phase: running unit tests, black box and grey box tests, regression tests

echo "> Run unit tests"
cd $TEST_SUITE
cmake .
cmake --build .
cd bin
./TestHub $TEST_TARGET/$TEST_TARGET_NAME/ > $TEST_OUTPUT/testHub_results.txt

# 3.1) [OPTIONAL] GTest to HTML

git clone https://gitlab.uni-koblenz.de/agrt/gtest2html.git $GTEST2HTML_PATH
cd $GTEST2HTML_PATH
python3 gtest2html.py $TEST_OUTPUT/gtest_report.xml $TEST_OUTPUT/gtest_report.html

# 4) Versions phase: log every 3rd Party Software's version

echo -e "< Software versions >\n" > $TEST_OUTPUT/version.log
echo -e "$(gfortran --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(g++ --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(make --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(python3 --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(pip --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(git --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(gprof --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(gcov --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(lcov --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(valgrind --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(tex --version)\n" >> $TEST_OUTPUT/version.log
echo -e "$(dot -V 2>&1)\n" >> $TEST_OUTPUT/version.log

echo -e "< Pip packages >\n" >> $TEST_OUTPUT/version.log
echo -e "$(pip freeze)\n" >> $TEST_OUTPUT/version.log

exec "$@"  # This allows passing the CMD arguments to the container
