#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"






char secretWord[WORD_SIZE];
char guesses[26];
int tries = 0;


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

void opening() {
    printf("*****************************\n");
    printf("  ----  Hangman Game   ----  \n");
    printf("----   You have 5 tries   -----\n");
    printf("*****************************\n\n");

}

void get_guess() {
        char guess;
        scanf(" %c", &guess);
        guesses[tries] = guess;
        tries ++;
}

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


/*void choose_secret_word () {
    sprintf(secretWord, "MELANCIA");
}
*/
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



int hanged() {

    return wrong_guesses() >= 5;
}

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
