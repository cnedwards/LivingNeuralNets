# LearningNeuralNets
 Neural Networks looking for food.
# Living Neural Networks

<b>First: I wrote this as a sophomore in high school (early 2013). I had not taken linear algebra (or even precal) at that time. The neural networks are very inefficient.  </b>

This is a simulation where neural networks control small entities with four outputs to learn to find food. It uses a a custom genetic algorithm and multilayer perceptron.  The rendering is done using SFML and the physics use Box2D. The current version creates a single creature with pretrained weights. Although the neural networks aren't useful, I think the environment is interesting. 

## Dependencies
The project is written in Microsoft Visual Studio 2010. It has been tweaked to work with Visual Studio 2017.
The code depends on Box2D and SFML 2.1 (linked statically). Box2D is included in the repository, but SFML will need to be downloaded. 

## Future
In the future, I'd like to change the AI portion of the algorithms to use what I've learned about modern reinforcement learning. I'd like to implement something like deep Q-learning (which didn't exist when I initially wrote this project). Furthermore, I would also like to increase the number of types of entities and what they eat. When I first envisioned this project (8th grade), I had envisioned making a small world. 