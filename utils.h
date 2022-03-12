/* Popescu Ioana-Maria - 314CB */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#ifndef _DOWNLOAD_RESOURCE_
#define _DOWNLOAD_RESOURCE_

#define MAX_LINE			256
#define MAX_RESOURCES		12
#define BW					1024
#define SEC					1

/* DEF COADA */

#define IC(a)			(((AQ)(a))->ic)
#define SC(a)			(((AQ)(a))->sc)
#define DIMEQ(a)		(((AQ)(a))->dime)
#define VIDAQ(a)		(IC(a) == NULL && SC(a) == NULL)

/* DEF STIVA */

#define VF(a)			(((ASt)(a))->vf)
#define DIMEST(a)		(((ASt)(a))->dime)
/*
	downloaded_size can be used to save the currently downloaded size;
	by default downloaded_size is set to 0
*/

typedef struct celst															/* Struct Celula Stiva */
{ 
	struct celst *urm;
	void* info;
} TCelSt, *ACelSt;

typedef struct stiva															/* Struct Stiva */
{ 
	size_t dime;
	ACelSt vf;
} TStiva, *ASt;

typedef struct cel																/* Struct Celula Coada */
{ 
	struct cel * urm;
	void* info;       
} TCel, *ACel;

typedef struct coada															/* Struct Coada */
{ 
	size_t dime;
 	ACel ic, sc;
} TCoada, *AQ;

typedef struct																	/* Struct Resursa */
{
    char name[100];
    unsigned long dimension;
    unsigned long currently_downloaded;
} Resource;


typedef struct																	/* Struct Pagina Web */
{
	char url[25];
	int num_res;
	Resource* resources;
} WebPage;

typedef struct																	/* Structura Tab */
{
	WebPage* current_page;
	TStiva* back_stack;
	TStiva* forward_stack;
} Tab;

typedef struct lista 															/* Structura Lista de tip Tab */
{
	Tab* tabs;
	struct lista *urm;
} CelLista, *ListaTabs;

Resource* get_page_resources(const char *URL_Name, int *n);



/* COADA */

void* AlocCelQ();
void* AlocQ(size_t e);
int IntrQ(void *c, void *ae);
int ExtrQ(void *a, void *ae);

/* STIVA */

void* AlocCelSt();
void* AlocSt(size_t e);
void Pop(void* s, void* ae);
void Push(void* s, void* ae);

/* TAB */

ListaTabs AlocCelula();
ListaTabs Adauga(ListaTabs* L, ListaTabs el);
ListaTabs newtab(ListaTabs L);
ListaTabs deltab(ListaTabs L, ListaTabs p);
ListaTabs change(ListaTabs L, FILE *in);
void PrintTabs(ListaTabs L, FILE* out);

/* WEB PAGE */

WebPage* AlocaWP(char* url);
void go_to(ListaTabs L, FILE* in, TCoada* history);
void back(ListaTabs L,FILE* out);
void forward(ListaTabs L, FILE* out);
void history(TCoada* history, FILE* out);
void del_history(TCoada* history, FILE* in);

/* DOWNLOADS */

void list_dl(ListaTabs L, FILE* out);
void download(ListaTabs L, TCoada* dl, FILE* in);
void downloads(TCoada* dl, FILE* out);
void avans_dl(TCoada* dl, int band, int sec);
void wait(TCoada* dl, int band, FILE* in);
int set_band(FILE* in);

#endif /* _DOWNLOAD_RESOURCE_ */