/*
 * pathfuncsrev.c
 *
 *  Created on: 22 feb. 2020
 *      Author: ipserc
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

char * strrev(char * rev, const char * fore)
{
	int len = strlen(fore);

	rev = (char *)memset(rev, '\0', len + 1);
	for(int i = 0; i < len; ++i)
		*(rev + i) = *(fore + len - i - 1);
	return rev;
}

char * pathdirname(const char * path)
{
	const char * sep = "/";
	char * dirname = (char *)malloc(strlen(path) + 1);
	dirname = (char *)memset(dirname, '\0', strlen(dirname) + 1);

	/* if path last character is sep path is the dirname */
	if (*(path+strlen(path)-1) == *sep) {
		sprintf(dirname, "%s",path);
		return dirname;
	}
	/* if there is no sep in path, dirname is empty */
	if (!strstr(path, sep)) return dirname;
	/* if first character is sep in path, starts dirname with sep */
	if (*(path) == *sep) sprintf(dirname, "/");

	char * revpath = malloc(strlen(path) + 1);
	revpath = strrev(revpath, path);
	sprintf(dirname, "%s", strchr(revpath, *sep));
	sprintf(dirname, "%s", strrev(revpath, dirname));
	free(revpath);
	return dirname;
}

char * pathbasename(const char * path)
{
	const char * sep = "/";
	int len = strlen(path);
	char * filename = (char *)malloc(strlen(path) + 1);

	/* if path last character is sep, filename is empty */
	if (*(path+len-1) == *sep) {
		sprintf(filename, "%s", "");
		return filename;
	}
	/* if there is no sep in path, filename is path */
	if (!strstr(path, sep))
	{
		sprintf(filename, "%s", path);
		return filename;
	}

	char * revfilename = (char *)malloc(strlen(path) + 1);
	revfilename = strrev(revfilename, path);
	for(int i = 0; i < len; ++i)
		if (*(revfilename + i) == *sep)
		{
			*(revfilename + i) = '\0';
			break;
		}

	filename = strrev(filename, revfilename);
	free(revfilename);
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
