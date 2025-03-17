#include "ladder.h"
int main() {
    verify_word_ladder();

    string start_word, end_word;
    cout << "Enter a starting word: ";
    cin >> start_word;
    make_word_lower(start_word);
    cout << "Enter an ending word: ";
    cin >> end_word;
    make_word_lower(end_word);
    if (start_word == end_word)
        error("start and end words cannot be the same!", start_word, end_word);
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    vector<string> word_ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(word_ladder);
}