// razlikovat sto je funkcija, a sto C keyword
funkcija();
if ();
while ();

// koristit write i read umjesto send i ...

// return funkcije je int8_t iako je return code 0 (uspjesno) ili nesto drugo ako nije uspjesno (>0)

// ostavit prazni red iznad i ispod petlji (ako nisu ugnjezdjene)

while (nesto)
{
	if (nesto_drugo)
	{
		printf...
	}
}

// nova naredba

uptime_get_s() mi izgleda bolje pase nego get_uptime_s
//recimo:
namespace_ime_funkcije_get_nesto();




// http://www.koonsolo.com/news/dewitters-tao-of-coding/
is_, has_
    Use these for all boolean values so there can be no mistake about their type. It also fits nicely in if statements. 
the_
    Start all global variables with “the_”, which makes it very clear that there is only one. 
_count
    Use _count to represent the number of elements. Don’t use plural like “bullets” instead of “bullet_count”, as plural will represent arrays. 

Arrays or other variables that represent lists must be written in plural, like enemies, walls and weapons. However, you don’t have to do this for all array types since some arrays don’t really represent a list of items. Some examples of these are “char filename[64]” or “byte buffer[128]“.

When conditions get too long, you’ll have to split the line. Try to split it up before an operator and where conditions are leastly related

switch
Also leave an extra space right behind the break. 	// ovo mi se bas i ne svidja

// MISRA on unsigned constants
// uint8_t var = 8		signed int 8 is assigned to an unsigned variable
"Rule 10.6 (required): A “U” suffix shall be applied to all constants of unsigned type."
uint8_t var = 8U
unsigned int foo = 6u;
unsigned int foo = 6U;	// best
unsigned int foo = (unsigned int)6;

////////////////////////////////////////////////////////////////////////////
javne funkcije na pocetak fajla, static na kraj radi lakseg pretrazivanja		// ili mozda ipak ne

//sve funkcije trebaju imat prototipe

I’ve mentioned several times in this blog that the main purpose of source code is not to generate a binary image but rather to educate those that come after you (including possibly a future version of yourself).

// napisat za koji kompjaler i platformu je projekt		hw isto
Place all the implicit information in main.c. Why is this you ask? Well if I was to dump three hundred source files on you, which one would you look at first? (An acceptable alternative is to state in main.c that useful information may be found in file X. Be aware however that non obvious source files sometimes get stripped out of source code archives).
Include in main as a minimum information about the compiler (including its version), the intended hardware target, and how to build the code.


// tabuliranje necega da bude poravnato
ostavit jedno prazno mjesto pa onda tab
npr za "var", "-" je space
var_[tab]= nesto;

// divajsovi
hw init funkcija koja treba napravit nesto sa HW pinom treba uzet taj pin kao argument, ako je potrebno, moze se onda napravit to kao #define ili dobit preko serijskog
funkcije ne uzimaju direktno #define
// rijeseno sa gpio libom

// Rule #4: Don't make your code unnecessarily complex
A single line of C code can have multiple side effects. Typically, though, a lengthy line of code that updates multiple variables is more difficult to understand than multiple, simple lines of code that accomplish this same objective. 

// Rule #5: Be explicit
 if (!tx_val) 
 if (tx_val == 0) 

// ala Ada 
Initialize variables before use.
Do not ignore compiler warnings.
Check return values.

you also have to make sure that your complex type functions, such as typedefed structs, are initialized first.

//Tip #2—Use enums as error types
NESTO_SUCCESS = 0,
NESTO_UNKNOWN_ERROR,
...
NESTO_LAST_ERROR
//LAST_ERROR, makes it possible to iterate over the content of the enum. That means you only have to know what the first element in the chain is. No matter how many more errors you add between the first and the last, all you have to do is check the range or iterate. Also, this last enum value gives you the total number of entries. More on this later.
// bolja ideja je ono Karlovo sa structom

 ///Tip #3—Expect to fail
func()
{
	return_value = NESTO_ERROR;
	if (uspjesno)
	{
		return_value = NESTO_SUCCESS;
	}
	else
	{
		return_value = NEST_ERROR_WRONG_NESTO;
	}
	return return_value;
}

//  Tip #4—Check input values: never trust a stranger
if (enum_t error < NESTO_LAST_ERROR);
//So, that was range checking. You should also check for NULL pointers if someone gives you an address value. You cannot check pointers for anything other than the NULL value, but this is better than nothing.
