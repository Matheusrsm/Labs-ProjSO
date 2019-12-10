# This is the file where you must implement the NRU algorithm

# This file will be imported from the main code. The PhysicalMemory class
# will be instantiated with the algorithm received from the input. You may edit
# this file as you wish

# NOTE: there may be methods you don't need to modify, you must decide what
# you need...

from random import randint

def calculateClass(page):
    if page['r'] and page['m']:
        return 3
    elif page['r'] and not page['m']:
        return 2
    elif not page['r'] and page['m']:
        return 1
    else:
        return 0

def getClass(page):
    return page['class']

class NRU:
    def __init__(self):
        self.pages = []
        pass

    def put(self, frameId):
        self.pages.append({
            'frameId': frameId,
            'r': False,
            'm': False,
            'class': 0
            })
        pass

    def evict(self):
        minClass = min(*self.pages, key=getClass)['class']
        filteredPages = [page for page in self.pages if page['class'] == minClass]
        ri = randint(0, len(filteredPages) - 1)
        page = filteredPages[ri]
        pagesIndex = self.pages.index(page)
        return self.pages.pop(pagesIndex)['frameId']

    def clock(self):
        for page in self.pages:
            page['r'] = False
            page['class'] = calculateClass(page)

    def access(self, frameId, isWrite):
        for page in self.pages:
            if page['frameId'] == frameId:
                page['m'] = isWrite
                page['r'] = not isWrite
                page['class'] = calculateClass(page)
