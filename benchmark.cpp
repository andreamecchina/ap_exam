#include"bst.hpp"
#include<iostream>
#include<chrono>
#include<map>
#include<unordered_map>
#include<random>
#include<algorithm>
#include<vector>
#include<set>


// auto t0 = std::chrono::high_resolution_clock::now();
// auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);

#define x_step 10000
#define max_x  100000
#define sample 10

template<typename S>
auto select_random(const S &s, size_t n) {
  auto it = std::begin(s);
  // 'advance' the iterator n times
  std::advance(it,n);
  return it;
}

void compare_map(){

  std::vector<int> v;
  for(unsigned int i{0}; i<max_x; i++)
    v.push_back(i);
  std::random_shuffle(std::begin(v), std::end(v));
  
  bst<int,int> tree{};
  bst<int,int> unbal_tree{};
  std::map<int,int> mp{};
  std::unordered_map<int,int> unord_mp{};
  std::vector<int> keys;

  auto t0 = std::chrono::high_resolution_clock::now();
  auto t1 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
  
  for(int i{0}; i<max_x; i += x_step){

    // add x_step elements to containers
    for(int j{0}; j<x_step; ++j){
      auto ins = v[ j+i ];
      //std::cout << "I'm inserting key " << ins << std::endl;
      tree.insert({ins, ins});
      unbal_tree.insert({ins, ins});
      mp[ins];
      unord_mp[ins];
      keys.push_back(ins);
    }
    
    // balance the tree
    tree.balance();
    
    // measure finding `sample` random elements 
    std::random_shuffle(std::begin(keys), std::end(keys));

    // measure tree
    t0 = std::chrono::high_resolution_clock::now();

    for(auto waldo{0}; waldo<sample ; ++waldo){
      tree.find( keys[waldo] );
    }

    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << "Balanced tree takes \t\t" << elapsed.count()/10 << "\tns\n";

    // measure unbal_tree
    t0 = std::chrono::high_resolution_clock::now();

    for(auto waldo{0}; waldo<sample ; ++waldo){
      unbal_tree.find( keys[waldo] );
    }
    
    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << "Non-balanced tree takes \t" << elapsed.count() << "\tns\n";

    // measure mp
    t0 = std::chrono::high_resolution_clock::now();

    for(auto waldo{0}; waldo<sample ; ++waldo){
      mp.find( keys[waldo] );
    }
    
    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << "Ordered map takes \t\t" << elapsed.count() << "\tns\n";

    // measure unord_mp
    t0 = std::chrono::high_resolution_clock::now();
    
    for(auto waldo{0}; waldo<sample ; ++waldo){
      unord_mp.find( keys[waldo] );
    }
    
    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << "Unordered map takes \t\t" << elapsed.count() << "\tns\n\n";
  }
}



int main(){

  try {

    compare_map();

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
