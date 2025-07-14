# Living Neural Networks

<b>Some code I wrote as a sophomore in high school (January 2014). The neural networks are very inefficient.  </b>

This is a simulation where neural networks control small entities with four outputs to learn to find food. It uses a a custom genetic algorithm and multilayer perceptron.  The rendering is done using SFML and the physics use Box2D. The current version creates a single creature with pretrained weights. Although the neural networks aren't useful, I think the environment is interesting. 


## Dependencies
The project is written in Microsoft Visual Studio 2010. It has been tweaked to work with Visual Studio 2017.
The code depends on Box2D and SFML 2.1 (linked statically). Box2D is included in the repository, but SFML will need to be downloaded. 

## Future
If I do anything like this again, I would start from scratch. 


## Example
Click the following picture for a video:
[<img src="https://cnedwards.github.io/images/nn.jpg?raw=true" alt="Photo" style="width: 450px;"/> ](https://cnedwards.github.io/files/neuralnets_video.mp4)

The green lights are turning lights. The pink lights are forward and backwards. The red bar is a health bar, and it turns yellow after the creature eats something. 

### Executable
There is an executable included: Release/NeuralNet.exe
