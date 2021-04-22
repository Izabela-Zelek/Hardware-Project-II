!/bin/bash

clear

cd $HOME

mkdir Projects

cd Projects

##########################################################################
echo Current Working Directory
##########################################################################
cwd=$(pwd)

sudo apt-get update

##########################################################################
echo Installing figlet for onscreen messages
##########################################################################

sudo apt-get install figlet

##########################################################################
figlet Installing AVR Toolchain
##########################################################################

sudo apt-get install -y gcc-avr binutils-avr avr-libc avrdude g++ git libsdl2-dev

## Enable Visual Studio Code access to directory
sudo ln -s /usr/lib/avr/include/ /usr/local/include/avr
sudo chmod 775 /usr/local/include/avr

##########################################################################
figlet Downloading uzebox kernel
##########################################################################

git clone https://github.com/Uzebox/uzebox.git

##########################################################################
figlet Building uzebox kernel and tools [make], will take time
##########################################################################

cd $cwd/uzebox/tools/packrom
make

cd $cwd/uzebox/tools/uzem
make

cd $cwd/uzebox/demos/Bootloader/default
make

## Enable Visual Studio access to directory
sudo ln -s $HOME/Projects/uzebox/kernel /usr/local/include/kernel
sudo chmod 775 /usr/local/include/kernel

##########################################################################
figlet Downloading StarterKit
##########################################################################

cd $cwd

echo "Download StarterKit #?: this will overwrite exiting work!"
echo "Enter a number choice:"

select yn in "Y" "n"; do
    case $yn in
	Y)
	    git clone https://MuddyGames@bitbucket.org/MuddyGames/uzeboxstarterkit.git
	    cd $cwd/uzeboxstarterkit/Tools
	    break;;
	n)
	    break;;
    esac
done
	        
	       
##########################################################################
figlet Installing Visual Studio Code (using SNAP)
##########################################################################

echo "Install Visual Studio Code"
echo "Enter a number choice:"

select yn in "Y" "n"; do
    case $yn in
	Y)
	    ## sudo dpkg -i code_1.12.2-1494422229_amd64.deb
	    ## sudo apt-get install -f # Install dependencies
		
		sudo rm /etc/apt/preferences.d/nosnap.pref
		sudo apt update
		sudo apt install snapd
		sudo snap install code --classic		
	    sudo update-alternatives --set editor /usr/bin/code

	    ##############################################################
	    figlet Starting Visual Studio Code
	    ##############################################################

	    code folder $cwd/uzeboxstarterkit/StarterKit/ --install-extension ms-vscode.cpptools --install-extension rockcat.avr-support
	    
	    break;;
	n)
	    break;;
    esac
done

##########################################################################
figlet Setup Symbolic Link for .s to .asm so  assembly is highlighted
##########################################################################

ln -s $cwd/uzeboxstarterkit/StarterKit/StarterKitEngine.s $cwd/uzeboxstarterkit/StarterKit/StarterKitEngine.asm

##########################################################################
figlet Building StarterKit [make]
##########################################################################

cd $cwd/uzeboxstarterkit
make
