/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

// Default constructor...
template <typename NodeValueType, typename EdgeWeightType>
Graph<NodeValueType, EdgeWeightType>::Graph()
{

}

// Construct and add a new node using perfect forwarding...
template<typename NodeValueType, typename EdgeWeightType>
template<typename ... ArgumentTypes>
typename Graph<NodeValueType, EdgeWeightType>::NodePointer Graph<NodeValueType, EdgeWeightType>::
    AddNode(ArgumentTypes && ... Arguments)
{

}

// Graph is isomorphic...
template <typename NodeValueType, typename EdgeWeightType>
bool Graph<NodeValueType, EdgeWeightType>::IsIsomorphic([[maybe_unused]] const Graph &OtherGraph) const
{
    // Stubbed...
    return false;
}

// Equivalence operator check for isomorphism...
template <typename NodeValueType, typename EdgeWeightType>
bool Graph<NodeValueType, EdgeWeightType>::operator==(const Graph &OtherGraph) const
{
    return IsIsomorphic(OtherGraph);
}

// Destructor...
template <typename NodeValueType, typename EdgeWeightType>
Graph<NodeValueType, EdgeWeightType>::~Graph()
{

}

