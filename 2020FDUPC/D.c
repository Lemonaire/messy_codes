#include<stdio.h>
int main() {
	int dec;
	scanf("%d", &dec);
	int ter[16];
	int lower = 0, upper = 0, index = 0;
	do {
		switch(dec % 3) {
		case 0:
			lower = 0 + upper;
			upper = 0;
			break;
		case 1:
			lower = 1 + upper;
			upper = 0;
			break;
		case 2:
			lower = -1 + upper;
			upper = 1;
			break;
		}
		if(lower == 2) {
			lower = -1;
			upper++;
		}
		ter[index++] = lower;
		dec /=3;
	} while(dec > 0);
	if(upper == 1) {
		ter[index] = upper;
	}
	else {
		index--;
	}
	for(int i = 0; i <= 16; i++) {
		if(i <= index) {
				printf("%d", ter[i]);
		}
		else {
			printf("0");
		}
		if(i != 16) {
			printf(" ");
		}
	}
	return 0;
}
