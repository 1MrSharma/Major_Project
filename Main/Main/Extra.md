		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;

		