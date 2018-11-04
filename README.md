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

-3 This is the THIRD iteration journal entry stub.
