QT_SDK_ROOT=/Users/tobii/QtSDK

PRO_FILE=src/EyetrackerBrowser.pro
DMG_MOUNTPOINT=mountpoint
BUILDDIR=build
BUILD_NUMBER?=0.0.1
SDKVERSION=3.0.2
TOBIISDK_DMG=TobiiSDK_$(SDKVERSION).dmg

APP=$(BUILDDIR)/EyetrackerBrowser.app

# those plugins will be removed 
QTPLUGINS := QtDeclarative.framework QtNetwork.framework QtScript.framework QtSql.framework QtSvg.framework QtXmlPatterns.framework

all-Release: $(APP)

set-version:
	sed -i .bak 's/0.0.1/$(BUILD_NUMBER)/' src/AppVersion.hpp

TobiiSDK.framework: $(TOBIISDK_DMG)
	rm -rf TobiiSDK.framework
	hdiutil attach "$(TOBIISDK_DMG)" -noautoopen -mountpoint "$(DMG_MOUNTPOINT)"
	cp -R "$(DMG_MOUNTPOINT)/TobiiSDK.framework" .
	hdiutil detach "$(DMG_MOUNTPOINT)"
	
includes: TobiiSDK.framework
	tar xvfz TobiiSDK.framework/Resources/headers.tar.gz

$(BUILDDIR)/Makefile: $(PRO_FILE) includes TobiiSDK.framework
	mkdir -p $(BUILDDIR)
	$(QT_SDK_ROOT)/Desktop/Qt/473/gcc/bin/qmake $(PRO_FILE) -r -spec macx-g++ CONFIG+=release INCLUDEPATH+=../includes -o $(BUILDDIR)

$(APP): $(BUILDDIR)/Makefile set-version
	rm -rf build/EyetrackerBrowser.app
	cd $(BUILDDIR); make -w
	./embed_private_framework.sh TobiiSDK.framework $(APP)
	# the -no-plugins does not quite work... :-S
	#$(QT_SDK_ROOT)/Desktop/Qt/473/gcc/bin/macdeployqt build/EyetrackerBrowser.app -no-plugins
	$(QT_SDK_ROOT)/Desktop/Qt/473/gcc/bin/macdeployqt build/EyetrackerBrowser.app
	rm -rf $(addprefix $(APP)/Contents/Frameworks/, $(QTPLUGINS))  

.PHONY: all-Release set-version