#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/* #region Constants */
const int MAX_NUMBER_OF_QUEENS = 10000;
const int MAX_NUMBER_OF_DIAGONALS = (2 * MAX_NUMBER_OF_QUEENS) - 1; 
const int INF = 100000000; 
const int MAX_PRINTING_SIZE = 50;  
/* #endregion */

/* #region Variables */
// size-up to 10 000, queens[5]=3 <=> in matrix-queen on fifth column is on third row
int size;
int queens[MAX_NUMBER_OF_QUEENS];

int r[MAX_NUMBER_OF_QUEENS];
int d1[MAX_NUMBER_OF_DIAGONALS];
int d2[MAX_NUMBER_OF_DIAGONALS];

int conflicts[MAX_NUMBER_OF_QUEENS];
int candidates[MAX_NUMBER_OF_QUEENS];

int MAX_ITERATIONS = 2 * size;
int DIAGONALS_NUMBER = (2 * size) - 1;
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

// r[queens[col]]++;
// // index = x - y + size - 1
// d1[d1Code(col, queens[col])]++;
// // index = x + y
// d2[d2Code(col, queens[col])]++;

void rowCsInit()
{
    for (int i = 0; i < size; i++)
    {
        r[i] = 0;
    }
}

void d1CsInit()
{
    int d1Size = 2 * size - 1;

    for (int i = 0; i < d1Size; i++)
    {
        d1[i] = 0;
    }
}

void d2CsInit()
{
    int d2Size = 2 * size - 1;

    for (int i = 0; i < d2Size; i++)
    {
        d2[i] = 0;
    }
}

void conflictsInit()
{
    rowCsInit();
    d1CsInit();
    d2CsInit();
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

    /* #region Initial Update for r, d1,d2 */
    void initialUpdate(int col)
    {
        int index1 = d1Code(col, queens[col]);
        int index2 = d2Code(col, queens[col]);
        r[queens[col]]++;
        d1[index1]++;
        d2[index2]++;
    }
    /* #endregion */

    /* #region CurrentConflicts */
    // x stands for col, y for row
    // +1, if we have no queen?
    int getCurrentConflicts(int x, int y)
    {
        int conflicts = 0;
        int index1 = d1Code(x, y);
        int index2 = d2Code(x, y);
        conflicts += r[y] + d1[index1] + d2[index2] - 3;

        return conflicts;
    }

    int getPotentionalConflicts(int x, int y)
    {
        int conflicts = 0;
        int index1 = d1Code(x, y);
        int index2 = d2Code(x, y);
        conflicts += r[y] + d1[index1] + d2[index2];

        return conflicts;
    }

    int getBoardConflicts() {
        int allRConflicts = 0;
        int allD1Conflicts = 0;
        int allD2Conflicts = 0;
        for (int i = 0; i < MAX_NUMBER_OF_QUEENS; i++) {
            allRConflicts += r[i];
        }
        cout << "All row conflicts: " << allRConflicts << endl;
        for (int i = 0; i < MAX_NUMBER_OF_DIAGONALS; i++) {
            allD1Conflicts += d1[i];
            allD2Conflicts += d2[i]; 
        }
        cout << "All d1 cs: " << allD1Conflicts << endl;
        cout << "All d2 cs: " << allD2Conflicts << endl;
        return 42;
    }
    /* #endregion */

    /* #region RowOfMinCoflicts */
    // x stands for col, y for row
    int getRowMinConflicts(int x)
    {
        int startRow = queens[x];
        int startConflicts = getCurrentConflicts(x, queens[x]);
        int minCs = INF;
        int tmpCs = 0;
        int minCsRow = startRow;
        for (int row = 0; row < size; row++)
        {
            if (row != startRow) {
                tmpCs = getCurrentConflicts(x, row) + 3;
            } 
            else {
                tmpCs = getCurrentConflicts(x, row);
            }
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
                candidates[counter] = row;
                counter++;
            }
        }
        int numberOfRowCandidates = counter;
        minCsRow = random_element(numberOfRowCandidates);

        if (minCs == startConflicts) {
            minCsRow = startRow;
        }

        return minCsRow;
    }
    /* #endregion */

    /* #region ReplaceAndUpdate */
    // x stands for col, y for row
    void replaceAndUpdate(int x, int y, int newRow)
    {
        int oldIndex1 = d1Code(x, y);
        int oldIndex2 = d2Code(x, y);
        int newIndex1 = d1Code(x, newRow);
        int newIndex2 = d2Code(x, newRow);
        queens[x] = newRow;
        r[y]--;
        d1[oldIndex1]--;
        d2[oldIndex2]--;
        r[newRow]++;
        d1[newIndex1]++;
        d2[newIndex2]++;
    }
    /* #endregion */

    /* #region Init */
    void init()
    {
        for (int col = 0; col < size; col++)
        {
            queens[col] = rand() % size;
            initialUpdate(col);
            cout << col << ": " << queens[col] << endl;
            int conflicts = getCurrentConflicts(col, queens[col]);
            cout << "firstCs: " << conflicts << endl;
            if (conflicts != 0)
            {
                int minRow = getRowMinConflicts(col);
                if (minRow != queens[col])
                {
                    replaceAndUpdate(col, queens[col], minRow);
                }
            }
            cout << col << " newRow: " << queens[col] << endl;
            conflicts = getCurrentConflicts(col, queens[col]);
            cout << "secondCs: " << conflicts << endl;
        }
    }
    /* #endregion */

    /* #region ColOfMaxConflicts */
    int getColMaxConflicts()
    {
        int maxCs = -INF;
        int tmpCs = 0;
        int maxCsCol = 0;

        for (int col = 0; col < size; col++) 
        {
            tmpCs = getCurrentConflicts(col, queens[col]);
            conflicts[col] = tmpCs;
            if (tmpCs > maxCs)
            {
                maxCs = tmpCs;
            }
        }
        int counter = 0;
        for (int col = 0; col < size; col++)
        {
            if (conflicts[col] == maxCs)
            {
                candidates[counter] = col;
                counter++;
            }
        }
        int numberOfColCandidates = counter;
        maxCsCol = random_element(numberOfColCandidates);

        return maxCsCol;
    }
    /* #endregion */

    /* #region MinMaxConflictOptimization */
    bool minMaxConflictOpt()
    {
        bool noConflicts = false;
        int maxCol = getColMaxConflicts();
        cout << "Col of max cs: " << maxCol << endl;
        int conflicts = getCurrentConflicts(maxCol, queens[maxCol]);
        cout << "Cs in maxCol: " << conflicts << endl;
        if (conflicts == 0)
        {
            cout << "NO CONFLICTS!" << endl << endl;
            noConflicts = true;
        }
        else
        {
            cout << "INTERESTING PART, REPLACEMENTS AND UPDATES STARTED!" << endl << endl;
            int minRow = getRowMinConflicts(maxCol);
            cout << "Min Row discovered: " << minRow << endl << endl;
            // is it true?
            if (minRow != queens[maxCol])
            {
                cout << "Min Row different from our row!" << endl << endl; 
                cout << "old position: " << queens[maxCol] << endl;
                replaceAndUpdate(maxCol, queens[maxCol], minRow);
                cout << "new position: " << queens[maxCol] << endl; 
            }
            conflicts = getCurrentConflicts(maxCol, queens[maxCol]);  
            cout << "Conflicts in maxCol after replace and update (potentional): " << conflicts << endl << endl;      
        }
        cout << "d2[what we need] = " << d2[d2Code(maxCol, queens[maxCol])] << endl << endl;
        return noConflicts;
    }
    /* #endregion */

    /* #region Solve */
    void solve()
    {
        conflictsInit();
        init();
        bool noConflicts = minMaxConflictOpt();
        int i = 0;
        while (!noConflicts && i < MAX_ITERATIONS)
        {
            noConflicts = minMaxConflictOpt();
            i++;
        }
    }
    /* #endregion */

    /* #region Print */

    void print()
    {
        char matrix[MAX_PRINTING_SIZE][MAX_PRINTING_SIZE]; 
        for (int i = 0; i < size; i++)
        {
            int counter = 0;
            while (counter < queens[i])
            {
                matrix[counter][i] = '-';
                counter++;
            }
            matrix[counter][i] = '*';
            while (counter < size - 1)
            {
                counter++;
                matrix[counter][i] = '-';
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
        cout << endl;
    }
/* #endregion */

    /* #region Isolated Tests */
    void printCsArrays() {
        cout << "R" << endl;
        for (int i = 0; i < MAX_NUMBER_OF_QUEENS / 1000; i++) {
            cout << r[i] << " ";
        }
        cout << endl;

        cout << "D1" << endl;
        for (int i = 0; i < MAX_NUMBER_OF_QUEENS / 1000; i++) {
            cout << d1[i] << " ";
        }
        cout << endl;

        cout << "D2" << endl;
        for (int i = 0; i < MAX_NUMBER_OF_QUEENS / 1000; i++) {
            cout << d2[i] << " ";
        }
        cout << endl;
    }

    void isolatedTests() {
        conflictsInit();
        init();
        print();
        minMaxConflictOpt();
        // cout << "All conflicts in board: " << getBoardConflicts() - (size * 3) << endl << endl; 
        // cout << "d2[6]" << d2[6] << endl << endl;
    }
    /* #endregion */
};
/* #endregion */