#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

typedef struct {
    char *term;
    double weight;
} Term;

void read_in_terms(Term **terms, int *nterms, const char *filename);
void autocomplete(Term **answer, int *n_answer, Term *terms, int nterms, const char *substr);
int lowest_match(Term *terms, int nterms, const char *substr);
int highest_match(Term *terms, int nterms, const char *substr);

#endif // AUTOCOMPLETE_H

