# this file is used to calculate the appropriate number of steps
# that the motors should rotate for every given position

import math

def getAbsStepsX(x,y,l1,l2):
    alpha = math.atan2(y,x)
    numerator = x**2 + y**2 + l1**2 - l2**2
    denominator = 2 * math.sqrt(x**2 + y**2) * l1
    theta = alpha - math.acos(numerator/denominator)
    thetaDeg = (180 / math.pi) * theta
    stepsTheta = 0.75 * thetaDeg # 0.75 steps / degree
    print(thetaDeg)
    return stepsTheta

def getAbsStepsY(x,y,l1,l2):
    numerator = l1**2 + l2**2 - x**2 - y**2
    denominator = 2 * l1 * l2
    phi = math.pi - math.acos(numerator/denominator)
    phiDeg = (180 / math.pi) * phi
    stepsPhi = 0.75 * phiDeg # 0.75 steps / degree
    print(phiDeg)
    return stepsPhi

def getRelSteps(x, y, prevTheta, prevPhi, l1, l2):
    newTheta = getAbsStepsX(x, y, l1, l2)
    newPhi = getAbsStepsY(x, y, l1, l2)
    stepsX = newTheta - prevTheta
    stepsY = newPhi - prevPhi
    return [stepsX, stepsY]




