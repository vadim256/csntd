
#ifndef LIST_H
#define LIST_H

typedef struct data {
    char address_ip[256];
    int count_ip;
} Data;

typedef struct list_ip{
    Data d;
    struct list_ip * next;
} ListIP;

ListIP * Create(const Data);

void Print(const ListIP *);

const ListIP * Find(const ListIP *, const Data);

void AddList(ListIP **, const Data);

void Clear(ListIP **);

#endif