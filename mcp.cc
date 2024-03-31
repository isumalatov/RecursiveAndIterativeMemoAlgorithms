//Ilyas Umalatov X7278165E
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int mcp_naive(const vector<vector<int>> &matrix, int posx, int posy, int rows, int cols)
{
    if (posx == rows - 1 && posy == cols - 1)
    {
        return matrix[posx][posy];
    }
    else
    {
        int solright = INT_MAX;
        int soldown = INT_MAX;
        int soldiag = INT_MAX;

        if (posy + 1 < cols)
        {
            solright = mcp_naive(matrix, posx, posy + 1, rows, cols);
        }
        if (posx + 1 < rows)
        {
            soldown = mcp_naive(matrix, posx + 1, posy, rows, cols);
        }
        if (posx + 1 < rows && posy + 1 < cols)
        {
            soldiag = mcp_naive(matrix, posx + 1, posy + 1, rows, cols);
        }

        return matrix[posx][posy] + min(solright, min(soldown, soldiag));
    }
}

int mcp_memo(const vector<vector<int>> &matrix, int posx, int posy, int rows, int cols, vector<vector<int>> &memo)
{
    if (posx == rows - 1 && posy == cols - 1)
    {
        return matrix[posx][posy];
    }
    else if (memo[posx][posy] != -1)
    {
        return memo[posx][posy];
    }
    else
    {
        int solright = INT_MAX;
        int soldown = INT_MAX;
        int soldiag = INT_MAX;

        if (posy + 1 < cols)
        {
            solright = mcp_memo(matrix, posx, posy + 1, rows, cols, memo);
        }
        if (posx + 1 < rows)
        {
            soldown = mcp_memo(matrix, posx + 1, posy, rows, cols, memo);
        }
        if (posx + 1 < rows && posy + 1 < cols)
        {
            soldiag = mcp_memo(matrix, posx + 1, posy + 1, rows, cols, memo);
        }

        int minimo = matrix[posx][posy] + min(solright, min(soldown, soldiag));
        memo[posx][posy] = minimo;

        return minimo;
    }
}

vector<pair<int, int>> reconstruct_path(const vector<vector<int>> &memo, int rows, int cols) {
    vector<pair<int, int>> path;
    int x = 0, y = 0;

    while (x < rows - 1 || y < cols - 1) {
        path.push_back({x, y});

        if (x + 1 < rows && y + 1 < cols) {
            if (memo[x + 1][y] < memo[x][y + 1] && memo[x + 1][y] < memo[x + 1][y + 1]) {
                x++;
            } else if (memo[x][y + 1] < memo[x + 1][y + 1]) {
                y++;
            } else {
                x++;
                y++;
            }
        } else if (x + 1 < rows) {
            x++;
        } else {
            y++;
        }
    }

    path.push_back({rows - 1, cols - 1});
    return path;
}

int mcp_it_matix(const vector<vector<int>> &matrix, int rows, int cols, vector<vector<int>> &memo)
{
    for (int i = rows - 1; i >= 0; --i)
    {
        for (int j = cols - 1; j >= 0; --j)
        {
            if (i == rows - 1 && j == cols - 1)
            {
                memo[i][j] = matrix[i][j];
            }
            else
            {
                int solright = INT_MAX;
                int soldown = INT_MAX;
                int soldiag = INT_MAX;

                if (j + 1 < cols)
                {
                    solright = memo[i][j + 1];
                }
                if (i + 1 < rows)
                {
                    soldown = memo[i + 1][j];
                }
                if (i + 1 < rows && j + 1 < cols)
                {
                    soldiag = memo[i + 1][j + 1];
                }

                memo[i][j] = matrix[i][j] + min(solright, min(soldown, soldiag));
            }
        }
    }

    return memo[0][0];
}

int mcp_it_vector(const vector<vector<int>> &matrix, int rows, int cols)
{
    vector<int> prev(cols, INT_MAX);
    vector<int> curr(cols, INT_MAX);

    for (int i = rows - 1; i >= 0; --i)
    {
        for (int j = cols - 1; j >= 0; --j)
        {
            if (i == rows - 1 && j == cols - 1)
            {
                curr[j] = matrix[i][j];
            }
            else
            {
                int solright = INT_MAX;
                int soldown = INT_MAX;
                int soldiag = INT_MAX;

                if (j + 1 < cols)
                {
                    solright = curr[j + 1];
                }
                if (i + 1 < rows)
                {
                    soldown = prev[j];
                }
                if (i + 1 < rows && j + 1 < cols)
                {
                    soldiag = prev[j + 1];
                }

                curr[j] = matrix[i][j] + min(solright, min(soldown, soldiag));
            }
        }
        swap(prev, curr);
    }

    return prev[0];
}

void mcp_parser(int rows, int cols, const vector<vector<int>> &matrix, const vector<vector<int>> &memo)
{
    int coste = 0;
    vector<vector<char>> charMatrix(rows, vector<char>(cols, '.'));

    vector<pair<int, int>> path = reconstruct_path(memo, rows, cols);

    for (int i = 0; i < path.size(); ++i)
    {
        charMatrix[path[i].first][path[i].second] = 'x';
    }


    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << charMatrix[i][j];
        }
        cout << '\n';
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (charMatrix[i][j] == 'x')
            {
                coste += matrix[i][j];
            }
        }
    }
    cout << coste << endl;
}

int main(int argc, char *argv[])
{
    bool t = false;
    bool p2D = false;
    bool ignore_naive = false;
    if (argc < 3)
    {
        cerr << "ERROR: missing filename.\nUsage:\nmcp [--p2D] [-t] [--ignore-naive] -f file" << endl;
        return 1;
    }

    ifstream file;
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i]; // Convert to std::string
        if (arg == "-t")
        {
            t = true;
        }
        else if (arg == "--p2D")
        {
            p2D = true;
        }
        else if (arg == "--ignore-naive")
        {
            ignore_naive = true;
        }
        else if (arg == "-f")
        {
            file.open(argv[i + 1]);
            i++;
        }
        else
        {
            cerr << "ERROR: unknown option " << arg << ".\nUsage:\nmcp [--p2D] [-t] [--ignore-naive] -f file" << endl;
            return 1;
        }
    }

    if (!file)
    {
        cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            file >> matrix[i][j];
        }
    }

    vector<vector<int>> memo(rows, vector<int>(cols, -1));
    vector<vector<int>> memo2(rows, vector<int>(cols, -1));

    if (ignore_naive == true)
    {
        cout << "- ";
        cout << mcp_memo(matrix, 0, 0, rows, cols, memo) << " ";
        cout << mcp_it_matix(matrix, rows, cols, memo2) << " ";
        cout << mcp_it_vector(matrix, rows, cols) << endl;
    }
    else
    {
        cout << mcp_naive(matrix, 0, 0, rows, cols) << " ";
        cout << mcp_memo(matrix, 0, 0, rows, cols, memo) << " ";
        cout << mcp_it_matix(matrix, rows, cols, memo2) << " ";
        cout << mcp_it_vector(matrix, rows, cols) << endl;
    }

    if (p2D == true)
    {
        mcp_parser(rows, cols, matrix, memo);
    }

    if (t == true)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << memo2[i][j] << " ";
            }
            cout << endl;
        }
    }

    file.close();
    return 0;
}