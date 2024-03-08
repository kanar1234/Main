from pacai.agents.learning.reinforcement import ReinforcementAgent
from pacai.util import reflection, counter, probability
import random


class QLearningAgent(ReinforcementAgent):
    """
    A Q-Learning agent.

    Some functions that may be useful:

    `pacai.agents.learning.reinforcement.ReinforcementAgent.getAlpha`:
    Get the learning rate.

    `pacai.agents.learning.reinforcement.ReinforcementAgent.getDiscountRate`:
    Get the discount rate.

    `pacai.agents.learning.reinforcement.ReinforcementAgent.getEpsilon`:
    Get the exploration probability.

    `pacai.agents.learning.reinforcement.ReinforcementAgent.getLegalActions`:
    Get the legal actions for a reinforcement agent.

    `pacai.util.probability.flipCoin`:
    Flip a coin (get a binary value) with some probability.

    `random.choice`:
    Pick randomly from a list.

    Additional methods to implement:

    `pacai.agents.base.BaseAgent.getAction`:
    Compute the action to take in the current state.
    With probability `pacai.agents.learning.reinforcement.ReinforcementAgent.getEpsilon`,
    we should take a random action and take the best policy action otherwise.
    Note that if there are no legal actions, which is the case at the terminal state,
    you should choose None as the action.

    `pacai.agents.learning.reinforcement.ReinforcementAgent.update`:
    The parent class calls this to observe a state transition and reward.
    You should do your Q-Value update here.
    Note that you should never call this function, it will be called on your behalf.

    DESCRIPTION: <Write something here so we know what you did.>
    """

    def __init__(self, index, **kwargs):
        super().__init__(index, **kwargs)

        # You can initialize Q-values here.
        # Create a counter to store pairs of (state,action) and q-values here
        self.QValues = counter.Counter()

    def getBestPolicyAndQValue(self, state):
        """
        This helper function is made to grab the best
        value and policy with the given state.
        Very convenient to grab both at the same time

        Best action is the direction that gives the highest V value
        in V(s) = amax(Q(s,a))

        Returns best action at index 0
        and returns best policy at index 1

        Edited a bit to work in this file
        """
        directionss = self.getLegalActions(state)
        bestPolicy = None
        bestQValue = float('-inf')
        # checks if there are legal directions
        if len(directionss) == 0:
            return None, 0.0

        for direction in directionss:
            QValue = self.getQValue(state, direction)
            if QValue > bestQValue:
                bestQValue = QValue
                bestPolicy = direction

        return bestPolicy, bestQValue

    def getQValue(self, state, action):
        """
        Get the Q-Value for a `pacai.core.gamestate.AbstractGameState`
        and `pacai.core.directions.Directions`.
        Should return 0.0 if the (state, action) pair has never been seen.
        """
        return self.QValues[(state, action)]

    def getValue(self, state):
        """
        Return the value of the best action in a state.
        I.E., the value of the action that solves: `max_action Q(state, action)`.
        Where the max is over legal actions.
        Note that if there are no legal actions, which is the case at the terminal state,
        you should return a value of 0.0.

        This method pairs with `QLearningAgent.getPolicy`,
        which returns the actual best action.
        Whereas this method returns the value of the best action.
        """
        return self.getBestPolicyAndQValue(state)[1]

    def getPolicy(self, state):
        """
        Return the best action in a state.
        I.E., the action that solves: `max_action Q(state, action)`.
        Where the max is over legal actions.
        Note that if there are no legal actions, which is the case at the terminal state,
        you should return a value of None.

        This method pairs with `QLearningAgent.getValue`,
        which returns the value of the best action.
        Whereas this method returns the best action itself.
        """

        return self.getBestPolicyAndQValue(state)[0]

    def getAction(self, state):
        """
        Compute the action to take in the current state.
        With probability `pacai.agents.learning.reinforcement.ReinforcementAgent.getEpsilon`,
        we should take a random action and take the best policy action otherwise.
        Note that if there are no legal actions, which is the case at the terminal state,
        you should choose None as the action.
        """
        action = None
        directionss = self.getLegalActions(state)
        if probability.flipCoin(self.getEpsilon()):
            # chooses random action
            action = random.choice(directionss)
        else:
            # or the best action
            action = self.getPolicy(state)

        return action

    def update(self, state, action, nextState, reward):
        """
        The parent class calls this to observe a state transition and reward.
        You should do your Q-Value update here.
        Note that you should never call this function, it will be called on your behalf.

        So this updates the QValues dictionary for us

        We update the q-values using the formula
        V(s) = (1 - alpha) * V(s) + alpha * [R(s, policy(s), s') + discount * V*(s)]
        """
        # gotta simplify names to fit in a line
        discount = self.getDiscountRate()
        alpha = self.getAlpha()
        nextQValue = self.getValue(nextState)
        QValue = self.getQValue(state, action)

        newQValue = (1 - alpha) * QValue + alpha * (reward + discount * nextQValue)
        self.QValues[(state, action)] = newQValue

class PacmanQAgent(QLearningAgent):
    """
    Exactly the same as `QLearningAgent`, but with different default parameters.
    """

    def __init__(self, index, epsilon = 0.05, gamma = 0.8, alpha = 0.2, numTraining = 0, **kwargs):
        kwargs['epsilon'] = epsilon
        kwargs['gamma'] = gamma
        kwargs['alpha'] = alpha
        kwargs['numTraining'] = numTraining

        super().__init__(index, **kwargs)

    def getAction(self, state):
        """
        Simply calls the super getAction method and then informs the parent of an action for Pacman.
        Do not change or remove this method.
        """

        action = super().getAction(state)
        self.doAction(state, action)

        return action

class ApproximateQAgent(PacmanQAgent):
    """
    An approximate Q-learning agent.

    You should only have to overwrite `QLearningAgent.getQValue`
    and `pacai.agents.learning.reinforcement.ReinforcementAgent.update`.
    All other `QLearningAgent` functions should work as is.

    Additional methods to implement:

    `QLearningAgent.getQValue`:
    Should return `Q(state, action) = w * featureVector`,
    where `*` is the dotProduct operator.

    `pacai.agents.learning.reinforcement.ReinforcementAgent.update`:
    Should update your weights based on transition.

    DESCRIPTION: <Write something here so we know what you did.>
    """

    def __init__(self, index,
            extractor = 'pacai.core.featureExtractors.IdentityExtractor', **kwargs):
        super().__init__(index, **kwargs)
        self.featExtractor = reflection.qualifiedImport(extractor)

        # You might want to initialize weights here.
        self.weights = counter.Counter()

    def final(self, state):
        """
        Called at the end of each game.
        """

        # Call the super-class final method.
        super().final(state)

        # Did we finish training?
        # if self.episodesSoFar == self.numTraining:
        # You might want to print your weights here for debugging.
        # *** Your Code Here ***
        # print("weights: ", self.weights)

    def getQValue(self, state, action):
        """
        Should return `Q(state, action) = w * featureVector`,
        where `*` is the dotProduct operator.
        """
        QValue = 0.0
        featuress = self.featExtractor.getFeatures(self, state, action)
        for feature in featuress:
            weight = self.weights[feature]
            feature = featuress[feature]
            QValue += weight * feature
        return QValue

    def update(self, state, action, nextState, reward):
        """
        `pacai.agents.learning.reinforcement.ReinforcementAgent.update`:
        Should update your weights based on transition.

        calculations are based on what's given in Q8
        """
        alpha = self.getAlpha()
        discount = self.getDiscountRate()
        nextValue = self.getValue(nextState)
        QValue = self.getQValue(state, action)
        featuress = self.featExtractor.getFeatures(self, state, action)
        correction = (reward + (discount * nextValue)) - QValue
        for feature in featuress:
            self.weights[feature] = self.weights[feature] + alpha * correction * featuress[feature]
