/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"
#include "include/l1_norm.h"
#include <Python.h>
#include <iostream>
#include <cstdlib>


void solve() {
	PyObject* numpy_test_module = PyImport_ImportModule("l1");

    // retrieve 'print_matrix(); from our mnc::Slice(aodule
    PyObject* l2 = PyObject_GetAttrString(numpy_test_module, "l2");

    // no longer need to reference the module directly
    Py_XDECREF(numpy_test_module);

    PyObject* matrix = PyList_New(4);
    PyObject* list = PyList_New(3);
    PyList_SetItem(list, 0, PyLong_FromLong(2));
    PyList_SetItem(list, 1, PyLong_FromLong(3));
    PyList_SetItem(list, 2, PyLong_FromLong(4));
    PyList_SetItem(matrix, 0, list);
    PyList_SetItem(matrix, 1, list);
    PyList_SetItem(matrix, 2, list);
    PyList_SetItem(matrix, 3, list);

    // call the function with the array as its parameter
    PyObject* res = PyObject_CallFunction(l2, "O", matrix);
    // no longer need the list, free the reference
    Py_XDECREF(list);

    std::cout << PyList_Size(res) << std::endl;

    Py_XDECREF(res);
}

int main(void) {
	setenv("PYTHONPATH",".",1);
	nc::array a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	std::cout << a << " :-> " << nc::rev_slice(a,0,2) << " : " << nc::slice(a, 2);
	return 0;
	
}
// PyObject *makearray(int array[], size_t size) {
//     npy_int dim = size;
//     return PyArray_SimpleNewFromData(1, &dim, (void *)array);
// }


// PyObject *getList(double * array, size_t size) {
// 	PyObject *l = PyList_New(size);
//     for (size_t i = 0; i != size; ++i) {
//         PyList_SET_ITEM(l, i, PyFloat_FromDouble(array[i]));
// 	}
// 	return l;
// }
// int main(void) {

// 	setenv("PYTHONPATH",".",1);
// 	CPyInstance pyInstance;
// 	nc::array out;

// 	double * arr = new double [5];
// 	arr[0]=1;arr[1]=4;arr[2]=5;arr[3]=8;arr[4]=9;

// 	PyObject *myList = getList(arr, 5);
// 	nc::matrix P = nc::ncmat(nc::shape (3,3));
// 	nc::matrix q = nc::ncmat(nc::shape (3,3));
// 		// CPyInstance pyInstance;

// 		// Py_ssize_t len_P = P.size();
// 		// Py_ssize_t len_q = q.size();

// 		// PyObject *res_P = PyTuple_New(len_P);
// 		// PyObject *res_q = PyTuple_New(len_q);

// 		// for(Py_ssize_t i=0;i<len_P;i++) {
// 		// 	Py_ssize_t len_in = P[i].size();
// 		// 	PyObject *item = PyTuple_New(len_in);
// 		// 	for(Py_ssize_t j=0;j<len_in;j++)
// 		// 		PyTuple_SET_ITEM(item, j, PyFloat_FromDouble(P[i][j]));
// 		// 	PyTuple_SET_ITEM(res_P, i, item);
// 		// }

// 		// for(Py_ssize_t i=0;i<len_q;i++) {
// 		// 	Py_ssize_t len_in = q[i].size();
// 		// 	PyObject *item = PyTuple_New(len_in);
// 		// 	for(Py_ssize_t j=0;j<len_in;j++)
// 		// 		PyTuple_SET_ITEM(item, j, PyFloat_FromDouble(q[i][j]));
// 		// 	PyTuple_SET_ITEM(res_q, i, item);
// 		// }

// 		CPyObject pName = PyUnicode_FromString("l1");
// 		CPyObject pModule = PyImport_Import(pName);
// 		if(pModule) {
// 			CPyObject pFunc = PyObject_GetAttrString(pModule, "l2");
// 			if(pFunc && PyCallable_Check(pFunc)) {
// 				// PyObject* args = PyTuple_New(1);
// 				// PyTuple_SetItem(args, 0, res_P);
// 				// PyTuple_SetItem(args, 1, res_q);
// 				PyObject *arglist = Py_BuildValue("(o)", myList);
// 				CPyObject pValue = PyObject_CallObject(pFunc, arglist);
// 				CPyObject item;
// 				std::cout<<PyList_Size(pValue)<<std::endl;
// 				for(int i=0; i<PyList_Size(pValue);i++) {
// 					item = PyList_GetItem(pValue, i);
// 					out.push_back(PyFloat_AsDouble(item));
// 				}
				
// 			} else {
// 				std::cout << "error" << std::endl;
// 			}
// 		} else {
// 			std::cout << "module not imported" << std::endl;
// 		}

// 		std::cout << out;

// 	return 0;
// }
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