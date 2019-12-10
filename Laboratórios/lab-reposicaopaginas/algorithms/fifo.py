# This is the file where you must implement the FIFO algorithm
# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you wish
# NOTE: there may be methods you don't need to modify, you must decide what
# you need...

from queue import Queue

class FIFO:

  def __init__(self):
    self.queue = Queue()

  def put(self, frameId):
    self.queue.put(frameId)

  def evict(self):
    return self.queue.get()

  def clock(self):
    pass

  def access(self, frameId, isWrite):
    pass
