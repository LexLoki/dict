typedef struct dict* Dict;

Dict *dict_cria(void);

void dict_set(Dict *d, char *key, void *value);

void dict_remove(Dict *d, char *key);

void *dict_getValue(Dict *d, char *key);

void dict_free(Dict *d);
