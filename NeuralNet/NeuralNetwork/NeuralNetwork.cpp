#include "NeuralNetwork.hpp"
#include <fstream>
NeuralNetwork::NeuralNetwork(int inputNumber, int hiddenNumber, int outputNumber)
{
	for (int loop=0; loop<inputNumber; loop++)
		input.push_back(Neuron());
	for (int loop=0; loop<hiddenNumber; loop++)
		hidden.push_back(Neuron());
	for (int loop=0; loop<outputNumber; loop++)
		output.push_back(Neuron());

	this->inputNumber=inputNumber;
	this->hiddenNumber=hiddenNumber;
	this->outputNumber=outputNumber;
}

void NeuralNetwork::reset()
{
	for (int loop=0; loop<input.size(); loop++)
		input[loop].reset();
	for (int loop=0; loop<hidden.size(); loop++)
		hidden[loop].reset();
	for (int loop=0; loop<output.size(); loop++)
		output[loop].reset();
}

std::vector<bool> NeuralNetwork::testCombination(std::vector<double> inputValues)
{
	std::vector<bool> returnValues;
    //Inputs
	for (int loop=0; loop<input.size(); loop++)
	{
		input[loop].setInput(inputValues[loop]);
		input[loop].addToInput(input[loop].getBias());
		input[loop].calculateFired();
	}

    //Hidden
	for (int loop=0; loop<hidden.size(); loop++)//Hidden loop
	{
		for (int loop2=0; loop2<input.size(); loop2++)//Input loop
		{
			//each input is added to each hidden
			if (input[loop2].getFired()) hidden[loop].addToInput(input[loop2].calculateFiringAmount());
		}
		//only one bias per hidden
		hidden[loop].addToInput(hidden[loop].getBias());
		hidden[loop].calculateFired();
	}

    //Output
	for (int loop=0; loop<output.size(); loop++)//Output loop
	{
		for (int loop2=0; loop2<hidden.size(); loop2++)//Hidden loop
		{
			if (hidden[loop2].getFired()) output[loop].addToInput(hidden[loop2].calculateFiringAmount());
		}
		
		//std::cout<<output[loop].getInput()<<" ";
		output[loop].addToInput(output[loop].getBias());
		//std::cout<<output[loop].getInput()<<std::endl;
		output[loop].calculateFired();

		returnValues.push_back(output[loop].getFired());
	}
	
	reset();
    return returnValues;
}



void NeuralNetwork::print(std::ostream &out)
{
	out << "Input\n";
	for (int loop=0; loop<input.size(); loop++)
		input[loop].print(out);
	
	out<<"Hidden\n";
	for (int loop=0; loop<hidden.size(); loop++)
		hidden[loop].print(out);

	out<<"Output\n";
	for (int loop=0; loop<output.size(); loop++)
		output[loop].print(out);
}

void NeuralNetwork::read(std::istream &in)
{
	std::string dummy; 

	in >> dummy;
	for (int loop=0; loop<input.size(); loop++)
		input[loop].read(in);
	
	in >> dummy;
	for (int loop=0; loop<hidden.size(); loop++)
		hidden[loop].read(in);

	in >> dummy;
	for (int loop=0; loop<output.size(); loop++)
		output[loop].read(in);
}