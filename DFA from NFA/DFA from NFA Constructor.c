#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#define SDFA struct DFA * 
#define INT_BOUND  100 
#define NT NFA_TABLE
#define num 65

int ind_count  = 0;  
int inputs; 

typedef struct DFA { 
	char *state_name ; 
	int number ; 
}dfa; 

void fillSymbolsInState(int arr[], int size, char string[]) { 
	int j, i = 0; 
	for (int j = 0; j < size; j++) { 
		if (arr[j] != 0) 
			string[i++] = (char)(num + j); 
		} 
	string[i] = '\0'; 
} 

int xed = 0;
void hash(int ar[], char S[]){ 
	int j=0; 
	for (int i = 0; i < strlen(S); i++) { 
		j = ((int)(S[i]) - num); 
		ar[j]++; 
	} 
}
char copy_array [INT_BOUND]; 
 

int retIndexClosure(int arr[], int size) { 
	for (int i = 0; i < size; i++) { 
		if (arr[i] == 1) 
		return i; 
	} 
	return -1; 
} 

void setZero(char *str){
	bzero((void *)str , INT_BOUND ); 
}

int setIndex(SDFA dfa) { 
	for (int i = 0; i < xed; i++) { 
		if (dfa[i].number  == 0) 
		return 1; 
	} 
	return -1; 
} 

void nullify(int arr[], int size) { 
	for (int i = 0; i < size; i++) { 
		arr[i] = 0; 
	} 
} 

void ShowClosureOf(int state_name , int line[], char *CloureTable[], char *NT[][inputs + 1], char *DFA_TABLE[][inputs]) { 
	for (int i = 0; i < state_name ; i++) { 
		nullify(line, state_name ); 
		line[i] = 2; 

		if (strcmp(&NT[i][inputs], "-") != 0) { 
		strcpy(copy_array , &NT[i][inputs]); 
		hash(line, copy_array ); 
		int z = retIndexClosure(line, state_name ); 
		
		while (z != -1) 
		{ 
			if (strcmp(&NT[z][inputs], "-") != 0) { 
				strcpy(copy_array , &NT[z][inputs]); 
				hash(line, copy_array ); 
			} 
			line[z]++; 
			z = retIndexClosure(line, state_name ); 
			}	 
		} 

		printf("e*(%c) : ", (char)(num + i)); 
		setZero(copy_array); 
		fillSymbolsInState(line, state_name , copy_array ); 
		strcpy(&CloureTable[i], copy_array ); 
		printf("%s\n\t", &CloureTable[i]); 
		setZero(copy_array); 
	} 
}  

void cross(char S[], int M, char *clsr_t[], int st, char *NFT[][inputs + 1], char TB[]) { 
	int j,k,arr[st],var; 
	nullify(arr, st); 
	char str[INT_BOUND ], str2[INT_BOUND ]; 
	for (int i = 0; i < strlen(S); i++) { 
		j = ((int)(S[i] - num)); 
		strcpy(str, &NFT[j][M]); 
		if (strcmp(str, "-") != 0) { 
		var = strlen(str); 
		int g = 0; 

		while (g < var) { 
			k = ((int)(str[g] - num)); 
			strcpy(str2, &clsr_t[k]); 
			hash(arr, str2); 
			g++; 
			} 
		} 
	} 

	setZero(str);
	fillSymbolsInState(arr, st, str); 


	if (str[0] != '\0') { 
		strcpy(TB, str); 
	} else
		strcpy(TB, "-"); 
} 

void printDFA(int xed, SDFA dfa_state_name , char *DFA_TABLE[][inputs]) 
{ 
	printf("\nDFA:\n");
	printf("\t\tTRANSITION TABLE\n"); 
	printf("\n\tSTATES :\t\t"); 

	for (int i = 1; i < xed; i++) 
		printf("%s, ", &dfa_state_name [i].state_name ); 
	printf("\n"); 
	printf("\tSYMBOLS: \t"); 

	for (int i = 0; i < inputs; i++) 
		printf("%d, ", i); 
	printf("\n\n"); 
	printf("\tSYMBOLS\t\t"); 

	for (int i = 0; i < inputs; i++) 
		printf("%d\t\t", i); 
	printf("\n"); 
	for (int i = 0; i < ind_count ; i++) { 
		printf("\t%s\t", &dfa_state_name [i + 1].state_name ); 
		for (int j = 0; j < inputs; j++) { 
		printf("\t%s \t", &DFA_TABLE[i][j]); 
		} 
		printf("\n"); 
	} 
} 

int new_state_name (SDFA dfa, char S[]) { 
	int i;  
	for (i = 0; i < xed; i++) { 
		if (strcmp(&dfa[i].state_name , S) == 0) 
			return 0; 
	} 
	strcpy(&dfa[xed++].state_name , S); 
	dfa[xed - 1].number  = 0; 
return 1; 
}

int main() { 
	SDFA dfa_state_name  = malloc(INT_BOUND  * (sizeof(dfa)));
	
	char input[INT_BOUND],output[INT_BOUND];
	printf("Enter the file address to scan input NFA transition table\n");
	scanf("%s",input);
	printf("Enter the file address to print output DFA transition table\n");
	scanf("%s",output);
	freopen(input,"r",stdin);
	freopen(output,"w",stdout);
	
	int i, j, state_name; 
	char copy[INT_BOUND]; 
	
	scanf("%d %d",&state_name ,&inputs);

	printf("\nNFA:\n\tSTATES : "); 
	for (int i = 0; i < state_name ; i++) {
		printf("%c, ", (char)(num + i)); 
	}
	printf("\n\tSYMBOLS : "); 

	for (int i = 0; i < inputs; i++) {
		printf("%d, ", i); 
	}
	printf("epsllon"); 
	printf("\n\t"); 
	char *NT[state_name ][inputs + 1]; 

	char *DFA_TABLE[INT_BOUND ][inputs];
	for(int ko=0;ko<state_name ;ko++){
		for(int k=0;k<=inputs;k++){
			scanf("%s",&NT[ko][k]);
		}		
	} 
	printf("\n\tTRANSITION TABLE : \n"); 
	printf("\tSTATES \t\t"); 

	for (i = 0; i < inputs; i++) 
		printf("%d\t\t", i); 
	printf("eps\n\t"); 
	for (i = 0; i < state_name ; i++) { 
		printf("\t%c\t", (char)(num + i)); 

		for (j = 0; j <= inputs; j++) { 
		printf("\t%s \t", &NT[i][j]); 
		} 
		printf("\n\t"); 
	} 
	int line[state_name ]; 
	char *CloureTable[state_name ]; 
	ShowClosureOf(state_name , line, CloureTable, NT, DFA_TABLE); 
	strcpy(&dfa_state_name [xed++].state_name , "-"); 
	dfa_state_name [xed - 1].number  = 1; 
	setZero(copy_array); 
	strcpy(copy_array , &CloureTable[0]); 
	strcpy(&dfa_state_name [xed++].state_name , copy_array ); 
	int Sm = 1, index= 1; 
	int start_index = 1; 
	while (index!= -1) { 
		dfa_state_name [start_index].number  = 1; 
		Sm = 0; 
		for (i = 0; i < inputs; i++) { 
			cross(copy_array , i, CloureTable, state_name , NT, copy); 
			strcpy(&DFA_TABLE[ind_count ][i], copy); 
			Sm = Sm + new_state_name (dfa_state_name , copy); 
		} 
		index= setIndex(dfa_state_name ); 
		if (index!= -1) 
			strcpy(copy_array , &dfa_state_name [++start_index].state_name ); 
		ind_count ++; 
	} 
	printDFA(xed, dfa_state_name , DFA_TABLE); 
return 0; 
} 
