#pragma once
#include <iostream>

namespace SomeNamespace {
	class SomeType {
	public:
		SomeType(const SomeType& Other) {
			//...
		}
		SomeType& operator=(const SomeType& Other) {
			//...
		}
		SomeType() = default;
		~SomeType() = default;
	};
}