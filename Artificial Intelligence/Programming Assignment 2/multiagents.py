import random

from pacai.agents.base import BaseAgent
from pacai.agents.search.multiagent import MultiAgentSearchAgent
from pacai.core import distance

class ReflexAgent(BaseAgent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.
    You are welcome to change it in any way you see fit,
    so long as you don't touch the method headers.
    """

    def __init__(self, index, **kwargs):
        super().__init__(index)

    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        `ReflexAgent.getAction` chooses among the best options according to the evaluation function.

        Just like in the previous project, this method takes a
        `pacai.core.gamestate.AbstractGameState` and returns some value from
        `pacai.core.directions.Directions`.
        """

        # Collect legal moves.
        legalMoves = gameState.getLegalActions()
        # Choose one of the best actions.
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices)  # Pick randomly among the best.

        # print("legal moves: ", end = "")
        # print(legalMoves)
        # print("scores: ", scores)
        # print("bestScore: ", bestScore)
        # print("bestIndices: ", bestIndices)
        # print("chosenIndex: ", chosenIndex)
        # print("---------------------------")
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current `pacai.bin.pacman.PacmanGameState`
        and an action, and returns a number, where higher numbers are better.
        Make sure to understand the range of different values before you combine them
        in your evaluation function.
        """

        successorGameState = currentGameState.generatePacmanSuccessor(action)

        # Useful information you can extract.
        newPosition = successorGameState.getPacmanPosition()
        oldFood = currentGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        # newScaredTimes = [ghostState.getScaredTimer() for ghostState in newGhostStates]
        score = 0

        # Runs away from ghosts if you can't eat it

        # Looks at the state of the ghosts
        for ghosts in newGhostStates:
            distFromGhost = distance.manhattan(newPosition, ghosts.getPosition())
            # print("manhattan from ghost is: ", distFromGhost)
            # print("ghost position is: ", ghosts.getPosition())
            if distFromGhost <= 1:
                # print("Scaredtimer: ", ghosts.getScaredTimer())
                if ghosts.getScaredTimer() == 0:
                    # should cost a little more to die to a ghost than to eat it when it's a tie
                    score -= 690
                else:
                    score += 420
            else:
                # if the ghost is within some steps
                if ghosts.getScaredTimer() == 0:
                    # wants to move away if not eatable and within 5 steps
                    score -= 5 / distFromGhost
                else:
                    # wants to move closer if it is eatable and within 10 steps
                    score += 10 / distFromGhost

        # Why does pacman even stop
        # also don't kill yourself to not stop
        if action == "Stop":
            score -= 69

        # Wants to eat food
        foodList = oldFood.asList()
        if newPosition in foodList:
            score += 200
        else:
            for food in foodList:
                # Wants to go to the nearest food, closer food has lower values
                # so we want the reciprocal
                # we want to start at 10 because we want to choose the area with
                # less food IF it is very close to us (within 10 steps)
                score += 10 / distance.manhattan(food, newPosition)

        # print("newPosition: ", end = "")
        # print(newPosition)
        # print("newScaredTimes: ", end = "")
        # print(newScaredTimes)
        # *** Your Code Here ***

        return score

class MinimaxAgent(MultiAgentSearchAgent):
    """
    A minimax agent.

    Here are some method calls that might be useful when implementing minimax.

    `pacai.core.gamestate.AbstractGameState.getNumAgents()`:
    Get the total number of agents in the game

    `pacai.core.gamestate.AbstractGameState.getLegalActions`:
    Returns a list of legal actions for an agent.
    Pacman is always at index 0, and ghosts are >= 1.

    `pacai.core.gamestate.AbstractGameState.generateSuccessor`:
    Get the successor game state after an agent takes an action.

    `pacai.core.directions.Directions.STOP`:
    The stop direction, which is always legal, but you may not want to include in your search.

    Method to Implement:

    `pacai.agents.base.BaseAgent.getAction`:
    Returns the minimax action from the current gameState using
    `pacai.agents.search.multiagent.MultiAgentSearchAgent.getTreeDepth`
    and `pacai.agents.search.multiagent.MultiAgentSearchAgent.getEvaluationFunction`.
    """

    def __init__(self, index, **kwargs):
        super().__init__(index, **kwargs)

    # returns best action to take given the current state
    def getAction(self, gameState):
        return self.minimax(gameState, self.getTreeDepth())

    def legalMovesOfAgent(self, gameState, agentID):
        # Collect legal moves of agent that isn't stop
        legalMoves = []
        for action in gameState.getLegalActions(agentID):
            if action != "Stop":
                legalMoves.append(action)
        return legalMoves

    def minimax(self, gameState, depth):
        value = -float("inf")
        move = "Stop"

        # calls maxValue on successor states
        for a in self.legalMovesOfAgent(gameState, 0):
            # creates an initial successor for the current action
            # and chooses the outcome that gives the best score
            successor = gameState.generateSuccessor(0, a)
            score = self.maxValue(successor, depth)
            if score > value:
                move = a
                value = score
        # print("move: ", move)
        # print("-------------------------------")
        return move

    # max value for pacman
    def maxValue(self, gameState, depth):
        # base case - if game is terminal state, returns the eval function
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.getEvaluationFunction()(gameState)

        v = -float("inf")
        # returns the best legal move for pacman
        for a in self.legalMovesOfAgent(gameState, 0):
            successor = gameState.generateSuccessor(0, a)
            v2 = self.minValue(successor, depth, 1)
            if v2 > v:
                v = v2
        return v

    # min value for ghosts
    def minValue(self, gameState, depth, ghostAgentID):
        # base case - if game is terminal state, returns the eval function
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.getEvaluationFunction()(gameState)

        v = float("inf")
        for a in self.legalMovesOfAgent(gameState, ghostAgentID):
            successor = gameState.generateSuccessor(ghostAgentID, a)
            # calls maxValue again after looking at all the ghosts
            if ghostAgentID == gameState.getNumAgents() - 1:
                v2 = self.maxValue(successor, depth - 1)
                if v2 < v:
                    v = v2
            else:
                # returns worst value for ghost(s)
                v2 = self.minValue(successor, depth, ghostAgentID + 1)
                if v2 < v:
                    v = v2
        return v

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    A minimax agent with alpha-beta pruning.

    Method to Implement:

    `pacai.agents.base.BaseAgent.getAction`:
    Returns the minimax action from the current gameState using
    `pacai.agents.search.multiagent.MultiAgentSearchAgent.getTreeDepth`
    and `pacai.agents.search.multiagent.MultiAgentSearchAgent.getEvaluationFunction`.
    """

    def __init__(self, index, **kwargs):
        super().__init__(index, **kwargs)

    # returns best action to take given the current state
    # and also prunes useless children
    def getAction(self, gameState):
        return self.minimax(gameState, self.getTreeDepth())

    def legalMovesOfAgent(self, gameState, agentID):
        # Collect legal moves of current agent that isn't stop
        # to save me some time
        legalMoves = []
        for action in gameState.getLegalActions(agentID):
            if action != "Stop":
                legalMoves.append(action)
        return legalMoves

    def minimax(self, gameState, depth):
        value = -float("inf")
        move = "Stop"
        alpha = -float("inf")
        beta = float("inf")
        # calls maxValue on successor states
        for a in self.legalMovesOfAgent(gameState, 0):
            # creates an initial successor for the current action
            # and chooses the outcome that gives the best score
            successor = gameState.generateSuccessor(0, a)
            score = self.maxValue(successor, depth, alpha, beta)
            if score > value:
                move = a
                value = score
        # print("move: ", move)
        # print("-------------------------------")
        return move

    # max value for pacman
    def maxValue(self, gameState, depth, alpha, beta):
        # base case - if game is terminal state, returns the eval function
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.getEvaluationFunction()(gameState)

        v = -float("inf")
        # returns the best legal move for pacman
        for a in self.legalMovesOfAgent(gameState, 0):
            successor = gameState.generateSuccessor(0, a)
            v2 = self.minValue(successor, depth, alpha, beta, 1)
            if v2 > v:
                v = v2
                alpha = max(alpha, v)
            # prunes useless children
            if v >= beta:
                return v
        return v

    # min value for ghosts
    def minValue(self, gameState, depth, alpha, beta, ghostAgentID):
        # base case - if game is terminal state, returns the eval function
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.getEvaluationFunction()(gameState)

        v = float("inf")
        for a in self.legalMovesOfAgent(gameState, ghostAgentID):
            successor = gameState.generateSuccessor(ghostAgentID, a)
            # calls maxValue again after looking at all the ghosts
            if ghostAgentID == gameState.getNumAgents() - 1:
                v2 = self.maxValue(successor, depth - 1, alpha, beta)
                if v2 < v:
                    v = v2
                    beta = min(beta, v)
                # prunes useless children
                if v <= alpha:
                    return v
            else:
                # returns worst value for ghost(s)
                v2 = self.minValue(successor, depth, alpha, beta, ghostAgentID + 1)
                if v2 < v:
                    v = v2
                    beta = min(beta, v)
                # prunes useless children
                if v <= alpha:
                    return v
        return v

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
    An expectimax agent.

    All ghosts should be modeled as choosing uniformly at random from their legal moves.

    Method to Implement:

    `pacai.agents.base.BaseAgent.getAction`:
    Returns the expectimax action from the current gameState using
    `pacai.agents.search.multiagent.MultiAgentSearchAgent.getTreeDepth`
    and `pacai.agents.search.multiagent.MultiAgentSearchAgent.getEvaluationFunction`.
    """

    def __init__(self, index, **kwargs):
        super().__init__(index, **kwargs)

    def getAction(self, gameState):
        return self.expectimax(gameState, self.getTreeDepth())

    def legalMovesOfAgent(self, gameState, agentID):
        # Collect legal moves of current agent that isn't stop
        # to save me some time
        legalMoves = []
        for action in gameState.getLegalActions(agentID):
            if action != "Stop":
                legalMoves.append(action)
        return legalMoves

    def expectimax(self, gameState, depth):
        value = -float("inf")
        move = "Stop"
        # calls expectimax on successor states
        for a in self.legalMovesOfAgent(gameState, 0):
            # creates an initial successor for the current action
            # and chooses the outcome that gives the best score
            successor = gameState.generateSuccessor(0, a)
            score = self.value(successor, depth, 1)
            if score > value:
                move = a
                value = score
        # print("move: ", move)
        # print("-------------------------------")
        return move

    def value(self, gameState, depth, agentID):
        # base case - if game is terminal state, returns the eval function
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.getEvaluationFunction()(gameState)

        # if max node, return max value
        if agentID == 0:
            return self.maxValue(gameState, depth, 0)

        # if exp node return exp value
        else:
            return self.expValue(gameState, depth, agentID)

    def maxValue(self, gameState, depth, agentID):
        # store a list of legal moves of current agent
        moves = self.legalMovesOfAgent(gameState, agentID)

        value = -float("inf")
        for a in moves:
            successor = gameState.generateSuccessor(0, a)
            value = max(value, self.value(successor, depth - 1, agentID + 1))
        return value

    def expValue(self, gameState, depth, agentID):
        value = 0
        # store a list of legal moves of current agent
        moves = self.legalMovesOfAgent(gameState, agentID)

        for a in moves:
            successor = gameState.generateSuccessor(agentID, a)
            if agentID != gameState.getNumAgents() - 1:
                nextAgent = (agentID + 1)
            else:
                nextAgent = 0
            value += self.value(successor, depth, nextAgent)
        # returns average expected value
        return value / len(moves)

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable evaluation function.

    DESCRIPTION: <write something here so we know what you did>
    To begin, I make pacman never want to lose and always want to win using the terminal states.

    I make the time matter, so the first thing I do is put a weight on each move pacman takes so it
    is less likely to move back and forth.

    Like my original eval function, I want to eat scared ghosts so I find the nearest ghost and
    put a high value for eating it if it's with 5 steps from pacman. I can ignore being near a
    brave ghost since that would lead to a terminal state.

    For the food, I made it so it gets a better score the closer it gets to food but it
    still sometimes thrashes in the spot for the last food. (Maybe my math is a bit off).

    This time I implemented the capsule cause it gives me more points
    The capsule is set at a constant value so when you eat it it increases your score by
    a lot

    """

    newPosition = currentGameState.getPacmanPosition()
    oldFood = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()
    score = 0

    # terminal states, always wants to win
    if currentGameState.isWin():
        return float("inf")
    if currentGameState.isLose():
        return -float("inf")

    # Wants a shorter time
    score += currentGameState.getScore()

    # Wants to eat scared ghosts
    distFromGhost = 1

    for ghost in newGhostStates:
        if ghost.getScaredTimer() != 0:
            distFromGhost = min(distFromGhost, distance.manhattan(newPosition, ghost.getPosition()))

    # wants to eat scared ghosts
    score += 10 / distFromGhost

    # Wants to eat food
    foodList = oldFood.asList()
    foodDist = float("inf")

    for food in foodList:
        foodDist = min(foodDist, distance.manhattan(newPosition, food))
    score += 5 / foodDist

    # capsules should have a high priority
    score -= 50 * len(currentGameState.getCapsules())

    # print("Score: ", score)
    return score

class ContestAgent(MultiAgentSearchAgent):
    """
    Your agent for the mini-contest.

    You can use any method you want and search to any depth you want.
    Just remember that the mini-contest is timed, so you have to trade off speed and computation.

    Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
    just make a beeline straight towards Pacman (or away if they're scared!)

    Method to Implement:

    `pacai.agents.base.BaseAgent.getAction`
    """

    def __init__(self, index, **kwargs):
        super().__init__(index)
