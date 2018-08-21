#include "EckertConstants.h"
#include "proc/GeneralProcessor.h"

namespace engine {

const std::map<std::string, SpElement>
EckertConstants::prefixValues = {
	{ "y", GEN_FLOATING(1.0E-24L) },
	{ "z", GEN_FLOATING(1.0E-21L) },
	{ "a", GEN_RATIONAL2(1, 1000000000000000000LL) },
	{ "f", GEN_RATIONAL2(1, 1000000000000000LL) },
	{ "p", GEN_RATIONAL2(1, 1000000000000LL) },
	{ "n", GEN_RATIONAL2(1, 1000000000LL) },
	{ "u", GEN_RATIONAL2(1, 1000000LL) },
	{ "m", GEN_RATIONAL2(1, 1000LL) },
	{ "c", GEN_RATIONAL2(1, 100LL) },
	{ "d", GEN_RATIONAL2(1, 10LL) },
	{ "da", GEN_INTEGER(10LL) },
	{ "h", GEN_INTEGER(100LL) },
	{ "k", GEN_INTEGER(1000LL) },
	{ "M", GEN_INTEGER(1000000LL) },
	{ "G", GEN_INTEGER(1000000000LL) },
	{ "T", GEN_INTEGER(1000000000000LL) },
	{ "P", GEN_INTEGER(1000000000000000LL) },
	{ "E", GEN_INTEGER(1000000000000000000LL) },
	{ "Z", GEN_FLOATING(1.0E+21L) },
	{ "Y", GEN_FLOATING(1.0E+24L) },
	{ "Ki", GEN_INTEGER(1LL << 10) },
	{ "Mi", GEN_INTEGER(1LL << 20) },
	{ "Gi", GEN_INTEGER(1LL << 30) },
	{ "Ti", GEN_INTEGER(1LL << 40) },
	{ "Pi", GEN_INTEGER(1LL << 50) },
	{ "Ei", GEN_INTEGER(1LL << 60) },
	{ "Zi", GEN_FLOATING(1.18059162071741E+21L) },
	{ "Yi", GEN_FLOATING(1.20892581961463E+24L) },
};

const std::map <std::string, unsigned int>
EckertConstants::scientificConstantKeywords = {
	// Math
	{ "pi", MATH_PI },
	{ "e", MATH_NAPIER },
	{ "eg", MATH_EGAMMA },
	// Univesal scientific constant
	{ "light", UNIV_C0 },
	{ "c0", UNIV_C0 },
	{ "magnetic", UNIV_MU0 },
	{ "mu0", UNIV_MU0 },
	{ "electric", UNIV_EPS0 },
	{ "eps0", UNIV_EPS0 },
	{ "impedance", UNIV_Z0 },
	{ "z0", UNIV_Z0 },
	{ "gravitation", UNIV_G0 },
	{ "newtonian", UNIV_G0 },
	{ "planck", UNIV_H },
	{ "h", UNIV_H },
	{ "rplanck", UNIV_HBAR },
	{ "hbar", UNIV_HBAR },
	// Electro-magnetic constant
	{ "echarge", ELEC_E_CHARGE },
	{ "evolt", ELEC_E_CHARGE },
	{ "q.flux", ELEC_Q_FLUX },
	{ "q.conduct", ELEC_Q_COND },
	{ "q.resist", ELEC_Q_RESIST },
	{ "josephson", ELEC_JOSEPH },
	{ "klitzing", ELEC_KLITZ },
	{ "b.magneton", ELEC_B_MAGNETON },
	{ "n.magneton", ELEC_N_MAGNETON },
	// Nuclear physics
	{ "fstruct", NUKE_F_STRUCT },
	{ "rydberg", NUKE_RYDBERG },
	{ "b.radius", NUKE_B_RADIUS },
	{ "hartree", NUKE_HARTREE },
	// electron
	{ "e.mass", NUKE_E_MASS },
	{ "e.compton", NUKE_E_COMPTON },
	{ "e.radius", NUKE_E_RADIUS },
	{ "e.magnetic", NUKE_E_MAGNETIC },
	{ "e.gyro", NUKE_E_GYRO },
	// proton
	{ "p.mass", NUKE_P_MASS },
	{ "p.compton", NUKE_P_COMPTON },
	{ "p.magnetic", NUKE_P_MAGNETIC },
	{ "p.gyro", NUKE_P_GYRO },
	// neutron
	{ "n.mass", NUKE_N_MASS },
	{ "n.compton", NUKE_N_COMPTON },
	{ "n.magnetic", NUKE_N_MAGNETIC },
	{ "n.gyro", NUKE_N_GYRO },
	// elementary particle
	{ "mu.mass", NUKE_MU_MASS },
	{ "mu.magnetic", NUKE_MU_MAGNETIC },
	{ "tau.mass", NUKE_TAU_MASS },
	// physical chemistry
	{ "boltzmann", CHEM_BOLTZMANN },
	{ "avogadro", CHEM_AVOGADRO },
	{ "dalton", CHEM_DALTON },
	{ "faraday", CHEM_FARADAY },
	{ "gas", CHEM_GAS },
	{ "molv", CHEM_MOLVOL },
	{ "molvl", CHEM_MOLVOL_L },
	{ "loschmidt", CHEM_LOSCHMIDT },
	// thermal radiation
	{ "stefan", CHEM_STEFAN },
	{ "f.rad", CHEM_F_RAD },
	{ "s.rad", CHEM_S_RAD },
	// adopted value
	{ "gravity", ADPT_G0 },
	{ "atm", ADPT_ATM },
	{ "zerod", ADPT_ZDEG },
	// Planck unit
	{ "pl.mass", PL_MASS },
	{ "pl.energy", PL_ENERGY },
	{ "pl.temp", PL_TEMP },
	{ "pl.length", PL_LENGTH },
	{ "pl.time", PL_TIME },
	// astromy
	{ "astro", ASTRO_AU },
	{ "parsec", ASTRO_PC },
	{ "lyear", ASTRO_LY },
};

const std::map <unsigned int, SpElementNamePair>
EckertConstants::scientificConstantValues = {
	// Math
	{ MATH_PI, { GEN_FLOATING(GeneralProcessor::PI), "PI" } },
	{ MATH_NAPIER, { GEN_FLOATING(GeneralProcessor::NAPIER), "Napier's constant" } },
	{ MATH_EGAMMA, { GEN_FLOATING(GeneralProcessor::EGAMMA), "Euler-Mascheroni constant" } },
	// Univesal scientific constant
	{ UNIV_C0, { GEN_INTEGER(299792458), "Speed of light in vacum" } },
	{ UNIV_MU0, { GEN_FLOATING(1.25663706143591729E-06L), "Magnetic constant" } },
	{ UNIV_EPS0, { GEN_FLOATING(8.85418781762038985E-12L), "Electric constant" } },
	{ UNIV_Z0, { GEN_FLOATING(376.730313461770655L), "Characteristic impedance of vacum" } },
	{ UNIV_G0, { GEN_FLOATING(6.67408E-11L), "Gravitation constant" } },
	{ UNIV_H, { GEN_FLOATING(6.626070040E-34L), "Planck constant" } },
	{ UNIV_HBAR, { GEN_FLOATING(1.054571800E-34L), "Reduced Planck constant" } },
	// Electro-magnetic constant
	{ ELEC_E_CHARGE, { GEN_FLOATING(1.6021766208E-19L), "Elementary charge" } },
	{ ELEC_Q_FLUX, { GEN_FLOATING(2.067833831E-15L), "Magnetic flux quantum" } },
	{ ELEC_Q_COND, { GEN_FLOATING(7.7480917310E-05L), "Conductance quantum" } },
	{ ELEC_Q_RESIST, { GEN_FLOATING(12906.4037278L), "Resistance quantum" } },
	{ ELEC_JOSEPH, { GEN_FLOATING(483597.8525E-09L), "Josephson constant" } },
	{ ELEC_KLITZ, { GEN_FLOATING(25812.8074555L), "von Klitzing constant" } },
	{ ELEC_B_MAGNETON, { GEN_FLOATING(927.4009994E-26L), "Bohr magneton" } },
	{ ELEC_N_MAGNETON, { GEN_FLOATING(5.050783699E-27L), "Nuclear magneton" } },
	// Nuclear physics
	{ NUKE_F_STRUCT, { GEN_FLOATING(7.2973525664E-03L), "Fine-structure constant" } },
	{ NUKE_RYDBERG, { GEN_FLOATING(10973731.568508L), "Rydberg constant" } },
	{ NUKE_B_RADIUS, { GEN_FLOATING(0.52917721067E-10L), "Bohr radius" } },
	{ NUKE_HARTREE, { GEN_FLOATING(4.359744650E-18L), "Hartree energy" } },
	// electron
	{ NUKE_E_MASS, { GEN_FLOATING(9.10938356E-31L), "Mass of electron" } },
	{ NUKE_E_COMPTON, { GEN_FLOATING(2.4263102367E-12L), "Compton wavelength of electron" } },
	{ NUKE_E_RADIUS, { GEN_FLOATING(2.8179403227E-15L), "Classical electron radius" } },
	{ NUKE_E_MAGNETIC, { GEN_FLOATING(-928.4764620E-26L), "Magnetic moment of electron" } },
	{ NUKE_E_GYRO, { GEN_FLOATING(1.760859644E+11L), "Gyromagnetic ratio of electron" } },
	// proton
	{ NUKE_P_MASS, { GEN_FLOATING(1.672621898E-27L), "Mass of proton" } },
	{ NUKE_P_COMPTON, { GEN_FLOATING(1.32140985396E-15L), "Compton wavelength of proton" } },
	{ NUKE_P_MAGNETIC, { GEN_FLOATING(1.4106067873E-26L), "Magnetic moment of proton" } },
	{ NUKE_P_GYRO, { GEN_FLOATING(2.675221900E+08L), "Gyromagnetic ratio of electron" } },
	// neutron
	{ NUKE_N_MASS, { GEN_FLOATING(1.674927471E-27L), "Mass of neutron" } },
	{ NUKE_N_COMPTON, { GEN_FLOATING(1.31959090481E-15L), "Compton wavelength of neutron" } },
	{ NUKE_N_MAGNETIC, { GEN_FLOATING(-0.96623650E-26L), "Magnetic moment of neutron" } },
	{ NUKE_N_GYRO, { GEN_FLOATING(1.83247172E+08L), "Gyromagnetic ratio of neutron" } },
	// elementary particle
	{ NUKE_MU_MASS, { GEN_FLOATING(1.883531594E-28L), "Mass of muon" } },
	{ NUKE_MU_MAGNETIC, { GEN_FLOATING(-4.49044826E-26L), "Magnetic moment of muon" } },
	{ NUKE_TAU_MASS, { GEN_FLOATING(3.16747E-27L), "Mass of tauon" } },
	// physical chemistry
	{ CHEM_BOLTZMANN, { GEN_FLOATING(1.38064852E-23L), "Boltzmann constant" } },
	{ CHEM_AVOGADRO, { GEN_FLOATING(6.022140857E+23L), "Avogadro constant" } },
	{ CHEM_DALTON, { GEN_FLOATING(1.660539040E-27L), "Atomic Mass Constant" } },
	{ CHEM_FARADAY, { GEN_FLOATING(96485.33289L), "Faraday constant" } },
	{ CHEM_GAS, { GEN_FLOATING(8.3144598L), "Molar gas constant" } },
	{ CHEM_MOLVOL, { GEN_FLOATING(22.413962E-03L), "Molar volume" } },
	{ CHEM_MOLVOL_L, { GEN_FLOATING(22.413962L), "Molar volume in litter" } },
	{ CHEM_LOSCHMIDT, { GEN_FLOATING(2.6867811E+25L), "Loschmidt's constant" } },
	// thermal radiation
	{ CHEM_STEFAN, { GEN_FLOATING(5.670367E-08L), "Stefan-Boltzmann constant" } },
	{ CHEM_F_RAD, { GEN_FLOATING(3.741771790E-16L), "First radiation constant" } },
	{ CHEM_S_RAD, { GEN_FLOATING(1.43877736E-02L), "Second radiation constant" } },
	// adopted value
	{ ADPT_G0, { GEN_RATIONAL2(196133, 20000), "Standard gravity" } },
	{ ADPT_ATM, { GEN_INTEGER(101325), "Standard atmosphere" } },
	{ ADPT_ZDEG, { GEN_RATIONAL2(5463, 20), "Zero degrees Celsius in Kelvin" } },
	// Planck unit
	{ PL_MASS, { GEN_FLOATING(2.176470E-08L), "Planck mass" } },
	{ PL_ENERGY, { GEN_FLOATING(1.220910E+19L), "Planck energy" } },
	{ PL_TEMP, { GEN_FLOATING(1.416808E+32L), "Planck temperature" } },
	{ PL_LENGTH, { GEN_FLOATING(1.616229E-35L), "Planck length" } },
	{ PL_TIME, { GEN_FLOATING(5.39116E-44L), "Planck time" } },
	// astromy
	{ ASTRO_AU, { GEN_INTEGER(149597870700), "Astronomical unit" } },
	{ ASTRO_PC, { GEN_FLOATING(3.085677581E+16L), "Parsec" } },
	{ ASTRO_LY, { GEN_INTEGER(9460730472580800LL), "Light year" } },
};

} // namespace engine
