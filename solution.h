#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/* #region Variables */
// size-up to 10 000, queens[5]=3 <=> in matrix-queen on fifth column is on third row
int size;
int queens[10000];

int row_conflicts[10000];
int d1_conflcits[19999];
int d2_conflcits[19999];

int candidates[10000];
/* #endregion */

/* #region Helpers */
int random_element(int number_of_candidates)
{
    return candidates[rand() % number_of_candidates];
}

int d1Code(int x, int y)
{
    return (x - y + size - 1);
}

int d2Code(int x, int y)
{
    return (x + y);
}
/* #endregion */

/* #region ClassSolution */
class Solution
{
public:
    /* #region Read */
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
    /* #endregion */

    /* #region Init */
    // void init()
    // {
    //     queens[0] = rand() % size;
    //     for (int col = 1; col < size; col++)
    //     {
    //         queens[col] = 0;
    //         int conflicts = getCurrentCnflicts(col, queens[col]);
    //         if (conflicts != 0)
    //         {
    //             int min = getRowMinConflicts(col);
    //             if (min != queens[col])
    //             {
    //                 replace(col, queens[col], min);
    //             }
    //         }
    //     }
    // }
    /* #endregion */

    /* #region Print */

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
    /* #endregion */

    /* #region CurrentConflicts */
    // x stands for col, y for row
    int getCurrentConflicts(int x, int y)
    {
        int conflicts = 0;
        int index1 = d1Code(x, y);
        int index2 = d1Code(x, y);
        conflicts += r[y] + d1[index1] + d2[index2];

        return conflicts;
    }

    /* #endregion */

    /* #region RowOfMinCoflicts */
    // x stands for col, y for row
    int getRowMinConflicts(int x)
    {
        int min = getCurrentConflicts(x, 0);
        int tmpCs = 0;
        int minCsRow = 0;
        for (int row = 1; row < size; row++)
        {
            tmpCs = getCurrentConflicts(x, row);
            if (tmpCs < min)
            {
                min = tmpCs;
                minCsRow = row;
            }
        }
        return minCsRow;
    }
    /* #endregion */

    /* #region Replace */
    // x stands for col, y for row
    void replace(int x, int y, int newRow)
    {
        int index1 = d1Code(x, y);
        int index2 = d2Code(x, y);
        queens[x] = newRow;
        r[y]--;
        d1[index1]--;
        d2[index2]--;
    }
    /* #endregion */

    /* #region ColOfMaxConflicts */
    int getColMaxConflicts()
    {
        int max = getCurrentConflicts(0, queens[0]);
        int tmpCs = 0;
        int maxCsCol = 0;

        for (int col = 1; col < size; col++)
        {
            tmpCs = getCurrentConflicts(col, queens[col]);
            if (tmpCs > max)
            {
                max = tmpCs;
                maxCsCol = col;
            }
        }

        return maxCsCol;
    }
    /* #endregion */
};
/* #endregion */