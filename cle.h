/*
 * cle.h
 *
 *  Created on: 9 déc. 2018
 *      Author: moumouh
 */

#ifndef CLE_H_
#define CLE_H_

typedef unsigned char cle;

cle * parse_cle(char* s);
int eg(cle* a, cle* b);
int inf(cle* a, cle* b);
void print(cle * c);

#endif /* CLE_H_ */
