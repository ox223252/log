
# log
small package to manage logs

## functions:

If the code is compiled without MODE_DEBUG defined, only *logSetQuiet()* and *logVerbose()* have effect. If the code is compiled with MODE_DEBUG defined all function will be available :
### Config:
#### logSetQuiet:
```C
void logSetQuiet ( const bool quiet );
```
This function diseable / or enable log outputs:
 - false to enable,
 - true to disable

#### logSetColor:
```C
void logSetColor ( const bool color );
```
This function allow usage of color for outputs:
 - false to disable colors
 - true to enable colors

#### logSetDebug:
```C
void logSetDebug ( const bool debug );
```
This function enable *logDebug()* output, and add file name, function name and line number display for *logVerbose()*:
 - false to disable *logDebug()* and only print the *logVerbose()* args (*logVerbose()* == *printf()*)
 - true to enable *logDebug()* outs and add file name, function name and line number display for *logVerbose()* in addition of printing args (*logVerbose()* == *logDebug()*)

### Display:
#### logPrintf:
```C
void logPrintf ( const char * restrict str, ... );
```
This function will display args to *stdout*, use it like *printf()*, the display is conditionned by *logSetQuiet(), logSetColor() and logSetDebug()*.
```C
	logSetDebug ( true );
	logSetColor ( true );
	logPrintf ( "test1\n" );

	logSetColor ( false );
	logSetDebug ( false );
	logPrintf ( "test2\n" );
```
```Shell
# gcc main.c log.c -D'MODE_DEBUG' && ./a.out
main.c main 7 : test1
test2
# gcc main.c log.c && ./a.out
test1
test2
```

#### logVerbose:
```C
void logVerbose ( const char * restrict str, ... );
```
This function will display args to *stdout*, use it like *printf()*, the display is conditionned by *logSetQuiet(), logSetVerbose(), logSetColor() and logSetDebug()*.
```C
	logSetDebug ( true );
	logSetColor ( true );
	logVerbose ( "test1\n" );

	logSetColor ( false );
	logSetDebug ( false );
	logVerbose ( "test2\n" );

	logSetVerbose ( true );
	logVerbose ( "test3\n" );
```
```Shell
# gcc main.c log.c -D'MODE_DEBUG' && ./a.out
main.c main 7 : test1
test3
```

#### logDebug:
```C
void logDebug( const char * restrict str, ... );
```
This function will display file name, function name and line number followed by args to *stdout*, use it like *printf()*, the display is conditionned by *logSetQuiet(), logSetColor() and logSetDebug()*.


## Example: 
```C
#include "log.h"

int main ( void )
{
	printf ( "\n\ndisplay only 'printf'\n\n" );
	logDebug ( "debug\n" );
	logVerbose ( "verbose\n" );
	logPrintf ( "printf\n" );

	logSetVerbose ( true );
	printf ( "\n\ndisplay printf & verbose\n\n" );
	logDebug ( "debug\n" );
	logVerbose ( "verbose\n" );
	logPrintf ( "printf\n" );

	logSetDebug ( true );
	printf ( "\n\ndisplay all\n\n" );
	logDebug ( "debug\n" );
	logVerbose ( "verbose\n" );
	logPrintf ( "printf\n" );

	logSetColor ( true );
	printf ( "\n\ndisplay all with colors\n\n" );
	logDebug ( "debug\n" );
	logVerbose ( "verbose\n" );
	logPrintf ( "printf\n" );

	logSetQuiet ( true );
	printf ( "\n\nnot display logs\n\n" );
	logDebug ( "debug no displayed\n" );
	logVerbose ( "verbose no displayed\n" );
	logPrintf ( "printf no displayed\n" );

	logSetQuiet ( false );

	printf ( "\n\ndisplay all\n\n" );
	logDebug ( "debug\n" );
	logVerbose ( "verbose\n" );
	logPrintf ( "printf\n" );
	return (0);
}

```

```Shel
# gcc main.c log.c -D'MODE_DEBUG' && ./a.out
display only 'printf'

printf


display printf & verbose

verbose
printf


display all

main.c main 18 : debug
main.c main 19 : verbose
main.c main 20 : printf


display all with colors

main.c main 24 : debug
main.c main 25 : verbose
main.c main 26 : printf


not display logs



display all

main.c main 37 : debug
main.c main 38 : verbose
main.c main 39 : printf
```
> the colors aren't displayed ^^
