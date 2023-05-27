// 
// Fast autocorrelation using Wiener-Khinchim theorem
//
// 2023, Jonathan Tainer
// 
// Introduction: Autocorrelation is the measure of how much a signal correlates
// with a delayed copy of itself. This is useful for finding repeating patterns
// or identifying the fundamental frequency of a noisy signal.
//
// Algorithm: To calculate the autocorrelation R(t) of a signal x(t),
// 1. Take the fourier transform: X(f) = FFT(x(t)).
// 2. Multiply the frequency-domain signal by its complex conjugate (flip the
// sign of the imaginary component): S(f) = X(f) * X`(f).
// 3. Take the inverse fourier transform of the product: R(T) = IFFT(S(f)).
//

#ifndef AUTOCOR_H
#define AUTOCOR_H

#include <complex.h>

// Calculates autocorrelation of sig and stores result in cor.
// Number of elements n must be a power of 2.
// Current implementation allocates a temporary auxiliary buffer,
// recommended for memory-constrained systems.
void autocor(float* sig, float* cor, unsigned int n);

// Calculates autocorrelation of sig in-place, overwriting the signal with the
// resulting autocorrelation values. Does not allocate auxiliary memory.
void autocor_inpl(float complex* sig, unsigned int n);

#endif
