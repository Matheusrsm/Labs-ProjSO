from .strategy import *

class FIFO(Strategy):
  
  def __init__(self):
    self.queue = []

  def put(self, frameId):
    self.queue.append(frameId)

  def evict(self):
    return self.queue.pop(0)

  def clock(self):
    pass

  def access(self, frameId, isWrite):
    pass
