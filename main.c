#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include<unistd.h>


#define DATA_SIZE 1000

int read_ints ()
{
	FILE *fs;
	char ch, buffer[32];
	int i = 0, arr[100], j = 0;
	fs = fopen("totals.txt", "r");
	while(1){
		ch = fgetc(fs);
		if(ch == EOF){
			break;
		}
		else if(ch == ','){
			arr[j] = atoi(buffer);
			j++;
			i = 0;
			continue;
		}
		else{

			buffer[i] = ch;

			i++;
		}
	}

	return arr[0];
}

void fileCreation(char* fname){

}

int inputTips(){
    char data[DATA_SIZE];

    FILE * amts;
    FILE * total;
    char prev[100];
    int num[100];
    int num2;
    total = fopen("totals.txt", "r+");
    num[0] = read_ints();

    if(total == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter contents to store in file : \n");
    fgets(data, DATA_SIZE, stdin);
    sscanf(data, "%d", &num2);
    num[1] = num2;
    int finalNumber = num[0] + num[1];
    sprintf(prev, "%d,", finalNumber);
    char buffer[5000];

    time_t current = time(NULL);
    struct tm* pLocal = localtime(&current);
    strftime(buffer, sizeof(buffer), "%a %x at %X %p", pLocal);

    amts = fopen("output.txt", "a+");
    total = fopen("totals.txt", "r+");
    fprintf(total, "%s", prev);
    fprintf(amts , "------------------------------------------------\n"
                      "%s tip money made %s"
                      "----------------------------------------------"
                      , buffer, data);
    fclose(amts);
    fclose(total);
    printf("File created and saved successfully. 🙂 \n");
    return 0;
}

void createNew(){
    FILE * amts;
    FILE * total;
    amts = fopen("output.txt","w");
    total = fopen("totals.txt","w");
    fprintf(total, "0,");
    fclose(amts);
    fclose(total);
    printf("File(s) created and saved successfully. 🙂 \n");
}

void getList(char* fileName){
  FILE *f = fopen(fileName, "r");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, 1, fsize, f);
  fclose(f);

  string[fsize] = 0;
  printf("%s\n", string);
}

void menu(){
    int input;
    input = 0;
    printf( "(1) Show Tips\n(2) Input Tips\n(3) Get Total\n(4) New User\n>");
    scanf("%d", &input);
    getchar();
    switch(input){
      case 1:
        getList("output.txt");
        break;
      case 2:
        inputTips();
        break;
      case 3:
        getList("totals.txt");
        break;
      case 4:
        createNew();
        break;
      default:
        printf("ERROR: Out of Range\n");
        break;
    }
}

int main(int argc, char *argv[]){
  while(1){
    menu();
  }
}

