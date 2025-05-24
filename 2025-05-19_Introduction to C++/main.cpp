#include <iostream>

// 47:
struct newPlayer {
	std::string Name;
	int Level;
};

// 47.1:
struct raiiImage {
	int Width;
	int Height;
	//...
};

// 47.1:
class raiiMonster {
public:
	raiiMonster() : Art{ new raiiImage( 256,256 ) } {}
	~raiiMonster() {
		delete Art;
	}

	raiiImage* Art{ nullptr };
};

// 47.2:
class raiiEncounter {
public:
	raiiEncounter() :
		A{ new raiiMonster() },
		B{ new raiiMonster() },
		C{ new raiiMonster() } {
	}
	~raiiEncounter() {
		//Monster type uses RAII so they'll delete their Image resources - we don't need to worry about it here
		delete A;
		delete B;
		delete C;
	}

	raiiMonster* A{ nullptr };
	raiiMonster* B{ nullptr };
	raiiMonster* C{ nullptr };
};

// 47.3:
class raiiDungeon {
public:
	raiiDungeon() :
		A{ new raiiEncounter() },
		B{ new raiiEncounter() } {
	}
	~raiiDungeon() {
		//don't need to worry about the Monsters, as they're deleted by the Encounters
		delete A;
		delete B;
	}

	raiiEncounter* A{ nullptr };
	raiiEncounter* B{ nullptr };
};

// 47.4:
#include "lesson47/vdtorCharacterTypesA.h"
#include "lesson47/vdtorCharacterTypesB.h"

// 47.5:
void UAFRender(raiiMonster EnemyCopy) {
	//...
}

// 47.6:
class cctorMonster {
public:
	//...
	cctorMonster(const cctorMonster& Other) :
		Art{ new raiiImage{Other.Art->Width, Other.Art->Height} } {
	}

	//this might be wrong
	raiiImage* Art;
};

// 47.7A:
class aoprMonsterA {
public:
	//...
	aoprMonsterA& operator=(const aoprMonsterA& Other) {
		if (&Other == this) return *this;

		//updating existing Art resource
		*Art = *Other.Art;
		
		return *this;
	}

	//this might be wrong
	raiiImage* Art;
};

// 47.7B:
class aoprMonsterB {
public:
	//...
	aoprMonsterB& operator=(const aoprMonsterB& Other) {
		if (&Other == this) return *this;

		//deleting existing resource and creating a new one from scratch
		delete Art;
		Art = new raiiImage(*Other.Art);
		
		return *this;
	}

	raiiImage* Art;
};

// unique_ptr approach:
class uniqpMonster {
public:
	uniqpMonster() :
		Art{ std::make_unique<raiiImage>(256,256) } {
	}

	uniqpMonster(const uniqpMonster& Other) :
		Art{ std::make_unique<raiiImage>(*Other.Art) } {
	}

	uniqpMonster& operator=(const uniqpMonster& Other) {
		if (&Other == this) return *this;
		*Art = *Other.Art;
		return *this;
	}

	std::unique_ptr<raiiImage> Art;
};

// get():
void getRender(raiiImage* Art) {
	//getRender() can use Art
	//...

	//don't own it, so shouldn't delete it
}

// 47.8:
raiiImage* extGetArt() {
	return new raiiImage{ 256,256 };
}

class rctorMonster {
public:
	rctorMonster() : Art{ extGetArt() } {}
	
	std::unique_ptr<raiiImage> Art;
};

// reset():
raiiImage* resetGetArt() {
	return new raiiImage{ 256,256 };
}

class resetMonster {
public:
	//tell a smart pointer it is now responsible for a different resource from what it is currently managing
	void UpdateArt(raiiImage* NewArt) {
		Art.reset(NewArt);
	}

	std::unique_ptr<raiiImage> Art;
};

// release():
void extHandleArt(raiiImage* Art) {
	//...
	delete Art;
}

class releaseMonster {
public:
	//returns a raw pointer to the resource, so that some other object or function can take ownership, and ultimately delete it
	~releaseMonster() {
		extHandleArt(Art.release());
	}

	std::unique_ptr<raiiImage> Art;
};

int main() {
// 1: Setting up a C++ Development Environment

	//Hello World!
	std::cout << "Hello World!";

	//Hello World!My name is CogGoodbye
	std::cout << "Hello World!";
	std::cout << "My name is Cog";
	std::cout << "Goodbye";
	
	//Hello World!
	//My name is Cog
	//Goodbye
	std::cout << "\n";
	std::cout << "Hello World!";
	std::cout << "\n";
	std::cout << "My name is Cog";
	std::cout << "\n";
	std::cout << "Goodbye";
	std::cout << "\n";
	
	//Hello World!
	//My name is Cog
	//Goodbye
	std::cout << "Hello World!\n";
	std::cout << "My name is Cog\nGoodbye\n";

	//Hello World!
	//My name is Cog
	//Goodbye
	std::cout << "Hello World!";
	std::cout << std::endl;
	std::cout << "My name is Cog" << std::endl;
	std::cout << "Goodbye" << "\n";

	//Hello World!
	//My name is Cog
	//Goodbye
	std::cout << "Hello World!\n"
		<< "My name is Cog\n"
		<< "Goodbye" << "\n";

	//14 is a number
	//Another number is 41
	std::cout << 14 << " is a number\n"
		<< "Another number is " << 41 << "\n";


// 2: Objects, Variables and Types

// 47: Managing Memory Manually

	//newNumber: 41
	int* newNumber{ new int(41) };
	std::cout << "\nnewNumber: " << *newNumber;

	//newPlayer1 name: James, level: 10
	newPlayer* newPlayer1 = new newPlayer{ "James", 10 };
	std::cout << "\nnewPlayer1 name: " << newPlayer1->Name
		<< ", level: " << newPlayer1->Level;

	// delete operator:
	delete newNumber;
	delete newPlayer1;
	
	//std::cout << "\ncheck " << *newNumber; //C6001: Using uninitialized memory 'newNumber'.

	// Memory leaks
	bool continueRunning{ true };
	while (continueRunning == true) {
		int* Integer{ new int(41) };
		// Memory leaks here (if we leave our running loop as it is)

		delete Integer;
		break;
	}
	
	//Creating MonsterA
	vdtorCharacterA* vdtorCharA{ new vdtorMonsterA{} };
	//...
	delete vdtorCharA;

	//Creating MonsterB
	//Deleting MonsterB
	vdtorCharacterB* vdtorCharB{ new vdtorMonsterB{} };
	//...
	delete vdtorCharB;

	// Use After Free and Double Free Errors
	
	//example 47.5A:
	raiiMonster* UAFEnemyA{ new raiiMonster() };
	UAFRender(*UAFEnemyA);
	//ArtA Width: -572662307
	std::cout << "\nArtA Width: "
		<< UAFEnemyA->Art->Width;

	//example 47.5B:
	raiiMonster* UAFEnemyB{ new raiiMonster() };
	UAFRender(*UAFEnemyB);
	//the following program is likely to crash before it logs anything
	//UAFRender(*UAFEnemyB);
	//ArtB Width: -572662307
	std::cout << "\nArtB Width: "
		<< UAFEnemyB->Art->Width;

	//get() example:
	uniqpMonster getA;
	
	//returns the raw memory address of the object it is managing
	getRender(getA.Art.get());

	//reset() example:
	resetMonster resetA;
	resetA.UpdateArt(resetGetArt());

	//release() example:
	//it returns a raw pointer to the resource, so that some other object or function can take ownership, and ultimately delete it

	//example:
	//stack allocated memory address managed by a smart pointer is undefined behavior
	raiiImage stackArt;
	
	//the following program will crash
	//std::unique_ptr<raiiImage> stackPtr{ &stackArt };

	return 0;
}