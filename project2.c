#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct node {
	char word[100];
	int count;
	struct node* next;

} list;

typedef struct nodet {
	char character;
	int count;
	struct nodet* next;

} list2;

void pushBack(list * head1, char* word2);
void alpha(char* word);
void print_list(list* head1);
int checkList(list* head1, char *word2);
void increaseCount(list* head1, char *word2);
void sortList(list* head1, int total, int N,int scaleState);
void prntingGraph(double maxp, int value, double percent, int maxlen, char *word, int maxper);
int maximum(list *head1, int N);
void printLastLine(int maxlen);
int checkListChar(list2* head1, char c);
void pushBackChar(list2 * head1, char c);
void increaseCountChar(list2* head1, char c);
void sortListchar(list2* head1, int total, int N, int scaleState);
void prntingGraphchar(double maxp, int value, double percent, int maxlen, char c, int maxper);
int maxcount(list *head);
int maxcountchar(list2 *head);

int main(int argc, char **argv ){

	//argument handling

	if(argc == 1){
		printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	}

	int m;
	int scaleState = 0, wordState=0, lenval=10, characterState = 0;
	char arg[1000][1000];
	int argcou=0;
	for(m=1; m<argc; m++){
		if(argv[m][0] == '-'){
			if ( strcmp(argv[m], "-w")== 0 ){
				wordState = 1;
			} else if ( strcmp(argv[m], "-c")== 0  ){
				characterState = 1;
			} else if (strcmp(argv[m],"--scaled")== 0 ){
				scaleState = 1;
			} else if ( strcmp(argv[m], "-l")== 0  ){
				if (argc == (m+1)){
					printf("Not enough options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
					return 0;
				}
				int length = strlen (argv[m+1]);
				int g;
				for(g=0;g<length;g++){
					if(!isdigit(argv[m+1][g])){
						printf("Invalid options for [-l]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
						return 0;

					} 
				}
				lenval = atoi(argv[m+1]);
				if(lenval == 0){
					return 0;
				}
				m++;
			} else{
				printf("Invalid option [%s]\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n", argv[m]);
				return 0;
			}
		} else {
			strcpy(arg[argcou], argv[m]);
			argcou++;

		}
		
	}

	if( (wordState==1) && (characterState == 1) ){
		printf("[-c] and [-w] cannot use together\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	} else if ( (wordState==0) && (characterState == 0)){
		wordState = 1;
	}
	
	if(argcou == 0){
		printf("No input files were given\nusage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
		return 0;
	}

	int p;
	for(p=0; p<argcou; p++){
		FILE *f = fopen(arg[p],"r");
		if(f == NULL){
			printf("Cannot open one or more given files\n");
			return 0;
		}
	}

	

	// argument handling


	if (wordState == 1){
		int x;
		char word1[100];
		int i=0;
		list* head = NULL;
		head = (list*)malloc(sizeof(list));

		for(x=0;x<argcou;x++){

			FILE *fp = fopen(arg[x],"r");
			if(fp != NULL){

				
		 
		        while( fscanf(fp, "%s", word1) != EOF ){
		        	int t;
		        	for(t = 0; word1[t] != '\0'; t++){
					    word1[t] = tolower(word1[t]);                //removing other characters and converting to lower case.
					}
		        	alpha(word1);
		            
					if (head != NULL  && strlen(word1)!=0 ) {			
						if(i==0){
							strcpy(head->word, word1);
							head->count = 1;
							head->next = NULL;
							i++;			
						} else{					
							char *p = word1;
							if(checkList(head,p) == 1){      //checkng list
								pushBack(head, p);          // adding items to the list
							} else {
								increaseCount(head, p);     //increasing count
							}
							i++;					
						}			   
					}

		        }
		        

			} else {
				printf("Cannot open one or more given files\n");
				return 0;
			}

		}
		if(i==0){
			printf("No data to process\n");
			return 0;
		}

		sortList(head,i,lenval,scaleState); //sorting and printing list
		        //print_list(head); //printing list
		

	} else if(characterState == 1) {
		
		int x;
		char c;
		int i=0;
		//int total = 0;
		list2* head = NULL;
		head = (list2*)malloc(sizeof(list2));

		for(x=0;x<argcou;x++){

			FILE *fp = fopen(arg[x],"r");
			if(fp != NULL){

				
		 
		        while( fscanf(fp, "%c", &c) != EOF ){
		        	if(isalpha(c) != 0){
		        		c = tolower(c);
		        	}
		            
					if (head != NULL  && (( (c>='a')&&(c<='z') ) || ( (c>='0')&&(c<='9') ) ) ) {			
						if(i==0){
							head->character = c;
							head->count = 1;
							head->next = NULL;
							i++;			
						} else{					
							if(checkListChar(head, c) == 1){      //checkng list
								pushBackChar(head, c);          // adding items to the list
							} else {
								increaseCountChar(head, c);     //increasing count
							}
							i++;					
						}			   
					}

		        }
		        

			} else {
				printf("Cannot open one or more given files\n");
				return 0;
			}

		}
		if(i==0){
			printf("No data to process\n");
			return 0;
		}

		sortListchar(head,i,lenval,scaleState);

	}



 	return 0;	
}


void prntingGraph(double maxp, int value, double percent, int maxlen, char *word, int maxper){
	int i;
	int len = strlen(word);
	int barlen = 80-maxlen-3-maxper;
	int val = percent*barlen/maxp;

	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("\n");


	printf(" %s ", word);
	for(i=0;i<(maxlen-len);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("%.2f%%\n",percent);


	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("\n");

	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	printf("\n");

}

void printLastLine(int maxlen){
	int i;
	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("└");
	for(i=0; i<(80-maxlen-3); i++){
		printf("─");
	}
	printf("\n");
	return;
}


void alpha(char* word) {                             //     ALPHA NUMERIC CHECKING
   while (*word) {
      if (!(*word >= 'a' && *word <= 'z') && !(*word >= '0' && *word <= '9')) {
         strcpy(word, word + 1);
         word--;
      }
      word++;
   }
}

void pushBack(list * head1, char *word2) {        //            ADDING ELEMENTS TO LIST
    list * current = head1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (list*)malloc(sizeof(list));
    strcpy(current->next->word, word2);
    current->next->count = 1;
    current->next->next = NULL;
    return;
}

/*void pushFront(list* head1, char *word2) {
    list * new_node;
    new_node = malloc(sizeof(list));
    strcpy(new_node->word, word2);
    new_node->length = strlen(word2);
    new_node->next = head1;
    head1 = new_node;
}*/

void print_list(list * head1) {    //   PRINTING LIST
    list * current = head1;
    while (current != NULL) {
        printf("%s= %d \n",current->word, current->count);
        current = current->next;
    }
    return;
}

int checkList(list* head1, char *word2){                   // CHECKING LIST
	list * current = head1;
	while (current != NULL){
		if(strcmp(word2, current->word) == 0){
			return 0;
		}
		current = current->next;
	}
	return 1;
}

void increaseCount(list* head1, char *word2){                //   INCREASING COUNT
	list * current = head1;
	while (current != NULL){
		if(strcmp(word2, current->word) == 0){
			current->count = current->count + 1;
			return;
		}
		current = current->next;
	}
}

int maxcount(list *head){
	list* current = head;
	int maxcount = 0;
	while( current != NULL){
		if(current->count > maxcount){
			maxcount = current->count;
		}
		current = current->next;
	}
	return maxcount;
}

int maxcountchar(list2 *head){
	list2* current = head;
	int maxcount = 0;
	while( current != NULL){
		if(current->count > maxcount){
			maxcount = current->count;
		}
		current = current->next;
	}
	return maxcount;
}

void sortList(list* head1, int total, int N, int scaleState){                     //      SORTING LIST
	printf("\n");
	list* current1 = head1;
	double maxp = 100.00;
	if (scaleState == 1){
		maxp = maxcount(head1)*100.00/total;
	}
	
	int q=0, hunState = 0, tenState = 0;
	int maxi = maximum(head1,N);
	while (head1 != NULL){
		// printf("***");
		
		list* current2 = current1->next;
		//printf("***");
		int max = current1->count;
		
		while(current2 != NULL){
			//printf("***");

			
			int c2 = current2->count;
			//printf("%d, %d\n",c1,c2 );

			if(c2>max){
				max = c2;
			}

			current2 = current2->next;
		}

		list* current3 = current1;
		while(current3 != NULL){
			if(current3->count == max && current3->count != 0 ){
				double percentage = (current3->count)*100.00/total;
				//printf("%s = %.2f%%\n", current3->word, percentage);
				if ((int)percentage == 100  || hunState == 1){
					prntingGraph( maxp, strlen(current3->word), percentage, maxi , current3->word,7);
					hunState = 1;
				} else if ((int)percentage >=10  || tenState == 1){
					prntingGraph(maxp,strlen(current3->word), percentage, maxi , current3->word,6);
					tenState = 1;
				} else {
					prntingGraph( maxp,strlen(current3->word), percentage, maxi , current3->word,5);
				}
				
				q++;
				if(q==N){
					printLastLine(maxi);
					return;
				}
				current3->count = 0;
			}
			current3 = current3->next;
		}
		head1 = head1->next;
		//return;
	}
	printLastLine(maxi);
	return;
}


int maximum(list *head1, int N){
	list* current4 = head1;
	int maxco=0;
	while(current4 != NULL){
		if(current4->count > maxco){
			maxco = current4->count;
		}
		current4 = current4->next;
	}
	//return maxlen;
	list* current5 = head1;
	int maxlen=0, j=0;

	while(maxco != 0){
		current5 = head1;
		while(current5 != NULL){
			if(current5->count == maxco){
				if(strlen(current5->word) > maxlen){
					maxlen = strlen(current5->word);
				}
				j++;
				if(j==N){
					return maxlen;
				}
			}
		current5 = current5->next;
		}
		maxco = maxco-1;
		
	}
	return maxlen;
}

int checkListChar(list2* head1, char c){                   // CHECKING LIST CHARACTER
	list2 * current = head1;
	while (current != NULL){
		if(current->character == c ){
			return 0;
		}
		current = current->next;
	}
	return 1;
}


void pushBackChar(list2 * head1, char c) {        //            ADDING ELEMENTS TO LIST CHARACTER
    list2 * current = head1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (list2*)malloc(sizeof(list2));
    current->next->character = c;
    current->next->count = 1;
    current->next->next = NULL;
    return;
}

void increaseCountChar(list2* head1, char c){                //   INCREASING COUNT
	list2 * current = head1;
	while (current != NULL){
		if(current->character == c){
			current->count = current->count + 1;
			return;
		}
		current = current->next;
	}
}

void sortListchar(list2* head1, int total, int N, int scaleState){                     //      SORTING LIST
	printf("\n");
	list2* current1 = head1;
	double maxp = 100.00;
	if(scaleState == 1){
		maxp = maxcountchar(head1)*100.00/total;
	}
	int q=0,hunState=0, tenState=0;
	int maxi =1;
	while (head1 != NULL){
		// printf("***");
		
		list2* current2 = current1->next;
		//printf("***");
		int max = current1->count;
		
		while(current2 != NULL){
			//printf("***");

			
			int c2 = current2->count;
			//printf("%d, %d\n",c1,c2 );

			if(c2>max){
				max = c2;
			}

			current2 = current2->next;
		}

		list2* current3 = current1;
		while(current3 != NULL){
			if(current3->count == max && current3->count != 0 ){
				double percentage = (current3->count)*100.00/total;
				//printf("%c = %.2f%%\n", current3->character, percentage);
				if ((int)percentage == 100  || hunState == 1){
					prntingGraphchar( maxp, 1 , percentage, 1 , current3->character, 7);
					hunState = 1;
				} else if((int)percentage >= 10 || tenState == 1){
					prntingGraphchar(maxp,  1 , percentage, 1 , current3->character, 6);
					tenState =1;
				} else {
					prntingGraphchar( maxp, 1 , percentage, 1 , current3->character, 5);
				}
				
				q++;
				if(q==N){
					printLastLine(maxi);
					return;
				}
				current3->count = 0;
			}
			current3 = current3->next;
		}
		head1 = head1->next;
		//return;
	}
	printLastLine(maxi);
	return;
}

void prntingGraphchar(double maxp, int value, double percent, int maxlen, char c, int maxper){
	int i;
	int len = 1;
	int barlen = 80-maxlen-3-maxper;
	int val = percent*barlen/maxp;

	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("\n");


	printf(" %c ", c);
	for(i=0;i<(maxlen-len);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("%.2f%%\n",percent);


	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	for(i=0;i<val;i++){
		printf("░");
	}
	printf("\n");

	for(i=0;i<(maxlen+2);i++){
		printf(" ");
	}
	printf("│");
	printf("\n");

}