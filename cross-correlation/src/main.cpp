#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using namespace std;

vector<double> cross_correlation(vector<double> raw, vector<double> ref){
    std::vector<double> output(raw.size()+ref.size(), 0);
    
    for (int i = 0; i < raw.size(); i++){
        for (int j = 0; j < ref.size(); j++){
            output[i+j] += raw[i]*ref[j];
        }
    }
    return output;
}

//array<double>

int main() {
    int samples = 100;
    float sample_period = 0.1; // in seconds

    float sample_rate = (samples/sample_period); // in Hz

    double raw_freq = 100; // raw frequency in Hz
    int raw_amplitude = 2;
    int noise_amplitude = 1;

    std::vector<double> random_signal(samples);
    for (int i = 0; i<samples; i++){
        random_signal[i] = rand()%100 * noise_amplitude;
    }

    int sample_no[samples] = {};
    for (int i = 0; i<samples; i++){
        sample_no[i] = i+1;
    }

    cout << sample_rate <<endl;
    cout << raw_freq <<endl;
    std::vector<double> raw_signal(samples);
    for (int i = 0; i<samples; i++){
        raw_signal[i] = (raw_amplitude*sin(2*M_PI*raw_freq/sample_rate*samples)) + random_signal[i];
    }
    return 0;
}