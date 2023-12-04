echo "uninstalling dependencies..."
rm -rf /var/TPworms
rm -rf /etc/TPworms
rm /usr/bin/wormsServer
rm /usr/bin/wormsClient
rm -rf /usr/lib/TPworms

echo "Done!"
echo "Removing build directory..."
rm -rf build
echo "Uninstall complete!"