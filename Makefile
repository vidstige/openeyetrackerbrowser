BUILDDIR=bin/Release
SDKVERSION=3.0.0
SDKDEBX64=libtobii-sdkcore_$(SDKVERSION)_amd64
SDKDEBX86=libtobii-sdkcore_$(SDKVERSION)_i386
PWD=`pwd`
BUILD_NUMBER?=0.0.1

all-Release:

set-version:
	sed -i 's/0.0.1/$(BUILD_NUMBER)/' src/AppVersion.hpp

x64-prereq: external/$(SDKDEBX64).deb
	echo Running x64-prereq target
	mkdir -p external
	dpkg -x external/$(SDKDEBX64).deb external/$(SDKDEBX64)

x86-prereq: external/$(SDKDEBX86).deb
	echo Running x86-prereq target
	mkdir -p external	
	dpkg -x external/$(SDKDEBX86).deb external/$(SDKDEBX86)

x64-Release: set-version x64-prereq
	echo Running x64-Release target
	mkdir -p $(BUILDDIR)
	qmake src/EyetrackerBrowser.pro -r -spec linux-g++-64 -o $(BUILDDIR) CONFIG+=release LIBS+=-L$(PWD)/external/$(SDKDEBX64)/usr/lib INCLUDEPATH+=$(PWD)/external/$(SDKDEBX64)/usr/include/
	cd $(BUILDDIR); make -w
	
x86-Release: set-version x86-prereq
	echo Running x86-Release target
	mkdir -p $(BUILDDIR)
	qmake src/EyetrackerBrowser.pro -spec linux-g++-32 -o $(BUILDDIR) CONFIG+=release LIBS+=-L$(PWD)/external/$(SDKDEBX86)/usr/lib INCLUDEPATH+=$(PWD)/external/$(SDKDEBX86)/usr/include/
	cd $(BUILDDIR); make -w


x64-build-packages: x64-Release
	LD_LIBRARY_PATH=$(PWD)/external/$(SDKDEBX64)/usr/lib make -C packaging/linux packages 

x86-build-packages: x86-Release
	LD_LIBRARY_PATH=$(PWD)/external/$(SDKDEBX86)/usr/lib make -C packaging/linux packages 


clean-packages:
	make -C packaging/linux clean

clean:
	rm -rf $(BUILDDIR)

.PHONY: all-Release x64-Release x86-Release x86-build-packages x64-build-packages x64-prereq x86-prereq clean set-version
