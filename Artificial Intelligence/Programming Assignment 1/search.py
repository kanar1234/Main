"""
In this file, you will implement generic search algorithms which are called by Pacman agents.
"""
from pacai.util.stack import Stack
from pacai.util.queue import Queue
from pacai.util.priorityQueue import PriorityQueue

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first [p 85].

    Your search algorithm needs to return a list of actions that reaches the goal.
    Make sure to implement a graph search algorithm [Fig. 3.7].

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:
    ```
    print("Start: %s" % (str(problem.startingState())))
    print("Is the start a goal?: %s" % (problem.isGoal(problem.startingState())))
    print("Start's successors: %s" % (problem.successorStates(problem.startingState())))
    ```
    """

    # *** Your Code Here ***

    current = Stack()                                         # creates a stack since dfs is FILO
    visited = []
    # you want to push the position and a list of all previous moves in the stack
    current.push((problem.startingState(), []))
    moves = []
    # checks if there are any items in the stack
    while not current.isEmpty():
        # sets current_position to the start position and moves
        current_position, moves = current.pop()
        # print("Current Position: ", end = "")
        # print(current_position)
        # print("Moves: ", end = "")
        # print(moves)

        # checks if you have visited the current position and visits it if it hasn't been visited
        if current_position not in visited:
            # adds current position to visited
            visited.append(current_position)
            # if your position is the goal, return the moves you have made
            if problem.isGoal(current_position):
                return moves
            # otherwise look at the successors
            successors = problem.successorStates(current_position)
            # print("Successors are: ", end = "")
            # print(successors)
            for suc_position, suc_direction, suc_cost in successors:
                new_moves = moves + [suc_direction]
                # pushes the previous moves and the next position into the stack
                current.push((suc_position, new_moves))
    return moves

# This function works the exact same way as DFS except you store items into a queue instead
# since BFS is a FIFO search algorithm
def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first. [p 81]
    """

    # *** Your Code Here ***

    current = Queue()
    current.push((problem.startingState(), []))
    visited = []
    moves = []
    while not current.isEmpty():
        current_position, moves = current.pop()
        # print("Current Position: ", end = "")
        # print(current_position)
        # print("Moves: ", end = "")
        # print(moves)
        if current_position not in visited:
            visited.append(current_position)
            if problem.isGoal(current_position):
                return moves
            successors = problem.successorStates(current_position)
            for suc_position, suc_direction, suc_cost in successors:
                new_moves = moves + [suc_direction]
                current.push((suc_position, new_moves))
    return moves

def uniformCostSearch(problem):
    """
    Search the node of least total cost first.
    """

    # *** Your Code Here ***

    current = PriorityQueue()
    # Push has 2 arguments for priorityQueue ((position, moves, cost)), cost)
    current.push((problem.startingState(), [], 0), 0)
    visited = []
    moves = []
    while not current.isEmpty():
        # We want to store the previous cost now in addition to the position and moves
        current_position, moves, prev_costs = current.pop()
        # print("Current Position: ", end = "")
        # print(current_position)
        # print("Moves: ", end = "")
        # print(moves)
        # print("Previous costs: ", end = "")
        # print(prev_costs)
        if current_position not in visited:
            visited.append(current_position)
            if problem.isGoal(current_position):
                return moves
            successors = problem.successorStates(current_position)
            for suc_position, suc_direction, suc_cost in successors:
                new_moves = moves + [suc_direction]
                # We want the total cost of all the previous paths now, similar to new_moves
                total_cost = prev_costs + suc_cost
                # pushes the total cost in addition to new_moves
                current.push((suc_position, new_moves, total_cost), total_cost)
    return moves

def aStarSearch(problem, heuristic):
    """
    Search the node that has the lowest combined cost and heuristic first.
    """

    # *** Your Code Here ***
    current = PriorityQueue()
    # Push has 2 arguments for priorityQueue ((position, moves, cost)), cost)
    current.push((problem.startingState(), [], 0), 0)
    visited = []
    moves = []
    while not current.isEmpty():
        # We want to store the previous cost now in addition to the position and moves
        current_position, moves, prev_costs = current.pop()
        # print("Current Position: ", end = "")
        # print(current_position)
        # print("Moves: ", end = "")
        # print(moves)
        # print("Previous costs: ", end = "")
        # print(prev_costs)
        # print("Heuristic: ", end = "")
        # print(heuristic(current_position, problem))
        if current_position not in visited:
            visited.append(current_position)
            if problem.isGoal(current_position):
                return moves
            successors = problem.successorStates(current_position)
            for suc_position, suc_direction, suc_cost in successors:
                new_moves = moves + [suc_direction]
                # We want the total cost of all the previous paths now, similar to new_moves
                total_cost = prev_costs + suc_cost
                # Heuristic = total cost + heuristic cost
                heuristic_cost = total_cost + heuristic(suc_position, problem)
                # pushes the heuristic in addition to new_moves
                current.push((suc_position, new_moves, total_cost), heuristic_cost)
    return moves
