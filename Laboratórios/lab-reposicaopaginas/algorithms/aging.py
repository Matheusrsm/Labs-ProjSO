# This is the file where you must implement the Aging algorithm

# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you whish

# NOTE: there may be methods you don't need to modify, you must decide what
# you need...

ALGORITHM_AGING_NBITS = 8
"""How many bits to use for the Aging algorithm"""

class Aging:

  def __init__(self):
    self.pages = []
    self.references = {}

  def put(self, frameId):
    self.pages.append({
        'frameId': frameId,
        'bits': 1 << ALGORITHM_AGING_NBITS
      })

  def evict(self):
    minimum = 1 << (ALGORITHM_AGING_NBITS + 1)
    chosen = None

    for page in self.pages:
      bits = page['bits']
      if bits < minimum:
        minimum = bits
        chosen = page

    if chosen is None:
      return -1

    self.pages.remove(chosen)

    return chosen['frameId']

  def clock(self):
    for page in self.pages:
      bit = 0

      if page['frameId'] in self.references:
        bit = 1

      page['bits'] = (bit << ALGORITHM_AGING_NBITS) + (page['bits'] >> 1)

    self.references = {}

  def access(self, frameId, isWrite):
    self.references[frameId] = 1
