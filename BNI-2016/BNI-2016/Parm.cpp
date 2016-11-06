#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
#include <wchar.h>
#include <cwchar>
#include <iostream>
namespace Parm {
	PARM getparm(int argc, _TCHAR* argv[],  Error::Errors& e) {
		bool fl = false, fl_out = false, fl_log = false;
		PARM p;
		p.lt = false;
		p.it = false;
		p.st = false;
		p.tr = false;
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)
				throw ERROR_THROW(104)
			else
				if (wcsstr(argv[i], PARM_IN)) {
					wcscpy_s(p.in, &argv[i][4]);
					fl = true;
				}
				else
					if (wcsstr(argv[i], PARM_OUT)) {
						wcscpy_s(p.out, &argv[i][5]);
						fl_out = true;
					}
					else
						if (wcsstr(argv[i], PARM_LOG)) {
							wcscpy_s(p.log, &argv[i][5]);
							fl_log = true;
						}
						else
							if (wcsstr(argv[i], PARM_LT))
							{
								p.lt = true;
							}
							else

								if (wcsstr(argv[i], PARM_IT))
								{
									p.it = true;
								}
								else

									if (wcsstr(argv[i], PARM_ST))
									{
										p.st = true;

									}
									else

										if (wcsstr(argv[i], PARM_TR))
										{
											p.tr = true;
										}
										else
										{
											Error::adderr(105, e);
										}
		}
		if (!fl)
			throw ERROR_THROW(100);
		if (!fl_out) {
			wcscpy_s(p.out, p.in);
			wcsncat_s(p.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (!fl_log) {
			wcscpy_s(p.log, p.in);
			wcsncat_s(p.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		return p;
	}
}