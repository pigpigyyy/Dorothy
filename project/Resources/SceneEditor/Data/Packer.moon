{
	fit: (blocks)=>
		table.sort blocks,(a,b)->
			va = math.max(a.w,a.h)
			vb = math.max(b.w,b.h)
			if va == vb
				a.w*a.h > b.w*b.h
			else
				va > vb
		len = #blocks
		x,y = 0,0
		w = len > 0 and blocks[1].w or 0
		h = len > 0 and blocks[1].h or 0
		@root = {:x, :y, :w, :h}
		for block in *blocks
			with block
				node = @findNode @root,.w,.h
				.fit = if node
					@splitNode node,.w,.h
				else
					@growNode .w,.h

	findNode: (root,w,h)=>
		if root.used
			@findNode(root.right,w,h) or @findNode(root.down,w,h)
		elseif w <= root.w and h <= root.h
			root
		else
			nil

	splitNode: (node,w,h)=>
		node.used = true
		node.down = {
			x: node.x
			y: node.y + h
			w: node.w
			h: node.h - h
		}
		node.right = {
			x: node.x + w
			y: node.y
			w: node.w - w
			h: h
		}
		node

	growNode: (w,h)=>
		canGrowDown = w <= @root.w
		canGrowRight = h <= @root.h
		shouldGrowRight = canGrowRight and (@root.h >= @root.w + w) -- attempt to keep square-ish by growing right when height is much greater than width
		shouldGrowDown = canGrowDown and (@root.w >= @root.h + h) -- attempt to keep square-ish by growing down	when width is much greater than height
		if shouldGrowRight
			@growRight w,h
		elseif shouldGrowDown
			@growDown w,h
		elseif canGrowRight
			@growRight w,h
		elseif canGrowDown
			@growDown w,h
		else
			nil -- need to ensure sensible root starting size to avoid this happening

	growRight: (w,h)=>
		@root = {
			used: true
			x: 0
			y: 0
			w: @root.w + w
			h: @root.h
			down: @root
			right: {
				x: @root.w
				y: 0
				w: w
				h: @root.h
			}
		}
		node = @findNode @root,w,h
		if node
			@splitNode node,w,h
		else
			nil

	growDown: (w,h)=>
		@root = {
			used: true
			x: 0
			y: 0
			w: @root.w
			h: @root.h + h
			down: {
				x: 0
				y: @root.h
				w: @root.w
				h: h
			},
			right: @root
		}
		node = @findNode @root,w,h
		if node
			@splitNode node,w,h
		else
			nil
}
