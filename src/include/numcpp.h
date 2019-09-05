#ifndef NUMCPP_H
#define NUMCPP_H

#include <vector>
#include <iostream>

using namespace std;

namespace nc {

	typedef vector<double> array;
	typedef vector<vector<double> > matrix;
	typedef pair<int, int> shape;
	typedef pair<array, int> od_array;
	typedef pair<int, int> tuple_i;
	typedef pair<double, double> tuple_d;

	// creates a new matrix from a shape
	matrix ncmat (shape shp) {
		matrix out;
		for(int i=0;i<shp.first;i++) {
			out.push_back(array(shp.second,0.0));
		}
		return out;
	}

	matrix ncmat (array in, shape shp) {
		matrix out = ncmat(shp);
		int i = 0, end = in.size();
		for(int j=0;j<shp.first;j++) {
			for(int k=0;k<shp.second;k++) {
				out[j][k] = in[i++];
			}
		}
		return out;
	}

	// flattens the matrix to array
	array flatten (matrix in) {
		array out;
		for(int i=0;i<in.size();i++)
			for(int j=0;j<in[i].size();j++)
				out.push_back(in[i][j]);

		return out;
	}


	matrix reshape (matrix in, shape shp) {
		array arr_in = flatten(in);
		if(shp.first*shp.second != arr_in.size())
			return ncmat(shp);
		return ncmat(arr_in, shp);
	}

	array concat (od_array in1, array in2, int offset) {
		array out;
		int order = in1.second;
		if(order == 1) {
			for(int i=0;i<in1.first.size();i++) out.push_back(in1.first[i]);
		} else {
			for(int i=in1.first.size()-1;i>=0;i--) out.push_back(in1.first[i]);
		}
		for(int i=offset;i<in2.size();i++) out.push_back(in2[i]);
		return out;
	}

	array concat (array a1, array a2) {
		array out;
		for(int i=0;i<a1.size();i++) out.push_back(a1[i]);
		for(int i=0;i<a2.size();i++) out.push_back(a2[i]);
		return out;
	}

	array slice (array in, int start, int end) {
		array out;
		if(end > in.size()) {
			return out; 
		}
		for(int i=start;i<end;i++) out.push_back(in[i]);
		return out;
	}

	array slice (array in, int start) {
		return slice(in, start, in.size());
	}

	array arange (double start, double end) {
		array out;
		for(int i=start;i<end;i+=1.0)
			out.push_back(i);
		return out;
	}

	void flush (matrix in) {
		for(int i=0;i<in.size();i++) {
			for(int j=0;j<in[i].size();j++)
				std::cout << in[i][j] << " ";
			std::cout << std::endl; 
		}
	}

	void flush (array in) {
		for(int i=0;i<in.size();i++) 
			std::cout << in[i] << " ";
		std::cout << std::endl; 
	}


	array add (double val, array in) {
		array out;
		for(int i=0;i<in.size();i++)
			out.push_back(in[i]+val);
		return out;
	}

	array add (array in, double val) {
		return add(val, in);
	}

	array mul (double val, array in) {
		array out;
		for(int i=0;i<in.size();i++)
			out.push_back(in[i]*val);
		return out;
	}

	array mul (array in1, array in2) {
		array out;
		if(in1.size() != in2.size())
			return out;
		for(int i=0;i<in1.size();i++)
			out.push_back(in1[i]*in2[i]);
		return out;
	}

	array mul (array in, double val) {
		return mul(val, in);
	}

	double sum (array in) {
		double sum = 0;
		for(int i=0;i<in.size();i++) sum += in[i];
		return sum;
	}

	// creates array of zeros
	array zeros (int size) { return array(size, 0.0);	}

	matrix zeros (shape shp) { return ncmat(shp); }

	array concat (double el, array a2) { return concat(array(1,el), a2); }

	array concat (array a1, double el) { return concat(a1, array(1,el)); }

	array concat (double el1, double el2) { return concat(array(1,el1), array(1,el2)); }

	// flattens the array
	array flatten (array in) { return in; }

	array arange (int end) {
		return arange(0, end);
	}

}


template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T> >& in) {
	os << "[ ";
    for(int i=0;i<in.size();i++) {
    	if(i==0) os << "[ " ;
    	else os << " [ ";
		for(int j=0;j<in[i].size();j++)
			os << in[i][j] << " ";
		if(i==in.size()-1) os << "]";
		else os << "], ";
		if(i!=in.size()-1) os << std::endl; 
	}
	os << " ]";
	os << std::endl;
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& in) {
	os << "[ ";
	for(int i=0;i<in.size();i++) 
		os << in[i] << " ";
	os << "]" << std::endl; 
    return os;
}

#endif