
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WRONG_ATTEMPTS 6
#define WORD_LIST_SIZE 5

void displayHangman(int wrongAttempts) {
    switch (wrongAttempts) {
        case 0:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 1:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 2:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |        |\n");
            printf("  |\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 3:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |       /|\n");
            printf("  |\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 4:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |       /|\\\n");
            printf("  |\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 5:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |       /|\\\n");
            printf("  |       /\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
        case 6:
            printf("   ________\n");
            printf("  |        |\n");
            printf("  |        O\n");
            printf("  |       /|\\\n");
            printf("  |       / \\\n");
            printf("  |\n");
            printf(" _|_________\n\n");
            break;
    }
}

int main() {
    const char *wordList[WORD_LIST_SIZE] = {"hangman", "programming", "computer", "algorithm", "school"};
    char guessedLetters[26] = {0};
    int playAgain = 1;

    srand(time(0)); // Seed the random number generator

    while (playAgain) {
        int randomIndex = rand() % WORD_LIST_SIZE;
        const char *word = wordList[randomIndex];
        int length = strlen(word);
        char guessed[length];
        memset(guessed, '_', length);

        int wrongAttempts = 0;
        int numGuessedLetters = 0;
        char guess;

        printf("Welcome to Hangman!\n");

        while (wrongAttempts < MAX_WRONG_ATTEMPTS) {
            printf("Word: ");
            for (int i = 0; i < length; i++) {
                printf("%c ", guessed[i]);
            }
            printf("\n");

            printf("Guessed letters: ");
            for (int i = 0; i < numGuessedLetters; i++) {
                printf("%c ", guessedLetters[i]);
            }
            printf("\n");

            printf("Enter a letter: ");
            scanf(" %c", &guess);
            guess = tolower(guess);

            if (!isalpha(guess)) {
                printf("Please enter a valid alphabetic character.\n");
                continue;
            }

            int alreadyGuessed = 0;
            for (int i = 0; i < numGuessedLetters; i++) {
                if (guessedLetters[i] == guess) {
                    alreadyGuessed = 1;
                    break;
                }
            }

            if (alreadyGuessed) {
                printf("You have already guessed that letter. Try again.\n");
                continue;
            }

            guessedLetters[numGuessedLetters++] = guess;

            int found = 0;
            for (int i = 0; i < length; i++) {
                if (word[i] == guess) {
                    guessed[i] = guess;
                    found = 1;
                }
            }

            if (!found) {
                wrongAttempts++;
                printf("Incorrect guess. You have %d attempts left.\n", MAX_WRONG_ATTEMPTS - wrongAttempts);
                displayHangman(wrongAttempts);
            }

            int allGuessed = 1;
            for (int i = 0; i < length; i++) {
                if (guessed[i] == '_') {
                    allGuessed = 0;
                    break;
                }
            }

            if (allGuessed) {
                printf("Congratulations! You guessed the word: %s\n", word);
                break;
            }
        }

        if (wrongAttempts >= MAX_WRONG_ATTEMPTS) {
            printf("Sorry, you lost. The word was: %s\n", word);
        }

        printf("Do you want to play again? (1 for Yes, 0 for No): ");
        scanf("%d", &playAgain);
    }

    return 0;
}

