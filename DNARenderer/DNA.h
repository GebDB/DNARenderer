#ifndef DNA_H
#define DNA_H
#include <string>

class DNA {
private:
	double helixLength;
	std::string sequence;

public:
	DNA();
	void setHelixLength(double value);
	double getHelixLength() const;
	void setSequence(std::string sequenceIn);
	std::string getSequence() const;
	//load dna sequence method
};

#endif