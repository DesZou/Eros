#include <bits/stdc++.h>

std::string fileName, command;
char caseId[1005];

int main(int argc, char *argv[]) {
	assert(argc >= 2);
	
	system("@echo off");
	
	fileName = std::string(argv[1]);
	system("gen_make.bat");
	
	int caseCnt;
	sscanf(argv[2], "%d", &caseCnt);
	
	for (int i = 1; i <= caseCnt; ++i) {
		sprintf(caseId, "%d", i);
		command = fileName + " " + caseId;
		system(command.c_str());
	}
	
	return 0;
}
