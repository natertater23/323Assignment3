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
	myfile.open("Syntax Analysis.txt", ios::out | ios::trunc);
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
string lastID = "";
string prevVar = "", nextVar = "";
char lastOp;

string instructions[1000];
int instructionLine = 1;
stack <int> s;
string delay = "";

/*for instructions that require an input for
integer value or memory location*/
void assemble(string instruction, int value) {
	if(instruction == "PUSHI"){
		cout << instructionLine << "\tPUSHI\t" << value << endl;
	}
	else if (instruction == "PUSHM") {
		cout << instructionLine << "\tPUSHM\t" << value << endl;
	}
	else if (instruction == "POPM") {
		cout << instructionLine << "\tPOPM\t" << value << endl;
	}
	else if (instruction == "JUMPZ") {
		cout << instructionLine << "\tJUMPZ\t" << value << endl;
	}
	else if (instruction == "JUMP") {
		cout << instructionLine << "\tJUMP\t" << value << endl;
	}
	else {
		error("Assembly Instruction not valid");
	}
	instructionLine++;
}


//for instructions that require no input
void assemble(string instruction) {
	if (instruction == "STDOUT") {
		cout << instructionLine << "\tSTDOUT" << endl;
	}
	else if (instruction == "STDIN") {
		cout << instructionLine << "\tSTDIN" << endl;
	}
	else if (instruction == "ADD") {
		cout << instructionLine << "\tADD" << endl;
	}
	else if (instruction == "SUB") {
		cout << instructionLine << "\tSUB" << endl;
	}
	else if (instruction == "MUL") {
		cout << instructionLine << "\tMUL" << endl;
	}
	else if (instruction == "DIV") {
		cout << instructionLine << "\tDIV" << endl;
	}
	else if (instruction == "GRT") {
		cout << instructionLine << "\tGRT" << endl;
	}
	else if (instruction == "LES") {
		cout << instructionLine << "\tLES" << endl;

	}
	else if (instruction == "EQU") {
		cout << instructionLine << "\tEQU" << endl;

	}
	else if (instruction == "NEQ") {
		cout << instructionLine << "\tNEQ" << endl;

	}
	else if (instruction == "GEQ") {
		cout << instructionLine << "\tGEQ" << endl;

	}
	else if (instruction == "LEQ") {
		cout << instructionLine << "\tLEQ" << endl;

	}
	else if (instruction == "LABEL") {
		cout << instructionLine << "\tLABEL" << endl;
	}
	else {
		error("Assembly Instruction not valid");
	}
	instructionLine++;
}

void symbolTable()
{
	cout << "\n\n\t\tSYMBOL TABLE\nIdentifier\tMemoryLocation\tType\n" ;
	
	for (int i = 0; i < idList.size(); i++) {
		cout << idList.at(i) << "\t\t" << (5000 + i) << "\t\t" << typesList.at(i) << endl;
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







string syntaxId() {
	string str, filtered;
	char operators[] = "+-*/%";
	bool rightHandSide = true, firstOfLHS = true;

	for (int i = 0; i < strlen(testCharList); i++)
	{
		if (testCharList[i] == '=')
			rightHandSide = false;
	}

	if (!rightHandSide)
	{
		for (int i = 0; i < strlen(testCharList); i++)
		{
			for (int j = 0; j < 5; j++)
				if (testCharList[i] == operators[j])
					firstOfLHS = false;
		}
		if (firstOfLHS)
			myfile << "<Expression> -> <Term> <Expression Prime>\n";
		myfile << "<Term> -> <Factor><TermPrime>\n";
		myfile << "<Factor> -> <Identifier>\n";
	}
	else
	{
		myfile << "<Statement> -> <Assign>\n";
		myfile << "<Assign> -> <Identifier> = <Expression>\n";
	}

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
	while (!found && i < idList.size()){
		if (idList.at(i) == filtered) {
			found = true;
			//cout << "found at index " << i << endl;
		}
		i++;
	}
	if (!found) {//if it doesn't exist in the list, add it
		if (prevType == "")
			error("No declaration given");
		idList.push_back(filtered);
		Memory_Address++;
		typesList.push_back(prevType);
	}
	

	if (prevVar == "") {
		//cout << "prevVar changes from " << prevVar << " to ";
		prevVar = testWord;

		//cout << prevVar;
		//cout << " because testword is " << testWord << endl;
	}
	else if (nextVar == "") {
		//cout << "nextVar changes from " << nextVar << " to ";
		nextVar = testWord;

		//cout <<  nextVar;
		//cout << " because testword is " << testWord << endl;

	}

	/*if (isblank(lastOp)) {
		for (int i = 0; i < idList.size(); i++) {
			if (idList.at(i) == nextVar)
				assemble("ADD", i);
		}
	}*/


	return str;
}





string syntaxSep() {
	//KEEP THIS CODE
	string str = " <Separator> -> ";

	char openers[5] = { "([{'" }, closers[] = { ")]}'" };
	for (int a = 0; a < 4; a++) {
		if (testChar == openers[a] && stackx[stackindex] != openers[a]) {//know testChar is a closing separator
			stackindex++;
			stackx[stackindex] = testChar;//add separator to the stack

			if (testChar == '(') {
				str += " <Condition>\n";
				str += " <Condition> -> ( <StatementList>";
			}
			else {
				str += " <OpeningSeparator> <StatementList>\n";
				str += " <OpeningSeparator> -> " + testChar;
			}
			return str;
		}
		else if (testChar == closers[a]) {//know testChar is a closing separator
			if (openers[a] == stackx[stackindex]) {
				//continue
				stackx[stackindex] = ' ';
				stackindex--;
				if (testChar == ')') {
					str += " <Condition>\n";
					str += " <Condition> -> <StatementList> )";
					str += "\n <StatementList> -> Epsilon";
				}
				else {
					str += " <StatementList> <ClosingSeparator>\n";
					str += " <ClosingSeparator> -> " + testChar;
				}
				return str;
			}
			else
				error("Closing separator incompatible");
		}
	}
	str += " <EndSeparator>\n";
	return str;
}





string syntaxKey() {
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
	if (delay != "") {//if delay is active
		assemble("PUSHI", atoi(str));

		for (int i = 0; i < idList.size(); i++) {//find memory address
			if (idList.at(i) == prevVar) {
				assemble(delay, (5000 + i));
				cout << "assembled at " << lineNum << "\n\n";

			}
		}
	}
	delay = "";
	return "";
}





string syntaxOp() {

	string str;

	lastOp = testChar;

	bool foundFirst = false;
	bool foundSecond = false;

	

	//only if operator is an = sign then delay must occur
	if (testChar == '=') {

		delay = "POPM";
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

		if (testChar == '*') {

			assemble("MULT");
		}
		else if (testChar == '/') {
			assemble("DIV");
		}
		if (testChar == '+') {
			assemble("ADD");
		}
		else if (testChar == '-') {
			assemble("SUB");
		}
	}
	

	return str;
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
			myfile << syntaxOp();
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
			myfile << syntaxSep();
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
			//cout << isprint(next) << " ";
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
			myfile << syntaxKey();
		}
		else {
			myfile << "\n\nToken:\tIDENTIFIER" << "\t\tLexme:\t" << testWord;
			if (printline)
				myfile << " at line " << lineNum;
			myfile << endl;
			if (print)
				cout << "\nToken:\tIDENTIFIER" << "\t\tLexme:\t" << testWord << endl;
			myfile << syntaxId();
		}
		flag = 0;
	}
	//cout << test << endl;

}





//-----------------------------------------------------------------------------------------


int main() {

	myfile.open("Syntax Analysis.txt");    //makes file named Syntax Analysis
	myfile << "            SYNTAX ANALYSIS" << endl;
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
