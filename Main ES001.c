/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 1
 Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
				l'indirizzo a 32 bit del primo carattere della stringa), ordinarlo
				secondo il codice ASCII. Ogni stringa termina con il carattere nullo
				(codice ASCII 0).

 ********************************************************************************/

#include <stdio.h>

void main() {
	/*
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "prova","66ZZZ1","555adfadfas","bsfufdasi","ciao","444ciao" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);
	*/
	
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "a", "ad", "ai", "alle", "altre", "botte", "che", "chioccia", "colori", "contadino", "contadino", "dallaltra", "del", "della", "dellaia", "delle", "Deluso", "di", "di", "di", "dipingerlo", "e", "e", "e", "fare", "galline", "gallo", "gran", "i", "il", "il", "il", "in", "indifferente", "lavori", "le", "le", "lo", "mette", "mezzo", "nascosto", "parte", "pavone", "per", "per", "pero", "Poi", "putiferio", "quando", "Questa", "reazioni", "resta", "riempie", "rimette", "scherzo", "si", "sottrae", "spiare", "sta", "sue", "suoi", "tornarsene", "tutti", "tutto", "Un", "un", "un", "una", "uno", "uova", "uovo", "vede", "vuol" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);
	
	__asm
	{
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX
		XOR EDX, EDX

		MOV ECX, num;
		MOV EDI, strings[0]; sposto l indirizzo del primo e del secondo valore in esi ed edi per iniziare a controllare
		MOV ESI, strings[1 * 4]
		
		JMP ScorriStrighe; inizio programma


		ControlloArray : ; funzione che mi verifica se ho completato tutti i controlli per terminare il programma
		XOR EDX, EDX
		MOV DL, CH
		INC EDX; incremento edx per equipararlo ad num in quanto siamo partiti da 0
			CMP EDX, num
			JE ControlloFine; se uguale a num sono arrivati in fondo al vettore
			XOR EDX, EDX
			RET
			ControlloFine : CMP CL, 0; se sono uguali vuol dire che scorso il vettore lo stesso numero di volte della lunghezza dello stesso
			JE ValFine
			DEC CL
			MOV DL, 2; imposto un valore per determinare il risultato alla fine della funione,se 2 eseguo un nuovo giro del vettore
			JMP Salto
			ValFine : MOV DL, 1;  se 1 ho finito tutti i giri
	Salto: RET
			


NuovoGiro:
		XOR EDX, EDX;ricomincio a controllare il mio vettore riposizionando gli indici all inizio
		XOR CH , CH
		MOV EDI, strings[0]; sposto i primi valori per iniziare il ciclo
		MOV ESI, strings[1 * 4]
		JMP ScorriStrighe


Scambia:
		XOR EAX, EAX
			XOR EBX, EBX
			MOV AL, CL; Sposto il valore di fine ciclo in un temporaneo
			SHR ECX, 8; sposto il registro
			MOV strings[ECX * 4], ESI; scambio i valori
			INC ECX
			MOV strings[ECX * 4], EDI; scambio i valori

			MOV EDI, strings[ECX * 4]; mi sposto nel vettore in avanti
			INC ECX
			MOV ESI, strings[ECX * 4]
			DEC ECX; riporto ecx al valore corrente di controllo
			SHL ECX, 8
			MOV CL, AL; riposizione i valori appoggiati in al

			Call ControlloArray; controllo se ho finito il ciclo
			CMP DL, 1
			JE Fine
			CMP DL, 2
			JE NuovoGiro
			XOR EDX, EDX
			JMP ScorriStrighe; se i controlli sopra non sono soddisfatti continuo a confrontare i valori


			ProssimoCarattere : ; scorro in avanti l indice dei caratteri se i precedenti sono uguali
			CMP AL, 0
			JE NuovaPosizione; Se e uguale  a zero allora entrambi sono uguali a 0 quindi sono uguali le parole
			INC EDX
			JMP ScorriStrighe

			NuovaPosizione : ; funzione per scorrere in vanti i miei puntatori
			XOR EDX, EDX; Azzero il contatore dei caratteri
			XOR EAX, EAX
			XOR EBX, EBX
			MOV AL, CL; Sposto il valore di fine ciclo in un temporaneo
			SHR ECX, 8; sposto il registro
			INC ECX
			MOV EDI, strings[ECX * 4]; mi sposto nel vettore
			INC ECX
			MOV ESI, strings[ECX * 4]
			DEC ECX
			SHL ECX, 8
			MOV CL, AL
			Call ControlloArray; verifico la posizione nel mio vettore
			CMP DL, 1
			JE Fine
			CMP DL, 2
			JE NuovoGiro
			XOR EDX, EDX
			JMP ScorriStrighe


ScorriStrighe:
		MOV AL, [EDI][EDX]; sposto il carattere della prima stringa in al
			;CMP AL, 90; Verifico se e un lettera maiuscola se lo fosse la riporto minuscola per confrontarla con le altre
			;JA Continua1
			;CMP AL, 65
			;JB Continua1
			;ADD AL, 32

Continua1: MOV BL, [ESI][EDX];sposto il carattere della seconda stringa in bl
			;CMP BL, 90; Verifico se e un lettera maiuscola se lo fosse la riporto minuscola per confrontarla con le altre
			;JA Continua2
			;CMP BL, 65
			;JB Continua2
			;ADD BL, 32
			
Continua2:CMP AL, BL
			JE ProssimoCarattere; se sono uguali scorro al carattere successivo
			CMP AL, BL
			JA Scambia; se il primo e maggiore scambio le due stringhe
			JMP NuovaPosizione; se il primo e minore scorro alla prossima stringa da confrontare nel vettore


			Fine:

	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
	}
}
