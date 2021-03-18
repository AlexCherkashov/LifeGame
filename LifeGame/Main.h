#pragma once
enum Run {
	Life = 1,
	Exit
};
enum Input {
	InputFromConsole = 1,
	InputFromFile,
	InputRandom
};

void RunProgram();
void BeginOfProcess();