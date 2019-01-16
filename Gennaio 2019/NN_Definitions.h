//
//  NN_Definitions.h
//  Neural Network
//
//  Created by Luca Savant on 11/05/17.
//  Copyright © 2017 Luca Savant. All rights reserved.
//

#ifndef NN_Definitions_h
#define NN_Definitions_h

#include <vector>
#include <utility>

// Identifier of a single neuron in the netowrk. First number: layer number, second number: neuron number
typedef std::pair<short, short> neuronID;

enum neuronType {input, output, hidden};
//enum layerType {inputL, outputL, hiddenL};

class Neuron{
    friend class NeuralNetwork;
protected:
    //neuronID NeuronID;
    neuronType NeuronType;
    double Value;
    std::vector<std::pair<neuronID, double>> Ingressi;
    
    
    static double Sigmoid_Function(neuronID ID);
    static neuronID Calculate_Neuron_ID(int Layer, int Number);
    static double Get_Value_From_Input_Neurons(neuronID ID);
    
    
    
};

//class Layer{
//    int Dimension;
//    layerType LayerType;
//    
//    std::vector<Neuron>
//    Neuron Neurons_in_Layer[Dimension];
//    
//    
//};

class NeuralNetwork{
private:
    int NumberOfInputNeurons;
    int NumberOfOutputNeurons;
    int NumberOfHiddenNeuronsPerLayer;
    int NumberOfHiddenLayer;
    
    std::vector<Neuron> NeuronMap;
    
    
    
    
public:
    NeuralNetwork(int NoInputNeurons, int NoOutputNeurons, int NoHiddenNeuronsPerLayer,int NoHiddenLayer);
    void Insert_Input();
    void Expand_Input_Ad_Output();
    
};

#endif /* NN_Definitions_h */
