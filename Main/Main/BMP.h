#pragma once
#include<Windows.h>
class CBMP
{
public:
	DWORD m_dwtype_file;//00 (2 bytes)
	DWORD m_dwbitmap_width_pixel;//12 (4 bytes)
	DWORD m_dwbitmap_height_pixel;//16 (4 bytes)
	DWORD m_dwnumber_color_planes;//1A (2 bytes)
	DWORD m_dwbits_per_pixel;//1C (2 bytes)
	LPCTSTR m_szcompression_method;//1E (4 bytes)
	DWORD m_dwhorizontal_resolution;//26 (4 bytes)
	DWORD m_dwvertical_resolution;//starting 2A (4 bytes)
	DWORD m_dwcolor_palette;//starting 2E (4 bytes)
};

