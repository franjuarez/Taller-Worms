#!/bin/bash

set -e

main() {
    help()
    while true; do
        echo "Enter a character (or 'q' to quit):"
        read input

        if [ "$input" == "q" ]; then
            echo "See you!"
            break
        fi
        process_input "$input"
    done
}

process_input() {
    case "$1" in
        "d")
            install_dependecies
            ;;
        "i")
            install_game
            ;;
        "a")
            install_dependencies
            install_game
            ;;
        "u")
            uninstall_game
            ;;
        "j")
            uninstall_dependencies
            ;;
        "p")
            uninstall_game
            uninstall_dependencies
            ;;
        "h")
            help
            ;;
        *)
            echo "Character not recognized. Try again.\n"
            ;;
    esac
}

help() {
    echo "Install options:"
    echo "  'd': To install dependencies"
    echo "  'i': To install the game"
    echo "  'a': To install the dependencies and the game"
    echo "  'h': To get the available options"
  
    echo ""
    
    echo "Uninstall options:"
    echo "  'u': To uninstall the game"
    echo "  'j': To uninstall the dependencies"
    echo "  'p': To uninstall the game and the dependencies"

    echo ""
    
    echo "Use 'q' to quit the installer"
}

install_dependencies() {
  echo "Installing dependencies..."
  sudo apt-get install cmake
  sudo apt-get install libsdl2-dev
  sudo apt-get install libsdl2-image-dev
  sudo apt-get install libsdl2-ttf-dev
  sudo apt-get install libsdl2-mixer-dev
  sudo apt-get install qtbase5-dev
  echo "Installation complete!"
}

install_game(){
  echo "Installing game..."
  mkdir build
  cd build
  cmake ..
  if sudo make install -j8; then
    echo "Build complete! Ready for use!"
  else
    echo "Error: Failed to install. Check the error message above for details."
  fi
}

uninstall_game(){
  echo "Uninstalling game..."
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
}

uninstall_dependencies(){
  echo "Uninstaling dependencies..."
  sudo apt remove cmake
  sudo apt remove libsdl2-dev
  sudo apt remove libsdl2-image-dev
  sudo apt remove libsdl2-ttf-dev
  sudo apt remove libsdl2-mixer-dev
  sudo apt remove qtbase5-dev
  echo "Completed!"
}

main
