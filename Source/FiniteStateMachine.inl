/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Standard C++ and POSIX headers...
    #include <algorithm>
    #include <cassert>

    // Our header...
    #include "FiniteStateMachine.h"

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

//extern template class FiniteStateMachine<class SignalType, class StateType>;

// Default constructor...
template<FiniteStateMachineTemplateDeclaration>
FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::FiniteStateMachine()
    : m_State(StateType()),
      m_NonMatchSignal(SignalType())
{
    // For any non-matching signal, we will register a constant that's available
    //  for transitions that don't match any other signal if user requests...
    RegisterSignal(m_NonMatchSignal);
}

// Add a transition on a given signal from one state to another, running
//  an optional action callback as well...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::AddTransition(
    const StateType &PreviousState,
    const SignalType &Signal,
    const StateType &NewState,
    TransitionAction Action)
{
    // Verify signal and states are known...

        // Trigger signal...
        if(!IsRegisteredSignal(Signal))
            throw std::invalid_argument(_("signal not registered"));

        // Previous state...
        if(!IsRegisteredState(PreviousState))
            throw std::invalid_argument(_("unknown previous state"));

        // New state...
        if(!IsRegisteredState(NewState))
            throw std::invalid_argument(_("unknown new state"));

    // Find the signal to transition map for the previous machine state...
    SmartSignalToTransitionMapType SmartSignalToTransitionMap = 
        GetSignalTransitionMap(PreviousState);

    // Set transition from the previous machine state to the new one on the
    //  given signal...

        // Prepare action to perform during transition to the next state...
        TransitionPairType TransitionPair(Action, NewState);
        SignalToTransitionPairType SignalToTransitionPair(Signal, TransitionPair);

        // Set the transition...
        SmartSignalToTransitionMap.get()->insert(SignalToTransitionPair);
}

// Add a transition on any non-matching signal from one state to another, 
//  running an optional action callback as well...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::AddTransitionNonMatch(
    const StateType &PreviousState,
    const StateType &NewState,
    const TransitionAction Action)
{
    // Use the non-matching signal constant as the signal...
    AddTransition(PreviousState, m_NonMatchSignal, NewState, Action);
}

// Default action callback...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::DefaultAction(
    const SignalType &Signal,
    const StateType &NewState)
{
    /* Do nothing for now, but can be overriden by subclass. */
    (void)(Signal);
    (void)(NewState);
}

// Default no action callback when no transition for signal available...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::DefaultNoAction(
    const SignalType &Signal)
{
    /* Do nothing for now, but can be overriden by subclass. */
    (void)(Signal);
}

// Dispatch an incoming signal, updating the machine as necessary...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    Dispatch(const SignalType &Signal)
{
    // Verify signal is known...
    if(!IsStateHaveNonMatch() && !IsRegisteredSignal(Signal))
        throw std::invalid_argument(_("signal is not registered"));

    // Find the transition map for the current machine state...
    //  (State -> (Signal, Transition))
    SmartSignalToTransitionMapType SmartSignalToTransitionMap =
        GetSignalTransitionMap(GetState());

    // Find the appropriate transition for the given signal...
    //  (Signal -> Transition)

        // Query...
        SignalToTransitionIteratorType SignalToTransitionIterator =
            SmartSignalToTransitionMap.get()->find(Signal);

            // No explicit transition found from this state...
            if(SignalToTransitionIterator == SmartSignalToTransitionMap.get()->end())
            {
                // Use the non-matching signal transition arc, if available...
                SignalToTransitionIterator =
                    SmartSignalToTransitionMap.get()->find(m_NonMatchSignal);

                    // None available...
                    if(SignalToTransitionIterator == SmartSignalToTransitionMap.get()->end())
                    {
                        // Invoke default no action dispatch callback...
                        DefaultNoAction(Signal);

                        // We don't change the machine state...
                        return;
                    }
            }

        // Retrieve the (Signal -> Transition) mapping...
        SignalToTransitionPairType SignalToTransitionPair = *SignalToTransitionIterator;

    // Invoke the requested action...

        // Get the transition pair (TransitionAction, NewState)
        TransitionPairType TransitionPair = SignalToTransitionPair.second;

        // Get the transition callback pointer, if any...
        TransitionAction Action = TransitionPair.first;

        // Get the next state we will transition to...
        const StateType &NewState = TransitionPair.second;

        // Use the client's provided callback, if any...
        if(Action)
            Action(Signal, NewState);

        // Otherwise call the default action...
        else
            DefaultAction(Signal, NewState);

    // Now update the current machine state...
    m_State = NewState;
}

// Get the signal transition map for the given machine state...
template<FiniteStateMachineTemplateDeclaration>
typename FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::SmartSignalToTransitionMapType 
FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    GetSignalTransitionMap(const StateType &State) noexcept
{
    // State must have been registered first...
    assert(IsRegisteredState(State));

    // Query State -> (Signal, Transition) mapping...
    StateToSignalTransitionIteratorType StateToSignalTransitionIterator =
        m_StateToSignalTransitionMap.find(State);

    // Check for failure, though this should never happen if the state was
    //  registered...
    assert(StateToSignalTransitionIterator != m_StateToSignalTransitionMap.end());

    // Get the given state's signal transition map...
    StateToSignalTransitionPairType StateToSignalTransitionPair = 
        *StateToSignalTransitionIterator;

    // Return a reference to the (Signal, Transition) mapping...
    return StateToSignalTransitionPair.second;
}

// Get the signal transition map for the given machine state... (const)
template<FiniteStateMachineTemplateDeclaration>
const typename FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::SmartSignalToTransitionMapType 
FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    GetSignalTransitionMap(const StateType &State) const noexcept
{
    // State must have been registered first...
    assert(IsRegisteredState(State));

    // Query State -> (Signal, Transition) mapping...
    StateToSignalTransitionConstIteratorType StateToSignalTransitionIterator =
        m_StateToSignalTransitionMap.find(State);

    // Check for failure, though this should never happen if the state was
    //  registered...
    assert(StateToSignalTransitionIterator != m_StateToSignalTransitionMap.end());

    // Get the given state's signal transition map...
    const StateToSignalTransitionPairType StateToSignalTransitionPair =
        *StateToSignalTransitionIterator;

    // Return a reference to the (Signal, Transition) mapping...
    return StateToSignalTransitionPair.second;
}

// Get a list of all supported signals on the given machine state...
template<FiniteStateMachineTemplateDeclaration>
std::vector<SignalType> FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    GetStateSignals(const StateType &State) const noexcept
{
    // Get the signal to transition map for the given machine state...
    const SmartSignalToTransitionMapType SmartSignalToTransitionMap = 
        GetSignalTransitionMap(State);

    // Get the signal to transition map from the smart pointer...
    const SignalToTransitionMapType &SignalToTransitionMap =
        *(SmartSignalToTransitionMap.get());

    // Prepare storage for all the signals found...
    std::vector<SignalType> StateSignals;

    // Scan through the given state's signal to transition map...
    for(SignalToTransitionConstIteratorType SignalToTransitionIterator = 
            SignalToTransitionMap.begin();
        SignalToTransitionIterator != SignalToTransitionMap.end();
      ++SignalToTransitionIterator)
    {
        // Get a signal to transition pair...
        const SignalToTransitionPairType &SignalToTransitionPair = 
            *SignalToTransitionIterator;

        // Isolate just the signal and add it to the list...
        StateSignals.push_back(SignalToTransitionPair.first);
    }

    // Sort and optimize the detected signals... (optional)
    std::sort(StateSignals.begin(), StateSignals.end());
    StateSignals.shrink_to_fit();

    // Return all detected signals...
    return StateSignals;
}

// Is the machine in a final state?
template<FiniteStateMachineTemplateDeclaration>
bool FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    IsFinalState() const noexcept
{
    // Get the current machine state's signal to transition map...
    SmartSignalToTransitionMapType &SmartSignalToTransitionMap = 
        GetSignalTransitionMap(GetState());

    // If the signal to transition map is empty, then we know that it was no
    //  outgoing edges...
    return SmartSignalToTransitionMap.get()->empty();
}

// Is this a known signal?
template<FiniteStateMachineTemplateDeclaration>
bool FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    IsRegisteredSignal(const SignalType &Signal) const noexcept
{
    // Check registered signals...
    return (m_RegisteredSignals.find(Signal) != m_RegisteredSignals.end());
}

// Is this a known state?
template<FiniteStateMachineTemplateDeclaration>
bool FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    IsRegisteredState(const StateType &State) const noexcept
{
    // Check registered states...
    return (m_RegisteredStates.find(State) != m_RegisteredStates.end());
}

// Is there a transition arc for non-matching signals at the current state?
template<FiniteStateMachineTemplateDeclaration>
bool FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    IsStateHaveNonMatch() const noexcept
{
    // Get the current machine state's signal to transition map...
    SmartSignalToTransitionMapType SmartSignalToTransitionMap =
        GetSignalTransitionMap(GetState());

    // Check...
    return (SmartSignalToTransitionMap.get()->find(m_NonMatchSignal) !=
            SmartSignalToTransitionMap.get()->end());
}

// Registered a signal...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    RegisterSignal(const SignalType &Signal)
{
    // Verify signal not already registered...
    if(IsRegisteredSignal(Signal))
        throw std::invalid_argument(_("signal already registered"));

    // Register the signal...
    m_RegisteredSignals.insert(Signal);
}

// Registered a start state...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    RegisterStartState(const StateType &StartState)
{
    // Register the state...
    RegisterState(StartState);

    // Set it as the start state...
    m_StartState = StartState;
    m_State = m_StartState;
}

// Registered a state...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    RegisterState(const StateType &State)
{
    // Verify state not already registerd...
    if(IsRegisteredState(State))
        throw std::invalid_argument(_("machine state already registered"));

    // Register the state...
    m_RegisteredStates.insert(State);

    // Add an empty signal transition table for the state...
    StateToSignalTransitionPairType StateToSignalTransitionPair(State, SmartSignalToTransitionMapType(new SignalToTransitionMapType));
    m_StateToSignalTransitionMap.insert(StateToSignalTransitionPair);
}

// Reset the machine back to the start state...
template<FiniteStateMachineTemplateDeclaration>
void FiniteStateMachine<FiniteStateMachineTemplateArgumentList>::
    SetStartState() noexcept
{
    // Set the current state to the start state...
    m_State = m_StartState;
}

