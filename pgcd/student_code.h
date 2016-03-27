struct Node {
    unsigned int divisor;
    struct Node *next;
};

struct Node *factorize(unsigned int n);

unsigned int gcd(unsigned int a, unsigned int b);
