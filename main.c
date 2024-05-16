#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"


char secretWord[WORD_SIZE];
char guesses[26];
int tries = 0;

//adds a word to the word bank by reading from "words.txt"; adds +1 to the counter of words on LINE 1 and adds the user's word at the bottom line.
void add_word() {
    char choice;
    printf("Do you wish to add a new word to the game? (Y/N)\n");
    scanf(" %c", &choice);

    if (choice == 'Y') {
        char newWord[WORD_SIZE];
        printf("Type in the word you wish to add. \n");
        scanf("%s", &newWord);

        FILE* f;

        f = fopen("words.txt", "r+");
        if (f == 0 ) {
            printf("Sorry, database not available\n\n");
            exit(1);
        }

        int wordAmount;
        fscanf(f, "%d", &wordAmount);
        wordAmount++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", wordAmount);


        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        fclose(f);
    }
}

//reads from the "words.txt" file and sets the secretWord variable to the scanned "string" array.
void choose_word () {
    FILE* f;

    f = fopen("words.txt", "r");
    if (f == 0 ) {
        printf("Sorry, database not available\n\n");
        exit(1);
    }

    int wordAmount;
    fscanf(f, "%d", &wordAmount);


    srand(time(0));
    int random = rand() % wordAmount;

    for (int i = 0; i <= random; i++) {
        fscanf(f,"%s", &secretWord);
    }

    fclose(f);

}

//Displays the opening "menu" of the game.
void opening() {
    printf("*****************************\n");
    printf("  ----  Hangman Game   ----  \n");
    printf("----   You have 5 tries   -----\n");
    printf("*****************************\n\n");

}

//Scans for the user's guess, adds it to the array "guesses" at the position [tries], and increments tries by 1.
void get_guess() {
        char guess;
        scanf(" %c", &guess);
        guesses[tries] = guess;
        tries ++;
}

//compares the char "letter" (user's guess) to the guesses array at the position [j], if the "letter" is found at any position of the array, returns 1;
//otherwise returns 0.
int already_guessed(char letter) {
    int found = 0;

    for (int j = 0; j < tries; j++) {
        if (guesses[j] == letter) {
            found = 1;
            break;
        }
    }
    return found;

}

//prints the noose based on how many misses the user has; iterates through each char of the secretWord, and checks if the char is present in the guesses array;
//if it is, it prints the char, otherwise, it prints an underscore.
void draw_letters(){
    int misses = wrong_guesses();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (misses>=1?'(':' '), (misses>=1?'_':' '), (misses>=1?')':' '));
    printf(" |      %c%c%c  \n", (misses>=3?'\\':' '), (misses>=2?'|':' '), (misses>=3?'/': ' '));
    printf(" |       %c     \n", (misses>=2?'|':' '));
    printf(" |      %c %c   \n", (misses>=4?'/':' '), (misses>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");




    for (int i = 0; i < strlen(secretWord); i++) {

    int found = already_guessed(secretWord[i]);


    if (found == 1) {
        printf("%c", secretWord[i]);
    } else {
        printf("_ ");
    }

    }
    printf("\n");


}

//compares each guess (char) to each letter of the secretWord; if the secretWord does not contain the char stored in the array guesses[i], increments the misses by 1.
int wrong_guesses() {
    int misses = 0;
    for (int i = 0; i < tries; i++) {
        int exists = 0;

        for (int j = 0; j < strlen(secretWord); j++) {
            if (guesses[i] == secretWord[j]) {
                exists = 1;
                break;

            }
        }
        if (exists == 0) misses++;
    }
    return misses;
}

//Checks whether the user guesses wrong 5 times, in that case, return true.
int hanged() {

    return wrong_guesses() >= 5;
}

//more complicated than it needs to be
//checks if there is a char in secretWord that is still not in the guesses array. If that is the case, returns 0, otherwise returns 1, meaning
//the player won, and all the chars are in the guesses array, which means the player guessed all the letters.
int won() {
    for (int i = 0; i < strlen(secretWord); i++) {
        if (!already_guessed(secretWord[i])) {
            return 0;
        }

    }
    return 1;
}

int main()
{

    choose_word();
    opening();

    do {
        draw_letters();

        get_guess();


    } while (!won() && !hanged());
    if (won()) {
        printf("\nCongratulations, you won.\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");



    } else {
        printf("\nYou got hanged.\n\n");
        printf("The word was **%s**\n\n", secretWord);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /        bruh     \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    add_word();
}
