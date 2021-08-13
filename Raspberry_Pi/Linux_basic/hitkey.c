#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int kbhit(void)
{
    struct termios oldt, newt; 		// struct about terminal
    int ch, oldf;

    tcgetattr(0, &oldt); 		// get the information set on right terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); 	// unlock the normal mode input and echo 
    tcsetattr(0, TCSANOW, &newt); 	// set the terminal to new value
    oldf = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, oldf | O_NONBLOCK); 	// set the input to non-blocking mode

    ch = getchar();

    tcsetattr(0, TCSANOW, &oldt); 	/* apply the terminal attribute to the origininal value */
    fcntl(0, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin); 		/* read from the front and put again the read character */
        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i = 0;
    for(i = 0; ; i++) {
        if(kbhit()) { 			/* check if keyboard is clicked or not */
            switch(getchar()) { 	/* read character */
                case 'q': 		/* terminate if read character is q */
                    goto END;
                    break;
            };
        }

        printf("%20d\t\t\r", i); 	/* print the counting number */
        usleep(100); 			/* sleep for 100 ms */
    }

END:
    printf("Good Bye!\n");
    return 0;
}
