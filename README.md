# Introduction

TeleBench™ is a suite of benchmarks that allows the users to approximate the performance of processors in modem and related fixed-telecom applications. Its benchmark kernels, which also serve as a representation of traditional DSP algorithms, include the following:

## Autocorrelation
This benchmark, which produces scores from three different data sets – pulse, sine, and speech – is based on a mathematical tool used frequently in signal processing for analyzing functions or series of values, such as time domain signals. It is the cross-correlation of a signal with itself.

## Convolutional Encoder
This benchmark, supports a type of error-correcting code, is based on an algorithm often used to improve the performance of digital radio, mobile phones, satellite links, and Bluetooth implementations.

## Bit Allocation
The benchmark tests the target processor’s ability to spread a stream of data over a series of buffers (or “frequency bins”) which it then modulates and transmits on a telephone line in ADSL applications.

## Inverse Fast Fourier Transform (iFFT)
The benchmark tests the target processor’s ability to convert frequency domain data into time domain data.

## Fast Fourier Transform (FFT)
The benchmark tests the target processor’s ability to convert time domain data into frequency domain data.

## Viterbi Decoder
The benchmark tests the processor’s ability to recover an output data packet from an encoded input data packet in embedded IS-136 channel coding applications.

# Score

The TelemarkTM score reported for each device is a single-number figure of merit calculated by taking the geometric mean of the individual TeleBench scores and dividing by 785.138 . (This normalization factor is derived from the lowest score in this category on December 5, 2000.) Scores for each of the individual benchmarks within this suite allow designers to weight and aggregate the benchmarks to suit specific application requirements.

To calculate a geometric mean, multiply all the results of the tests together and take the nth root of the product, where n equals the number of tests.

# Notes

This repository contains the TeleBench benchmark and its corresponding Test Harness for the Version 1.1 benchmarks produced by EEMBC between 1997 and 2004. This benchmark is released as-is, meaning EEMBC will follow issues but cannot guarantee support. Issues should be considered errata, and changes to the benchmark core algorithms are no longer considered compatible with version 1.1.

