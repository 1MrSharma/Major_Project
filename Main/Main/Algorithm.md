
### Algorithm to create 1-bit black and white image using 24-bit BMP coloured image

	* 'Step-1'
		* Start.
	* 'Step-2' 
		* Calculate values for 'Bitmap file header' and store values in 'bMonoReadBuffer'.
		* ![Step-2](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-2.png)
	* 'Step-3'
		* Calculate values for 'DIB header' and store values in 'bMonoReadBuffer'.
		* ![Step-3](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-3.png)
	* 'Step-4'
		* Calculate the 'nLineLengthColoured' for source i.e coloured.
		* ![Step-4](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-4.png)
	* 'Step-5'
		* Calculate the 'nLineLengthBlackAndWhite' for destination i.e black and white
		* ![Step-5](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-5.png)
	* 'Step-6'
		* Create handle for reading to the source via object 'objFileToRead'.
		* ![Step-6](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-6.png)
	* 'Step-7'
		* Create handle for writing to the destination via object 'objFileToWrite'.
		* ![Step-7](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-7.png)
	* 'Step-8'
		* 'Step-8.a'
			* While 'dwBitmapHeight' is true run a while loop.
		* 'Step-8.b' 
			* Copy the buffer created in 'Step-3' only once using a 'nHeaderFlag'.
			* ![Step-8.b](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.b.png)
		* 'Step-8.c'
			* Set pointer of read i.e 'objFileToRead' after headers  
			  to copy only pixel array to the 'bTupleColoured' buffer.
			* ![Step-8.c](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.c.png)
		* 'Step-8.d'
			* Read the data from source file and copy to 'bTupleColoured'.
			* ![Step-8.d](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.d.png)
		* 'Step-8.e'
			* While 'nByteBlackAndWhite' is true run a loop,which is the linelength
			calculated in 'Step-5'.
			* 'Step-8.e.1' 
				* With every 3 byte of coloured,have to make 1 byte of black and white
				so while 'nbitConversionLoop' is true run loop, with every iteration
				1 pixel i.e 3 colour values is being converted to either black or white
				and being saved in 'bTupleBinary'.
			* 'Step-8.e.1.2'
				* Calculate 'rAverage'((B+G+R)/255*3) for every BGR value and compare 
		  		  it with 'fthreshold' value to get equivalent b&w values and store
				  it in 'bTupleBinary'and with every iteration 'IteratorbTupleColoured'
				  is incremented by 3.
				* ![Step-8.e.1.2](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.e.1.2.png)
			* 'Step-8.e.1.3' 
				* When 'bTupleBinary' is full filled once i.e 'nIteratorbTupleColoured'
				  (which keeps track of values currently scanned) have scanned 3 bytes
				   and have equivalent bits value for blak and white.
				* 'Step-8.e.1.3.1'
					* Convert the bits in 'bTupleBinary' to 1 byte and store it in
					'bWriteBW'.
				* ![Step-8.e.1.3](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.e.1.3.png)
		* 'Step-8.f'
			* Decremnt 'nbitConversionLoop' in every iteration.
		* 'Step-8.g'
			* Decrement 'nByteBlackAndWhite' in every iteration.
		* 'Step-8.h'
			* Write the created 'bWriteBW' to destination file using 'objFileToWrite'.
			* ![Step-8.h](https://github.com/1MrSharma/Major_Project/blob/White_Belt/Step-8.h.png)
		* 'Step-8.i'
			* Decrement 'dwBitmapHeight'' in every iteration.
	* 'Step-9' Stop

