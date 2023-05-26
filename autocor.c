// 
// Fast autocorrelation using Wiener-Khinchim theorem
//
// 2023, Jonathan Tainer
// 

#include "autocor.h"
#include "fft/fft.h"

// Calculates autocorrelation of sig and stores result in cor.
// Number of elements n must be a power of 2.
void autocor(float* sig, float* cor, unsigned int n) {

}

// Calculates autocorrelation of sig in-place, overwriting the signal with the
// resulting autocorrelation values.
void autocor_inpl(float complex* sig, unsigned int n) {
	fft_inpl(sig, n);
	for (unsigned int i = 0; i < n; i++) {
		sig[i] = sig[i] * conjf(sig[i]);
	}
	ifft_inpl(sig, n);
}
