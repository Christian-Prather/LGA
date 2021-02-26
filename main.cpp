#include <string>
#include <sstream>
using namespace std;

#include "cfg.h"

int main(int argc, char* argv[]) {
    string inputFile;
	istringstream(argv[1]) >> inputFile;

    CFG cfg = ReadFile(inputFile);
    PrintCFG(cfg);

    return 0;
}