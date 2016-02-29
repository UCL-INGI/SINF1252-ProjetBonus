typedef struct indexEntry {
    char *word;
    int count; //nombre de fois qu'un mot est apparu dans le corpus
    struct indexEntry *next;
} Entry;

Entry *build_index(char *corpus);
void filter_index(int treshold);
