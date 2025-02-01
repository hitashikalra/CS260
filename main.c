#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "autocomplete.h"

int main() {
    Term *terms;
    int nterms;

    read_in_terms(&terms, &nterms, "fixed_queries.txt");

    char substr[200];
    printf("Enter a substring to autocomplete: ");
    fgets(substr, sizeof(substr), stdin);
    substr[strcspn(substr, "\n")] = '\0';

    Term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, substr);

    for (int i = 0; i < n_answer; i++) {
        printf("%s\n", answer[i].term);
    }

    free(terms);
    free(answer);
    return 0;
}

