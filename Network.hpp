#ifndef NETWORK_H
#define NETWORK_H
#include "Neuron.hpp"
#include <iostream>
#include <vector>
using namespace std;


class Neuron;

class Network
{
	private:
		std::vector<Neuron> neurons_;
		std::vector<vector<int>> connections_;
		int nb_neurons;
		int nb_excitatory;
		int nb_inhibitory;
		double c_excitatory;
		double c_inhibitory;
		unsigned long network_time_;
		const double step_time_;
	public:
	Network(int nb_n=12500);
	~Network();
	void setNeurons();
	void setConnections();
	void set_network_time(unsigned long& t);
	void store_data();
	void update_network(double Iext, unsigned long t_start, unsigned long t_stop);
	
	
	};
	
#endif
	
