from .fifo import FIFO
from .strategy import *

class SecondChance(FIFO):

  def __init__(self):
    super(SecondChance, self).__init__()

  def put(self, frameId, bit=0):
    frame = Frame(frameId)
    frame.bit = bit
    super(SecondChance, self).put(frame)

  def evict(self):
    while self.queue:
        frame = super(SecondChance, self).evict()
        if frame.bit == 1:
            self.put(frame.frameId)
        else:
            return frame.frameId
          
  def access(self, frameId, isWrite):
    for frame in self.queue:
        if frame.frameId == frameId:
            frame.bit = 1
            break
