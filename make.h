enum types {ROW, HEADER, COMBINED};

typedef struct {
    enum types type;
    char* content;
    char* inst;
} phrase;

const unsigned int ROW_SIZE = 128;
const unsigned int COL_SIZE = 512;
const unsigned int INST_SIZE = 128;

int normalize(char* str);
int phrase_init(phrase* p, char* str);
phrase* phrase_create(char* str);
int buffer_get(phrase** buffer, FILE* fp);
int eval(char* inst, phrase** buffer, int size);