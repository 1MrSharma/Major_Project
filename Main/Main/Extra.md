if (obj_cmdline.fnCheckEndingCharofBMP(argv[2]) == FALSE)//1
	{
		return 0;
	}
	if (obj_cmdline.fnCheckOptionList(argv[3]) == FALSE)//2
	{
		 if (obj_cmdline.fnCheckEndingCharofBMP(argv[2]) == FALSE)//2
		 {
			return 0;
		 }
		 if (obj_cmdline.fnCheckOptionList(argv[1]) == FALSE)//3
		 {
			 return 0;
		 }
		
	}