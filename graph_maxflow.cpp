#include <iostream>
#include <vector>
#include <string>

#define HASH_BASE 17
#define MOD 1000000007

using namespace std;

unsigned long long modPow(unsigned long long base, unsigned long long exponent) {
    unsigned long long result = 1;
    while (exponent > 0) {
        if (exponent % 2) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return result;
}

unsigned long long modInverse(unsigned long long n) {
    return modPow(n, MOD - 2);
}

void computeHashes(const string &str, vector<unsigned long long> &prefixHash, vector<unsigned long long> &suffixHash,
                   const vector<unsigned long long> &hashPowers) {
    int length = str.length();
    prefixHash[0] = 0;
    suffixHash[0] = 0;
    prefixHash[1] = str[0];
    suffixHash[1] = str[length - 1];

    for (int i = 2; i <= length; i++) {
        prefixHash[i] = (prefixHash[i - 1] + (str[i - 1] * hashPowers[i - 1]) % MOD) % MOD;
        suffixHash[i] = (suffixHash[i - 1] + (str[length - i] * hashPowers[i - 1]) % MOD) % MOD;
    }
}

bool isHashPalindrome(const string &str, int left, int right,
                      const vector<unsigned long long> &prefixHash,
                      const vector<unsigned long long> &suffixHash,
                      const vector<unsigned long long> &hashPowers) {
    unsigned long long forwardHash = (prefixHash[right + 1] - prefixHash[left] + MOD) % MOD * modInverse(hashPowers[left]) % MOD;
    unsigned long long reverseHash = (suffixHash[str.length() - left] - suffixHash[str.length() - right - 1] + MOD) % MOD
                                     * modInverse(hashPowers[str.length() - right - 1]) % MOD;

    return forwardHash == reverseHash;
}

void computeHashPowers(vector<unsigned long long> &hashPowers, int n) {
    hashPowers[0] = 1;
    for (int i = 1; i <= n; i++) {
        hashPowers[i] = (hashPowers[i - 1] * HASH_BASE) % MOD;
    }
}

int palindromeDegree(const string &str, int left, int right,
                     const vector<unsigned long long> &prefixHash,
                     const vector<unsigned long long> &suffixHash,
                     const vector<unsigned long long> &hashPowers) {
    int degree = 0;
    while (left <= right) {
        if (left == right) {
            degree++;
            break;
        }
        int span = (right - left + 1) / 2;
        int middle = left + span - 1;
        if (isHashPalindrome(str, left, right, prefixHash, suffixHash, hashPowers)) {
            degree++;
            right = middle;
        } else {
            break;
        }
    }
    return degree;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string str;
    cin >> str;

    int queryCount;
    cin >> queryCount;

    vector<unsigned long long> hashPowers(str.length() + 1), prefixHash(str.length() + 1), suffixHash(str.length() + 1);

    computeHashPowers(hashPowers, str.length());
    computeHashes(str, prefixHash, suffixHash, hashPowers);

    for (int i = 0; i < queryCount; ++i) {
        int startIndex, endIndex;
        cin >> startIndex >> endIndex;
        cout << palindromeDegree(str, startIndex - 1, endIndex - 1, prefixHash, suffixHash, hashPowers) << '\n';
    }

    return 0;
}
