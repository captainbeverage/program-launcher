/*
  This program acts as a shell program. When run, the program asks the user to 
  enter a command. The user enters the name of a program, followed by any 
  parameters the program requires. For example, the user can run ls, pwd, date, 
  git status, git add <filename>, etc. and the program will launch with any 
  arguments provided.
**/

#include <iostream>
#include <unistd.h>
using namespace std;

/*
  This function parses the string entered by the user so that the program can
  be launched with the first word being the program, and all the remaining words
  as arguments.
**/
void parse(char* cmd, char** tokens) {
	// Loops through the entire char array
	while(*cmd != '\0') {
		// When a space is found, it is replaced with NULL, and the pointer is
		// incremented to the next value.
		while(*cmd == ' ' || *cmd == '\n' || *cmd == '\t') {
			*cmd = '\0';
			*cmd++;
		}

		// The tokens pointer is pointed to the current cmd location, which is the
		// location of the first letter of the current word. Tokens is incremented.
		*tokens = cmd;
		*tokens++;

		// Cmd loops through the char array until it find another space or NULL
		while(*cmd != '\0' && *cmd != ' ' && *cmd != '\n' && *cmd != '\t') {
			cmd++;
		}
	}
	// Tokens is pointed at the final NULL to indicate the end of the char array
	*tokens = '\0';

}

/*
  This function launches the program by creating a fork and passing the child
  process the tokens array to the execvp method.
**/
void launch(char** tokens) {
	pid_t id, wp_id;               // Holds the process id's of the parent and child
	int execStatus, parentStatus;  // Holds the int value of the status

	// The process is forked and assigned to id
	id = fork();

	// Checks for errors in the forking process
	if(id == -1) {
		cout << "Error.... process creation failed" << endl;
	} else if(id == 0) {
		// Launches the program with the name of the program and its parameters
		execStatus = execvp(*tokens, tokens);
		
		// Checks of there was an error launching the program and exits the program
		if(execStatus < 0) {
			cout << "Error... failed to execute" << endl;
			exit(1);
		}
	} else {
		// The parent process waits while the child process is running
		wp_id = wait(&parentStatus);
		while (id != wp_id);
	}

}

// Main function
int main() {

	// Char array to hold input and pointer for use in the parse and launch functions
	char cmd[100];
	char* tokens[100];

	// Provides instructions to the user
	cout << "-------------------------------------------------" << endl;
	cout << "                PROGRAM LAUNCHER" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Type program name and arguments to launch program" << endl;
	cout << "Type 'exit' to quit" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Enter command: ";

	//Gets input from the user
	cin.getline(cmd, 100);

	// Parses the user's input
	parse(cmd, tokens);

	// Continues running programs and getting input while the user doesn't enter "exit"
	while(strcmp(*tokens, "exit") != 0) {
		// Launches the program based on the parsed tokens
		launch(tokens);

		cout << "Enter command: ";
		cin.getline(cmd, 100);

		parse(cmd, tokens);
	}

	// Lets the user know the program has ended
	cout << "Exiting PROGRAM LAUNCHER..." << endl;

	return 0;
}