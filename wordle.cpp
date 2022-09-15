/*
File name:       proj1.cpp
Assignment name: Project 1 - Wordle
Author:          Andrew Chen
Date:            2/27/2022
Section:         50
Email:           achen18@umbc.edu
Description:     This program simulates the word guessing game
                    Wordle.

*/


#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
Name: countWords
PreCondition: There are more than 0 words within
              the file being read.
PostCondition: Returns the total number of words
              within the file.
*/
int countWords();


const int TOTAL_WORDS = countWords();
const char RIGHT_SPOT = '!';        /*Letter in correct position*/
const char RIGHT_CHAR = '&';        /*Letter NOT in correct
                                    position, but is in word.*/
const char INCORRECT = '_';         /*Letter is does not exist
                                    in word at all.*/

/*
Name: intoWordList
PreCondition: There are more than 0 words
              within the source file.
PostCondition: Appends words from source file
               into an array called wordList
*/
void intoWordList(string wordList[]);


/*
Name: validWord
PreCondition: The user has made a guess and wordList
                has been populated with all possible words
                in the game.
PostCondition: returns true if the word is valid and false
                if the word is invalid.
*/
bool validWord(string userGuess, string wordList[]);


/*
Name: generateWord
PreCondition: The array wordList must be populated with words
PostCondtion: Returns a randomly selected word.
*/
string generateWord(string wordList[]);


/*
Name: checker
PreCondition: The user has made a guess
PostCondition: Returns results, which
                tells user which letters
                they got correct and incorrect
*/
string checker(string userGuess, string wordle);


/*
Name: checkWin
PreCondition: User has made a guess and their
                guess has been checked in the
                function called checker
Post Condition: Returns true if the user
                guessed the word, false if not.
*/
bool checkWin(string results);


int main(){
    string wordList[9999];
    string guesses[6][2];
    string userGuess = "";
    bool play = true;

    //Prompt
    intoWordList(wordList);
    cout << "Welcome to UMBC Wordle" << endl;
    cout << "Your file was imported!" << endl;
    cout << TOTAL_WORDS << " words imported." << endl;

    while(play){
        //Setup
        int numOfGuesses = 0;
        bool endRound = false;
        //Word that user needs to guess.
        string wordle = generateWord(wordList);
        string results = "";
        char playAgain = 'x';

        cout << "Ok. I am thinking of a word with five letter" << endl;
        
        for(int i = 0; i < 6; i++){
            guesses[i][0] = "";
            guesses[i][1] = "-----";
        }

        //Play
        do{
            //Win condition
            if(checkWin(results)){
                endRound = true;
                cout << "Congrats you won!" << endl;
            }else{
                //When user does not guess the word
                cout << "GUESS #" << numOfGuesses+1 << endl;
                cout << "What word would you like to guess?" << endl;
                cin >> userGuess;

                while (!(validWord(userGuess, wordList))){
                    cout << "That word is not in the word list" << endl;
                    cout << "What word would you like to guess?" << endl;
                    cin >> userGuess;
                }

                cout << "You guessed: " << userGuess << endl;
                results = checker(userGuess, wordle);
                
                guesses[numOfGuesses][0] = userGuess;
                guesses[numOfGuesses][1] = results;

                //Display current
                for(int i = 0; i<6; i++){
                    if (guesses[i][0] != ""){
                        cout << guesses[i][0] << endl;
                    }
                    cout << guesses[i][1] << endl;
                }

                numOfGuesses++;
            }
        }while((numOfGuesses < 6) && !(endRound));

        //Round End
        cout << "The correct word was: " << wordle << endl;
        cout << "Please wait 24 hou- Jk." << endl;
        
        while((playAgain != 'y') && (playAgain != 'n')){
            cout << "Another game? y/n" << endl;
            cin >> playAgain;
        }        

        if(playAgain == 'n'){
            play = false;
        }
        cout << endl;
    }
    //Stops playing wordle.
    cout << "Thanks for playing!" << endl;
    cout << endl;

    return 0;
}


int countWords(){
    /*
    Name: countWords
    PreCondition: There are more than 0 words within
                  the file being read.
    PostCondition: Returns the total number of words
                  within the file.
    */

    ifstream readData("proj1_data.txt");
    int count = 0;
    string word = "";

    while (getline(readData, word)){
        count++;
    }
    
    readData.close();

    return count;
}


void intoWordList(string wordList[]){
    /*
    Name: intoWordList
    PreCondition: There are more than 0 words
                  within the source file.
    PostCondition: Appends words from source file
                   into an array called wordList
    */

    ifstream readData("proj1_data.txt");
    int i = 0;
    string word = "";

    while(getline(readData, word)){
        wordList[i] = word;
        i++;
    }
}


bool validWord(string userGuess, string wordList[]){
    /*
    Name: validWord
    PreCondition: The user has made a guess and wordList
                   has been populated with all possible words
                   in the game.
    PostCondition: returns true if the word is valid and false
                   if the word is invalid.
    */

    bool validLength = false;
    bool wordFound = false;
    bool flag = false; //flag for detecting invalid/valid words.

    if (userGuess.size() == 5){
        //check length
        validLength = true;
    }

    for(int i = 0; i < TOTAL_WORDS; i++){
        //check if word is in word list
        if (userGuess == wordList[i]){
            wordFound = true;
        }
    }

    if (validLength && wordFound){
        flag = true;
    }

    return flag;

}


string generateWord(string wordList[]){
    /*
    Name: generateWord
    PreCondition: The array wordList must be populated with words
    PostCondtion: Returns a randomly selected word.
    */

    srand(time(NULL));
    int min = 1;
    int max = TOTAL_WORDS;
    int randomNum = (rand() % (max + 1 - min)) + min; 
    string chosenWord = wordList[randomNum];

    return chosenWord;
}


string checker(string userGuess, string wordle){
    /*
    Name: checker
    PreCondition: The user has made a guess
    PostCondition: Returns results, which
                    tells user which letters
                    they got correct and incorrect
    */
    string results = "_____";
    bool isBlank = false;
    
    if(userGuess == wordle){
        results = "!!!!!";
    }else{
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){

                //Checks if spot is a '_'
                if((results[j] != RIGHT_CHAR) && (results[j] != RIGHT_SPOT)){
                    isBlank = true;
                }

                if(wordle[i] == userGuess[j]){
                    if(i == j){
                        //If letter is in correct position
                        results[j] = RIGHT_SPOT;

                    }else if((i != j) && isBlank){
                        /*If letter is not in correct position,
                        but exists in the chosen word*/
                        results[j] = RIGHT_CHAR;
                        isBlank = false;
                        j = 5;

                    }
                }
            }
        }
    }

    return results;

}


bool checkWin(string results){
    /*
    Name: checkWin
    PreCondition: User has made a guess and their
                    guess has been checked in the
                    function called checker
    Post Condition: Returns true if the user
                    guessed the word, false if not.
    */

    bool win = false;

    if(results == "!!!!!"){
        win = true;
    }

    return win;
}