#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "lexicon.h"
using namespace std;

void setGame(string **s, int N)
{
    int line = 0;
    for(int i = 0; i < N; i++){
        string str;
        cin >> str;
        for(int j = 0; j < N; j++){
            s[line][j] = str[j];
        }
        line++;
    }
}

void display(string **s, int N, int score, vector<string> v)
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << s[i][j];
        }
        cout << endl;
    }
    cout << "Your Score: " << score << endl;
    cout << "Your Words:";
    for (const auto & iter : v){
        cout << " " << iter;
    }
    cout << endl;
}


bool check(const string& guess_word, Lexicon &lex)
{
    if(lex.contains(guess_word) == 1)
        return true;
    else
        return false;
}

void computerPlay(Lexicon lex1, const Lexicon& lex2, int computer_score)
{
    cout << "Computer Score: " << computer_score << endl;
    cout << "Computer Words:";
    for (const auto & iter : lex2){
        string s = iter;
        if(check(s, lex1) == 0){
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            cout << " " << s;
        }
    }
}

void findAll(string **s, int N, int &computer_score, Lexicon &lex, Lexicon &lex2,
             int i, int j, const string& word, vector<int> va, vector<int> vb)
{
    for(unsigned int k = 0; k < va.size(); k++){
        if(i == va[k] && j == vb[k]){
            return;
        }
    }
    string new_word = word + s[i][j];
    if(lex.containsPrefix(new_word) == 0) return;
    int add_score = new_word.length() - 3;
    if(check(new_word, lex) == 1 &&
       check(new_word, lex2) == 0 && add_score > 0){
        computer_score += add_score;
        lex2.add(new_word);
    }
    if(i >= 1 && i < N && j >= 0 && j < N){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i - 1, j, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 0 && i < N - 1 && j >= 0 && j < N){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i + 1, j, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 0 && i < N && j >= 1 && j < N){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i, j - 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 0 && i < N && j >= 0 && j < N - 1){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i, j + 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 1 && i < N && j >= 1 && j < N){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i - 1, j - 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 1 && i < N && j >= 0 && j < N - 1){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i - 1, j + 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 0 && i < N - 1 && j >= 1 && j < N){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i + 1, j - 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
    if(i >= 0 && i < N - 1 && j >= 0 && j < N - 1){
        va.push_back(i);
        vb.push_back(j);
        findAll(s, N, computer_score, lex, lex2, i + 1, j + 1, new_word, va, vb);
        va.pop_back();
        vb.pop_back();
    }
}

int main()
{
    Lexicon lex("./EnglishWords.txt");
    Lexicon lex1, lex2;

    vector<string> v;
    vector<int> va, vb;
    string word;
    int N, score = 0, com_score = 0;
    cin >> N;
    string **maze = new string*[N];
    for(int i = 0; i < N; ++i){
        maze[i] = new string[N];
    }
    setGame(maze, N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            findAll(maze, N, com_score, lex, lex2, i, j, word, va, vb);
        }
    }

    while(true){
        display(maze, N, score, v);
        string guess_word;
        cin >> guess_word;

        if(guess_word != "???"){
            transform(guess_word.begin(), guess_word.end(), guess_word.begin(), ::tolower);
            int add_score = guess_word.length() - 3;
            if(add_score > 0){
                if(check(guess_word, lex) == 1){
                    if(check(guess_word, lex1) == 0){
                        if(check(guess_word, lex2) == 1){
                            lex1.add(guess_word);
                            v.push_back(guess_word);
                            score += add_score;
                            com_score -= add_score;
                        }
                        else
                            cout << guess_word << " is not on board."<< endl;
                    }
                    else
                        cout << guess_word << " is already found." << endl;
                }
                else
                    cout << guess_word << " is not a word."<< endl;
            }
            else
                cout << guess_word << " is too short." << endl;
        }
        else{
            computerPlay(lex1, lex2, com_score);
            break;
        }
    }
    lex.~Lexicon();

    return 0;
}

