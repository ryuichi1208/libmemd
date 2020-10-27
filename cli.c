#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libmemcached/memcached.h>

int main(int argc, char **argv) {
  memcached_st *memc = NULL;
  memcached_return rv; 
  const char *key = "some_key";
  const char *val = "this is a value";
  int data;

  if ((memc = memcached_create(NULL)) == NULL) {
    fprintf(stderr, "failed to allocate memory\n");
    return 1;
  }

  rv = memcached_server_add(memc, "localhost", 11211);

  if (rv != MEMCACHED_SUCCESS) {
    fprintf(stderr, "failed to set server\n");
    return 1;
  }

  rv = memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, data);

  if (rv != MEMCACHED_SUCCESS) {
    fprintf(stderr, "failed to enable binary protocol\n");
    return 1;
  }

  rv =  memcached_set(memc, key, strlen(key), val, strlen(val), 0, 0); 

  if (rv != MEMCACHED_SUCCESS) {
    fprintf(stderr, "failed to set record\n");
    return 1;
  }

  char *result;
  uint32_t flags;
  size_t result_length;
  result = memcached_get(memc, key, strlen(key), &result_length, &flags, &rv); 

  if (rv != MEMCACHED_SUCCESS) {
    fprintf(stderr, "failed to fetch record\n");
    return 1;
  }

  printf("Key: %s\n", key);
  printf("Fetched: %s\n", result);
  printf("Data Length: %d\n", (int)result_length);

  free(result);
  memcached_free(memc);
  return 0;
}
