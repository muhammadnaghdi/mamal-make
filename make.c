#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "make.h"

int normalize(char* str) {
    int lenght = strlen(str);
    if (str[lenght - 1] == '\n') {
        str[lenght - 1] = 0;
    }
    
    return 0;
}

int phrase_init(phrase* p, char* str) {
    if (p->type == ROW) {
        strcpy(p->content, str);
        p->inst = NULL;
    } else if (p->type == HEADER) {
        str[strlen(str) - 1] = 0;
        strcpy(p->inst, str);
        p->content = NULL;
    } else {
        strcpy(p->inst, strtok(str, " "));
        p->inst[strlen(p->inst) - 1] = 0;
        strcpy(p->content, strtok(NULL, ""));
    }
    
    return 0;
}

phrase* phrase_create(char* str) {
    int lenght = strlen(str);

    phrase* tmp = (phrase*) malloc(sizeof(phrase));

    tmp->content = (char *) malloc(COL_SIZE * sizeof(char));
    tmp->inst = (char*) malloc(INST_SIZE * sizeof(char));
    tmp->type = ROW;

    int i;
    for (i = 0; i < lenght; ++i) {
        if (str[i] == ':') {
            if (str[i + 1] == 0) {
                tmp->type = HEADER;
                break;
            } else {
                tmp->type = COMBINED;
                break;
            }
        }
    }

    phrase_init(tmp, str);

    return tmp;
}

int buffer_get(phrase** buffer, FILE* fp) {
    char str[COL_SIZE];
    int i = 0;
    while (i < ROW_SIZE && fgets(str, COL_SIZE, fp) != NULL) {
        normalize(str);
        phrase* p = phrase_create(str);
        buffer[i] = p;
        ++i;
    }

    return i;
}

int eval(char* inst, phrase** buffer, int size) {
    phrase* tmp;
    int i;
    if (inst == NULL) {
        tmp = buffer[0];
    } else {
        for (i = 0; i < size; ++i) {
            if (buffer[i]->inst != NULL) {
                if (!strcmp(inst, buffer[i]->inst)) {
                    tmp = buffer[i];
                    break;
                }
            }
        }
    }
    
    if (tmp->type == ROW) {
        system(tmp->content);
    } else if (tmp->type == HEADER) {
        ++i;
        while (i < size && buffer[i]->type == ROW) {
            system(buffer[i]->content);
            ++i;
        } 
    } else {
        char* next_inst = strtok(tmp->content, " ");
        while (next_inst != NULL)
        {
            eval(next_inst, buffer, size);
            next_inst = strtok(NULL, " ");
        }
    }
    
    return 0;
}