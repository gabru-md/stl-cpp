#ifndef L1_NORM_APPROX_H
#define L1_NORM_APPROX_H

#include <cstdlib>
#include <Python.h>
#include "numcpp.h"
#include "pyhelper.h"

namespace l1 {
	nc::array l1(nc::matrix P, nc::matrix q) {
		nc::array out;

		CPyInstance pyInstance;
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append(\".\")");

		Py_ssize_t len_P = P.size();
		Py_ssize_t len_q = q.size();

		PyObject *res_P = PyTuple_New(len_P);
		PyObject *res_q = PyTuple_New(len_q);

		for(Py_ssize_t i=0;i<len_P;i++) {
			Py_ssize_t len_in = P[i].size();
			PyObject *item = PyTuple_New(len_in);
			for(Py_ssize_t j=0;j<len_in;j++)
				PyTuple_SET_ITEM(item, j, PyFloat_FromDouble(P[i][j]));
			PyTuple_SET_ITEM(res_P, i, item);
		}

		for(Py_ssize_t i=0;i<len_q;i++) {
			Py_ssize_t len_in = q[i].size();
			PyObject *item = PyTuple_New(len_in);
			for(Py_ssize_t j=0;j<len_in;j++)
				PyTuple_SET_ITEM(item, j, PyFloat_FromDouble(q[i][j]));
			PyTuple_SET_ITEM(res_q, i, item);
		}

		CPyObject pName = PyUnicode_FromString("l1");
		CPyObject pModule = PyImport_Import(pName);
		if(pModule) {
			CPyObject pFunc = PyObject_GetAttrString(pModule, "l1");
			if(pFunc && PyCallable_Check(pFunc)) {
				CPyObject pParam = Py_BuildValue("(0)(0)", res_P, res_q);
				CPyObject pValue = PyObject_CallObject(pFunc, pParam);
				CPyObject item;
				for(int i=0; i<PyList_Size(pValue);i++) {
					item = PyList_GetItem(pValue, i);
					out.push_back(PyFloat_AsDouble(item));
				}
				
			} else {
				std::cout << "error" << std::endl;
			}
		} else {
			std::cout << "module not imported" << std::endl;
		}

		return out;
	}
}

#endif