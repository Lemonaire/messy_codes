#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	char str[100];
	scanf("%s",str);
	int t =  strlen(str);
	for(int i = 1; i < 26; i++){
		for(int j = 0; j < t; j++){
			if(str[j] + i > 122){
				str[j] -= 26;
			}
			printf("%c",str[j] + i);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}
