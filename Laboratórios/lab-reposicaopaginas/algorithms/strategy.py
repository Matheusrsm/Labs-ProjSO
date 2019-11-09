class Strategy(object):
  def __init__(self):
    pass

  def put(self, frameId):
    pass

  def evict(self):
    pass

  def clock(self):
    pass

  def access(self, frameId, isWrite):
    pass


class Frame:
  
  def __init__(self, frameId):
    self.frameId = frameId
