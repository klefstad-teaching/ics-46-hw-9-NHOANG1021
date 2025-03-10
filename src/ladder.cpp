#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1.length() != str2.length()) return false;
    int diff_count = 0;
    for (size_t i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            diff_count++;
            if (diff_count > d) return false;
        }
    }
    return diff_count == d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladders.empty()) {
        int size = ladders.size();
        set<string> level_visited;
        
        for (int i = 0; i < size; ++i) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();
            
            if (last_word == end_word) return ladder;
            
            for (const string& word : word_list) {
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        visited.insert(level_visited.begin(), level_visited.end());
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << ladder[i];
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}