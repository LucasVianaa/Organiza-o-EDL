#include "time.h"
#include "stdlib.h"
#include "fstream"
#include "iostream"
#include "string.h"

using namespace std;

int main(int argc, char const *argv[]){
    srand(time(NULL));
    ofstream outFile("dadosTeste.txt");
    for (int i = 0; i < 4000; ++i)
    {
        outFile << to_string((rand() % 50000)) << endl;
    }

    return 0;
}
