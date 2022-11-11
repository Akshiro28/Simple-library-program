#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <time.h> 
int total = 0;//book total in bookshelf
int genretotal[25]= {0}; // jumlah genre setiap buku
char memberID[100];
int librarytotal; //  jumlah buku dalam database perpustakaan
struct books{
	char title[100];
	char author[50];
	char summary [10005];
	char rating[5];
	char genre[100][100];
}ex[1001];
struct bookshelf{
	int index;
	char title[100];
}bs[1001];
void bookdetails(int z){
	int i;
	printf ("%s\n", ex[z].title);
	printf ("----------------------------------------\n");
	printf ("Author : %s\n", ex[z].author);
	printf ("Rating : %s\n", ex[z].rating);
	printf ("Genre : -");
	for (i=0; i<genretotal[z]; i++) printf (" %s -", ex[z].genre[i]);
	printf ("\nSummary : \n %s\n\n", ex[z].summary);
}
void selectionSort(char num){  
    int i,j;
    char temp [1001];
    int tempindex;
    for (j=0; j<total-1; j++) { 
        for (i=j+1; i<total; i++) { 
        	if (num == '1'){
	            if (strcmp(bs[j].title, bs[i].title) > 0){ 
	            strcpy (temp, bs[j].title);
	            strcpy (bs[j].title, bs[i].title);
	            strcpy (bs[i].title,temp);
	            tempindex = bs[j].index;
	            bs[j].index = bs[i].index;
	            bs[i].index = tempindex;
				}
			}
	        else if (num == '2'){
	        	if (strcmp(bs[j].title, bs[i].title) < 0){ 
	            strcpy (temp, bs[j].title);
	            strcpy (bs[j].title, bs[i].title);
	            strcpy (bs[i].title,temp);
	            tempindex = bs[j].index;
	            bs[j].index = bs[i].index;
	            bs[i].index = tempindex;
				}
	    	}
	        else {
	        	printf("Input Tidak Sesuai\n\n");
	            bookshelf();
	       }
		
		}
    } 
    int k;
    for(k=0; k<total; k++)
	{
     printf("%d. %s\n",k+1, bs[k]. title) ;
    }
}
void bookshelf(){
	printf ("My Bookshelf\n");
	int i;
	printf ("-------------------------------------\n");
	
	//show books in bookshelf
	for (i=0; i < total; i++){
		printf ("%d. %s\n", i+1, bs[i].title);	 
	}
	
	// if there are no books in bookshelf
	if (total == 0) {
		printf ("Your bookshelf is empty \n");
		menu();
	}
	
	//sort book
	else{
	  	int j;
		printf ("\nSort My Bookshelf by: \n1.Ascending 2.Descending 3. Go to menu\n");
		int num;
		fflush (stdin);
		num = getchar();
		system ("cls");
	    if (num == '1')
		   printf("My Bookshelf in Ascending Order\n");
	
		else if (num == '2')
		   printf("My Bookshelf in Descending Order\n");
		
		else if (num == '3') menu();
		else {
			system ("cls");
			printf ("Input tidak sesuai\n");
			bookshelf ();
		}  	
		selectionSort(num);
    }
    // open selected book
    printf ("\nSelect the book you want to read:\n");
	int num;
	scanf ("%d",&num);
	int ada=0;
	for (i=0; i<total; i++){
		if (num == i) ada = 1;	
	}
	if (ada != 1) {
		system ("cls");
		printf ("Input tidak sesuai\n");
		bookshelf ();
	} 
	system ("cls");
	bookdetails(bs[num-1].index);
		printf ("[Press 1 to see other books]\n");
		printf ("[Press 2 to go to bookshelf]\n");
		printf ("[Press 3 to go to menu]\n");
	fflush (stdin);
	num = getchar ();

	if (num == '1'){
		system("cls");
		explore();
	} 
	else if (num == '2'){
		system("cls");
		bookshelf();
	}
	else if (num == '3'){
		system("cls");
		menu();
	}
	else {
		system("cls");
		printf ("Input tidak sesuai\n\n");
		bookshelf();
	}
	
}
void explore(){
	int i, n;
	printf ("Explore\n");
	printf ("----------------------------------------\n");
	printf ("What do you want to read today?\n");
	printf ("Top Picks:\n");
	int arr[1000] = {0};//  how many times a randomized number shows up
	int x[5] = {0};// to save randomized number
	srand(time(NULL));
	//title randomizer
	for (i=0; i<3; i++){
		int r = rand() % librarytotal; 
		// make sure randomized number does not duplicate
		arr[r] ++;
		if (arr[r]>1) i--;
		else{
			printf ("%d. %s\n",i+1, ex[r].title);
			x[i+1] = r;
		} 
	}
	
	printf ("Reshuffle Recommendation?\n1.Yes 2.No 3.Menu\n");
	fflush (stdin);
	n = getchar();
	
	if (n=='1'){
		system("cls");
		explore();
	}
	 
	else if (n == '2') {
		printf ("Select The book you want to read\n");
		int num;
		scanf  ("%d",&num);
		int selectedbook = x[num];
		system("cls");
		bookdetails(selectedbook);
		
		printf ("[Press 1 to add book to your bookshelf]\n");
		printf ("[Press 2 to see other books]\n");
		printf ("[Press 3 to go to menu]\n");
		int y;
		
		fflush (stdin);
		num=  getchar ();
		if (num == '1'){
			//checking if the book is already in the bookshelf
			for (i=0; i<total; i++){
				if (bs[i].index == selectedbook) {
					system("cls");
					printf ("This book is already in your bookshelf\n\n");
					explore();
				}
			}
			// adding book into user bookshelf file
				FILE *fp;
				fp = fopen (memberID, "a+");
				if (total != 0) fprintf (fp, "\n");
				fprintf (fp,"%s\n", ex[selectedbook].title);
				fprintf (fp, "%d", selectedbook);
				bs[total].index = selectedbook;
				strcpy (bs[total].title,ex[selectedbook].title);
				total++;
				fclose (fp);
				system("cls");
				printf ("Book is added to your bookshelf\n\n");
				explore();
			}
		else if (num == '2'){
			system("cls");
			explore();
		} 
		else if (num == '3'){
			system("cls");
			menu();
		}
		else {
			system("cls");
			printf ("Input tidak sesuai\n\n");
			explore();
		}
	}
	else if (n=='3'){
		system("cls");
		menu();
	} 
	else {
		system("cls");
		printf ("Input tidak sesuai\n\n");
		explore();
	}
	
}
void search(){
	int n, i;
	char title[100];
	char* match;
	printf ("SEARCH\n----------------------------------------\n");
	printf ("Search by:\n1. Name\n2. Genre\n3. Author\n4. Menu\n");
	fflush (stdin);
	n = getchar();
	system("cls");
	//SEARCH BY NAME
	if (n =='1'){
		int counter=0;
		printf ("Type book title: ");
		scanf (" %[^\n]s", title);
		strupr (title);
		for (i=0; i<librarytotal; i++){
			match = strstr (ex[i].title, title);
			if (match != '\0'){
				bookdetails(i);
				counter=1;
			}
		}
		if (counter==0) {
			system ("cls");
			printf ("Book not found!\n\n");
		}
		search();
	}
	
	//SEARCH BY GENRE//
	else if (n == '2'){
		char reqgenre[100];
		int i,j;
		printf ("Type book genre: ");
		getchar ();
		scanf("%[^\n]", &reqgenre);
		int counter =0;
		strupr (reqgenre); // mengubah input menjadi uppercase
		for(i=0;i<librarytotal;i++){
			for(j=0;j<librarytotal;j++){
				if(strcmp(reqgenre,ex[i].genre[j])==0){
					bookdetails(i); // menampilkan keterangan buku
					counter =1;
					break;
				}
			}
		}
		if (counter==0) {
			system ("cls");
			printf ("Book not found!\n\n");
		}
		search();
	}
		
	// SEARCH BY AUTHOR
	else if (n == '3') {
		int counter=0;
		char author [100];
		printf ("Type author name: ");
		scanf (" %[^\n]", author);
		strlwr (author); // mengubah input menjadi lowercase
		for (i=0; i<librarytotal; i++){
			match = strstr (ex[i].author, author);
			if (match != '\0'){
				bookdetails(i);
				counter=1;
			}
		}
		if (counter==0) {
			system ("cls");
			printf ("Book not found!\n\n");
		}
		search();
	}
	else if (n=='4'){
		system("cls");
		menu();
	}
	else {
		system("cls");
		printf ("Input tidak sesuai\n\n");
		search();
	}
	
}
int menu (){
	int num;
 	printf ("Menu\n-------------------------------------\n");
	printf ("1.Explore\n2.My Bookshelf\n3.Search\n4.Exit\n");
	printf ("\nPilih menu yang ingin dituju: ");
	fflush (stdin);
	num = getchar ();
	system("cls");
	if (num == '1')explore ();
	else if (num == '2') bookshelf();
	else if (num =='3') search();
	else if (num == '4'){
 		printf ("Exiting the application...\n");
  		exit(1);
	}
	else {
		system("cls");
		printf ("Input tidak sesuai\n\n");
		menu();
	}
}
int main (){
	printf ("SAF ONLINE LIBRARY\n");
	printf ("A room without books is like a body without a soul \n\n");	
	printf ("Nama Siswa: ");
	char name[100];
	scanf ("%[^\n]", &name); 
	printf ("NIM: ");
	char NIM[10];
	scanf ("%s", &NIM); 
	
	strcpy (memberID, name);
	strcat (memberID, "-");
	strcat (memberID, NIM);
	system("cls");
	
	//open user bookshelf
	FILE *fp;
	if ((fp = fopen (memberID, "r"))== NULL){
		printf ("Nice to meet you %s, welcome to SAF online library\n", name);  // jika user baru
		fp = fopen (memberID, "a+");
	}
	else printf ("Hello %s, welcome back to SAF online library\n", name); 
	
	while (fscanf (fp, "%[^\n]%*c", &bs[total].title) != EOF ){
		fscanf (fp, "%d%*c",&bs[total].index);
		total ++;
	}
	
	// open book database
	FILE *fptr;
	int i;
	if ((fptr = fopen ("booklist.txt", "r"))== NULL) exit (1);
	
	//scan book data
	fscanf (fptr, "%d%*c", &librarytotal);
	for (i=0; i<librarytotal; i++){
		fscanf (fptr,"%[^\n]%*c", &ex[i].title);
	 	fscanf (fptr,"%[^\n]%*c", &ex[i].author);
		fscanf (fptr,"%[^\n]%*c", &ex[i].rating);
		char check;
		int flag=1;
		check='\0';
	 	while(check!='\n')
		 {
		 	flag=0;
	 		fscanf (fptr,"%[^#]#%c", ex[i].genre[genretotal[i]],&check);	
	 		genretotal[i]++;
		 }
	 	fscanf (fptr,"%[^\t]%*c%*c", &ex[i].summary);
	}
			
	fclose(fptr);
	fclose(fp);
	menu();
}
