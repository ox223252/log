
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
#### logVerbose:
```C
void logVerbose ( const char * restrict str, ... );
```
This function will display args to *stdout*, use it like *printf()*, the display is conditionned by *logSetQuiet(), logSetColor() and logSetDebug()*.
```C
	logSetDebug ( true );
	logSetColor ( true );
	logVerbose ( "test1\n" );

	logSetColor ( false );
	logSetDebug ( false );
	logVerbose ( "test2\n" );
```
```Shell
main.c main 17 : test1
test2
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
	printf ( "--> %d\n", __LINE__ );

	logSetDebug ( true );
	logSetColor ( true );

	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "test\n" );
	logDebug ( "test\n" );

	logSetColor ( false );

	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "a\n" );
	logDebug ( "a\n" );

	logSetDebug ( false );
	
	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "b\n" );
	logDebug ( "b\n" );

	logSetQuiet ( true );
	
	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "c\n" );
	logDebug ( "c\n" );

	logSetDebug ( true );
	
	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "d\n" );
	logDebug ( "d\n" );
	
	logSetQuiet ( false );

	printf ( "--> %d\n", __LINE__ );
	logVerbose ( "e\n" );
	logDebug ( "e\n" );
	return (0);
}
```
```Shel
--> 5
--> 10
main.c main 11 : test
main.c main 12 : test
--> 16
main.c main 17 : a
main.c main 18 : a
--> 22
b
--> 28
--> 34
--> 40
main.c main 41 : e
main.c main 42 : e
```
> the color isn't displayed ^^
