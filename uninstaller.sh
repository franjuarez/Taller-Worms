echo "uninstalling dependencies..."
sudo apt-get remove cmake
sudo apt-get remove libsdl2-dev
sudo apt-get remove libsdl2-image-dev
sudo apt-get remove libsdl2-ttf-dev
sudo apt-get remove libsdl2-mixer-dev
sudo apt-get remove qtbase5-dev
echo "Done!"
echo "Removing build directory..."
rm -rf build
echo "Uninstall complete!"