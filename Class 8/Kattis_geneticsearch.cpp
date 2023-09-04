//
// Created by barbe on 30/05/2023.
//
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

typedef vector<int> vi;

string KMP_str; // The string to search in
string KMP_pat; // The pattern to search
vi lps;

// KMP Init
void KMP_init(){
    int m = KMP_pat.length();
    lps.resize(m+1,0);
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
int KMP_search() {
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int count =0;
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            count++;
            j = lps[j];
        }
    }
    return count;
}


int main() {
    string S;
    unordered_set<string> s;
    cin >> S;
    while (S != "0")
    {
        int type1=0, type2=0, type3=0;
        cin >> KMP_str;
        KMP_pat=S;
        KMP_init();
        type1 = KMP_search();
        for (int i = 0; i < (int)S.size(); i++) {
            s.insert(S.substr(0, i) + S.substr(i + 1));
        }
        for (auto it = s.begin(); it != s.end(); it++) {
            KMP_pat = *it;
            KMP_init();
            type2 += KMP_search();
        }

        s.clear();
        char avail[] = {'A', 'T', 'C', 'G'};
        for (int i = 0; i <= (int)S.size(); i++) {
            for (int j = 0; j < 4; j++) {
                s.insert(S.substr(0, i) + avail[j] + S.substr(i));
            }
        }
        for (auto i : s) {
            KMP_pat = i;
            KMP_init();
            type3 += KMP_search();
        }
        s.clear();
        cout << type1 << " " << type2 << " " << type3 << endl;
        cin >> S;
    }
    return 0;
}