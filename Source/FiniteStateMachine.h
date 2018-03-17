/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _FINITE_STATE_MACHINE_H_
#define _FINITE_STATE_MACHINE_H_

// Includes...

    // Provided by Autoconf...
    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif

    // Standard C++ and POSIX system headers...
    #include <cstddef>
    #include <functional>
    #include <map>
    #include <memory>
    #include <set>
    #include <vector>

// Template macros to make changing template arguments easier...
#define FiniteStateMachineTemplateDeclaration class SignalType, class StateType
#define FiniteStateMachineTemplateArgumentList SignalType, StateType

// Template for a finite state machine abstract base class...
template<FiniteStateMachineTemplateDeclaration>
class FiniteStateMachine
{
    // Public types...
    public:

        // Transition action callback...
        typedef std::function<void(
            const SignalType &Signal, const StateType &NewState)> 
        TransitionAction;

    // Public methods...
    public:

        // Constructor...
        FiniteStateMachine();

        // Add a transition on a given signal from one state to another, running
        //  an optional action callback as well...
        void AddTransition(
            const StateType &PreviousState,
            const SignalType &Signal,
            const StateType &NewState,
            TransitionAction Action = nullptr);

        // Add a transition on any non-matching signal from one state to
        //  another, running an optional action callback as well...
        void AddTransitionNonMatch(
            const StateType &PreviousState,
            const StateType &NewState,
            const TransitionAction Action = nullptr);

        // Default action callback...
        virtual void DefaultAction(
            const SignalType &Signal,
            const StateType &NewState);

        // Default no action callback when no transition for signal available...
        virtual void DefaultNoAction(const SignalType &Signal);

        // Dispatch an incoming signal, updating the machine as necessary...
        void Dispatch(const SignalType &Signal);

        // Is the machine in a final state?
        bool IsFinalState() const noexcept;

        // Get the current state...
        const StateType &GetState() const noexcept { return m_State; }

        // Get the signal that's used for non-matching signals when a 
        //  non-matching transitions...
        const SignalType &GetNonMatchSignal() const noexcept { return m_NonMatchSignal; }

        // Get a list of all supported signals on the given machine state...
        std::vector<SignalType> GetStateSignals(const StateType &State) const noexcept;

        // Is this a known signal?
        bool IsRegisteredSignal(const SignalType &Signal) const noexcept;

        // Is this a known state?
        bool IsRegisteredState(const StateType &State) const noexcept;

        // Is this the current state of the machine?
        bool IsState(const StateType &State) const noexcept { return State == m_State; }
        bool operator==(const StateType &State) const noexcept { return IsState(State); }

        // Is there a transition arc for non-matching signals at current state?
        bool IsStateHaveNonMatch() const noexcept;

        // Register a signal...
        void RegisterSignal(const SignalType &Signal);

        // Register and set the start state...
        void RegisterStartState(const StateType &StartState);

        // Register a state...
        void RegisterState(const StateType &State);

        // Reset the machine back to the start state...
        void SetStartState() noexcept;

        // Deconstructor...
        virtual ~FiniteStateMachine() { };

    // Protected types...
    protected:

        // State transition type...
        typedef std::pair<TransitionAction, StateType>                  TransitionPairType;

        // (Signal -> Transition) mapping of a single state...
        typedef std::pair<SignalType, TransitionPairType>               SignalToTransitionPairType;
        typedef std::map<SignalType, TransitionPairType>                SignalToTransitionMapType;
        typedef typename SignalToTransitionMapType::iterator            SignalToTransitionIteratorType;
        typedef typename SignalToTransitionMapType::const_iterator      SignalToTransitionConstIteratorType;

        // Smart pointer to (Signal -> Transition) map...
        typedef std::shared_ptr<SignalToTransitionMapType>              SmartSignalToTransitionMapType;

        // (State -> (Signal, Transition)) mapping...
        typedef std::pair<StateType, SmartSignalToTransitionMapType>    StateToSignalTransitionPairType;
        typedef std::map<StateType, SmartSignalToTransitionMapType>     StateToSignalTransitionMapType;
        typedef typename StateToSignalTransitionMapType::iterator       StateToSignalTransitionIteratorType;
        typedef typename StateToSignalTransitionMapType::const_iterator StateToSignalTransitionConstIteratorType;

    // Protected methods...
    protected:

        // Get the signal transition map for the given machine state...
        SmartSignalToTransitionMapType GetSignalTransitionMap(const StateType &State) noexcept;
        const SmartSignalToTransitionMapType GetSignalTransitionMap(const StateType &State) const noexcept;

        // Setup a transition table. Derived implementation must call this...
        virtual void PopulateTransitionTable() = 0;

    // Protected attributes...
    protected:

        // Start state...
        StateType                       m_StartState;

        // Current state...
        StateType                       m_State;

        // State to signal transition table...
        StateToSignalTransitionMapType  m_StateToSignalTransitionMap;

        // Known signals...
        std::set<SignalType>            m_RegisteredSignals;

        // Any non-matching signal will be considered equivalent to this 
        //  value as set during construction...
        const SignalType                m_NonMatchSignal;

        // Known states...
        std::set<StateType>             m_RegisteredStates;
};

// The actual template definitions imported because export keyword deprecated...
#include "FiniteStateMachine.inl"

// Multiple include protection...
#endif

