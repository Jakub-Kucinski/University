// #include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;
const int N = 200000;

int main()
{
    ofstream outfile;
    outfile.open("test.dat");

    
    outfile << 200000 << endl;
    for (int i = 0; i < N; i++)
    {
        // write inputted data into the file.      
        outfile << i%10000 << " " << (i+1)%10000 << " " << (i+3) % 10000 << endl;
    }
    // close the opened file.
    outfile.close();

    return 0;
}