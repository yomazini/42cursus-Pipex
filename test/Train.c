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


// 2️⃣ execve()
// What is it?

//     execve() replaces the current process with a new program.
//     It does not return if successful (the old process is completely replaced).

// pathname: Path to the program (e.g., /bin/ls).
// argv[]: Arguments (e.g., ["ls", "-l", NULL]).
// envp[]: Environment variables (can pass environ).


// int main() {
//     char *args[] = {"/bin/ls","-la", NULL};

//     printf("Before execve\n");
//     execve("/bin/ls", args, NULL);
//     printf("This will not be printed!\n");

//     return 0;
// }

		/*------------------------------------------*/

// 5/ Inter-Process Communication "pipe and heredoc 'ONLY IDEA AND HOW it works' " 

// 1️⃣ pipe()
// What is it?

//     pipe() creates a unidirectional communication channel between processes.
//     It allows one process to write and another to read.
//     Works with file descriptors.

// int main()
// {
// 	int fd[2];
// 	char *chhhar = "Hello mothfckck";
// 	int len = strlen(chhhar);
// 	char buffer[25];
// 	close (1);
// 	close (0);
// 	int flag = pipe(fd);
// 	write(fd[1],chhhar,len);
// 	read(fd[0],buffer,len);
// 	printf("\nreceived: %s\n",buffer);
// }	

// int main()
// {
// 	char buffer[25];
// 	int len;
// 	int fds[2];
// 	pipe(fds); // here pay attetion 
// 	pid_t pid = fork(); // and here (what is switch the two)
// 	if (pid == 0)
// 	{
// 		read(fds[0],buffer,sizeof(buffer));
// 		printf("Child Recierved : %s\n",buffer);
// 	}
// 	else 
// 	{
// 		write(fds[1],"Message from parent", 19);

// 	}
// }

//heredoc

// int main() {
//     char buffer[100];

//     printf("Enter text (type 'STOP' to end):\n");
//     while (1) {
//         fgets(buffer, sizeof(buffer), stdin);
//         if (strncmp(buffer, "STOP", 4) == 0) break;
//         printf("You entered: %s", buffer);
//     }
//     return 0;
// }

// 2️⃣ heredoc
// What is it?

//     heredoc (<< DELIMITER) allows a shell script or program to take multiple lines of input until a specific keyword (delimiter) is entered.
//     In pipex, it acts as an alternative to a file for input.

// How It Works in Shell?

// cat << EOF
// Hello
// This is a heredoc
// EOF

// ✅ Output:

// Hello
// This is a heredoc

// (The input stops when EOF is entered.)

/*
Scenario	First Version (pipe() before fork())	Second Version (fork() before pipe())
✅ Pipe exists in both processes?	✅ Yes	❌ No (child may not inherit a valid pipe)
✅ Parent writes, child reads?	✅ Works correctly	❌ May fail (invalid file descriptors)
✅ Safe behavior?	✅ Yes, predictable	❌ No, can cause hangs/crashes
*/

//Best Practice	Always call pipe(fds); before fork(); to ensure both processes inherit the same pipe.

		/*------------------------------------------*/

// 6/ Process Termination and Waiting "exit, wait, waitpid"
		/*------------------------------------------*/


// 1️⃣ exit()
// What is it?

//     exit() terminates the current process immediately.
//     Can return an exit status (0 = success, non-zero = failure).

// 2️⃣ wait()
// What is it?

//     wait() makes the parent process wait for a child process to finish.
//     Returns the PID of the terminated child.

// Syntax:

// pid_t wait(int *status);

//     status: Stores child's exit status.

// 🚀 Exercise 2: Using wait()

// Task:

//     Fork a child process.
//     The child should print "Child running" and exit with 100.
//     The parent should wait and print "Child finished with status: X".

// 📌 Hint: Use int status; wait(&status);.

// int main()
// {
// 	char buf[25];
// 	pid_t pid = fork();
// 	int status;

// 	if (pid == 0)
// 	{
// 		printf("Child Running");
// 		exit(-1); // will output with 255 unsighnted char ;
// 	//	exit(0);
// 	}
// 	else
// 	{
// 		wait(&status);
// 		//wait(NULL);
// 		printf("child finish with status %d\n", WEXITSTATUS(status));
// 	}
// }

// 3️⃣ waitpid()
// What is it?

//     A more flexible version of wait(), allowing:
//         Waiting for a specific child.
//         Non-blocking behavior (using WNOHANG).

// Syntax:

// pid_t waitpid(pid_t pid, int *status, int options);

//     pid: The specific child PID (or -1 for any child).
//     status: Stores exit status.
//     options: Can be 0 (blocking) or WNOHANG (non-blocking).

// int main() {
//     int status1, status2;
//     pid_t pid1 = fork();

//     if (pid1 == 0) {  // First child
//         printf("Child 1 running...\n");
//         exit(1);
//     }

//     pid_t pid2 = fork();
//     if (pid2 == 0) {  // Second child
//         printf("Child 2 running...\n");
//         exit(2);
//     }

//     // Parent waits for both children
//     waitpid(pid1, &status1, 0);
//     printf("Parent: Child 1 exited with status %d\n", WEXITSTATUS(status1));

//     waitpid(pid2, &status2, 0);
//     printf("Parent: Child 2 exited with status %d\n", WEXITSTATUS(status2));

//     return 0;
// }




// 7/ Integration - Building a Mini Pipex "to apply all these functions simple"

		// 	Mini Pipex Implementation
    	// Exercise:
     	//    Implement ./pipex infile "cat" "wc -l" outfile.
     	//    Use fork(), pipe(), dup2(), execve(), and waitpid().


/*
Exercise 1: Execute Two Commands with a Pipe (ls | wc -l)
📝 Task:

    Create a parent-child process using fork().
    The child process runs ls and sends output to a pipe.
    The parent process reads from the pipe and executes wc -l.
    Use perror() for errors, waitpid() to wait for child processes.

*/
// int main()
// {
// 	int fds[2];

// 	if (pipe(fds) == -1)
// 	{
// 		perror("EROOR IN PIPE: ");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid_t pid1 = fork();
// 	if (pid1 == -1)
// 	{
// 		perror("ERROR IN pid1");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid1 == 0)
// 	{
// 		dup2(fds[1],1);
// 		close(fds[0]);
// 		close(fds[1]);
// 		char *char1[] = {"/bin/ls","-l",NULL};
// 		execve(char1[0],char1,NULL);
// 		perror("the exceeve is failed\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid_t pid2 = fork();
// 	if (pid2 == -1)
// 	{
// 		perror("ERror in pid2");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid2 == 0)
// 	{
// 		dup2(fds[0],0);
// 		close(fds[0]);
// 		close(fds[1]);
// 		char *char2[] = {"/usr/bin/wc","-l",NULL};
// 		execve(char2[0],char2,NULL);
// 		perror("the exceve is faileed");
// 		exit(EXIT_FAILURE);
// 	}
// 	close(fds[0]);
// 	close(fds[1]);
// 	//  close(0);
// 	waitpid(pid1,NULL,0);
// 	waitpid(pid2,NULL,0);

// // 	 Final Takeaways
// // 	Code	Purpose	What Happens If Not Closed?
// // 	close(fds[0]);	Closes pipe read end in parent.	wc -l may hang forever, waiting for EOF.
// //	close(fds[1]);	Closes pipe write end in parent.	Pipe remains open, leading to deadlocks.
// // 	close(1);	Closes stdout.	Nothing prints to terminal.
// //	waitpid(pid1, NULL, 0);	Waits for child 1 (ls -l).	Zombie processes may appear.
// // 	waitpid(pid2, NULL, 0);	Waits for child 2 (wc -l).	Parent may exit before child finishes.

// }

				/*----------*/

/*
Exercise 2: Create & Delete a File, Then Execute a Command
📝 Task:

    Check if testfile.txt exists using access().
    If the file does not exist, create it and write "Hello, world!".
    Fork a child process:
        Use dup() or dup2() to redirect stdout to the file.
        Execute echo "This is a test".
    Wait for the child process using wait().
    Delete testfile.txt using unlink().
    Use perror() for error handling when opening/writing the file.
*/

int main()
{
	char *file  = "file.txt";
	// check if file if not write (hello workdld )
	if (access(file, F_OK) == -1)
	{
		perror("\nERROR: ");
		int fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
		{
			perror("\nERROR 01: ");
			exit(EXIT_FAILURE);
		}
		write(fd,"HELLO THIS\n", strlen("HELLO THIS\n"));
		close(fd);
	}
	pid_t pid1 = fork();
	if (pid1 == -1)
	{
		perror("\nERRO: ");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0) // child process
	{

		char *str[] = {"/bin/echo","This is just a small test",NULL};
		int fd1 = open(file, O_RDWR | O_APPEND);
		// check for failure 
		if (fd1 == -1)
		{
			perror("ERRO hna:");
			exit(EXIT_FAILURE);
		} 
		dup2(fd1, 1);
		//close(1);
		execve(str[0],str,NULL);
		perror("this is an error\n");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	// fork child 

	// write this is test ffro m chidl in to file 
	sleep(5);
	// delete with unlink 
	if (unlink(file) == -1)
	{
		perror("ERR:");

	}
	else
		printf("file deleted succesfully");
}

		/*------------------------------------------*/

// 8/ Summary of all to Recap;

		/*------------------------------------------*/
// 9/ 

		/*------------------------------------------*/

	