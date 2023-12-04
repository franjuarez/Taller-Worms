echo "uninstalling..."
sudo rm -rf /var/TPworms
sudo rm -rf /etc/TPworms
sudo rm /usr/bin/wormsServer
sudo rm /usr/bin/wormsClient
sudo rm -rf /usr/lib/TPworms
echo "Done!"
echo "Removing build directory..."
if sudo rm -rf build; then
    echo "Uninstall complete!"
else    
    echo "Error: Failed to uninstall. Check the error message above for details."
fi