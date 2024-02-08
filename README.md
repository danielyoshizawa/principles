![GitHub commit activity](https://img.shields.io/github/commit-activity/t/danielyoshizawa/principles)
![GitHub issues](https://img.shields.io/github/issues/danielyoshizawa/principles)

# Study of the Principles of Software Development

 - [Purpose](#purpose)
 - [Methodology](#methodology)
 - [Technologies Used](#technologies-used)
 - [Requirements](#requirements)
 - [Directories Structure](#directories-structure)
 - [Local Configurations](#local-configurations)
 - [Build](#build)
 - [Testing](#testing)
 - [Roadmap](#roadmap)
 - [Support](#support)

## Purpose
It is hard to learn everything, remember concepts, and keep up to date with the newest and most modern things, everybody has a way of doing the same thing, and is extremely overwhelming to try to keep up, but there is one thing that never changes, we only say it in different ways, principles. The small concepts that rule all other things in computer science, go as far as energy itself, however, we are not, what we are trying to achieve here is to create a collection of small studies about the basis of software engineering, and answer questions like, what is a pointer, how a vector works, constructor, destructors, what are those?

From there, we want to keep going to higher abstractions, what are patterns and how to use them, libs, frameworks, tests, profiling, and anything else related to software engineering.

This is a lifetime project to keep evolving in the fascinating world of programming, who knows what is to come, our best guess is that these same principles will be the foundation of it.

## Methodology
Our general approach to study is to follow the flow, go to the documentation of what you want to study, take the most basic concept you can find, read, you can type, or write while you do it if you think that it is best, write the most basic example, a kind of hello world of everything, and move on.

While you read you will probably find other concepts that you may or may not previously know, follow those next, if a concept is blocking you from moving on with your study, usually means that you are not at the right place, stop, go one step back, and study a concept that is part of the one that you were blocked, however, if you don't understand fully a concept but it's not stopping you from moving on, keep going, it will probably make sense at the end of your study.

Think about programming, and the study of it, as a very well-unorganized book, each concept is a chapter, that is not in order, and each chapter is a plot to another one, which is very confusing since those don't have a chronological order, to not get lost all the time, we must allow gaps, accept that we can't cover everything at once, and take our time to fill those gaps one at a time. My proposal is a way to minimize the impact of these gaps in our overall understanding of programming.

Summarizing, find out what you want to learn, go to the documentation, get the most basic concept of that topic, read it, create small examples, figure out what composes that concept or what that concept composes, go to one of those concepts, read it, create small examples, and so on. Just remember that enough is enough, you don't need to understand everything, when you have a good idea of what that is and what it does, move on or even better, take a break, play some games, chat with friends, live a little.

## Technologies Used
 - [C++](https://isocpp.org/)
 - [CMake](https://cmake.org/)
 - [Catch2](https://github.com/catchorg/Catch2)
 - [LibCurl](https://curl.se/libcurl/)
 - [Simdjson](https://simdjson.org/)
 - [Boost](https://www.boost.org/)

## Requirements

### C++
This project is using C++20, compiling with GCC v.10.2.1, should work with other versions as well, and other C++ compilers, e.g. clang, since it has support for C++20.

### CMake
CMake is our pre-builder of choice, and we are generating makefiles to build it. You can opt for any builder that CMake provides. You need to have it installed to build the project. To do so run :

`sudo apt install -y cmake`

### Catch2
Catch2 will be downloaded and compiled as you build the project, don't need to worry about installing it locally, we only recommend not constantly doing a full build, because it would that some time to build catch2 as well.

### LibCurl
The current version in use is v8.5.0-2 (openssl version), to install it locally on Debian call : 

`sudo apt install -y libcurl4-openssl-dev`

If not in Debian, or this lib is not available, check your distro repository to see which version is available, or manually install the .deb file. More information can be found [here](https://curl.se/libcurl/)

### Simdjson
We choose to install our packages using aptitude whenever possible, to install on Debian call:

`sudo apt install -y libsimdjson-dev`

More information can be found [here](https://simdjson.org/).

### Boost
On Debian, call:

`sudo apt install -y libboost-all-dev`

More information can be found [here](https://www.boost.org/).

## Directories Structure
```
Project
|-- Challenges : Code challenges study, at this moment we are following the book Cracking the Coding Interview
|-- Fundamentals : C++ fundamentals, mostly the study of the STL (90, 11, 14, 17, 20, 23)
|-- Libs : Study of libs and frameworks, e.g., boost, simdjson, libcurl
|-- Patterns : Study of design patterns implementations and concepts
|-- Utils : Utility code to be used in different projects, e.g. timer, benchmarks, randomizers
|-- BASIC_CONCEPTS.md : Terminology definitions and concepts description used in C++.
|-- LICENSE : GPL2.0 (Fell free to fork, modify, and use it, and if you could give me a Star I'd be very grateful)
|-- README.md : This file you are reading at this very moment. =)
```

## Local Configurations
 - After cloning the project, you need to build the project that you want to work on individually.
 - Some may need additional steps, in those cases, you will need to install any dependencies required.
 - In the case of libs and frameworks, follow the instructions in [*Requirements*](#requirements) section.
 - After that, enter the project directory and create a folder build (replace \<root\> by the project root folder)

    ```
    cd <root>/src
    mkdir build
    ```
 
### Build
To build and run the project 
 - Create the build using CMake and compile 
    ```
    cmake ..
    make
    ```
 - After the build is done, you can execute the program using (replace \<project_name\> with the project name inside the CMakeLists.txt)
    ```
    ./<project_name>
    ```

### Testing
Tests were written using Catch2 and integrated with CTest, to run call : (Not all projects have tests)

    make test

## Roadmap
 - Add Conan to our projects reducing the configuration needed
 - Create a single CMake tree targeting each project to build it individually
 - Write a Readme for each section
 - Patronize the project names to make it easier for the user to call it

More to come as the project evolves.

## Support
Feel free to participate in our discussion page, use our methodology, copy examples, and suggest new topics, learning and mastering code is not easy, but we can do it together!

Wish you a wonderful day, my friend!
