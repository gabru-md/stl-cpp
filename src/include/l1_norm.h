#ifndef L1_NORM_APPROX_H
#define L1_NORM_APPROX_H

#include <cstdlib>
#include <Python.h>
#include "numcpp.h"

#define PMat first
#define qMat second
#define L1 "l1"

// DEPRECATED

namespace l1 {

	typedef std::pair<PyObject*, PyObject*> pyArgs;

	PyObject* pyMatrix (nc::matrix mat, nc::shape shp) {
		PyObject* pMatrix = PyList_New(shp.first);
		for(int i=0;i<shp.first;i++) {
			PyObject* pRow = PyList_New(shp.second);
			for(int j=0;j<shp.second;i++) {
				PyList_SetItem(pRow, j, PyFloat_FromDouble(mat[i][j]));
			}
			PyList_SetItem(pMatrix, i, pRow);
		}
		return pMatrix;
	}

	pyArgs L1_Args (nc::matrix P, nc::shape shpP, nc::matrix q, nc::shape shpq) {
		pyArgs args;
		args.PMat = pyMatrix(P, shpP);
		args.qMat = pyMatrix(q, shpq);
		return args;
	}

	nc::array py_L1 (nc::matrix P, nc::matrix q) {
		nc::array out;

		Py_InitializeEx(1);

		PyObject* l1_module = PyImport_ImportModule(L1);
		if(l1_module) {

			PyObject* l1_norm = PyObject_GetAttrString(l1_module, L1);
			if(l1_norm && PyCallable_Check(l1_norm)) {

				pyArgs args = L1_Args(P, nc::shape(P.size(), P[0].size()), q, nc::shape(q.size(), q[0].size()));
				PyObject* res = PyObject_CallFunction(l1_norm, "00", args.PMat, args.qMat);

				// if(PyList_Size(res) == 0) return out;
				// PyObject* item;
				// for(int i=0;i<PyList_Size(res);i++) {
				// 	item = PyList_GetItem(res, i);
				// 	out.push_back(PyFloat_AsDouble(item));
				// }

				// Py_XDECREF(item);

				Py_XDECREF(res);

			} else {
				std::cout << "l1 function not present" << std::endl;
				return out;
			}

			Py_XDECREF(l1_norm);

		} else {
			std::cout << "l1 module not present" << std::endl;
			return out;
		}

		Py_XDECREF(l1_module);

	    Py_Finalize();

	    return out;
	}

}

#endif