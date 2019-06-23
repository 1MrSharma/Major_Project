DWORD dwRetVal = 0;
		UINT uRetVal = 0;
		TCHAR szTempFileName[MAX_PATH];
		TCHAR lpTempPathBuffer[MAX_PATH];
		dwRetVal = GetTempPath(MAX_PATH, lpTempPathBuffer);
		if (dwRetVal > (MAX_PATH + 1) || (dwRetVal == 0))
		{
			obj_file_to_read.fnClose();
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			return EXIT_FAILURE;
		}
		uRetVal = GetTempFileName(lpTempPathBuffer, TEXT("MAIN"), 0, szTempFileName);
		if (uRetVal == 0)
		{
			obj_file_to_read.fnClose();
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			return EXIT_FAILURE;
		}

		if (obj_file_to_write_tempFile.fnCreate((LPTSTR)szTempFileName, GENERIC_WRITE, CREATE_ALWAYS) == FALSE)//object to the temporary filename is obj_file_to_write_tempFile
		{
			obj_file_to_write_tempFile.fnClose();
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			return EXIT_FAILURE;
		}
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;

		do {

			if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				return EXIT_FAILURE;
			}
			if (obj_file_to_write_tempFile.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				return EXIT_FAILURE;
			}
			nSectors--;
		} while (nSectors);
		if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			return EXIT_FAILURE;
		}
		if (obj_file_to_write_tempFile.fnWrite(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			return EXIT_FAILURE;
		}

		DeleteFileA(szTempFileName);