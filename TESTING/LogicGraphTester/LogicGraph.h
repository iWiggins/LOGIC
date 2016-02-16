#ifndef LOGIC_GRAPH
#define LOGIC_GRAPH
#include <memory>
#include <list>
#include <map>
#include <functional>
#include <exception>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

namespace LogicGraph
{
    /// <summary>
    /// A logic graph is a collection of nodes connected in an order
    /// wherein nodes have inputs and outputs.
    /// </summary>
    class LogicGraph
    {
        struct Node;

    public:

        typedef unsigned Key;
        typedef std::shared_ptr<Node> Ptr;
        typedef std::map<Key,Ptr> Map;
        typedef std::function<int(int,int)> Gate;
        typedef Ptr* Vec;
        typedef std::unordered_set<Key> Set;
        typedef char SByte;

    private:

        /// <summary>
        /// A node for a logic graph.
        /// </summary>
        struct Node : std::enable_shared_from_this<Node>
        {
        protected:

            Node() = delete;

            Node(Key k)
            {
                key = k;
            }

        public:

            /// <summary>
            /// Returns the output of the gate based on the inputs.
            /// </summary>
            /// <returns>
            ///  0: False
            ///  1: True
            /// -1: No inputs
            /// -2: A higher node returned an error
            /// </returns>
            virtual SByte output() = 0;

            /// <summary>
            /// Adds an input to the map of inputs.
            /// </summary>
            /// <returns>
            ///  0: Success
            ///  1: Input already exists
            ///  2: Given key is an output
            ///  3: (for inverter) Already has an input
            /// -1: (for input) This is an input node, it cannot have an input added
            /// </returns>
            virtual SByte addInput(Key k,Ptr value) = 0;

            /// <summary>
            /// Removes an input from the map of inputs.
            /// </summary>
            /// <params>
            /// k: The key of the input to remove.
            /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
            /// </params>
            /// <returns>
            ///  0: Success
            /// -1: Node has no inputs.
            /// -2: Passed key is not an input.
            /// -3: This gate is not an output to passed input.
            /// -4: (for input) This is an input node, it cannot have an input removed
            /// </returns>
            virtual SByte removeInput(Key k,bool remOut = true) = 0;

            /// <summary>
            /// Adds an output to the map of outputs.
            /// </summary>
            /// <returns>
            ///  0: Success
            SByte addOutput(Key k,Ptr value)
            {
                outputs[k] = value;

                return 0;
            }

            /// <summary>
            /// Removes an output from the map of outputs.
            /// </summary>
            /// <returns>
            ///  0: Success
            /// -1: No outputs
            /// -2: Output does not exist
            /// </returns>
            SByte removeOutput(Key k)
            {
                if(outputs.count(k) <= 0) return -2;

                if(outputs.size() == 0) return -1;

                outputs.erase(k);

                return 0;
            }

            /// <summary>
            /// Removes all inputs and all outputs.
            /// </summary>
            /// <returns>
            /// -2: An input does not list this as an output.
            /// -1: An output does not list this as an input.
            ///  0: Success
            /// </returns>
            virtual SByte disconnect()
            {
                SByte ret = 0;

                invalidateOutput();

                for(auto a : outputs){
                    SByte c = a.second->removeInput(key,false);

                    if(c == -1) ret = -1;
                }

                outputs.clear();

                return ret;
            }

            /// <summary>
            /// Returns the key of this gate.
            /// </summary>
            Key getKey() const
            {
                return key;
            }

            /// <summary>
            /// Invalidates any outputs.
            /// </summary>
            virtual void invalidateOutput()
            {
                for(auto a : outputs){

                    a.second->invalidateOutput();

                }
            }

        protected:

            Map outputs;

            Key key;

            /// <summary>
            /// Checks if any of the passed node is an output to any of the nodes along the tree.
            /// </summary>
            static bool isOutput(Ptr current,Key node)
            {
                if(current->outputs.size() == 0) return false;

                if(current->outputs.count(node) > 0) return true;

                for(auto a : current->outputs){

                    if(isOutput(a.second,node)) return true;
                }

                return false;
            }
        };

        struct GateNode : Node
        {
            GateNode(Key k,Gate g) : Node(k)
            {
                gate = g;
            }

            SByte output()
            {
                if(inputs.begin() == inputs.end()){

                    return -1;//No inputs.
                }

                if(storedOutput == -1){

                    int Ts = 0;
                    int Fs = 0;

                    for(auto a : inputs){

                        a.second->output() ? ++Ts : ++Fs;

                    }

                    storedOutput = gate(Ts,Fs) ? 1 : 0;
                }

                return storedOutput == 1;
            }

            void invalidateOutput()
            {
                storedOutput = -1;

                Node::invalidateOutput();
            }

            SByte addInput(Key k,Ptr value)
            {
                if(inputs.count(k) > 0) return 1;
                else if(isOutput(shared_from_this(),k)) return 2;

                inputs[k] = value;

                value->addOutput(key,shared_from_this());

                invalidateOutput();

                return 0;
            }

            SByte removeInput(Key k,bool removeOut = true)
            {
                if(inputs.size() == 0) return -1;
                if(inputs.count(k) == 0) return -2;

                if(removeOut){
                    SByte c = inputs[k]->removeOutput(key);
                    if(c < 0) return -3;
                }
                inputs.erase(k);

                invalidateOutput();

                return 0;
            }

            SByte disconnect()
            {
                std::list<Key>inputKs;
                for(auto a : inputs){
                    inputKs.push_back(a.first);
                }

                for(auto a : inputKs){
                    SByte c = inputs[a]->removeOutput(key);

                    if(c < 0) return -2;
                }

                inputs.clear();

                return Node::disconnect();
            }

        private:

            int storedOutput;
            Gate gate;
            Map inputs;
        };

        struct InverterNode : Node
        {
            InverterNode(Key k) : Node(k)
            {
                input.reset();
            }

            SByte output()
            {
                if(input == nullptr) return -1;

                SByte lastOut = input->output();

                if(lastOut < 0) return -2;

                return lastOut == 0 ? 1 : 0;
            }

            SByte addInput(Key k,Ptr value)
            {
                if(input != nullptr) return 3;
                input = value;
                return 0;
            }

            SByte removeInput(Key k, bool remOut = true)
            {
                if(input == nullptr) return -1;

                if(input->getKey() == k){
                    if(remOut) input->removeOutput(key);
                    input.reset();
                    return 0;
                }
                else return -2;
            }

            SByte disconnect()
            {
                if(input != nullptr){

                    SByte c = input->removeOutput(key);
                    if(c < 0) return -2;
                    input.reset();
                }

                return Node::disconnect();
            }

        private:

            Ptr input;
        };

        struct InputNode : Node
        {
            InputNode(Key k,unsigned i) : Node(k)
            {
                index = i;
                myVal = false;
            }

            void setVal(bool b)
            {
                if(myVal != b){
                    myVal = b;
                    invalidateOutput();
                }
            }

            SByte addInput(Key k,Ptr value)
            {
                return -1;
            }

            SByte removeInput(Key k,bool b)
            {
                return -3;
            }

            SByte output() { return myVal ? 1 : 0; }

            unsigned getIndex() const
            {
                return index;
            }

        private:

            bool myVal;
            unsigned index;
        };

    public:


        struct Gates
        {
            static Gate AND;

            static Gate OR;

            static Gate NAND;

            static Gate NOR;

            static Gate XOR;
        };

        LogicGraph(unsigned inputCount,unsigned outputCount)
        {
            currentKey = 1;
            inputs = new Ptr[inputCount];

            for(unsigned i = 0; i < inputCount; ++i){

                Key k = currentKey++;
                auto point = std::make_shared<InputNode>(k,i); 
                inputs[i] = point;
                nodes[k] = point;
                inKeys.insert(k);
            }

            outputs = new Ptr[outputCount];
        }

        ~LogicGraph()
        {
            if(inputs != nullptr) delete [] inputs;
            if(outputs != nullptr) delete [] outputs;
        }

        Key addGate(Gate gate)
        {
            Key k = currentKey++;

            nodes[k] = std::make_shared<GateNode>(k,gate);

            return k;
        }

        Key addInverter()
        {
            Key k = currentKey++;

            nodes[k] = std::make_shared<InverterNode>(k);

            return k;
        }

        SByte connectGates(Key gate,Key input)
        {
            return nodes[gate]->addInput(input,nodes[input]);
        }

        SByte disconnectGates(Key gate,Key input)
        {
            return nodes[gate]->removeInput(input);
        }

        /// <summary>
        /// Removes the gate from the graph.
        /// </summary>
        /// <returns>
        /// -3: That key does not exist.
        /// -2: An input does not list this as an output. (from Node.disconnect)
        /// -1: An output does not list this as an input. (from Node.disconnect)
        ///  0: Success
        /// </returns>
        SByte removeGate(Key gate)
        {
            if(inKeys.count(gate) > 0){

                return -3;
            }

            SByte c = nodes[gate]->disconnect();

            if(c < 0) return c;

            nodes.erase(gate);

            return 0;
        }

        Key getInputKey(unsigned index)
        {
            return inputs[index]->getKey();
        }

        Key createKey()
        {
            return currentKey++;
        }

        void setInputVal(unsigned index,bool val)
        {
            auto ptr = (InputNode*)(inputs[index].get());

            ptr->setVal(val);
        }

        void collectOutput(Key gate,unsigned index)
        {
            outputs[index] = nodes[gate];
        }

        /// <summary>
        /// Returns the output with the given index.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs (from Node.output)
        /// -2: A higher node returned an error (from Node.output)
        /// -3: An output does not exist.
        /// </returns>
        SByte getOutput(unsigned index)
        {
            if(outputs[index] == nullptr) return -3;

            return outputs[index]->output();
        }

        /// <summary>
        /// Returns the output of the gate based on the inputs.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs
        /// -2: A higher node returned an error
        /// </returns>
        SByte testOutput(Key gate)
        {
            return nodes[gate]->output();
        }

        SByte inputToGate(Key gate, unsigned index)
        {
            return connectGates(gate,getInputKey(index));
        }

        SByte removeInputToGate(Key gate,unsigned index)
        {
            return disconnectGates(gate,getInputKey(index));
        }

        SByte removeConnection(Key gate0,Key gate1)
        {
            SByte c = nodes[gate0]->removeInput(gate1);

            if(c < -1) c = nodes[gate1]->removeInput(gate0);

            return c;
        }

    private:

        Map nodes;
        Vec inputs;
        Vec outputs;
        Key currentKey;
        Set inKeys;
    };

    #define Gate_Sig [](int Ts, int Fs)->int

    LogicGraph::Gate LogicGraph::Gates::AND = Gate_Sig
    {
        return Ts > 0 && Fs == 0 ? 1 : 0;
    };

    LogicGraph::Gate LogicGraph::Gates::OR = Gate_Sig
    {
        return Ts > 0 ? 1 : 0;
    };

    LogicGraph::Gate LogicGraph::Gates::NAND = Gate_Sig
    {
        return Fs > 0 ? 1 : 0;
    };

    LogicGraph::Gate LogicGraph::Gates::NOR = Gate_Sig
    {
        return Ts == 0 ? 1 : 0;
    };

    LogicGraph::Gate LogicGraph::Gates::XOR = Gate_Sig
    {
        return Ts == 1 ? 1 : 0;
    };
}

#endif//LOGIC_GRAPH
