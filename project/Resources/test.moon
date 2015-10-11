Dorothy!

local *
noop = ->
eq = (a,b)-> a == b

fromValue = (val)->
	(onNext)->
		(_)-> onNext val

fromRange = (start,stop,step)->
	(onNext)->
		(_)->
			onEnd = noop
			for i = start, stop, step or 1
				onEnd = onNext i
			onEnd

fromList = (items)->
	(onNext)->
		(_)->
			onEnd = noop
			for item in *items
				onEnd = onNext item
			onEnd

fromTable = (t,noKey)->
	(onNext)->
		(_)->
			onEnd = noop
			for k,v in pairs t
				if noKey
					onEnd = onNext v
				else
					onEnd = onNext k,v
			onEnd

forEach = (work)->
	(onNext)->
		(values)->
			onEnd = noop
			for value in *values
				onEnd = onNext work value
			onEnd

map = (work)->
	(onNext)->
		(...)-> onNext work ...

reduce = (work)-> 
	(onNext)->
		result = nil
		thisEnd = ->
			(onNext result)!
			result = nil
		(...)->
			if result
				result = work result,...
			else
				result = ...
			thisEnd

filter = (cond)->
	(onNext)->
		(...)->
			onEnd = noop
			if cond ...
				onEnd = onNext ...
			onEnd

reject = (cond)->
	(onNext)->
		(...)->
			onEnd = noop
			if not cond ...
				onEnd = onNext ...
			onEnd

changes = (cmp)->
	(onNext)->
		onEnd = noop
		currentValue = nil
		thisEnd = ()->
			onEnd!
			onEnd = noop
			currentValue = nil
		cmp or= eq
		(value,...)->
			if not currentValue or not cmp currentValue,value,...
				currentValue = value
				onEnd = onNext value,...
			thisEnd

concat = (observer,...)->
	others = {...}
	(onNext)->
		onEnd = noop
		thisEnd = ->
			if not observer
				onEnd!
				onEnd = noop
			else
				nextObserver = stream { concat unpack others }
				observerNext = (...)->
					onEnd = onNext ...
					->
						nextObserver\remove observerNext
						observer\remove nextObserver
						onEnd!
						onEnd = noop
				nextObserver\add observerNext
				observer\add nextObserver
		(...)->
			onEnd = onNext ...
			thisEnd

merge = (...)->
	observers = {...}
	(onNext)->
		onEnd = noop
		count = 0
		total = #observers+1
		taskEnd = ()->
			count += 1
			if count == total
				onEnd!
				onEnd = noop
				count = 0
		taskNext = (...)->
			onEnd = onNext ...
			taskEnd
		for observer in *observers do observer\add taskNext
		(...)->
			onEnd = onNext ...
			taskEnd

distinct = ()->
	(onNext)->
		items = {}
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			items = {}
		(value,...)->
			if not items[value]
				items[value] = true
				onEnd = onNext value,...
			thisEnd

find = (cond)->
	(onNext)->
		find = false
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			find = false
		(...)->
			if not find and cond ...
				find = true
				onEnd = onNext ...
			thisEnd

first = ()->
	(onNext)->
		get = false
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			get = false
		(...)->
			if not get
				get = true
				onEnd = onNext ...
			thisEnd

flatten = ()->
	(onNext)->
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
		taskNext = (...)->
			onEnd = onNext ...
			noop
		(observer)->
			observer\add taskNext
			observer!!
			thisEnd

last = ()->
	(onNext)->
		lastValue = nil
		thisEnd = ->
			(onNext unpack lastValue)!
			lastValue = nil
		(...)->
			lastValue = {...}
			thisEnd

max = ()->
	reduce math.max

min = ()->
	reduce math.min

pack = ()->
	map (...)-> {...}

upack = ()->
	map (t)-> unpack t

wrap = (size)->
	(onNext)->
		buffer = {}
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			buffer = {}
		(value)->
			table.insert buffer,value
			if #buffer >= size
				onEnd = onNext unpack buffer
				buffer = {}
			thisEnd

unwrap = ()->
	(onNext)->
		(...)->
			onEnd = noop
			items = {...}
			for item in *items
				onEnd = onNext item
			onEnd

partition = (cond,routeA,routeB)->
	(onNext)->
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
		routeNext = (...)->
			onEnd = onNext ...
			noop
		routeA\add routeNext
		routeB\add routeNext
		(...)->
			if cond ...
				routeA ...
			else
				routeB ...
			thisEnd

pluck = (...)->
	keys = {...}
	(onNext)->
		(value)->
			onEnd = noop
			for key in *keys
				onEnd = onNext value[key]
			onEnd

skip = (num)->
	num or= 1
	(onNext)->
		count = 0
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			count = 0
		(...)->
			count += 1
			if count > num
				onEnd = onNext ...
			thisEnd

skipUntil = (observer)->
	(onNext)->
		triggered = false
		onEnd = noop
		observerNext = (value)->
			triggered = true
			noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			triggered = false
		observer\add observerNext
		(...)->
			if triggered
				onEnd = onNext ...
			thisEnd

takeUntil = (observer)->
	(onNext)->
		triggered = false
		onEnd = noop
		observerNext = (value)->
			triggered = true
			noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			triggered = false
		observer\add observerNext
		(...)->
			if not triggered
				onEnd = onNext ...
			thisEnd

skipWhile = (cond)->
	(onNext)->
		skipping = true
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			skipping = true
		(...)->
			if skipping
				skipping = cond ...
			if not skipping
				onEnd = onNext ...
			thisEnd

takeWhile = (cond)->
	(onNext)->
		taking = true
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			taking = true
		(...)->
			if taking
				taking = cond ...
				onEnd = onNext ...
			thisEnd

take = (num)->
	num or= 1
	(onNext)->
		count = 0
		onEnd = noop
		thisEnd = ()->
			onEnd!
			onEnd = noop
			count = 0
		(...)->
			count += 1
			if count <= num
				onEnd = onNext ...
			thisEnd

streamFuncs = (tasks)->
	(onNext)->
		last = table.remove tasks
		last = last onNext
		while #tasks > 0
			cur = table.remove tasks
			cur = cur last
			last = cur
		last

streamDef = 
	__call:(...)=>
		@[1] ...
	__index:(key)=>
		streamDef[key]
	add:(item)=>
		table.insert @,item
	remove:(item)=>
		for i = 1,#@
			if @[i] == item
				table.remove @,i
				break

stream = (tasks)->
	last = table.remove tasks
	last = last (...)->
		onEnds = [(tasks[i] ...) for i = 2,#tasks]
		-> for onEnd in *onEnds do onEnd!
	while #tasks > 0
		cur = table.remove tasks
		cur = cur last
		last = cur
	tasks[1] = last
	setmetatable tasks,streamDef
	tasks

subject = (tasks)->
	observer = stream tasks
	(...)-> (observer ...)!

run = (observer)-> thread -> observer!!

s1 = stream {
	fromRange 2,4
	map (x)-> x/2
	reduce (last,x)-> last+x
	map (x)->
		print "s1",x
		x
}
s2 = stream {
	fromRange 100,200
	map (x)-> x-100
	reduce (last,x)-> last-x
	map (x)->
		print "s2",x
		x
}

s = stream {
	reduce (last,x)-> last+x
	--first!
	--find (x)-> x > 4
	--map (x)-> x * 2
	--filter (x)-> x < 10
	concat s1, s2
		--, (last,x)-> last + x
	--reduce (last, x)-> last + x
	--map (x)-> fromValue x+998
	--flatten!
	partition (x)-> x > 0,
		stream {
			--take!
			map (x)->
				print "pos",x
				x
		},
		stream {
			map (x)->
				print "neg",x
				x
		}
}

thread ->
	thread ->
		s1!!
	thread ->
		s2!!
	thread ->
		s1!!
	thread ->
		s2!!

	s\add stream {
		reduce (last,x)-> last+x
		map (x)->
			print "sum",x
			x
	}
	s\add stream {
		max!
		map (x)->
			print "maxValue",x
			x
	}
	s\add stream {
		min!
		map (x)->
			print "minValue",x
			x
	}
	onEnd = nil
	for i = 1,10
		onEnd = s i
	onEnd!

	sleep 1
	thread ->
		s1!!
	thread ->
		s2!!

	print "\nagain\n"
	onEnd = nil
	for i = 10,20
		onEnd = s i
	onEnd!

	f = subject {
		map (x)->
			print x
			x
	}

	for i = 1,10
		f i

