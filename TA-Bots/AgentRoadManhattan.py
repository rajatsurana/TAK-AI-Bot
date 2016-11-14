# Embedded file name: ./AgentRoadManhattan.py
import sys
import pdb
import time
import random
from copy import deepcopy
from collections import deque
from math import exp

class Game():

    class Player:

        def __init__(self, flats, capstones):
            self.flats = flats
            self.capstones = capstones

    def __init__(self, n):
        self.n = n
        self.total_squares = n * n
        self.board = [ [] for i in xrange(self.total_squares) ]
        self.turn = 0
        if n == 5:
            self.max_flats = 21
            self.max_capstones = 1
        elif n == 6:
            self.max_flats = 30
            self.max_capstones = 1
        elif n == 7:
            self.max_flats = 40
            self.max_capstones = 1
        self.max_movable = n
        self.max_down = 1
        self.max_up = n
        self.max_left = 'a'
        self.max_right = chr(ord('a') + n - 1)
        self.moves = 0
        self.players = []
        self.players.append(Game.Player(self.max_flats, self.max_capstones))
        self.players.append(Game.Player(self.max_flats, self.max_capstones))
        self.all_squares = [ self.square_to_string(i) for i in xrange(self.total_squares) ]

    def square_to_num(self, square_string):
        """ Return -1 if square_string is invalid
        """
        if len(square_string) != 2:
            return -1
        if not square_string[0].isalpha() or not square_string[0].islower() or not square_string[1].isdigit():
            return -1
        row = ord(square_string[0]) - 96
        col = int(square_string[1])
        if row < 1 or row > self.n or col < 1 or col > self.n:
            return -1
        return self.n * (col - 1) + (row - 1)

    def square_to_string(self, square):
        """Convert square number to string
        """
        if square < 0 or square >= self.total_squares:
            return ''
        row = square % self.n
        col = square / self.n
        return chr(row + 97) + str(col + 1)

    def execute_move(self, move_string):
        """Execute move
        """
        if self.turn == 0:
            self.moves += 1
        if self.moves != 1:
            current_piece = self.turn
        else:
            current_piece = 1 - self.turn
        if move_string[0].isalpha():
            square = self.square_to_num(move_string[1:])
            if move_string[0] == 'F' or move_string[0] == 'S':
                self.board[square].append((current_piece, move_string[0]))
                self.players[current_piece].flats -= 1
            elif move_string[0] == 'C':
                self.board[square].append((current_piece, move_string[0]))
                self.players[current_piece].capstones -= 1
        elif move_string[0].isdigit():
            count = int(move_string[0])
            square = self.square_to_num(move_string[1:3])
            direction = move_string[3]
            if direction == '+':
                change = self.n
            elif direction == '-':
                change = -self.n
            elif direction == '>':
                change = 1
            elif direction == '<':
                change = -1
            prev_square = square
            for i in xrange(4, len(move_string)):
                next_count = int(move_string[i])
                next_square = prev_square + change
                if len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S':
                    self.board[next_square][-1] = (self.board[next_square][-1][0], 'F')
                if next_count - count == 0:
                    self.board[next_square] += self.board[square][-count:]
                else:
                    self.board[next_square] += self.board[square][-count:-count + next_count]
                prev_square = next_square
                count -= next_count

            count = int(move_string[0])
            self.board[square] = self.board[square][:-count]
        self.turn = 1 - self.turn

    def partition(self, n):
        """Generates all permutations of all partitions
        of n
        """
        part_list = []
        part_list.append([n])
        for x in xrange(1, n):
            for y in self.partition(n - x):
                part_list.append([x] + y)

        return part_list

    def check_valid(self, square, direction, partition):
        """For given movement (partition), check if stack on
        square can be moved in direction. Assumes active player
        is topmost color
        """
        if direction == '+':
            change = self.n
        elif direction == '-':
            change = -self.n
        elif direction == '>':
            change = 1
        elif direction == '<':
            change = -1
        for i in xrange(len(partition)):
            next_square = square + change * (i + 1)
            if len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'C':
                return False
            if len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and i != len(partition) - 1:
                return False
            if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and partition[i] > 1:
                return False
            if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and self.board[square][-1][1] != 'C':
                return False

        return True

    def generate_stack_moves(self, square):
        """Generate stack moves from square
        Assumes active player is topmost color
        """
        all_moves = []
        r = square % self.n
        c = square / self.n
        size = len(self.board[square])
        dirs = ['+',
         '-',
         '<',
         '>']
        up = self.n - 1 - c
        down = c
        right = self.n - 1 - r
        left = r
        rem_squares = [up,
         down,
         left,
         right]
        for num in xrange(min(size, self.n)):
            part_list = self.partition(num + 1)
            for di in range(4):
                part_dir = [ part for part in part_list if len(part) <= rem_squares[di] ]
                for part in part_dir:
                    if self.check_valid(square, dirs[di], part):
                        part_string = ''.join([ str(i) for i in part ])
                        all_moves.append(str(sum(part)) + self.all_squares[square] + dirs[di] + part_string)

        return all_moves

    def generate_all_moves(self, player):
        """Generate all possible moves for player
        Returns a list of move strings
        """
        all_moves = []
        for i in xrange(len(self.board)):
            if len(self.board[i]) == 0:
                if self.players[player].flats > 0:
                    all_moves.append('F' + self.all_squares[i])
                if self.moves != player and self.players[player].flats > 0:
                    all_moves.append('S' + self.all_squares[i])
                if self.moves != player and self.players[player].capstones > 0:
                    all_moves.append('C' + self.all_squares[i])

        for i in xrange(len(self.board)):
            if len(self.board[i]) > 0 and self.board[i][-1][0] == player and self.moves != player:
                all_moves += self.generate_stack_moves(i)

        return all_moves


class Agent():

    def __init__(self):
        data = sys.stdin.readline().strip().split()
        self.player = int(data[0]) - 1
        self.n = int(data[1])
        self.time_left = int(data[2])
        self.game = Game(self.n)
        self.max_depth = 1
        self.play()

    def getNeighbors(self, square):
        total_squares = self.n * self.n
        if square < 0 or square >= total_squares:
            return []
        elif square == 0:
            return [square + 1, square + self.n]
        elif square == self.n - 1:
            return [square - 1, square + self.n]
        elif square == total_squares - self.n:
            return [square + 1, square - self.n]
        elif square == total_squares - 1:
            return [square - 1, square - self.n]
        elif square < self.n:
            return [square - 1, square + 1, square + self.n]
        elif square % self.n == 0:
            return [square + 1, square - self.n, square + self.n]
        elif (square + 1) % self.n == 0:
            return [square - 1, square - self.n, square + self.n]
        elif square >= total_squares - self.n:
            return [square - 1, square + 1, square - self.n]
        else:
            return [square - 1,
             square + 1,
             square - self.n,
             square + self.n]

    def score_combination(self, bfs, dfs):
        if dfs == -1:
            return 0
        else:
            return self.n * self.n * exp(-0.5 * (bfs + dfs))

    def road_score(self, player):
        value = 0
        visited = [set(), set()]
        for r in xrange(0, self.n / 2):
            for c in xrange(0, self.n):
                idx = r * self.n + c
                if len(self.game.board[idx]) > 0 and self.game.board[idx][-1][0] == player and self.game.board[idx][-1][1] != 'S' and idx not in visited[1]:
                    value = max(value, self.score_combination(self.bfs(idx, '-', player), self.dfs(idx, '+', player, visited[1])))
                idx = c * self.n + r
                if len(self.game.board[idx]) > 0 and self.game.board[idx][-1][0] == player and self.game.board[idx][-1][1] != 'S' and idx not in visited[0]:
                    value = max(value, self.score_combination(self.bfs(idx, '<', player), self.dfs(idx, '>', player, visited[0])))

        return value

    def bfs_ud(self, process_bfs, player, connected):
        ret_value = self.n * self.n
        for source, dst_list in process_bfs:
            reaches_end = False
            fringe = deque()
            fringe.append((source, 0))
            value = self.n
            while len(fringe) > 0:
                node, value = fringe.popleft()
                if value >= self.n:
                    break
                if node // self.n == 0:
                    reaches_end = True
                    break
                nbrs = self.getNeighbors(node)
                for nbr in nbrs:
                    if nbr // self.n > source // self.n:
                        continue
                    if len(self.game.board[nbr]) == 0 or self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr in connected and connected[nbr] != connected[source]:
                        fringe.append((nbr, value + 1))

            if reaches_end:
                value_back = value
                global_min = self.n * self.n
                for dst in dst_list:
                    reaches_end = False
                    fringe = deque()
                    fringe.append((dst, 0))
                    val = self.n * self.n
                    while len(fringe) > 0:
                        node, val = fringe.popleft()
                        if val >= self.n:
                            break
                        if node // self.n == self.n - 1:
                            reaches_end = True
                            break
                        nbrs = self.getNeighbors(node)
                        for nbr in nbrs:
                            if nbr // self.n < source // self.n:
                                continue
                            if len(self.game.board[nbr]) == 0:
                                fringe.append((nbr, val + 1))
                            elif self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr in connected and source in connected and connected[nbr] != connected[source]:
                                fringe.append((nbr, val + 1))

                    if reaches_end:
                        global_min = min(global_min, val)

                ret_value = min(ret_value, global_min + value_back)
            else:
                continue

        return ret_value

    def bfs_lr2(self, process_bfs, player, connected):
        global_min = self.n * self.n
        for source, dst_list in process_bfs:
            v1 = source % self.n
            v2 = self.n * self.n
            for dst in dst_list:
                v2 = min(v2, self.n - 1 - dst % self.n)

            global_min = min(global_min, v1 + v2)

        return global_min

    def bfs_ud2(self, process_bfs, player, connected):
        global_min = self.n * self.n
        for source, dst_list in process_bfs:
            v1 = source // self.n
            v2 = self.n * self.n
            for dst in dst_list:
                v2 = min(v2, self.n - 1 - dst // self.n)

            global_min = min(global_min, v1 + v2)

        return global_min

    def bfs_lr(self, process_bfs, player, connected):
        ret_value = self.n * self.n
        for source, dst_list in process_bfs:
            reaches_end = False
            fringe = deque()
            fringe.append((source, 0))
            value = self.n
            while len(fringe) > 0:
                node, value = fringe.popleft()
                if value >= self.n:
                    break
                if node % self.n == 0:
                    reaches_end = True
                    break
                nbrs = self.getNeighbors(node)
                for nbr in nbrs:
                    if nbr % self.n > source % self.n:
                        continue
                    if len(self.game.board[nbr]) == 0 or self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr in connected and connected[nbr] != connected[source]:
                        fringe.append((nbr, value + 1))

            if reaches_end:
                value_back = value
                global_min = self.n * self.n
                for dst in dst_list:
                    reaches_end = False
                    fringe = deque()
                    fringe.append((dst, 0))
                    val = self.n * self.n
                    while len(fringe) > 0:
                        node, val = fringe.popleft()
                        if val >= self.n:
                            break
                        if (node + 1) % self.n == 0:
                            reaches_end = True
                            break
                        nbrs = self.getNeighbors(node)
                        for nbr in nbrs:
                            if nbr % self.n < source % self.n:
                                continue
                            if len(self.game.board[nbr]) == 0:
                                fringe.append((nbr, val + 1))
                            elif self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr in connected and source in connected and connected[nbr] != connected[source]:
                                fringe.append((nbr, val + 1))

                    if reaches_end:
                        global_min = min(global_min, val)

                ret_value = min(ret_value, global_min + value_back)
            else:
                continue

        return ret_value

    def road_score_lr(self, player):
        connected = {}
        connected_count = 0
        score_lr = self.n * self.n
        process_bfs = []
        for c in xrange(self.n / 2):
            for r in xrange(self.n):
                idx = r * self.n + c
                if len(self.game.board[idx]) > 0 and self.game.board[idx][-1][0] == player and self.game.board[idx][-1][1] != 'S' and idx not in connected:
                    no_children_nodes = []
                    connected_count += 1
                    connected[idx] = connected_count
                    fringe = [idx]
                    while len(fringe) != 0:
                        node = fringe.pop()
                        connected[node] = connected_count
                        nbrs = self.getNeighbors(node)
                        has_children = False
                        for nbr in nbrs:
                            if len(self.game.board[nbr]) > 0 and self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr not in connected:
                                fringe.append(nbr)
                                has_children = True

                        if not has_children:
                            no_children_nodes.append(node)

                    process_bfs.append((idx, deepcopy(no_children_nodes)))

        score_lr = self.bfs_lr2(process_bfs, player, connected)
        return score_lr

    def road_score_ud(self, player):
        connected = {}
        connected_count = 0
        score_ud = self.n * self.n
        process_bfs = []
        for r in xrange(self.n / 2):
            for c in xrange(self.n):
                idx = r * self.n + c
                if len(self.game.board[idx]) > 0 and self.game.board[idx][-1][0] == player and self.game.board[idx][-1][1] != 'S' and idx not in connected:
                    no_children_nodes = []
                    connected_count += 1
                    connected[idx] = connected_count
                    fringe = [idx]
                    while len(fringe) != 0:
                        node = fringe.pop()
                        connected[node] = connected_count
                        nbrs = self.getNeighbors(node)
                        has_children = False
                        for nbr in nbrs:
                            if len(self.game.board[nbr]) > 0 and self.game.board[nbr][-1][0] == player and self.game.board[nbr][-1][1] != 'S' and nbr not in connected:
                                fringe.append(nbr)
                                has_children = True

                        if not has_children:
                            no_children_nodes.append(node)

                    process_bfs.append((idx, deepcopy(no_children_nodes)))

        score_ud = self.bfs_ud2(process_bfs, player, connected)
        return score_ud

    def road_score(self, player):
        score = min(self.road_score_lr(player), self.road_score_ud(player))
        return self.n * self.n * exp(-0.5 * score)

    def evaluation_function(self):
        tiles_owned = [0, 0]
        for idx in xrange(len(self.game.board)):
            if len(self.game.board[idx]) > 0 and self.game.board[idx][-1][1] != 'S':
                tiles_owned[self.game.board[idx][-1][0]] += 1

        flat_comp = tiles_owned[self.player] - tiles_owned[1 - self.player]
        road_score = self.road_score(self.player) - self.road_score(1 - self.player)
        return flat_comp + road_score

    def play(self):
        opponent_move = ''
        while True:
            if self.player == 0:
                move = self.min_max(opponent_move)
                sys.stdout.write(move + '\n')
                sys.stdout.flush()
                opponent_move = sys.stdin.readline().strip()
            else:
                opponent_move = sys.stdin.readline().strip()
                move = self.min_max(opponent_move)
                sys.stdout.write(move + '\n')
                sys.stdout.flush()

    def min_max(self, move):
        if move != '':
            self.game.execute_move(move)
        my_move = self.max_node(float('-inf'), float('inf'), 0)
        self.game.execute_move(my_move)
        return my_move

    def max_node(self, alpha, beta, depth):
        if depth == self.max_depth:
            return self.evaluation_function()
        val = float('-inf')
        store_val = False
        if depth == 0:
            store_val = True
        action = ''
        for move in self.game.generate_all_moves(self.player):
            old_game = deepcopy(self.game)
            self.game.execute_move(move)
            node_val = self.min_node(alpha, beta, depth + 1)
            self.game = old_game
            val = max(node_val, val)
            if store_val and val == node_val:
                action = move
            alpha = max(alpha, val)
            if beta <= alpha:
                break

        if store_val:
            sys.stderr.write('Value: ' + str(val) + '\n')
            return action
        else:
            return val

    def min_node(self, alpha, beta, depth):
        if depth == self.max_depth:
            return self.evaluation_function()
        val = float('inf')
        store_val = False
        if depth == 0:
            store_val = True
        action = ''
        for move in self.game.generate_all_moves(1 - self.player):
            old_game = deepcopy(self.game)
            self.game.execute_move(move)
            node_val = self.max_node(alpha, beta, depth + 1)
            self.game = old_game
            val = min(node_val, val)
            if store_val and val == node_val:
                action = move
            beta = min(beta, val)
            if beta <= alpha:
                break

        if store_val:
            sys.stderr.write('Value: ' + str(val) + '\n')
            return action
        else:
            return val


random_player = Agent()