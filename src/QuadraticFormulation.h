#ifndef QUADRATICFORMULATION_H
#define QUADRATICFORMULATION_H

#include <ilcplex/ilocplex.h>

class Data;

class QuadraticFormulation
{
public:
	QuadraticFormulation();
	~QuadraticFormulation();

	bool run();

private:
	const Data& data;

	IloEnv env;
	IloModel model;
	IloCplex cplex;

	IloArray<IloBoolVarArray> x;

	IloObjective obj;

	void createVariables();
	void createObjecitve();
	void createConstraints();
};

#endif
