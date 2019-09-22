#ifndef NUMCPP_H
#define NUMCPP_H

#include <vector>
#include <iostream>
#include <stdarg.h>

using namespace std;

namespace nc {

	typedef vector<double> array;
	typedef vector<vector<double> > matrix;
	typedef vector<bool> anomaly;
	typedef pair<int, int> shape;
	typedef pair<array, int> od_array;
	typedef pair<int, int> tuple_i;
	typedef pair<double, double> tuple_d;
	typedef pair<array, array> tuple_a;


	struct tuple_tri {
		array first;
		array second;
		array third;
	};

	struct tuple_quad {
		array first;
		array second;
		array third;
		array fourth;
	};

	void RELEASE_MEM (array& in) {
		vector<double>().swap(in);
	}

	void RELEASE_MEM (vector<vector<double> >& in) {
		for(int i=0;i<in.size();i++) {
			RELEASE_MEM(in[i]);
		}
		vector<vector<double> >().swap(in);
	}

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

	matrix ncmat (double *in, shape shp) {
		array in1; int size = shp.first*shp.second;
		for(int i=0;i<size;i++) in1.push_back(in[i]);
		return ncmat(in1, shp);
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

	matrix reshape (array in, shape shp) {
		return ncmat(in, shp);
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

	matrix concat (matrix m1, matrix m2, matrix m3) {
		matrix out = ncmat(shape(m1.size()+m2.size()+m3.size(), m1[0].size()));
		int i,j,k=0;
		for(i=0;i<m1.size();i++,k++) for(j=0;j<m1[i].size();j++) out[k][j] = m1[i][j];
		for(i=0;i<m2.size();i++,k++) for(j=0;j<m2[i].size();j++) out[k][j] = m2[i][j];
		for(i=0;i<m3.size();i++,k++) for(j=0;j<m3[i].size();j++) out[k][j] = m3[i][j];
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

	array rev_slice (array in, int start, int offset) {
		array out;
		for(int i=start; i<in.size()-offset;i++) out.push_back(in[i]);
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

	void flush (string name, anomaly in) {
		std::cout << std::endl << "[>!<] ANOMALIES : " << name << std::endl;
		std::cout << "[ ";
		for(int i=0;i<in.size();i++)
			if(in[i])
				std::cout << "YES ";
			else
				std::cout << "NO ";
		std::cout << "] " << std::endl; 		
	}

	void flush (string name, matrix in) {
		std::cout << std::endl << "[>!<] MATRIX :" << name << std::endl;
		for(int i=0;i<in.size();i++) {
			for(int j=0;j<in[i].size();j++)
				std::cout << in[i][j] << " ";
			std::cout << std::endl; 
		}
	}

	void flush (string name, array in) {
		std::cout << std::endl << "[>!<] ARRAY : " << name << std::endl;
		std::cout << "[ ";
		for(int i=0;i<in.size();i++) 
			std::cout << in[i] << " ";
		std::cout << "] " << std::endl; 
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

	array sub (double val, array in) {
		return add(-1*val, in);
	}

	array add (array in1, array in2) {
		array out;
		if(in1.size() != in2.size()) return out;
		for(int i=0;i<in1.size();i++) 
			out.push_back(in1[i]+in2[i]);
		return out;
	}

	array sub (array in, double val) {
		return add(in, -1*val);
	}

	array sub (array in1, array in2) {
		array out;
		if(in1.size() != in2.size()) return out;
		for(int i=0;i<in1.size();i++) 
			out.push_back(in1[i]-in2[i]);
		return out;
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

	matrix mul (matrix in, double val) {
		matrix out = in;
		for(int i=0;i<in.size();i++)
			out[i] = mul(out[i], val);
		return out;
	}

	matrix mul (double val, matrix in) {
		return mul(in, val);
	}

	double sum (array in) {
		double sum = 0;
		for(int i=0;i<in.size();i++) sum += in[i];
		return sum;
	}

	double mean (array in) {
		return sum(in)/in.size();
	}

	array square (array in) {
		array out;
		for(int i=0;i<in.size();i++)
			out.push_back(in[i]*in[i]);
		return out;
	}

	matrix eye (shape shp) {
		matrix out = ncmat(shp);
		for(int i=0;i<shp.first;i++) out[i][i] = 1.0;
		return out;
	}

	matrix eye (int n) {
		return eye(shape(n,n));
	}

	// creates array of zeros
	array zeros (int size) { return array(size, 0.0); }

	matrix zeros (shape shp) { return ncmat(shp); }

	array ones (int size) { return array(size, 1.0); }

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