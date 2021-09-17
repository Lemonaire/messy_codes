#include<stdio.h>
int main() {
	int n, p;
	scanf("%d %d", &n, &p);
	
	long long x = 1, y = p % n, res = 0;
	while(y != -1 && x != 0) {
		res += x;
		res %= n;
		x *= y;
		x %= n;
		y--;		

	}
	printf("%lld\n", res);
}