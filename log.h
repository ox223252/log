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
/// \version 1.0
/// \warning NONE
/// \bug NONE
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
/// \fn void logQuiet ( const uint8_t quiet );
/// \param[ in ] quiet: flag used to set clean general print quiet falg
///     value: 0/1 - true/false
/// \breif enable/disable all next logPrintf(), logVerbose() and logDebug() 
///     functions until a new logSetQuiet() called to change settings
////////////////////////////////////////////////////////////////////////////////
void logSetQuiet ( const bool quiet );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logSetVerbose ( const uint8_t verbose );
/// \param[ in ] verbose: flag used to set verbose falg
///     value: 0/1 - true/false
/// \breif enable/disable all next logverbose()
////////////////////////////////////////////////////////////////////////////////
void logSetVerbose ( const bool quiet );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logColor ( const uint8_t color );
/// \param[ in ] color: flag used to set the use of color in debug commands
///     value: 0/1 - true/false
/// \breif enable/disable use of color in next logDebug function until a new
///     logSetColor called to change settings
////////////////////////////////////////////////////////////////////////////////
void logSetColor ( const bool color );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logSetDebug ( const uint8_t debug );
/// \param[ in ] debug: flag used to set the use of debug value: 0/1 - 
///     true/false
/// \breif enable/disable use of debug in next logDebug function until a new
///     logSetDebug called to change settings
////////////////////////////////////////////////////////////////////////////////
void logSetDebug ( const bool debug );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logPrintf ( char * str, ... );
/// \param[ in ] str: formated string see printf
/// \param[ in ] ...: see printf
/// \breif display file, function, line before str if debug set and display str 
///     if quiet not set
////////////////////////////////////////////////////////////////////////////////
void logPrintf ( const char * restrict str, ... );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logVerbose ( char * str, ... );
/// \param[ in ] str: formated string see printf
/// \param[ in ] ...: see printf
/// \breif display file, function, line before str if debug set and display str 
///     if quiet not set and verbose flag is set
////////////////////////////////////////////////////////////////////////////////
void logVerbose ( const char * restrict str, ... );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logDebug ( char * str, ... );
/// \param[ in ] str: formated string see printf
/// \param[ in ] ...: see printf
/// \breif display file, function, line and str if quiet not set and debug flag
///     is set
////////////////////////////////////////////////////////////////////////////////
void logDebug ( const char * restrict str, ... );

////////////////////////////////////////////////////////////////////////////////
/// \fn void logSetOutput ( const bool term, const bool file );
/// \param[ in ] term: flag to set or not output on terminal
/// \param[ in ] file: flag to set or not output on file
/// \breif select out put for logs
////////////////////////////////////////////////////////////////////////////////
void logSetOutput ( const bool term, const bool file );

////////////////////////////////////////////////////////////////////////////////
/// \fn int logSetFileName ( const char * const fileName );
/// \param[ in ] fileName: path of the output log file 
/// \breif the the output file name
/// \return it 0 ok else see ernno for more details
////////////////////////////////////////////////////////////////////////////////
int logSetFileName ( const char * const fileName );

#ifdef MODE_DEBUG
void logPrintfSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... );
#define logPrintf(...) logPrintfSr(__FILE__,__func__,__LINE__,__VA_ARGS__)

void logVerboseSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... );
#define logVerbose(...) logVerboseSr(__FILE__,__func__,__LINE__,__VA_ARGS__)

void logDebugSr ( const char * restrict file, const char * restrict func, 
	const int line, const char * restrict str, ... );
#define logDebug(...) logDebugSr(__FILE__,__func__,__LINE__,__VA_ARGS__)
#else
#define logDebug(str,...)
#endif

#endif
