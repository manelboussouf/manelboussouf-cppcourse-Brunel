#include "Network.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
using namespace std;

/**
 * @brief constructor
 * @param int nb_n
 * @return none
 * @details The network time is initialized at 0
 * The number of neuron is initialized at 125000
 * The constructor create all the neurons,
 * and set the connections of the network
 */
 
Network::Network(int nb_n)
	: nb_neurons(nb_n),
	network_time_(0.0),
	step_time_(0.1)
{
	nb_inhibitory = nb_neurons/5;
	nb_excitatory = nb_neurons - nb_inhibitory;
	c_excitatory= 0,1*nb_excitatory;
	c_inhibitory= 0,1*nb_inhibitory;
	
	setNeurons();
	setConnections();
	
}

/**
 * @brief Destructor
 * @param none
 * @return none
 */

Network::~Network(){}
	
/**
 * @brief set the network_time to a certain value.
 * @param unsigned long& t
 * @return void
 */
 
void Network::set_network_time(unsigned long& t)
{
	network_time_ = t;
}

/**
 * @brief set all the connections
 * @param none
 * @return void
 * @details Creation of the 2D matrix
 * Each neuron create c_excitatory connections
 * and c_inhibitory connections
 * Note that the neuron to connect is selected randomly
 */
 
void Network::setConnections()
{
	for( size_t i(0); i<neurons_.size(); ++i)
	{
		vector<int> c;
		connections_.push_back(c);
	}
	
	static random_device rd;
	static mt19937 gen(rd());

	
	for(size_t i(0); i<neurons_.size();++i)
	{
		for( int j(0); j<c_excitatory; ++j)
		{	
			static uniform_int_distribution<> connexion_with(0,nb_excitatory-1);
			connections_[connexion_with(gen)].push_back(i);
		}
		
		for(int k(0); k<c_inhibitory; ++k)
		{	
			static uniform_int_distribution<> connexion_with(nb_excitatory,nb_neurons);
			connections_[connexion_with(gen)].push_back(i);
		}
	}
}
	
/**
 * @brief create the neurons
 * @param none
 * @return void
 * @details create 10.000 excitatory neurons
 * and 2500 inhibitory neurons
 */
 
void Network::setNeurons()
{
	for (int i(0); i>nb_excitatory; ++i)
	{
		neurons_.push_back(Neuron(true));
	}
	
	for (int i(0); i<nb_inhibitory; ++i)
	{
		neurons_.push_back(Neuron(false));
	}
}

/**
 * @brief draw the matrix
 * @param none
 * @details Write in a file wich neuron is connected
 * to a selected one.
 */
 
void Network::store_data()
{
	ofstream n_spikes;
	n_spikes.open("spikes.odt");
	
	
	for( size_t i(0); i<neurons_.size(); ++i)
		{
			{ neurons_[i].get_time_spikes();
				n_spikes <<network_time_ <<'\t'<<i+1<<'\n';
			}
		}
	n_spikes.close();
}

/**
 * @brief update the network
 * @param double Iext
 * unsigned long t_start
 * unsigned long t_stop
 * @return void
 * @details First, update each neuron
 * then if the neuron is Excitatory send J
 * if the neuron is Inhibitory send Ji
 * store the data in a file
 */
 
void Network::update_network(double Iext, unsigned long t_start, unsigned long t_stop)
{
	set_network_time(t_start);
		
	while ((network_time_*step_time_)<t_stop)
	{
		for( size_t i(0); i<neurons_.size(); ++i)
			{
				neurons_[i].update_neuron(network_time_,Iext);
				
				for( size_t j(0); j<connections_[i].size(); ++j)
					{
						int interaction=connections_[i][j];
					
						if(neurons_[i].isExcitatory_())
						{
							double J(0.1);
							neurons_[interaction].recieve(J, network_time_);	
						}else{
							double Ji_(-0.5);
							neurons_[interaction].recieve(Ji_, network_time_);	
					}
				}	
			}	
		
		++network_time_;
		
		}
		
		store_data();

}
