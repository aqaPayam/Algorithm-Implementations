#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

typedef long double Double;
typedef vector<Double> DoubleVector;
typedef vector<DoubleVector> DoubleMatrix;
typedef vector<int> IntVector;

const Double EPSILON = 1e-9;

struct LinearProgramSolver {
    int numRows, numCols;
    IntVector basicVariables, nonBasicVariables;
    DoubleMatrix tableau;

    LinearProgramSolver(const DoubleMatrix &coefficientsMatrix, const DoubleVector &constraintsVector,
                        const DoubleVector &objectiveFunction) :
            numRows(constraintsVector.size()), numCols(objectiveFunction.size()), nonBasicVariables(numCols + 1),
            basicVariables(numRows), tableau(numRows + 2, DoubleVector(numCols + 2)) {
        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numCols; j++)
                tableau[i][j] = coefficientsMatrix[i][j];

        for (int i = 0; i < numRows; i++) {
            basicVariables[i] = numCols + i;
            tableau[i][numCols] = -1;
            tableau[i][numCols + 1] = constraintsVector[i];
        }
        for (int j = 0; j < numCols; j++) {
            nonBasicVariables[j] = j;
            tableau[numRows][j] = -objectiveFunction[j];
        }
        nonBasicVariables[numCols] = -1;
        tableau[numRows + 1][numCols] = 1;
    }

    void Pivot(int r, int s) {
        double inv = 1.0 / tableau[r][s];
        for (int i = 0; i < numRows + 2; i++)
            if (i != r)
                for (int j = 0; j < numCols + 2; j++)
                    if (j != s)
                        tableau[i][j] -= tableau[r][j] * tableau[i][s] * inv;
        for (int j = 0; j < numCols + 2; j++) if (j != s) tableau[r][j] *= inv;
        for (int i = 0; i < numRows + 2; i++) if (i != r) tableau[i][s] *= -inv;
        tableau[r][s] = inv;
        swap(basicVariables[r], nonBasicVariables[s]);
    }

    bool Simplex(int phase) {
        int x = phase == 1 ? numRows + 1 : numRows;
        while (true) {
            int s = -1;
            for (int j = 0; j <= numCols; j++) {
                if (phase == 2 && nonBasicVariables[j] == -1) continue;
                if (s == -1 || tableau[x][j] < tableau[x][s] ||
                    tableau[x][j] == tableau[x][s] && nonBasicVariables[j] < nonBasicVariables[s])
                    s = j;
            }
            if (tableau[x][s] > -EPSILON) return true;
            int r = -1;
            for (int i = 0; i < numRows; i++) {
                if (tableau[i][s] < EPSILON) continue;
                if (r == -1 || tableau[i][numCols + 1] / tableau[i][s] < tableau[r][numCols + 1] / tableau[r][s] ||
                    (tableau[i][numCols + 1] / tableau[i][s]) == (tableau[r][numCols + 1] / tableau[r][s]) &&
                    basicVariables[i] < basicVariables[r])
                    r = i;
            }
            if (r == -1) return false;
            Pivot(r, s);
        }
    }

    Double Solve(DoubleVector &result) {
        int r = 0;
        for (int i = 1; i < numRows; i++) if (tableau[i][numCols + 1] < tableau[r][numCols + 1]) r = i;
        if (tableau[r][numCols + 1] < -EPSILON) {
            Pivot(r, numCols);
            if (!Simplex(1) || tableau[numRows + 1][numCols + 1] < -EPSILON) return -numeric_limits<Double>::infinity();
            for (int i = 0; i < numRows; i++)
                if (basicVariables[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= numCols; j++)
                        if (s == -1 || tableau[i][j] < tableau[i][s] ||
                            tableau[i][j] == tableau[i][s] && nonBasicVariables[j] < nonBasicVariables[s])
                            s = j;
                    Pivot(i, s);
                }
        }
        if (!Simplex(2)) return numeric_limits<Double>::infinity();
        result = DoubleVector(numCols);
        for (int i = 0; i < numRows; i++)
            if (basicVariables[i] < numCols)
                result[basicVariables[i]] = tableau[i][numCols + 1];
        return tableau[numRows][numCols + 1];
    }
};

int main() {
    int numProducts, numConstraints;
    cin >> numProducts >> numConstraints;

    DoubleMatrix coefficientsMatrix(numProducts, DoubleVector(numConstraints));
    for (int i = 0; i < numProducts; ++i) {
        for (int j = 0; j < numConstraints; ++j) {
            cin >> coefficientsMatrix[i][j];
        }
    }

    DoubleVector constraintsVector(numProducts);
    for (int i = 0; i < numProducts; ++i) {
        cin >> constraintsVector[i];
    }

    DoubleVector objectiveFunction(numConstraints);
    for (int i = 0; i < numConstraints; ++i) {
        cin >> objectiveFunction[i];
    }

    DoubleMatrix transposedMatrix(numConstraints, DoubleVector(numProducts));
    for (int i = 0; i < numProducts; ++i) {
        for (int j = 0; j < numConstraints; ++j) {
            transposedMatrix[j][i] = coefficientsMatrix[i][j];
        }
    }

    LinearProgramSolver lpSolver(transposedMatrix, objectiveFunction, constraintsVector);
    DoubleVector result;
    Double maxSales = lpSolver.Solve(result);

    cout << fixed << setprecision(3) << maxSales << endl;

    return 0;
}
