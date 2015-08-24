# nodal - C++ Audio Unit Generator library

NODAL is a Unit Generator audio framework. It has been developed at Dinahmoe in 2012 to 
realize native applications using the interface of the Web Audio API (Javascript), that 
felt comfortable and had already been used in the other company’s projects.

## Supported platforms
The library has been successfully used for the following platforms:
- Mac OS
- Linux
- iOs
- Android (NDK)

For all these platforms, the library is able to be used online or as an audio file rendering tool.

## Binary download
The binary for the chosen platform are in the releases section. Please note that builds are not made for each commit, so for the latest updates it’s better to build from source.

## Structure of the repository
The main GIT repo uses submodules to download other libraries for dinahmoe. This arrangement has been kept because it allows to keep the same directory structure as in Dinahmoe’s private projects. 
These repos, that can be used independently, are:
* dm-audioengine: the bare audioengine itself
* dm-audiomidi: classes to read-write audio files
* dm-utils: a collection of C++ utility classes, used by mostly all other libraries
* dm-cmake: a collection of CMake scripts
* dm-dsp: digital signal processing building blocks, used by the audio engine
* dm-log: a simple logging facility

## Download
After having cloned this repository, and cd’ed into the repo’s directory, update the submodules, issuing
* git submodule update
* git submodule foreach "(git checkout master; git pull)&"
This will download the dependencies mentioned above.

## Building
You must have cmake installed. From the main directory, you can issue the following commands i the terminal
* mkdir build && cd build && cmake .. && make

## This will compile and build the static library, merging all the other libraries into one.
* make install 
will install the library

## Examples
The examples directory contains a few examples of using the library with Openframeworks, JUCE, PortAudio, and libsndfile for offline bounce.

Extras
The directory “Extras” contains instruments and effects built using the basic “vanilla” building blocks provided by the audio engine. It can be compared to the objects contained in the “Extended” version of pure data.

The API
The interface to the librarier resembles the one of the WebAudio API.
The AudioContext is the main class on which the user operates on: it holds the current status of the node graph, 





