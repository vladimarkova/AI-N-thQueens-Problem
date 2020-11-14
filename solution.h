#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/* #region Variables */
// size-up to 10 000, queens[5]=3 <=> in matrix-queen on fifth column is on third row
int size;
int queens[10000];

int r[10000];
int d1[19999];
int d2[19999];

int conflicts[10000];
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

void rowCsInit()
{
    for (int i = 0; i < size; i++)
    {
        r[i] = 0;
    }

    for (int col = 0; col < size; col++)
    {
        r[queens[col]]++;
    }
}

void d1CsInit()
{
    int d1Size = 2 * size - 1;
    for (int i = 0; i < d1Size; i++)
    {
        int diff = i - size + 1; // x - y = index - size +1
        d1[i] = 0;
    }
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

    /* #region CurrentConflicts */
    // x stands for col, y for row
    int getCurrentConflicts(int x, int y)
    {
        int conflicts = 0;
        int index1 = d1Code(x, y);
        int index2 = d1Code(x, y);
        conflicts += r[y] + d1[index1] + d2[index2] - 3;

        return conflicts;
    }

    /* #endregion */

    /* #region RowOfMinCoflicts */
    // x stands for col, y for row
    int getRowMinConflicts(int x)
    {
        int minCs = getCurrentConflicts(x, 0);
        int tmpCs = 0;
        int minCsRow = 0;
        conflicts[0] = minCs;
        for (int row = 1; row < size; row++)
        {
            tmpCs = getCurrentConflicts(x, row);
            conflicts[row] = tmpCs; 
            if (tmpCs < minCs)
            {
                minCs = tmpCs;
            }
        }
        int counter = 0;
        for (int row = 0; row < size; row++)
        {
            if (conflicts[row] == minCs)
            {
                if (row != 0)
                {
                    counter++;
                }              
                candidates[counter] = row;              
            }
        }
        int numberOfRowCandidates = counter + 1;
        minCsRow = random_element(numberOfRowCandidates);

        return minCsRow;
    }
    /* #endregion */

    /* #region ReplaceAndUpdate */
    // x stands for col, y for row
    void replaceAndUpdate(int x, int y, int newRow)
    {
        int index1 = d1Code(x, y);
        int index2 = d2Code(x, y);
        queens[x] = newRow;
        r[y]--;
        d1[index1]--;
        d2[index2]--;
    }
    /* #endregion */

    /* #region Init */
    void init()
    {
        queens[0] = rand() % size;
        for (int col = 1; col < size; col++)
        {
            queens[col] = 0;
            int conflicts = getCurrentConflicts(col, queens[col]);
            if (conflicts != 0)
            {
                int minRow = getRowMinConflicts(col);
                if (minRow != queens[col])
                {
                    replaceAndUpdate(col, queens[col], minRow);
                }
            }
        }
    }
    /* #endregion */

    /* #region ColOfMaxConflicts */
    int getColMaxConflicts()
    {
        int maxCs = getCurrentConflicts(0, queens[0]);
        int tmpCs = 0;
        int maxCsCol = 0;

        conflicts[0] = maxCs;
        for (int col = 1; col < size; col++)
        {
            tmpCs = getCurrentConflicts(col, queens[col]);
            conflicts[col] = tmpCs;
            if (tmpCs > maxCs)
            {
                maxCs = tmpCs;
                // maxCsCol = col;
            }
        }
        int counter = 0;
        for (int col = 0; col < size; col++)
        {
            if (conflicts[col] == maxCs)
            {
                if (col != 0)
                {
                    counter++;
                }
                candidates[counter] = col;
            }          
        }
        int numberOfColCandidates = counter + 1;
        maxCsCol = random_element(numberOfColCandidates);
        
        return maxCsCol;
    }
    /* #endregion */

    /* #region MinMaxConflictOptimization */
    bool minMaxConflictOpt()
    {
        bool noConflicts = false;
        int maxCol = getColMaxConflicts();
        int conflicts = getCurrentConflicts(maxCol, queens[maxCol]);
        if (conflicts == 0)
        {
            noConflicts = true;
        }
        else
        {
            int minRow = getRowMinConflicts(maxCol);
            if (minRow != queens[maxCol])
            {
                replaceAndUpdate(maxCol, queens[maxCol], minRow);
            }
        }
        return noConflicts;
    }
    /* #endregion */

    /* #region Solve */
    void solve()
    {
        init();
        bool noConflicts = minMaxConflictOpt();
        int i = 0;
        while (!noConflicts && i < 2 * size)
        {
            noConflicts = minMaxConflictOpt();
            i++;
        }
    }
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
};
/* #endregion */