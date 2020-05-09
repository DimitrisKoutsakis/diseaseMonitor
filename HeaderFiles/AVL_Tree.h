#pragma once
#include "PatientList.h"


class AVL_Tree {
private:
    struct node {
        PatientList* list;
        node *left, *right;
        int date, height;
    };

    node* root;

    void empty(node* t);    // delete all nodes of AVL Tree
    node* recInsert(PatientRecord* x, node* t);     // Insert new item and rotate if necessary to maintain balance
    node* RightRotate(node*& t);    // Single right rotate
    node* LeftRotate(node*& t);     // Single left Rotate
    int height(node* t);            // Return height of node in tree
    int recCount(node* t, int date1=0, int date2=0, PatientRecord *p=NULL); // Recursive search and count
    bool changeExitRec(node *t, int id, int date);
    void deleteRecordsRec(node *t);     // Delete all PatientRecords in AVL tree

public:
    AVL_Tree();
    ~AVL_Tree();
    void insert(PatientRecord* x);
    int count(int date1=0, int date2=0, PatientRecord *p=NULL);     // Count all Patient records simila to p with date1<entryDate<date2
    bool changeExitDate(int id, int date);
    void deleteRecords();
};

