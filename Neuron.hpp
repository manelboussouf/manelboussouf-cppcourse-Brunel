#ifndef NEURON_H
#define NEURON_H
#include <vector>


class Neuron
{
	private:
		//constants
		const double step_time_=0.1; 
		const int c_ = 1;
		const double v_threshold_= 20.0;
		const double t_rp_= 2.0; 
		const double v_reset_ = 0.0;
		const double tau_ = 20.0;
		const double Delay_ = 1.5;
		const double J_ = 0.1;
		
		double mb_potential;
		int nb_spikes;
		
		bool spike_;
		bool excitatory_;
		bool isRefractory;
		
		std::vector <double> buffer_;
		std::vector<double> time_spikes;
		std::vector<int> connection_list;
		
	public:
		Neuron(bool excitatory);
		~Neuron();
		
		double get_mb_potential();
		int get_nb_spikes(int n);
		double get_J();
		
		bool get_state_();
		bool isExcitatory_();
		
		std::vector <double> get_time_spikes() const;
		void update_neuron(unsigned long& time, double Iext);
		void recieve(double& J,double time);
		
		
};

#endif
