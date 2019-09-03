#ifndef NUMCPP_H
#define NUMCPP_H

#include <vector>

using namespace std;

namespace nc {

	typedef vector<int> array;
	typedef vector<vector<int> > matrix;
	typedef pair<int, int> shape;
	typedef pair<array, int> odarray;

	// creates a new matrix from a shape
	matrix ncmat(shape s) {
		matrix out;
		for(int i=0;i<s.first;i++) {
			out.push_back(array(s.second,0));
		}
		return out;
	}

	// flattens the array
	array flatten (array in) { return in; }

	// flattens the matrix to array
	array flatten (matrix in) {
		array out;
		for(int i=0;i<in.size();i++)
			for(int j=0;j<in[i].size();j++)
				out.push_back(in[i][j]);

		return out;
	}

	array concat (odarray in1, array in2, int offset) {
		array out;
		int order = in1.second;
		switch (order) {
			case 1: // in-same-order
				for(int i=0;i<in1.first.size();i++) out.push_back(in1.first[i]);
				break;
			case -1:
				for(int i=in1.first.size()-1;i>=0;i--) out.push_back(in1.first[i]);
				break;
			default:
				break;
		}
		for(int i=offset;i<in2.size();i++) out.push_back(in2[i]);
		return out;
	}

	array concat (array a1, array a2) {
		array out(a1.size() + a2.size());
		for(int i=0;i<a1.size();i++) out.push_back(a1[i]);
		for(int i=0;i<a2.size();i++) out.push_back(a2[i]);
		return out;
	}
	
}

#endif