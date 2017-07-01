#include "EngineeringCalculator.h"

#include "OperatorsAngleConversion.h"
#include "OperatorsArithmetic.h"
#include "OperatorsBinary.h"
#include "OperatorsCast.h"
#include "OperatorsClear.h"
#include "OperatorsComplex.h"
#include "OperatorsEngineering.h"
#include "OperatorsFundamental.h"
#include "OperatorsHealthy.h"
#include "OperatorsHyperbolic.h"
#include "OperatorsInteger.h"
#include "OperatorsMatrix.h"
#include "OperatorsPower.h"
#include "OperatorsPrefix.h"
#include "OperatorsRandom.h"
#include "OperatorsStack.h"
#include "OperatorsStats.h"
#include "OperatorsTime.h"
#include "OperatorsTrigonometric.h"
#include "OperatorsTuple.h"

////==--------------------------------------------------------------------====//
// ENGINEERING CALCULATOR
// [ Update ]
// Jul 01, 2017
//====--------------------------------------------------------------------==////

namespace engine {

EngineeringCalculator::EngineeringCalculator() {
	init();
}

void EngineeringCalculator::init() {
	using namespace engine;
	auto &stackEngine = refStackEngine();
	auto &stk = stackEngine.refStack();
	auto &reg = stackEngine.refRegister();
	stk.clear();
	reg.clear();
	reg.resize(26); // alphabet
	resetOperators();
	// angle conversion
	addOperator("todms", StackOperatorPtr(new ToDmsOperator()));
	addOperator("dmsto", StackOperatorPtr(new DmsToOperator()));
	addOperator("rtod", StackOperatorPtr(new RadianToDegreeOperator()));
	addOperator("rtog", StackOperatorPtr(new RadianToGradeOperator()));
	addOperator("dtor", StackOperatorPtr(new DegreeToRadianOperator()));
	addOperator("dtog", StackOperatorPtr(new DegreeToGradeOperator()));
	addOperator("gtor", StackOperatorPtr(new GradeToRadianOperator()));
	addOperator("gtod", StackOperatorPtr(new GradeToDegreeOperator()));
	addOperator("cangr", StackOperatorPtr(new ComplementaryAngleRadian()));
	addOperator("cangd", StackOperatorPtr(new ComplementaryAngleDegree()));
	addOperator("cangg", StackOperatorPtr(new ComplementaryAngleGrade()));
	addOperator("sangr", StackOperatorPtr(new SupplementaryAngleRadian()));
	addOperator("sangd", StackOperatorPtr(new SupplementaryAngleDegree()));
	addOperator("sangg", StackOperatorPtr(new SupplementaryAngleGrade()));
	// arithmetic
	addOperator("add", StackOperatorPtr(new AddOperator()));
	addOperator("+", StackOperatorPtr(new AddOperator()));
	addOperator("sub", StackOperatorPtr(new SubOperator()));
	addOperator("-", StackOperatorPtr(new SubOperator()));
	addOperator("mul", StackOperatorPtr(new MulOperator()));
	addOperator("*", StackOperatorPtr(new MulOperator()));
	addOperator("div", StackOperatorPtr(new DivOperator()));
	addOperator("/", StackOperatorPtr(new DivOperator()));
	addOperator("mod", StackOperatorPtr(new ModOperator()));
	addOperator("%", StackOperatorPtr(new ModOperator()));
	addOperator("qm", StackOperatorPtr(new QremOperator()));
	// binary
	addOperator("not", StackOperatorPtr(new NotOperator()));
	addOperator("~", StackOperatorPtr(new NotOperator()));
	addOperator("or", StackOperatorPtr(new OrOperator()));
	addOperator("|", StackOperatorPtr(new OrOperator()));
	addOperator("and", StackOperatorPtr(new AndOperator()));
	addOperator("&", StackOperatorPtr(new AndOperator()));
	addOperator("xor", StackOperatorPtr(new XorOperator()));
	addOperator("nor", StackOperatorPtr(new NorOperator()));
	addOperator("nand", StackOperatorPtr(new NandOperator()));
	addOperator("shl", StackOperatorPtr(new ShiftLeftOperator()));
	addOperator("<<", StackOperatorPtr(new ShiftLeftOperator()));
	addOperator("shr", StackOperatorPtr(new ShiftRightOperator()));
	addOperator(">>", StackOperatorPtr(new ShiftRightOperator()));
	addOperator("sar", StackOperatorPtr(new ShiftArithmeticRightOperator()));
	addOperator(">>>", StackOperatorPtr(new ShiftArithmeticRightOperator()));
	addOperator("shlc", StackOperatorPtr(new ShiftLeftCountOperator()));
	addOperator("shrc", StackOperatorPtr(new ShiftRightCountOperator()));
	addOperator("sarc", StackOperatorPtr(new ShiftArithmeticRightCountOperator()));
	addOperator("sbl", StackOperatorPtr(new ShiftByteLeftOperator()));
	addOperator("sbr", StackOperatorPtr(new ShiftByteRightOperator()));
	addOperator("snl", StackOperatorPtr(new ShiftNibbleLeftOperator()));
	addOperator("snr", StackOperatorPtr(new ShiftNibbleRightOperator()));
	addOperator("rol", StackOperatorPtr(new RotateLeftOperator()));
	addOperator("ror", StackOperatorPtr(new RotateRightOperator()));
	// cast
	addOperator("toint", StackOperatorPtr(new ToIntegerOperator()));
	addOperator("toflt", StackOperatorPtr(new ToFloatingOperator()));
	addOperator("torat", StackOperatorPtr(new ToRationalOperator()));
	addOperator("tobool", StackOperatorPtr(new ToBooleanOperator()));
	addOperator("tobyte", StackOperatorPtr(new ToByteOperator()));
	addOperator("toword", StackOperatorPtr(new ToWordOperator()));
	addOperator("todword", StackOperatorPtr(new ToDwordOperator()));
	addOperator("toqword", StackOperatorPtr(new ToQwordOperator()));
	addOperator("tosword", StackOperatorPtr(new ToSWordOperator()));
	addOperator("tosdword", StackOperatorPtr(new ToSDwordOperator()));
	addOperator("tosqword", StackOperatorPtr(new ToSQwordOperator()));
	// clear
	addOperator("ac", StackOperatorPtr(new AllClearOperator()));
	addOperator("clear", StackOperatorPtr(new StackClearOperator()));
	addOperator("clr", StackOperatorPtr(new StackClearOperator()));
	addOperator("regclear", StackOperatorPtr(new RegisterClearOperator()));
	addOperator("rclr", StackOperatorPtr(new RegisterClearOperator()));
	// complex
	addOperator("mkc", StackOperatorPtr(new MakeComplexReImOperator()));
	addOperator("mkcmp", StackOperatorPtr(new MakeComplexReImOperator()));
	addOperator("mker", StackOperatorPtr(new MakeComplexPolRadianOperator()));
	addOperator("mked", StackOperatorPtr(new MakeComplexPolDegreeOperator()));
	addOperator("mkeg", StackOperatorPtr(new MakeComplexPolGradeOperator()));
	addOperator("re", StackOperatorPtr(new ReOperator()));
	addOperator("im", StackOperatorPtr(new ImOperator()));
	addOperator("conj", StackOperatorPtr(new ConjOperator()));
	addOperator("argr", StackOperatorPtr(new ArgRadianOperator()));
	addOperator("argd", StackOperatorPtr(new ArgDegreeOperator()));
	addOperator("argg", StackOperatorPtr(new ArgGradeOperator()));
	addOperator("reim", StackOperatorPtr(new RealImagOperator()));
	addOperator("magar", StackOperatorPtr(new MagArgRadianOperator()));
	addOperator("magad", StackOperatorPtr(new MagArgDegreeOperator()));
	addOperator("magag", StackOperatorPtr(new MagArgGradeOperator()));
	// engineering
	addOperator("radix", StackOperatorPtr(new RadixOperator()));
	addOperator("eps", StackOperatorPtr(new EpsilonOperator()));
	addOperator("tpix", StackOperatorPtr(new TpixOperator()));
	addOperator("dtpi", StackOperatorPtr(new DtpiOperator()));
	addOperator("para", StackOperatorPtr(new ParallelOperator()));
	addOperator("todb", StackOperatorPtr(new TodbOperator()));
	addOperator("dbto", StackOperatorPtr(new DbtoOperator()));
	addOperator("toeqm", StackOperatorPtr(new ToEqmOperator()));
	addOperator("eqmto", StackOperatorPtr(new EqmToOperator()));
	// fundamental
	addOperator("neg", StackOperatorPtr(new NegateOperator()));
	addOperator("pm", StackOperatorPtr(new NegateOperator()));
	addOperator("inv", StackOperatorPtr(new InvertOperator()));
	addOperator("abs", StackOperatorPtr(new AbsoluteOperator()));
	addOperator("flr", StackOperatorPtr(new FloorOperator()));
	addOperator("floor", StackOperatorPtr(new FloorOperator()));
	addOperator("ceil", StackOperatorPtr(new CeilingOperator()));
	addOperator("round", StackOperatorPtr(new RoundOperator()));
	addOperator("rnd", StackOperatorPtr(new RoundOperator()));
	addOperator("sq", StackOperatorPtr(new SquareOperator()));
	addOperator("sqrt", StackOperatorPtr(new SquareRootOperator()));
	addOperator("cbrt", StackOperatorPtr(new CubicRootOperator()));
	addOperator("hypot", StackOperatorPtr(new HypotOperator()));
	addOperator("ratio", StackOperatorPtr(new RatioOperator()));
	addOperator("perc", StackOperatorPtr(new PercentOperator()));
	addOperator("pc", StackOperatorPtr(new PercentOperator()));
	addOperator("dperc", StackOperatorPtr(new DeltaPercentOperator()));
	addOperator("dp", StackOperatorPtr(new DeltaPercentOperator()));
	addOperator("intax", StackOperatorPtr(new IncludeTaxOperator()));
	addOperator("extax", StackOperatorPtr(new ExcludeTaxOperator()));
	// healthy
	addOperator("discom", StackOperatorPtr(new DiscomfortIndexOperator()));
	addOperator("bmi", StackOperatorPtr(new BmiOperator()));
	// hyperbolic
	addOperator("sinh", StackOperatorPtr(new SinhOperator()));
	addOperator("cosh", StackOperatorPtr(new CoshOperator()));
	addOperator("tanh", StackOperatorPtr(new TanhOperator()));
	addOperator("asinh", StackOperatorPtr(new AsinhOperator()));
	addOperator("acosh", StackOperatorPtr(new AcoshOperator()));
	addOperator("atanh", StackOperatorPtr(new AtanhOperator()));
	// integer
	addOperator("inc", StackOperatorPtr(new IncrementOperator()));
	addOperator("++", StackOperatorPtr(new IncrementOperator()));
	addOperator("dec", StackOperatorPtr(new DecrementOperator()));
	addOperator("--", StackOperatorPtr(new DecrementOperator()));
	addOperator("fact", StackOperatorPtr(new FactorialOperator()));
	addOperator("!", StackOperatorPtr(new FactorialOperator()));
	addOperator("gcd", StackOperatorPtr(new GcdOperator()));
	addOperator("lcm", StackOperatorPtr(new LcmOperator()));
	addOperator("perm", StackOperatorPtr(new PermutationOperator()));
	addOperator("comb", StackOperatorPtr(new CombinationOperator()));
	// matrix
	addOperator("mkmat", StackOperatorPtr(new MakeMatrixOperator()));
	addOperator("mkumat", StackOperatorPtr(new MakeUnitMatrixOperator()));
	addOperator("mget", StackOperatorPtr(new GetElementFromMatrixOperator()));
	addOperator("mgetr", StackOperatorPtr(new GetRowFromMatrixOperator()));
	addOperator("mgetc", StackOperatorPtr(new GetColumnFromMatrixOperator()));
	addOperator("trans", StackOperatorPtr(new TransposeOperator()));
	addOperator("htrans", StackOperatorPtr(new HermitianTransposeOperator()));
	addOperator("hconj", StackOperatorPtr(new HermitianTransposeOperator()));
	addOperator("det", StackOperatorPtr(new DeterminantOperator()));
	addOperator("trace", StackOperatorPtr(new TraceOperator()));
	// power
	addOperator("^", StackOperatorPtr(new PowerOperator()));
	addOperator("**", StackOperatorPtr(new PowerOperator()));
	addOperator("pow", StackOperatorPtr(new PowerOperator()));
	addOperator("nrt", StackOperatorPtr(new NthRootOperator()));
	addOperator("logb", StackOperatorPtr(new LogBaseOperator()));
	addOperator("exp", StackOperatorPtr(new ExponentOperator()));
	addOperator("tpow", StackOperatorPtr(new Pow10Operator()));
	addOperator("bpow", StackOperatorPtr(new BinaryPowerOperator()));
	addOperator("ln", StackOperatorPtr(new NaturalLogarithmOperator()));
	addOperator("log", StackOperatorPtr(new CommonLogarithmOperator()));
	addOperator("lb", StackOperatorPtr(new BinaryLogarithmOperator()));
	// prefix
	addOperator("yocto", StackOperatorPtr(new YoctoOperator()));
	addOperator("zepto", StackOperatorPtr(new ZeptoOperator()));
	addOperator("atto", StackOperatorPtr(new AttoOperator()));
	addOperator("femto", StackOperatorPtr(new FemtoOperator()));
	addOperator("pico", StackOperatorPtr(new PicoOperator()));
	addOperator("nano", StackOperatorPtr(new NanoOperator()));
	addOperator("micro", StackOperatorPtr(new MicroOperator()));
	addOperator("milli", StackOperatorPtr(new MilliOperator()));
	addOperator("centi", StackOperatorPtr(new CentiOperator()));
	addOperator("deci", StackOperatorPtr(new DeciOperator()));
	addOperator("deca", StackOperatorPtr(new DecaOperator()));
	addOperator("hecto", StackOperatorPtr(new HectoOperator()));
	addOperator("kilo", StackOperatorPtr(new KiloOperator()));
	addOperator("mega", StackOperatorPtr(new MegaOperator()));
	addOperator("giga", StackOperatorPtr(new GigaOperator()));
	addOperator("tera", StackOperatorPtr(new TeraOperator()));
	addOperator("peta", StackOperatorPtr(new PetaOperator()));
	addOperator("exa", StackOperatorPtr(new ExaOperator()));
	addOperator("zetta", StackOperatorPtr(new ZettaOperator()));
	addOperator("yotta", StackOperatorPtr(new YottaOperator()));
	addOperator("kibi", StackOperatorPtr(new KibiOperator()));
	addOperator("mebi", StackOperatorPtr(new MebiOperator()));
	addOperator("gibi", StackOperatorPtr(new GibiOperator()));
	addOperator("tebi", StackOperatorPtr(new TebiOperator()));
	addOperator("pebi", StackOperatorPtr(new PebiOperator()));
	addOperator("exbi", StackOperatorPtr(new ExbiOperator()));
	addOperator("zebi", StackOperatorPtr(new ZebiOperator()));
	addOperator("yobi", StackOperatorPtr(new YobiOperator()));
	addOperator("toyocto", StackOperatorPtr(new ToYoctoOperator()));
	addOperator("tozepto", StackOperatorPtr(new ToZeptoOperator()));
	addOperator("toatto", StackOperatorPtr(new ToAttoOperator()));
	addOperator("tofemto", StackOperatorPtr(new ToFemtoOperator()));
	addOperator("topico", StackOperatorPtr(new ToPicoOperator()));
	addOperator("tonano", StackOperatorPtr(new ToNanoOperator()));
	addOperator("tomicro", StackOperatorPtr(new ToMicroOperator()));
	addOperator("tomilli", StackOperatorPtr(new ToMilliOperator()));
	addOperator("tocenti", StackOperatorPtr(new ToCentiOperator()));
	addOperator("todeci", StackOperatorPtr(new ToDeciOperator()));
	addOperator("todeca", StackOperatorPtr(new ToDecaOperator()));
	addOperator("tohecto", StackOperatorPtr(new ToHectoOperator()));
	addOperator("tokilo", StackOperatorPtr(new ToKiloOperator()));
	addOperator("tomega", StackOperatorPtr(new ToMegaOperator()));
	addOperator("togiga", StackOperatorPtr(new ToGigaOperator()));
	addOperator("totera", StackOperatorPtr(new ToTeraOperator()));
	addOperator("topeta", StackOperatorPtr(new ToPetaOperator()));
	addOperator("toexa", StackOperatorPtr(new ToExaOperator()));
	addOperator("tozetta", StackOperatorPtr(new ToZettaOperator()));
	addOperator("toyotta", StackOperatorPtr(new ToYottaOperator()));
	addOperator("tokibi", StackOperatorPtr(new ToKibiOperator()));
	addOperator("tomebi", StackOperatorPtr(new ToMebiOperator()));
	addOperator("togibi", StackOperatorPtr(new ToGibiOperator()));
	addOperator("totebi", StackOperatorPtr(new ToTebiOperator()));
	addOperator("topebi", StackOperatorPtr(new ToPebiOperator()));
	addOperator("toexbi", StackOperatorPtr(new ToExbiOperator()));
	addOperator("tozebi", StackOperatorPtr(new ToZebiOperator()));
	addOperator("toyobi", StackOperatorPtr(new ToYobiOperator()));
	// random
	RandomOperator::init();
	addOperator("rand", StackOperatorPtr(new RandomIntegerOperator()));
	addOperator("frand", StackOperatorPtr(new RandomFloatingOperator()));
	// stack
	addOperator("copy", StackOperatorPtr(new DupOperator()));
	addOperator("c", StackOperatorPtr(new DupOperator()));
	addOperator("dup", StackOperatorPtr(new DupOperator()));
	addOperator("swap", StackOperatorPtr(new SwapOperator()));
	addOperator("$", StackOperatorPtr(new SwapOperator()));
	addOperator("over", StackOperatorPtr(new OverOperator()));
	addOperator("o", StackOperatorPtr(new OverOperator()));
	addOperator("drop", StackOperatorPtr(new DropOperator()));
	addOperator("\\", StackOperatorPtr(new DropOperator()));
	addOperator("rot", StackOperatorPtr(new RotOperator()));
	addOperator("unrot", StackOperatorPtr(new UnrotOperator()));
	addOperator("roll", StackOperatorPtr(new RollOperator()));
	addOperator("rolld", StackOperatorPtr(new RolldOperator()));
	addOperator("pick", StackOperatorPtr(new PickOperator()));
	addOperator("unpick", StackOperatorPtr(new UnpickOperator()));
	//addOperator("pick3", StackOperatorPtr(new Pick3Operator()));
	addOperator("depth", StackOperatorPtr(new StackDepthOperator()));
	addOperator("dup2", StackOperatorPtr(new Dup2Operator()));
	addOperator("xy", StackOperatorPtr(new Dup2Operator()));
	addOperator("yx", StackOperatorPtr(new Dup2Operator()));
	addOperator("dupn", StackOperatorPtr(new DupnOperator()));
	addOperator("drop2", StackOperatorPtr(new Drop2Operator()));
	addOperator("\\\\", StackOperatorPtr(new Drop2Operator()));
	addOperator("drop3", StackOperatorPtr(new Drop3Operator()));
	addOperator("\\\\\\", StackOperatorPtr(new Drop3Operator()));
	addOperator("dropn", StackOperatorPtr(new DropnOperator()));
	addOperator("dupdup", StackOperatorPtr(new DupDupOperator()));
	addOperator("dd", StackOperatorPtr(new DupDupOperator()));
	addOperator("nip", StackOperatorPtr(new NipOperator()));
	addOperator("nipn", StackOperatorPtr(new NipnOperator()));
	addOperator("ndupn", StackOperatorPtr(new NdupnOperator()));
	// stats
	addOperator("beta", StackOperatorPtr(new BetaOperator()));
	addOperator("gamma", StackOperatorPtr(new GammaOperator()));
	addOperator("lngamma", StackOperatorPtr(new LnGammaOperator()));
	addOperator("erf", StackOperatorPtr(new ErrorFunctionOperator()));
	addOperator("erfc", StackOperatorPtr(new ComplementaryErrorFunctionOperator()));
	addOperator("sum", StackOperatorPtr(new SumOperator()));
	addOperator("prod", StackOperatorPtr(new ProdOperator()));
	addOperator("avr", StackOperatorPtr(new ArithmeticAverageOperator()));
	addOperator("gavr", StackOperatorPtr(new GeometricAverageOperator()));
	addOperator("havr", StackOperatorPtr(new HarmonicAverageOperator()));
	addOperator("sumw", StackOperatorPtr(new SumWDOperator()));
	addOperator("prodw", StackOperatorPtr(new ProdWDOperator()));
	addOperator("avrw", StackOperatorPtr(new ArithmeticAverageWDOperator()));
	addOperator("gavrw", StackOperatorPtr(new GeometricAverageWDOperator()));
	addOperator("havrw", StackOperatorPtr(new HarmonicAverageWDOperator()));
	addOperator("psum", StackOperatorPtr(new PartialSumOperator()));
	addOperator("pprod", StackOperatorPtr(new PartialProdOperator()));
	addOperator("pavr", StackOperatorPtr(new PartialArithmeticAverageOperator()));
	addOperator("pgavr", StackOperatorPtr(new PartialGeometricAverageOperator()));
	addOperator("phavr", StackOperatorPtr(new PartialHarmonicAverageOperator()));
	addOperator("psumw", StackOperatorPtr(new PartialSumWDOperator()));
	addOperator("pprodw", StackOperatorPtr(new PartialProdWDOperator()));
	addOperator("pavrw", StackOperatorPtr(new PartialArithmeticAverageWDOperator()));
	addOperator("pgavrw", StackOperatorPtr(new PartialGeometricAverageWDOperator()));
	addOperator("phavrw", StackOperatorPtr(new PartialHarmonicAverageWDOperator()));
	addOperator("alland", StackOperatorPtr(new AllAndOperator()));
	addOperator("allor", StackOperatorPtr(new AllOrOperator()));
	addOperator("allxor", StackOperatorPtr(new AllXorOperator()));
	// time conversion
	addOperator("stom", StackOperatorPtr(new SecToMinOperator()));
	addOperator("stoh", StackOperatorPtr(new SecToHourOperator()));
	addOperator("stod", StackOperatorPtr(new SecToDayOperator()));
	addOperator("stow", StackOperatorPtr(new SecToWeekOperator()));
	addOperator("mtos", StackOperatorPtr(new MinToSecOperator()));
	addOperator("mtoh", StackOperatorPtr(new MinToHourOperator()));
	addOperator("mtod", StackOperatorPtr(new MinToDayOperator()));
	addOperator("mtow", StackOperatorPtr(new MinToWeekOperator()));
	addOperator("htos", StackOperatorPtr(new HourToSecOperator()));
	addOperator("htom", StackOperatorPtr(new HourToMinOperator()));
	addOperator("htod", StackOperatorPtr(new HourToDayOperator()));
	addOperator("htow", StackOperatorPtr(new HourToWeekOperator()));
	addOperator("dtos", StackOperatorPtr(new DayToSecOperator()));
	addOperator("dtom", StackOperatorPtr(new DayToMinOperator()));
	addOperator("dtoh", StackOperatorPtr(new DayToHourOperator()));
	addOperator("dtow", StackOperatorPtr(new DayToWeekOperator()));
	addOperator("wtos", StackOperatorPtr(new WeekToSecOperator()));
	addOperator("wtom", StackOperatorPtr(new WeekToMinOperator()));
	addOperator("wtoh", StackOperatorPtr(new WeekToHourOperator()));
	addOperator("wtod", StackOperatorPtr(new WeekToDayOperator()));
	// trigonometric
	addOperator("sinr", StackOperatorPtr(new SinRadianOperator()));
	addOperator("cosr", StackOperatorPtr(new CosRadianOperator()));
	addOperator("tanr", StackOperatorPtr(new TanRadianOperator()));
	addOperator("asinr", StackOperatorPtr(new AsinRadianOperator()));
	addOperator("acosr", StackOperatorPtr(new AcosRadianOperator()));
	addOperator("atanr", StackOperatorPtr(new AtanRadianOperator()));
	addOperator("sind", StackOperatorPtr(new SinDegreeOperator()));
	addOperator("cosd", StackOperatorPtr(new CosDegreeOperator()));
	addOperator("tand", StackOperatorPtr(new TanDegreeOperator()));
	addOperator("asind", StackOperatorPtr(new AsinDegreeOperator()));
	addOperator("acosd", StackOperatorPtr(new AcosDegreeOperator()));
	addOperator("atand", StackOperatorPtr(new AtanDegreeOperator()));
	addOperator("sing", StackOperatorPtr(new SinGradeOperator()));
	addOperator("cosg", StackOperatorPtr(new CosGradeOperator()));
	addOperator("tang", StackOperatorPtr(new TanGradeOperator()));
	addOperator("asing", StackOperatorPtr(new AsinGradeOperator()));
	addOperator("acosg", StackOperatorPtr(new AcosGradeOperator()));
	addOperator("atang", StackOperatorPtr(new AtanGradeOperator()));
	// tuple
	addOperator("mrtup", StackOperatorPtr(new MakeRowTupleOperator()));
	addOperator("mctup", StackOperatorPtr(new MakeColumnTupleOperator()));
	addOperator("mrutup", StackOperatorPtr(new MakeRowUnitTupleOperator()));
	addOperator("mcutup", StackOperatorPtr(new MakeColumnUnitTupleOperator()));
	addOperator("tget", StackOperatorPtr(new GetFromTupleOperator()));
	addOperator("inner", StackOperatorPtr(new InnerProductOperator()));
	addOperator("dot", StackOperatorPtr(new InnerProductOperator()));
	addOperator("outer", StackOperatorPtr(new OuterProductOperator()));
	addOperator("cross", StackOperatorPtr(new OuterProductOperator()));
	addOperator("norm", StackOperatorPtr(new EuclidNormOperator()));
	addOperator("nsq", StackOperatorPtr(new EuclidNormSqOperator()));
	addOperator("pnorm", StackOperatorPtr(new LpNormOperator()));
	addOperator("maxnorm", StackOperatorPtr(new MaxNormOperator()));
	addOperator("cut", StackOperatorPtr(new CraveOperator()));
	addOperator("crave", StackOperatorPtr(new CraveOperator()));
}

bool EngineeringCalculator::operate(const std::string &str) {
	auto &stackEngine = refStackEngine();
	const auto &operators = refOperators();
	if (doesCommandExist(str)) {
		const auto &op = operators.at(str);
		return stackEngine.acceptOperator(op);
	}
	else {
		return true;
	}
}

} // namespace engine
