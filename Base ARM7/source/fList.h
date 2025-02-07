
#ifndef __F_FLIST_H__
#define __F_FLIST_H__

typedef struct
{
   int  data;
} list_data;

typedef struct list_t
{
  list_data *data;
  struct list_t *nxt;
  struct list_t *prv;
}list_t;

int list_length(list_t **l);
int is_list_empty(list_t **l);
int contains_value(list_t **l, char *value);

int list_insert_end(list_t **l, int data);/*Returns TRUE if everything goes OK and MEMORY_OVERFLOW if no memory is available to allocate new node*/
void list_create_empty(list_t **l);/*Points list pointer to NULL*/
int list_is_item_in(list_t **l, int data);

#endif
