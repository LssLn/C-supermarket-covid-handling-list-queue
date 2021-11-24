/*
Sviluppo di applicazione desktop in ANSI C per gestire la coda di accesso ad
un supercomercato durante l'emergenza COVID-19.
Ogni cliente inserisce un nickname, l'ora di arrivo nel formato "HH:MM", che viene salvato
in una coda.

Il gestore del supermercato attiva la funzione accetando l'ingresso dell'utente che viene
copiato nella lista delle persone entrate agggiungendo l'ora di inggresso

I dati dei clienti in attesa sono inialmente caricati dal file "archivio.dat"

implementare le seguenti funzioni:
1. carica_clienti_da_file
2. inserisci un nuovo cliente in coda
3. accetta n persone in ingresso estraendo i dati dalla coda ed inserendoli nella lista, ed inserisce un valore da 1
	a 5 che rappresenta un giudizio sul servizio di attesa
4. calcola il tempo medio di attesa
5. restituisce un vettore in cui ogni elemento contiene il numero di clienti che hanno espresso il giudizio corrispondente
	all'indice + 1
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DIMENSIONE_STRINGA 128
#define NOME_ARCHIVIO "archivio.dat"

typedef struct s_cliente {
	char nickname[DIMENSIONE_STRINGA];
	char tempo_ingresso[8];
	char tempo_uscita[8];
	int giudizio;
} t_cliente;
typedef struct s_nodo_sequenza {
	t_cliente info;
	struct s_nodo_sequenza* successivo;
} t_nodo_sequenza;
typedef t_nodo_sequenza* t_lista_clienti;
typedef struct {
	t_nodo_sequenza* primo;
	t_nodo_sequenza* ultimo;
} t_coda_clienti;

// La funzione inserisce un elemento in testa alla lista passata come primo parametro e
// restituisce la lista modificata
t_lista_clienti lista_aggiungi(t_lista_clienti lista_clienti, t_cliente cliente) {
	t_nodo_sequenza* aux = (t_nodo_sequenza*)malloc(sizeof(t_nodo_sequenza));
	if (aux == 0)
		return NULL;
	aux->info = cliente;
	aux->successivo = lista_clienti;
	return aux;
}

// la funzione restituice vero se la coda e' vuota
int coda_vuota(t_coda_clienti coda) {
	return (coda.primo == NULL);
}
// La funzione inserisce un elemento in coda 
void coda_aggiungi(t_coda_clienti* pt_coda, t_cliente cliente) {
	t_nodo_sequenza* aux = (t_nodo_sequenza*)malloc(sizeof(t_nodo_sequenza));
	if (aux == 0)
		return NULL;

	aux->info = cliente;
	aux->successivo = NULL;
	// aggiungere il codice necessario a completare l'aggiunta di un elemento alla coda
	// devo differenziare 2 casi: coda vuota, coda non vuota
	if (coda_vuota(*pt_coda)) { // si aspetta una coda, non un puntatore : *coda* = coda
		pt_coda->primo = pt_coda->ultimo = aux;
	}
	else {
		pt_coda->ultimo->successivo = aux;
		pt_coda->ultimo = aux; //non devo dimenticarlo per
	}
}

// la funzione restituisce il primo elemento della coda. L'elemento non viene
// cancellato dalla coda.
// Se la coda è vuota restituisce NULL
t_cliente* coda_primo_elemento(t_coda_clienti coda) {
	if (coda_vuota(coda))
		return NULL;
	return &(coda.primo->info);
}

// la funzione cancella il primo elemento della coda. 
void coda_cancella_elemento(t_coda_clienti* pt_coda) {
	t_nodo_sequenza* aux = pt_coda->primo;
	if (coda_vuota(*pt_coda))
		return;
	if (pt_coda->primo == pt_coda->ultimo)
		pt_coda->primo = pt_coda->ultimo = NULL;
	else
		pt_coda->primo = pt_coda->primo->successivo;

	free(aux);
}

// funzioni utili per il calclo del tempo
// la funzione converti_ora, data un tempo espresso nel formato "HH:MM" restituisce 
// un valore intero che rappresenta i minuti passati dalla mezzanotte (ore 00:00)
int converti_ora(const char* tempo) {
	int ore, minuti;
	sscanf(tempo, "%d:%d", &ore, &minuti);
	return ore * 60 + minuti;
}
//
// la funzione carica i dati dal file passato come parametro e restituisce il
// numero di record letti
// lo studente implementi il corpo ella funzione
int carica_clienti_da_file(t_coda_clienti* pt_clienti, FILE* f) {
	t_cliente c;
	c.giudizio = 0;
	int contatore = 0;
	if (f == NULL)
		return 0;
	while (fscanf(f, "%s%s", c.nickname, c.tempo_ingresso) == 2) {
		coda_aggiungi(pt_clienti, c);
		++contatore;
	}
	return contatore;
}
// la funzione calcola il tempo medio di attesa dei clienti 
// numero di record letti
// lo studente implementi il corpo della funzione
float calcolo_tempo_medio(t_lista_clienti clienti) {
	// da fare
	float calcolo_tempo_medio(t_lista_clienti clienti) {
		int tempo_uscita_minuti = 0;
		int tempo_ingresso_minuti = 0;
		int somma_tempi_attesa = 0;
		int numero_elementi = 0;
		while (clienti != NULL) {
			tempo_ingresso_minuti = converti_ora(clienti->info.tempo_ingresso);
			tempo_uscita_minuti = converti_ora(clienti->info.tempo_uscita); //quando lo abbiamo assegnato??????
			somma_tempi_attesa += tempo_uscita_minuti - tempo_ingresso_minuti;
			++numero_elementi;
			clienti = clienti->successivo;
		}
		if (numero_elementi == 0)
			return 0.0;
		return ((float)somma_tempi_attesa) / numero_elementi;
	}
}
// la funzione rstituisce un vettore in cui ogni elemento contiene la somma delle
// persone che hanno espresso un giudizio pari all'indice + 1
// Lo studente deve scegliere i parametri corretti ed implementare il corpo della funzione
void sommario_giudizi() {
	// da fare
}

int main(void) {
	int scelta;
	t_lista_clienti clienti_serviti = NULL;
	t_coda_clienti clienti_attesa = { NULL, NULL };
	FILE* file_archivio = NULL;
	int numero_clienti;
	char buffer[128];
	t_cliente cliente; //lo definisco puntatore? perchè così posso modificare subito i parametri
	// dallo scanf? no! il discorso passaggio per puntatore serve nelle funzioni, non nel main.
	int n;
	char ora[8];
	float tempo_medio;

	file_archivio = fopen(NOME_ARCHIVIO, "r");
	if (file_archivio == NULL) {
		printf("archivio non esistente, non caricato\n");
	}
	else {
		// lo studenti completi il codice inserendo i parametri attuali corretti
		//int carica_clienti_da_file(t_coda_clienti* pt_clienti, FILE* f)    
		//& perchè coda è def come coda semplice, devo passare un puntatore (modifica la coda)
		numero_clienti = carica_clienti_da_file(&clienti_attesa,file_archivio);
		fclose(file_archivio);
		printf("Caricati %d clienti\n", numero_clienti);
	}
	do {
		printf("1. Inserimento cliente\n");
		printf("2. Accettazione clienti\n");
		printf("3. Calcolo tempo medio di attesa\n");
		printf("4. Sommario dei giudizi\n");
		printf("\n0. esci\n");
		printf(">>> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 1: // Inserimento cliente
			// inserire tutto il codice necessario a
			//	1. leggere i dati del cliente dalla console (inserire il valore "" nel campo tempo_uscita
			//	2. inserire il cliente in coda
			printf("\nInserire il nickname : ");
			scanf("%s", cliente.nickname);
			printf("\nInserire l'orario (hh:mm) : ");
			scanf("%s", cliente.tempo_ingresso);
			cliente.giudizio = 0;
			strcpy(cliente.tempo_uscita, "");
			//void coda_aggiungi(t_coda_clienti* pt_coda, t_cliente cliente)
			coda_aggiungi(&clienti_attesa, cliente); 
			//&clienti_attesa perchè devo passare *coda, ma è def come coda, quindi &coda-> arriva un *coda alla funzione
			
			break;
		case 2: // Accettazione clienti
			// inserire tutto il codice necessario a
			//	1. inserire il numero di clienti da accettare (verificare che sia un valore > 0)
			//	2. inserire l'ora corrente
			//	3. estrarre i clienti dalla coda nell'ordine corretto
			//	4. aggiornare il cliente aggiungendo il valore dell'ora corrente e del giudizio dato
			//	5. inserire il cliente nella lista dei clienti serviti
			//	3. stampare il nickname
			printf("\nQuanti clienti devo accettare? ");
			scanf("%d", &n);
			printf("\nChe ora è? (tempo di ingresso hh:mm) : ");
			scanf("%s", ora);
			//DEVO ESTRARRE I CLIENTI DALLA CODA, CIOE' DEVO PRENDERE N VOLTE IL PRIMO IN CODA
			for (int i = 0; i < n; i++) {
				cliente = *coda_primo_elemento(clienti_attesa); // return &(coda.primo->info);
				//siccome la funz mi torna un pt, e cliente non lo è, faccio cliente = *(cliente*)
				//devo modificare i parametri del cliente con l'ora e poi inserirlo
				printf("\nInserire il voto di %s : ", cliente.nickname);
				scanf("%d", &cliente.giudizio);
				//*cliente.tempo_ingresso = ora; //ho messo * perchè mi diceva lvalue deve essere modificabile
				strcpy(cliente.tempo_ingresso, ora);
				//t_lista_clienti lista_aggiungi(t_lista_clienti lista_clienti, t_cliente cliente) {
				clienti_serviti=lista_aggiungi(clienti_serviti, cliente); //&clienti_serviti? no, è def come pt e la f vuole pt...
				//lista_aggiungi mi torna una lista, se non la assegno è inutile
				coda_cancella_elemento(&clienti_attesa);
				//IMPORTANTE! SE NON METTO CODA_CANCELLA INSERISCO N VOLTE LO STESSO ELEMENTO!!!!!!!! 
				//posso metterlo anche dopo cliente=*coda_...
			}

			break;
		case 3: // calcolo del tempo medio di attesa, nota che il supermercato non fa servizio notturno.
			// inserire tutto il codice necessario a chiamare la funzione calcolo_tempo_medio e 
			// stampare il tempo medio di attesa dei clienti
			printf("tempo_medio_attesa %.2f\n", calcolo_tempo_medio(clienti_serviti));
			break;
		case 4: // calcolo del giudizio
			// inserire tutto il codice necessario a chiamare la funzione sommario_giudizi e a stampare
			// il vettore risultante
			break;
		case 0: // programma terminato
			break;
		}
	} while (scelta != 0);
}