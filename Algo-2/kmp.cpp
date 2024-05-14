#include<iostream>
#include<vector>
using namespace std;

void computeLPSarray(const string &pattern, vector<int> &lps) {
    int patternlen = pattern.length();
    int j = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < patternlen) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(const string &txt, const string &pattern) {
    int textlen = txt.length();
    int patternlen = pattern.length();
    vector<int> lps(patternlen, 0);
    computeLPSarray(pattern, lps);
    int i = 0, j = 0;
    while (i < textlen) {
        if (pattern[j] == txt[i]) {
            i++;
            j++;
        }
        if (j == patternlen) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < textlen && pattern[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    string txt, pattern;
    cout << "Enter the text: ";
    cin >> txt;
    cout << "Enter the pattern to search: ";
    cin >> pattern;
    KMPSearch(txt, pattern);
    return 0;
}