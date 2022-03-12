/* Popescu Ioana-Maria - 314CB */
#include "utils.h"

void* AlocCelSt()																/* Aloacare celula stiva */
{
	ACelSt aux = (ACelSt)malloc(sizeof(TCelSt));
	if(!aux)
		return NULL;

	aux->urm = NULL;
	aux->info = NULL;

	return aux;
}

void* AlocSt(size_t e)															/* Alocare stiva */
{
	ASt aux = (ASt)malloc(sizeof(TStiva));
	if(!aux)
		return NULL;

	aux->vf = NULL;
	aux->dime = e;

	return (void*)aux;
}

void Pop(void* s, void* ae)														/* Scoate primul elem din stiva */
{
	if( VF(s) == NULL) 
		return ;

	memcpy(ae, VF(s)->info, DIMEST(s));
	ACelSt aux = VF(s);
	VF(s) = aux->urm;
}

void Push(void* s, void* ae)													/*  Adauga elem la finalul stivei */
{
	ACelSt aux = (ACelSt)calloc(1, sizeof(TCelSt));
	if(!aux) return ;

	aux->info = calloc(1, DIMEST(s));
	memcpy(aux->info, ae, DIMEST(s));

	aux->urm = VF(s);
	VF(s) = aux;
}