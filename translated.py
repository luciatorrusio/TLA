class defaultlist(list):

    def __init__(self,defData):
        self.defData = defData

    def _getDefault(self):
        if isinstance(self.defData,type):
            return self.defData()
        return self.defData

    def __getitem__(self,index):
        if index >= len(self):
            return self._getDefault()
        return super.__getitem__(index)

    def __setitem__(self,index,value):
        while index>=len(self):
            self.append(self._getDefault())
        list.__setitem__(self,index,value)

def main():
	i = 0
	arr = defaultlist(0)
	i = 0
	while(int( i <= 10 )):
		arr[i] = pow(2, i)
		i += 1

	print(arr)
	return 0

main()
