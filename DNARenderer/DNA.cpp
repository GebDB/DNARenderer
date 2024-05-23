#include "DNA.h"

DNA::DNA() {
	helixLength = 0;
	sequence = "";
}
void DNA::setHelixLength(double value) {
	helixLength = value;
}
double DNA::getHelixLength() const {
	return helixLength;
}
void DNA::setSequence(std::string& sequenceIn) {
	sequence = sequenceIn;
}
std::string DNA::getSequence() const{
	return sequence;
}

//load DNA sequence method