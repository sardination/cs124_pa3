#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>
#define DELTATIME(end, begin) (std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000.0)

using namespace std;

int max_iter = 25000;

int64_t karkarp(vector<int64_t>& a);
int64_t reprand(vector<int64_t>& a, bool stan);
int64_t climbing(vector<int64_t>& a, bool stan);
int64_t annealing(vector<int64_t>& a, bool stan);
vector<bool> makerand_standard(int n);
vector<bool> neighbor_standard(vector<bool>& s);
int64_t residue_standard(vector<int64_t>& a, vector<bool>& s);
vector<int> makerand_prepart(int n);
vector<int> neighbor_prepart(vector<int>& p);
int64_t residue_prepart(vector<int64_t>& a, vector<int>& p);

int main(int argc, char *argv[]) {

  // read in input from user
  if (argc != 2) {
    cout << "Failure: incorrect number of arguments\n";
    return 1;
  }

  // open and read inputfile

  // find and return result of running kk

  // generate 100 random instances

    // for each, find the result using 7 different methods

  cout << "hello!" << endl;

  return 0;
}

int64_t karkarp(vector<int64_t>& a){

  // place all into a heap

  // while the size is greater than 1,

    // find the difference between the two greatest elements

    // place this difference at the

}

// temporarily written assuming the standard representation
int64_t reprand(vector<int64_t>& a, bool stan){
  int n = a.size;

  s = makerand_standard();
  for (int i = 0; i < max_iter; i++){
    s_new = makerand_standard();
    if (residue_standard(s_new) < residue_standard(s)){
      s = s_new;
    }
  }

  return s;
}

int64_t climbing(vector<int64_t>& a, bool stan){

}

int64_t annealing(vector<int64_t>& a, bool stan){

}

vector<bool> makerand_standard(int n){

}

vector<bool> neighbor_standard(vector<bool>& s){

}

int64_t residue_standard(vector<int64_t>& a, vector<bool>& s){

}

vector<int> makerand_prepart(int n){

}

vector<int> neighbor_prepart(vector<int>& p){

}

int64_t residue_prepart(vector<int64_t>& a, vector<int>& p){

}

