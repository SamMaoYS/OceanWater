## Simulating Ocean Water
by Jerry Tessendorf &nbsp;&nbsp;&nbsp;[paper link](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.161.9102&rep=rep1&type=pdf)  
#### Radiosity of the Ocean Environment
* L-Above = r*LS + r*LA + tU*LU
1. r is the Fresnel reflectivity for reflection from a spot on the surface of the ocean to the camera.
2. tU is the transmission coefficient for the light LU coming up from the ocean volume, refracted at the surface into the camera.
3. LS is the amount of light coming directly from the sun, through the atmosphere, to the spot on the ocean surface where it is reflected by the surface to the camera.
4. LA is the (diffuse) atmospheric skylight
5. LU is the light just below the surface that is transmitted through
the surface into the air.

* LS =LTOA * exp{−τ},  
LTOA is the intensity of the direct sunlight at the top of the atmosphere, and τ is the “optical thickness” of the atmosphere
- LA = LA_0(LS) + LA_1(LU)
- LU = LU_0(LS) + LU_1(LA)  
solution: take the skylight to depend only on the light from the sun

* L-BELOW =t*LD +t*LI +LSS +LM
1. t is the Fresnel transmissivity for transmission through the water surface at each point and angle on the surface.
2. LD The “direct” light from the sun that penetrates into the water.
3. LI The “indirect” light from the atmosphere that penetrates into
the water.
4. LSS The single-scattered light, from both the sun and the atmosphere, that is scattered once in the water volume before arriving at any point.
5. LM The multiply-scattered light. This is the single-scattered light that undergoes more scattering events in the volume.

- LSS =P(tLI)+P(tLD)
- LM = G(tLI) + G(tLD)  
multiple scattering is just a series of single scatters.

#### Practical Ocean Wave Algorithms
###### Gerstner Waves
If a point on the undisturbed surface is labelled x0 = (x0,z0) and the undisturbed height is y0 = 0, then as a single wave with amplitude A passes by, the point on the surface is displaced at time t to
- x = x0 − (**k**/k)Asin(**k**·x0 −ωt)
- y = Acos(**k**·x0 −ωt)  

In these expressions, the vector k, called the wavevector, is a horizontal vector that points in the direction of travel of the wave, and has magnitude k related to the length of the wave (λ) by `k = 2π/λ`  
this can be generalized to a more complex profile by summing a set of sine waves. One picks a set of wavevectors ki, amplitudes Ai, frequencies ωi, and phases φi, for i = 1,...,N, to get the expressions
- x = x0 - sum_1~N( **ki**/ki)Ai·sin( **ki**·x0 − ωi·t + φi)
- y = sum_1~N(Ai·cos(**ki**·x0−ωi·t+φi)).

#### Animating Waves: The Dispersion Relation
