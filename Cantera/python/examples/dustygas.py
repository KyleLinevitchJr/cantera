"""
 Dusty Gas transport model.

 The Dusty Gas model is a mulicomponent transport model for gas
 transport through the pores of a stationary porous medium. This
 example shows how to create a transport manager that implements the
 Dusty Gas model and use it to compute the multicomponent diffusion
 coefficients.

 """

from Cantera import *
from Cantera.DustyGasTransport import *

# create a gas-phase object to represent the gas in the pores
g = importPhase('h2o2.cti')

# set the gas state
g.setState_TPX(500.0, OneAtm, "OH:1, H:2, O2:3")

# create a Dusty Gas transport manager for this phase
d = DustyGasTransport(g)

# set its parameters
d.set(porosity = 0.2, tortuosity = 4.0,
      pore_radius = 1.5e-7, diameter = 1.5e-6)  # lengths in meters

# print the multicomponent diffusion coefficients
print d.multiDiffCoeffs()

