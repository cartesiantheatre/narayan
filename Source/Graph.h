/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _GRAPH_H_
#define _GRAPH_H_

// Includes...

    // Provided by Autoconf...
    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif

    // Standard C++ and POSIX system headers...
    #include <atomic>
    #include <cmath>
    #include <memory>
    #include <vector>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Forward declarations the compiler can expect within the Narayan namespace...
//template <class NodeValueType> class Narayan::Node;

// Template for a graph class. Can be undirected or directed. Edges may be 
//  weighted. May contain self loops, multi-edges (non-simple graph), and cyclic
//  paths. An adjacency list is used allow for more efficient handling for
//  sparse graphs...
template <typename NodeValueType, typename EdgeWeightType>
class Graph
{
    // Public types...
    public:

        // Node...
        struct Node
        {
            NodeValueType   Value;
        };
    
    // Protected types...
    protected:
        
        // Smart pointer to a node...
        using NodePointer = std::shared_ptr<Node>;
        
    // Public methods...
    public:
        
        // Default constructor...
        Graph();
        
        // Construct and add a new node using perfect forwarding...
        template<typename ... ArgumentTypes>
        NodePointer AddNode(ArgumentTypes && ... Arguments);

        // Graph is isomorphic...
        bool IsIsomorphic(const Graph &OtherGraph) const;
        
        // Equivalence operator checks for isomorphism...
        bool operator==(const Graph &OtherGraph) const;
        
        // Destructor...
       ~Graph();
   
    // Protected attributes...
    protected:

        // Number of vertices...
        std::atomic< typename std::vector<Graph::Node>::size_type > TotalNodes;
};

// The actual template definitions imported because export keyword deprecated...
#include "Graph.inl"

// Multiple include protection...
#endif

