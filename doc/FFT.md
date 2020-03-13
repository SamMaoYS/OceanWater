## Fast Fourier Transform
by Paul Heckbert from Feb. 1995 &nbsp;&nbsp;&nbsp;[paper link](http://www.cs.cmu.edu/afs/andrew/scs/cs/15-463/2001/pub/www/notes/fourier/fourier.pdf)  
#### Definition of the Fourier Transform
The Fourier Transform of the function `f(x)` is `F(ω)` &nbsp;&nbsp;
<img src="FFT_images/ft.png" alt="ft" title="ft" width = 30% />
The inverse Fourier Transform is  &nbsp;&nbsp;
<img src="FFT_images/ft_inv.png" alt="ft_inv" title="ft_inv" width = 30% />  
`i` is an indeterminate with `i^2 = -1`, `e^(iθ) = cos(θ)+isin(θ)`  
**The Fourier transform uses complex exponentials (sinusoids) of various frequencies as its basis functions.**
#### Discrete Fourier Transform (DFT)
When a signal is discrete and periodic, we don’t need the continuous Fourier transform. Suppose our signal is `a_n` for `n` = 0...N−1, and `a_n = a_(n+jN)` for all `n` and `j`. The DFT of `a`, also known as the spectrum of `a`, is:
<img src="FFT_images/dft.png" alt="dft" title="dft" width = 25% /> More commonly wriiten as: <img src="FFT_images/dft_common.png" alt="dft_common" title="dft_common" width = 25% /> where <img src="FFT_images/dft_W.png" alt="dft_W" title="dft_W" width = 20% />  and <img src="FFT_images/dft_Wk.png" alt="dft_Wk" title="dft_Wk" width = 25% />  are called the **_Nth root of unity_**  

Below are roots of unity for N = 2, N = 4, and N = 8, graphed in the complex plane.  <img src="FFT_images/dft_plane.png" alt="dft_plane" title="dft_plane" width = 90% />  
The formula for the inverse DFT is: <img src="FFT_images/dft_inv.png" alt="dft_inv" title="dft_inv" width = 25% />

#### The Fast Fourier Transform (FFT) Algorithm
To compute the DFT of an N-point sequence using equation <img src="FFT_images/dft_common.png" alt="dft_common" title="dft_common" width = 25% /> would take **O(N^2)** multiplies and adds. The FFT computes the DFT using **O(NlogN)** multiplies and adds.  
Below is a diagram of an 8-point FFT, where <img src="FFT_images/p8_W.png" alt="p8_W" title="p8_W" width = 34% /> diagram as:  
<img src="FFT_images/p8_gram.png" alt="p8_gram" title="p8_gram" width = 48% />  
**Butterflies and Bit-Reversal** The FFT algorithm decomposes the DFT into `log2N` stages, each of which consists of N/2 butterfly computations. Each butterfly takes two complex numbers p and q and computes from them two other numbers, `p + αq` and `p − αq`, where `α` is a complex number.  
In the diagram of the 8-point FFT above, note that the inputs aren’t in normal order: `a0, a1, a2, a3, a4, a5, a6, a7`, they’re in the bizarre order: `a0, a4, a2, a6, a1, a5, a3, a7`.  <img src="FFT_images/reverse.png" alt="reverse" title="reverse" width = 50% /> `nj` is the bit-reversal of `j`. The sequence is also related to breadth-first traversal of a binary tree.

#### FFT Explained Using Matrix Factorization
The 8-point DFT can be written as a matrix product:  <img src="FFT_images/p8_matrix.png" alt="p8_matrix" title="p8_matrix" width = 50% />  
Rearranging so that the input array a is bit-reversed and factoring the 8 × 8 matrix: <img src="FFT_images/p8_matrix_rearrange.png" alt="p8_matrix_rearrange" title="p8_matrix_rearrange" width = 50% />  <img src="FFT_images/p8_matrix_decomp.png" alt="p8_matrix_decomp" title="p8_matrix_decomp" width = 80% />

#### Why Would We Want to Compute Fourier Transforms
Because it is faster than traditional convolution algorithm.
If `h = f ⊙ g`, think f as the signal and g as the filter. The convolution theorem says that the Fourier transform of the convolution of two signals is the product of their Fourier transforms: `f ⊙ g ↔ FG`.
Computing the convolution with a straight forward algorithm would require `N^2` (real) multiplies and adds.  
Using **Fourier Convolution**:  

<img src="FFT_images/ft_conv.png" alt="ft_conv" title="ft_conv" width = 60% />  

#### Fourier Transforms of Images
The two-dimensional discrete Fourier transform is a simple generalization of the standard 1-D DFT: <img src="FFT_images/dft_2d.png" alt="dft_2d" title="dft_2d" width = 30% />
To compute the Fourier transform of an image:
- > Compute 1-D DFT of each row, in place.
- > Compute 1-D DFT of each column, in place.
For an `N × N` picture, `N` a power of 2, the cost of a 2-D FFT is proportional to `N^2log N`.
