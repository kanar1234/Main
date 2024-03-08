from pacai.agents.learning.value import ValueEstimationAgent
from pacai.util import counter

class ValueIterationAgent(ValueEstimationAgent):
    """
    A value iteration agent.

    Make sure to read `pacai.agents.learning` before working on this class.

    A `ValueIterationAgent` takes a `pacai.core.mdp.MarkovDecisionProcess` on initialization,
    and runs value iteration for a given number of iterations using the supplied discount factor.

    Some useful mdp methods you will use:
    `pacai.core.mdp.MarkovDecisionProcess.getStates`,
    `pacai.core.mdp.MarkovDecisionProcess.getPossibleActions`,
    `pacai.core.mdp.MarkovDecisionProcess.getTransitionStatesAndProbs`,
    `pacai.core.mdp.MarkovDecisionProcess.getReward`.

    Additional methods to implement:

    `pacai.agents.learning.value.ValueEstimationAgent.getQValue`:
    The q-value of the state action pair (after the indicated number of value iteration passes).
    Note that value iteration does not necessarily create this quantity,
    and you may have to derive it on the fly.

    `pacai.agents.learning.value.ValueEstimationAgent.getPolicy`:
    The policy is the best action in the given state
    according to the values computed by value iteration.
    You may break ties any way you see fit.
    Note that if there are no legal actions, which is the case at the terminal state,
    you should return None.
    """

    def __init__(self, index, mdp, discountRate = 0.9, iters = 100, **kwargs):
        super().__init__(index)

        self.mdp = mdp
        self.discountRate = discountRate
        self.iters = iters
        self.values = counter.Counter()  # A Counter is a dict with default 0
        # Compute the values here.
        # print("discountRate: ", self.discountRate)
        # print("iterations: ", self.iters)
        for i in range(self.iters):
            statess = self.mdp.getStates()
            # we want a temporary counter so we
            # can put it in our counter after finishing
            # the calculations
            tempCounter = counter.Counter()
            # I'm going to be adding an extra s to make it really
            # obvious to remind myself which is which
            for state in statess:
                QValue = self.getBestPolicyAndQValue(state)[1]
                # if the q-value is -inf then we set it to 0
                # since it doesn't reach a terminal state
                if QValue == float('-inf'):
                    tempCounter[state] = 0
                else:
                    tempCounter[state] = QValue
            for state in statess:
                self.values[state] = tempCounter[state]
            # checking if my functions give the correct output
            # print("values: ", self.values)

    def getValue(self, state):
        """
        Return the value of the state (computed in __init__).
        """
        return self.values[state]

    def getAction(self, state):
        """
        Returns the policy at the state (no exploration).
        """
        return self.getPolicy(state)

    def getBestPolicyAndQValue(self, state):
        """
        This helper function is made to grab the best
        value and policy with the given state.
        Very convenient to grab both at the same time

        Best action is the direction that gives the highest V value
        in V(s) = amax(Q(s,a))

        Returns best action at index 0
        and returns best policy at index 1
        """
        directionss = self.mdp.getPossibleActions(state)
        bestPolicy = None
        # Initial value has to be -inf since we want negative values
        bestQValue = float('-inf')
        for direction in directionss:
            QValue = self.getQValue(state, direction)
            if QValue > bestQValue:
                bestQValue = QValue
                bestPolicy = direction
        # print("bestQValue: ", bestQValue)
        return bestPolicy, bestQValue

    def getPolicy(self, state):
        """
          The policy is the best action in the given state
          according to the values computed by value iteration.
          You may break ties any way you see fit.
          Note that if there are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        return self.getBestPolicyAndQValue(state)[0]

    def getQValue(self, state, action):
        """
          The q-value of the state action pair
          (after the indicated number of value iteration passes).
          Note that value iteration does not necessarily create this quantity,
          and you may have to derive it on the fly.

          q-value is the sum of T(s,a,s')[R(s,a,s') + discount * V'(s)]
        """
        transitionss = self.mdp.getTransitionStatesAndProbs(state, action)
        QValue = 0
        # print("transitions: ", transitionss)
        for transition in transitionss:
            # grabs s', probability, reward, discount, and V'(s)
            nextState, probability = transition[0], transition[1]
            reward = self.mdp.getReward(state, action, nextState)
            discount = self.discountRate
            nextValue = self.values[nextState]
            # now we calculate that formula that I put above
            QValue += probability * (reward + discount * nextValue)

        return QValue
