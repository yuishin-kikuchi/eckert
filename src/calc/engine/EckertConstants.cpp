#include "EckertConstants.h"
#include "proc/GeneralProcessor.h"

namespace engine {

const std::map<std::string, SpElement>
EckertConstants::prefixValue = {
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

const std::map <std::string, SpElementNamePair>
EckertConstants::scientificConstants = {
	// MATH CONSTANT
	{ "pi", { GEN_FLOATING(GeneralProcessor::PI), "PI" } },
	{ "e", { GEN_FLOATING(GeneralProcessor::NAPIER), "Napier's constant" } },
	{ "eg", { GEN_FLOATING(GeneralProcessor::EGAMMA), "Euler-Mascheroni constant" } },
	// Univesal scientific constant
	{ "light", { GEN_INTEGER(299792458), "Speed of light in vacum" } },
	{ "magnetic", { GEN_FLOATING(1.25663706143591729E-06L), "Magnetic constant" } },
	{ "electric", { GEN_FLOATING(8.85418781762038985E-12L), "Electric constant" } },
	{ "impedance", { GEN_FLOATING(376.730313461770655L), "Characteristic impedance of vacuum" } },
	{ "gravitation", { GEN_FLOATING(6.67408E-11L), "Gravitation constant" } },
	{ "planck", { GEN_FLOATING(6.626070040E-34L), "Planck constant" } },
	{ "rplanck", { GEN_FLOATING(1.054571800E-34L), "Reduced Planck constant" } },
	// Electro-magnetic constant
	{ "echarge", { GEN_FLOATING(1.6021766208E-19L), "Elementary charge" } },
	{ "q.flux", { GEN_FLOATING(2.067833831E-15L), "Magnetic flux quantum" } },
	{ "q.conduct", { GEN_FLOATING(7.7480917310E-05L), "Conductance quantum" } },
	{ "q.resist", { GEN_FLOATING(12906.4037278L), "Resistance quantum" } },
	{ "josephson", { GEN_FLOATING(483597.8525E-09L), "Josephson constant" } },
	{ "klitzing", { GEN_FLOATING(25812.8074555L), "von Klitzing constant" } },
	{ "b.magneton", { GEN_FLOATING(927.4009994E-26L), "Bohr magneton" } },
	{ "n.magneton", { GEN_FLOATING(5.050783699E-27L), "Nuclear magneton" } },
	// Nuclear physics
	{ "fstruct", { GEN_FLOATING(7.2973525664E-03L), "Fine-structure constant" } },
	{ "rydberg", { GEN_FLOATING(10973731.568508L), "Rydberg constant" } },
	{ "b.radius", { GEN_FLOATING(0.52917721067E-10L), "Bohr radius" } },
	{ "hartree", { GEN_FLOATING(4.359744650E-18L), "Hartree energy" } },
	// electron
	{ "e.mass", { GEN_FLOATING(9.10938356E-31L), "Mass of electron" } },
	{ "e.compton", { GEN_FLOATING(2.4263102367E-12L), "Compton wavelength of electron" } },
	{ "e.radius", { GEN_FLOATING(2.8179403227E-15L), "Classical electron radius" } },
	{ "e.magnetic", { GEN_FLOATING(-928.4764620E-26L), "Magnetic moment of electron" } },
	{ "e.gyro", { GEN_FLOATING(1.760859644E+11L), "Gyromagnetic ratio of electron" } },
	// proton
	{ "p.mass", { GEN_FLOATING(1.672621898E-27L), "Mass of proton" } },
	{ "p.compton", { GEN_FLOATING(1.32140985396E-15L), "Compton wavelength of proton" } },
	{ "p.magnetic", { GEN_FLOATING(1.4106067873E-26L), "Magnetic moment of proton" } },
	{ "p.gyro", { GEN_FLOATING(2.675221900E+08L), "Gyromagnetic ratio of electron" } },
	// neutron
	{ "n.mass", { GEN_FLOATING(1.674927471E-27L), "Mass of neutron" } },
	{ "n.compton", { GEN_FLOATING(1.31959090481E-15L), "Compton wavelength of neutron" } },
	{ "n.magnetic", { GEN_FLOATING(-0.96623650E-26L), "Magnetic moment of neutron" } },
	{ "n.gyro", { GEN_FLOATING(1.83247172E+08L), "Gyromagnetic ratio of neutron" } },
	// elementary particle
	{ "mu.mass", { GEN_FLOATING(1.883531594E-28L), "Mass of muon" } },
	{ "mu.magnetic", { GEN_FLOATING(-4.49044826E-26L), "Magnetic moment of muon" } },
	{ "tau.mass", { GEN_FLOATING(3.16747E-27L), "Mass of tauon" } },
	// physical chemistry
	{ "boltzmann", { GEN_FLOATING(1.38064852E-23L), "Boltzmann constant" } },
	{ "avogadro", { GEN_FLOATING(6.022140857E+23L), "Avogadro constant" } },
	{ "dalton", { GEN_FLOATING(1.660539040E-27L), "Atomic Mass Constant" } },
	{ "faraday", { GEN_FLOATING(96485.33289L), "Faraday constant" } },
	{ "gas", { GEN_FLOATING(8.3144598L), "Molar gas constant" } },
	{ "molv", { GEN_FLOATING(22.413962E-03L), "Molar volume" } },
	{ "molvl", { GEN_FLOATING(22.413962L), "Molar volume in litter" } },
	{ "loschmidt", { GEN_FLOATING(2.6867811E+25L), "Loschmidt's constant" } },
	// thermal radiation
	{ "stefan", { GEN_FLOATING(5.670367E-08L), "Stefan-Boltzmann constant" } },
	{ "f.rad", { GEN_FLOATING(3.741771790E-16L), "First radiation constant" } },
	{ "s.rad", { GEN_FLOATING(1.43877736E-02L), "Second radiation constant" } },
	// agreement value
	{ "gravity", { GEN_RATIONAL2(196133, 20000), "Standard gravity" } },
	{ "atm", { GEN_INTEGER(101325), "Standard atmosphere" } },
	{ "zerod", { GEN_RATIONAL2(5463, 20), "Zero degrees Celsius in Kelvin" } },
	// Planck unit
	{ "pl.mass", { GEN_FLOATING(2.176470E-08L), "Planck mass" } },
	{ "pl.energy", { GEN_FLOATING(1.220910E+19L), "Planck energy" } },
	{ "pl.temp", { GEN_FLOATING(1.416808E+32L), "Planck temperature" } },
	{ "pl.length", { GEN_FLOATING(1.616229E-35L), "Planck length" } },
	{ "pl.time", { GEN_FLOATING(5.39116E-44L), "Planck time" } },
	// astromy
	{ "astro", { GEN_INTEGER(149597870700), "Astromical unit" } },
	{ "parsec", { GEN_FLOATING(3.085677581E+16L), "Parsec" } },
	{ "lyear", { GEN_INTEGER(9460730472580800LL), "Light year" } },
};

} // namespace engine
