// 47.4A:
#pragma once
#include <iostream>

class vdtorCharacterA {
public:
	virtual void Render() {}
};

class vdtorMonsterA : public vdtorCharacterA {
public:
	vdtorMonsterA() :
		Art{ new raiiImage(256, 256) } {
		std::cout << "\nCreating MonsterA";
	}
	~vdtorMonsterA() {
		std::cout << "\nDeleting MonsterA";
		delete Art;
	}

	raiiImage* Art{ nullptr };
};