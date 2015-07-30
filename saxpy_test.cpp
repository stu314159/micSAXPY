#include <omp.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]){
  cout << "commencing test of mic..." << endl;

  // verify 2 command line arguments besides the program
  if(argc < 3) {
    cerr << "Usage: aprun -cc none -k ./saxpy_test [vec length] [num iterations]" << endl;
    exit(1);
  }
  // get command line arguments
  int N = atoi(argv[1]);
  int NumIter = atoi(argv[2]);
    
  // allocate memory for array
  float * X = new float[N];
  float * Y = new float[N];
  float * Z = new float[N];
  float * Zgold = new float[N];

  const float cX = 1.;
  const float cY = 1.;
  const float alpha = 2.;

  // initialize arrays and pre-compute expected values
  for(int i=0;i<N;i++){
    X[i] = cX; Y[i] = cY;
    Zgold[i] = alpha*X[i]+Y[i];
  }

  int num_threads = omp_get_num_threads();
  
  // compute Z on the mic
  int i,offset,loopIter,k,th_id;
#pragma offload target(mic:0) in(X[0:N],Y[0:N]) out(Z[0:N]) //<-- for offload mode only
#pragma omp parallel for private(i,offset,loopIter,k)
  for(i=0;i<num_threads;i++){
    th_id = omp_get_thread_num(); // get thread num
    loopIter = N/num_threads; // basic number of vector entries to compute
    if(th_id<N%num_threads) { // adjust for N not evenly divided by numthreads
      loopIter++;
    }
    offset = loopIter*th_id;
    if(th_id>=N%num_threads){    
      offset+=N%num_threads;
    }
    for(k=0;k<loopIter;k++){
      Z[offset+k]=alpha*X[offset+k]+Y[offset+k];
    }
  }

  
  

  // compare with Zgold
  int nErr = 0;
  for(int i=0;i<N;i++){
    if(Zgold[i]!=Z[i]){
       nErr++;
    }
  }
  cout << "The number of errors = " << nErr << endl;

  cout << "A few values of Z..." << endl;
  for(int i=0;i<10;i++){
   cout << "Z[" << i << "] = " << Z[i] << endl;
  }


  // deallocate dynamic memory
  delete [] X;
  delete [] Y;
  delete [] Z;
  delete [] Zgold;

  return 0;
}
