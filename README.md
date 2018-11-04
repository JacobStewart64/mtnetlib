//HERES THE BIG IDEA
//I HONESTLY THINK IT'S POSSIBLE FOR ME TO GET A LOT OF THIS STUFF WORKING
//BUT IT'S STILL JUST A BIG IDEA RIGHT NOW
//#1 THING TO CREATE IS THE DEEP LEARNING BIT-PACKING DYNAMIC FUNCTIONS
//AND 'LIGHTNING NET' THE OPTIMIZED DEEP-LEARNING API
//THAT IS NECESSARY FOR 'STATE-OF-THE-ART'-NESS
//ALL THE OTHER STUFF DOESN'T REQUIRE MUCH 'HARD' RESEARCH, RATHER IT WILL NECESSITATE 'EASY' EXHAUSTIVE RESEARCH.
//I HAVE FINALLY LEARNT ENOUGH TO MAKE A REAL LIBRARY!
//THIS WILL BE MY FIRST REAL LIBRARY ATTEMPT.

//TO-DO: REWRITE ALL THIS AS MASTERFUL PROPAGANDA
//AND ALSO AS DEV MATERIAL TROLOLOL

//THIS WILL BE A CROSS-PLATFORM LIBRARY BUT FOR NOW JUST LINUX
//HOPEFULLY THE MANY-PLATFORMS WILL NOT HAVE SPECIFICS THAT BREAK
//THE GENERIC USE OF MY PUBLIC INTERFACES!

//BUILD CONFIGURER!
//LIKE LMBRWAF
//SETS EVERYTHING UP AND RUNS THE BUILD
//CAN PROMPT FOR OPTIONS
//OR NOT SO IT DOESN'T BLOCK AND CAN BE PART OF ANOTHER SYSTEM
//PROMPTS FOR NECESSARY OPTIONS THAT ARE LEFT OUT NO MATTER WHAT

//BUILD OPTIONS:
//CXX [option || path to compiler] - clang, gcc, or msvc
//LD  [option || path to linker] - ld, gold?
//RELEASE - builds release
//DEBUG - builds debug
//OPTIMIZATION [option] - none, low, medium, high, all, custom [flags_str]
//ENABLEBUGREPORT [path to qt - the same one used by CMake] - easily send Lightning Net a bug report regarding internal lib exceptions/assert failures. This build option fails if you do not also ENABLEEXCEPTIONS
//and or ENABLEASSERTS. Your log file for the session can be attached to the bug report. No information
//about your code besides the arguments you passed to mtnetlib functions is collected. Hardware information is collected by default but can be disabled.
//The bug report gui is created with Qt. You need Qt to build mtnetlib with this option.
//ENABLEEXCEPTIONS - enables exceptions
//ENABLEASSERTS - enables asserts
//ENABLESESSIONLOG [optional - path to logfile - defaults to cwd] - create a log file for the session (one execution of the program)
//ENABLEMONOLITHICLOG [path to logfile] - one monolithic log is created once and always appended to
//ENABLESEPERATELOGS - each mtnetlib object also produces a log specific to itself
//(you can specifiy a unique name for each object - or a default name is used - it becomes
//an unused parameter in release builds. It is relevant to specify a unique name for each object
//when any logging flag is set.)
//ARCH [option] - option is the part you put after -march=. default is -march=native NEED TO ALLOW PEOPLE TO BUILD FOR A DIF ARCH
//ENABLETESTS [option] - y, n - build the tests. need google test. option specifies whether to run the tests after a successful build. default is yes. 
//ENABLEPERFORMANCETESTS [optional, path to jme] - asio - builds the performance test tool and downloads jme files. Must have jme.
//if asio is specified as an option before the path option then you can run an independent test on your platform of mtnetlib vs boost.asio
//and report it to be put on Lightning Net's website!
//promoting the use of mtnetlib can help mtnetlib use as a shared object across the world lolol.
//CHECKSUM [option] - network, offline [directory of good sources] - checks mtnetlib sources against their checksums. If offline is specified
//you may not check sources used in the build against themselves, this will fail and explain that it doesn't do anything. You should maintain good sources
//in a secure location accessible to your system via a path.
//FROMCONFIG [id, path to config-file] - id = look at example. get all build options from a config file. You cannot
//specify any other options when this is specified. because that would be mixing oil
//and water. document the syntax of the mtnetlibbuildconf_${id}.ini
//TIMING-METHOD [compile-time [options] &&|||| run-time [options]] || DISABLED - GetTimeofDay, RDTSCP, std::chrono, OmpGetWtime, time.h?, QueryPerformanceCounter, all, etc listed with a space after each
//ENABLEINFINITEOPTIMIZATION [option] - restrict, fill, give-way, nazi (kill other processes lmao - what if a nazi scan is never improve performance lol)
//GUI-BUILD TOOL - should be simple and provides a gui for writing and running
//build confs. will be distributed as a binary with installer for basic platforms
//can automagically install dependencies like Qt and googletest
//EPIC IDEA - cmd("strip_one_time_tasks") - strips build conf of Tools and other things
//done once usually, prompt for save as, and this could be useful.
//MORE.....................

/*
  sometimes you may want the added security of a pre-authorized whitelist
  of ip-addresses or whatever that can even connect.
  provide this capability at the software level, find out if this even smart
*/

/*
  provide a generic solution for doing auth
*/

/*
  provide a generic way to be a proxy
*/

/*
  IPV4 &&|||| IPV6
*/

/*
  MAXIMALLY CONFIGURABLE IN TERMS OF RESOURCE USAGE OF A MACHINE
*/

/*
  AS FAST AS IT GETS WITHOUT HAND-CODED ASM
*/

/*
  TIMER GRAPHS:
  https://www.researchgate.net/publication/315484000_Evaluation_of_selected_C11_features_with_GCC_ICC_and_Clang
*/

/*
  MAXIMALLY CONFIGURABLE DOES NOT MEAN MANUAL CONFIGURING
*/

/*
  REAL-TIME PERFORMANCE VISUALS WITH QT
*/

/*
  COULD-TRY TO HELP COMPILER PEOPLE OPTIMIZE COMPILER FOR MY LIB WITH DANK
  DEBUGGINATING STUFF LIKE MAYBE ATOMIC AND RTDSCP AND WHATNOT
*/

/*
  WHAT KIND OF SIGNALS SHOULD I BLOCK OR HANDLE?
*/

/*
  STATE OF THE ART PRINCIPLE #1
  use self-modifying code instead of a big switch and templates
  you can get an idea of how easy this is to do for a small part of a system
  from this stack-overflow QA:
  https://stackoverflow.com/questions/11016078/is-it-possible-to-create-a-function-dynamically-during-runtime-in-c
  Do not use DLLs to achieve this - it hampers performance
  however u can tell me to use DLLs and I should learn to do it right
  according to your performance-value (weights)
*/

/*
  STATE OF THE ART PRINCIPLE #2
  optimize without boundaries
  whenever I can say I'm not doing this it's not exactly right, maybe
*/

/*
  STATE OF THE ART PRINCIPLE #3
  Commitment to Lightning Net (deep-learning)
  Light Net and Lightning Net work together, but are seperate.
  Strive to provide a framework for optimizing all applications
  through machine learning. But that is a far jump.
  This basically means simple linear-regressions won't cut it
  deep-learning provides more performant learning and greater accuracy
  My tools (and programs written with my tools) should optimize themselves
  together wholeistically targetting your production environment.
  This might mean shared objects when it satisfies your performance-value
  fall-back if I dumb - linear-regressions trololololol
*/

/*
  STATE OF THE ART PRINCIPLE #4
  USE A SUBSET OF THE LANGUAGE DESIGNED ONLY FOR A PARTICULAR SUBSET OF DYNAMIC FUNCTIONS
  THIS AVOIDS RUNNING WHOLE MASSIVE COMPILERS AND WHATNOT AT RUNTIME, AND CALLING
  system(char*);
  SO FAR I THINK I NEED TO DO ALL PERMUTATIONS OF POSSIBLE CALLS INSIDE A BINARY FUNCTION
  THAT SATISFIES SERIALIZING DATA BIT-PACKED
  ITS ALMOST MANDATORY THAT I WRITE MY OWN ASSEMBLY TO PREVENT ERRORS
  THE FUNCTIONS IN QUESTION ARE packet::read_one/read_many/write_one/write_many
  and their respective overloads
  WORKING ON OPTIMIZING THIS ASSEMBLY IS A JOB FOR A HARDWARE/COMPILER GENIUS
*/

/*
  GENERATE THE NEXT PERMUTATION OF DYNAMIC FUNCTION ON DEMAND
  BE SMALL YET AGILE
*/

/*
  ALWAYS PROVIDE THE OTHER WAY TO DO IT AND 'LEARN' WHAT'S BEST!
*/

/*
  BE DYNAMIC - EVEN IF IT MEANS RUNNING A COMPILER
*/

/*
  DYNAMIC GENERALLY INDICATES SMALLER, IT CAN MEAN FASTER TOO!
  ~INFINITEOPTIMIZATION~
*/

/*
  DREAM - YOU ARE AMAZON AND MY PRODUCT MAKES YOU MONEY
  BY BETTER UTILIZING YOUR EXISTING HARDWARE RESOURCES
*/

/*
  provide a generic way to load-balance?
*/

/*
  allow to specify paths to any external include or lib folder needed
*/

/*
  putting off perfection is how it will get done, but not put off completeness
  complete things exhaustively one at a time
*/

/*
  there is no string. it is the most abominable thing ever created.
  same for all streams but fstream. fstream is awesome.
*/

/*
  prefer c to c++ except when c++ has better available algorithms
  or is danker (GETS ME MOAR W33D MONEY FASTER)
*/

/*
  classes and functions within mtnetlib can have complicated template signatures, etc.
  everything needs to be explicit
  there must be a macro for generic spec and common specs, etc.
  e.g. this means there needs to be a nothrow macro that doesn't do anything
  or something else #ifdef ENABLEEXCEPTIONS on ALL functions!
*/

/*
  there should be an example for everything and everything should be explained in the docs
  if they read the docs, know how to code, and are decent at referencing the docs,
  there should be absolutely no real problems. People are supposed to buy this lol!
  RTFM should make people feel bad, and suddenly good when they open the docs.
*/

/*
  INFINITEOPTIMIZATION - The server keeps trying to make itself better
  through all means possible.
  This could mean rebuilding Light Net &&|||| Lightning Net at runtime
  This could mean pulling from the internet any updated dependency and
  rebuilding it as well. Auto-Patch OpenSSL?
  THIS IS A WHOLE DESIGN IN AND OF ITSELF THAT WILL DEFINE MY FRAMEWORK
  FOR INFINITEOPTIMIZATION!
  CONCEPT - LIGHT AUTHORITY - A LITTLE SERVER THAT IS REGISTERED
  WITH LIGHT SOFTWARE AND MANAGES THE LIGHT FRAME-WORK ON YOUR SYSTEM'S
  INTRANET. THEN I CAN REVIEW RELEASES OF DEPENDENCIES AND CURATE
  THE GLOBE'S VERSIONS OF SOFTWARE LOLOL.
*/

/*
  WORK SMARTER NOT HARDER
  WASTE TIME WHERE IT DOESN'T MATTER
  TO SAVE TIME WHERE IT DOES
  E.G. COMPLEX ALGS/ML/STASTICAL ANALYSIS TO CONFIGURE
  SO IT ALL JUST WORKS WELL
*/

/*
  have a way to make all things guarded by a mutex into an atomic instead!
  for crazy haxxors doing crazy things
*/

/*
  YOU JUST RUN IT IN YOUR PRODUCTION ENVIRONMENT!
*/

/*
  the http part is super big and it will only be 1.1 at first! fux idk how to make
  that perfect it's hard but I can definitely copy yihrose and get some kind of 1.1 going
*/

/*
  DTLS has always defeated me before but it would be a great attraction atm.
  Nobody has DTLS, except OpenSSL lol.
  A number of other obscure protocols and such will need to be supported somehow
  if this is going to completely replace everybody.
*/

/*
  stick to tcp as the first thing
  but don't stop working on a working templated design that provides all the flexibility
  I need until that is done (WHICH IS LESS FLEXIBILITY NOW THAT I WILL
  USE THE CONCEPT OF DYNAMIC FUNCTIONS), so I can stop iterating on that and be done now and
  have the plan done! I need to get my interfaces set in stone! it can't be released
  until the interfaces are all carefully decided upon because my public interface
  must remain backwards compatible forever and ever!
*/

/*
  wouldn't it be neat to generate the public interface as boilerplate
  so you could write your own mtnetlib implementation? lol idk it's kinda kewl.
  I think theoretically this allows you to swap in your own implementation.
  Or is this just making hacking me easier? Should I opaque a best set of crucial things?
*/

/*
  using googletest - your tests should be real tests. You must mock to the max.
  You only have to do unit tests right now, idk wtf an integration test is lol.
  they should be fast. Sleep is not allowed. String is still not allowed!
  STL Containers are allowed in everything for now... for now. But their interface
  is not to be relied upon.
*/

/*
  ML bit-packing needs to be highly-optimized and 'state-of-the-art' before
  I continue. My current conception of it is barely ML, it's more random steps.
  This needs to be [unintelligible] runtime by a background task! Prove its
  efficacy and boast of it lmao.
*/

/*
  So the ML bit-packing does this all
  it varies pack order of items (does all permutations)
  it varies pack_many occurrence (does all permutations)
  it varies MODE size and whatnot and ranges of symbol values and all that.
  finds the max necessary mode size and clamps
  tries all combinations of everything i can think of
*/

/*
  need notion of a background task, it is necessary
*/

/*
  the server must broadcast to all clients any changes to bitpacking strat
  or pack order/pack_many, etc.
  This could be server centric or client centric if you think about it?
*/

/*
  ML packing strategies FIRST!
  why? because it is a huge selling point.
  But just do an ML string packing thing for now and then work on the real one
  cuz this going to be a learning experience.
  It would do something like this -> do a linear regression on a random pack strat
  performance data points. try the next dot up on the line, linear regression, next dot up,
  until performance gains are neglible. Also do it all randomly and see what's up.
  performance_value - could be a weighted average ratio of resource usage to throughput and things like
  that.
  THIS NEEDS TO BE STATE OF THE ART OR IT'S KIND OF A DUD!
  DEEP LEARNING OR BUST
*/

//EXPLAIN THAT YOU SHOULDN'T SPECIFY TO BUILD AND REBUILD AND REBUILD THE TOOLS
//THROW AN ERROR IF THEY SPECIFY AN OPTION THAT SAYS NO TOOLS AND THEY SPECIFY A TOOL
//MAKE BUILD CONFIG FILES SO THEY CAN SAVE BUILD ARG SETS BECAUSE OTHER METHODS OF THIS ARE
//HARDER AND READING 1 SMALL FILE IS HARDLY A PERFORMANCE CONCERN IN A BUILD

//CHECKSUM TOOL!
//SET [path to build folder] [path to output file(with filename) (defaults cwd)] - finds your built libs and records their checksums in a file
//[optional - path(with filename) to input file (defaults cwd)] - uses the path to build in input file generated by SET variant
//sees if the checksums are the same and gives details. Used to identify corruption/tomfoolery/insecure build system!
//this library is not designed to be distributed in compiled and linked form and is distributed as source.
//this is to allow you the necessary capacity to build the lib specific to your very performance needs.
//it is a performance library && a convenience library. It does things the most optimal way I could think of.
//As such there is no way to provide libs to compare checksums against over the network. That would be too damn hard lol.
//The point is to make your network code scalable, maximizing speed and minimizing ram usage, and minimizing network usage,
//while taking advantage of all of your machine, or being restricted to a subset of your machine.

//WOW I NEED TO LET YOU SPECIFY WHICH COREZ GET USED IF I CAN LOLOL
//(RESEARCH THIS AND 'STATE-OF-THE-ART' IT IF CAN)
//IT SHOULD WARN IF CANT
//IT SHOULD EXPLAIN THAT THIS ISN'T POSSIBLE ON A PARTICULAR PLATFORM IF THEY ARE ON THAT PLATFORM
//IF IT IS AN UNKNOWN PLATFORM THEN BUGSPLAT

//PERFORMANCE TEST TOOL
//COMPARE WITH BOOST.ASIO IN NETWORK USAGE, RAM USAGE, CPU, THROUGHPUT, ETC
//COMES WITH SAMPLE TEST PROGRAMS TO RUN AND ALLOWS YOU TO MAKE A REPORT ABOUT YOUR TEST
//THAT I CAN POST ON THE WEBSITE

KEEP AN ITERATION JOURNAL
PLAN ITERATIONS
TRY TO LEARN WHAT TO ANTICIPATE FROM THIS JOURNALING
LEARN ABOUT THE AGILE 'DISCIPLINES' AS DESCRIBED BY UNCLE BOB THE PROGRAMMER LOL
(IMO THEY ARE PASSES YOU CAN MAKE OVER YOUR CODE AND PLANNING PASSES - HOW TO ITERATE)

ITERATION JOURNAL
-1 THIS IS THE FIRST ITERATION JOURNAL ENTRY. I ALREADY DOVE IN AND WROTE CODE.
I THINK IT'S GOOD AND MOST OF IT WILL BE PUT TO SOME KIND OF USE IN THE END.
I WANT TO KEEP DESIGNING AND WORK ON A TOTAL-PUBLIC-INTERFACE that describes
my whole public interface. Each function should have a unit-test stub. This
should make coding easier if I anticipate things well - will I?
Is a unit-test stub generator worth it? Find out on the next episode of DRAGON BALL Z!

-2 This is the SECOND iteration journal entry. Iteration 1 lasted not even a minute.
I decided I can't anticipate things well enough to create a whole public interface.
I'm going to work on ML-bit-packing instead. Research iteration. Report back.
I need to implement a deep-learning neural network!

-3 This is the THIRD iteration journal entry. I did some research in my head.
I need to compare simple-lightning-fast linear regressions ML : deep-learning neural net
where applicable. Results could be surprising. I really don't know what I'm doing here.
Ideally Lightning Net would have a full range of front and back ends but for now it's
going to linear regressions based 'ML' (if you can even call it that?) or deep-learning neural network
of little variance. I'm very much in the research and experiment phase with Lightning Net.
I have to figure out if something simple can do the job better sometimes. The curve would likely
look like y = x/2 flipped upside down and moved up a sector sometimes... I could see simple statistical
analasys linear regression easily predicting the 'intelligent vector' to set some variables with during
warmup and maintanence optimization. Warmup optimization - initial optimizering. Maintanence optimization -
happens more and more infrequently as predictions become more assured. Whole days and months and years
of data can be used to train a machine and Maintance optimization can become a Ghost. You could even
eject Maintance optimization code from the program's set RAM and lower RAM hogging, JUST WRITE IT TO THE DISK STACK LOL!
DISK STACK IS A NEAT IDEA TOO. *10 MIN LATER* - NEED TO LEARN ABOUT/COPY&&EXPERIMENT DEEP - LEARN NEURAL NET CODE/LIB... *30 seconds* I NEED TO OPTIMIZE EVERY SINGLE C++ PROGRAM ON EARTH WITH MACHINE LEARNING TECHNIQUES

BROADCAST SUSPENSION SYSTEM?
https://d2v9y0dukr6mq2.cloudfront.net/video/thumbnail/dHnxL5V/fireworks-pinwheel-catherine-wheel_e1xuowhdz__F0000.png
https://www.allisonarmour.com/wp-content/uploads/2015/12/fire-pinwheel.jpg
HOLD OLD DYNAMIC FUNCTIONS WHILE BROADCASTING NEW ONES! WRITE THE LAST ONES TO DISK ON THE THINGS DISKSTACK SO U
CAN REVERT - IT IS DOUBLE DATA KEEPING BUT THIS ALGORITHMS WITH THE DISK STACK IS TOO EAZY AND OKAY FOR NOA
DISKSTACKLENMAX??????

DETECT AND SIGNAL BAD NETWORK FROM THE CLIENT TO THE SERVER AND HAVE IT BE ABLE TO 'DELAY ITSELF' IF IT ACTUALLY MAKES
SENSE, LIKE KEEPING A BROADCAST ORDER WITH PEOPLE WITH GOOD SIGNALS GO FIRST AND POSSIBLY PEOPLE WITH BAD SIGNALS
WILL GET BETTER SIGNALS BY THE TIME IT IS THEIR TURN. THIS IS ACTUALLY SO GOOD AS A bit FOR EACH CONNECTION! WHAT
IF I CAN LEARN SOMETING???? VARIANCE! IF EXPIREMENTAL_RESULT > LAST_EXPERIMENTAL_RESULT THEN WINNING()

HAVE TO BE ABLE TO SPECIFY A PACKET THAT'S RELIABLE ON UDP

I WONDER HOW MANY IDEAS ARE THERE THAT COULD MAKE IT ALL BETTER? IDK, JUST FIND WAYS IT VARIES AND MAKE IT DO EXPERIMENTS
FOR EACH ONE AND THEN SEE WHAT WAS BEST. OR DO A PERMUTATION AND SEE IF IT WAS BETTER AND IF NOT REVERT!
MAYBE YOU DON'T EVEN NEED ML BUT I THINK A SENSIBLY HAND-CODED CLIENT CODE OF LIGHT NET SHOULD BE MORE QUICKLY AND
FULLY OPTIMIZED BY DEEP LEARNING FOR SOME REASON. WHAAAT IS IT?

THERE REALLY OUGHT TO BE CLAMPS ON EVERYTHING!

FORGOT THE STREAM PACKETS FOR ACTUAL STREAMS LIKE VIDEO, SOUND, ETC. ANYTHING THAT IS ACTUALLY A STREAM,
MAYBE LIKE AN INTERPRETED SCRIPT? XML... MOAR STUFF

VIDYA GAMES DO A LOT SIGNALLING THAT IS NOT LIKE A STREAM AT ALL. ALL APPS DO REALLY. THIS IS OFTEN IGNORED
AND SHOVED INTO A STREAM I FEEL. STREAMS DO NOT ALWAYS HELP MAKE GOOD CODE. DO THEY?

MANAGING CONNECTIONS SHOULDN'T BECOME COMPLICATED. I FEEL LIKE STREAM COULD BE AT THE LEVEL OF CONNECTION AND POSSIBLY
EVEN A WORKER TYPE TO BE LEARNINATED ABOUT. SHOULDN'T BE COMPLICATED FOR CLIENT CODE LOL.

SIMPLIFYING THINGS IS OKAY. THE IDEA ABOVE MAY BE RADICAL, BUT I CAN DEAL WITH THE CONSEQUENCES FOR SURE - IT WILL
DEFINITELY MAKE THINGS SIMPLER AND COULD EVEN BE THE WAY TO GO. IT INTRODUCES MORE VARIANCE WHILE MAKING CODING SIMPLER
IMO. WIN-WIN.

THE THREAD POOL NEEDS TO BE HANDLED DYNAMICALLY AND BASICALLY 'GLOBALLY TO LIGHT NET CODE'. I NEED TO INTRODUCE
MUCH VARIANCE THERE. THERE ARE BASIC TYPES OF JOBS LIKE STREAM JOB, GRAM JOB, ACCEPT JOB, BROADCAST JOB, OPENCLOSE JOB,
KEEP-ALIVE JOB, ETC. THERE MUST BE BETTER WORKER DISTRIBUTIONS TO HANDLE THIS KIND OF JOBBIES. YOU SHOULD BE ABLE TO WRITE
ALL YOUR CODE WITHIN MY MT FRAMEWORK AND HAVE IT ALL BE OPTIMIZED RIGHT.

DISTRIBUTED COMPUTING - KEEP THIS IN MIND. IT SEEMS TO BE A HIGHER LEVEL JOB THAN MINMAXING A MACHINE. IT COULD
POSSIBLY JUST COORDINATE AND 'LEARN' HOW TO MIN MAX WHOLE NETWORKS OF SYSTEMS. THERE COULD BE A SPECIAL
TOOL THAT JUST RUNS JOBS ON A MACHINE THAT YOU SEND IT. JOB JOB JOB JOB JOB JOB JOB JOB JOB.

HOPEFULLY 'MACHINE' IN THIS DOC MEANS VM TOO. IT REALLY NEEDS TO. OR SOMETHING LIKE THAT. MAYBE NOT LIKE VIRTUAL BOX.
BUT LIKE SWITCHES AND STUFF?

A PREDICTED SOURCE OF LEARNING 'A VARIANCE' IS SOME STATE WITH A NAME PREFIXED WITH A LOWERCASE v_
A TEMPLATE ARGUMENT CANNOT BE A SOURCE OF VARIANCE. THAT IS WHAT DYNAMIC FUNCTIONS ARE FOR.
TEMPLATES ARE FOR SPECIALIZING THE INTERFACE TO DO UDP, TCP, SSL, DTLS, HTTP, ETC.
THAT IS NOT A SOURCE OF VARIANCE LOL!

IDENTIFY ALL VARIANCE OR SOMEONE WILL!

SELF-IMPROVING SYSTEMS ARE THE BEST I THINK. THEY SAVE TONS OF DEV TIME. THEY `CAN` ACHIEVE BETTER RESULTS EVEN!
THE HOLY-GRAIL WOULD BE GETTING BEAT BY .0001% EVERY TIME BY THE BEST HAND-CODED THING. I DON'T THINK A LOT
OF MACHINE LEARNING IS SUITABLE TO TO COMPILERING THOUGH BECAUSE IT'S AN ESTIMATING GAME AND COMPILERS DON'T ESTIMATE.
MAYBE THEY DO WHEN OPTIMIZING? IDK. YOU CANT ESTIMATE THE VALIDITY OF THE BINARIE'S FAITHFUL IMPLEMENTATION OF THE STANDARD'S DECREE FOR YOUR SOURCE INSTRUCTIONS THAT'S FOR SURE. (lol)

WHY NOT JUST CHILL AND SERIALIZE A FUNCTION REAL QUICK? SOUNDS DANK.

KEEP ITERATING OVER THIS DOCUMENT, MAYBE MAKE A REAL CLEANUP PASS

COPY LMBR_WAF? IT'S POSSIBLE, IT'S FREE CODE. I CAN COPY A LOT OF LUMBERYARD PROBABLY.
KEEP THAT IN MIND. ESPECIALLY FOR THE LMBR_WAF (the `perl configure` but nah to perl, mine in c++)

I'D TAKE AN HOUR

THE FASTER YOU CAN BUILD THIS THING THE FASTER YOU CAN ITERATE ON IT LATER ON
ITERATING ON YOUR PROJECT FAST IS NECESSARY TO SUCCESSFUL DEVELOPMENT
THE BUILD MUST NOT REBUILD THINGS IT'S ALREADY BUILT AND IT MUST JUST BUILD THE RIGHT THINGS ACTUALLY
THIS MEANS THINGS NEED TO BE SEGMENTED INTO SOMETHING LIKE GEMS.
PHO REAL. MY COMPUTER SUCKS.

YOU CAN MAKE YOUR OWN GEMS AND ADD THEM TO LMBR WAF!
FOR ALL YOUR LIGHT-ORIENTED PROJECTS

vd_ - could be deleted!

I should really use typedefs for primitives and such like programming an OS kind of, right?
What exactly do I gain?
ENTER RESEARCH POINT
LEAVE RESEARCH POINT
I NEED TO IMPROVE BOOST'S `<cstdint>` and `<cstdfloat>` a little if i can one time and use it for
cross-platforming and further specializing primitive types.
This helps me change code in less places and achieve a sort of control on the variance of my types.
https://www.boost.org/doc/libs/1_55_0/boost/cstdint.hpp
https://www.boost.org/doc/libs/1_61_0/boost/cstdfloat.hpp

PREPROCESSOR CONTROL-FLOW MUST BE VERTICALLY SPACED

CODING STYLE TEMPLATE - CLASS
coding style templates establish everything for you.
don't violate the law of the template as it lay before you.


CLASS TEMPLATE {
public:
  TEMPLATE();
  ~TEMPLATE();

  VOID DO(char*, int);
  VOID DO(char*);
  VOID DO(char);
  VOID DO(int*, int)
  VOID DO(int*);
  VOID DO(int);
  VAL GET();
  VAL SET();

protected:

private:

  VAL state; //initialize in the initialization list, not here

};

___________________________________________________________________________________
DON'T MAKE TONS OF SMALL FILES, LUMP THEM A LITTLE BIT WHEN IT ACTUALLY MAKES SENSE
BREAK THEM APART WHEN IT REALLY DOESN'T (INCLUDING EXTRA CODE 100 TIMES)
-----------------------------------------------------------------------------------
YOU COULD ESTABLISH PREPROCESSOR THAT HELPS YOU CHUNK FILES PERHAPS. VARY IT?
VARIANCE IN THE BUILD SHOULD BE TAKEN ADVANTAGE OF IF THAT EVEN MAKES SENSE.
IT'S A WAY TO LEARN, TO THROW DATA AT IT AND GET RESULTS BACK.

YOU SEE LMBR_WAF INCLUDING A LOT OF LMBR_OBJ_TYPE_NAME_113.h, etc.
did they break apart their files on purpose? This doesn't seem the right approach.
A file should be as big as it can be without including extra code everwhere more than
makes it good. I think. the compiler should be capable of taking big chunks and using few threads.
if it's not written right I don't even wanna support them with some massive nibbleting of my files.

#define TEMPLATECLASSGENERICSPEC typename NOUN, \
                                 typename PERSON \

//LEAVE A LINE BLANK UNDERNEATH MACRO AND DO CONT-LINE AFTER LAST LINE

template<typename NOUN = DEF, typename PERSON = DEF> //cannot put the genericspec_macro in the class template sig
CLASS TEMPLATECLASS {
public:
  TEMPLATE();
  ~TEMPLATE();

  template<const int val = 10> //example template function definition in the template class!
  VOID DO(char*, int = val); //NOTICE - PREFER TEMPLATES WITH DEFAULTS AND PREFER TEMPLATE FUNCTIONS
                              //FIRST PREFER 'DYNAMIC FUNCTIONS' OR 'DYNAMIC OBJECTS' WHICH REWRITE RAM
                              //AND WRITE TO DISK THEIR OWN RUNNING CODE AND CAN BE SERIALIZED AND BIT-PACKED LOL
                              //THIS IS GREAT FOR DISTRIBUTED COMPUTING

  VOID DO(char*); //LAW - THE INLINE COMMENTS THAT ARE GENERATED INTO DOCS MUST NAME THE IMPLEMENTATION ARG NAME AND DESCRIPTION OF THE ARGS COMMAND OF THE FUNCTION. TRY HARD TO ESTABLISH MORE STATE WITH vd_ or v_
  VOID DO(char); //FOR CLEANLINESS WE DO NOT PUT THE ARG NAME IN THE PROTOTYPE
  VOID DO(int*, int) //ALL CONSTS SHOULD BE EXPLICITLY MARKED CONST, CONST CORRECTNESS!
  VOID DO(int*); //RVALUE-REFERENCES AND MOVE SHOULD BE USED CORRECTLY IN CONSTRUCTORS AND DESTRUCTORS (SEEMS BEST THERE - BJARNE SAID SO MAYBE?)
  VOID DO(int); //IS THAT A FD? BETTER USE THE SPECIAL TYPE OF INT. THAT HELPS WRITE PORTABILITY CODE AND WILL BE LOVED TO
  //BE DONE CORRECTLY, DON'T FORGET TO ANALYZE BOOSTS IMPLEMENTATION OF THE cstdint and cstdfloat, it's pretty darn good
  //already from reading halfway. How could it go wrong? It's just boosting me with extras in there lol.
  VAL GET();
  VAL SET();

protected:

private:

  VAL state;

}

template<TEMPLATECLASSGENERICSPEC>
TEMPLATECLASS<TEMPLATECLASSGENERICSPEC>::TEMPLATECLASS()
  : state(1)        //chop this out if u don't init list
  , imagine_macro
  , imagine_macro   //end-chop
{
  //codes gud noa
}
