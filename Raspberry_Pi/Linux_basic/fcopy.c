#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv){
	int n;
	FILE *in, *out;
	char buf[1024];

	// Print error and terminate if there is no file name to be copied in command element
	if (argc != 3){
		fprintf(stderr, "Usage : fcopy file1 file2\n");
		return -1;
	}

	// Open the origin file of copying with read mode
	if ((in = fopen(argv[1], "r")) == NULL){
		perror(argv[1]);
		return -1;
	}

	// Open the result file which will be copied with write mode(create new file | erase origin file contents)
	if ((out = fopen(argv[2], "w")) == NULL){
		perror(argv[2]);
		return -1;
	}

	// Read the origin file and write to the file will be copied
	while ((n = fread(buf, sizeof(char), BUFSIZ, in)) > 0)
		fwrite(buf, sizeof(char), n, out);

	// Close the opened files
	fclose(out);
	fclose(in);

	// return 0 when this program is terminated normally
	return 0;
}
