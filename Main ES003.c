/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi è
                un bit di parità (1 se il numero di bit a 1 fra i precedenti n è
                dispari), verificare se vi sono errori.


                PASSARE AL CONTROLLO BIT A BIT , NON INTERO VALORE DEL VETTORE . CORREGGERE !
                VERIFACARE DI CONTROLLARLI DA MENO SIGNIFICATIVO AL PIU SIGNIFICATIVO


                len = 50 n = 4
                vet={0x98,0xF9,0xAC,0x46,0x79,0x77,0x03}
                errori = 1
 ********************************************************************************/

#include <stdio.h>

void main()
{
  /*
    // Input
    unsigned char vet[] = { 152,249,172,70,121,119,3 };
    unsigned int len = 50;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
  */  
   /*
    // Input
    unsigned char vet[] = { 141,43,60,43,33,65,232 };
    unsigned int len = 56;	// lunghezza (numero di bit)
    unsigned char n = 7;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
 */
 
    // Input
    unsigned char vet[] = { 2,4,67,2,2,58,99 };
    unsigned int len = 55;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

/*
// Input
    unsigned char vet[] = {18};
    unsigned int len = 7;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
*/
/*
// Input
    unsigned char vet[] = { 227,165,14,146,47,178,0 };
    unsigned int len = 50;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
  */ 
/*
    // Input
    unsigned char vet[] = {123,176,187,211,192,210,211,24,187,79,41,98};
    unsigned int len = 95;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori
*/

    __asm
    {
        XOR EAX, EAX; lo uso per appoggiare il byte prelevato e conteggiare quanti bit ho scorso
        XOR EBX, EBX; Uso BH per capire la posizione rispetto alla lunghezza n data - BL conteggiare gli 1
        XOR ECX, ECX; uso per scorrere il byte preso fino a consumarlo
        XOR EDX, EDX; indice di posizione nel vettore dato

        JMP Primobyte

        Nuovobyte : INC DL; per l iserimento del nuovo byte incremento l indice
                        
            Primobyte : 
             XOR CL, CL
            MOV CL, 8; Punto di partenza del programma
            XOR AL, AL
            MOV AL, vet[EDX]; sposto il byte successivo in AL     

        Ciclo:  
                    INC AH
                    TEST AL, 1; verifico se è a 1 o a 0   
                    JZ Salto; se è a 0 zero non incremento bx
                    INC BL      
              Salto:    
                    INC BH
                        CMP BH, n; verifico se ho controllato 4 bit nel caso passo alla verifica del 5o bit
                        JE Verifica
                        SHR AL, 1; scorro al bit successivo da analizare
                        loop Ciclo; uso un loop per decrementare cx

                        ROR EAX, 8; verifico che se sono in fondo al vettore
                        CMP EAX, len; comparo i bit analizzati con il quantitativo massimo di bit
                        JAE FineCorretto
                        ROL EAX, 8
                        JMP Nuovobyte; se non sono arrivato in fondo al vettore riparto il ciclo prelevando un nuovo byte

               Verifica : 
                    DEC CL
                        SHR AL, 1
                        CMP CL, 0; verifico se sono in fondo al byte nel caso carico in ax il nuovo valore
                            JNE Continua1

                            INC DL
                            XOR CL, CL
                            MOV CL, 8
                            XOR AL, AL
                            MOV AL, vet[EDX]; sposto il byte successivo in AL
                            
                        
              Continua1 : 
                    TEST BL, 1; verifico il valore del bit meno significativo di BL
                        JZ Pari
                        INC AH
                        TEST AL, 1; caso dispari verifico il corrispondente bit meno significativo in  AL
                        JZ FineErrore; se diverso da 0 fermo il programma e segnalo errore
                        XOR BX, BX
                        JMP Scorrimento;salto alla funzione per continuare a scorerere i bit

                        Pari : ;caso pari verifico il corrispondente bit in  AL
                        INC AH
                        TEST AL, 1
                        JNZ FineErrore; se diverso da 1 fermo il programma e segnalo errore
                        XOR BX, BX
                        JMP Scorrimento;salto alla funzione per continuare a scorerere i bit

                        Scorrimento : SHR AL, 1;scorro il bit successivo a quello di verifica per ripartire il ciclo di verifica

                        MOV BL, AL; verifico che se sono in fondo al vettore; verifico se sono in fondo al vettore
                        SHR EAX, 8
                        CMP EAX, len; comparo i bit analizzati con il quantitativo massimo di bit
                        JAE FineCorretto
                        SHL EAX , 8
                        MOV AL , BL
                        XOR BL , BL
                        
                        DEC CL
                        CMP CL, 0
                        JE Nuovobyte; verifico se sono in fondo al byte nel caso carico in ax il nuovo valore
                        JMP Ciclo


                        FineErrore : MOV errori, 1
                JMP Fine

              FineCorretto: MOV errori , 0

                Fine:

  
    }
    
    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
}

