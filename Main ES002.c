
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all’interno di array
              monodimensionali. Gli elementi delle matrici sono da considerarsi
              con segno (in complemento a due).
 ********************************************************************************/

#include <stdio.h>


void main()
{
 /*
    unsigned int m = 3; // numero di righe della prima matrice
    unsigned int n = 2; // numero di colonne della prima matrice
    unsigned int k = 4; // numero di colonne della seconda matrice
    short int mat1[] = { -1,-2, 4,5, 4,-2 }; // prima matrice
    short int mat2[] = { 2,0,0,0, 0,2,0,0 }; // seconda matrice
    int mat3[1024]; // matrice risultato
  */
 
    unsigned int m = 1; // numero di righe della prima matrice
    unsigned int n = 1; // numero di colonne della prima matrice
    unsigned int k = 1; // numero di colonne della seconda matrice
    short int mat1[] = { -70 }; // prima matrice
    short int mat2[] = { 20000 }; // seconda matrice
    int mat3[1024]; // matrice risultato
 
/*
    unsigned int m = 3; // numero di righe della prima matrice
    unsigned int n = 4; // numero di colonne della prima matrice
    unsigned int k = 3; // numero di colonne della seconda matrice
    short int mat1[] = { -7 , 5 ,5,4,
        8 ,5,5,4,
        7,-6,7,4,
    }; // prima matrice
    short int mat2[] = { -7 , -6 ,4 ,
        -6,5,6,
    5,7,-9,
    5,8,-9 }; // seconda matrice
    int mat3[1024]; // matrice risultato
 */
/*
   unsigned int m = 10; // numero di righe della prima matrice
   unsigned int n = 10; // numero di colonne della prima matrice
   unsigned int k = 10; // numero di colonne della seconda matrice
   short int mat1[] = { 95,-27,-30,-29,42,70,-86,-59,-54,20,
53,-47,90,90,77,-49,-24,77,37,7,
-1,-45,30,-94,-26,-57,-94,-62,-12,82,
11,77,-43,-85,35,-28,58,11,-71,-77,
50,-5,-75,35,36,47,48,-70,-64,-78,
- 10,-50,-48,-83,-69,39,42,-37,97,-2,
64,75,53,-37,-92,76,95,75,-46,5,
-8,65,47,14,56,-97,-70,95,-31,26,
-5,75,-98,-34,-9,-39,24,-60,84,95,
30,-5,14,30,-42,75,42,61,27,60 }; // prima matrice
   short int mat2[] = { 95,-27,-30,-29,42,70,-86,-59,-54,20,
53,-47,90,90,77,-49,-24,77,37,7,
-1,-45,30,-94,-26,-57,-94,-62,-12,82,
11,77,-43,-85,35,-28,58,11,-71,-77,
50,-5,-75,35,36,47,48,-70,-64,-78,
-10,-50,-48,-83,-69,39,42,-37,97,-2,
64,75,53,-37,-92,76,95,75,-46,5,
-8,65,47,14,56,-97,-70,95,-31,26,
-5,75,-98,-34,-9,-39,24,-60,84,95,
30,-5,14,30,-42,75,42,61,27,60 }; // seconda matrice
   int mat3[1024]; // matrice risultato
 */
    /*
    unsigned int m = 9; // numero di righe della prima matrice
    unsigned int n = 9; // numero di colonne della prima matrice
    unsigned int k = 9; // numero di colonne della seconda matrice
    short int mat1[] = { 95,-27,-30,-29,42,70,-86,-59,-54,
 53,-47,90,90,77,-49,-24,77,37,
 -1,-45,30,-94,-26,-57,-94,-62,-12,
 11,77,-43,-85,35,-28,58,11,-71,
 50,-5,-75,35,36,47,48,-70,-64,
 -10,-50,-48,-83,-69,39,42,-37,97,
 64,75,53,-37,-92,76,95,75,-46,
 -8,65,47,14,56,-97,-70,95,-31,
 -5,75,-98,-34,-9,-39,24,-60,84,}; // prima matrice
    short int mat2[] = { 95,-27,-30,-29,42,70,-86,-59,-54,
 53,-47,90,90,77,-49,-24,77,37,
 -1,-45,30,-94,-26,-57,-94,-62,-12,
 11,77,-43,-85,35,-28,58,11,-71,
 50,-5,-75,35,36,47,48,-70,-64,
 -10,-50,-48,-83,-69,39,42,-37,97,
 64,75,53,-37,-92,76,95,75,-46,
 -8,65,47,14,56,-97,-70,95,-31,
 -5,75,-98,-34,-9,-39,24,-60,84,}; // seconda matrice
    int mat3[1024]; // matrice risultato
    */
    __asm
    {
        XOR EAX, EAX
        XOR EBX, EBX
        XOR ECX, ECX
        XOR EDX, EDX


        MOV ECX, m
        IMUL ECX, k
        Inizializza : ; inizializzo la matrice destinazione a 0 in base alla grandezza della matrice distinazione
        MOV mat3[ECX * 4], 0
        loop Inizializza
        MOV mat3[0], 0

        JMP Molt; Salto assoluto per iniziare il programma dentro Molt


        Negativo : ; funzione per correggere i bit mancanti nel restante del registro 32bit nel caso il mio valore sia negativo
        ROR EDX, 15
        TEST EDX, 1b
        JE Finetest; salto solo se il numero in esame è uguale ad 1
        ROR EDX, 1
        MOV DX, 1111111111111111b; aggiungo gli 1 nella meta del registri mancante
        ROL EDX, 1
        Finetest: ROL EDX, 15
        RET

             Cambiorigamat1 : ;Salto che mi permette di spostarmi nella riga successiva della mat1
            XOR EDX, EDX
            XOR CX,CX
           
            ROR ECX, 16 ; cambio la posizione nella matrice destinazione mat3
            INC ECX
            ROL ECX, 16
           
            SHR EAX, 16; Uso il restante del registr EAX per segnare gli indici di scorrimento
            XOR AL, AL; Azzero Al che è il mio indice per scorrere orizontamlente la riga della mat1
            XOR EDX, EDX
            MOV DL, AH; incremneto AH che è il mio indice per posizionarmi nel primo valore della riga successiva della mat1
            ADD EDX , n
            MOV AH , DL
            SHL EAX, 16;
            JMP Molt; Fine Fuzione Cambiorigamat1

            Cambiocolonnamat2 : ; Funzione per scorrere le colonne della mat2 
            XOR EDX , EDX 
            MOV EDX , n
            DEC EDX
            IMUL EDX , k
             
            SUB ECX, EDX; Decremento ECX e lo riporto allo stato iniziale
            INC ECX;
            XOR EDX ,EDX

            ROR ECX, 16; cambio la posizione nella matrice destinazione mat3
            INC ECX
            ROL ECX, 16

            SHR EAX, 16;
            XOR AL , AL; Azzero Al che è il mio indice per scorrere orizontalente la riga della mat1
            SHL EAX, 16;
            JMP Molt; Fine Fuzione Cambiocolonnamat2

                Cambiocolonnamat1 : ; Funzione per moltiplicare il valore successivo di mat1 con quella della riga successiva di mat2
                ADD ECX, k; incremento ECX


            Molt:;creo un ciclo per moltiplicare un valore con un altro delle matrici e lo scrivo in mat3

                XOR EDX, EDX; uso EDX come registro temp
                XOR AX, AX
                XOR BX, BX

                ROR ECX, 16; recupero l indice di di posizione nella mat2
                MOV AX, CX
                SHR ECX, 16

                MOV BX, mat2[ECX * 2]; copio il valore in BX di mat2

                ROR ECX, 16; sistemo il registro ECX come prima
                MOV CX, AX
                ROL ECX , 16
                XOR AX, AX

                MOV DX , BX
                Call Negativo; verifico se il numero inserito è negativo
                MOV EBX , EDX
                XOR EDX ,EDX

            SHR EAX, 16;
            MOV DL, AH; recupero gli indici di posizionamento della mat1

                ADD DL, AL; Sommo la posizione attuale nella riga
                
             SHL EAX, 16;
              
            MOV AX, mat1[EDX * 2]; scrivo i valori da moltiplicare delle matrici nei miei registri 16bit

                XOR EDX, EDX

                MOV DX, AX

                Call Negativo; verifico se il numero inserito è negativo
                IMUL EDX, EBX

                XOR AX, AX
                MOV AX, CX; salvo il valore della parte bassa di cx in ax

                SHR ECX, 16; uso il restante del registro per segnare l avanzamento nella matrice destinazione
                
                ADD mat3[ECX * 4], EDX; sommo il valore ottenuto al mio valore destinazione in mat3

                SHL ECX, 16; riposizione il registro ECX

                MOV CX , AX

             SHR EAX, 16;
            INC AL; incremente al per scorrere la riga mat1
        XOR EDX, EDX
        MOV DL , AL 
    SHL EAX, 16;

        CMP EDX, n; verifico se ho scorso tutta la riga di mat1 in esame e se no mi sposto e ripeto il giro
            JB Cambiocolonnamat1

            XOR EDX, EDX
            MOV EDX, n
            IMUL EDX, k
            DEC EDX
            CMP CX, DX
            JB Cambiocolonnamat2; ; verifico se ho scorso tutte le colonna di mat2 in esame e se si no mi sposto di colonna fino a fine matrice

            SHR EAX, 16;
            XOR EDX, EDX
            MOV DL, AH
            SHL EAX, 16;
            XOR EBX, EBX
            MOV EBX, m
            IMUL EBX, n; verifico se sono arrivato in fondo al vettore mat1
            ;INC EDX
            CMP EDX, EBX
            JB Cambiorigamat1; verifico se ho scorso tutte le righe di mat1 in esame e se si no mi sposto di riga fino a fine matrice

    }


    // Stampa su video
    {
        unsigned int i, j, h;
        printf("Matrice prodotto:\n");
        for (i = h = 0; i < m; i++)
        {
            for (j = 0; j < k; j++, h++)
                printf("%6d ", mat3[h]);
            printf("\n");
        }
    }
}


