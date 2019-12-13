#include <stdio.h>
#include <string.h>
 
#define STATES  99
#define SYMBOLS 20
 
int N_symbols;  
int N_DFA_states; 
char *DFA_finals;
int DFAtab[STATES][SYMBOLS];
 
char StateName[STATES][STATES+1];
 
int N_optDFA_states;
int OptDFA[STATES][SYMBOLS];
char NEW_finals[STATES+1];
 
void printDfaTable(int tab[][SYMBOLS], int nstates, int nsymbols, char *finals)
{
    int i, j;

	printf("States :");
    for(i=0;i<nstates-1;i++)
    	printf(" %c,", 'A'+i);
    printf(" %c", 'A'+i);
    printf("\n");
    
	printf("Input Symbols :");
    for(i=0;i<nsymbols-1;i++)
    	printf(" %d,", i);
    printf(" %d ", i);
    printf("\n");

    puts("\nDFA: STATE TRANSITION TABLE");
 
    printf("     | ");
    for (i = 0; i < nsymbols; i++) 
		printf("  %c  ", '0'+i);
 
    printf("\n-----+--");
    for (i = 0; i < nsymbols; i++)
		printf("-----");
    printf("\n");
 
    for (i = 0; i < nstates; i++) 
	{
        printf("  %c  | ", 'A'+i);  /* state */
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", tab[i][j]);    /* next state */
        printf("\n");
    }
    printf("Final states = %s\n", finals);
}
 
void loadDfaTable()
{
 	int i;
    DFAtab[0][0] = 'B'; DFAtab[0][1] = 'C';
    DFAtab[1][0] = 'E'; DFAtab[1][1] = 'F';
    DFAtab[2][0] = 'A'; DFAtab[2][1] = 'A';
    DFAtab[3][0] = 'F'; DFAtab[3][1] = 'E';
    DFAtab[4][0] = 'D'; DFAtab[4][1] = 'F';
    DFAtab[5][0] = 'D'; DFAtab[5][1] = 'E';
 
    DFA_finals = "EF";
    N_DFA_states = 6;
    N_symbols = 2;
    
}
 
//get next state string corresponding to given current state string as argument
void getNextState(char *nextstates, char *cur_states, int dfa[STATES][SYMBOLS], int symbol)
{
    int i, ch;
 
    for (i = 0; i < strlen(cur_states); i++)
    {
    	*nextstates++ = dfa[cur_states[i]-'A'][symbol];
	}
    *nextstates = '\0';
}
 
//gives index of equivalence class in form of 0,1,2.......
char equivClassIndex(char ch, char stnt[][STATES+1], int n)
{
    int i;
 
    for (i = 0; i < n; i++)
        if (strchr(stnt[i], ch)) return i+'0';
        
    // next state is NOT defined 
    return -1;  
}
 
/*
    Check if all the next states belongs to same equivalence class.
    Return values:
        If next state is NOT unique, return 0.
        If next state is unique, return next state --> 'A/B/C/...'
    's' is a '0/1' string: state-id's
*/
char uniqueNextState(char *s)
{
    char equiv_class;   /* first equiv. class */
 
    while (*s == '@') s++;
    equiv_class = *s++; /* index of equiv. class */
 
    while (*s) {
        if (*s != '@' && *s != equiv_class) return 0;
        s++;
    }
 
    return equiv_class; /* next state: char type */
}
 
int stateIndex(char *state, char stnt[][STATES+1], int n, int *pn, int cur)  
{
    int i;
    char state_flags[STATES+1]; /* next state info. */
 
    if (!*state) 
		return -1; /* no next state */
 
    for (i = 0; i < strlen(state); i++)
        state_flags[i] = equivClassIndex(state[i], stnt, n);
    state_flags[i] = '\0';
 
    printf("   %d:[%s]\t--> [%s] (%s)\n",
        cur, stnt[cur], state, state_flags);
 
    if (i=uniqueNextState(state_flags))
        return i-'0';   /* deterministic next states */
    else {
        strcpy(stnt[*pn], state_flags); /* state-division info */
        return (*pn)++;
    }
}
 
/*
    Divide DFA states into finals and non-finals.
*/
int initEquivClass(char statename[][STATES+1], int n, char *finals)
{
    int i, j;
 
    if (strlen(finals) == n) {  /* all states are final states */
        strcpy(statename[0], finals);
        return 1;
    }
 
    strcpy(statename[1], finals);   /* final state group */
 
    for (i=j=0; i < n; i++) {
        if (i == *finals-'A') {
            finals++;
        } else statename[0][j++] = i+'A';
    }
    statename[0][j] = '\0';
 
    return 2;
}
 
 
int getOptimizedDfa(char stnt[][STATES+1], int n, int dfa[][SYMBOLS], int n_sym, int newdfa[][SYMBOLS])
{
	int i,x=0;
	for(i=0;i<n;i++)
    	x++;
    
    for(i=0;i<n_sym;i++)
	    x++;
    
    int n2=n;       
    int j;
    char nextstate[STATES+1];
 
    for (i = 0; i < n; i++) {    /* for each pseudo-DFA state */
        for (j = 0; j < n_sym; j++) {    /* for each input symbol */
            getNextState(nextstate, stnt[i], dfa, j);
            newdfa[i][j] = stateIndex(nextstate, stnt, n, &n2, i)+'A';
        }
    }
 
    return n2;
}
 
void charAppend(char *s, char ch)
{
    int n=strlen(s);
 
    *(s+n) = ch;
    *(s+n+1) = '\0';
}
 
void sort(char stnt[][STATES+1], int n)
{
    int i, j;
    char temp[STATES+1];
 
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (stnt[i][0] > stnt[j][0]) {
                strcpy(temp, stnt[i]);
                strcpy(stnt[i], stnt[j]);
                strcpy(stnt[j], temp);
            }
}

int splitEquivClass(char stnt[][STATES+1], int i1, int i2, int n, int n_dfa)  // number of source DFA entries 
{
    char *old=stnt[i1], *vec=stnt[i2];
    int i, n2, flag=0;
    char newstates[STATES][STATES+1];   
 
    for (i=0; i < STATES; i++) newstates[i][0] = '\0';
 	int news[n_dfa];
    for (i=0; vec[i]; i++)
        charAppend(newstates[vec[i]-'0'], old[i]);
 
    for (i=0, n2=n; i < n_dfa; i++) {
        if (newstates[i][0]) {
            if (!flag) 
			{    
                strcpy(stnt[i1], newstates[i]);
                flag = 1;   
            } else  // newstate is appended in 'stnt' 
                strcpy(stnt[n2++], newstates[i]);
        }
    }
 
    sort(stnt, n2); 
 
    return n2;  
}
 
/*
    Equiv. classes are segmented and get NEW equiv. classes.
*/
int setNewEquivClass(char stnt[][STATES+1], int n, int newdfa[][SYMBOLS], int n_sym, int n_dfa)
{
    int i, j, k;
 	int news[n_dfa];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n_sym; j++) {
            k = newdfa[i][j]-'A';   
            if (k >= n)  
                return splitEquivClass(stnt, i, k, n, n_dfa);
        }
    }
 
    return n;
}
 
void printEquivClasses(char stnt[][STATES+1], int n)
{
    int i;
 
    printf("\nEQUIV. CLASS CANDIDATE ==>");
    for (i = 0; i < n; i++)
        printf(" %d:[%s]", i, stnt[i]);
    printf("\n");
}
 
int optimizeDfa(int dfa[][SYMBOLS], int n_dfa, int n_sym, char *finals, char stnt[][STATES+1], int newdfa[][SYMBOLS])  // reduced DFA table 
{
	int news[n_dfa];
    char nextstate[STATES+1];
    int n;  // number of new DFA states 
    int n2; // 'n' + <num. of state-dividing info> 
 
    n = initEquivClass(stnt, n_dfa, finals);
 
    while (1) {
        printEquivClasses(stnt, n);
        n2 = getOptimizedDfa(stnt, n, dfa, n_sym, newdfa);
        if (n != n2)
            n = setNewEquivClass(stnt, n, newdfa, n_sym, n_dfa);
        else break; // equiv. class segmentation ended!!! 
    }
 
    return n;   
}
 
//    Check if 't' is a subset of 's'.
int isSubset(char *s, char *t)
{
    int i;
 
    for (i = 0; *t; i++)
        if (!strchr(s, *t++)) return 0;
    return 1;
}
 
//    New finals states of reduced DFA.
void get_NEW_finals( char *newfinals, char *oldfinals, char stnt[][STATES+1], int n)  /* number of states in 'stnt' */
{
    int i;
 
    for (i = 0; i < n; i++)
        if (isSubset(oldfinals, stnt[i])) *newfinals++ = i+'A';
    *newfinals++ = '\0';
}
 
int main()
{
    loadDfaTable();
    
	printDfaTable(DFAtab, N_DFA_states, N_symbols, DFA_finals);
 
    N_optDFA_states = optimizeDfa(DFAtab, N_DFA_states, N_symbols, DFA_finals, StateName, OptDFA);
    
	get_NEW_finals(NEW_finals, DFA_finals, StateName, N_optDFA_states);
 
    printDfaTable(OptDFA, N_optDFA_states, N_symbols, NEW_finals);
    return 0;
}
