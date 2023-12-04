echo "Installing dependencies..."
sudo apt-get install cmake
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install qtbase5-dev
<<<<<<< HEAD
echo "Done!"
=======
echo "Installation complete!"
>>>>>>> cfe8b0abad93ea48f1f35a5897c98a1c7cbdf993

echo "Building..."
mkdir build
cd build
cmake ..
<<<<<<< HEAD
make install -j4
=======
sudo make install -j4
echo "Build complete! Ready for use!"
>>>>>>> cfe8b0abad93ea48f1f35a5897c98a1c7cbdf993
