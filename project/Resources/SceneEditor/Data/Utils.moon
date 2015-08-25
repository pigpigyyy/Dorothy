Set = (list)-> {item,true for item in *list}

CompareTable = (olds,news)->
	itemsToDel = {}
	itemSet = Set news
	for item in *olds
		if not itemSet[item]
			table.insert itemsToDel,item
	itemsToAdd = {}
	itemSet = Set olds
	for item in *news
		if not itemSet[item]
			table.insert itemsToAdd,item
	return itemsToAdd,itemsToDel

{:Set,:CompareTable}
