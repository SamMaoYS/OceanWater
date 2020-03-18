## Simulating Ocean Water
by Jerry Tessendorf &nbsp;&nbsp;&nbsp;[paper link](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.161.9102&rep=rep1&type=pdf)  
#### Radiosity of the Ocean Environment
- > L-Above = r*LS + r*LA + tU*LU
1. r is the Fresnel reflectivity for reflection from a spot on the surface of the ocean to the camera.
2. tU is the transmission coefficient for the light LU coming up from the ocean volume, refracted at the surface into the camera.
3. LS is the amount of light coming directly from the sun, through the atmosphere, to the spot on the ocean surface where it is reflected by the surface to the camera.
4. LA is the (diffuse) atmospheric skylight
5. LU is the light just below the surface that is transmitted through
the surface into the air.

- > LS =LTOA * exp{−τ}  
LTOA is the intensity of the direct sunlight at the top of the atmosphere, and τ is the “optical thickness” of the atmosphere
- > LA = LA_0(LS) + LA_1(LU)
- > LU = LU_0(LS) + LU_1(LA)  

solution: take the skylight to depend only on the light from the sun

- > L-BELOW =t*LD +t*LI +LSS +LM
1. t is the Fresnel transmissivity for transmission through the water surface at each point and angle on the surface.
2. LD The “direct” light from the sun that penetrates into the water.
3. LI The “indirect” light from the atmosphere that penetrates into
the water.
4. LSS The single-scattered light, from both the sun and the atmosphere, that is scattered once in the water volume before arriving at any point.
5. LM The multiply-scattered light. This is the single-scattered light that undergoes more scattering events in the volume.

- > LSS =P(tLI)+P(tLD)
- > LM = G(tLI) + G(tLD)
multiple scattering is just a series of single scatters.

#### Practical Ocean Wave Algorithms
###### Gerstner Waves
If a point on the undisturbed surface is labelled x0 = (x0,z0) and the undisturbed height is y0 = 0, then as a single wave with amplitude A passes by, the point on the surface is displaced at time t to
- > x = x0 − (**k**/k)Asin(**k**·x0 −ωt)
- > y = Acos(**k**·x0 −ωt)  

In these expressions, the vector k, called the wavevector, is a horizontal vector that points in the direction of travel of the wave, and has magnitude k related to the length of the wave (λ) by `k = 2π/λ`  
this can be generalized to a more complex profile by summing a set of sine waves. One picks a set of wavevectors ki, amplitudes Ai, frequencies ωi, and phases φi, for i = 1,...,N, to get the expressions
- > x = x0 - sum_1~N( **ki**/ki)Ai·sin( **ki**·x0 − ωi·t + φi)
- > y = sum_1~N(Ai·cos(**ki**·x0−ωi·t+φi))

#### Animating Waves: The Dispersion Relation
In deep water, where the bottom may be ignored, that relationship is
- `ω^2 (k) = g·k`
When the bottom is relatively shallow compared to the length of the waves, the bottom has a retarding affect on the waves. For a bottom at a depth D below the mean water level, the dispersion relation is
- `ω^2 (k) = g·k·tanh(kD)`
A second situation which modifies the dispersion relation is surface tension. Very small waves, with a wavelength of about 1 cm or less, have an additional term:
- `ω^2 (k) = g·k(1 + k^2·L^2)` (the parameter L has units of length)

For a given wavenumber k, we use the frequency
- > **ω(k)** = [[_ω(k)_/w0]]ω0  
[[a]] means take the integer part of the value of a

#### Statistical Wave Models and the Fourier Transform
[Details about Fourier Transform](doc/FFT.md)  
The fft-based representation of a wave height field expresses the wave height `h(x, t)` at the horizontal position `x = (x, z)` as the sum of sinusoids with complex, time-dependent amplitudes:
- > h(**x**,t) =sum_k( ̃h(**k**,t) exp(i**k** · **x**) )  
where **k** is a two-dimensional vector with components, **k** = (kx,kz), kx = 2πn/Lx, kz = 2πm/Lz, and n and m are integers with bounds −N/2 ≤ n < N/2 and −M/2 ≤ m < M/2.

The fft process generates the height field at discrete points `x = (nLx/N,mLz/M)`
An exact computation of the slope vector can be obtained by using more ffts   
- > ε(x,t) = ∇h(x,t) = sum_k(i **k** ̃h(**k**,t) exp(i**k** · **x**) )

#### Building a Random Ocean Wave Height Field
The Fourier amplitudes of a wave height field can be produced as
- > ~h0(**k**) = 1/sqrt(2) * (ξr+iξi)sqrt(Ph(**k**))  
where ξr and ξi are ordinary independent draws from a gaussian random number generator, with mean 0 and standard deviation 1.  
Given a dispersion relation ω(k), the Fourier amplitudes of the wave field realization at time t are
- > ̃h(**k**,t) = ̃h0(**k**)exp{iw(k)t} + ̃h0\*(**k**)exp{-iw(k)t}  

the complex conjugation property h\*(**k**,t) = ̃h(−k, t) by propagating waves “to the left” and “to the right”.
