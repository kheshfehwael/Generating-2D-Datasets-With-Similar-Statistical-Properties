<a id="top"></a>
# Visualize Your Data: Generating Datasets with Dissimilar Custom Shapes and Similar Statistical Properties
<img src="https://user-images.githubusercontent.com/92784846/156038153-ab7096c4-c754-4b74-8bfc-7c739e5536af.jpg" width="240" height="240"> <img src="https://user-images.githubusercontent.com/92784846/156038727-106ea6d9-da9c-4361-9f61-cb42395f38e2.jpg" width="240" height="240"> <img src="https://user-images.githubusercontent.com/92784846/156038734-cada3326-e61a-45da-8df2-ceee991aae04.jpg" width="240" height="240"> <img src="https://user-images.githubusercontent.com/92784846/156038740-785f133c-adf1-4c24-a629-1cb6b3b0c6b5.jpg" width="240" height="240">

This repository contains the project submit of Stephan Olbrich and Wael Mohamad Kheshfeh for the course "Algorithm Engineering WiSe 2021/2022". The structure of the repository is as follows: The folder [project](project) contains the actual program. Inside of that there are subdirectories in [tools](project/tools) with which a library is created for the main program [same_stats](project/same_stats.cpp) to be used. In the directory [additional_files](project/additional_files) .csv and .txt files are located which can be used to work with the program. It is recommended to select this directory as the working directory. The folder [Catch2_Testing_FrameWork](Catch2_Testing_FrameWork) has a similar structure and contains the testing framework to the program. In the main directory you can also find the corresponding [Paper](Visualize&#32;Your&#32;Data.pdf) to our project.

**Contents**<br>
[How to use it](#how-to-use-it)<br>
[Structure](#structure)<br>
[Dependencies for Project generator](#dependencies-for-Project-generator)<br>

## How to use it

There are two options, how to use it. Either you download zip-package or you can clone this repository to your project directory.
If you use the repository directly, you should be aware that the project generator uses relative paths, e.g. input and output paths.
To familiarize yourself with the software, read our [Project Paper](Visualize&#32;Your&#32;Data.pdf). A good starting point is the "Background" guide. There are further sections describing the individual building blocks of the project generator.


Once installation, test the project using the Generating 2D Datasets function: 

    same_stats slanted_less heart_test -h -i 
    
  or 
    
    same_stats --usage
    
for more information.
    
    
If you need help reading the documentation, please contact Flag: 


    same_stats --help

## Structure

The Program is structured as follows: The main file [same_stats](project/same_stats.cpp) acts as the interface for the user through the command line and does all the modifications on the datasets. The subdirectory [tools](project/tools) is created as a library with the help of CMake. This library contains functions that are used by the main file. Those functions are used for the calculation of the statistics, as interface to read/write .csv files, discretize the datasets and calculate the distance matrix.

## Dependencies for Project generator

* Cmake 
* Project Jupyter 
* Visual studio (Makefile with GCC ARM) 
