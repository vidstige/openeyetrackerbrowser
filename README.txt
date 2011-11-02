Open Eye Tracker Browser
------------------------
Use the Open Eye Tracker Browser to browse, upgrade and configure your tracker.


Building the open tracker browser
---------------------------------
The Tobii SDK 3.0 is need to build the open tracker browser. Download it for free at
http://www.tobii.com/eye-tracking-research/global/products/software/tobii-software-development-kit/
Or just google for "tobii eye tracking sdk download"

You will need to download a diffrent SDK package for the varios platforms and place the downloaded file in a pre-defined location. The make file/msbuild file will extract the Tobii SDK package automatically.

Note: If you got this source code by downloading the SDK, you need to move this folder outside the SDK since this code depends on the SDK.

Windows
1. Place the tobiisdk-Win32.zip in the same folder as this README file.
2. You need VS2008 installed to build.
3. You need QT installed to build.
4. Just run "msbuild build.msproj"
5. When opening the .pro file in QtCreator, select Desktop->MVS2008 tool-chain rather than mingw

Linux
1. You need QT development packages installed.
2. Place the .deb package inside a folder named "external"
3. Just run "make x86-Release"

Mac
1. You need QT development frameworks installed.
2. Place the downloaded TobiiSDK.dmg file in the same folder as this README
3. Just run "make -f darwin.mk"