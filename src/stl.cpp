/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"
#include "include/l1_norm.h"
#include "include/pyhelper.h"
#include <iostream>
#include <cstdlib>

int main(void) {

	setenv("PYTHONPATH",".",1);

	nc::array out;

	nc::matrix P = nc::ncmat(nc::shape (3,3));
	nc::matrix q = nc::ncmat(nc::shape(3,3));
		CPyInstance pyInstance;

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
				PyObject* args = PyTuple_New(2);
				// PyTuple_SetItem(args, 0, res_P);
				// PyTuple_SetItem(args, 1, res_q);
				CPyObject pValue = PyObject_CallObject(pFunc, NULL);
				CPyObject item;
				std::cout<<PyList_Size(pValue)<<std::endl;
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

		std::cout << out;

	return 0;
}
/*
	nc::shape shp (3,4);
	nc::array entry (3,0); entry[0] = 5; entry[1] = 2; entry[2] = 4;
	nc::matrix op = tz::get_toeplitz(shp, entry);
	std::cout << op ;
	std::cout << util::get_season_idx(32,14);
	std::cout <<  std::endl ;
	std::cout << util::bilateral_filter(3.2,2.1,4.3,3.2) << std::endl;
	std::cout <<  nc::reshape(op, nc::shape (4,3));
	std::cout << utils::get_relative_trends(nc::arange(6));
	std::cout << stl::seasonality_extraction(nc::arange(10));
	nc::tuple_tri ot = stl::adjustment(nc::arange(10), nc::arange(10,20),nc::arange(10),2); 
	std::cout << ot.first;
	std::cout << ot.second;
	std::cout << ot.third;
	nc::array a1; a1.push_back(0); a1.push_back(2);
	nc::array a2; a2.push_back(1);
	std::cout << l1::l1_mat(
		l1::tuple_ia(4,a1),
		l1::tuple_ia(3,a2)
		);
	std::cout << l1::l1_mat(
		nc::ncmat(nc::shape(3,3)), nc::mul(-1, nc::ncmat(nc::shape(3,3))));
	setenv("PYTHONPATH",".",1);
	CPyInstance pyInstance;
	CPyObject pName = PyUnicode_FromString("incl");
	CPyObject pModule = PyImport_Import(pName);
	if(pModule) {
		CPyObject pFunc = PyObject_GetAttrString(pModule, "getIt");
		if(pFunc && PyCallable_Check(pFunc)) {
			CPyObject pValue = PyObject_CallObject(pFunc, NULL);
			CPyObject item;
			std::cout << PyList_Size(pValue) << std::endl;
			for(int i=0; i<PyList_Size(pValue);i++) {
				item = PyList_GetItem(pValue, i);
				std::cout << "value is : " << PyLong_AsLong(item) << std::endl;
			}		
		} else {
			std::cout << "error" << std::endl;
		}
	} else {
		std::cout << "module not imported" << std::endl;
	}
*/