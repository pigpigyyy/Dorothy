local oPacker =
{
	fit = function(self, blocks)
		table.sort(blocks,
			function(a,b)
				return math.max(a.w,a.h) > math.max(b.w,b.h)
			end)
		local len = #blocks
		local w = len > 0 and blocks[1].w or 0
		local h = len > 0 and blocks[1].h or 0
		self.root = { x = 0, y = 0, w = w, h = h }
		for n = 1, len do
			local block = blocks[n]
			local node = self:findNode(self.root, block.w, block.h)
			if node then
				block.fit = self:splitNode(node, block.w, block.h)
			else
				block.fit = self:growNode(block.w, block.h)
			end
		end
	end,

	findNode = function(self, root, w, h)
		if root.used then
			return self:findNode(root.right, w, h) or self:findNode(root.down, w, h)
		elseif w <= root.w and h <= root.h then
			return root
		else
			return nil
		end
	end,

	splitNode = function(self, node, w, h)
		node.used = true
		node.down =
		{
			x = node.x,
			y = node.y + h,
			w = node.w,
			h = node.h - h
		}
		node.right =
		{
			x = node.x + w,
			y = node.y,
			w = node.w - w,
			h = h
		}
		return node
	end,

	growNode = function(self, w, h)
		local canGrowDown = (w <= self.root.w)
		local canGrowRight = (h <= self.root.h)

		local shouldGrowRight = canGrowRight and (self.root.h >= (self.root.w + w)) -- attempt to keep square-ish by growing right when height is much greater than width
		local shouldGrowDown = canGrowDown and (self.root.w >= (self.root.h + h)) -- attempt to keep square-ish by growing down	when width is much greater than height

		if shouldGrowRight then
			return self:growRight(w, h)
		elseif shouldGrowDown then
			return self:growDown(w, h)
		elseif canGrowRight then
			return self:growRight(w, h)
		elseif canGrowDown then
			return self:growDown(w, h)
		else
			return nil -- need to ensure sensible root starting size to avoid this happening
		end
	end,

	growRight = function(self, w, h)
		self.root =
		{
			used = true,
			x = 0,
			y = 0,
			w = self.root.w + w,
			h = self.root.h,
			down = self.root,
			right =
			{
				x = self.root.w,
				y = 0,
				w = w,
				h = self.root.h
			}
		}
		local node = self:findNode(self.root, w, h)
		if node then
			return self:splitNode(node, w, h)
		else
			return nil
		end
	end,

	growDown = function(self, w, h)
		self.root =
		{
			used = true,
			x = 0,
			y = 0,
			w = self.root.w,
			h = self.root.h + h,
			down =
			{
				x = 0,
				y = self.root.h,
				w = self.root.w,
				h = h
			},
			right = self.root
		}
		local node = self:findNode(self.root, w, h)
		if node then
			return self:splitNode(node, w, h)
		else
			return nil
		end
	end
}

return oPacker