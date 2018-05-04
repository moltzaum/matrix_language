#include "Enviroment.h"

bool initialized = false;
int var_count = 0;
const int hash_size = 10007;
struct Variable* vars[hash_size];
int var_keys[hash_size];

void init_enviroment () {
  
  /* Environment is a singleton. It HAS to be initialized (ie. I'm not
   * using a static block), and I'm not going to give an error if the
   * environment has already been initialized even though it shouldn't
   * need to be. */
  if (!initialized) {
    printf ("Initializing the environment.\n");
    esp = malloc (4096);
    top = esp;
    initialized = true;
  }
}

//TODO call this method
void shutdown_enviroment () {
  
  //free the memory for all variables
  for (int i = 0; i < var_count; i++) {
    free(vars[var_keys[i]]);
  }
}

//This hashing algorithm was found here:
//http://www.cse.yorku.ca/~oz/hash.html
int hash(char *str) {
  unsigned int hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % hash_size;
}

int insert_probe(int hash, char* name) {
  if (var_count == hash_size) return -1;
  int pos = hash;
  for (int i = 0; i < hash_size; i++) {
    if (vars[pos] == NULL) {
      var_count++;
      return pos;
    } else if (strcmp(vars[pos]->name, name) == 0) {
      //A variable of the same name was already declared. That's
      //fine, just return the current position.
      return pos;
    }
    pos = (hash + i + 3 * i*i) % hash_size;
  }
  return -1;
}

int lookup_probe(int hash, char* name) {
  int pos = hash;
  for (int i = 0; i < hash_size; i++)
    if (vars[pos] != NULL && strcmp(vars[pos]->name, name) == 0) {
      return pos;
    pos = (hash + i + 3 * i*i) % hash_size;
  }
  return -1;
}

int register_variable(char* name) {
  int index = hash_variable(name);
  if (index != -1) {
    return index;
  }
  
  struct Variable* v = malloc(sizeof(struct Variable));
  //v->name = malloc(strlen(name) * sizeof(char));
  //strcpy(v->name, name);
  v->name = name;
  index = insert_probe(hash(name), name);
  var_keys[var_count-1] = index;
  vars[index] = v;
  return index;
}

int hash_variable(char* name) {
  return lookup_probe(hash(name), name);
}

struct Variable* lookup_variable(int i) {
  return vars[i];
}


