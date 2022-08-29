#include "pa5.h"

#define MAX_LINE_LENGTH 1000
#define MAX_CELL_LENGTH 20
int main( int argc, char *argv[]){
	char inExt[4], outExt[4];
	char line[MAX_LINE_LENGTH];
	char cell[MAX_CELL_LENGTH];
	char* rest;
	int size;
	int cSpace;
	
//	for (int i = 0; i < argc; i++) {
//		printf("%s ",argv[i]);
//		printf("\n");
//	}
	if(argc < 5){
		fprintf(stderr, "too few args\n");
		exit(1);
	}
	else if(argc > 5){
		fprintf(stderr, "too many args\n");
		exit(1);
	}
	if(!strcmp(argv[1], "-i")){
		strncpy(inExt, argv[2], 4);
		strncpy(outExt, argv[4], 4);
	}
	else if(!strcmp(argv[1], "-o")){
		strncpy(outExt, argv[2], 3);
		strncpy(inExt, argv[4], 3);
	}else{
		fprintf(stderr, "Error: usage of converter: -i inExt -o outExt\n");
		exit(1);
	}
	fprintf(stderr, "Input format is %s, output format is %s\n", inExt, outExt);
	
	//						== ===CSV=== ==
	if(!strcmp(inExt, "csv") && !strcmp(outExt, "csv")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^,\n],%[^\n]\n",cell , line) == 2)
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "csv") && !strcmp(outExt, "tl5")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^,\n],%[^\n]\n",cell , line) == 2)
				printf("%-5.5s|", cell);//internal cell followed by tab
			printf("%-5.5s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "csv") && !strcmp(outExt, "tr9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^,\n],%[^\n]\n",cell , line) == 2){
				if (strlen(cell)>9) {
					size = strlen(cell)-9;
					printf("%9.9s|", cell+size);
				}
				else{
					printf("%9.9s|", cell);//internal cell followed by tab
				}
			}
			if (strlen(cell)>9) {
				size = strlen(cell)-9;
				printf("%9.9s\n", cell+size);
			}else{
				printf("%9.9s\n",cell);//last cell followed by new line
			}
		}
	}else if(!strcmp(inExt, "csv") && !strcmp(outExt, "tc9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^,\n],%[^\n]\n",cell , line) == 2){
				//trims string length to middle 8 characters and adds a space
				if (strlen(cell)>9 && (strlen(cell)%2) == 0){
					cSpace = (1+(strlen(cell)-9)/2);
					printf("%-9.8s|", cell+(int)cSpace);
				}
				else if (strlen(cell)>9 && ((strlen(cell)%2)!=0)) {
					cSpace = ((strlen(cell)-9)/2);
					printf("%9.9s|", cell+(int)cSpace);
				}else{
					cSpace = (strlen(cell));
					printf("%*s%*s|", (9+cSpace)/2, cell, (((9-cSpace)/2)+((cSpace+9)%2)), "");
				}
			}
			if (strlen(cell)>9 && (strlen(cell)%2)==0){
				cSpace = (1+(strlen(cell)-9)/2);
				printf("%-9.8s\n", cell+(int)cSpace);//printf("%-9.8s\n%d:\n%d:\n%d:\n", cell+(int)cSpace, cSpace, strlen(cell), strlen(cell)-9);
			}
			else if (strlen(cell)>9 && (strlen(cell)%2)!=0) {//if not then if this is true
				cSpace = ((strlen(cell)-9)/2);
				printf("%9.9s\n", cell+(int)cSpace);
			}else{
				cSpace = (strlen(cell));
				printf("%*s%*s\n", (9+cSpace)/2, cell, (((9-cSpace)/2)+((cSpace+9)%2)), "");
			}
		}
	}
	//						== ===TL5=== ==
	else if(!strcmp(inExt, "tl5") && !strcmp(outExt, "tl5")) {
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^ |] |%[^\n]\n",cell , line) == 2)
				printf("%-5.5s|", cell);//internal cell followed by tab
			printf("%-5.5s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tl5") && !strcmp(outExt, "csv")) {
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^ |] |%[^\n]\n",cell , line) == 2)
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tl5") && !strcmp(outExt, "tr9")) {
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^ |] |%[^\n]\n",cell , line) == 2)
				printf("%9.9s|", cell);//internal cell followed by tab
			printf("%9.9s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tl5") && !strcmp(outExt, "tc9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^ |] |%[^\n]\n",cell , line) == 2){
				if (strlen(cell)>9) {
					cSpace = ((strlen(cell)-9)/2);
					printf("%9.9s|", cell+(int)cSpace);
				}
				else{
					int pad = (strlen(cell));
					printf("%*s%*s|", (9+pad)/2, cell, (((9-pad)/2)+((pad+9)%2)), "");
				}
			}
			if (strlen(cell)>9) {
				cSpace = ((strlen(cell)-9)/2);
				printf("%9.9s\n", cell+(int)cSpace);
			}else{
				cSpace = (strlen(cell));
				printf("%*s%*s\n", (9+cSpace)/2, cell, (((9-cSpace)/2)+((cSpace+9)%2)), "");
			}
		}
	}
	//						== ===TR9=== ==
	else if(!strcmp(inExt, "tr9") && !strcmp(outExt, "tr9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^ |] |%[^\n]\n",cell , line) == 2){
				if (strlen(cell)>9) {
					size = strlen(cell)-9;
					printf("%9.9s|", cell+size);
				}
				else{
					printf("%9.9s|", cell);//internal cell followed by tab
				}
			}
			if (strlen(cell)>9) {
				size = strlen(cell)-9;
				printf("%9.9s\n", cell+size);
			}else{
				printf("%9.9s\n",cell);//last cell followed by new line
			}
		}
	}else if(!strcmp(inExt, "tr9") && !strcmp(outExt, "csv")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^|\n] |%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tr9") && !strcmp(outExt, "tl5")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^|\n]| %[^\n]\n",cell , line) == 2)
				printf("%-5.5s|", cell);//internal cell followed by tab
			printf("%-5.5s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tr9") && !strcmp(outExt, "tc9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^|\n]| %[^\n]\n",cell , line) == 2){
				if (strlen(cell)>9) {
					cSpace = ((strlen(cell)-9)/2);
					printf("%9.9s|", cell+(int)cSpace);
				}
				else{
					int pad = (strlen(cell));
					printf("%*s%*s|", (9+pad)/2, cell, (((9-pad)/2)+((pad+9)%2)), "");
				}
			}
			if (strlen(cell)>9) {
				cSpace = ((strlen(cell)-9)/2);
				printf("%9.9s\n", cell+(int)cSpace);
			}else{
				cSpace = (strlen(cell));
				printf("%*s%*s\n", (9+cSpace)/2, cell, (((9-cSpace)/2)+((cSpace+9)%2)), "");
			}
		}
	}
	//						== ===TC9=== ==
	else if(!strcmp(inExt, "tc9") && !strcmp(outExt, "tc9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^ |] |%[^\n]\n",cell , line) == 2){
				if (strlen(cell)>9) {
					cSpace = ((strlen(cell)-9)/2);
					printf("%9.9s|", cell+(int)cSpace);
				}
				else{
					int pad = (strlen(cell));
					printf("%*s%*s|", (9+pad)/2, cell, (((9-pad)/2)+((pad+9)%2)), "");
				}
			}
			if (strlen(cell)>9) {
				cSpace = ((strlen(cell)-9)/2);
				printf("%9.9s\n", cell+(int)cSpace);
			}else{
				cSpace = (strlen(cell));
				printf("%*s%*s\n", (9+cSpace)/2, cell, (((9-cSpace)/2)+((cSpace+9)%2)), "");
			}
		}
	}else if(!strcmp(inExt, "tc9") && !strcmp(outExt, "csv")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^ |] |%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tc9") && !strcmp(outExt, "tl5")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^ |] |%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%-5.5s|", cell);//internal cell followed by tab
			printf("%-5.5s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(inExt, "tc9") && !strcmp(outExt, "tr9")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line," %[^ |] |%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%9.9s|", cell);//internal cell followed by tab
			printf("%9.9s\n",cell);//last cell followed by new line
		}
	}
}
