package games.pacman.features;

import neuralj.networks.feedforward.*;
import neuralj.networks.feedforward.activation.ActivationFunctionSigmoid;
import neuralj.networks.feedforward.activation.ActivationFunctionLinear;
import neuralj.networks.feedforward.activation.IActivationFunction;
import neuralj.Mathematics;

import java.util.Random;
import java.util.Vector;

/**
 * Created by IntelliJ IDEA.
 * User: kristoffer
 * Date: Dec 4, 2009
 * Time: 7:26:48 PM
 * To change this template use File | Settings | File Templates.
 */
public class PacmanFeedForwardNeuralNetwork extends FeedForwardNeuralNetwork {
    
    public PacmanFeedForwardNeuralNetwork(int input_size, int[] hidden_size, int output_size)
	{
		super(input_size, hidden_size, output_size, new ActivationFunctionHTangent());
        System.out.println("Size NeuralN: "+this.neuron_layers.size());
	}    

	/**
	 * Connects neurons from one layer to the next
	 *
	 * @param source
	 *            Source layer
	 * @param destination
	 *            Destination layer
	 * @return Boolean indicating if the operation was successful
	 */
	private boolean connectLayers(int source, int destination)
	{
		int iter2;
		SynapseLayer synapse_layer = new SynapseLayer();
		for (Neuron neuron : this.neuron_layers.get(source).neurons)
		{
			// int last_neuron_layer = this.neuron_layers.size() - 1;
			for (iter2 = 0; iter2 < this.neuron_layers.get(destination).neurons.size(); iter2++)
			{
				if (this.neuron_layers.get(destination).neurons.get(iter2).neuron_type == Neuron.NeuronType.Normal)
				{
					Neuron source_neuron = neuron;
					Neuron destination_neuron = this.neuron_layers.get(destination).getNeuron(iter2);
					Synapse synapse = connectNeurons(source_neuron, destination_neuron);
					synapse_layer.synapses.add(synapse);
				}
			}
		}
		this.synapse_layers.add(synapse_layer);
		return true;
	}
    

    public Synapse connectNeurons(Neuron source, Neuron destination)
	{
        Random rnd = new Random(); 
		double weight = rnd.nextGaussian()*Math.sqrt(getNumberNeuronsInput(Neuron.NeuronType.Normal));
		Synapse synapse = new Synapse(source, destination, weight);
		source.outgoing_synapses.add(synapse);
		destination.incoming_synapses.add(synapse);
		return synapse;		
	}

}
