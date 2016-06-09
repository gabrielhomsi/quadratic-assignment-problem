#include "QuadraticFormulation.h"

#include <sstream>

#include "Data.h"

using namespace std;

QuadraticFormulation::QuadraticFormulation() : model(env, "qp-qap"), data(Data::getInstance())
{
	createVariables();
	createObjecitve();
	createConstraints();

	cplex = IloCplex(model);
}

QuadraticFormulation::~QuadraticFormulation()
{
	model.end();
	env.end();
}

bool QuadraticFormulation::run()
{
#ifdef _DEBUG
	cplex.exportModel("qap.lp");
#endif

	IloBool status = cplex.solve();
	if (status == IloTrue)
	{
		cout << "Obj = " << cplex.getObjValue() << endl;

		return true;
	}
	return false;
}

void QuadraticFormulation::createVariables()
{
	x = IloArray<IloBoolVarArray>(env, data.n);
	for (int i = 0; i < data.n; i++)
	{
		x[i] = IloBoolVarArray(env, data.n);
#ifdef _DEBUG
		for (int k = 0; k < data.n; k++)
		{
			stringstream ss;
			ss << "x(" << i << ")(" << k << ")";
			x[i][k].setName(ss.str().c_str());
		}
#endif
	}
}

void QuadraticFormulation::createObjecitve()
{
	IloExpr expr(env);
	for (int i = 0; i < data.n; i++)
		for (int j = 0; j < data.n; j++)
			for (int k = 0; k < data.n; k++)
				for (int l = 0; l < data.n; l++)
					expr += data.A[i][j] * data.B[k][l] * x[i][k] * x[j][l];
	obj = IloMinimize(env, expr);
	expr.end();
	model.add(obj);
}

void QuadraticFormulation::createConstraints()
{
	for (int i = 0; i < data.n; i++)
	{
		IloExpr expr(env);
		for (int k = 0; k < data.n; k++)
			expr += x[i][k];
		IloRange range = IloRange(expr == 1);
		expr.end();
		model.add(range);
#ifdef _DEBUG
		stringstream ss;
		ss << "loc(" << i << ")";
		range.setName(ss.str().c_str());
#endif
	}

	for (int k = 0; k < data.n; k++)
	{
		IloExpr expr(env);
		for (int i = 0; i < data.n; i++)
			expr += x[i][k];
		IloRange range = IloRange(expr == 1);
		expr.end();
		model.add(range);
#ifdef _DEBUG
		stringstream ss;
		ss << "fab(" << k << ")";
		range.setName(ss.str().c_str());
#endif
	}
}
