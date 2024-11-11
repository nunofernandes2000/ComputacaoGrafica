//
// Created by Nuno Fernandes on 22/10/2024.
//

#ifndef __DBFORM_H__
#define __DBFORM_H__

#include "form.h"

void initDBForms(int num);
void populateDBForms(int maxSize);
int insertBDForm(Form f);
void deleteRandomDBForm();
void drawDBForms();
void printDBForms();


//functions to delete a form from the array (Pergunta 3 da ficha 4)
int deleteFormDB(Form f);



Form pickDBForm(float x, float y);





#endif