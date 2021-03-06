////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2017
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU General Public License published by the Free
///     Software Foundation, either version 2 of the License, or (at your
///     option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU General Public License for more
///     details.
///
/// You should have received a copy of the GNU General Public License along with
///     this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \file log.c
/// \brief library used to manage logs
/// \author ox223252
/// \date 2017-07
/// \copyright GPLv2
/// \version 0.1
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "log.h"

#define NONE "\e[0m"
#define BY "\e[1;33m"
#define BB "\e[1;34m"
#define BG "\e[1;32m"
#define BR "\e[1;31m"
#define MAX_FILE_NAME_LENGTH 512

#if defined ( _WIN64 ) || defined ( _WIN32 )
#include <conio.h>
#include <windows.h>
#endif

///< logs not quiet
///< debugs without colors
///< logs without debugs
///< logs displayed in terminal
///< logs printed in files
static struct
{
	uint8_t quiet:1,
		verbose:1,
		color:1,
		debug:1,
		term:1,
		file:1;
}
_log_flag = { 0, 0, 0, 0, 1, 0 };

static char _log_fileName[ MAX_FILE_NAME_LENGTH ] = { 0 };

static inline void vprintInTerm ( const char * const restrict str, va_list argptr )
{
	if ( _log_flag.term )
	{
		vprintf ( str, argptr );
	}
}

static inline void printInTerm ( const char * const restrict str, ... )
{
	va_list argptr;

	if ( !_log_flag.term )
	{
		return;
	}

	va_start ( argptr, str );
	vprintf ( str, argptr );
	va_end ( argptr );
}

static inline void vprintInFile ( const char * const restrict str, va_list argptr )
{
	FILE * f = NULL;

	if ( ( !_log_flag.file ) ||
		!strlen ( _log_fileName ) )
	{
		return;
	}

	f = fopen ( _log_fileName, "a" );
	if ( !f )
	{
		return;
	}

	vfprintf ( f, str, argptr );

	fclose ( f );
}

static inline void printInFile ( const char * const restrict str, ... )
{
	va_list argptr;
	FILE * f = NULL;

	if ( ( !_log_flag.file ) ||
		!strlen ( _log_fileName ) )
	{
		return;
	}

	f = fopen ( _log_fileName, "a" );
	if ( !f )
	{
		return;
	}

	va_start ( argptr, str );
	vfprintf ( f, str, argptr );
	va_end ( argptr );

	fclose ( f );
}

void logSetQuiet ( const bool quiet )
{
	_log_flag.quiet = quiet & 0x01;
}

void logSetVerbose ( const bool verbose )
{
	_log_flag.verbose = verbose & 0x01;
}

void logSetColor ( const bool color )
{
	_log_flag.color = color & 0x01;
}

void logSetDebug ( const bool debug )
{
	_log_flag.debug = debug & 0x01;
}

void logSetOutput ( const bool term, const bool file )
{
	_log_flag.term = term & 0x01;
	_log_flag.file = file & 0x01;
}

int logSetFileName ( const char * const fileName )
{
	FILE * f = NULL;

	if ( strlen ( fileName  ) > ( MAX_FILE_NAME_LENGTH - 1 ) )
	{
		errno = E2BIG;
		return ( __LINE__ );
	}

	strcpy ( _log_fileName, fileName );

	f = fopen ( _log_fileName, "a" );
	if ( !f )
	{
		return ( __LINE__ );
	}
	fclose ( f );

	return ( 0 );
}

// permit to display func name line number and file name if debug option was activated
#ifdef MODE_DEBUG
void logPrintfSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... )
{
	va_list ptr1, ptr2;

	#if defined ( _WIN64 ) || defined ( _WIN32 )
		long unsigned int WcmdStatus;
	#endif

	if ( _log_flag.quiet )
	{
		return;
	}

	if ( _log_flag.debug )
	{
		#if defined ( _WIN64 ) || defined ( _WIN32 )
			GetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), &WcmdStatus );
			SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus | 0x0004 );
		#endif
		
		printInTerm ( ( _log_flag.color ) ? BR"%s "BG"%s "BB"%d\e"NONE" : " : "%s %s %d : ", file, func, line );
		printInFile ( "%s %s %d : ", file, func, line );

		#if defined ( _WIN64 ) || defined ( _WIN32 )
			SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus );
		#endif
	}

	va_start ( ptr1, str );
	va_copy ( ptr2, ptr1 );
	vprintInTerm ( str, ptr1 );
	vprintInFile ( str, ptr2 );
	va_end ( ptr2 );
	va_end ( ptr1 );
}

void logVerboseSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... )
{
	va_list ptr1, ptr2;

	#if defined ( _WIN64 ) || defined ( _WIN32 )
		long unsigned int WcmdStatus;
	#endif

	if ( ( !_log_flag.verbose &&
		!_log_flag.debug ) ||
		_log_flag.quiet )
	{
		return;
	}

	if ( _log_flag.debug )
	{
		#if defined ( _WIN64 ) || defined ( _WIN32 )
			GetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), &WcmdStatus );
			SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus | 0x0004 );
		#endif
		
		printInTerm ( ( _log_flag.color ) ? BR"%s "BG"%s "BB"%d\e"NONE" : " : "%s %s %d : ", file, func, line );
		printInFile ( "%s %s %d : ", file, func, line );

		#if defined ( _WIN64 ) || defined ( _WIN32 )
			SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus );
		#endif
	}

	va_start ( ptr1, str );
	va_copy ( ptr2, ptr1 );
	vprintInTerm ( str, ptr1 );
	vprintInFile ( str, ptr2 );
	va_end ( ptr2 );
	va_end ( ptr1 );
}

void logDebugSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... )
{
	va_list ptr1, ptr2;

	#if defined ( _WIN64 ) || defined ( _WIN32 )
		long unsigned int WcmdStatus;
	#endif

	if ( !_log_flag.debug ||
		_log_flag.quiet )
	{
		return;
	}

	#if defined ( _WIN64 ) || defined ( _WIN32 )
		GetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), &WcmdStatus );
		SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus | 0x0004 );
	#endif
	
	printInTerm ( ( _log_flag.color ) ? BR"%s "BG"%s "BB"%d\e"NONE" : " : "%s %s %d : ", file, func, line );
	printInFile (  "%s %s %d : ", file, func, line );


	#if defined ( _WIN64 ) || defined ( _WIN32 )
		SetConsoleMode ( GetStdHandle ( STD_OUTPUT_HANDLE ), WcmdStatus );
	#endif

	va_start ( ptr1, str );
	va_copy ( ptr2, ptr1 );
	vprintInTerm ( str, ptr1 );
	vprintInFile ( str, ptr2 );
	va_end ( ptr2 );
	va_end ( ptr1 );
}
#else
void logPrintf ( const char * restrict str, ... )
{
	va_list ptr1, ptr2;

	if ( _log_flag.quiet )
	{
		return;
	}

	va_start ( ptr1, str );
	va_copy ( ptr2, ptr1 );
	vprintInTerm ( str, ptr1 );
	vprintInFile ( str, ptr2 );
	va_end ( ptr2 );
	va_end ( ptr1 );
}

void logVerbose ( const char * restrict str, ... )
{
	va_list ptr1, ptr2;

	if ( !_log_flag.verbose ||
		_log_flag.quiet )
	{
		return;
	}

	va_start ( ptr1, str );
	va_copy ( ptr2, ptr1 );
	vprintInTerm ( str, ptr1 );
	vprintInFile ( str, ptr2 );
	va_end ( ptr2 );
	va_end ( ptr1 );
}
#endif

