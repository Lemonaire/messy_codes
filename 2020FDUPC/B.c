#include<stdio.h>
int main() {
	char s[160];
	scanf("%s", s);
	int i = 0;
	while(s[i] != '\0'){
		printf("%d", s[i]);
		if(s[++i] != '\0') {
			printf(" ");
		}
	}
	return 0;
}