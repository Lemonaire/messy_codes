#include<stdio.h>
int main() {
	char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int length;
	scanf("%d", &length);
	int str[length];
	for(int i = 0; i < length; i++) {
		scanf("%d", &str[i]);
	}

	int resLength;
	if(length % 3 == 0) {
        resLength = length / 3 * 4;  
	}
    else {
        resLength = (length / 3 + 1) * 4;  
    }

    char res[resLength];
    int i, j;
	for(i = 0, j = 0; i < resLength - 2; j += 3,i += 4) {  
	    res[i] = base64_table[str[j] >> 2];
	    res[i+1] = base64_table[(str[j] & 0x3) << 4 | (str[j+1] >> 4)];
	    res[i+2] = base64_table[(str[j+1] & 0xf) << 2 | (str[j+2] >> 6)];
	    res[i+3] = base64_table[str[j+2] & 0x3f];
	}
	switch(length % 3) {  
        case 1:  
            res[i-2] = '=';  
            res[i-1] = '=';  
            break;
        case 2:  
            res[i-1] = '=';  
            break;  
    }
    printf("%s", res);
	return 0;
}