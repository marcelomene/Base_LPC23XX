/*******************************************
	@file: fList.c
		Generic Double Linked List for Integers 
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
********************************************/

#include <stdlib.h>
#include "fList.h"

void list_create_empty(list_t **l)
{
   *l = NULL;
}

int is_list_empty(list_t **l)
{
    if(*l == NULL)
        return 1;
    else
        return 0;
}

int list_length(list_t **l)
{
	list_t *aux = *l;
	int count = 0;
	
	if(l == NULL)
		return count;
	
	while(aux != NULL)
	{
		count++;
		aux = aux->nxt;
	}
	
	return count;
}

int list_insert_end(list_t **l, int data)
{
    list_t *aux = *l;
    list_t *new_node;
		list_data *dataNode;
	
    new_node = (list_t *)malloc(sizeof(list_t));
	
		dataNode = (list_data *)malloc(sizeof(list_data));
		dataNode->data = data;
	
    if(new_node == NULL)
       return -1;

    new_node->data = dataNode;
    new_node->nxt = NULL;
    new_node->prv = NULL;

    if(is_list_empty(l))
    {
        *l = new_node;
    }
    else
    {
       while(aux->nxt !=  NULL)/*Places aux in the end of the list when the iteration finishes*/
       {
          aux = aux->nxt;
       }
        aux->nxt = new_node;
        new_node->prv = aux;
        new_node->nxt = NULL;
    }

    return 1;
}

int list_is_item_in(list_t **l, int data)
{
	list_t *aux = *l;
	
	if(*l == NULL)
		return 0;
	
	while(aux->nxt !=  NULL && aux->data->data != data)
			aux = aux->nxt;
	
	if(aux->data->data == data)
		return 1;
	else
		return 0;
}