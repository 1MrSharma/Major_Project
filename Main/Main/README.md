## BImage - A bitmap file format data structure viewer software
###### Software that tells structure of *'.bmp'* image and also changes the image to **black and white**! 

### Table of contents
* [Introduction](#Introduction)
* [Technologies](#Technologies)
* [Minimun hardware requirement](#Minimum-hardware-requirement)
* [Launch](#Launch)
* [Illustrations](#Illustrations)
* [Features](#Features)
* [Example of use](#Example-of-use)
* [Project status](#Project-status)
* [Limitations and Future Improvements](#Limitations-and-Future-Improvements)
* [Sources](#Sources)

### Introduction
* It is an image processing software.
* Can read and decrypt binary data of bitmap file.
* Done for the purpose of learning software creation.
* Used microsoft's general techniques and api's.
* Independent project under the guidance of Mr.Tapan Pandey.
* It shows us the internal data within bmp image.
* Converts the bmp image to black and white image.
* Takes "*.bmp" input from command line and process the image.
* Appliction is made for educational purpose.
* Done as an industrial trainee project.

### Technologies 
* C++14 and C as primary development languages.
* Microsoft cl compiler.
* Visual studio development environment.

### Minimum hardware requirement
* Compiler which support C++11 or above.
* Windows compatible.

### Launch
* Main <Option> <Source file> <Destination file>.
* Options list
	* -h2 : DIB header
		* <-h2> <Source.bmp>
	* -h1 : Bitmap file header
		* <-h1> <Source.bmp>
	* -i  : Basic information
		* <-i> <Source.bmp>
	* -p  : pixel array 
		*  <-p> <Source.bmp>
	* -o  : Original image copy 
		* <-o> <Source.bmp> <Destination.bmp>
	* -bw : Monochrome image
		* <-bw> <Source.bmp> <Destination.bmp>


### Illustrations
* ![Option used](https://github.com/1MrSharma/Major_Project/blob/White_Belt/OptionImage.png)

### Features
* Display the information of the image file.
* Can open,close,read & write file.
* Generates error message for wrong input.


### Example of use
* ![Original Image](https://github.com/1MrSharma/Major_Project/blob/White_Belt/24-bit.bmp)
* ![Black and white converted](https://github.com/1MrSharma/Major_Project/blob/White_Belt/blackAndWhiteConverted.bmp)

### Project status
* Still under development.
	
### Limitations and Future Improvements
* Picture blend feature.
* Adjusting brightness saturation hue.
* Can be used with only small input size images.
* Can only work with 24-bit bmp. 

### Sources

* BMP File Format : https://en.wikipedia.org/wiki/BMP_file_format