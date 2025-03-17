#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string msg, string word1, string word2) {
    if (word1.empty() && word2.empty())
        cerr << "Error: " << msg << endl;
    else if (word1.empty() ^ word2.empty())
        cerr << "For word: "  << word1 << word2 << "\nError: " << msg << endl;
    else
        cerr << "For words: " << word1 << " " << word2  << "\nError: " << msg << endl;
    return;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1 == str2)
        return false;

    int size1 = str1.size(), size2 = str2.size();
    if (abs(size1 - size2) > d)
        return false; 

    if (abs(size1 - size2) == d) {
        string longer_word = size1 > size2 ? str1 : str2;
        string shorter_word = size1 < size2 ? str1 : str2;
        for (int i = 0; i < longer_word.size(); ++i) {
            string shortened_word = longer_word;
            shortened_word.erase(i, 1);
            if (shortened_word == shorter_word)
                return true;
        }
    }
    else if (size1 == size2)
        return is_adjacent(str1, str2);

    return false;
}
bool is_adjacent(const string& word1, const string& word2) {
    int word_size = word1.size();
    int diff_count = 0;
    for (int i = 0; i < word_size; ++i) {
        if (word1[i] != word2[i])
            ++diff_count;
    }
    return diff_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (!word_list.contains(end_word)) {
        error("ending word is not in word list", end_word);
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (edit_distance_within(last_word, word, 1)) {
                if (!visited.contains(word)) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        error("word_list file failed to open.");
        return;
    }
    for (string word; in >> word;) {
        make_word_lower(word);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found for the two words." << endl;
        return;
    }
    for (int i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}


void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

void make_word_lower(string& word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}