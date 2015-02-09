#include <iostream>
using namespace std;

void parse(char* cmd, char** tokens) {

	char** arrayOfTokens[80];

	tokens = &cmd;

	arrayOfTokens[0] = tokens;
	cout << *arrayOfTokens[0];

}

int main() {

	char userInput[80];
	char* inputPointer;
	char** tokens;

	cout << "Please enter a command: ";
	cin.getline(userInput, 80);
	inputPointer = userInput;

	parse(inputPointer, tokens);

	return 0;
}