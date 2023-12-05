echo "Installing Tests..."
cd build
cmake -DTESTING=ON .
cmake --build . -j8
echo "Running Tests"
ctest -rerun-failed --output-on-failure
echo "All Done!!"