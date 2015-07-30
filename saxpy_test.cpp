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
  

return 0;
}
