//#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <type_traits>
#include <vector>
#include <string>
#include <stack>
#include <sstream> 

using namespace std;
char testChar = ' ', stackx[23] = " ", testWord[23];
char testCharList[23];
char keyWords[23][10] = { "int", "float", "bool", "boolean", "if", "else", "then", "endif", "while",
		"whileend", "do", "doend", "for", "forend", "input", "output",
		"and", "or", "function", "void", "main", "true", "false" };
bool conditionset;
int flag = 0, lineNum = 1, stackindex = 0;
ifstream file("SampleInputFile.txt");
ofstream myfile;

void error(string str)
{
	//Clear output file
	myfile.close();
	myfile.open("FinalOutput.txt", ios::out | ios::trunc);
	// Output error message
	myfile << "ERROR: " << str << " at line: " << lineNum;
	exit(EXIT_FAILURE);
}



//---------------------------PROJECT 3-------------------------------------
//INSTRUCTION ARRAY 
//SYMBOL TABLE

int Memory_Address = 5000;
string prevType = "";
vector<string> idList, typesList;
vector<int> memoryList;
string lastID = "";
string prevVar = "", nextVar = "";
char lastOp;

string instructions[1000];
int instructionLine = 1;
stack <int> s;
string delay = "";
char equation[10][23];
int iteration = 0;
bool isEquation = false;

/*for instructions that require an input for
integer value or memory location*/
void assemble(string instruction, int value) {
	cout << instructionLine;
	if (instruction == "PUSHI") 
		cout << "\tPUSHI\t";
	else if (instruction == "PUSHM") 
		cout << "\tPUSHM\t";
	else if (instruction == "POPM") 
		cout << "\tPOPM\t";
	else if (instruction == "JUMPZ") 
		cout << "\tJUMPZ\t";
	else if (instruction == "JUMP") 
		cout << "\tJUMP\t";
	else 
		error("Assembly Instruction not valid");
	instructionLine++;
	cout << value << " @ line " << lineNum << endl;
}


//for instructions that require no input
void assemble(string instruction) {
	cout << instructionLine;
	if (instruction == "STDOUT") 
		cout << "\tSTDOUT";
	else if (instruction == "STDIN") 
		cout << "\tSTDIN";
	else if (instruction == "ADD") 
		cout << "\tADD";
	else if (instruction == "SUB") 
		cout << "\tSUB";
	else if (instruction == "MUL") 
		cout << "\tMUL";
	else if (instruction == "DIV") 
		cout << "\tDIV";
	else if (instruction == "GRT") 
		cout << "\tGRT";
	else if (instruction == "LES") 
		cout << "\tLES";
	else if (instruction == "EQU") 
		cout << "\tEQU";
	else if (instruction == "NEQ") 
		cout << "\tNEQ";
	else if (instruction == "GEQ")
		cout << "\tGEQ";
	else if (instruction == "LEQ") 
		cout << "\tLEQ";
	else if (instruction == "LABEL") 
		cout << "\tLABEL";
	else 
		error("Assembly Instruction not valid");
	instructionLine++;
	cout << " @ line " << lineNum << endl;
}

void symbolTable()
{
	cout << "\n\n\t\tSYMBOL TABLE\nIdentifier\tMemoryLocation\tType\n";

	for (int i = 0; i < idList.size(); i++) {
		cout << idList.at(i) << "\t\t" << memoryList.at(i) << "\t\t" << typesList.at(i) << endl;
	}
	cout << endl << endl;
}





//-------------------------------------------------------------------------------------








bool isKeyword(char input[]) {
	int i;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keyWords[i], input) == 0) {
			return true;
		}
	}

	return false;
}







string addId() {
	string str, filtered;
	char operators[] = "+-*/%";
//	bool rightHandSide = true, firstOfLHS = true;


	//KEEP THIS CODE
	int i = 0;
	bool found = false;
	while (testWord[i] != NULL) { //filter out $
		if (testWord[i] != '$')
			filtered += testWord[i];
		i++;
	}

	//find if testWord already exists in idList
	i = 0;
	while (!found && i < idList.size()) {
		if (idList.at(i) == filtered) {
			found = true;
		}
		i++;
	}
	if (!found) {//if it doesn't exist in the list, add it
		if (prevType == "")
			error("No declaration given");
		idList.push_back(filtered);
		memoryList.push_back(Memory_Address);
		Memory_Address++;
		typesList.push_back(prevType);
	}


	if (prevVar == "") {
		prevVar = testWord;
	}
	else if (nextVar == "") {
		nextVar = testWord;
	}

	//adds id to equation
	i = 0;
	while (!isblank(testWord[i]) && i < 23) {
		equation[iteration][i] = testWord[i];
		i++;
	}
	iteration++;

	return str;
}





string analyzeSep() {
	//KEEP THIS CODE
	string str = " ";

	char openers[5] = { "([{'" }, closers[] = { ")]}'" };
	
	return str;
}





string analyzeKey() {
	//KEEP THIS CODE
	string str;

	char wordsWithParenthese[6][10] = { "if", "while", "for", "forend","function", "main" };

	for (int z = 0; z < 7; z++) {
		if (strcmp(testWord, wordsWithParenthese[z]) == 0)
			conditionset = true;
	}

	char importantKeys[6][10] = { "int", "bool", "float", "double", "char", "boolean" };
	for (int z = 0; z < 6; z++) {
		if (strcmp(testWord, importantKeys[z]) == 0)
			prevType = testWord;
	}

	for (int a = 0; a < 20; a++) {
		if (strcmp(testWord, keyWords[a]) == 0) {
			string key = (string)keyWords[a];

			if (a < 3) { //is a variable
				str += " <KeyWord> -> <Variable>\n";
				str += " <Variable> -> <" + key + ">";
			}
			else if (a > 2 && a < 13) {//is a conditional
				str += " <KeyWord> -> <Conditional>\n";
				str += " <Conditional> -> <" + key + "> + <Separator>";
			}
			else {//is a function
				str += " <KeyWord> -> <Function>\n";
				str += " <Function> -> <" + key + ">";
			}
		}


	}

	return str;
}





string syntaxNum(char str[]) {
	//cout << "current number is " << atoi(str) << " (" << str << ")" << endl;
	/*if (delay != "") {//if delay is active
		assemble("PUSHI", atoi(str));

		for (int i = 0; i < idList.size(); i++) {//find memory address
			if (idList.at(i) == prevVar) {
				assemble(delay, (5000 + i));
				cout << "assembled at " << lineNum << "\n\n";

			}
		}
	}*/
	//equation[iteration] = str;
	delay = "";
	for (int i = 0; i < 23; i++) {
		equation[iteration][i] = testWord[i];
	}
	iteration++;
	return "";
}





string analyzeOp() {

	string str;

	lastOp = testChar;

	bool foundFirst = false;
	bool foundSecond = false;



	//only if operator is an = sign then delay must occur
	if (testChar == '=') {

		delay = "POPM";
		isEquation = true;
	}
	else {//all other operators

		for (int i = 0; i < idList.size(); i++) {
			if (!foundFirst && idList.at(i) == prevVar) {
				//cout << "prevVar: " << prevVar << " @ " << lineNum << "\n";
				//cout << "Operator: " << testChar << endl;
				assemble("PUSHM", (5000 + i));
				foundFirst = true;
				//cout << " at iteration " << i << " at line " << lineNum << endl;
			}
		}

		/*if (!foundSecond && idList.at(i) == nextVar) {
			assemble("PUSHM", (5000 + i));
			//cout << "WITH " << prevVar << " + " << nextVar << endl;
			foundSecond - true;
			//cout << " at iteration " << i  << " at line " << lineNum << endl;
			*/

		
	}


	equation[iteration][0] = testChar;
	iteration++;

	return str;
}





int getAddr(string id) {
	for (int i = 0; i < idList.size(); i++) {
		if (id == idList.at(i))
			return memoryList.at(i);
	}
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void getInstruction(string str) {
	
	//cout << "Instruction: ___" << str << "___\n";

	if (isNumber(str)) {
		int val = 0;
		stringstream num(str);
		num >> val;
		cout << str << " IS NUMBER " << val;
	}

	if (testChar == '*') {

		assemble("MULT");
	}
	else if (testChar == '/') {
		assemble("DIV");
	}
	else if (testChar == '+') {
		assemble("ADD");
	}
	else if (testChar == '-') {
		assemble("SUB");
	}
	else if (str == "=") {
		//skip
	}
	else if (isNumber(str)) {
		int val = 0;
		stringstream num(str);
		num >> val;
		assemble("PUSHI", val);
	}
	else {//is an id
		assemble("PUSHM", getAddr(str));
	}
}













//-----------------------------------------------------------------------------------------


void lexer(int& j) {
	bool print = false, printline = false, test = false;
	char operators[] = "+-*/%=", separators[] = "'(){}[],.:;!";
	int i;

	//discard all spaces
	while (testChar == ' ')
		testChar = file.get();

	//check if comment
	if (testChar == '!') {
		testChar = file.get();
		while (testChar != '!') {
			testChar = file.get();
		}
		return;
	}

	//Check operator
	for (i = 0; i < 6; ++i)
	{
		if (testChar == operators[i]) {
			//cout << testChar << " is operator\n";
			myfile << "\n\nToken:\tOPERATOR" << "\t\tLexme:\t" << testChar;
			if (printline)
				myfile << " at line " << lineNum;
			myfile << endl;
			if (print)
				cout << "\nToken:\tOPERATOR" << "\t\tLexme:\t" << testChar << endl;
			myfile << analyzeOp();
			flag = 1;
			return;
		}
	}

	//Check seprator
	for (int m = 0; m < 11; m++)
	{
		if (testChar == separators[m]) {
			//cout << testChar << " is separator\n";
			myfile << "\n\nToken:\tSEPARATOR" << "\t\tLexme:\t" << testChar;
			if (printline)
				myfile << " at line " << lineNum;
			myfile << endl;
			if (print)
				cout << "\nToken:\tSEPARATOR" << "\t\tLexme:\t" << testChar << endl;
			myfile << analyzeSep();
			flag = 1;
			return;
		}
	}

	//Check if number
	if (isdigit(testChar))
	{
		char str[5];
		int x = 0;
		testWord[j] = '\0';
		j = 0;
		str[x++] = testChar;

		while (isdigit(file.peek())) {
			testChar = file.get();
			str[x] = testChar;
			x++;
		}

		if (x == 0)
			myfile << str[0];
		else {
			for (int u = 0; u < x; u++) {
				testWord[j] = '\0';
				myfile << str[u];
			}
		}
		if (printline)
			myfile << " at line " << lineNum;
		myfile << endl;
		flag = 0;
		myfile << syntaxNum(str);
		return;
	}

	//If the first character is not operator nor the seperator, get all the rest of word until reach space
	if (isalnum(testChar) || testChar == '$')
	{
		//cout << "IS ALNUM: " << testChar << "\tj = " << j << endl;
		bool stop = false;
		char next;
		if (testChar == ' ' || testChar == '\n')
			stop = true;
		while (!stop) {
			testWord[j++] = testChar;
			if (strcmp(testWord, "endif$") == 0)//competes program @ endif statement
			{
				file.close();
				myfile.close();
				symbolTable();
				exit(EXIT_SUCCESS);
				return;
			}
			next = file.peek();
			for (i = 0; i < 11; ++i)
			{
				if (next == separators[i]) {
					stop = true;
				}
			}
			for (i = 0; i < 6; ++i)
			{
				if (next == operators[i]) {
					stop = true;
				}
			}
			if (!stop)
				testChar = file.get();
			if (testChar == ' ' || testChar == '\n')
				stop = true;
		}

		test = true;
		//Make the rest of c string become null
		testWord[j] = '\0';
		//reset new index of testWord for next testWord
		j = 0;


		if (isKeyword(testWord)) {
			myfile << "\n\nToken:\tKEYWORD" << "\t\t\tLexme:\t" << testWord;
			if (printline)
				myfile << " at line " << lineNum;
			myfile << endl;
			if (print)
				cout << "\nToken:\tKEYWORD" << "\t\t\tLexme:\t" << testWord << endl;
			myfile << analyzeKey();
		}
		else {
			myfile << "\n\nToken:\tIDENTIFIER" << "\t\tLexme:\t" << testWord;
			if (printline)
				myfile << " at line " << lineNum;
			myfile << endl;
			if (print)
				cout << "\nToken:\tIDENTIFIER" << "\t\tLexme:\t" << testWord << endl;
			myfile << addId();
		}
		flag = 0;
	}
	//cout << test << endl;

}





//-----------------------------------------------------------------------------------------


int main() {

	myfile.open("FinalOutput.txt");    //makes file named Final Output
	myfile << "            Final Output" << endl;
	myfile << "----------------------------------------------------" << endl;

	if (!file.is_open()) {
		//cout << "Error while opening the file, please change file name to SampleInputFile\n";
		cout << "EXITED";
		exit(0);
	}

	int i = 0, j = 0;
	while (!file.eof())
	{

		testChar = file.get();
		testCharList[i] = testChar;
		i++;
		if (testChar == '\n')
		{
			prevType = "";
			prevVar = "";
			nextVar = "";
			lineNum++;
			for (int i = 0; i < 20; i++)
				testCharList[i] = '\0';
			i = 0;
			
			cout << "Result of Equation is: '";
			for (int q = 0; q < 10; q++)
			{
				cout << equation[q] << "' '";
			}
			cout << endl;

			if (isEquation) {
				for (int x = iteration-1; x > 0; x--) {
					getInstruction((string)equation[x]);
				}
				assemble("POPM", getAddr(equation[0]));
			}
			
			//reset equation values
			for (int z = 0; z < iteration; z++) {
				memset(equation[iteration], 0, sizeof(equation[iteration]));
			}
			iteration = 0;
			isEquation = false;
			cout << "CLEARED: \niteration = " << iteration << "\nisEquation = " << isEquation << "\nEquation = " ;
			for (int q = 0; q < 10; q++)
			{
				cout << equation[q] << "' '";
			}
			cout << endl;
		}
		lexer(j);
	}
	if (stackindex != 0)
		error("Closing argument not found");

	file.close();
	myfile.close();

	symbolTable();

	return 0;
}
