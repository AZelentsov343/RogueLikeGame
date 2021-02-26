import random

class DrunkardsWalk:
    def __init__(self):
        self.level = []
        self._percentGoal = .6
        self.walkIterations = 25000  # cut off in case _percentGoal in never reached
        self.weightedTowardCenter = 0.15
        self.weightedTowardPreviousDirection = 0.7

    def generateLevel(self, mapWidth, mapHeight):
        # Creates an empty 2D array or clears existing array
        self.walkIterations = max(self.walkIterations, (mapWidth * mapHeight * 10))
        self.level = [[1
                       for y in range(mapHeight)]
                      for x in range(mapWidth)]

        self._filled = 0
        self._previousDirection = None

        self.drunkardX = random.randint(2, mapWidth - 2)
        self.drunkardY = random.randint(2, mapHeight - 2)
        self.filledGoal = mapWidth * mapHeight * self._percentGoal

        for i in range(self.walkIterations):
            self.walk(mapWidth, mapHeight)
            if (self._filled >= self.filledGoal):
                break

        return self.level

    def walk(self, mapWidth, mapHeight):
        # ==== Choose Direction ====
        north = 1.0
        south = 1.0
        east = 1.0
        west = 1.0

        # weight the random walk against edges
        if self.drunkardX < mapWidth * 0.25:  # drunkard is at far left side of map
            east += self.weightedTowardCenter
        elif self.drunkardX > mapWidth * 0.75:  # drunkard is at far right side of map
            west += self.weightedTowardCenter
        if self.drunkardY < mapHeight * 0.25:  # drunkard is at the top of the map
            south += self.weightedTowardCenter
        elif self.drunkardY > mapHeight * 0.75:  # drunkard is at the bottom of the map
            north += self.weightedTowardCenter

        # weight the random walk in favor of the previous direction
        if self._previousDirection == "north":
            north += self.weightedTowardPreviousDirection
        if self._previousDirection == "south":
            south += self.weightedTowardPreviousDirection
        if self._previousDirection == "east":
            east += self.weightedTowardPreviousDirection
        if self._previousDirection == "west":
            west += self.weightedTowardPreviousDirection

        # normalize probabilities so they form a range from 0 to 1
        total = north + south + east + west

        north /= total
        south /= total
        east /= total
        west /= total

        # choose the direction
        choice = random.random()
        if 0 <= choice < north:
            dx = 0
            dy = -1
            direction = "north"
        elif north <= choice < (north + south):
            dx = 0
            dy = 1
            direction = "south"
        elif (north + south) <= choice < (north + south + east):
            dx = 1
            dy = 0
            direction = "east"
        else:
            dx = -1
            dy = 0
            direction = "west"

        # ==== Walk ====
        # check colision at edges TODO: change so it stops one tile from edge
        if (0 < self.drunkardX + dx < mapWidth - 1) and (0 < self.drunkardY + dy < mapHeight - 1):
            self.drunkardX += dx
            self.drunkardY += dy
            if self.level[self.drunkardX][self.drunkardY] == 1:
                self.level[self.drunkardX][self.drunkardY] = 0
                self._filled += 1
            self._previousDirection = direction


if __name__ == '__main__':
    dw = DrunkardsWalk()
    mas = ['.', '#']
    level = dw.generateLevel(32, 32)
    for i in range(len(level)):
        for j in range(len(level[0])):
            if level[i][j] == 1:
                r = random.random()
                if r > 1.0:
                    level[i][j] = ' '
                else:
                    level[i][j] = '#'
                #level[i][j] = random.choice(['#', ' ']) # prob=[0.7, 0.3])
            else:
                level[i][j] = '.'
    f = open('template1_cpp/level_drunkards.txt', 'w')
    for k in level:
        f.write(''.join(k)+'\n')
        print(k)
    f.close()
    #print(level)