#include "UnitConverter.h"
#include "proc/GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// UNIT CONVERTER / GET UNIT NAME
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
const std::string& UnitConverter::getUnitName(const unsigned int &unit) {
	static const std::string msg = "UNKNOWN";
	if (criteria.find(unit) != criteria.end()) {
		const auto &criterion = criteria.at(unit);
		return criterion.name;
	}
	else {
		return msg;
	}
}

////==--------------------------------------------------------------------====//
// UNIT CONVERTER / CONVERT
// [ Update ]
// Dec 22, 2016
//====--------------------------------------------------------------------==////
bool UnitConverter::convert(SpElement &dst, const SpElement &src, const unsigned int &fromUnit, const unsigned int &toUnit) {
	if ((UnitConverter::U_MASK & fromUnit) != (UnitConverter::U_MASK & toUnit)) {
		return true;
	}
	if ((criteria.find(fromUnit) == criteria.end()) || (criteria.find(toUnit) == criteria.end())) {
		return true;
	}
	GeneralProcessor proc;
	const auto &fromUnitCriterion = criteria.at(fromUnit);
	const auto &toUnitCriterion = criteria.at(toUnit);
	const auto &fromStep = fromUnitCriterion.step;
	const auto &fromZero = fromUnitCriterion.zero;
	const auto &toStep = toUnitCriterion.step;
	const auto &toZero = toUnitCriterion.zero;
	try {
		SpElement p_etemp = proc.sub(src, fromZero);
		p_etemp = proc.mul(p_etemp, proc.div(fromStep, toStep));
		p_etemp = proc.add(p_etemp, toZero);
		dst = p_etemp;
	}
	catch (...) {
		return true;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// UNIT CONVERTER / KEYWORD TO UNIT
// [ Update ]
// Sep 30, 2018
//====--------------------------------------------------------------------==////
const std::map <std::string, unsigned int> UnitConverter::unitKeywords = {
	// LEN
	{ "m", LEN_M },
	{ "km", LEN_KM },
	{ "cm", LEN_CM },
	{ "mm", LEN_MM },
	{ "nmi", LEN_NMI },
	{ "yd", LEN_YD },
	{ "ft", LEN_FT },
	{ "in", LEN_IN },
	{ "mi", LEN_MI },
	{ "fath", LEN_FATH },
	{ "shaku", LEN_SHAKU },
	{ "sun", LEN_SUN },
	{ "ken", LEN_KEN },
	{ "jou", LEN_JOU },
	{ "chou", LEN_CHOU },
	{ "ri", LEN_RI },
	// LEN INV
	{ "/m", LENI_M },
	{ "/km", LENI_KM },
	{ "/cm", LENI_CM },
	{ "/mm", LENI_MM },
	{ "/nmi", LENI_NMI },
	{ "/yd", LENI_YD },
	{ "/ft", LENI_FT },
	{ "/in", LENI_IN },
	{ "/mi", LENI_MI },
	{ "/fath", LENI_FATH },
	{ "/shaku", LENI_SHAKU },
	{ "/sun", LENI_SUN },
	{ "/ken", LENI_KEN },
	{ "/jou", LENI_JOU },
	{ "/chou", LENI_CHOU },
	{ "/ri", LENI_RI },
	// AREA
	{ "m2", AR_M2 },
	{ "km2", AR_KM2 },
	{ "cm2", AR_CM2 },
	{ "mm2", AR_MM2 },
	{ "are", AR_ARE },
	{ "ha", AR_HARE },
	{ "acre", AR_ACRE },
	{ "yd2", AR_YD2 },
	{ "ft2", AR_FT2 },
	{ "in2", AR_IN2 },
	{ "mi2", AR_MI2 },
	{ "tsubo", AR_TSUBO },
	{ "isse", AR_ISSE },
	{ "ittan", AR_ITTAN },
	{ "choubu", AR_CHOUBU },
	// AREA INV
	{ "/m2", ARI_M2 },
	{ "/km2", ARI_KM2 },
	{ "/cm2", ARI_CM2 },
	{ "/mm2", ARI_MM2 },
	{ "/are", ARI_ARE },
	{ "/ha", ARI_HARE },
	{ "/acre", ARI_ACRE },
	{ "/yd2", ARI_YD2 },
	{ "/ft2", ARI_FT2 },
	{ "/in2", ARI_IN2 },
	{ "/mi2", ARI_MI2 },
	{ "/tsubo", ARI_TSUBO },
	{ "/isse", ARI_ISSE },
	{ "/ittan", ARI_ITTAN },
	{ "/choubu", ARI_CHOUBU },
	// VOLUME
	{ "m3", VOL_M3 },
	{ "km3", VOL_KM3 },
	{ "cm3", VOL_CM3 },
	{ "mm3", VOL_MM3 },
	{ "l", VOL_L },
	{ "dl", VOL_DL },
	{ "kl", VOL_KL },
	{ "ml", VOL_ML },
	{ "yd3", VOL_YD3 },
	{ "ft3", VOL_FT3 },
	{ "in3", VOL_IN3 },
	{ "mi3", VOL_MI3 },
	{ "img", VOL_IMGAL },
	{ "usg", VOL_USGAL },
	{ "gou", VOL_GOU },
	{ "shou", VOL_SHOU },
	{ "itto", VOL_ITTO },
	{ "koku", VOL_KOKU },
	// VOLUME INV
	{ "/m3", VOLI_M3 },
	{ "/km3", VOLI_KM3 },
	{ "/cm3", VOLI_CM3 },
	{ "/mm3", VOLI_MM3 },
	{ "/l", VOLI_L },
	{ "/dl", VOLI_DL },
	{ "/kl", VOLI_KL },
	{ "/ml", VOLI_ML },
	{ "/yd3", VOLI_YD3 },
	{ "/ft3", VOLI_FT3 },
	{ "/in3", VOLI_IN3 },
	{ "/mi3", VOLI_MI3 },
	{ "/img", VOLI_IMGAL },
	{ "/usg", VOLI_USGAL },
	{ "/gou", VOLI_GOU },
	{ "/shou", VOLI_SHOU },
	{ "/itto", VOLI_ITTO },
	{ "/koku", VOLI_KOKU },
	// TIME
	{ "sec", TIM_SEC },
	{ "s", TIM_SEC },
	{ "min", TIM_MIN },
	{ "hour", TIM_HOUR },
	{ "h", TIM_HOUR },
	{ "day", TIM_DAY },
	{ "d", TIM_DAY },
	{ "week", TIM_WEEK },
	{ "wk", TIM_WEEK },
	{ "year", TIM_YEAR },
	{ "yr", TIM_YEAR },
	{ "gyear", TIM_GYEAR },
	{ "jyear", TIM_JYEAR },
	// TIME INV
	{ "/sec", TIMI_SEC },
	{ "/s", TIMI_SEC },
	{ "/min", TIMI_MIN },
	{ "/hour", TIMI_HOUR },
	{ "/h", TIMI_HOUR },
	{ "/day", TIMI_DAY },
	{ "/d", TIMI_DAY },
	{ "/week", TIMI_WEEK },
	{ "/wk", TIMI_WEEK },
	{ "/year", TIMI_YEAR },
	{ "/yr", TIMI_YEAR },
	{ "/gyear", TIMI_GYEAR },
	{ "/jyear", TIMI_JYEAR },
	// MASS
	{ "kg", MS_KG },
	{ "g", MS_G },
	{ "mg", MS_MG },
	{ "ton", MS_TON },
	{ "lton", MS_LTON },
	{ "ston", MS_STON },
	{ "oz", MS_OZ },
	{ "lb", MS_LB },
	{ "kan", MS_KAN },
	{ "ryou", MS_RYOU },
	{ "momme", MS_MOMME },
	{ "kin", MS_KIN },
	// VELOCITY
	{ "m/s", VEL_MTPS },
	{ "m/min", VEL_MTPM },
	{ "km/s", VEL_KMPS },
	{ "km/h", VEL_KMPH },
	{ "kph", VEL_KMPH },
	{ "ips", VEL_IPS },
	{ "fps", VEL_FPS },
	{ "mph", VEL_MPH },
	{ "kn", VEL_KN },
	{ "kt", VEL_KN },
	// ACCELERATION
	{ "m/s2", ACL_MPS2 },
	{ "km/h/s", ACL_KMPHPS },
	{ "kph/s", ACL_KMPHPS },
	{ "gal", ACL_GAL },
	{ "ips2", ACL_IPS2 },
	{ "fps2", ACL_FPS2 },
	{ "mph/s", ACL_MPHPS },
	{ "kn/s", ACL_KNPS },
	{ "kt/s", ACL_KNPS },
	// FORCE
	{ "newton", FC_NEWTON },
	{ "dyn", FC_DYN },
	{ "kgf", FC_KGF },
	{ "gf", FC_GF },
	// PRESSURE
	{ "pa", PRS_PA },
	{ "hpa", PRS_HPA },
	{ "kpa", PRS_KPA },
	{ "mpa", PRS_MPA },
	{ "bar", PRS_BAR },
	{ "mmhg", PRS_MMHG },
	{ "inhg", PRS_INHG },
	// ENERGY
	{ "j", EN_J },
	{ "kj", EN_KJ },
	{ "mj", EN_MJ },
	{ "ev", EN_EV },
	{ "kev", EN_KEV },
	{ "mev", EN_MEV },
	{ "gev", EN_GEV },
	{ "cal", EN_CAL },
	{ "kcal", EN_KCAL },
	{ "ttnt", EN_TTNT },
	{ "kwh", EN_KWH },
	{ "btu", EN_BTU },
	// TEMPERATURE
	{ "kel", TMP_K },
	{ "degc", TMP_C },
	{ "degr", TMP_R },
	{ "degf", TMP_F },
};

////==--------------------------------------------------------------------====//
// UNIT CONVERTER / KEYWORD TO UNIT
// [ Update ]
// Mar 06, 2017
//====--------------------------------------------------------------------==////
const std::map <unsigned int, CoversionCriterion> UnitConverter::criteria = {
	// LENGTH
	{ LEN_M, { "m", U_LENGTH, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ LEN_KM, { "km", U_LENGTH, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ LEN_CM, { "cm", U_LENGTH, GEN_RATIONAL2(1, 100), GEN_INTEGER(0) } },
	{ LEN_MM, { "mm", U_LENGTH, GEN_RATIONAL2(1, 1000), GEN_INTEGER(0) } },
	{ LEN_NMI, { "nmi", U_LENGTH, GEN_INTEGER(1852), GEN_INTEGER(0) } },
	{ LEN_YD, { "yd", U_LENGTH, GEN_RATIONAL2(1143, 1250), GEN_INTEGER(0) } },
	{ LEN_FT, { "ft", U_LENGTH, GEN_RATIONAL2(381, 1250), GEN_INTEGER(0) } },
	{ LEN_IN, { "in", U_LENGTH, GEN_RATIONAL2(127, 5000), GEN_INTEGER(0) } },
	{ LEN_MI, { "mi", U_LENGTH, GEN_RATIONAL2(201168, 125), GEN_INTEGER(0) } },
	{ LEN_FATH, { "fath", U_LENGTH, GEN_RATIONAL2(1143, 625), GEN_INTEGER(0) } },
	{ LEN_SHAKU, { "shaku", U_LENGTH, GEN_RATIONAL2(10, 33), GEN_INTEGER(0) } },
	{ LEN_SUN, { "sun", U_LENGTH, GEN_RATIONAL2(1, 33), GEN_INTEGER(0) } },
	{ LEN_KEN, { "ken", U_LENGTH, GEN_RATIONAL2(20, 11), GEN_INTEGER(0) } },
	{ LEN_JOU, { "jou", U_LENGTH, GEN_RATIONAL2(100, 33), GEN_INTEGER(0) } },
	{ LEN_CHOU, { "chou", U_LENGTH, GEN_RATIONAL2(1200, 11), GEN_INTEGER(0) } },
	{ LEN_RI, { "ri", U_LENGTH, GEN_RATIONAL2(43200, 11), GEN_INTEGER(0) } },
	// LENGTH INV
	{ LENI_M, { "/m", U_LENGTH_I, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ LENI_KM, { "/km", U_LENGTH_I, GEN_RATIONAL2(1, 1000), GEN_INTEGER(0) } },
	{ LENI_CM, { "/cm", U_LENGTH_I, GEN_INTEGER(100), GEN_INTEGER(0) } },
	{ LENI_MM, { "/mm", U_LENGTH_I, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ LENI_NMI, { "/nmi", U_LENGTH_I, GEN_RATIONAL2(1, 1852), GEN_INTEGER(0) } },
	{ LENI_YD, { "/yard", U_LENGTH_I, GEN_RATIONAL2(1250, 1143), GEN_INTEGER(0) } },
	{ LENI_FT, { "/feet", U_LENGTH_I, GEN_RATIONAL2(1250, 381), GEN_INTEGER(0) } },
	{ LENI_IN, { "/inch", U_LENGTH_I, GEN_RATIONAL2(5000, 127), GEN_INTEGER(0) } },
	{ LENI_MI, { "/mile", U_LENGTH_I, GEN_RATIONAL2(125, 201168), GEN_INTEGER(0) } },
	{ LENI_FATH, { "/fath", U_LENGTH_I, GEN_RATIONAL2(625, 1143), GEN_INTEGER(0) } },
	{ LENI_SHAKU, { "/shaku", U_LENGTH_I, GEN_RATIONAL2(33, 10), GEN_INTEGER(0) } },
	{ LENI_SUN, { "/sun", U_LENGTH_I, GEN_INTEGER(33), GEN_INTEGER(0) } },
	{ LENI_KEN, { "/ken", U_LENGTH_I, GEN_RATIONAL2(11, 20), GEN_INTEGER(0) } },
	{ LENI_JOU, { "/jou", U_LENGTH_I, GEN_RATIONAL2(33, 100), GEN_INTEGER(0) } },
	{ LENI_CHOU, { "/chou", U_LENGTH_I, GEN_RATIONAL2(11, 1200), GEN_INTEGER(0) } },
	{ LENI_RI, { "/ri", U_LENGTH_I, GEN_RATIONAL2(11, 43200), GEN_INTEGER(0) } },
	// AREA
	{ AR_M2, { "m2", U_AREA, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ AR_KM2, { "km2", U_AREA, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ AR_CM2, { "cm2", U_AREA, GEN_RATIONAL2(1, 10000), GEN_INTEGER(0) } },
	{ AR_MM2, { "mm2", U_AREA, GEN_RATIONAL2(1, 1000000), GEN_INTEGER(0) } },
	{ AR_ARE, { "are", U_AREA, GEN_INTEGER(100), GEN_INTEGER(0) } },
	{ AR_HARE, { "ha", U_AREA, GEN_INTEGER(10000), GEN_INTEGER(0) } },
	{ AR_ACRE, { "acre", U_AREA, GEN_RATIONAL2(316160658LL, 78125LL), GEN_INTEGER(0) } },
	{ AR_YD2, { "yd2", U_AREA, GEN_RATIONAL2(1306449LL, 1562500LL), GEN_INTEGER(0) } },
	{ AR_FT2, { "ft2", U_AREA, GEN_RATIONAL2(145161LL, 1562500LL), GEN_INTEGER(0) } },
	{ AR_IN2, { "in2", U_AREA, GEN_RATIONAL2(16129LL, 25000000LL), GEN_INTEGER(0) } },
	{ AR_MI2, { "mi2", U_AREA, GEN_RATIONAL2(40468564224LL, 15625LL), GEN_INTEGER(0) } },
	{ AR_TSUBO, { "tsubo", U_AREA, GEN_RATIONAL2(400, 121), GEN_INTEGER(0) } },
	{ AR_ISSE, { "isse", U_AREA, GEN_RATIONAL2(12000, 121), GEN_INTEGER(0) } },
	{ AR_ITTAN, { "ittan", U_AREA, GEN_RATIONAL2(120000, 121), GEN_INTEGER(0) } },
	{ AR_CHOUBU, { "choubu", U_AREA, GEN_RATIONAL2(1200000, 121), GEN_INTEGER(0) } },
	// AREA INV
	{ ARI_M2, { "/m2", U_AREA_I, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ ARI_KM2, { "/km2", U_AREA_I, GEN_RATIONAL2(1, 1000000), GEN_INTEGER(0) } },
	{ ARI_CM2, { "/cm2", U_AREA_I, GEN_INTEGER(10000), GEN_INTEGER(0) } },
	{ ARI_MM2, { "/mm2", U_AREA_I, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ ARI_ARE, { "/are", U_AREA_I, GEN_RATIONAL2(1, 100), GEN_INTEGER(0) } },
	{ ARI_HARE, { "/ha", U_AREA_I, GEN_RATIONAL2(1, 10000), GEN_INTEGER(0) } },
	{ ARI_ACRE, { "/acre", U_AREA_I, GEN_RATIONAL2(78125LL, 316160658LL), GEN_INTEGER(0) } },
	{ ARI_YD2, { "/yd2", U_AREA_I, GEN_RATIONAL2(1562500LL, 1306449LL), GEN_INTEGER(0) } },
	{ ARI_FT2, { "/ft2", U_AREA_I, GEN_RATIONAL2(1562500LL, 145161LL), GEN_INTEGER(0) } },
	{ ARI_IN2, { "/in2", U_AREA_I, GEN_RATIONAL2(25000000LL, 16129LL), GEN_INTEGER(0) } },
	{ ARI_MI2, { "/mi2", U_AREA_I, GEN_RATIONAL2(15625LL, 40468564224LL), GEN_INTEGER(0) } },
	{ ARI_TSUBO, { "/tsubo", U_AREA_I, GEN_RATIONAL2(121, 400), GEN_INTEGER(0) } },
	{ ARI_ISSE, { "/isse", U_AREA_I, GEN_RATIONAL2(121, 12000), GEN_INTEGER(0) } },
	{ ARI_ITTAN, { "/ittan", U_AREA_I, GEN_RATIONAL2(121, 120000), GEN_INTEGER(0) } },
	{ ARI_CHOUBU, { "/choubu", U_AREA_I, GEN_RATIONAL2(121, 1200000), GEN_INTEGER(0) } },
	// VOLUME
	{ VOL_M3, { "m3", U_VOLUME, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ VOL_KM3, { "km3", U_VOLUME, GEN_INTEGER(1000000000LL), GEN_INTEGER(0) } },
	{ VOL_CM3, { "cm3", U_VOLUME, GEN_RATIONAL2(1, 1000000LL), GEN_INTEGER(0) } },
	{ VOL_MM3, { "mm3", U_VOLUME, GEN_RATIONAL2(1, 1000000000LL), GEN_INTEGER(0) } },
	{ VOL_L, { "L", U_VOLUME, GEN_RATIONAL2(1, 1000), GEN_INTEGER(0) } },
	{ VOL_DL, { "dL", U_VOLUME, GEN_RATIONAL2(1, 10000), GEN_INTEGER(0) } },
	{ VOL_KL, { "kL", U_VOLUME, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ VOL_ML, { "mL", U_VOLUME, GEN_RATIONAL2(1, 1000000), GEN_INTEGER(0) } },
	{ VOL_YD3, { "yd3", U_VOLUME, GEN_RATIONAL2(1493271207LL, 1953125000LL), GEN_INTEGER(0) } },
	{ VOL_FT3, { "ft3", U_VOLUME, GEN_RATIONAL2(55306341LL, 1953125000LL), GEN_INTEGER(0) } },
	{ VOL_IN3, { "in3", U_VOLUME, GEN_RATIONAL2(2048383LL, 125000000000LL), GEN_INTEGER(0) } },
	{ VOL_MI3, { "mi3", U_VOLUME, GEN_RATIONAL2(8140980127813632LL, 1953125LL), GEN_INTEGER(0) } },
	{ VOL_IMGAL, { "gal(Imp)", U_VOLUME, GEN_RATIONAL2(454609LL, 100000000LL), GEN_INTEGER(0) } },
	{ VOL_USGAL, { "gal(US)", U_VOLUME, GEN_RATIONAL2(473176473LL, 125000000000LL), GEN_INTEGER(0) } },
	{ VOL_GOU, { "gou", U_VOLUME, GEN_RATIONAL2(2401, 13310000), GEN_INTEGER(0) } },
	{ VOL_SHOU, { "shou", U_VOLUME, GEN_RATIONAL2(2401, 1331000), GEN_INTEGER(0) } },
	{ VOL_ITTO, { "itto", U_VOLUME, GEN_RATIONAL2(2401, 133100), GEN_INTEGER(0) } },
	{ VOL_KOKU, { "koku", U_VOLUME, GEN_RATIONAL2(2401, 13310), GEN_INTEGER(0) } },
	// VOLUME INV
	{ VOLI_M3, { "/m3", U_VOLUME_I, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ VOLI_KM3, { "/km3", U_VOLUME_I, GEN_RATIONAL2(1, 1000000000LL), GEN_INTEGER(0) } },
	{ VOLI_CM3, { "/cm3", U_VOLUME_I, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ VOLI_MM3, { "/mm3", U_VOLUME_I, GEN_INTEGER(1000000000LL), GEN_INTEGER(0) } },
	{ VOLI_L, { "/L", U_VOLUME_I, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ VOLI_DL, { "/dL", U_VOLUME_I, GEN_INTEGER(10000), GEN_INTEGER(0) } },
	{ VOLI_KL, { "/kL", U_VOLUME_I, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ VOLI_ML, { "/mL", U_VOLUME_I, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ VOLI_YD3, { "/yd3", U_VOLUME_I, GEN_RATIONAL2(1953125000LL, 1493271207LL), GEN_INTEGER(0) } },
	{ VOLI_FT3, { "/ft3", U_VOLUME_I, GEN_RATIONAL2(1953125000LL, 55306341LL), GEN_INTEGER(0) } },
	{ VOLI_IN3, { "/in3", U_VOLUME_I, GEN_RATIONAL2(125000000000LL, 2048383LL), GEN_INTEGER(0) } },
	{ VOLI_MI3, { "/mi3", U_VOLUME_I, GEN_RATIONAL2(1953125LL, 8140980127813632LL), GEN_INTEGER(0) } },
	{ VOLI_IMGAL, { "/gal(Imp)", U_VOLUME_I, GEN_RATIONAL2(100000000LL, 454609LL), GEN_INTEGER(0) } },
	{ VOLI_USGAL, { "/gal(US)", U_VOLUME_I, GEN_RATIONAL2(125000000000LL, 473176473LL), GEN_INTEGER(0) } },
	{ VOLI_GOU, { "/gou", U_VOLUME, GEN_RATIONAL2(13310000, 2401), GEN_INTEGER(0) } },
	{ VOLI_SHOU, { "/shou", U_VOLUME, GEN_RATIONAL2(1331000, 2401), GEN_INTEGER(0) } },
	{ VOLI_ITTO, { "/itto", U_VOLUME, GEN_RATIONAL2(133100, 2401), GEN_INTEGER(0) } },
	{ VOLI_KOKU, { "/koku", U_VOLUME, GEN_RATIONAL2(13310, 2401), GEN_INTEGER(0) } },
	// TIME
	{ TIM_SEC, { "sec", U_TIME, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ TIM_MIN, { "min", U_TIME, GEN_INTEGER(60), GEN_INTEGER(0) } },
	{ TIM_HOUR, { "hour", U_TIME, GEN_INTEGER(3600), GEN_INTEGER(0) } },
	{ TIM_DAY, { "day", U_TIME, GEN_INTEGER(86400), GEN_INTEGER(0) } },
	{ TIM_WEEK, { "week", U_TIME, GEN_INTEGER(604800), GEN_INTEGER(0) } },
	{ TIM_YEAR, { "year", U_TIME, GEN_INTEGER(31536000), GEN_INTEGER(0) } },
	{ TIM_GYEAR, { "year.G", U_TIME, GEN_INTEGER(31556952), GEN_INTEGER(0) } },
	{ TIM_JYEAR, { "year.J", U_TIME, GEN_INTEGER(31557600), GEN_INTEGER(0) } },
	// TIME INV
	{ TIMI_SEC, { "/sec", U_TIME_I, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ TIMI_MIN, { "/min", U_TIME_I, GEN_RATIONAL2(1, 60), GEN_INTEGER(0) } },
	{ TIMI_HOUR, { "/hour", U_TIME_I, GEN_RATIONAL2(1, 3600), GEN_INTEGER(0) } },
	{ TIMI_DAY, { "/day", U_TIME_I, GEN_RATIONAL2(1, 86400), GEN_INTEGER(0) } },
	{ TIMI_WEEK, { "/week", U_TIME_I, GEN_RATIONAL2(1, 604800), GEN_INTEGER(0) } },
	{ TIMI_YEAR, { "/year", U_TIME_I, GEN_RATIONAL2(1, 31536000), GEN_INTEGER(0) } },
	{ TIMI_GYEAR, { "/year.G", U_TIME_I, GEN_RATIONAL2(1, 31556952), GEN_INTEGER(0) } },
	{ TIMI_JYEAR, { "/year.J", U_TIME_I, GEN_RATIONAL2(1, 31557600), GEN_INTEGER(0) } },
	// MASS
	{ MS_KG, { "kg", U_MASS, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ MS_G, { "gram", U_MASS, GEN_RATIONAL2(1, 1000), GEN_INTEGER(0) } },
	{ MS_MG, { "mg", U_MASS, GEN_RATIONAL2(1, 1000000), GEN_INTEGER(0) } },
	{ MS_TON, { "ton", U_MASS, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ MS_LTON, { "long ton", U_MASS, GEN_RATIONAL2(317514659, 312500), GEN_INTEGER(0) } },
	{ MS_STON, { "short ton", U_MASS, GEN_RATIONAL2(45359237, 50000), GEN_INTEGER(0) } },
	{ MS_OZ, { "oz", U_MASS, GEN_RATIONAL2(45359237, 1600000000), GEN_INTEGER(0) } },
	{ MS_LB, { "lb", U_MASS, GEN_RATIONAL2(45359237, 100000000), GEN_INTEGER(0) } },
	{ MS_KAN, { "kan", U_MASS, GEN_RATIONAL2(15, 4), GEN_INTEGER(0) } },
	{ MS_RYOU, { "ryou", U_MASS, GEN_RATIONAL2(3, 80), GEN_INTEGER(0) } },
	{ MS_MOMME, { "momme", U_MASS, GEN_RATIONAL2(3, 800), GEN_INTEGER(0) } },
	{ MS_KIN, { "kin", U_MASS, GEN_RATIONAL2(3, 5), GEN_INTEGER(0) } },
	// VELOCITY
	{ VEL_MTPS, { "m/s", U_VEL, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ VEL_MTPM, { "m/min", U_VEL, GEN_RATIONAL2(1, 60), GEN_INTEGER(0) } },
	{ VEL_KMPS, { "km/s", U_VEL, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ VEL_KMPH, { "km/h", U_VEL, GEN_RATIONAL2(5, 18), GEN_INTEGER(0) } },
	{ VEL_IPS, { "ips", U_VEL, GEN_RATIONAL2(127, 5000), GEN_INTEGER(0) } },
	{ VEL_FPS, { "fps", U_VEL, GEN_RATIONAL2(381, 1250), GEN_INTEGER(0) } },
	{ VEL_MPH, { "mph", U_VEL, GEN_RATIONAL2(1397, 3125), GEN_INTEGER(0) } },
	{ VEL_KN, { "kn", U_VEL, GEN_RATIONAL2(463, 900), GEN_INTEGER(0) } },
	// ACCELERATION
	{ ACL_MPS2, { "m/s2", U_ACCEL, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ ACL_KMPHPS, { "km/h/s", U_ACCEL, GEN_RATIONAL2(5, 18), GEN_INTEGER(0) } },
	{ ACL_GAL, { "Gal", U_ACCEL, GEN_RATIONAL2(1, 100), GEN_INTEGER(0) } },
	{ ACL_IPS2, { "ips2", U_ACCEL, GEN_RATIONAL2(127, 5000), GEN_INTEGER(0) } },
	{ ACL_FPS2, { "fps2", U_ACCEL, GEN_RATIONAL2(381, 1250), GEN_INTEGER(0) } },
	{ ACL_MPHPS, { "mph/s", U_ACCEL, GEN_RATIONAL2(1397, 3125), GEN_INTEGER(0) } },
	{ ACL_KNPS, { "kn/s", U_ACCEL, GEN_RATIONAL2(463, 900), GEN_INTEGER(0) } },
	// FORCE
	{ FC_NEWTON, { "N", U_FORCE, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ FC_DYN, { "dyn", U_FORCE, GEN_RATIONAL2(1, 100000), GEN_INTEGER(0) } },
	{ FC_KGF, { "kgf", U_FORCE, GEN_RATIONAL2(196133, 20000), GEN_INTEGER(0) } },
	{ FC_GF, { "gf", U_FORCE, GEN_RATIONAL2(196133, 20000000), GEN_INTEGER(0) } },
	// PRESSURE
	{ PRS_PA, { "Pa", U_PRESS, GEN_INTEGER(1), GEN_INTEGER(0) } }, 
	{ PRS_HPA, { "hPa", U_PRESS, GEN_INTEGER(100), GEN_INTEGER(0) } },
	{ PRS_KPA, { "kPa", U_PRESS, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ PRS_MPA, { "MPa", U_PRESS, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ PRS_BAR, { "bar", U_PRESS, GEN_INTEGER(100000), GEN_INTEGER(0) } },
	{ PRS_MMHG, { "mmHg", U_PRESS, GEN_RATIONAL2(101325, 760), GEN_INTEGER(0) } },
	{ PRS_INHG, { "inHg", U_PRESS, GEN_RATIONAL2(21164929, 6250), GEN_INTEGER(0) } },
	// ENERGY
	{ EN_J, { "J", U_ENERGY, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ EN_KJ, { "kJ", U_ENERGY, GEN_INTEGER(1000), GEN_INTEGER(0) } },
	{ EN_MJ, { "MJ", U_ENERGY, GEN_INTEGER(1000000), GEN_INTEGER(0) } },
	{ EN_EV, { "eV", U_ENERGY, GEN_FLOATING(1.6021766208E-19L), GEN_INTEGER(0) } },
	{ EN_KEV, { "keV", U_ENERGY, GEN_FLOATING(1.6021766208E-16L), GEN_INTEGER(0) } },
	{ EN_MEV, { "MeV", U_ENERGY, GEN_FLOATING(1.6021766208E-13L), GEN_INTEGER(0) } },
	{ EN_GEV, { "GeV", U_ENERGY, GEN_FLOATING(1.6021766208E-10L), GEN_INTEGER(0) } },
	{ EN_CAL, { "cal", U_ENERGY, GEN_RATIONAL2(523, 125), GEN_INTEGER(0) } },
	{ EN_KCAL, { "kcal", U_ENERGY, GEN_INTEGER(4184), GEN_INTEGER(0) } },
	{ EN_TTNT, { "ton of TNT", U_ENERGY, GEN_INTEGER(4184000000), GEN_INTEGER(0) } },
	{ EN_KWH, { "kWh", U_ENERGY, GEN_INTEGER(3600000), GEN_INTEGER(0) } },
	{ EN_BTU, { "Btu", U_ENERGY, GEN_RATIONAL2(52753, 50), GEN_INTEGER(0) } },
	// TEMPERATURE
	{ TMP_K, { "Kelvin", U_TEMP, GEN_INTEGER(1), GEN_INTEGER(0) } },
	{ TMP_C, { "Celsius", U_TEMP, GEN_INTEGER(1), GEN_RATIONAL2(-5463, 20) } },
	{ TMP_R, { "Rankine", U_TEMP, GEN_RATIONAL2(5, 9), GEN_INTEGER(0) } },
	{ TMP_F, { "Fahrenheit", U_TEMP, GEN_RATIONAL2(5, 9), GEN_RATIONAL2(-45967, 100) } },
};

} // namespace engine
