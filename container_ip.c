#include "include/container_ip.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void Print(const ListIP * u){
    ListIP * p = u;
    while(p != NULL){
        printf("IP:%s : %d", p->d.address_ip, p->d.count_ip);
        p = p->next;
    }
}

const ListIP * Find(const ListIP * u, const Data * x){
    const ListIP * p = u;
    while(p != NULL){
        if(!strcmp(p->d.address_ip, x->address_ip))
            return p;
        p = p->next;
    }
    return NULL;
}

void AddBeg(ListIP ** u, const Data * x){
    ListIP * p = (ListIP*)malloc(sizeof(ListIP));
    if(!p)
        return;
    p->d.address_ip = (char *) malloc(sizeof(char)*strlen(x->address_ip)+1);
    if(!(p->d.address_ip))
        return;
    strcpy(p->d.address_ip, x->address_ip);
    p->d.count_ip = x->count_ip;
    p->next = *u;
    *u = p;
}

void Insert(ListIP ** u, const Data * x){
    ListIP *p = (ListIP*) malloc(sizeof(ListIP));
    if(!p)
        return;
    p->d.address_ip = (char *) malloc(sizeof(char)*strlen(x->address_ip)+1);
    if(!(p->d.address_ip))
        return;
    strcpy(p->d.address_ip, x->address_ip);
    p->d.count_ip = x->count_ip;
    if(*u == 0) 
    {
        p->next = 0;
        *u = p;
      return;
    }
    ListIP *t = *u;
    if(strcmp(t->d.address_ip, p->d.address_ip) >= 0) {
        p->next = t;
        *u = p;
        return;
    }
    ListIP *t1 = t->next;
    while(t1) {
        if(strcmp(t->d.address_ip, p->d.address_ip) < 0 && 
           strcmp(p->d.address_ip, t1->d.address_ip) <= 0) { 
            t->next = p;
            p->next = t1;
            return;
        }
        t = t1;
        t1 = t1->next;
    }
    t->next = p; 
    p->next = 0;
}

void Delete(ListIP ** u, const Data * x){
    if(*u == 0){
        return;
    }
    ListIP *t = *u;
    if(!strcmp(t->d.address_ip,x->address_ip)) {
        *u = t->next;
        free(t->d.address_ip);
        free(t);
        return;
    }

    ListIP *t1 = t->next;

    while(t1) {
        if(!strcmp(t1->d.address_ip, x->address_ip)){
            t->next = t1->next;
            free(t1->d.address_ip);
            free(t1);
            return;
        }
        t = t1;
        t1 = t1->next;
   }
}

void Clear(ListIP ** u){

    if(*u == 0) return;
    ListIP *p = *u;
    ListIP *t;
    while(p) {
      t = p;
      p = p->next;
      free(t->d.address_ip);
      free(t);
   }
   *u = NULL;
}