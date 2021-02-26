import random

# ==== Helper Classes ====
class Rect: # used for the tunneling algorithm
	def __init__(self, x, y, w, h):
		self.x1 = x
		self.y1 = y
		self.x2 = x+w
		self.y2 = y+h

	def center(self):
		centerX = int((self.x1 + self.x2)/2)
		centerY = int((self.y1 + self.y2)/2)
		return (centerX, centerY)

	def intersect(self, other):
		#returns true if this rectangle intersects with another one
		return (self.x1 <= other.x2 and self.x2 >= other.x1 and
			self.y1 <= other.y2 and self.y2 >= other.y1)

class TunnelingAlgorithm:
    '''
    This version of the tunneling algorithm is essentially
    identical to the tunneling algorithm in the Complete Roguelike
    Tutorial using Python, which can be found at
    http://www.roguebasin.com/index.php?title=Complete_Roguelike_Tutorial,_using_python%2Blibtcod,_part_1

    Requires random.randint() and the Rect class defined below.
    '''

    def __init__(self):
        self.level = []
        self.ROOM_MAX_SIZE = 12
        self.ROOM_MIN_SIZE = 4
        self.MAX_ROOMS = 1000

    # TODO: raise an error if any necessary classes are missing

    def generateLevel(self, mapWidth, mapHeight):
        # Creates an empty 2D array or clears existing array
        self.level = [[1
                       for y in range(mapHeight)]
                      for x in range(mapWidth)]

        rooms = []
        num_rooms = 0

        for r in range(self.MAX_ROOMS):
            # random width and height
            w = random.randint(self.ROOM_MIN_SIZE, self.ROOM_MAX_SIZE)
            h = random.randint(self.ROOM_MIN_SIZE, self.ROOM_MAX_SIZE)
            # random position within map boundries
            x = random.randint(0, mapWidth - w - 1)
            y = random.randint(0, mapHeight - h - 1)

            new_room = Rect(x, y, w, h)
            # check for overlap with previous rooms
            failed = False
            for other_room in rooms:
                if new_room.intersect(other_room):
                    failed = True
                    continue

            if not failed:
                self.createRoom(new_room)
                (new_x, new_y) = new_room.center()

                if num_rooms != 0:
                    # all rooms after the first one
                    # connect to the previous room

                    # center coordinates of the previous room
                    (prev_x, prev_y) = rooms[num_rooms - 1].center()

                    # 50% chance that a tunnel will start horizontally
                    if random.randint(0, 1) == 1:
                        self.createHorTunnel(prev_x, new_x, prev_y)
                        self.createVirTunnel(prev_y, new_y, new_x)

                    else:  # else it starts virtically
                        self.createVirTunnel(prev_y, new_y, prev_x)
                        self.createHorTunnel(prev_x, new_x, new_y)

                # append the new room to the list
                rooms.append(new_room)
                num_rooms += 1

        return self.level

    def createRoom(self, room):
        # set all tiles within a rectangle to 0
        for x in range(room.x1 + 1, room.x2):
            for y in range(room.y1 + 1, room.y2):
                self.level[x][y] = 0

    def createHorTunnel(self, x1, x2, y):
        for x in range(min(x1, x2), max(x1, x2) + 1):
            self.level[x][y] = 0

    def createVirTunnel(self, y1, y2, x):
        for y in range(min(y1, y2), max(y1, y2) + 1):
            self.level[x][y] = 0


if __name__ == '__main__':
    ta = TunnelingAlgorithm()
    level = ta.generateLevel(32, 32)
    mas = ['.', '#']
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
    f = open('template1_cpp/level_tunnel.txt', 'w')
    for k in level:
        f.write(''.join(k)+'\n')
        print(k)
    f.close()
    #print(level)