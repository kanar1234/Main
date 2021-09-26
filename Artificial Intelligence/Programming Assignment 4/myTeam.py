from pacai.util import reflection, counter
from pacai.agents.capture.reflex import ReflexCaptureAgent
from pacai.agents.base import BaseAgent
from pacai.agents.search.multiagent import MultiAgentSearchAgent
from pacai.core.distance import manhattan
from pacai.core.directions import Directions

import random

"""
Useful methods to (maybe) use:
    chooseAction(self, gameState)
    getAction(self, gameState)
    getFood(self, gameState)
    getFoodYouAreDefending(self, gameState)
    getCapsulesYouAreDefending(self, gameState)
    getOpponents(self, gameState)
    getTeam(self, gameState)
    getScore(self, gameState)
    getMazeDistance(self, pos1, pos2)
    getPreviousObservation(self)
    getCurrentObservation
    registerTeam(self, agentsOnTeam)
    observationFunction(self, state)
"""

class AttackerAgent(ReflexCaptureAgent):
    def __init__(self, index, **kwargs):
        super().__init__(index)

    def chooseAction(self, gameState):
        actions = gameState.getLegalActions()
        best_eval = -float('inf')
        best_action = None
        for action in actions:
            if (action == 'Stop') or (action == 'None'):
                continue
            action_eval = self.evalFunc(gameState, action)
            print("action: ", action, " value", action_eval)
            if action_eval > best_eval: 
                best_eval = action_eval
                best_action = action
        print("state: ", self.getSuccessor(gameState, action).getAgentState(self.index).getPosition())
        print("action taken: ", best_action, "| best value: ", best_eval)
        print("----------------------------")
        return best_action

    def evalFunc(self, gameState, action):
        # pac_state = gameState.generateSuccessor(0, action).getAgentPosition(0)
        # pac_state = self.getSuccessor(gameState, action).getAgentPosition(self.index)
        features = self.getFeatures(gameState, action)
        return features * self.getWeights(gameState, action)
    
    def getFeatures(self, gameState, action):
        getEne
        features = counter.Counter()
        successor = self.getSuccessor(gameState, action)
        myState = successor.getAgentState(self.index)
        features['successorScore'] = self.getScore(successor)

        # Compute distance to the nearest food.
        foodList = self.getFood(successor).asList()

        # This should always be True, but better safe than sorry.
        myPos = myState.getPosition()
        if (len(foodList) > 0):
            minDistance = min([self.getMazeDistance(myPos, food) for food in foodList])
            features['distanceToFood'] = minDistance

        minDist = float("inf")
        for capsule in self.getCapsules(successor):
            minDist = min(minDist, manhattan(myPos, capsule))
        
        ghosts = [successor.getAgentState(i) for i in self.getOpponents(successor)]
        closest = float("inf")
        closestg = ghosts[0]
        
        # gets closest ghost
        for g in ghosts:
            dist = manhattan(myPos, g.getPosition())
            if closest > dist:
                closest = dist
                closestg = g
        # print("closest: ",closest)
        if closest < 4:
            if closest == 0:
                closest = 0.1
            if closestg.isBraveGhost():
                features["closestGhost"] = 4 / closest
            else:
                features["closestGhost"] = -4 / closest
        else:
            features["closestGhost"] = 0

        print("ghostMultiplier: ", features["closestGhost"], "closest: ", closest)
        rev = Directions.REVERSE[gameState.getAgentState(self.index).getDirection()]
        if (action == rev):
            features['reverse'] = 1
        
        features['capsule'] = len(self.getCapsules(successor))

        return features

    def getWeights(self, gameState, action):
        return {
            'successorScore': 100,
            'distanceToFood': -1,
            'closestGhost': -200,
            'capsule': -50
            # 'reverse': -2
        }

class DefenderAgent(ReflexCaptureAgent):
    def __init__(self, index, **kwargs):
        super().__init__(index)

    def chooseAction(self, gameState):
        actions = gameState.getLegalActions(self.index)
        best_eval = -float('inf')
        best_action = None
        for action in actions:
            if (action == 'Stop') or (action == 'None'):
                continue
            action_eval = self.evaluationFunction(gameState, action)
            if action_eval > best_eval: 
                best_eval = action_eval
                best_action = action

        return best_action

    def evaluationFunction(self, currentGameState, action):
        # pac_state = gameState.generateSuccessor(0, action).getAgentPosition(0)
        # pac_state = self.getSuccessor(currentGameState, action)
        features = self.getFeatures(currentGameState, action)
        return features * self.getWeights()
    
    def getFeatures(self, gameState, action):
        features = counter.Counter()
        successor = self.getSuccessor(gameState, action)

        myState = successor.getAgentState(self.index)
        myPos = myState.getPosition()

        # Computes whether we're on defense (1) or offense (0).
        features['onDefense'] = 1
        if (myState.isPacman()):
            features['onDefense'] = 0

        # Computes distance to invaders we can see.
        enemies = [successor.getAgentState(i) for i in self.getOpponents(successor)]
        invaders = [a for a in enemies if a.isPacman() and a.getPosition() is not None]
        features['numInvaders'] = len(invaders)

        if (len(invaders) > 0):
            closest_dist = float("inf")
            closest_ghost = None
            for ghost in invaders:
                invader_dist = self.getMazeDistance(myPos, ghost.getPosition())
                if closest_dist > invader_dist : # inf > dist
                    closest_dist = invader_dist
                    closest_ghost = ghost
            features['invaderDistance'] = closest_dist
            features['closestInvader'] = closest_ghost
        else:
            closest_dist = float("inf")
            closest_ghost = None
            for ghost in enemies:
                enemy_dist = self.getMazeDistance(myPos, ghost.getPosition())
                if  closest_dist > enemy_dist:
                    closest_dist = enemy_dist
                    closest_ghost = ghost
            features['enemyDistance'] = closest_dist
            features['closestEnemy'] = closest_ghost

        if (action == Directions.STOP):
            features['stop'] = 1

        rev = Directions.REVERSE[gameState.getAgentState(self.index).getDirection()]
        if (action == rev):
            features['reverse'] = 1

        return features
    
    def getWeights(self):
        return {
            'numInvaders': -1000,
            'onDefense': 100,
            'invaderDistance': -10,
            'enemyDistance': -15,
            'stop': -100,
            'reverse': -2
        }

def createTeam(firstIndex, secondIndex, isRed,
        first = 'pacai.student.myTeam.AttackerAgent',
        second = 'pacai.student.myTeam.DefenderAgent'):
    """
    This function should return a list of two agents that will form the capture team,
    initialized using firstIndex and secondIndex as their agent indexed.
    isRed is True if the red team is being created,
    and will be False if the blue team is being created.
    """

    firstAgent = AttackerAgent
    secondAgent = DefenderAgent

    return [
        firstAgent(firstIndex),
        secondAgent(secondIndex),
    ]

