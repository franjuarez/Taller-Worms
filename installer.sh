#!/bin/bash

set -e

GREEN='\033[0;32m'
GRAY='\033[1;30m'
NC='\033[0m' # No Color

show_ascii_art() {
cat << "EOF"
                                                                                                    
 /$$  /$$  /$$  /$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$$
| $$ | $$ | $$ /$$__  $$ /$$__  $$| $$_  $$_  $$ /$$_____/
| $$ | $$ | $$| $$  \ $$| $$  \__/| $$ \ $$ \ $$|  $$$$$$ 
| $$ | $$ | $$| $$  | $$| $$      | $$ | $$ | $$ \____  $$
|  $$$$$/$$$$/|  $$$$$$/| $$      | $$ | $$ | $$ /$$$$$$$/ 
 \_____/\___/  \______/ |__/      |__/ |__/ |__/|_______/  
                                                                            
  /$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$ | $$   /$$  /$$$$$$ 
 /$$__  $$ /$$__  $$| $$_  $$_  $$ |____  $$| $$  /$$/ /$$__  $$
| $$  \__/| $$$$$$$$| $$ \ $$ \ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$
| $$      | $$_____/| $$ | $$ | $$ /$$__  $$| $$_  $$ | $$_____/
| $$      |  $$$$$$$| $$ | $$ | $$|  $$$$$$$| $$ \  $$|  $$$$$$$
|__/       \_______/|__/ |__/ |__/ \_______/|__/  \__/ \_______/
EOF
echo ""
}


main() {
    show_ascii_art
    help
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
            install_dependencies
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

install_game() {
  echo "Installing game..."
  if [ -d "build" ]; then
    sudo rm -rf build
  fi
  mkdir build
  cd build
  cmake ..
  if sudo make install -j8; then
    echo "Build complete! Ready for use!"
  else
    echo "Error: Failed to install. Check the error message above for details."
  fi
}


uninstall_game() {
  echo "Uninstalling game..."
  sudo rm -rf /var/TPworms || true
  sudo rm -rf /etc/TPworms || true
  sudo rm /usr/bin/wormsServer || true
  sudo rm /usr/bin/wormsClient || true
  sudo rm -rf /usr/lib/TPworms || true
  
  echo "Done!"
  echo "Removing build directory..."
  
  if sudo rm -rf build || true; then
      echo "Uninstall complete!"
  else    
      echo "Error: Failed to uninstall. Check the error message above for details."
  fi
}


uninstall_dependencies(){
  echo "Uninstaling dependencies..."
  sudo apt remove cmake || true
  sudo apt remove libsdl2-dev || true
  sudo apt remove libsdl2-image-dev || true
  sudo apt remove libsdl2-ttf-dev || true
  sudo apt remove libsdl2-mixer-dev || true
  sudo apt remove qtbase5-dev || true
  echo "Completed!"
}

main
