// 
// Fast autocorrelation using Wiener-Khinchim theorem
//
// 2023, Jonathan Tainer
// 

#include "autocor.h"
#include "fft/fft.h"
#include <stdlib.h>

// Calculates autocorrelation of sig and stores result in cor.
// Number of elements n must be a power of 2.
void autocor(float* sig, float* cor, unsigned int n) {
	float complex* fft_buf = malloc(sizeof(float complex) * n);
	for (unsigned int i = 0; i < n; i++) {
		fft_buf[i] = sig[i] + 0*I;
	}
	fft_inpl(fft_buf, n);
	for (unsigned int i = 0; i < n; i++) {
		fft_buf[i] *= conjf(fft_buf[i]);
	}
	ifft_inpl(fft_buf, n);
	for (unsigned int i = 0; i < n; i++) {
		cor[i] = crealf(fft_buf[i]);
	}
	free(fft_buf);
}

// Calculates autocorrelation of sig in-place, overwriting the signal with the
// resulting autocorrelation values.
void autocor_inpl(float complex* sig, unsigned int n) {
	fft_inpl(sig, n);
	for (unsigned int i = 0; i < n; i++) {
		sig[i] *= conjf(sig[i]);
	}
	ifft_inpl(sig, n);
}
