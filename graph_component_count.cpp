#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int main() {
    long long int n, B;
    cin >> n >> B;
    vector<long long int> a(n);
    for (long long int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long int dp[n][B + 1][2];

    for (long long int i = 0; i < n; ++i) {
        for (long long int j = 0; j <= B; ++j) {
            dp[i][j][0] = INF;
            dp[i][j][1] = INF;
        }
    }

    for (long long int i = 1; i < n; ++i) {
        for (long long int j = 0; j <= B; ++j) {
            //dp[0][0][0] = 0;
            dp[0][1][0] = 0;
            //dp[0][1][1] = 0;
            dp[0][0][1] = 0;

            if (j <= B && (i - j < B)) {
                if (j != 0)
                    dp[i][j][0] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + a[i]);

                if (i < B || j != 0)
                    dp[i][j][1] = (i == j) ? a[i] : min(dp[i - 1][j][0] + a[i], dp[i - 1][j][1]);
            }

        }


    }


    long long int ans = INF;
    for (long long int l = 0; l <= B; l++) {
        ans = min(ans, dp[n - 1][l][0]);
    }

    long long int ans2 = INF;
    for (long long int l = 0; l <= B; l++) {
        ans2 = min(ans, dp[n - 1][l][1]);
    }
    cout << min(ans, ans2) << endl;
    return 0;
}


