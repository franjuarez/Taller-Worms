echo "Installing dependencies..."
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install qtbase5-dev
echo "Installation complete!"

echo "Building..."
mkdir build
cd build
cmake ..
sudo make install -j4
echo "Build complete! Ready for use!"