#include "Neuron.hpp"
#include "Math.hpp"

Neuron::Neuron()
{
	bias=rand() % 10000/10000.f *sign(); input=0.f; weight=rand() % 10000/10000.f *sign(); threshold=rand() % 10000/10000.f; fired=0;
}

Neuron::Neuron(double bias, double weight, double threshold)
{
	this->bias=bias; input=0.f; this->weight=weight; this->threshold=threshold; fired=0;
}

void Neuron::reset()
{
    input=0.f; fired=0;
}

double Neuron::getWeight()
{
	return weight;
}


double Neuron::getBias()
{
	return bias;
}

double Neuron::getThreshold()
{
	return threshold;
}

bool Neuron::getFired()
{
	return fired;
}

double Neuron::getInput()
{
	return input;
}

void Neuron::setInput(double arg)
{
	input=arg;
}

void Neuron::addToInput(double arg)
{
	input+=arg;
}

void Neuron::setFired(bool arg)
{
	fired=arg;
}

double Neuron::calculateFiringAmount()
{
    if (input>threshold)
    {
        fired=true;
        return weight*(int)fired;
        //arg.weightedFire=sigmoidValue(arg.weightedFire);
    }
    else return 0.f;
}

void Neuron::calculateFired()
{
    if (input>threshold)
    {
        fired=true;
    }
	else fired=false;
}


void Neuron::print(std::ostream &out)
{
	out << bias << " " << threshold << " " << weight << std::endl;
}


void Neuron::read(std::istream &in)
{
	in >> bias >> threshold >> weight;
}