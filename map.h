/*
 * Copyright (c) 2022 XXIV
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>
#include <string.h>

typedef struct map map;

struct map {
    char **keys;
    char **values;
    size_t length;

    int (*push)(map *, char *, char *);

    int (*is_empty)(map *);

    char *(*get)(map *, char *);

    char *(*get_key)(map *, char *);
};

/**
 * Push key-value pair to the map
 *
 * @param self pointer to the map
 * @param key key
 * @param value value
 * @return 0 on success and non zero value on failure
 */
int _push(map *self, char *key, char *value) {
    if (self->length == 0) {
        self->keys = (char **) malloc(sizeof(char *));
        if (self->keys == NULL) {
            return -1;
        }

        self->values = (char **) malloc(sizeof(char *));
        if (self->values == NULL) {
            return -1;
        }
        self->keys[self->length] = (char *) malloc((strlen(key) + 1) * sizeof(char));
        if (self->keys[self->length] == NULL) {
            return -1;
        }
        strncpy(self->keys[self->length], key, strlen(key));

        self->values[self->length] = (char *) malloc((strlen(value) + 1) * sizeof(char));
        if (self->values[self->length] == NULL) {
            return -1;
        }
        strncpy(self->values[self->length], value, strlen(value));
        self->length += 1;
    } else {
        self->keys = (char **) realloc(self->keys, (self->length + 1) * sizeof(char *));
        if (self->keys == NULL) {
            return -1;
        }
        self->keys[self->length] = (char *) malloc((strlen(key) + 1) * sizeof(char));
        if (self->keys[self->length] == NULL) {
            return -1;
        }
        strncpy(self->keys[self->length], key, strlen(key));

        self->values = (char **) realloc(self->values, (self->length + 1) * sizeof(char *));
        if (self->values == NULL) {
            return -1;
        }
        self->values[self->length] = (char *) malloc((strlen(value) + 1) * sizeof(char));
        if (self->values[self->length] == NULL) {
            return -1;
        }
        strncpy(self->values[self->length], value, strlen(value));
        self->length += 1;
    }
    return 0;
}

/**
 * Get value by key
 *
 * @param self pointer to the map
 * @param key key associated with the value
 * @return value on success and NULL on failure
 */
char *_get(map *self, char *key) {
    for (int i = 0; i < self->length; i++) {
        if (strcmp(self->keys[i], key) == 0) {
            return self->values[i];
        }
    }
    return NULL;
}

/**
 * Get key by value
 *
 * @param self pointer to the map
 * @param value value associated with the key
 * @return key on success and NULL on failure
 */
char *_get_key(map *self, char *value) {
    for (int i = 0; i < self->length; i++) {
        if (strcmp(self->values[i], value) == 0) {
            return self->keys[i];
        }
    }
    return NULL;
}

/**
 * Check if the map is empty
 *
 * @param self pointer to the map
 * @return 1 if it's empty and 0 if it's not
 */
int _is_empty(map *self) {
    if (self->length != 0) {
        return 0;
    }
    return 1;
}

/**
 * function to clean the memory after using the map
 *
 * @param self pointer to the map
 */
void map_clean(map *self) {
    if (self != NULL) {
        if (self->keys != NULL) {
            for (int i = 0; i < self->length; i++) {
                if (self->keys[i] != NULL) {
                    free(self->keys[i]);
                }
            }
            free(self->keys);
        }
        if (self->values != NULL) {
            for (int i = 0; i < self->length; i++) {
                if (self->values[i] != NULL) {
                    free(self->values[i]);
                }
            }
            free(self->values);
        }
        free(self);
    }
}

/**
 * function to create map
 *
 * @param self pointer to the map
 * @return map
 */
map *map_init() {
    map *self = (map *) malloc(sizeof(map));
    self->push = &_push;
    self->is_empty = &_is_empty;
    self->get = &_get;
    self->get_key = &_get_key;

    return self;
}

#endif // __MAP_H__