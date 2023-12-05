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
if sudo make install -j4 > /dev/null 2>&1; then
  echo "Build complete! Ready for use!"
else
  echo "Error: Failed to install. Check the error message above for details."
fi

