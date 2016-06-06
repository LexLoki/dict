#include<stdio.h>
#include<string.h>
#include "dict.h"

int main(void){
  Dict *d = dict_init(sizeof(int));
  int year=2016,month=6,day=5;

  dict_set(d,"year",&year);
  dict_set(d,"month",&month);
  dict_set(d,"day",&day);

  printf("%d\n", *(int*)dict_getValue(d,"year"));
  printf("%d\n", *(int*)dict_getValue(d,"month"));
  printf("%d\n", *(int*)dict_getValue(d,"day"));

  dict_remove(d,"year");
  if(dict_getValue(d,"year")==NULL)
    printf("entry year does not exist\n");

  dict_free(d);
  return 0;
}
