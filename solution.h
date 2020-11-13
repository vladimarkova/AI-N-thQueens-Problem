#include <iostream>
// #include "Queens.h"
using namespace std;

class Solution
{
private:
    // size-up to 10 000, queens[5]=3 <=> in matrix-queen on fifth column is on third row
    int size;
    int queens[50];

    public: 
    void read()
    {
        int n;
        cout << "Enter number of queens: " << endl;
        cin >> n;
        while (n == 2 || n == 3)
        {
            cout << "This problem does not have a solution. Please try with another input: " << endl; 
            cin >> n;     
        }
        size = n;
    }

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            queens[i]=i;
        }
    }

    // void print()
    // {   
    //     for (int i = 0; i < size; i++)
    //     {
    //         int counter = 0;
    //         while (counter < queens[i])
    //         {
    //             cout << '-' << endl;
    //             counter++; 
    //         }
    //         cout << '*' << endl;         
    //         while (counter < size - 1)
    //         {
    //             counter++;
    //             cout << '-' << endl;             
    //         }
    //         cout << endl << endl;
    //     }
    // }
    

      void print()
      {   
         char matrix[50][50];
         for (int i = 0; i < size; i++)
         {
             int counter = 0;
             while (counter < queens[i])
             {
                 // cout << '-' << endl;
                 matrix[i][counter] = '-';
                 counter++; 
             }
             // cout << '*' << endl; 
             matrix[i][counter] = '*';          
                while (counter < size - 1)
          {
                // cout << '-' << endl;
                 counter++;
                 matrix[i][counter] = '-';               
             }
         }
          for (int i = 0; i < size; i++)
          {
              for (int j = 0; j < size; j++)
              {
                  cout << matrix[i][j] << " ";
              }
              cout << endl;
         }
    }
};