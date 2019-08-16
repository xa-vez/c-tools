/**
 * @file filegen.c
 * @brief this module generate a .c and a .h skeleton
 * $Id: $
 **/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

char source[] = {
"/**\n \
* @file %s\n \
* @brief This is the source file.\n \
* $Id: $\n \
**/\n\
\n" };

char header[] = {
"/**\n \
* @file %s\n \
* @brief This is the header file.\n \
* $Id: $\n \
**/\n\
\n" };

char ifndef[] = {
"#ifndef __%s_H__\n\
#define __%s_H__\n\
\n" };

char dependencies[] = {
"//****************************** DEPENDENCIES ********************************//\n\
//============================================================================//\n\
\n"
};
char includes[] = { "#include \"%s.h\" \r\n" };

char defines[] = {
"//******************************** DEFINES ***********************************//\n\
//============================================================================//\n\
\n"
};

char typedefs[] = {
"//******************************** TYPEDEFS **********************************//\n\
//============================================================================//\n\
\n"
};

char enums[] = {
"//********************************* ENUMS ************************************//\n\
//============================================================================//\n\
\n"
};

char pub_const[] = {
"//**************************** PUBLIC CONSTANTS ******************************//\n\
//============================================================================//\n\
\n"
};

char pri_const[] = {
"//*************************** PRIVATE CONSTANTS ******************************//\n\
//============================================================================//\n\
\n"
};

char pri_vars[] = {
"//*************************** PRIVATE VARIABLES ******************************//\n\
//============================================================================//\n\
\n"
};
char pub_vars[] = {
"//***************************  PUBLIC VARIABLES ******************************//\n\
//============================================================================//\n\
\n"
};

char pri_fun[] = {
"//**************************  PRIVATE FUNCTIONS ******************************//\n\
//============================================================================//\n\
\n"
};

char pub_fun[] = {
"//***************************  PUBLIC FUNCTIONS ******************************//\n\
//============================================================================//\n\
\n"
};

char endif[] = { "#endif // __%s_H__\n" };

/**
 * @brief
 * @param[in]
 * @return
 */
char * convert_to_upper(char * n)
{
	static char name[32];
	int i;
	int j;

	i = strlen(n);

	for (j = 0; j < i; j++)
		name[j] = toupper(n[j]);

	name[j] = 0;

	return name;
}

/**
 * @brief main entry point
 * @param[in] argc
 * @param[in] argv
 * @return error status
 */
int main(int argc, char ** argv)
{
	char file_name[32];
	char * name;
	char * ptr;
	FILE * pf;

	do
	{
		if (argv[1] == NULL)
		{
			printf("error creating files...\n");
			break;
		}

		name = argv[1];

		printf("Generating files... %s .c .h \n", argv[1]);

		sprintf(file_name, "%s.h", name);
		pf = fopen(file_name, "w");
		ptr = convert_to_upper(name);

		fprintf(pf, header, file_name);
		fprintf(pf, ifndef, ptr, ptr);
		fprintf(pf, "%s", dependencies);
		fprintf(pf, "%s", defines);
		fprintf(pf, "%s", typedefs);
		fprintf(pf, "%s", enums);
		fprintf(pf, "%s", pub_const);
		fprintf(pf, "%s", pub_vars);
		fprintf(pf, "%s", pub_fun);
		fprintf(pf, endif, ptr);

		fclose(pf);

		sprintf(file_name, "%s.c", name);
		pf = fopen(file_name, "w");
		ptr = convert_to_upper(name);

		fprintf(pf, source, file_name);
		fprintf(pf, "%s", dependencies);
		fprintf(pf, includes, name);
		fprintf(pf, "%s", defines);
		fprintf(pf, "%s", typedefs);
		fprintf(pf, "%s", enums);
		fprintf(pf, "%s", pri_const);
		fprintf(pf, "%s", pub_const);
		fprintf(pf, "%s", pri_vars);
		fprintf(pf, "%s", pub_vars);
		fprintf(pf, "%s", pri_fun);
		fprintf(pf, "%s", pub_fun);

		fclose(pf);

		printf("success...\n");

	} while (0);

	return 1;
}

