# This is the file where you must implement the Aging algorithm

# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you whish

# NOTE: there may be methods you don't need to modify, you must decide what
# you need...

ALGORITHM_AGING_NBITS = 8
from .strategy import *

class Aging(Strategy):

  def __init__(self):
    self.nbits = ALGORITHM_AGING_NBITS
    self.frames = []
    
  def put(self, frameId):
    frame = Frame(frameId)
    frame.counter = 1
    self.frames.append(frame)

  def evict(self):
    frameIndex = 0
    minimum = self.frames[frameIndex].counter
    for i in range(len(self.frames)):
      counter = self.frames[i].counter
      if counter < minimum:
        frameIndex = i
        minimum = counter

    frame = self.frames[frameIndex]
    self.frames.pop(frameIndex)
    return frame.frameId    
  
  def access(self, frameId, isWrite):
    for frame in self.frames:
      if frame.frameId == frameId:
        leftbit = 2 ** self.nbits
        frame.counter |= leftbit
        break
 
  def clock(self):
    for frame in self.frames:
      frame.counter >>= 1