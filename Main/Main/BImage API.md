# Table of content
##### MAIN
* [Main](#Main)
	* [Funtion's](#Function's)
	* [Object's](#Object's)
	* [Buffer's](#Buffer's)
	* [Variable's](#Variable's)
	* [Constant's'](#Constant's')

##### CLASSES

* [BMP](#BMP)
	* [Parameters](#Parameters)
		* [private](#private)
			* [BMPstructure](#BMPstructure)
				* [*m_pStructurepointer](#*m_pStructurepointer)
	* [Functions](#Functions)
		* [public](#public)
			* [DWORD](#DWORD)
				* [fnreturnSizeBMP()](#fnreturnSizeBMP())
				* [fnreturnOffsetpixelarray()](#fnreturnOffsetpixelarray())
				* [fnreturnSizebitmapinfoheader()](#fnreturnSizebitmapinfoheader())
				* [fnreturnCompressionmethod()](#fnreturnCompressionmethod())
				* [fnreturnRawimagesize()](#fnreturnRawimagesize())
				* [fnreturnHorizontalresolution()](#fnreturnHorizontalresolution())
				* [fnreturnVerticalresolution](#fnreturnVerticalresolution())
				* [fnreturnColorpallete](#fnreturnColorpallete())
				* [fnreturnImportantcolors()](#fnreturnImportantcolors())
			* [INT32](#INT32)
				* [fnreturnBitamapwidth()](#fnreturnBitamapwidth())
				* [fnreturnBitmapheight()](#fnreturnBitmapheight())
			* [WORD](#WORD)
				* [fnreturnFiletype()](#fnreturnFiletype())
				* [fnreturnReserved1()](#fnreturnReserved1())
				* [fnreturnReserved2()](#fnreturnReserved2())
				* [fnreturnColorplanes()](#fnreturnColorplanes())
				* [fnreturnColordepth()](#fnreturnColordepth())
			*[void](#void)
				* [fnsetStructurepointer(BMPstructure*)](#fnsetStructurepointer(BMPstructure*))
			*[BOOL](#BOOL)
				* [fncheckFiletype()](#fncheckFiletype())
				
* [CmdLine](#CmdLine)
	* [private](#private)
		* [Parameters](#Parameters)
			* [vector](#vector)
				* [Optionslist](#Optionslist)
			* [string](#string)
				* [strCurrentOption](#strCurrentOption)
	* [public](#public)
		* [Functions](#Functions)
			* [BOOL](#BOOL)
				* [Searchoptionslist(string)](#Searchoptionslist(string))
				* [Checkextension(TCHAR*,const char[])](#Checkextension(TCHAR*,const char[]))
			* [void](#void)
				* [Addoptions(string)](#Addoptions(string))
				* [SetCurrentOption(string)](#SetCurrentOption(string))
			* [string](#string)
				* [GetCurrentOption()](#GetCurrentOption())
* [Error](#Error)
	* [private](#private)
		* [Parameters](#Parameters)
			* [DWORD](#DWORD)
				* [m_dwErrCode](#m_dwErrCode)
			*[string](#string)
				* [szErrorString](#szErrorString)
	* [public](#public)
		* [Functions](#Functions)
			* [LPCTSTR](#LPCTSTR)
				* [fngeterrordescription()](#fngeterrordescription())
				* [fngeterrordescription(DWORD)](#fngeterrordescription(DWORD))
			* [void](#void)
				* [fnsetErrCode(DWORD)](#fnsetErrCode(DWORD))
			*[DWORD](#DWORD)
				* [fngetErrCode(void)](#fngetErrCode(void))
			*[string](#string)
				* [getErrorString()](#getErrorString())

##### Structure

* [BMPstructure](#BMPstructure)
	* [Parameters](#Parameters)
		* [WORD](#WORD)
			* [m_wFiletype](#m_wFiletype)
			* [m_wReserved1](#m_wReserved1)
			* [m_wReserved2](#m_wReserved2)
			* [m_wColorplanes](#m_wColorplanes)
			* [m_wColordepth](#m_wColordepth)
		* [DWORD](#DWORD)
			* [m_dwSizeBMP](#m_dwSizeBMP)
			* [m_dwOffsetpixelarray](#m_dwOffsetpixelarray)
			* [m_dwSizebitmapinfoheader](#m_dwSizebitmapinfoheader)
			* [m_dwCompressionmethod](#m_dwCompressionmethod)
			* [m_dwRawimagesize](#m_dwRawimagesize)
			* [m_dwHorizontalresolution](#m_dwHorizontalresolution)
			* [m_dwVerticalresolution](#m_dwVerticalresolution)
			* [m_dwColorpallete](#m_dwColorpallete)
			* [m_dwImportantcolors](#m_dwImportantcolors)
		* [INT32](#INT32)
			* [m_nBitmapwidth](#m_nBitmapwidth)
			* [m_nBitmapheight](#m_nBitmapheight) 

## Main 

##### Function's:
	* copyToStructure.
		* Function do: 
			* copy data of Image to 'bReadBuffer' via ReadFile, then from buffer to 'BMPstructure'.
		* Function parameters: 
			* *pBMPstructure   
				* Pointer of 'BMPstructure' type.
			* bReadBuffer[] 
				* Buffer where the raw image data is stored.
		* Funtion return
			* void
##### Object's:
	* objCmdline
		* Object to class CCmdLine.
	* objBmp
		* Object to class CBMP
	* objFileToRead, objFileToWrite
		* Object to class CFile.
	* objErrorHandler
		* Object to class CError.
##### Buffer's:
	* bReadBuffer
		* copyToStrcture function
			 * Using 'objFileToRead' to read source and copying constant 'm_knSECTORSIZE' amount of bytes to it.
			 * Using the copied bytes for to copy it to the 'BMPstructure'.
		* pixelarray (Case-4)
			* Copying bytes to the 'bReadBuffer' and printing it to output.
		* original image copy (Case-5)
			* Reading from the source and copying to destination while keeping the bytes in 'bReadBuffer'.
	* bMonoReadBuffer
		* Bitmap file header
			* Making the header and storing it in 'bMonoReadBuffer'.
		* DIB header
			* Making the header and storing it in 'bMonoReadBuffer'.
		* Use of buffer
			* Both header bitmap and dib one after other is copied to the buffer.
			* Using 'objFileToWrite' buffer is copied to destination file.
	* bTupleColoured
		* Contains one row of pixel (i.e) BGR value.
		* Using 'objFileToRead' copying 'nLineLengthColoured' to bTupleColoured.
		* To find out 'rAverage' which is compared to 'fThreshold' using 'nIteratorbTupleColoured'.
	* bTupleBinary
		* After comparison with 'fThreshold', equivalent 1||0 is inserted in it.
		* Once it is fully filled the decimal equivalent is created and copied to 'bWriteBW'.
	* bWriteBW
		* For each pixel rows of coloured equivalent black and white pixel rows is created.
		* Place where it get stored is bWriteBW.
##### Variable's
	* DWORD
		* dwErrCode
			* Used for storing last error code in main.
			* Is global variable.
		* bsizeofBMP
			* Used to store size of source BMP.
			* Is a global variable.
		* dwptr
			* Used to check for failure in the SetFailureAPI.
			* Condition checked is 'INVALID_SET_FILE_POINTER'.
			* Used in displaying the output in pixel array case i.e case 4.
		* dwBitmapHeight
			* Used to store bitmap height of the original image.
			* Is local to case 6 i.e black and white image creation.
	* float_t
		* rAverage
			* Used to store the average computed for the BGR values.
			* This value will be compared to 'fThreshold'.
	* int
		* nChoice
			* Used to switch between diffrent options
		* nSectors
			* Used to calculate the image size into how many sectors of constant size.
		* nAdditional
			* After calculating the 'nsectors' if there are remaining bytes then, this give the count.
		* userChoice
			* Asks [Y/N] to view full pixel array.
		* nBitmapImageWidth
			* Used to get image width which is the source image.
			* Helps in copying memory into the 'bMonoReadBuffer'.
		* nSizeRawBitmap
			* ((⌊(ColorDepth.ImageWidth + 31)/32⌋)*4)* |ImageHeight| 
			* Formula as per wikipedia 
			* [Link](https://en.wikipedia.org/wiki/BMP_file_format)
		*  nSizeBMP
			* Size of whole image including both the header including color table.
		* nLineLengthColoured
			* Each image is having pixel array in the form of width*height.
			* Each row is having set of pixels which is having 'BGR' vlaues.
			* This is in multiple of 4.
			* If each row is is not in the multiple of 4 then extra padding bytes is added.
			* Along with the padding bytes and colored bytes this tells what is the total size of one row.
		* nPaddingColoured
			* Each pixel i.e BGR value whole total should be multiple of 4.
			* If not nPaddingColoured comes into play.
			* This stores the count of padding bytes for source image i.e coloured image.
		* nBitmapwidth
			* This is to check whether there is padding bytes in the image or not.
		* nByteBlackAndWhite
			* This contains the count of how many bytes/pixels (as 1 byte per pixel) in it.
			* This is for the destination file means black and white image.
		* nPaddingBlackAndWhite
			* This contains the count of image padding for black and white.
			* This is for the destination image.
		* nLineLengthBlackAndWhite
			* This is the summation of ' nByteBlackAndWhite' and 'nPaddingBlackAndWhite'.
			* Means 1 line i.e 1 row of pixels containing how many bytes.
		* nHeaderFlag
			* While creating the data for black and white it is used.
			* Header should be copied first in the destination file.
			* To copy the header only once this flag is used.
			* It gets decremented after one successful run.
		* nToReadSetFlag
			* Used along with 'objFileToRead'.
			* Reading should occur after the header.
			* only pixel array is read this is used once.
		* nIteratorbTupleColoured
			* This iterator is for buffer 'bTupleColoured'.
			* Keeps track where the function is been tracked.
			* Helpful when calculating 'rAverage' as we've BGR value.
			* That is why incremented after calculating 'rAverage' every time.
			* Helpful while calculating a byte from 3 bytes of coloured image.
		* nIteratorbTupleBinary
			* This is the iterator for buffer 'bTupleBinary'.
			* Helpful in filling the buffer 8 times with corressponding 0 and 1.
		* nIteratorbWriteBW
			* An iterator to buffer 'bWriteBW'.
			* This helps to keep track of the position till where we've filled.
			* This is the iterator to the final buffer to be copied after every iteration.
		* nbitConversionLoop
			* The loop is running for every height of bmp.
			* For first iteration of height it is running for the amount of 'nByteBlackAndWhite'.
			* For every iteration of 'nByteBlackAndWhite' it is running for nbitConversionLoop times i.e 8.
		* nDecimalValue
			* Value which is stored in buffer 'bTupleBinary' converted into decimal.
			* That decimal value is being stored inside it.
		* nValue
			* Equivalent decimal value from binary is stored inside it.
			* Later being added to 'nDecimalValue'.
		* nReadOffset
			* Inside 'copyToStructure' function.
			* Used to keep track of specific location of 'bReadBuffer' to be copied.

	* WORD
		* filetype
			* Used to copy magic characters of BMP to 'bMonoReadBuffer'.
			* While creating bitmap file header for black and white.
##### Constant's
	* nBUFFERSIZE
	* nBUFFERSIZEbMonoReadBuffer
	* nOffsetPixelArrayMono
	* nSizeBitmapInfoHeaderMono
	* nColorDepthMono
	* nColorTableWhiteMono
	* nColorTableBlackMono
	* nColorDepth24
	* nPixelColorValue
	* nMaxArgumentSupported
	* nMultiple4Check
	* nMono8bpp
	* fThreshold
	* nBitValueMonochromeOne
	* nBitValueMonochromeZero
	* nTotalValuePixel

## BMP

##### Parameters:
	
	* private
		* *m_pStructurepointer
			* Here the structure pointer is stored which is passed by main function.

##### Functions
	
	* Public
		* DWORD
			* fnreturnSizeBMP()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetSizeBMP()'
				* Function parameter
					* void
				* Function return
					* Returns size of bmp source image i.e DWORD.
			* fnreturnOffsetpixelarray()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetOffsetpixelarray()'
				* Function parameter
					* void
				* Function return
					* Returns the position where from the pixel array is starting i.e DWORD.
			* fnreturnSizebitmapinfoheader()
				* Function do
					* With 'm_pStructurepointer' accessing 'fnreturnSizebitmapinfoheader()'
				* Function parameter
					* void
				* Function return
					* The size of DIB header i.e DWORD.
			* fnreturnCompressionmethod()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetCompressionmethod()'.
				* Function parameter
					* void
				* Function return
					* Compression method which is used by the image i.e in DWORD.
			* fnreturnRawimagesize()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetRawimagesize()'
				* Function parameter
					* void
				* Function return
					* Raw image size i.e the size without the header i.e in DWORD.
			* fnreturnHorizontalresolution()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetHorizontalresolution()'.
				* Function parameter
					* void
				* Function return
					* The horizontal resolution of the source image i.e in DWORD.
			* fnreturnVerticalresolution()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetVerticalresolution()'.
				* Function parameter
					* void
				* Function return
					* THe vertical resolution of the image i.e in DWORD.
			* fnreturnColorpallete()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetColorpalette()'.
				* Function parameter
					* void
				* Function return
					*  the number of colors in the color palette, or 0 to default to 2n i.e in DWORD.
			* fnreturnImportantcolors()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetImportantcolors()'.
				* Function parameter
					* void
				* Function return
					* The number of important colors used, or 0 when every color is important; generally ignored i.e in DWORD.


		* INT32
			* fnreturnBitamapwidth()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetBitmapwidth()'.
				* Function parameter
					* void
				* Function return
					*  The bitmap width in pixels (signed integer) i.e in INT32.
			* fnreturnBitmapheight()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetBitmapheight()'.
				* Function parameter
					* void
				* Function return
					* The bitmap height in pixels (signed integer) i.e in INT32.
		* WORD
			* fnreturnFiletype()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetFiletype()'.
				* Function parameter
					* void
				* Function return
					* The header field used to identify the BMP and DIB file i.e in WORD.
			* fnreturnReserved1()
				* Function do
					*  With 'm_pStructurepointer' accessing 'fngetReserved1()'.
				* Function parameter
					* void
				* Function return
					*  Reserved; actual value depends on the application that creates the image i.e in WORD.
			* fnreturnReserved2()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetReserved2()'.
				* Function parameter
					* void
				* Function return
					*  Reserved; actual value depends on the application that creates the image i.e in WORD.
			* fnreturnColorplanes()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetColorplanes()'.
				* Function parameter
					* void
				* Function return
					*  the number of color planes (must be 1) i.e in WORD.
			* fnreturnColordepth()
				* Function do
					* With 'm_pStructurepointer' accessing 'fngetColordepth()'.
				* Function parameter
					* void
				* Function return
					* The number of bits per pixel, which is the color depth of the image i.e in WORD.
		* void
			* fnsetStructurepointer(BMPstructure*)
				* Function do
					* Set the private attribute *m_pStructurepointer.
				* Function parameter
					* Parameter is of type 'BMPstructure*' which is passed by main function.
				* Function return
					void
		* BOOL
			* fncheckFiletype()
				* Function do
					*  With 'm_pStructurepointer' accessing 'fngetFiletype()' and comparing with magic number of BMP.
				* Function parameter
					* void
				* Function return
					* BOOL
			
## CmdLine
	* private
		* Parameters
			* vector
				* Optionslist
					* This is of string type and holds the options being passed.
			* string
				* strCurrentOption
					* The current option which is being in use.
	* public
		* Functions
			* BOOL
				* Searchoptionslist(string)
					* Function do
					* Function parameter
					* Function return
				* Checkextension(TCHAR*,const char[])
					* Function do
					* Function parameter
					* Function return
			* void 
				* Addoptions(string)
					* Function do
					* Function parameter
					* Function return
				* SetCurrentOption(string)
					* Function do
					* Function parameter
					* Function return
			* string
				* GetCurrentOption()
					* Function do
					* Function parameter
					* Function return

## Error
	* private
		* Parameters
			* DWORD
				* m_dwErrCode
			* string
				* szErrorString
	* public
		* Functions
			* LPCTSTR
				* fngeterrordescription()
					* Function do
					* Function parameter
					* Function return
				* fngeterrordescription(DWORD)
					* Function do
					* Function parameter
					* Function return
			* void 
				* fnsetErrCode(DWORD)
					* Function do
					* Function parameter
					* Function return
			* DWORD
				* fngetErrCode(void)
					* Function do
					* Function parameter
					* Function return
			* string
				* getErrorString()
					* Function do
					* Function parameter
					* Function return

## BMPstructure
	* public
		* Parameters
			* WORD
				* m_wFiletype
				* m_wReserved1
				* m_wReserved2
				* m_wColorplanes
				* m_wColordepth
			* DWORD
				* m_dwSizeBMP
				* m_dwOffsetpixelarray
				* m_dwSizebitmapinfoheader
				* m_dwCompressionmethod
				* m_dwRawimagesize
				* m_dwHorizontalresolution
				* m_dwVerticalresolution
				* m_dwColorpallete
				* m_dwImportantcolors
			* INT32
				* m_nBitmapwidth
				* m_nBitmapheight

