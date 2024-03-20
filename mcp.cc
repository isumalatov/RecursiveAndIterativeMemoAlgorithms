#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mcp_naive(const vector<vector<int>>& matrix,int posx, int posy, int rows, int cols){
    if(posx == rows-1 && posy == cols-1){
        return matrix[posx][posy];
    }
    else{
        int solright = mcp_naive(matrix, posx, posy+1, rows, cols);
        int soldown = mcp_naive(matrix, posx+1, posy, rows, cols);
        int soldiag = mcp_naive(matrix, posx+1, posy+1, rows, cols);
        return matrix[posx][posy] + min(solright, min(soldown, soldiag));
    }
}

int mcp_memo(const vector<vector<int>>& matrix, int posx, int posy, int rows, int cols, vector<vector<int>>& memo){
    if(posx == rows-1 && posy == cols-1){
        return matrix[posx][posy];
    }
    else{
        if(memo[posx][posy] == -1){
            int solright = mcp_memo(matrix, posx, posy+1, rows, cols, memo);
            int soldown = mcp_memo(matrix, posx+1, posy, rows, cols, memo);
            int soldiag = mcp_memo(matrix, posx+1, posy+1, rows, cols, memo);
            memo[posx][posy] = matrix[posx][posy] + min(solright, min(soldown, soldiag));
        }
        else{
            return memo[posx][posy];
        }
    }
}

int main(int argc, char* argv[]) {
    bool t = false;
    bool p2D = false;
    bool ignore_naive = false;
    if (argc < 3) {
        cout << "Por favor, proporciona el nombre del archivo como argumento.\n";
        return 1;
    }

    ifstream file(argv[2]);
    if (!file) {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }

    int rows, cols;
    file >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    vector<vector<int>> memo(rows, vector<int>(cols, -1));

    for(int i = 0; i<6 ; i++)
    {
        if(argv[i] == "-t")
        {
            t = true;
        }
        else if(argv[i] == "--p2D")
        {
            p2D = true;
        }
        else if(argv[i] == "--ignore-naive")
        {
            ignore_naive = true;
        }
    }
    
    cout << mcp_naive(matrix, 0, 0, rows, cols) << endl;
    cout << mcp_memo(matrix, 0, 0, rows, cols, memo) << endl;

    file.close();
    return 0;
}