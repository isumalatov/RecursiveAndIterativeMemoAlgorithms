#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mcp_naive(const vector<vector<int>> &matrix, int posx, int posy, int rows, int cols)
{
    if (posx == rows - 1 && posy == cols - 1)
    {
        return matrix[posx][posy];
    }
    else
    {
        int solright = mcp_naive(matrix, posx, posy + 1, rows, cols);
        int soldown = mcp_naive(matrix, posx + 1, posy, rows, cols);
        int soldiag = mcp_naive(matrix, posx + 1, posy + 1, rows, cols);
        return matrix[posx][posy] + min(solright, min(soldown, soldiag));
    }
}

int mcp_memo(const vector<vector<int>> &matrix, int posx, int posy, int rows, int cols, vector<vector<int>> &memo, vector<pair<int, int>> &path)
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
        int solright = mcp_memo(matrix, posx, posy + 1, rows, cols, memo, path);
        int soldown = mcp_memo(matrix, posx + 1, posy, rows, cols, memo, path);
        int soldiag = mcp_memo(matrix, posx + 1, posy + 1, rows, cols, memo, path);
        int minimo = matrix[posx][posy] + min(solright, min(soldown, soldiag));
        memo[posx][posy] = minimo;
        if (minimo == solright)
        {
            path.push_back({posx, posy + 1});
        }
        else if (minimo == soldown)
        {
            path.push_back({posx + 1, posy});
        }
        else
        {
            path.push_back({posx + 1, posy + 1});
        }
        return minimo;
    }
}

int mcp_it_matix()
{
    return -1;
}

int mcp_it_vector()
{
    return -1;
}

int mcp_parser()
{
    return -1;
}

int main(int argc, char *argv[])
{
    bool t = false;
    bool p2D = false;
    bool ignore_naive = false;
    if (argc < 3)
    {
        cout << "Por favor, proporciona el nombre del archivo como argumento.\n";
        return 1;
    }

    ifstream file;
    for (int i = 0; i < argc; ++i)
    {
        if (argv[i] == "-t")
        {
            t = true;
        }
        else if (argv[i] == "--p2D")
        {
            p2D = true;
        }
        else if (argv[i] == "--ignore-naive")
        {
            ignore_naive = true;
        }
        else if (argv[i] == "-f")
        {
            ifstream file(argv[i + 1]);
        }
    }

    if (!file)
    {
        cout << "No se pudo abrir el archivo.\n";
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

    vector<pair<int, int>> path;

    if (ignore_naive == true)
    {
        cout << "- ";
        cout << mcp_memo(matrix, 0, 0, rows, cols, memo, path);
    }
    else
    {
        cout << mcp_naive(matrix, 0, 0, rows, cols) << " ";
        cout << mcp_memo(matrix, 0, 0, rows, cols, memo, path);
    }

    if (mcp_it_matix() == -1)
    {
        cout << " ? ";
    }

    if (mcp_it_vector() == -1)
    {
        cout << "? ";
    }

    if (mcp_parser() == -1)
    {
        cout << "?";
    }

    if (p2D == true)
    {
        int coste = 0;
        // Create a character matrix filled with '.'
        vector<vector<char>> charMatrix(rows, vector<char>(cols, '.'));

        // Replace the points in the path with '*'
        for (const auto &p : path)
        {
            charMatrix[p.first][p.second] = '*';
        }

        // Print the character matrix
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
                if (charMatrix[i][j] == '*')
                {
                    coste += matrix[i][j];
                }
            }
        }
        cout << coste << endl;
    }

    if (t == true)
    {
        cout << "?";
    }

    file.close();
    return 0;
}