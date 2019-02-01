#pragma once
#include<Windows.h>
class CBMP
{
public:
	DWORD type_file;//00 (2 bytes)
	DWORD bitmap_width_pixel;//12 (4 bytes)
	DWORD bitmap_height_pixel;//16 (4 bytes)
	DWORD number_color_planes;//1A (2 bytes)
	DWORD bits_per_pixel;//1C (2 bytes)
	LPCTSTR compression_method;//1E (4 bytes)
	DWORD horizontal_resolution;//26 (4 bytes)
	DWORD vertical_resolution;//starting 2A (4 bytes)
	DWORD color_palette;//starting 2E (4 bytes)
};

