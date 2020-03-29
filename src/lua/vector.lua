local Vector = {}

function Vector.Normalize(a, b, c)
	if (c == nil) then
		local magnitude = math.sqrt((a * a) + (b * b))
		return a / magnitude, b / magnitude
	else
		local magnitude = math.sqrt((a * a) + (b * b) + (c * c))
		return a / magnitude, b / magnitude, c / magnitude
	end
end

function Vector.Magnitude(a, b, c)
	local magnitude
	if (c == nil) then
		magnitude = math.sqrt((a * a) + (b * b))
	else
		magnitude = math.sqrt((a * a) + (b * b) + (c * c))
	end
	return magnitude
end

return Vector