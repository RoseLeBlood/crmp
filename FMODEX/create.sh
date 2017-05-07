#!/bin/bash
version=4.44.21

function fmodex_create {
	mkdir -p bin/usr/include/fmodex/
	mkdir -p bin/usr/lib/
	mkdir -p bin/usr/lib32/
	
	wget http://www.fmod.org/download/fmodex/api/Linux/fmodapi${version//./}linux.tar.gz
	tar xf fmodapi${version//./}linux.tar.gz

	mv fmodapi${version//./}linux/api/inc/* bin/usr/include/fmodex/

	mv fmodapi${version//./}linux/api/lib/libfmodex64.so bin/usr/lib/
	mv fmodapi${version//./}linux/api/lib/libfmodex64-4.44.21.so bin/usr/lib/
	mv fmodapi${version//./}linux/api/lib/libfmodexL64.so bin/usr/lib/
	mv fmodapi${version//./}linux/api/lib/libfmodexL64-4.44.21.so bin/usr/lib/
	mv fmodapi${version//./}linux/api/lib/libfmodex.so bin/usr/lib32/
	mv fmodapi${version//./}linux/api/lib/libfmodex-4.44.21.so bin/usr/lib32/
	mv fmodapi${version//./}linux/api/lib/libfmodexL.so bin/usr/lib32/
	mv fmodapi${version//./}linux/api/lib/libfmodexL-4.44.21.so bin/usr/lib32/
}
function fmodex_deb {
	mkdir -p bin/DEBIAN/
	cp control bin/DEBIAN/
	echo "Version:" $version >> bin/DEBIAN/control
	
	sudo chown -R root:root bin/*
	sudo dpkg -b bin ../libfmodex-devel-$version.any.deb

	sudo chown -R $USER:$USER bin/
	sudo chown -R $USER:$USER ../../libfmodex-devel-$version.any.deb
}
function fmodex_clean {
	rm -r bin/
	rm fmodapi${version//./}linux.tar.gz
	rm ../libfmodex-devel-$version.any.deb
}


case "$1" in
	clean)
		fmodex_clean	
	;;
	deb)
		fmodex_deb
	;;
	arch)

	;;
	*)
		fmodex_clean
		fmodex_create
	;;
esac





