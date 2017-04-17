#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits.h>
#define DELTATIME(end, begin) (std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000.0)

using namespace std;

int max_iter = 25000;

int64_t karkarp(vector<int64_t>& aprime);
int64_t reprand(vector<int64_t>& a, bool stan);
int64_t climbing(vector<int64_t>& a, bool stan);
int64_t annealing(vector<int64_t>& a, bool stan);
vector<bool> makerand_standard(int n);
vector<bool> neighbor_standard(vector<bool>& s);
int64_t residue_standard(vector<int64_t>& a, vector<bool>& s);
vector<int> makerand_prepart(int n);
vector<int> neighbor_prepart(vector<int>& p);
vector<int64_t> partition(vector<int64_t>& a, vector<int>& p);
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

int64_t karkarp(vector<int64_t>& aprime){

  // place all into a heap

  // while the size is greater than 1,

    // find the difference between the two greatest elements

    // place this difference at the

}

int64_t reprand(vector<int64_t>& a, bool stan){
  int n = a.size();
  int64_t resid = LONG_MAX;

  if (stan) {
    vector<bool> s = makerand_standard(n);
    int64_t resid = residue_standard(a, s);
    for (int i = 0; i < max_iter; i++){
      vector<bool> s_new = makerand_standard(n);
      int64_t resid_new = residue_standard(a, s_new);
      if (resid_new < resid){
        resid = resid_new;
      }
    }
  }
  else {
    vector<int> p = makerand_prepart(n);
    int64_t resid = residue_prepart(a, p);
    for (int i = 0; i < max_iter; i++){
      vector<int> p_new = makerand_prepart(n);
      int64_t resid_new = residue_prepart(a, p_new);
      if (resid_new < resid){
        resid = resid_new;
      }
    }
  }

  return resid;
}

int64_t climbing(vector<int64_t>& a, bool stan){

}

int64_t annealing(vector<int64_t>& a, bool stan){

}

vector<bool> makerand_standard(int n){
  vector<bool> s(n);

  for (int i = 0; i < n; i++){
    if (rand() % 2 == 1){
      s[i] = true;
    }
  }

  return s;

}

vector<bool> neighbor_standard(vector<bool>& s){
  int n = s.size();
  vector<bool> s_new = s;

  // choose two random elements
  int i = rand() % n;
  int j = i;
  while (j == i){
    j = rand() % n;
  }

  s_new[i] = !s_new[i];
  if (rand() % 2 == 1){
    s_new[j] = !s_new[j];
  }

  return s_new;

}

int64_t residue_standard(vector<int64_t>& a, vector<bool>& s){
  int n = a.size();
  int64_t res = 0;

  for (int i = 0; i < n; i++){
    if (s[i]){
      res += a[i];
    }
    else{
      res -= a[i];
    }
  }

}

vector<int> makerand_prepart(int n){

}

vector<int> neighbor_prepart(vector<int>& p){

}

int64_t residue_prepart(vector<int64_t>& a, vector<int>& p){

}

