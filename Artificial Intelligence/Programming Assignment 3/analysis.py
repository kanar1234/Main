"""
Analysis question.
Change these default values to obtain the specified policies through value iteration.
If any question is not possible, return just the constant NOT_POSSIBLE:
```
return NOT_POSSIBLE
```
"""

NOT_POSSIBLE = None

def question2():
    """
    [Enter a description of what you did here.]
    By changing noise to 0.0, I guarantee the action
    it takes to be the action that's going to happen so
    there is no punishment for going right multiple times
    since there's no way you would fall off the bridge
    """

    answerDiscount = 0.9
    answerNoise = 0.0

    return answerDiscount, answerNoise

def question3a():
    """
    [Enter a description of what you did here.]
    Since I want to risk the cliff, I need a lower value for noise.
    Since I want the close exit, I need to make it so that
    the longer you stay alive the more points you lose
    so it doesn't go to the further exit
    """

    answerDiscount = 0.9
    answerNoise = 0.0
    answerLivingReward = -5.0

    return answerDiscount, answerNoise, answerLivingReward

def question3b():
    """
    [Enter a description of what you did here.]
    Need to make the further exit way worse to get to
    by lowering the discount and have a bad living reward.
    We also want to avoid bridges so we need to turn up the noise a bit

    """

    answerDiscount = 0.4
    answerNoise = 0.3
    answerLivingReward = -3.0

    return answerDiscount, answerNoise, answerLivingReward

def question3c():
    """
    [Enter a description of what you did here.]
    Have no noise or negative living reward
    """

    answerDiscount = 0.9
    answerNoise = 0.0
    answerLivingReward = 0.0

    return answerDiscount, answerNoise, answerLivingReward

def question3d():
    """
    [Enter a description of what you did here.]
    Left it as is because there's no living reward
    and has noise
    """

    answerDiscount = 0.9
    answerNoise = 0.2
    answerLivingReward = 0.0

    return answerDiscount, answerNoise, answerLivingReward

def question3e():
    """
    [Enter a description of what you did here.]
    Have a positive living reward so it gets more points just
    being alive
    """

    answerDiscount = 0.9
    answerNoise = 0.2
    answerLivingReward = 1

    return answerDiscount, answerNoise, answerLivingReward

def question6():
    """
    [Enter a description of what you did here.]
    There is no way it would reach the right exit because decreasing
    epsilon makes him go to the best place and not explore new places
    and decreasing epsilon does the opposite but the odds of it finding
    the best path is extremely low
    """
    return NOT_POSSIBLE

if __name__ == '__main__':
    questions = [
        question2,
        question3a,
        question3b,
        question3c,
        question3d,
        question3e,
        question6,
    ]

    print('Answers to analysis questions:')
    for question in questions:
        response = question()
        print('    Question %-10s:\t%s' % (question.__name__, str(response)))
