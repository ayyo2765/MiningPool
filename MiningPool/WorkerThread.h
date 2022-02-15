#pragma once


#include <vector>
#include <string>
#include <thread>
#include <sstream>
#include <algorithm>
#include <iterator>

#ifdef _WIN32
#include <windows.h>
#endif

#include "json.hpp"

#include "Global.h"
#include "hex.h"
#include "sha256.h"
#include "difficulty.h"
#include "endian.h"

using namespace std;

using json = nlohmann::json;

class WorkerThread
{

	int socketError;
	int authDone;
	int lastBlockHeightSent;
	int difficulty;
	int extraNonce;

	mutex lockProgram;
	vector<string> vProgram;

	unsigned char nativeTarget[32];

	int submitShareCount;

	void sendDifficulty(int clientSocket);
	void sendExtraNonce(int clientSocket);
	void sendMiningWallet(int clientSocket, Settings* settings);
	void sendCurrentBlock(int clientSocket, Global* global);
	void sendBlockStatus(int clientSocket, Settings* settings, string status);

	void sendString(int clientSocket, string data);
	string calcHash(string data);

public:
	void clientWorker(int clientSocket, Global* global);
	void blockUpdateThread(int clientSocket, Global* global);

};
