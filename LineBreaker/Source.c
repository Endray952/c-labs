#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
int resultStrIndex = 0;
char *getString()
{
	char *string;
	char charInput;
	int i = 0;
	printf("%s", "Enter output file name: ");
	string = (char*)malloc(1 * sizeof(char));
	while (charInput = getc(stdin), charInput != '\n')
	{
		string[i] = charInput;
		i++;
		string = realloc(string, (i + 1) * sizeof(char));
	}
	string[i] = '\0';
	return string;
}
char *readFile(int strLen) {
	FILE *dataFile;
	dataFile = fopen("test.txt", "r");
	char *text;
	text = (char*)malloc(1 * sizeof(char));
	int i = 0;
	while (EOF != (text[i] = fgetc(dataFile))) {
		i++;
		text = realloc(text, (i + 1) * sizeof(char));
	}
	text[i] = '\0';
	fclose(dataFile);
	return text;

}
void addSpaces(char *wordArray, char *resultStr, int b, int c) {
	for (int i = 0; wordArray[i] != '\0'; i++) {
		resultStr[resultStrIndex] = wordArray[i];
		resultStrIndex++;
	}
	for (int k = 0; k < b; k++) {
		resultStr[resultStrIndex] = ' ';
		resultStrIndex++;
	}
	if (c > 0) {
		resultStr[resultStrIndex] = ' ';
		resultStrIndex++;
	}
}
void carryoverStr(char *wordArray, char *resultStr, int charIndex, int spaceNumber, int * ptrOnI) {
	if (spaceNumber > 0) {
		wordArray[charIndex] = '\0';
	}
	else {
		wordArray[charIndex - 1] = '\0';
		*ptrOnI = *ptrOnI - 1;
	}
	for (int i = 0;wordArray[i] != '\0'; i++) {
		resultStr[resultStrIndex] = wordArray[i];
		resultStrIndex++;
	}
	resultStr[resultStrIndex] = '-';
	resultStrIndex++;
	resultStr[resultStrIndex] = '\n';
	resultStrIndex++;
}
int main(void) {
	char *locale = setlocale(LC_ALL, "");
	char *text; // исходная строка с текстом
	char resultStr[1000];
	char wordArray[100][100];
	int strLen;
	int strIndex = 0;
	int charIndex = 0;
	int counter = 0;
	int spaceNumber = 0;
	int spacesBetweenWords = 0;
	int extraSpace = 0;
	char *outputFileName;
	outputFileName = getString();
	printf("%s", "Enter line length: ");
	scanf("%d", &strLen);
	text = readFile(strLen); // Взять строку из файла
	printf("\n");
	printf("%s\n", "input text:");
	puts(text);
	for (int i = 0; text[i] != '\0'; i++) {
		if (text[i] != ' ') {
			wordArray[strIndex][charIndex] = text[i];
			charIndex++;
		}
		else {
			if (counter != 0) {
				wordArray[strIndex][charIndex] = '\0';
				strIndex++;
				charIndex = 0;
			}
			spaceNumber++;
		}
		counter++;
		if (counter == strLen || text[i + 1] == '\0') {		// Запихиваем в результирующую строку	
			counter = 0;
			if (strIndex == 0 && text[i + 1] != '\0' && text[i + 1] != ' ') {
				carryoverStr(wordArray[0], resultStr, charIndex, spaceNumber, &i);
			}
			else if (text[i] != ' ') {
				if (text[i + 1] != ' ') { // Если слово не вместилось в строку
					if (strIndex > 0) {
						if (text[i + 1] != '\0') {
							i -= charIndex;
							spaceNumber += charIndex;
							strIndex--;
							if (strIndex > 1) {
								spacesBetweenWords = spaceNumber / strIndex;
								extraSpace = spaceNumber % strIndex;
							}
							else {
								spacesBetweenWords = spaceNumber;
								extraSpace = 0;
							}
						}
						else {
							wordArray[strIndex][charIndex] = '\0'; // если строка вида abc_bd\0
						}
					}
					else {
						wordArray[strIndex][charIndex] = '\0'; // случай, когда строка abc\0
					}
					for (int j = 0; j <= strIndex; j++) {
						if (j == strIndex) {
							addSpaces(wordArray[j], resultStr, 0, 0);
						}
						else {
							addSpaces(wordArray[j], resultStr, spacesBetweenWords, extraSpace);
						}
						extraSpace--;
					}
					resultStr[resultStrIndex] = '\n';
					resultStrIndex++;
				}
				else {
					if (strIndex > 0) {
						spacesBetweenWords = spaceNumber / strIndex;
						extraSpace = spaceNumber % strIndex;
					}
					wordArray[strIndex][charIndex] = '\0';
					for (int j = 0; j <= strIndex; j++) {
						if (j == strIndex)
							addSpaces(wordArray[j], resultStr, 0, 0);
						else
							addSpaces(wordArray[j], resultStr, spacesBetweenWords, extraSpace);
						extraSpace--;
					}
					resultStr[resultStrIndex] = '\n';
					resultStrIndex++;
				}
			}
			else { // text[i] == ' '
				if (strIndex > 0) {
					strIndex--;
					if (strIndex != 0) {
						spacesBetweenWords = spaceNumber / strIndex;
						extraSpace = spaceNumber % strIndex;
					}
				}
				for (int j = 0; j <= strIndex; j++) {
					if (j == strIndex)
						addSpaces(wordArray[j], resultStr, 0, 0);
					else
						addSpaces(wordArray[j], resultStr, spacesBetweenWords, extraSpace);
					extraSpace--;
				}
				resultStr[resultStrIndex] = '\n';
				resultStrIndex++;
			}			
			strIndex = 0;
			charIndex = 0;
			spaceNumber = 0;
		}

	}
	resultStr[resultStrIndex] = '\0';
	printf("\n");
	printf("%s\n", "output text:");
	puts(resultStr);
	FILE * outputFIle;
	outputFIle = fopen(outputFileName, "w");
	fputs(resultStr, outputFIle);
	fclose(outputFIle);
	return 0;
}
