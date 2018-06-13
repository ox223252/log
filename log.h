#ifndef __LOG_H__
#define __LOG_H__

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
/// \file log.h
/// \brief library to manage log
/// \author ox223252
/// \date 2017-07
/// \copyright GPLv2
/// \version 0.1
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
/// \fn void logQuiet ( const uint8_t quiet );
/// \param[ in ] quiet: flag used to set clean general debug quiet falg
///     value: 0/1 - true/false
/// \breif enable/disable all next logverbose() function until a new 
///     logSetQuiet() called to change settings
/// \return 0: OK
////////////////////////////////////////////////////////////////////////////////
void logSetQuiet ( const bool quiet );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logColor ( const uint8_t color );
/// \param[ in ] color: flag used to set the use of color in debug commands
///     value: 0/1 - true/false
/// \breif enable/disable use of color in next logDebug function until a new
///     logSetColor called to change settings
/// \return 0: OK
////////////////////////////////////////////////////////////////////////////////
void logSetColor ( const bool color );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logSetDebug ( const uint8_t debug );
/// \param[ in ] debug: flag used to set the use of debug value: 0/1 - 
///     true/false
/// \breif enable/disable use of debug in next logDebug function until a new
///     logSetDebug called to change settings
/// \return 0: OK
////////////////////////////////////////////////////////////////////////////////
void logSetDebug ( const bool debug );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logVerbose ( char * str, ... );
/// \param[ in ] str: formated string see printf
/// \param[ in ] ...: see printf
/// \breif display file, function, line before str if debug set and display str 
///     if quiet not set
////////////////////////////////////////////////////////////////////////////////
#ifdef MODE_DEBUG
void logVerboseSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... );

#define logVerbose(...) logVerboseSr(__FILE__,__func__,__LINE__,__VA_ARGS__)
#else
void logVerbose ( const char * restrict str, ... );
#endif

#ifdef MODE_DEBUG
void logDebugSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... );
	
////////////////////////////////////////////////////////////////////////////////
/// \fn void logDebug ( char * str, ... );
/// \param[ in ] str: formated string see printf
/// \param[ in ] ...: see printf
/// \breif display file, function, line and str if quiet not set
////////////////////////////////////////////////////////////////////////////////
#define logDebug(...) logDebugSr(__FILE__,__func__,__LINE__,__VA_ARGS__)
#else
#define logDebug(str,...)
#endif
#endif
