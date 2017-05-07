#!/bin/bash

MACHINE_TYPE=`uname -m`
VERSION=0.50.28-r53

function crmp_build {
	rm -r ../bin
	mkdir -p ../bin/usr/bin/
	mkdir -p ../bin/usr/share/crmp/
	mkdir -p ../bin/usr/share/icons/crmp/
	mkdir -p ../bin/usr/share/applications/
	mkdir -p ../bin/etc/



	echo "Build main programm ..."
	mkdir build
	cd build
	qmake-qt4 ../crmp.pro -r -spec linux-g++
	make 
	chmod 755 crmp
	cp crmp ../../bin/usr/bin/

	echo "Build dsp_normalize programm ..."
	cd ../dsp/dsp_normalize/
	mkdir build
	cd build
	qmake-qt4 ../dsp_normalize.pro -r -spec linux-g++
	make
	chmod 755 libdsp_normalize.so.1.0.0 
	cp libdsp_normalize.so.1.0.0 ../../../../bin/usr/share/crmp/dsp_normalize.dsp

	echo "Build dsp_normalize programm ..."
	cd ../../dsp_parameq/
	mkdir build
	cd build
	qmake-qt4 ../dsp_parameq.pro -r -spec linux-g++
	make
	chmod 755 libdsp_parameq.so.1.0.0
	cp libdsp_parameq.so.1.0.0 ../../../../bin/usr/share/crmp/dsp_parameq.dsp

	echo "Install config file"
	cd ../../..
	chmod 755 unix/crmp.xml
	cp unix/crmp.xml ../bin/etc/crmp.xml

	echo "Install app-icon"
	chmod 644 icons/media_player.png
	cp icons/media_player.png ../bin/usr/share/icons/crmp/application_crmp.png

	echo "Install desktop file"
	chmod 644 unix/crmp.desktop
	cp unix/crmp.desktop ../bin/usr/share/applications/crmp.desktop	
}
function crmp_clean {
 	echo "Clean build"
	rm -r build/
	rm -r  dsp/dsp_normalize/build/
	rm -r  dsp/dsp_parameq/build/
	sudo rm -r ../bin/
}
function crmp_deb {
	echo "Make deb"
	mkdir -p ../bin/DEBIAN

	sudo chown -R root:root ../bin/
	if [ ${MACHINE_TYPE} == 'x86_64' ]; then
	  sudo cp control64 ../bin/DEBIAN/control
	  sudo echo "Version:" $VERSION >> ../bin/DEBIAN/control
	  sudo dpkg -b ../bin ../crmp-$VERSION.x86_64.deb
	else
	  sudo cp control32 ../bin/DEBIAN/control
          sudo echo "Version:" $VERSION >> ../bin/DEBIAN/control
	  sudo dpkg -b ../bin ../crmp-$VERSION.x86.deb
	fi
	sudo chown -R $USER:$USER ../bin/
	sudo chown $USER:$USER ../*.deb
}

case "$1" in
	clean)
		crmp_clean	
	;;
	deb)
		crmp_deb
	;;
	arch)

	;;
	*)
		crmp_clean
		crmp_build
	;;
esac



