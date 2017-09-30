/**
 * @file debug.c
 * @brief Debugging Tools
 * $Id: $
 **/

//Dependencies
#ifdef CUSTOM_HEADER_FILE
#include CUSTOM_HEADER_FILE
#endif // CUSTOM_HEADER_FILE

#include "types.h"
#include "debug.h"


#ifndef DEBUG_WRITE_BYTE
#warning "DEBUG_WRITE_BYTE" is not defined
#define DEBUG_WRITE_BYTE(x)     putchar(x)
#endif // DEBUG_WRITE_BYTE

#ifndef DEBUG_INITIALIZATION
#warning "DEBUG_INITIALIZATION" is not defined
#define DEBUG_INITIALIZATION()
#endif // DEBUG_INITIALIZATION



/**
 * @brief Write character to stream
 * @param[in] c The character to be written
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @return On success, the character written is returned. If a writing
 *   error occurs, EOF is returned
 **/
int_t fputc(int_t c, FILE *stream)
{
	//Standard output or error output?
	if (stream == stdout || stream == stderr)
	{
		DEBUG_WRITE_BYTE(c);

		//On success, the character written is returned
		return c;
	}
	//Unknown output?
	else
	{
		//If a writing error occurs, EOF is returned
		return EOF;
	}
}

/**
 * @brief Debug initialization
 **/
void DEBUG_Init(void)
{
	DEBUG_INITIALIZATION();
}

/**
 * @brief Display the contents of an array (32 Bytes per line)
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @param[in] prepend String to prepend to the left of each line
 * @param[in] data Pointer to the data array
 * @param[in] length Number of bytes to display
 **/
void DEBUG_DisplayArray(FILE *stream, const char_t *prepend, const void *data,
		size_t length)
{
	int_t i;

	for (i = 0; i < length; i++)
	{

		//Beginning of a new line?
		if ((i % 32) == 0)
			fprintf(stream, "%s x%08X ", prepend, i);

		//Display current data byte
		fprintf(stream, "%02" PRIX8 " ", *((uint8_t *) data + i));

		//End of current line?
		if ((i % 32) == 31 || i == (length - 1))
			fprintf(stream, "\r\n");
	}
}

/**
 * @brief
 */
void DEBUG_mpiDump(FILE *stream, const char_t *prepend, const void *data)
{

}



