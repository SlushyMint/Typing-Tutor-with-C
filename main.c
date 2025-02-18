#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Sentence lists for different difficulty levels
const char *easy_sentences[] = {
    "The quick brown fox jumps over the lazy dog.",
    "A cat sleeps on the couch.",
    "I love to eat pizza.",
    "The sun is shining brightly.",
    "She reads a book every day."
};
const int num_easy_sentences = sizeof(easy_sentences) / sizeof(easy_sentences[0]);

const char *medium_sentences[] = {
    "Learning to type faster takes practice and patience.",
    "The weather is perfect for a walk in the park.",
    "She enjoys cooking delicious meals for her family.",
    "He decided to travel the world after graduation.",
    "Reading books helps improve your vocabulary."
};
const int num_medium_sentences = sizeof(medium_sentences) / sizeof(medium_sentences[0]);

const char *hard_sentences[] = {
    "Despite the heavy rain, they continued their journey without hesitation.",
    "The scientist conducted an experiment to test the new hypothesis.",
    "Programming requires logical thinking, creativity, and attention to detail.",
    "In the middle of the night, she heard a strange noise coming from the attic.",
    "Success is not final, failure is not fatal: It is the courage to continue that counts."
};
const int num_hard_sentences = sizeof(hard_sentences) / sizeof(hard_sentences[0]);

// Function to generate a random sentence based on difficulty
const char* get_random_sentence(int difficulty) {
    if (difficulty == 1) {
        return easy_sentences[rand() % num_easy_sentences];
    } else if (difficulty == 2) {
        return medium_sentences[rand() % num_medium_sentences];
    } else if (difficulty == 3) {
        return hard_sentences[rand() % num_hard_sentences];
    } else {
        printf("Invalid difficulty level. Defaulting to Easy.\n");
        return easy_sentences[rand() % num_easy_sentences];
    }
}

// Function to calculate typing speed (characters per minute)
double calculate_typing_speed(int num_characters, double elapsed_time) {
    // Convert elapsed time to minutes and calculate characters per minute
    return (num_characters / (elapsed_time / CLOCKS_PER_SEC)) * 60;
}

// Function to calculate typing accuracy (percentage)
int calculate_accuracy(const char *target, const char *input) {
    int correct = 0;
    int length = strlen(target);
    int i; // Declare the loop variable here
    for (i = 0; i < length; i++) {
        if (target[i] == input[i]) {
            correct++;
        }
    }
    return (correct * 100) / length; // Return accuracy as a percentage
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    while (1) { // Infinite loop to keep the program running
        printf("\nWelcome to the Typing Tutor!\n");

        // Let the user choose difficulty level or exit
        printf("Choose an option:\n");
        printf("1. Easy\n");
        printf("2. Medium\n");
        printf("3. Hard\n");
        printf("4. Exit\n");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        if (choice == 4) {
            printf("Exiting the program. Goodbye!\n");
            break; // Break out of the loop to exit the program
        }

        // Get a random sentence based on the chosen difficulty
        const char *target_sentence = get_random_sentence(choice);
        printf("\nType the following sentence as fast and accurately as possible:\n");
        printf("\nSentence: %s\n", target_sentence);

        // Start the timer
        clock_t start_time = clock();

        // Get user input
        char input[256]; // Increase buffer size for sentences
        printf("Your input: ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from fgets
        input[strcspn(input, "\n")] = '\0';

        // Stop the timer
        clock_t end_time = clock();

        // Calculate elapsed time
        double elapsed_time = (double)(end_time - start_time);

        // Calculate typing speed
        int num_characters = strlen(input);
        double speed = calculate_typing_speed(num_characters, elapsed_time);

        // Calculate accuracy
        int accuracy = calculate_accuracy(target_sentence, input);

        // Display results
        printf("\nResults:\n");
        printf("Time taken: %.2f seconds\n", elapsed_time / CLOCKS_PER_SEC);
        printf("Typing speed: %.2f characters per minute\n", speed);
        printf("Accuracy: %d%%\n", accuracy);

        if (strcmp(target_sentence, input) == 0) {
            printf("Perfect! You typed the sentence correctly.\n");
        } else {
            printf("You made some mistakes. Keep practicing!\n");
        }
    }

    return 0;
}
