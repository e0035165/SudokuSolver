
#include <iostream>
#include <string>
#include<algorithm>
#include<functional>
#include<fstream>
#include<vector>
#include <set>
#include <queue>
#include<map>
#include <chrono>
#include <thread>

using namespace std;


// UNASSIGNED is used for empty cells in sudoku grid 
#define UNASSIGNED 0  
string ltrim(const string& str);
string rtrim(const string& str);
vector<string> split(const string& str);
// N is used for the size of Sudoku grid.  
// Size will be NxN  
#define N 9  


 // } Driver Code Ends


class Solution
{
private:
    int* p = new int;
    bool forward = true;
    vector<int>combinatorics[81];
    vector<int>empty_positions;
public:
    //Function to find a solved Sudoku. 
    bool SolveSudoku(int grid[N][N])
    {
        
        return true;
    }

    void secondSolver(int target[N][N], int pos)
    {
        if (pos >= (int)empty_positions.size())
        {
            cout << " Solved!! " << endl;
            forward = false;
            return;
        }

        auto x = combinatorics[empty_positions[pos]].begin();
        while (x != combinatorics[empty_positions[pos]].end())
        {
            if (sq_chk(target, empty_positions[pos], *x) && chk_row(target, empty_positions[pos], *x) && chk_col(target, empty_positions[pos], *x))
            {
                target[empty_positions[pos] / 9][empty_positions[pos] % 9] = *x;
                //cout << "Value set to " << *x << " for position " << empty_positions[pos] << endl;
                secondSolver(target, pos + 1);
            }
            if (forward == false)
            {
                break;
            }
            target[empty_positions[pos] / 9][empty_positions[pos] % 9] = 0;
            //cout << "Value reset to " << 0 << " for position " << empty_positions[pos] << endl;
            ++x;
        }
        return;
    }

    

    void square_comb(int grid[N][N])
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (grid[i][j] == 0) {
                    empty_positions.push_back(i * 9 + j);
                    for (int k = 1; k <= 9; ++k)
                    {
                        if (sq_chk(grid, i * 9 + j, k) && chk_row(grid, i * 9 + j, k) && chk_col(grid, i * 9 + j, k))
                        {
                            combinatorics[i * 9 + j].push_back(k);

                        }
                    }
                }
            }
        }
        
        /*for (int i = 0; i < 81; i++)
        {
            for (int j = 0; j < combinatorics[i].size(); ++j)
            {
                cout << combinatorics[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        for (auto x = empty_positions.begin(); x != empty_positions.end(); ++x)
        {
            cout << *x << " ";
        }
        cout << endl;*/
    }
    bool sq_chk(int grid[N][N], int pos, int num) {
        int i = pos / 9;
        int j = pos % 9;
        int lower_end_i = i - (i % 3);
        int upper_end_i = lower_end_i + 2;
        int lower_end_j = j - (j % 3);
        int upper_end_j = lower_end_j + 2;

        for (int x = lower_end_i; x <= upper_end_i; x++) {
            for (int y = lower_end_j; y <= upper_end_j; y++) {
                if (num == grid[x][y]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool chk_col(int grid[N][N], int pos, int num) {
        int col_no = (pos % 9);
        for (int x = 0; x < N; x++) {
            if (grid[x][col_no] == num) {
                return false;
            }
        }
        return true;
    }
    bool chk_row(int grid[N][N], int pos, int num) {
        int row_no = (pos / 9);
        for (int x = 0; x < N; x++) {
            if (grid[row_no][x] == num) {
                return false;
            }
        }
        return true;
    }
    //Function to print grids of the Sudoku.
    void printGrid(int grid[N][N])
    {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }
};

// { Driver Code Starts.

int main() {
    int t;
    fstream fout("Text.txt", ios::in | ios::out);
    int grid[N][N];
    if (fout.is_open())
    {
        
        string first_multiple_input_temp;
        getline(fout, first_multiple_input_temp);
        vector<string>numbers = split(rtrim(first_multiple_input_temp));
        //cout << numbers.size() << endl;
        for (int i=0;i<81;++i)
        {
            grid[i / 9][i % 9] = stoi(numbers[i]);
        }

        Solution sln;
        sln.square_comb(grid);
        sln.secondSolver(grid, 0);
        sln.printGrid(grid);
    }

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}