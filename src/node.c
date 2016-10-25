#include "node.h"
#include <stddef.h>

node * new_node(node * list, void * object){
  if(list==NULL){
    list = (node *)malloc(sizeof(node));
    list->next = NULL;
    list->obj = object;
    return list;
  }
  else{
    node * temp = list;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next=(node *)malloc(sizeof(node));
    temp = temp->next;
    temp->next = NULL;
    temp->obj = object;
  }
  return list;
}

node * delete_node(node * list, void * object){
  if(list == NULL)
    return NULL;
  else if(list->obj == object){
    node * current = list->next;
    free(list);
    return current;
  }
  else{
    node * next = list->next;
    node * current = list;
    while(next != NULL){
      if(next->obj == object){
	current->next = next->next;
	free(next);
	return list;
      }
      else if(next->next == NULL){
	return list;
      }
      else{
	current = next;
	next = current->next;
      }
    }
  }
  return list;
}


