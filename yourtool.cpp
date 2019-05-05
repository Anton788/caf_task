#include <iostream>
#include <vector>
using namespace std;

vector<int> Prefix_Function(string& s) {
    vector<int> prefix(s.size());
    prefix[0] = 0;
    for (int i = 1; i < s.size() - 1; ++i) {
        int k = prefix[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = prefix[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        prefix[i] = k;
    }
    return prefix;
}

void Algorithm(string& pattern){
    pattern += '#'; // Символ, которого нету в тексте.
    vector<int> pref_pattern = Prefix_Function(pattern);
    char a;
    int counter = 0;
    int len = pref_pattern.size();
    while ((a = getchar()) != EOF){
        printf("%c", a);
        if (pattern[counter] == a){
            ++counter;
        } else {
            while (counter > 0 && pattern[counter] != a) {
                counter = pref_pattern[counter - 1];
            }
            if (pattern[counter] == a){
                ++counter;
            }
        }
        if (counter == len - 1){
            printf("%c", '*');
        }
    }
}

int main(int argc, char** argv) {
    string pattern = argv[1];
    Algorithm(pattern);
    return 0;
}
