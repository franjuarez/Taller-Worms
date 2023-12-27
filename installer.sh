#!/bin/bash

set -e

GREEN='\033[0;32m'
GRAY='\033[1;30m'
RED='\033[0;31m'
NC='\033[0m'

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
  echo -e "${GREEN}Installing dependencies...${NC}"
  sudo sh -c '
    apt-get install cmake
    apt-get install libsdl2-dev
    apt-get install libsdl2-image-dev
    apt-get install libsdl2-ttf-dev
    apt-get install libsdl2-mixer-dev
    apt-get install qtbase5-dev
  ' | while IFS= read -r line; do
    echo -e "${GRAY}${line}${NC}"
  done
  echo -e "${GREEN}Installation complete!${NC}"
}

install_game() {
  echo -e "${GREEN}Installing game...${NC}"
  if [ -d "build" ]; then
    sudo rm -rf build
  fi
  mkdir build
  cd build
  cmake ..
  if sudo make install -j8; then
    echo -e "${GREEN}Build complete! Ready for use!${NC}"
  else
    echo -e "${RED}Error: Failed to install. Check the error message above for details.${NC}"
  fi
}


uninstall_game() {
  echo -e "${GREEN}Uninstalling game...${NC}"
  sudo rm -rf /var/TPworms || true
  sudo rm -rf /etc/TPworms || true
  sudo rm /usr/bin/wormsServer || true
  sudo rm /usr/bin/wormsClient || true
  sudo rm -rf /usr/lib/TPworms || true
  
  if sudo rm -rf build || true; then
      echo -e "${GREEN}Uninstall complete!${NC}"
  else    
      echo -e "${RED}Error: Failed to uninstall. Check the error message above for details.${NC}"
  fi
}


uninstall_dependencies(){
  echo -e "${GREEN}Uninstaling dependencies...${NC}"
  sudo apt remove cmake || true
  sudo apt remove libsdl2-dev || true
  sudo apt remove libsdl2-image-dev || true
  sudo apt remove libsdl2-ttf-dev || true
  sudo apt remove libsdl2-mixer-dev || true
  sudo apt remove qtbase5-dev || true
  echo -e "${GREEN}Completed!${NC}"
}

main
