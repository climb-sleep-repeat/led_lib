#ifndef node_h
#define node_h

typedef void (*find)(void *);

typedef struct node_t node;
typedef struct node_t{
  void * obj;
  node * next;
}node;

led_node * new_node(node * list, void * object);
void delete_node(node * list, void * object);
node * find_node(node * list, find fp_find);


#endif
