#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;


//const string MAP   = "101110000101100000110000001010110111";
const string MAP   = "111100010111000000000111111111110111";
const int BLOCK    = 2;
const int THREADS  = MAP.length() / BLOCK;
const int COLS     = 6;
const int ROWS     = THREADS / COLS;


//Thread function: looks for oil in the block and write result in results[]:
void look(string str, int tid, int* results) {
    int res = 0;
    for ( unsigned int i = 0; i < str.length(); i++ ){
        res += atoi( str.substr(BLOCK-i-1,1).c_str() ) * pow(2,i);
    }
    results[tid] = res;
    //    cout << tid << " " << str << " " << res << endl;
}

int at(int* res, int row, int col){
    return res[row*COLS + col];
}


int main() {
    //Create vector of threads:
    vector <thread> threads;
    //Create array for threads results:
    int* results;
    results = new int[THREADS];
    //Create cost array:
    int cost[4] = {0,1,1,2};
    int count[4] = {0,0,0,0};
    int max_spots = 0;

    //Create threads and fill results:
    for( int block = 0; block < THREADS; block++){
        string str = MAP.substr(block*BLOCK, BLOCK);
        threads.push_back(std::thread(&look, str, block, results));
    }

    //Join created threads to main thread:
    for(auto &t : threads){
        t.join();
    }

    //Show results and calculate max number of spots:
    for ( int i = 0; i <  ROWS; i++){
        for ( int j = 0; j < COLS; j++ ){
            cout<< " " << at(results, i, j);
            max_spots += cost[at(results, i, j)];
            count[at(results, i, j)]++;
        }
        cout << endl;
    }

    //    for ( int i = 0; i < 4; i++ ){
    //        cout << i << "'s :" << count[i] << endl;
    //    }


    //Remove one of two equal spots in col:
    cout << endl << "max spots: " << max_spots << endl;
    for ( int i = 0; i < COLS; i++ ){
        for ( int j = ROWS-1; j > 0; j-- ){
            if ( at(results, j, i) == at( results, j-1, i ) ) {
                cout << " max_spots -= " << cost[at( results, j, i )] << endl;
                max_spots -= cost[at( results, j, i )];
                count[at( results, j, i )]--;
                results[(j)*COLS + i] = 0;
            }
        }
    }


    cout << endl << "max spots: " << max_spots << endl;
    for ( int i = 0; i <  ROWS; i++){
        for ( int j = 0; j < COLS; j++ ){
            cout<< " " << at(results, i, j);
        }
        cout << endl;
    }

    //Remove spots in row:
    for ( int i = 0; i < ROWS; i++ ){
        for ( int j = 0; j < COLS-1; j++ ){
            if ( ( at( results, i, j ) == 1 || at( results, i, j ) == 3 )
                 && ( at( results, i, j + 1 ) == 2 || at( results, i, j + 1 ) == 3 )) {
                max_spots -= cost[at( results, i, j + 1 )];
                count[at( results, i, j + 1 )]--;
            }
        }
    }

    for ( int i = 0; i < 4; i++ ){
        cout << i << "'s :" << count[i] << endl;
    }

    max_spots -= count[3];

    cout << endl << "max: " << max_spots << endl;

    //Delete dynamic array:
    delete results;

    return 0;
}
