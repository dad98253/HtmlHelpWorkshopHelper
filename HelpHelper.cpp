/*
 * HelpHelper.cpp
 *
 *  Created on: Dec 8, 2020
 *      Author: dad
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOZE
#define ssize_t int
ssize_t getline(char** lineptr, size_t* n, FILE* stream)
{
    if (fgets(*lineptr, (int)n, stream) == NULL) return(-1);
    return strlen(*lineptr);
}
#endif

void trimleadingandTrailing(char* s);
int replacestr(char* str, char* substr, char* replace, char* output);

int main(int argc, char* argv[])
{
	FILE* fp;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;
	char* line = NULL;
	char* line2 = NULL;
	char* output = NULL;
	char* htmfile;
	char* title;
	char* substr;
	size_t len = 250;
	ssize_t read;
	ssize_t read2;
	size_t size = 255;
	int level = 0;
	int currentlevel = -1;
	int i;
	char tabs[] = "\t\t\t\t\t\t\t\t\t\t\t\t\0";

	if (argc > 1) {
		fp = fopen(argv[1], "r");
	}
	else {
		fp = fopen("outline.txt", "r");
	}
	if (fp == NULL)return(1);

	if (argc > 2) {
		fp2 = fopen(argv[2], "r");
	}
	else {
		fp2 = fopen("template.txt", "r");
	}
	if (fp2 == NULL)return(2);
	if (argc > 3) {
		fp4 = fopen(argv[3], "w");
	}
	else {
		fp4 = fopen("toc.txt", "w");
	}
	if (fp4 == NULL)return(3);
	if (argc > 4) {
		fp5 = fopen(argv[4], "w");
	}
	else {
		fp5 = fopen("hhp.txt", "w");
	}
	if (fp5 == NULL)return(4);
	if (argc > 5) return(5);

	line = (char*)malloc(size);
	line2 = (char*)malloc(size);
	output = (char*)malloc(size);

    printf("running HelpHelper\n");

	while ((read = getline(&line, &len, fp)) != -1) {
		//	        printf("Retrieved line of length %zu:\n", read);
		line[read - 1] = '\000';
		title = line;
		for (i = 0, level = 0; i < (int)read; i++) {
			if (line[i] == '\t') {
				level++;
				title++;
			}
		}
		if (level > 10) {
			fprintf(stderr,"too many levels\n");
			return(6);
		}
		printf(" line found : \"%s\", level is %i\n", line, level);
		// find the ;
		htmfile = strchr(line, ';');
		if (htmfile == NULL)
		{
			printf("could not find a ; in this line!\n");
			return(7);
		}
		*htmfile = '\000';
		htmfile++;
		printf(" Title = \"%s\", file name = \"%s\"\n", title, htmfile);
		rewind(fp2);
		trimleadingandTrailing(htmfile);
		fp3 = fopen(htmfile, "w");
		if (fp3 == NULL) {
			return(8);
		}
		while ((read2 = getline(&line2, &len, fp2)) != -1) {
				replacestr(line2, (char*)"xtitlex", title, output);
				fprintf(fp3, "%s", output);
		}
		fclose(fp3);
		if (level > currentlevel) {
			fprintf(fp4, "%.*s<UL>\n", currentlevel+1, tabs);
		}
		while (level < currentlevel) {
			fprintf(fp4, "%.*s</UL>\n", currentlevel, tabs);
			currentlevel--;
		}

/*		<LI> <OBJECT type = "text/sitemap">
			<param name = "Name" value = "My Secret Box Help">
			<param name = "Local" value = "AboutSBHtopics.htm">
			< / OBJECT>	
*/
		fprintf(fp4, "%.*s<LI> <OBJECT type=\"text/sitemap\">\n", level + 1, tabs);
		fprintf(fp4, "%.*s<param name=\"Name\" value=\"%s\">\n", level + 2, tabs, title);
		fprintf(fp4, "%.*s<param name=\"Local\" value=\"%s\">\n", level + 2, tabs, htmfile);
		fprintf(fp4, "%.*s</OBJECT>\n", level + 2, tabs);

		currentlevel = level;
		fprintf(fp5, "%s\n", htmfile);

	}
	while (-1 < currentlevel) {
		fprintf(fp4, "%.*s</UL>\n", currentlevel, tabs);
		currentlevel--;
	}
	fclose(fp);
	fclose(fp2);
	fclose(fp4);
	fclose(fp5);


	free(line);
	free(line2);
	free(output);
	return(0);
}


void trimleadingandTrailing(char* s)
{
	int  i, j;

	for (i = 0; s[i] == ' ' || s[i] == '\t'; i++);

	for (j = 0; s[i]; i++)
	{
		s[j++] = s[i];
	}
	s[j] = '\0';
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != ' ' && s[i] != '\t')
			j = i;
	}
	s[j + 1] = '\0';
}

int replacestr(char *str, char *substr,char * replace, char *output) {
	int i = 0;
	int j = 0;
	int flag = 0;
	int start = 0;
	// check whether the substring to be replaced is present 
	while (str[i] != '\0')
	{
		if (str[i] == substr[j])
		{
			if (!flag)
				start = i;
			j++;
			if (substr[j] == '\0') break;
			flag = 1;
		}
		else
		{
			flag = start = j = 0;
		}
		i++;
	}
	if (substr[j] == '\0' && flag)
	{
		for (i = 0; i < start; i++) output[i] = str[i];
		// replace substring with another string 
		for (j = 0; j < (int)strlen(replace); j++)
		{
			output[i] = replace[j];
			i++;
		}

		// copy remaining portion of the input string "str" 
		for (j = start + (int)strlen(substr); j < (int)strlen(str); j++)
		{
			output[i] = str[j];
			i++;
		}

		// print the final string 
		output[i] = '\0';
	}
	else {
		strcpy(output, str);
	}

	return(0);
}
