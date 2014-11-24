//
//  hw2.cpp
//  CSPP51045
//
//  Created by Michael Dorman on 4/6/12.
//  Copyright (c) 2012 University of Chicago. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

std::vector<int> carmichael_numbers = {561, 1105, 1729, 2465, 2321, 6601, 8911};

const int K_RUN_TIMES = 4;

/**
 *   Returns random number between 1 and (n-1)
 *   @param n integer n
 */
int IsPrime::randomNumGenerator(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, (n-1));
    return dis(gen);
}
/**
 * Primality test. This primality test uses Fermat's little theorem.
 * Pseudocode used in implementation from
 * "http://en.wikipedia.org/wiki/Fermat_primality_test"
 * @param n number to test
 */
bool IsPrime::operator(const int n){
    
    if(pseudoPrimeTest(n))
        return false;
    
    int a = randomNumGenerator(n);
    for(int i = 0; i<K_RUN_TIMES; i++){
        if(Math.pow(a,(n-1)) == a%p)
            return false;
    }
	return true;
}

/**
 *	Checks integer to see if it is one of the Carmichael numbers.
 *  @param n number to be tested.
 *  return true if number is a Carmichael number.
 */
bool IsPrime::pseudoPrimeTest(const int n){
	it = find(carmichael_numbers.begin(), carmichael_numbers.end(), n);
	++it;
	if(*it < (carmichael.end()+1)){
		return true;
    }
    
