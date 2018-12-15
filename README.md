# COMP 465 Final Project: Exploring Procedural Terrain Generation Techniques

## Spencer Grant, Nam Phung

## 1. Introduction
This is the repository for a final project for Comp 465 - Interactive Computer Graphics at Macalester College. 
The main objective of this project is to explore the different techniques used to generate terrain procedurally and 
dynamically. This is an aspects of computer graphics that has been studied extensively for the past 30 years, partly thanks
to the development of the gaming industry. Players are always demanding more and more complicated and interesting content 
as games grow in complexity, and terrain plays a vital role in the modern player's experience. As the need of a reliable process of 
generating game terrain without having to handcraft the landscapes from scratch becomes more prominent, there has been a great deal 
of research and literature pertaining to procedural terrain generation.

This project explores the generation realistic terrain for use in gaming. In order to go about implementing a terrain that is randomized as well as being smooth and realistic, we used Perlin noise to determine the y-coordinates of each of the vertices. Once the coordinates of each vertex on the terrain have been calculated, we gave each vertex a brown, sandy color in order to give the appearance of sand dunes. We created a separate variable that updates each time the frame updates in order to give the appearance of the user flying over the sand dunes. We implemented a shader that uses the Oren-Nayar illumination model, which is specifically designed for rougher surfaces like sand, in order to give a more realistic depiction of our terrain.

## 2. Build and run the code
We use CMake as the build tool for this project. To run the project, make sure CMake is installed, along with its command line tools. 
We also make use of two main dependencies:
- MinVR: a low-level C++ library that supports writing graphics applications with a focus on virtual reality applications.
- BasicGraphics: a mid-level C++ library that abstracts some of the usual C++ boilerplate. It also includes classes for creating/loading
models, textures, shaders, etc.

Make sure you have both library installed before building this project. Follow the steps this [link](https://docs.google.com/document/d/1eAPJK8-5PVgs30_pSBYFUQDQ6vxPnC1iGEfDeVRvSkw/edit) to set up your machine to run this project.

There are two ways to download this repository, either as a zip or by using git
### Zip download
To download this project as a zip file, find the green 'Clone or Download' button on the top right hand side. Click that button, then download this project as a zip file.

Once downloaded extract the zip file to your local computer.

### Git download
To download this project using git, run the following command at your terminal:
```
git clone https://github.com/namphung1998/Comp465-Project
```
To build the project with CMake, use the following commands:
```
cd Comp465-Project
mkdir build
cd build
cmake-gui ..
```

CMake will walk you through the process of generating project files for development and testing on your system.
