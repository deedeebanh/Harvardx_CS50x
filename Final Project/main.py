import pygame
import sys
from pygame.locals import *

BLACK = (0, 0, 0)
IVORY = (255, 235, 215)
GREEN = (46, 139, 87)

DISPLAY_WIDTH = 600
DISPLAY_HEIGHT = 600

FPS = 60

RESERVED = 0

BOX = int(DISPLAY_HEIGHT / 8)
PAD = 5

# Initialize the pygame library
pygame.init()
# Set up the drawing Display
screen = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
screen_rect = screen.get_rect()
# Title and Icon
pygame.display.set_caption('Checkers')
icon = pygame.image.load('icon.png')
pygame.display.set_icon(icon)
legalPos = []
illegalPos = []


def drawCheckersBoard():
    for row in range(8):
        for col in range(8):
            if (col + row) % 2:
                color = GREEN
                legalPos.append([col, row])
            else:
                color = IVORY
                illegalPos.append([col, row])
            pygame.draw.rect(screen, color, [col * BOX + RESERVED, row * BOX, BOX, BOX])


positions = []
for r in range(8):
    for c in range(8):
        if (c + r) % 2:
            if r < 3:
                positions.append([c, r, 'pawn1'])
            elif r > 4:
                positions.append([c, r, 'pawn2'])


def isLegalPosition(eventPos):
    for i, p in enumerate(legalPos):
        if (p[0] <= eventPos[0] / BOX <= p[0] + 1) and (p[1] <= eventPos[1] / BOX <= p[1] + 1):
            return [True, p]
    for i, p in enumerate(illegalPos):
        if (p[0] <= eventPos[0] / BOX <= p[0] + 1) and (p[1] <= eventPos[1] / BOX <= p[1] + 1):
            return [False, None, None]


def drawCheckerPieces():
    for i, p in enumerate(positions):
        pixelPosition = (p[0] * BOX + RESERVED + PAD, p[1] * BOX + PAD)
        if p[2] == 'pawn1':
            screen.blit(pygame.image.load('brown.png'), pixelPosition)
        elif p[2] == 'king1':
            screen.blit(pygame.image.load('brownKing.png'), pixelPosition)
        elif p[2] == 'pawn2':
            screen.blit(pygame.image.load('blue.png'), pixelPosition)
        elif p[2] == 'king2':
            screen.blit(pygame.image.load('blueKing.png'), pixelPosition)


def isVacantPosition(newPos):
    for i, p in enumerate(positions):
        if i != curID:
            if newPos[0] == p[0] and newPos[1] == p[1]:
                return False
            else:
                return True


def isLegalMove(ptA, ptB):
    ptAx, ptAy = ptA[0], ptA[1]
    ptBx, ptBy = ptB[0], ptB[1]
    delCol = ptBx - ptAx
    delRow = ptBy - ptAy
    # Check if the new position is within bound
    if 0 <= ptBx < 8 and 0 <= ptBy < 8:
        # Check if is moving one square diagonally
        # if Pawn, can only move forward on the board
        # if King, can move forward and backward on the board
        if abs(delRow) == 1 and abs(delCol) == 1:
            if (ptA[2] == 'pawn1' and delRow > 0) or (ptA[2] == 'king1'):
                return True
            elif (ptA[2] == 'pawn2' and delRow < 0) or (ptA[2] == 'king2'):
                return True
        # If is moving two squares diagonally
        elif abs(delRow) == 2 and abs(delCol) == 2:
            # Check if there's an enemy to capture
            midWayStat = None
            selected = None
            midWayX, midWayY = int(ptAx + delCol / 2), int(ptAy + delRow / 2)
            for i, p in enumerate(positions):
                if p[0] == midWayX and p[1] == midWayY:
                    selected = i
                    midWayStat = p[2]
            # If there's an enemy to capture, proceed to move
            # If Pawn, can only move forward on the board
            # If King, can move forward and backward on the board
            # capture the enemy by moving the positions out of board
            if midWayStat is not None and (
                    (ptA[2] == 'pawn1' and delRow > 0) and (midWayStat == 'pawn2' or midWayStat == 'king2')) or (
                    (ptA[2] == 'pawn2' and delRow < 0) and (midWayStat == 'pawn1' or midWayStat == 'king1')) or (
                    (ptA[2] == 'king1') and (midWayStat == 'pawn2' or midWayStat == 'king2')) or (
                    (ptA[2] == 'king2') and (midWayStat == 'pawn1' or midWayStat == 'king1')):
                positions[selected][0] = 2000
                positions[selected][1] = 2000
                return True
            else:
                return False
        # Return false is moving more than two squares
        else:
            return False
    # Return false if out of bound
    else:
        return False


clock = pygame.time.Clock()
curID = None
pointA = None
pointB = None
deltaX = None
deltaY = None
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                for i, p in enumerate(positions):
                    if (p[0] <= event.pos[0] / BOX <= p[0] + 1) and (p[1] <= event.pos[1] / BOX <= p[1] + 1):
                        pointA = p.copy()
                        curID = i
                        deltaX = positions[curID][0] - event.pos[0] / BOX
                        deltaY = positions[curID][1] - event.pos[1] / BOX
        elif event.type == pygame.MOUSEMOTION:
            if curID is not None:
                positions[curID][0] = event.pos[0] / BOX + deltaX
                positions[curID][1] = event.pos[1] / BOX + deltaY
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:
                if curID is not None:
                    # check if the square is diagonal to the current position (i.e. legal position)
                    isLegalPos = isLegalPosition(event.pos)
                    if isLegalPos[0]:
                        # check if the square is vacant
                        isVacant = isVacantPosition(isLegalPos[1])
                        if isVacant:
                            pointB = isLegalPos[1]
                            # Go to isLegalMove logic and check if this is a legal move
                            isMoving = isLegalMove(pointA, pointB)
                            if isMoving:
                                # If True, proceed to move the checkers piece and update positions
                                positions[curID][0] = pointB[0]
                                positions[curID][1] = pointB[1]
                                # If pawns reach the end of board, make them into kings
                                # otherwise, keep as pawns
                                if pointA[2] == 'pawn1' and pointB[1] == 7:
                                    positions[curID][2] = 'king1'
                                elif pointA[2] == 'pawn2' and pointB[1] == 0:
                                    positions[curID][2] = 'king2'
                                else:
                                    positions[curID][2] = pointA[2]
                            else:
                                positions[curID] = pointA
                        else:
                            positions[curID] = pointA
                    else:
                        positions[curID] = pointA
                    curID = None

    screen.fill(BLACK)

    # draw checker board:
    drawCheckersBoard()

    # draw checker pieces:

    drawCheckerPieces()

    # update display

    pygame.display.update()

    # --- FPS ---

    clock.tick(FPS)

    # --- the end ---
