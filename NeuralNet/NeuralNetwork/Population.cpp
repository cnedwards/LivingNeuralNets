#include "Population.hpp"

Population::Population()
{
	generation=0;

	bestFitness=0; fout=std::ofstream("data.out");
	individualBestFitness=0;
}


Population::~Population()
{
	empty();
	fout.close();
}

void Population::addMonster(Monster *newnetwork)
{
	monsters.push_back(newnetwork);
}

void Population::update(b2World &world,sf::Time& elapsedTime, Map& map)
{
	int numberDead=0;
	for (int loop = 0; loop < monsters.size(); loop++)
	{
		bool dead=monsters[loop]->getDead();
		if (!dead)

		{
			monsters[loop]->update(world, elapsedTime, map);
		}
		numberDead+=dead;
	}

	if (numberDead>=monsters.size())
		newGeneration(world, map);
}


void Population::logData()
{
	//Record new best fitness
	int best=highestFitnessNetwork();
	long double f=monsters[best]->getFitness();
		std::cout<<best<<"\t"<<f<<std::endl;
	if (f>individualBestFitness) 
	{
		individualBestFitness=f;
		std::ofstream o("Networks/FitnessBest_"+std::to_string(f)+".dat");
		o<<"Best is #"<<best<<std::endl<<std::endl;
		print(o);
		o.close();
	};


        double popFitness=testFitness();

        if (generation%1==0 || popFitness>bestFitness)
		{std::cout<<generation<<"\t"<<popFitness<<std::endl; fout<<generation<<"\t"<<popFitness<<std::endl;}
        if (popFitness>bestFitness) bestFitness=popFitness;
}



void Population::resurrect(b2World &world, Map& map)
{
	for (int loop=0; loop<amount()/3; loop++)selection();

	int sideWidth=map.getSideWidth();
	for (int loop = 0; loop < monsters.size(); loop++)
	{
		monsters[loop]->resurrect(world, map);
	}
	generation++;
}

void Population::render(sf::RenderWindow &Window)
{
	for (int loop = 0; loop < monsters.size(); loop++)
	{
		if (!monsters[loop]->getDead())
		{
			monsters[loop]->render(Window);
		}
	}
}

Monster* Population::getMonster(int index)
{
	return monsters[index];
}

void Population::empty()
{
	for (int loop = 0; loop < monsters.size(); loop++)
	{
        delete monsters[loop];
	}
	monsters.clear();
}

///Mutates a random neuron from an organism
void Population::mutateMonster(Monster &loser)
{
    int randomLayer=rand() %3;

    if (randomLayer==0)
	{
		int randomGene= rand() % loser.inputNumber;
		loser.input[randomGene]=Neuron();
	}
    if (randomLayer==1)
	{
		int randomGene= rand() % loser.hiddenNumber;
		loser.hidden[randomGene]=Neuron();
	}
    if (randomLayer==2)
	{
		int randomGene= rand() % loser.outputNumber;
		loser.output[randomGene]=Neuron();
	}
}

void Population::mutateMonsterSlow(Monster &loser)
{
    int randomLayer=rand() %3;
	double random=rand() % 10000/10000.f *sign();

    if (randomLayer==0) loser.input[0]=Neuron();
	{
		int randomGene= rand() % loser.inputNumber;
		Neuron * lost= &loser.input[randomGene];

		int randomFloat= rand() % 3;
		if		(randomFloat==1)	*lost=Neuron(random, lost->getWeight(), lost->getThreshold());
		else if (randomFloat==2)	*lost=Neuron(lost->getBias(), random, lost->getThreshold());
		else						*lost=Neuron(lost->getBias(), lost->getWeight(), random);
	}
    if (randomLayer==1) loser.input[1]=Neuron();
	{
		int randomGene= rand() % loser.hiddenNumber;
		Neuron * lost= &loser.hidden[randomGene];

		int randomFloat= rand() % 3;
		if		(randomFloat==1)	*lost=Neuron(random, lost->getWeight(), lost->getThreshold());
		else if (randomFloat==2)	*lost=Neuron(lost->getBias(), random, lost->getThreshold());
		else						*lost=Neuron(lost->getBias(), lost->getWeight(), random);
	}
    if (randomLayer==2) loser.hidden[0]=Neuron();
	{
		int randomGene= rand() % loser.outputNumber;
		Neuron * lost= &loser.output[randomGene];

		int randomFloat= rand() % 3;
		if		(randomFloat==1)	*lost=Neuron(random, lost->getWeight(), lost->getThreshold());
		else if (randomFloat==2)	*lost=Neuron(lost->getBias(), random, lost->getThreshold());
		else						*lost=Neuron(lost->getBias(), lost->getWeight(), random);
	}
}


///copies a gene into organism 1
///Winner first
void Population::copyGene(Monster &winner, Monster &loser)
{
    int randomLayer=rand() %3;

    if (randomLayer==0) loser.input[0]=Neuron();
	{
		int randomGene= rand() % loser.inputNumber;
		loser.input[randomGene]=winner.input[randomGene];
	}
    if (randomLayer==1) loser.input[1]=Neuron();
	{
		int randomGene= rand() % loser.hiddenNumber;
		loser.hidden[randomGene]=winner.hidden[randomGene];
	}
    if (randomLayer==2) loser.hidden[0]=Neuron();
	{
		int randomGene= rand() % loser.outputNumber;
		loser.output[randomGene]=winner.output[randomGene];
	}
}

void Population::resetNetworks()
{
    for (int loop=0; loop<amount(); loop++)
        monsters[loop]->reset();
}

///This is basically a function incapsulating resurrect that allows intermediate stuff. 
///Destroying all monster bodies caused ocasional memory throws and it looks like an alternative
///is used now.
void Population::newGeneration(b2World &world, Map &map)
{
	logData();

    //for (int loop=0; loop<amount(); loop++)
	//	monsters[loop]->destroyBody(world);
	resurrect(world, map);

}

int Population::amount()
{
	return monsters.size();
}

int Population::amountAlive()
{
	int number=0;
	for (int loop=0; loop<monsters.size(); loop++) {if (!(monsters.at(loop)->getDead())) number++;}
	return number;
}


///Winner first
void Population::mutateMonsters(Monster &winner, Monster &loser)
{
        mutateMonster(loser);
        copyGene(winner, loser);
}

///Works in fitness values to suit multiple different scenarios
double Population::testFitness()
{
    double fitness=0;

    //test organisms
    for (int loop=0; loop<amount(); loop++)
    {
		fitness+=monsters[loop]->getFitness();
    }

	resetNetworks();
    return fitness/amount();
}

Monster* Population::bestMonster()
{
    int bestOrganismID=0;
    unsigned long long highestFitness=0;
    //what winner organism should swap genes
    for (int loop=0; loop<amount(); loop++)
    {
		unsigned long long fitness =monsters[loop]->getFitness();
        if (fitness > highestFitness) {bestOrganismID=loop; highestFitness=fitness;}
    }

	resetNetworks();
	return monsters[bestOrganismID];
}



double Population::highestFitness()
{
    double largest=-1;
    for (int loop=0; loop<amount(); loop++)
    {
		if (monsters[loop]->getFitness()>largest) largest=monsters[loop]->getFitness();
    }

	resetNetworks();
    return largest;
}

double Population::lowestFitness()
{
    double lowest=500;
    for (int loop=0; loop<amount(); loop++)
    {
        if (monsters[loop]->getFitness()<lowest) lowest=monsters[loop]->getFitness();
    }

	resetNetworks();
    return lowest;
}

int Population::highestFitnessNetwork()
{
	int best=0;
    double largest=-1;
    for (int loop=0; loop<amount(); loop++)
    {
		if (monsters[loop]->getFitness()>largest) {largest=monsters[loop]->getFitness(); best=loop;}
    }

	resetNetworks();
    return best;
}

int Population::lowestFitnessNetwork()
{
	int best=0;
    double lowest=500;
    for (int loop=0; loop<amount(); loop++)
    {
        if (monsters[loop]->getFitness()<lowest) {lowest=monsters[loop]->getFitness(); best=loop;}
    }

	resetNetworks();
    return best;
}

double Population::averageFitness()
{
    unsigned long long total=0;
    for (int loop=0; loop<amount(); loop++)
    {
		total+=monsters[loop]->getFitness();
    }
    return total/(float)amount();

	resetNetworks();
}

void Population::selection()
{
    int ID1=rand() % amount(), ID2=rand() % amount();
    while (ID1==ID2) ID2=rand() % amount();

	unsigned long long correct1=monsters[ID1]->getFitness();
	unsigned long long correct2=monsters[ID2]->getFitness();

    correct1>correct2? mutateMonsters(*monsters[ID1], *monsters[ID2]) : mutateMonsters(*monsters[ID2], *monsters[ID1]);

	resetNetworks();
}

int Population::getGenerationNumber()
{
	return generation;
}


void Population::print(std::ostream &out)
{
	out << generation << std::endl;

	for (int loop = 0; loop < monsters.size(); loop++)
	{
		out << loop << std::endl;
		monsters[loop]->print(out);
	}
}

void Population::read(std::istream &in)
{
	in >> generation;
	int dummy;
	

	while (!in.eof())
	{
		for (int loop = 0; loop < monsters.size(); loop++)
		{
			in >> dummy;
			monsters[loop]->read(in);
		}
	}
}