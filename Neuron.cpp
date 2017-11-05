#include "Neuron.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <random>
using namespace std;

/**
 * @brief constructor
 * @param bool excitatory
 * @return none
 * @details This constructor allows us to
 * define our neuron to an excitatory or
 * inhibitory one.
 * The membrane potential is initialized to 0
 * as the number of spikes.
 * The neuron doesn't spike.
 * The buffer has a size of 16 and is initialized
 * with all the values at 0
 */
 
Neuron::Neuron (bool excitatory)
	: mb_potential(0.0), 
	  nb_spikes(0), 
	  spike_(false), 
	  excitatory_(excitatory),
	  isRefractory(false), 
	  buffer_(16,0.0) 
{ }
	
/**
 * @brief Destructor
 * @param none
 * @return none
 */
 
Neuron::~Neuron(){}


double Neuron:: get_J()
{
	return J_;
}
double Neuron::get_mb_potential()
{
	return mb_potential;
	}
	
int Neuron::get_nb_spikes(int n)
{ 
	n = time_spikes.size();
	nb_spikes =n; 
	return nb_spikes;
	}

	
bool Neuron::get_state_(){
	return spike_;
	}
	
bool Neuron::isExcitatory_(){
	return excitatory_;
}
	
vector <double> Neuron::get_time_spikes() const{
	return time_spikes;
	}
	

/**
 * @brief update neuron
 * @param unsigned long& time
 * double Iext
 * @return void
 * @details regarding of certain circumstances
 * the method will update the state of the neuron
 */
 
void Neuron::update_neuron(unsigned long& time, double Iext)
{
	int n;
	n=int(floor((time+Delay_)/step_time_));
	
	double r(t_rp_);
	
	if (mb_potential < v_threshold_)
	{mb_potential = v_reset_;
			time += step_time_;
		mb_potential = exp(-step_time_/tau_)*mb_potential + Iext*(tau_/c_)*(1-exp(-step_time_/tau_))+buffer_[n%16];
		buffer_[n% 16]=0.0;
		time = time + step_time_;
		
			
	} 
		else {
		time_spikes.push_back(time);
		spike_=true;
		cout << time_spikes.back() << endl;
		}
	
	if( r >=0){
			mb_potential = v_reset_;
			isRefractory = true;
			r -=step_time_;
			time += step_time_;
	} 
	
		spike_=false;
	 }
	 
/**
 * @brief send signal to a post synaptic neurod
 * @param double& J
 * double time
 * @return void
 * @details The method changes the values in the buffer
 * after a certain delay with the spike value
 */
 
void Neuron::recieve(double& J, double time){
	if ( buffer_.empty()){
		cout << "stop" << endl;
	}
	int n;
	n=int(floor((time+Delay_)/step_time_));
	buffer_[n%16]+= J;
}
	

		
	

