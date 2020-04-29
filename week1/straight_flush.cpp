//
// Created by Gregory Walter on 4/26/20.
//

// Given one deck of 52 French playing cards, determine if five cards provided
// in standard input could represent a straight flush.
//
// Suits are marked as C, D, H, S.
// Ranks include [2, 3, 4, 5, 6, 7, 8, 9, T, Q, J, K, A]
//
// A straight flush is defined as five cards of the same suit of sequential rank.
// Ace can be a 1 or a 13.  No wrapping permitted.
//
// Test Cases
// 1.
// Input: 2D 5D 3D 4D 6D
// Output: YES
//
// 2.
// Input:  AD KH QH JS TC
// Output:  NO

#include <iostream>
#include <vector>
#include <string>

// #define MYDEBUG

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

static const int NUM = 5;
static const int RANKS = 13;
static const string YES = "YES";
static const string NO = "NO";
static const string NOT_SET = "NOT SET";

bool fill_ranks( vector<string> & raw, vector<unsigned int> & vals );
string check_flush( vector<unsigned int> & r );

#ifdef MYDEBUG
void show_raw_cards( vector<string> & raw );
#endif

int main( int argc, char *argv[] ) {
    vector<string> raw_cards(NUM);
    vector<unsigned int> ranks(RANKS + 2,0);
    string answer = NOT_SET;
    bool ace_found = false;

    // read in cards from stdin
    for ( auto i = 0; i < NUM; i++ ) {
        cin >> raw_cards[i];
    }

#ifdef MYDEBUG
    show_raw_cards( raw_cards );
#endif

    // check that suit is the same
    char suit = raw_cards[0][1];
    for ( auto i = 1; i < NUM; i++ ) {
        if ( raw_cards[i][1] != suit ) {
            answer = NO;
            cout << answer;
            return 0;
        }
    }

    // fill ranks vector according to card rank - Ace is high
    ace_found = fill_ranks( raw_cards, ranks );

    // all ranks must be same to enter here;
    // three cases:
    // 1.  no Ace -- add cards and check for sequence
    // 2.  Ace -- use as 13 and check for sequence
    // 3.  Ace -- use as 1 and check for sequence
    answer = check_flush(ranks);
    if ( answer != YES && ace_found ) {
        // check low-value Ace
        ranks[14] = 0;
        ranks[1] = 1;
        answer = check_flush(ranks);
    }

    cout << answer << endl;

    return 0;
}

string check_flush( vector<unsigned int> & r ) {
    int first_one = 0;
    string ans;
    unsigned int seq = 1;

    // find start of prospective flush
    for ( int i = 0; i < r.size(); i++ ) {
        if ( r[i] == 1 ) {
            first_one = i;
            break;
        }
    }

    // check five consecutive values
    for ( int i = first_one; i < first_one + NUM; i++ ) {
        seq = seq && r[i];
    }
    ans = seq ? YES : NO;
    return ans;
}

bool fill_ranks( vector<string> & raw, vector<unsigned int> & vals ) {
    bool ace = false;
    for ( auto card : raw ) {
        switch(card[0]) {
            case '2': vals[2] = 1; break;
            case '3': vals[3] = 1; break;
            case '4': vals[4] = 1; break;
            case '5': vals[5] = 1; break;
            case '6': vals[6] = 1; break;
            case '7': vals[7] = 1; break;
            case '8': vals[8] = 1; break;
            case '9': vals[9] = 1; break;
            case 'T': vals[10] = 1; break;
            case 'J': vals[11] = 1; break;
            case 'Q': vals[12] = 1; break;
            case 'K': vals[13] = 1; break;
            case 'A': vals[14] = 1;
                ace = true;
                break;
        }
    }
    return ace;
}

#ifdef MYDEBUG
void show_raw_cards( vector<string> & raw ) {
    for ( const auto & val : raw ) cout << val << " ";
    cout << endl;
}
#endif
