class SecondChance:

  def __init__(self):
    self.pages = []
    self.current = 0
    pass

  def put(self, frameId):
    self.pages.append({
        'frameId': frameId,
        'access': 0 
        })
    pass

  def evict(self):
    while True:
      page = self.pages[self.current]
      if (page['access'] == 1):
        page['access'] = 0
        self.current = (self.current + 1) % len(self.pages)
      else:
        return self.pages.pop(self.current)['frameId']
    pass

  def clock(self):
    pass

  def access(self, frameId, isWrite):
    for page in self.pages:
      if page['frameId'] == frameId:
        page['access'] = 1
        break
    pass
