// 47.4B
#pragma once
#include <iostream>

class vdtorCharacterB {
public:
	virtual void Render() {}

	//we can implement a virtual default destructor like this:
	virtual ~vdtorCharacterB() = default;
};

class vdtorMonsterB : public vdtorCharacterB {
public:
	vdtorMonsterB() :
		Art{ new raiiImage(256, 256) } {
		std::cout << "\nCreating MonsterB";
	}
	~vdtorMonsterB() {
		std::cout << "\nDeleting MonsterB";
		delete Art;
	}

	raiiImage* Art{ nullptr };
};