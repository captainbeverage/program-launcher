#include <iostream>
#include <unistd.h>
using namespace std;

void parse(char* cmd, char** tokens) {
	
	while(*cmd != '\0') {
		while(*cmd == ' ' || *cmd == '\n' || *cmd == '\t') {
			*cmd = '\0';
			*cmd++;
		}
		*tokens = cmd;
		*tokens++;

		while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t' && *cmd != '\n') {
			cmd++;
		}
	}
	*tokens = '\0';

}

void launch(char** tokens) {
	pid_t id, wp_id;
	int status, status2;

	id = fork();

	if(id == -1) {
		cout << "Error.... process creation failed" << endl;
	} else if(id == 0) {
		status2 = execvp(*tokens, tokens);
		
		if(status2 < 0) {
			cout << "Error... failed to execute" << endl;
			exit(1);
		}
	} else {
		wp_id = wait(&status);
		while (id != wp_id);
	}

}

int main() {

	char cmd[100];
	char* tokens[100];

	cout << "Enter command: ";
	cin.getline(cmd, 100);

	parse(cmd, tokens);

	while(strcmp(tokens[0], "exit") != 0) {
		launch(tokens);

		cout << "\nEnter command: ";
		cin.getline(cmd, 100);

		parse(cmd, tokens);
	}

	cout << "\nExiting program..." << endl;

	return 0;
}