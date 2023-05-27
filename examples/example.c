// 
// Autocorrelation example
//
// 2023, Jonathan Tainer
//

#include "../autocor.h"
#include <stdio.h>
#include <math.h>

int main() {
	const unsigned int n = 16;
	float complex sig[n];
	const float period = 3.f;
	for (unsigned int i = 0; i < n; i++) {
		sig[i] = sinf(i * 2 * M_PI / period) + 0*I;
	}
	autocor_inpl(sig, n);
	for (unsigned int i = 0; i < n; i++) {
		printf("R(%d) = %f\n", i, crealf(sig[i]));
	}
	return 0;
}
