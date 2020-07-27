# vidyo.io-connector-electron

Run VidyoConnector web app on Windows or macOS PC using Electron.

Follow these instructions to download corresponding developer package(s) from vidyo.io, install tools for building and running electron with add-on, then run the vidyo.io-connector-electron app.

## Prerequisites

Create a directory for the Electron sample (e.g. electronsample).
Download the Vidyo Client SDK for macOS and/or Windows.  We need the libraries and include files from these packages to build Electron add-on.
Extract the content of the package(s) into the new directory.
> macOS SDK: https://static.vidyo.io/latest/package/VidyoClient-OSXSDK.zip  
> Windows SDK (Visual Studio 2017): https://static.vidyo.io/latest/package/VidyoClient-WinVS2017SDK.zip  

```
$ ls -l electronsample
total 32
drwxr-xr-x@ 7 ...   238 Jul 27 17:58 VidyoClient-OSXSDK
drwxr-xr-x@ 7 ...   238 Jul 27 17:31 VidyoClient-WinVS2017SDK
```

## Installing

Download sample electron add-on source code to the same directory.

```
$ ls -l electronsample
total 32
-rw-r--r--  1 ...  1474 Jun 16 13:12 VidyoAddon.cc
drwxr-xr-x@ 7 ...   238 Jul 27 17:58 VidyoClient-OSXSDK
drwxr-xr-x@ 7 ...   238 Jul 27 17:31 VidyoClient-WinVS2017SDK
-rw-r--r--  1 ...  1822 Aug 11 17:31 binding.gyp
-rw-r--r--  1 ...  1999 Aug 17 16:54 main.js
-rw-r--r--  1 ...   366 Jun 16 13:13 package.json
```

Install electron and node-gyp:
```
npm install electron@9.1.1
npm install -g node-gyp
```

## Build and Run

### Set environment variables

For Mac:
```
export VIDYO_CLIENT_INCL_DIR=$PWD/VidyoClient-OSXSDK/include
export VIDYO_CLIENT_LIB_DIR=$PWD/VidyoClient-OSXSDK/lib/macos
```

For Windows:
```
set VIDYO_CLIENT_INCL_DIR=%cd%\VidyoClient-WinVS2017SDK\include
set VIDYO_CLIENT_LIB_DIR=%cd%\VidyoClient-WinVS2017SDK\lib\windows\x64\Release
```

### Build Vidyo Client Electron add-on

For Mac:
```
node-gyp rebuild --target=9.1.1 --arch=x64 --dist-url=https://atom.io/download/electron
```
For Windows:
```
node-gyp rebuild --target=9.1.1 --arch=x64 --dist-url=https://atom.io/download/electron -msvs_version=2017
```

### Run the App
```
npm start
```

### Note
Replace 9.1.1 with desired electron version number as needed.

### Known Issues
Windows 10 update 1709 introduced an issue which prevents video from rendering properly.
The workaround is to upgrade to version 1.8.3 or later of Electron and to disable hardware acceleration, which can be done as follows in main.js:
```
app.disableHardwareAcceleration();
```
