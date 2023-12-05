echo "Conecting proxys for tests..." #admin mal
cd build
cmake -DTESTING=ON . > /dev/null 2>&1
cmake --build . -j8 > /dev/null 2>&1
echo "Running Tests"
ctest -rerun-failed --output-on-failure
echo "All Done!!"