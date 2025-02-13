#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <errno.h>


// This file only for train on the new functions each exercice and each concept behind it; and where come from in breif and some commpn Q&A and each has main function of course;

// 1/ Understanding Error Handling "perror and strerror and errno"

// int main()
// {
// 	int fd = open("apahnotexist.txt",O_RDONLY);
// 	if (fd == -1)
// 		fprintf(stderr,"shit prbl in fd: %d",errno);
// 		perror("\nErr: ");
// 	if (errno == 2)
// 	{
// 		fprintf(stderr,"\noh you say here the reason %s", "file not found" );
// 		printf("\n Oh shit %s",strerror(errno));
// 	}
// 	    if (remove("fake.txt") != 0) {  // Try deleting a non-existing file
//         printf("\n Hey Error: %s\n", strerror(errno));
// 	}
// }
/*
	Explanation:

1/	    errno is a global integer variable that stores the error code when a system call or library function fails.
    Defined in <errno.h>, it helps programmers understand why a function failed.

2/	perror() is used to print an error message to stderr when a function fails.
It prints:

    The custom string message you provide.
    The corresponding system error message based on errno.

3/ strerror() converts an error code (errno) into a human-readable string.
Defined in <string.h>, it returns a string (unlike perror(), which directly prints the message).
*/

/*
	Key Takeaways
Function	Purpose
errno	Stores the last error code from a failed system call
perror()	Prints an error message to stderr based on errno
strerror()	Converts errno into a human-readable string
*/

// 2/ File Access and Manipulation "access and unlink"

// 3/  Duplicating File Descriptors "dup and dup2"

// 4/ Process Creation and Execution "fork and execve"

// 5/ Inter-Process Communication "pipe and heredoc 'ONLY IDEA AND HOW it works' " 

// 6/ Process Termination and Waiting "exit, wait, waitpid"

// 7/ Integration - Building a Mini Pipex 

		/*------------------------------------------*/

// 2/ File Access and Manipulation "access and unlink"

/*
    access() checks if a file exists and whether the calling process has permission to read, write, or execute it.
	Returns 0 if the file exists and has the required permissions.
	Returns -1 if the file does not exist or lacks permissions.

	Mode Flags (Permissions to Check)
	Mode	Meaning
	F_OK	Check if file exists
	R_OK	Check if file is readable
	W_OK	Check if file is writable
	X_OK	Check if file is executable
*/

// int main()
// {
// 	int exist = access("test.txt", F_OK);
// 	int read = access("test.txt", R_OK);
// 	int write = access("test.txt", W_OK);
// 	int execute = access("test.txt", X_OK);
// 	int all = access("test.txt", F_OK | W_OK | X_OK | R_OK);
// 	if (!exist)
// 		printf("\nyes it exist");
// 	if (!read)
// 		printf("\nyes it read");
// 	if (!write)
// 		printf("\nyes it write\n");
// 	if (!execute)
// 		printf("\nyes it execute\n");
// 	if (!all)
// 		printf("\nyes it all\n");
	
// 	if (exist == -1)
// 		fprintf(stderr,"\n No1 : %s",strerror(errno));
// 	if (read == -1)
// 		fprintf(stderr,"\n No2 : %s",strerror(errno));
// 	if (write == -1)
// 		fprintf(stderr,"\n No3 : %s",strerror(errno));
// 	if (execute == -1)
// 		fprintf(stderr,"\n No4 : %s",strerror(errno));
// 	if (all == -1)
// 		fprintf(stderr,"\n No5 : %s",strerror(errno));
// }


// now for unlink 

//unlink() deletes a file from the filesystem. 
// Returns 0 if successful.
// Returns -1 if an error occurs (e.g., file does not exist, no permission).

// int main ()
// {
// 	int rem= unlink("apah.txt");
	
// 	if (!rem)
// 		printf("Done\n");
// 	else if (rem == -1)
// 		perror("NAh");
// 		#include <stdio.h>
//     if (unlink("mydir") == 0)
//         printf("Directory deleted successfully!\n");
//     else
//         perror("unlink failed");

//     if (remove("mydir") == 0)
//         printf("Directory deleted successfully with remove!\n");
//     else
//         perror("remove failed");

//     return 0;

// }



/*
	Grreat now the Difference between remove() & unlink()

	Feature				unlink()			remove()
	Header File			<unistd.h>			<stdio.h>
	Works on			Only files			Files and empty directories
	Low-Level\Level		Low-level (direct system call)	High-level (library function)
	Removes Directory Entry	✅ Yes					✅ Yes
	Deletes Opened Files	✅ Yes (file data exists until closed)	❌ No (fails if file is in use)
	Can Delete Empty Directories	❌ No			✅ Yes
*/
		/*------------------------------------------*/

// 3/  Duplicating File Descriptors "dup and dup2"

// int main()
// {
// 	int fd1 = open("test.txt", O_RDONLY);
// 	if (fd1 == -1)
// 		perror("ER1: ");
// 	int fd2 = dup(fd1);
// 	close(fd1);
// 	if (fd2 == -1)
// 		perror("ER2:");
// 	close (fd1);
// 	//close (fd2);

// 	char *ptr = malloc (10);
// 	ssize_t byte_read = read(fd2,ptr,8);
// 	ptr[byte_read] = '\0';
// 	printf("%s",ptr);
// 	free(ptr); // shit valgrind aasat

// }

// int main()
// {
// 	int fd1 = open("test.txt", O_RDONLY | O_RDWR | O_CREAT);
// 	if (fd1 == -1)
// 		perror("ER1: ");
// 	int fd2 = dup2(fd1,1); // this is rediect form stdout into fd1
// 	write(1,"tapa papa",15); // look at file not std out

// }

/*
Feature											dup()	dup2()
Creates a new file descriptor					✅ Yes	✅ Yes
Closes existing file descriptor					❌ No	✅ Yes (if newfd is open)
Allows specifying new file descriptor number	❌ No	✅ Yes
System call overhead							Lower	Slightly higher
*/

// 1️⃣ dup()
// What is it?

//     Duplicates a file descriptor and returns a new one.
//     The new file descriptor points to the same file as the original.

// 2️⃣ dup2()
// What is it?

//     Redirects a file descriptor to a specific new number.
//     More flexible than dup().


		/*------------------------------------------*/
// 4/ Process Creation and Execution "fork and execve"


/*
1️⃣ fork()
What is it?

    fork() creates a new process (child process).
    The child process is an exact copy of the parent.
    After calling fork(), two processes exist:
        Parent process (original)
        Child process (newly created)
*/
// int main()
// {
// 	pid_t pid1= fork();
// 	if (pid1 == 0)
// 	{
// 		// pid_t pid = getpid();
// 		// close(pid);
// 		return 1;
// 		printf("\ni am child my pid:%d",getpid());
// 		sleep(1);
// 		printf("\nfff");
// 		sleep(1);
// 	}
// 	printf("\ni ma the parent my child pid is %d",pid1);
// }


// int main() {
//     pid_t pid = fork();

//     if (pid == -1) {
//         perror("fork failed");
//         return 1;
//     }

//     if (pid == 0) {
//         printf("I am the child!\n");
//     } else {
//         waitpid(pid, NULL, 0); // Parent waits for the child to finish
//         printf("I am the parent!\n");
//     }

//     return 0;
// }


int main ()
{
	printf("Before the execve\n");
	char **str; 
	str = {,,NULL};
	execve("/bin/ls","-la");
	printf("\nafter");
}

		/*------------------------------------------*/

// 5/ Inter-Process Communication "pipe and heredoc 'ONLY IDEA AND HOW it works' " 
		/*------------------------------------------*/

// 6/ Process Termination and Waiting "exit, wait, waitpid"
		/*------------------------------------------*/

// 7/ Integration - Building a Mini Pipex 

		// 	Mini Pipex Implementation
    	// Exercise:
     	//    Implement ./pipex infile "cat" "wc -l" outfile.
     	//    Use fork(), pipe(), dup2(), execve(), and waitpid().

		/*------------------------------------------*/

// 8/ Summary of all to Recap;

		/*------------------------------------------*/
// 9/ 

		/*------------------------------------------*/

	