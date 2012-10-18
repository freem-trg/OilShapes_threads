#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;


const string MAP   = "101110000101100000110000001010110111";
const int BLOCK    = 3;
const int THREADS  = MAP.length() / BLOCK;


//Thread function: looks for oil in the block and write result in results[]:
void look(string str, int tid, int* results) {
    int res = 0;
    for ( unsigned int i = 0; i < str.length(); i++ ){
        res += atoi( str.substr(BLOCK-i-1,1).c_str() ) * pow(2,i);
    }
    results[tid] = res;
    cout << tid << " " << str << " " << res << endl;
}


int main() {
    //Create vector of threads:
    vector <thread> threads;
    //Create array for threads results:
    int* results;
    results = new int[THREADS];

    //Create threads and fill results:
    for( int block = 0; block < THREADS; block++){
        string str = MAP.substr(block*BLOCK, BLOCK);
        threads.push_back(std::thread(&look, str, block, results));
    }

    //Join created threads to main thread:
    for(auto &t : threads){
        t.join();
    }

    //Show results[]:
    for ( int block = 0; block < THREADS; block++ ){
        cout << "result: " << results[block] << endl;
    }

    //Calculate the number of oil spots:


    //Delete dynamic array:
    delete results;

    return 0;
}
