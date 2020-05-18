//
// Created by Gregory Walter on 5/18/20.
//

// INPUT
// LINE1:  string, S (1 ≤ |S| ≤ 50,000), small, Latin letters only
// Line2:  Q (1 ≤ Q ≤ 50,000), number of queries
// Line3 - Line (Q+3-1): l, r (1 ≤ l ≤ r ≤ |S|), positions of first and last symbols in substring

#include <iostream>
#include <string>
#include <cinttypes>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// #define MYDEBUG

struct query {
    uint32_t left;
    uint32_t right;
};

class LetterFreq {
private:
public:
    char letter;
    vector<uint32_t> dsum{0};

    explicit LetterFreq(char l) { letter = l; }

    friend std::ostream &operator<<(std::ostream &os, const LetterFreq &lf);

};

std::ostream &operator<<(std::ostream &os, const LetterFreq &lf) {
    os << lf.letter << ":  ";
    for (auto &val : lf.dsum) { cout << val << " "; }
    cout << endl;
    return os;
}

void show(string &, uint32_t, vector<query> &);

char run_query(query &, vector<LetterFreq> &);

int main(int argc, char *argv[]) {
    string in_str;
    uint32_t num_q;
    vector<query> queries;
    vector<LetterFreq> alphabet;
    vector<char> answers;

    // create an array of arrays -- one row for each letter in alphabet
    auto *tmp_p = new LetterFreq('z');
    for (char a = 'a'; a <= 'z'; a++) {
        tmp_p->letter = a;
        alphabet.push_back(*tmp_p);
    }

    // read in stdin
    cin >> in_str;
    cin >> num_q;
    for (int i = 0; i < num_q; i++) {
        query tmp{0, 0};
        cin >> tmp.left >> tmp.right;
        queries.push_back(tmp);
    }

#ifdef MYDEBUG
    show(in_str, num_q, queries);
#endif

    // for each letter in S, add running total entry to each alphabet array
    uint32_t next_sum;
    uint32_t index = 1;
    for (auto &let : in_str) {
        for (auto &row : alphabet) {
            next_sum = row.letter == let ? row.dsum.at(index - 1) + 1 : row.dsum.at(index - 1);
            row.dsum.push_back(next_sum);
        }
        index++;
    }

    char mode;
    for (auto &q : queries) {
        mode = run_query(q, alphabet);
        answers.push_back(mode);
    }

#ifdef MYDEBUG
    for (auto &val : alphabet) { cout << val; }
    cout << endl;
#endif

    for (auto &val : answers) { cout << val << '\n'; }

    return 0;
}

char run_query(query &q, vector<LetterFreq> &alpha) {
    uint32_t occurences;
    uint32_t max_occurences = 0;
    char max_char;

    for (auto &row : alpha) {
        occurences = row.dsum.at(q.right) - row.dsum.at(q.left - 1);
        if (occurences >= max_occurences) {
            max_occurences = occurences;
            max_char = row.letter;
        }
    }
    return max_char;
}

void show(string &st, uint32_t q, vector<query> &v) {
    cout << st << endl;
    cout << q << endl;
    for (auto &val : v) { cout << val.left << " " << val.right << endl; }
}
