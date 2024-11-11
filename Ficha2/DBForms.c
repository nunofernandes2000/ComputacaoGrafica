//
// Created by Nuno Fernandes on 22/10/2024.
//

#include "form.h"
#include "DBForms.h"
#include <stdlib.h>

// Array of pointers to form objects (Recall, Form is a pointer!)
Form* a;
int n;

void initDBForms(int num) {
    int i;

    n = num;

    a = malloc(sizeof(Form) * n);

    // initialize array of forms (pointers to forms) to NULL
    for (i = 0; i < n; i++)
        a[i] = NULL;
}



void populateDBForms(int maxSize) {
    int i;

    for (i = 0; i < n; i++)
        if (a[i] == NULL) {
            a[i] = createRandomForm(maxSize);
            setBackgroundColor(a[i], rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0));
        }
}

int insertBDForm(Form f) {
    int i;

    for (i = 0; i < n; i++)
        if (a[i] == NULL) {
            a[i] = f;
            return 1;
        }

    return 0;
}

void deleteRandomDBForm() {
    int i = rand() % n;
    if (a[i] != NULL) {
        deleteForm(a[i]);
        a[i] = NULL;
    }
}






void drawDBForms() {
    int i;
    for (i = 0; i < n; i++)
        if (a[i] != NULL)
            drawForm(a[i]);
}

void printDBForms() {
    int i;

    // print the content of the array
    for (i = 0; i < n; i++)
        if (a[i] != NULL)
            printfForm(a[i]);
}


Form pickDBForm(float x, float y) {
    int i;
    for (i = n - 1; i >= 0; i--)
        if (a[i] != NULL && pick(x, y, a[i]))
            return a[i];
    return NULL;
}



//Pergunta 3 da ficha 4
int deleteFormDB(Form f) {
    int i;
    int formDeleted = 0; // flag to indicate if the form was deleted 0 - not deleted, 1 - deleted
    for (i = 0; i < n && a[i] != NULL; i++)
        if (a[i] == f) {
            deleteForm(a[i]);
            formDeleted = 1;
            break;
        }
    if(formDeleted) {
        // shift all elements to the left
        for (i = i + 1; i < n && a[i] != NULL; i++) {
            a[i - 1] = a[i];
        }
        a[i - 1] = NULL;
    }
    return formDeleted; // return 1 if the form was deleted, 0 otherwise
}


