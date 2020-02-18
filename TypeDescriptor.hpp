//Author:Christian Esperon

#ifndef EXPRINTER_TYPEDESCRIPTOR_HPP
#define EXPRINTER_TYPEDESCRIPTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Token.hpp"

class TypeDescriptor {
public:
	enum types { INTEGER, DOUBLE, BOOLEAN, STRING, NULLARRAY, STRINGARRAY, NUMBERARRAY };

	explicit TypeDescriptor(types type);
	virtual ~TypeDescriptor() = default;
    
	
	types &type();

private:
	types _type;	
};

class NumberDescriptor : public TypeDescriptor {
public:
	explicit NumberDescriptor(types descType);
	union {
		int intValue;
		double doubleValue;
		bool boolValue;
	} value;	
};

class StringDescriptor : public TypeDescriptor {
public:
	explicit StringDescriptor(types descType);
	std::string value;
};

class StringArray : public TypeDescriptor {
public:
    explicit StringArray(types descType);
	std::vector<std::string> stringArray;
    //return size of array
    int sArraySize(){return stringArray.size();}
    void sPop() { stringArray.pop_back();}
    //returns indexed value of vector
    std::string sSub(int n);
    //sets indexed value of vector
    void setSubStr(int n, std::string s) { stringArray[n] = s;}
    
};

class NumberArray : public TypeDescriptor {
public:
    explicit NumberArray(types descType);
    std::vector<int> numberArray;
    //returns size of array
    int nArraySize(){return numberArray.size(); }
    void nPop() { numberArray.pop_back();}
    //returns inexed value of vector
    int nSub(int n);
    //sets indexed value of vector
    void setSubNum(int n, int s) { numberArray[n] = s;}
};

void printValue (TypeDescriptor *desc);

bool evaluateBool(TypeDescriptor *desc);

void changeSign(TypeDescriptor *desc);

std::shared_ptr<TypeDescriptor> negate(TypeDescriptor *desc);

std::shared_ptr<TypeDescriptor> stringOperations(StringDescriptor *lValue,
												 StringDescriptor *rValue,
												 Token const &tok);

std::shared_ptr<TypeDescriptor> relOperations(NumberDescriptor *lDesc,
											  NumberDescriptor *rDesc,
											  Token const &tok);

std::shared_ptr<TypeDescriptor> arithOperations(NumberDescriptor *lDesc,
												NumberDescriptor *rDesc,
												Token const &tok);

#endif //EXPRINTER_TYPEDESCRIPTOR_HPP	
