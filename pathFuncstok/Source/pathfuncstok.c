/*
 * pathfuncstok.c
 *
 *  Created on: 22 feb. 2020
 *      Author: ipserc
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

char * pathdirname(const char * path)
{
	char * dirname = (char *)malloc(strlen(path) + 1);
	dirname = (char *)memset(dirname, '\0', strlen(dirname) + 1);
	char * token;
	char * prevtoken;
	const char * sep = "/";

	/* if path last character is sep path is the dirname */
	if (*(path+strlen(path)-1) == *sep)
	{
		sprintf(dirname, "%s",path);
		return dirname;
	}
	/* if there is no sep in path, dirname is empty */
	if (!strstr(path, sep))
	{
		sprintf(dirname, "%s", "");
		return dirname;
	}
	/* if first character is sep in path, starts dirname with sep */
	if (*(path) == *sep) sprintf(dirname, "/");

	char * pathname = (char *)malloc(strlen(path) + 1);
	sprintf(pathname, "%s",path);
	/* get the first token */
	token = (char *)strtok(pathname, sep);
	if (!token)
	{
		free(pathname);
		return dirname;
	}

	/* walk through other tokens */
	while(token) {
		prevtoken = token;
	    token = (char *)strtok(NULL, sep);
		if (token) sprintf(dirname, "%s%s/", dirname, prevtoken);
	}
	free(pathname);
	return dirname;
}

char * pathbasename(const char * path)
{
	char * filename = (char *)malloc(strlen(path) + 1);
	char * token;
	char * prevtoken;
	const char * sep = "/";

	/* if path last character is sep, filename is empty */
	if (*(path+strlen(path)-1) == *sep) {
		sprintf(filename, "%s", "");
		return filename;
	}
	sprintf(filename, "%s",path);
	/* if there is no sep in path, filename is path */
	if (!strstr(filename, sep)) return filename;

	/* get the first token */
	token = (char *)strtok(filename, sep);
	if (!token)
	{
		sprintf(filename, "%s", "");
		return filename;
	}

	/* walk through other tokens */
	while(token) {
		prevtoken = token;
	    token = (char *)strtok(NULL, sep);
	}
	sprintf(filename, "%s", prevtoken);
	return filename;
}

int main(void)
{
	char path[200];
	char * filename;
	char * dirname;

	sprintf(path, "%s", "/dir1/dir2/dir3/dir4/fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "/");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "/dir1/dir2/dir3/dir4/");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "/fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "./fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "../fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	sprintf(path, "%s", "../dir1/fichero.ext/dir3/fichero.ext");
	printf("Path:%s:\n", path);
	dirname = pathdirname(path);
	printf("Dirname:%s:\n", dirname);
	filename = pathbasename(path);
	printf("Filename:%s:\n\n", filename);
	free(filename);
	free(dirname);

	return 1;
}
