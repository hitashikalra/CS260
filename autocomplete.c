#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"

// Compare function for qsort
int compare_terms(const void *a, const void *b) {
    return strcmp(((Term *)a)->term, ((Term *)b)->term);
}

// Read terms from file
void read_in_terms(Term **terms, int *nterms, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    *nterms = 0;
    *terms = malloc(10000 * sizeof(Term));  // Allocate space for up to 10,000 terms
    if (!*terms) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
        (*terms)[*nterms].term = malloc(strlen(buffer) + 1); // Allocate memory
        if (!(*terms)[*nterms].term) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        strcpy((*terms)[*nterms].term, buffer);  // Copy string
        (*terms)[*nterms].weight = (double)(*nterms + 1);  // Dummy weight
        (*nterms)++;
    }

    fclose(file);
    qsort(*terms, *nterms, sizeof(Term), compare_terms);
}

// Find the lowest index where term starts with substr
int lowest_match(Term *terms, int nterms, const char *substr) {
    for (int i = 0; i < nterms; i++) {
        if (strncmp(terms[i].term, substr, strlen(substr)) == 0) {
            return i;
        }
    }
    return -1;
}

// Find the highest index where term starts with substr
int highest_match(Term *terms, int nterms, const char *substr) {
    int index = -1;
    for (int i = 0; i < nterms; i++) {
        if (strncmp(terms[i].term, substr, strlen(substr)) == 0) {
            index = i;
        }
    }
    return index;
}

// Autocomplete function
void autocomplete(Term **answer, int *n_answer, Term *terms, int nterms, const char *substr) {
    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);

    if (low == -1 || high == -1 || high < low) {
        *n_answer = 0;
        *answer = NULL;
        return;
    }

    *n_answer = high - low + 1;
    *answer = malloc((*n_answer) * sizeof(Term));
    if (!*answer) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *n_answer; i++) {
        (*answer)[i] = terms[low + i];
    }
}

