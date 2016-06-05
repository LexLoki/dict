//  The MIT License (MIT)
//  Copyright © 2016 Pietro Ribeiro Pepe.

//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#define HASHSIZE 101
#define K 31

#include "dict.h"
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char *key;
	void *value;
	struct node *next;
}Node;

struct Dict{
	Node *table[HASHSIZE];
	int valueSize;
}

unsigned _hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

Node *node_init(char *key, void *value, int valueSize){
	Node *nd = (Node*)malloc(sizeof(Node));
	if(nd==NULL) exit(-1);
	nd->key = (char *)malloc((strlen(key)+1)*sizeof(char));
	if(nd->key==NULL) exit(-1);
	nd->value = malloc(valueSize);
	if(nd->value==NULL) exit(-1);
	memcpy(nd->value,value,valueSize);
	strcpy(nd->key,key);
	nd->next = NULL;
	return nd;
}

void node_free(Node *nd){
	free(nd->key);
	free(nd->value);
	free(nd);
}

Dict *dict_init(int valueSize){
	int i;
	Dict *d = (Dict*)malloc(sizeof(Dict));
	if(d==NULL) exit(-1);
	for(i=0;i<HASHSIZE;d->table[i++]=NULL);
	d->valueSize = valueSize;
	return d;
}

void dict_set(Dict *d, char *key, void *value){
	unsigned idx = _hash(key);
	Node *nd=d[idx];
	if(nd==NULL) d[idx]=node_init(key,value,d->valueSize);
	for(;strcmp(nd->key,key);nd=nd->next)
		if(nd->next==NULL){
			nd->next=node_init(key,value,d->valueSize);
			return;
		}
	memcpy(nd->value,value,d->valueSize);
}

void *dict_getValue(Dict *d, char *key){
	Node *nd;
	for(nd=d[_hash(key)];nd!=NULL;nd=nd->next)
		if(!strcmp(nd->key,key)) return nd->value;
	return NULL;
}

void dict_remove(Dict *d, char *key){
	unsigned idx = _hash(key);
	Node *nd=d[idx], *aux=NULL;
	for(;nd!=NULL;aux=nd,nd=nd->next)
		if(!strcmp(nd->key,key)){
			(aux==NULL) ? d[idx]=nd : aux->next=nd->next;
			node_free(nd);
			return;
		}
}

void dict_free(Dict *d){
	Node *aux, *nd;
	int i;
	for(i=0;i<HASHSIZE;i++)
		for(nd=d[i];nd!=NULL;aux=nd,nd=nd->next,node_free(aux));
	free(d);
}

