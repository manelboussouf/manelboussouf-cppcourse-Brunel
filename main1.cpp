#include "Neuron.hpp"
#include "Network.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

int main ()
{
	Network network;
	
	network.update_network(0.0,0, 100);
	
	return 0;
}

