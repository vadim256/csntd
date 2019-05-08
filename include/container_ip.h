
#ifndef CONTAINER_IP_H_
#define CONTAINER_IP_H_

typedef struct data {
    char * address_ip;
    int count_ip;
} Data;

typedef struct linked_list_ip{
    Data d;
    struct linked_list_ip * next;
} ListIP;

ListIP * Init(void);
void Print(const ListIP *);
const ListIP * Find(const ListIP *, const Data *);
void AddBeg(ListIP **, const Data*);
void Insert(ListIP**, const Data*);
void Delete(ListIP**, const Data*);
void Clear(ListIP **);

#endif