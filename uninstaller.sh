echo "uninstalling dependencies..."
sudo rm -rf /var/TPworms
sudo rm -rf /etc/TPworms
sudo rm /usr/bin/wormsServer
sudo rm /usr/bin/wormsClient
sudo rm -rf /usr/lib/TPworms

echo "Done!"
echo "Removing build directory..."
sudo rm -rf build
echo "Uninstall complete!"