#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv){
	int n, in, out;
	char buf[1024];

	// Print error and terminate if there is no file name to be copied in command element
	if (argc < 3){
		write(2, "Usage : copy file1 file2\n", 25);
		return -1;
	}

	// Open the origin file of copying with read mode
	if ((in = open(argv[1], O_RDONLY)) < 0){
		perror(argv[1]);
		return -1;
	}

	// Open the result file which will be copied with write mode(create new file | erase origin file contents)
	if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
		perror(argv[2]);
		return -1;
	}

	// Read the origin file and write to the file will be copied
	while ((n = read(in, buf, sizeof(buf))) > 0)
		write(out, buf, n);

	// Close the opened files
	close(out);
	close(in);

	// return 0 when this program is terminated normally
	return 0;
}
