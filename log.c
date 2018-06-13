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

#include "log.h"

#define NONE "\e[0m"
#define BY "\e[1;33m"
#define BB "\e[1;34m"
#define BG "\e[1;32m"
#define BR "\e[1;31m"

static struct
{
	uint8_t quiet:1,
		color:1,
		debug:1;
}
flag;

void logSetQuiet ( const bool quiet )
{
	flag.quiet = quiet & 0x01;
}

void logSetColor ( const bool color )
{
	flag.color = color & 0x01;
}

void logSetDebug ( const bool debug )
{
	flag.debug = debug & 0x01;
}

// permit to display func name line number and file name if debug option was activated
#ifdef MODE_DEBUG
void logVerboseSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... )
{
	va_list argptr;

	if ( flag.quiet )
	{
		return;
	}

	if ( flag.debug )
	{
		if ( flag.color )
		{
			printf ( BY"%s"BG" %s"BB" %d"NONE" : ", file, func, line );
		}
		else
		{
			printf ( "%s %s %d : ", file, func, line );
		}
	}

	va_start ( argptr, str );
	vfprintf ( stdout, str, argptr );
	va_end ( argptr );
}

void logDebugSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... )
{
	va_list argptr;

	if ( !flag.quiet &&
		flag.debug )
	{
		if ( flag.color )
		{
			printf ( BR"%s "BG"%s "BB"%d\e"NONE" : ", file, func, line );
		}
		else
		{
			printf ( "%s %s %d : ", file, func, line );
		}
		va_start ( argptr, str );
		vfprintf ( stdout, str, argptr );
		va_end ( argptr );
	}
}
#else
void logVerbose ( const char * restrict str, ... )
{
	va_list argptr;

	if ( flag.quiet )
	{
		return;
	}

	va_start ( argptr, str );
	vfprintf ( stdout, str, argptr );
	va_end ( argptr );
}
#endif
