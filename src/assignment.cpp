#include <iostream>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void parsec_roi_begin() {

}

void parsec_roi_end() {

}


struct Result {
    vector<vector<int> > A;
    vector<vector<int> > B;
};

// Reads |n| number of matrices into the Result object
Result read(string filename, int n) {
    vector<vector<int> > A, B;
    Result ab;
    string line;
    ifstream infile;
    infile.open(filename.c_str());

    for (int num_read = 0; num_read < n; num_read++) {
        vector<vector<int>> temp;
        int i = 0;
        while (getline(infile, line) && !line.empty()) {
            istringstream iss(line);
            temp.resize(temp.size() + 1);
            int a, j = 0;
            while (iss >> a) {
                temp[i].push_back(a);
                j++;
            }
            i++;
        }
        if (num_read == 0) {
            A = temp;
        } else {
            B = temp;
        }
    }

    infile.close();
    ab.A = A;
    ab.B = B;
    return ab;
}

vector<vector<int> > ijkalgorithm(vector<vector<int> > A,
                                  vector<vector<int> > B) {
    int n = A.size();

    // initialise C with 0s
    vector<int> tmp(n, 0);
    vector<vector<int> > C(n, tmp);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<int>> matrix_column_copy(vector<vector<int>> src) {
    auto n = src.size();
    vector<vector<int>> dst(n, vector<int>(n, 0));
    for (auto col = 0; col != n; col++) {
        for (auto row = 0; row != n; row++) {
            dst[row][col] = src[row][col];
        }
    }
    return dst;
}

vector<int> gather(vector<vector<int>> src, vector<vector<int>> indexing_vector) {
    auto n = indexing_vector.size();
    unsigned long i = 0;
    vector<int> dst(n);
    for (auto idx: indexing_vector) {
        dst[i] = src[idx[0]][idx[1]];
        i++;
    }
    return dst;
}

vector<vector<int>> scatter(vector<vector<int>> indexing_vector, vector<int> gathered_values) {
    auto n = indexing_vector.size();
    vector<vector<int>> dst(n, vector<int>(n, 0));
    for (long i = 0; i < n; i++) {
        dst[indexing_vector[i][0]][indexing_vector[i][1]] = gathered_values[i];
    }
    return dst;
}

vector<vector<int>> transpose(vector<vector<int>> src) {
    auto n = src.size();
    vector<vector<int>> dst(n, vector<int>(n, 0));
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            dst[j][i] = src[i][j];
        }
    }
    return dst;
}

void printMatrix(vector<vector<int> > matrix) {
    vector<vector<int> >::iterator it;
    vector<int>::iterator inner;
    for (it = matrix.begin(); it != matrix.end(); it++) {
        for (inner = it->begin(); inner != it->end(); inner++) {
            cout << *inner;
            if (inner + 1 != it->end()) {
                cout << "\t";
            }
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read(filename, 2);
    parsec_roi_begin();
    //vector<vector<int> > C = ijkalgorithm(result.A, result.B);
    //vector<vector<int>> C = matrix_column_copy(result.A);
    //vector<int> C = gather(result.A, result.B);
    //vector<vector<int>> C = scatter(result.B, result.A[0]);
    vector<vector<int>> C = transpose(result.A);
    parsec_roi_end();
    printMatrix(C);
    return 0;
}
