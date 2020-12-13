#include <iostream>
#include <ratio>
#include <chrono>
#include "solution.h"
using namespace std;

char response = '1';

void play()
{
    while (response != '0')
    {
        Solution solution;
        // solution.read();
        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();   

        // solution.solve();
        solution.isolatedTests();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1; 
        cout << "Time in miliseconds for execution was: " << time_span.count() << " milliseconds." << endl;     

        // solution.print(); 

        cout << "Enter 0 to stop the game or 1 to continue" << endl << endl;
        cin >> response;
    }
}