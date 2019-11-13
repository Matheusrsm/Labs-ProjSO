from .strategy import *

class LRU(Strategy):

  def __init__(self):
    self.frames = []
    self.timer = 0
    
  def put(self, frameId):
    self.timer += 1
    frame = Frame(frameId)
    frame.timer = self.timer
    self.frames.append(frame)

  def evict(self):
    frameIndex = 0
    minimum = self.frames[frameIndex].timer
    for i in range(len(self.frames)):
      timer = self.frames[i].timer
      if timer < minimum:
        frameIndex = i
        minimum = timer

    frame = self.frames[frameIndex]
    self.frames.pop(frameIndex)
    return frame.frameId
  
  def access(self, frameId, isWrite):
    self.timer += 1
    for frame in self.frames:
      if frame.frameId == frameId:
        frame.timer = self.timer
        break