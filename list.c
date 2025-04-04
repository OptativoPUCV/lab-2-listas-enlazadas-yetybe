#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{

    List * list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;   
}

void * firstList(List * list) 
{
    if (list->head != NULL )
    {
        list->current = list->head;
        return list->head->data;
    }

    return NULL;
}

void * nextList(List * list) 
{
    
    if (list->current != NULL)
        if(list->current->next != NULL)
        {
            list->current = list->current->next;
            return list->current->data;
        }
    return NULL;
}


void * lastList(List * list) 
{
    
    if (list->tail != NULL)
    {
        list->current = list->tail;
        return list->tail->data;
    }
    return NULL;
}

void * prevList(List * list) 
{
    if (list->current != NULL)
    {
        if (list->current->prev != NULL)
        {
            list->current = list->current->prev;
            return list->current->data;
        }
    }
    return NULL;
}

void pushFront(List * list, void * data) 
{
    Node * newNode = createNode(data);
    newNode->prev = NULL;
    if (list->head == NULL) 
    {
        
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        
    }
}

void pushBack(List * list, void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node *newNode = createNode(data);
    if (list->current == NULL) return;
    else
    {
        newNode->prev = list->current;
        if (list->current->next != NULL)
        {
            newNode->next = list->current->next;
            list->current->next->prev  = newNode;
        }
        else
        {
            list->tail = newNode;
        }
        list->current->next = newNode; 
       
    }

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}



void * popCurrent(List * list) 
{
    if (list == NULL || list->current == NULL ) return NULL;
    else
    {
        Node * nodoTarget = list->current;
        void * data = nodoTarget->data;
        if (nodoTarget == list->head && nodoTarget == list->tail) 
        {
            list->head = NULL;
            list->tail = NULL;
        }

        else if (nodoTarget == list->head) 
        {
            list->head = nodoTarget->next;
            list->head->prev = NULL;
        }
        
        else if (nodoTarget == list->tail) 
        {
            list->tail = nodoTarget->prev;
            list->tail->next = NULL;
        }
        
        else
        {
            Node * izq = list->current->prev;
            Node * der = list->current->next;
            izq->next = der;
            der->prev = izq;
        }
        
        list->current = nodoTarget->next;
        free(nodoTarget); 
        return data;
    }
   
    
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}