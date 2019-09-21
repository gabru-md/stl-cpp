#ifndef L1_SOLVE_H
#define L1_SOLVE_H

#include "cvl1qc.h"
#include "../numcpp.h"

nc::matrix toNCMatrix (CvMat* X) {
	CvMat* temp = cvCloneMat(X);
	nc::shape shp(temp->rows, temp->cols);
	return nc::ncmat(temp->data.db, shp);
}

CvMat* toCvMat (nc::matrix mat) {
	CvMat* X = cvCreateMat(mat.size(), mat[0].size(), CV_64FC1);
	int SIZE = mat.size()*mat[0].size();
	double *dd = new double [SIZE];
	nc::array flat = nc::flatten(mat);
	for(int i=0;i<SIZE;i++) dd[i] = flat[i];
	X->data.db = dd;
	return X;
}

void icvAOps( CvMat* X, CvMat* Y, void* userdata )
{
	CvMat* A = (CvMat*)userdata;
	cvMatMul( A, X, Y );
}

void icvAtOps( CvMat* X, CvMat* Y, void* userdata )
{
	CvMat* A = (CvMat*)userdata;
	cvGEMM( A, X, 1, NULL, 0, Y, CV_GEMM_A_T );
}

nc::array l1_solve(nc::matrix P, nc::matrix q)
{

	const int N = P[0].size();
	const int K = P.size();
	const int T = 20;
	CvMat* A = toCvMat(P);
	CvMat* X = cvCreateMat( N, 1, CV_64FC1 );
	CvMat* Y = toCvMat(q);
	CvRNG rng_state = cvRNG(0xffffffff);
	cvRandArr( &rng_state, A, CV_RAND_NORMAL, cvScalar(0), cvScalar(1) );
	cvZero( X );
	for ( int i = 0; i < T; i++ )
	{
		int idx = cvRandInt( &rng_state ) % N;
		X->data.db[idx] = (int)(cvRandInt( &rng_state ) % 3) - 1;
	}
	double sigma = .005;
	CvMat* e = cvCreateMat( K, 1, CV_64FC1 );
	cvRandArr( &rng_state, e, CV_RAND_NORMAL, cvScalar(0), cvScalar(sigma) );
	cvMatMulAdd( A, X, e, Y );
	double epsilon = sigma * sqrt(K) * sqrt(1 + 2 * sqrt(2) / sqrt(K));
	CvMat* X0 = cvCreateMat( N, 1, CV_64FC1 );
	// printf("||X0 - X|| Before L1QC : %f\n", cvNorm(X0, X, CV_L1));
	double t = (double)cvGetTickCount();
	cvL1QCSolve( icvAOps, icvAtOps, A, Y, X0, epsilon );
	t = (double)cvGetTickCount() - t;
	// printf( "time = %gms\n", t/((double)cvGetTickFrequency() * 1000.) );
	// printf("||X0 - X|| After L1QC : %f\n", cvNorm(X0, X, CV_L1));
	//for ( int i = 0; i < N; i++ )
	//	printf("%f %f\n", X->data.db[i], X0->data.db[i]);

	nc::array toReturn = nc::flatten(toNCMatrix(X0));

	cvReleaseMat( &X0 );
	cvReleaseMat( &e );
	cvReleaseMat( &Y );
	cvReleaseMat( &X );
	cvReleaseMat( &A );

	return toReturn;
}

#endif