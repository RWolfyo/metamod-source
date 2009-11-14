/**
 * vim: set ts=4 :
 * ======================================================
 * Metamod:Source
 * Copyright (C) 2004-2008 AlliedModders LLC and authors.
 * All rights reserved.
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from 
 * the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute it 
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not 
 * claim that you wrote the original software. If you use this software in a 
 * product, an acknowledgment in the product documentation would be 
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_OSLINK_H
#define _INCLUDE_OSLINK_H

/**
 * @brief Defines OS-independent information
 * @file oslink.h
 */

#if defined __WIN32__ || defined _WIN32 || defined WIN32
	#define WIN32_LEAN_AND_MEAN
	#define OS_WIN32
	#if defined _MSC_VER && _MSC_VER >= 1400
		#undef ARRAYSIZE
	#else
		#define mkdir(a) _mkdir(a)
	#endif
	#include <windows.h>
	#include <io.h>
	#include <direct.h>
	#define		dlmount(x)		LoadLibrary(x)
	#define		dlsym(x, s)		GetProcAddress(x, s)
	#define		dlclose(x)		FreeLibrary(x)
	const char*	dlerror();
	#define		abspath(x, s)	_fullpath(x, s, sizeof(x))
	#define	PATH_SEP_STR		"\\"
	#define PATH_SEP_CHAR		'\\'
	#define ALT_SEP_CHAR		'/'
	#define PATH_SIZE			MAX_PATH
	#define SERVER_DLL			"server.dll"
	#define strcasecmp			stricmp
	inline bool _IsPathSepChar(char c) { return (c == '/' || c == '\\'); }
#elif defined __linux__
	#define OS_LINUX
	#include <dlfcn.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <dirent.h>
	typedef		void*			HINSTANCE;
	#define		dlmount(x)		dlopen(x,RTLD_NOW)
	#define		abspath(x, s)	realpath(s, x)
	#define	PATH_SEP_STR		"/"
	#define PATH_SEP_CHAR		'/'
	#define ALT_SEP_CHAR		'\\'
	#define PATH_SIZE			PATH_MAX
	#define	stricmp				strcasecmp
	#define strnicmp			strncasecmp
	#define SERVER_DLL			"server_i486.so"
	inline bool _IsPathSepChar(char c) { return (c == '/'); }
#endif

#if defined __linux__
	#include <errno.h>
	int GetLastError();
#endif

bool GetFileOfAddress(void *pAddr, char *buffer, size_t maxlength);

#if defined __WIN32__ || defined _WIN32 || defined WIN32
	#define SMM_API extern "C" __declspec(dllexport)
#elif defined __GNUC__
	#if (__GNUC__ == 4)
		#define SMM_API extern "C" __attribute__ ((visibility("default")))	
	#else
		#define SMM_API	extern "C" 
	#endif	
#endif

#if defined __WIN32__ || defined _WIN32 || defined WIN32
	typedef __int64				int64_t;
	typedef unsigned __int64	uint64_t;
#elif defined __GNUC__
#include <stdint.h>
#if !__GLIBC_HAVE_LONG_LONG
	typedef long long			int64_t;
	typedef unsigned long long	uint64_t;
#endif
#endif

#ifndef __linux__
	#define snprintf	_snprintf
	#if defined _MSC_VER && _MSC_VER < 1500
		#define vsnprintf	_vsnprintf
	#endif
#endif

#endif //_INCLUDE_OSLINK_H
