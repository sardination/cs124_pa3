#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <random>
#define DELTATIME(end, begin) (std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1000.0)

using namespace std;

const int max_iter = 25000;
const int64_t maxnum = pow(10, 12);

void printVector(vector<int>& v);
void printVector(vector<bool>& v);
void printVector(vector<int64_t>& v);
int64_t karkarp(vector<int64_t>& aprime);
int64_t reprand(vector<int64_t>& a, bool stan);
int64_t climbing(vector<int64_t>& a, bool stan);
int64_t annealing(vector<int64_t>& a, bool stan);
double T(int iter);
vector<bool> makerand_standard(int n);
vector<bool> neighbor_standard(vector<bool>& s);
int64_t residue_standard(vector<int64_t>& a, vector<bool>& s);
vector<int> makerand_prepart(int n);
vector<int> neighbor_prepart(vector<int>& p);
vector<int64_t> partition(vector<int64_t>& a, vector<int>& p);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  // read in input from user
  if (argc != 2) {
    cout << "Failure: incorrect number of arguments\n";
    return 1;
  }

  // open and read inputfile
  vector<int64_t> a;
  string fileName = argv[1];
  string line;
  ifstream infile(fileName);
  if (infile.is_open()) {
    while (getline (infile, line)) {
      a.push_back(atoi(line.c_str()));
    }
  }
  int n = a.size();

  // find and return result of running kk, for original and 100 random instances
  cout << "input karkarp: " << karkarp(a) << endl;
  int instances = 100;
  random_device rd;
  default_random_engine generator(rd());
  uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);
  for (int i = 0; i < instances; i++){
    cout << "Instance " << i << endl;
    vector<int64_t> randprob;
    for (int j = 0; j < n; j++){
      randprob.push_back(distribution(generator) % maxnum + 1);
    }

    // print the result after karkarp
    cout << "karkarp: " << karkarp(randprob) << endl;

    // result after repeated random
    cout << "reprand standard: " << reprand(randprob, true) << endl;
    cout << "reprand prepart: " << reprand(randprob, false) << endl;

    // hill climbing
    cout << "hill climbing standard: " << climbing(randprob, true) << endl;
    cout << "hill climbing prepart: " << climbing(randprob, false) << endl;

    // simulated annealing
    cout << "annealing standard: " << annealing(randprob, true) << endl;
    cout << "annealing prepart: " << annealing(randprob, false) << endl;

  }

  return 0;
}

void printVector(vector<int>& v) {
  for(int i=0; i<v.size(); ++i)
    cout << v[i] << ' ';
  cout << endl;
}

void printVector(vector<bool>& v) {
  for(int i=0; i<v.size(); ++i)
    cout << v[i] << ' ';
  cout << endl;
}

void printVector(vector<int64_t>& v) {
  for(int i=0; i<v.size(); ++i)
    cout << v[i] << ' ';
  cout << endl;
}

int64_t karkarp(vector<int64_t>& aprime){
  int n = aprime.size();

  // place all into a heap
  priority_queue<int64_t> q;

  for (int i = 0; i < n; i++){
    q.push(aprime[i]);
  }

  // while the size is greater than 1,
  for (int j = 0; j < n - 1; j++){
    // find the difference between the two greatest elements and reinsert it
    int64_t first = q.top();
    q.pop();
    int64_t second = q.top();
    q.pop();
    int64_t diff = abs(first - second);
    q.push(diff);
  }

  return (q.top());
}

int64_t reprand(vector<int64_t>& a, bool stan){
  int n = a.size();
  int64_t resid;

  if (stan) {
    vector<bool> s_new;
    resid = INFINITY;
    for (int i = 0; i < max_iter; i++){
      s_new = makerand_standard(n);
      int64_t resid_new = residue_standard(a, s_new);
      if (resid_new < resid){
        resid = resid_new;
      }
    }
  }
  else {
    vector<int> p_new;
    vector<int64_t> aprime;
    resid = INFINITY;
    for (int i = 0; i < max_iter; i++){
      p_new = makerand_prepart(n);
      aprime = partition(a, p_new);
      int64_t resid_new = karkarp(aprime);
      if (resid_new < resid){
        resid = resid_new;
      }
    }
  }

  return resid;
}

int64_t climbing(vector<int64_t>& a, bool stan){
  int n = a.size();
  int64_t resid;
  int64_t resid_neighbor;

  if (stan) {
    vector<bool> s = makerand_standard(n);
    resid = residue_standard(a,s);
    vector<bool> neighbor;
    for (int i=0; i < max_iter; i++) {
      neighbor = neighbor_standard(s);
      resid_neighbor = residue_standard(a, neighbor);
      if (resid_neighbor < resid) {
        s = neighbor;
        resid = resid_neighbor;
      }
    }
  } else {
    vector<int> p = makerand_prepart(n);
    vector<int64_t> aprime = partition(a,p);
    resid = karkarp(aprime);
    vector<int> neighbor;
    for (int i = 0; i < max_iter; i++) {
      neighbor = neighbor_prepart(p);
      aprime = partition(a, neighbor);
      resid_neighbor = karkarp(aprime);
      if (resid_neighbor < resid) {
        p = neighbor;
        resid = resid_neighbor;
      }
    }
  }

  return resid;
}


int64_t annealing(vector<int64_t>& a, bool stan){
  int n = a.size();
  int64_t current_residue; //S''
  int64_t testing_residue; //S
  int64_t neighbor_residue; //S'

  if (stan) {
    vector<bool> testing = makerand_standard(n); //S
    testing_residue = residue_standard(a,testing);
    vector<bool> current (testing); //S''
    current_residue = testing_residue;

    vector<bool> neighbor;
    for (int i = 0; i < max_iter; i++) {
      neighbor = neighbor_standard(testing); //S'
      neighbor_residue = residue_standard(a,neighbor); //S'
      if (neighbor_residue < testing_residue) {
        testing = neighbor;
        testing_residue = neighbor_residue;
      } else {
        double prob = exp(-(neighbor_residue - testing_residue)/T(i+1));
        double random_assign = (double)rand() / RAND_MAX;
        if (random_assign < prob) {
          testing = neighbor;
          testing_residue = neighbor_residue;
        }
      }

      if (testing_residue < current_residue) {
        current = testing;
        current_residue = testing_residue;
      }
    }
  } else {
    vector<int> testing = makerand_prepart(n); //P
    vector<int64_t> aprime = partition(a,testing);
    testing_residue = karkarp(aprime);
    vector<int> current (testing); //P''
    current_residue = testing_residue;

    vector<int> neighbor;
    for (int i = 0; i < max_iter; i++) {
      neighbor = neighbor_prepart(testing); //P'
      aprime = partition(a, neighbor);
      neighbor_residue = karkarp(aprime); //P'
      if (neighbor_residue < testing_residue) {
        testing = neighbor;
        testing_residue = neighbor_residue;
      } else {
        double prob = exp(-(neighbor_residue - testing_residue)/T(i+1));
        double random_assign = (double)rand() / RAND_MAX;
        if (random_assign < prob) {
          testing = neighbor;
          testing_residue = neighbor_residue;
        }
      }

      if (testing_residue < current_residue) {
        current = testing;
        current_residue = testing_residue;
      }
    }
  }

  return current_residue;
}

double T(int iter) {
  return pow(10,10)*pow(0.8,floor(iter/300));
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
  return abs(res);
}

// returns prepartioning p
vector<int> makerand_prepart(int n){
  vector<int> p; //prepartition sequence with values 0 through n-1
  for (int i=0; i<n; i++) {
    p.push_back(rand() % n);
  }

  return p;
}

// takes prepartioning p, returns a neighbor solution
vector<int> neighbor_prepart(vector<int>& p){
  int n = p.size();
  int i = rand() % n;
  int j = rand() % n;
  while (p[i] == j) {
    i = rand() % n;
    j = rand() % n;
  }
  vector<int> p_neighbor (p);
  p_neighbor[i] = j;

  return p_neighbor;
}

vector<int64_t> partition(vector<int64_t>& a, vector<int>& p) {
  int n = a.size();
  vector<int64_t> partitioned_sequence (n,0);
  for (int j=0; j<n; j++) {
    partitioned_sequence[p[j]] += a[j];
  }

  return partitioned_sequence;
}

