#include <iostream>
using namespace std;

void parse(char* cmd, char** tokens) {
	int i = 0;
	int j = 0;
	int k = 0;

	while(cmd[i] != '\0') {
		if(cmd[i] == ' ') {
			cmd[i] = '\0';
			tokens[k] = &cmd[j];
			j = i+1;
			k++;
		}
		i++;
	}

	tokens[k] = &cmd[j];

	for(int index = 0; index <= k; index++) {
		cout << tokens[index] << endl;
	}
}

int main() {

	char input[80];
	cout << "Enter command: ";
	cin.getline(input, 80);

	char* cmd = input;
	char** tokens = &cmd;

	parse(cmd, tokens);

	return 0;
}