#pragma once
#include<iostream>
class node
{
    int info;
    node* next;
    node* before;
public:
    node();
    node(int, node*, node*);
    friend class lista;
};



