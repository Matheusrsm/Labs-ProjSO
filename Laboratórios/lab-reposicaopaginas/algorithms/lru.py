# This is the file where you must implement the LRU algorithm

# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you wish

# NOTE: there may be methods you don't need to modify, you must decide what
# you need...

class LRU:

  def __init__(self):
    self.frames = []

  def put(self, frame_id):
    self.frames.append(frame_id)

  def evict(self):
    return self.frames.pop(0)

  def clock(self):
    pass

  def access(self, frame_id, is_write):
    for i in range(len(self.frames)):
      if self.frames[i] == frame_id:
        self.frames.pop(i)
        self.frames.append(frame_id)
        break
