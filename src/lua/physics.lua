-- Yenah:physics.lua
local ffi = require 'ffi'
cp = ffi.load("chipmunk")
ffi.cdef[[
	void free(void *ptr);

	typedef double cpFloat;
	typedef unsigned char cpBool;
	typedef struct cpVect{cpFloat x,y;} cpVect;

	typedef void cpSpace;
	typedef void cpBody;
	typedef void cpShape;
	typedef void cpCircleShape;

	cpSpace *cpSpaceNew();
	void     cpSpaceFree(cpSpace *space);

	void     cpSpaceStep(cpSpace *space, cpFloat dt);
	cpBody * cpSpaceAddBody(cpSpace *space, cpBody *body);
	void     cpSpaceRemoveBody(cpSpace *space, cpBody *body);
	cpShape *cpSpaceAddShape(cpSpace *space, cpShape *shape);
	void     cpSpaceRemoveShape(cpSpace *space, cpShape *shape);

	cpVect   cpSpaceGetGravity(const cpSpace *space);
	void     cpSpaceSetGravity(cpSpace *space, cpVect value);

	cpFloat  cpSpaceGetDamping(const cpSpace *space);
	void     cpSpaceSetDamping(cpSpace *space, cpFloat value);

	cpBody * cpBodyNew(cpFloat m, cpFloat i);
	cpBody * cpBodyNewStatic();
	cpBody * cpBodyNewKinematic();
	void     cpBodyFree(cpBody *body);

	cpVect   cpBodyGetPosition(const cpBody *body);
	void     cpBodySetPosition(cpBody *body, cpVect pos);
	cpFloat  cpBodyGetAngle(const cpBody *body);
	void     cpBodySetAngle(cpBody *body, cpFloat angle);
	cpFloat  cpBodyGetTorque(const cpBody *body);
	void     cpBodySetTorque(cpBody *body, cpFloat torque);

	cpSpace *cpBodyGetSpace(const cpBody *body);

	void     cpBodyApplyForceAtWorldPoint(cpBody *body, const cpVect force, const cpVect point);
	void     cpBodyApplyForceAtLocalPoint(cpBody *body, const cpVect force, const cpVect point);
	void     cpBodyApplyImpulseAtWorldPoint(cpBody *body, const cpVect impulse, const cpVect point);
	void     cpBodyApplyImpulseAtLocalPoint(cpBody *body, const cpVect impulse, const cpVect point);

	cpCircleShape *cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset);
	cpShape *      cpBoxShapeNew(cpBody *body, cpFloat width, cpFloat height, cpFloat radius);
	void           cpShapeFree(cpShape *shape);

	cpSpace *      cpShapeGetSpace(const cpShape *shape);

	cpBody *       cpShapeGetBody(const cpShape *shape);
	void           cpShapeSetBody(cpShape *shape, cpBody *body);

	cpBool         cpShapeGetSensor(const cpShape *shape);
	void           cpShapeSetSensor(cpShape *shape, cpBool value);

	cpFloat        cpShapeGetFriction(const cpShape *shape);
	void           cpShapeSetFriction(cpShape *shape, cpFloat friction);

	cpPinJoint *   cpPinJointNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB);
	void           cpConstraintFree(cpConstraint *constraint);

	cpVect         cpPinJointGetanchorA(const cpConstraint *constraint);
	void           cpPinJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect         cpPinJointGetanchorB(const cpConstraint *constraint);
	void           cpPinJointSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat        cpPinJointGetDist(const cpConstraint *constraint);
	void           cpPinJointSetDist(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpSlideJointNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat min, cpFloat max);

	cpVect         cpSlideJointGetanchorA(const cpConstraint *constraint);
	void           cpSlideJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect         cpSlideJointGetanchorB(const cpConstraint *constraint);
	void           cpSlideJointSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat        cpSlideJointGetMin(const cpConstraint *constraint);
	void           cpSlideJointSetMin(cpConstraint *constraint, cpFloat value);
	cpFloat        cpSlideJointGetMax(const cpConstraint *constraint);
	void           cpSlideJointSetMax(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpPivotJointNew(cpBody *a, cpBody *b, cpVect pivot);

	cpVect         cpPivotJointGetanchorA(const cpConstraint *constraint);
	void           cpPivotJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect         cpPivotJointGetanchorB(const cpConstraint *constraint);
	void           cpPivotJointSetanchorB(cpConstraint *constraint, cpVect value);

	cpConstraint * cpGrooveJointNew(cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchorB);

	cpVect         cpGrooveJointGetGrooveA(const cpConstraint *constraint);
	void           cpGrooveJointSetGrooveA(cpConstraint *constraint, cpVect value);
	cpVect         cpGrooveJointGetGrooveB(const cpConstraint *constraint);
	void           cpGrooveJointSetGrooveB(cpConstraint *constraint, cpVect value);
	cpVect         cpGrooveJointGetanchorB(const cpConstraint *constraint);
	void           cpGrooveJointSetanchorB(cpConstraint *constraint, cpVect value);

	cpConstraint * cpDampedSpringNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat restLength, cpFloat stiffness, cpFloat damping);

	cpVect         cpDampedSpringGetanchorA(const cpConstraint *constraint);
	void           cpDampedSpringSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect         cpDampedSpringGetanchorB(const cpConstraint *constraint);
	void           cpDampedSpringSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat        cpDampedSpringGetRestLength(const cpConstraint *constraint);
	void           cpDampedSpringSetRestLength(cpConstraint *constraint, cpFloat value);
	cpFloat        cpDampedSpringGetStiffness(const cpConstraint *constraint);
	void           cpDampedSpringSetStiffness(cpConstraint *constraint, cpFloat value);
	cpFloat        cpDampedSpringGetDamping(const cpConstraint *constraint);
	void           cpDampedSpringSetDamping(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpDampedRotarySpringNew(cpBody *a, cpBody *b, cpFloat restAngle, cpFloat stiffness, cpFloat damping);

	cpFloat        cpDampedRotarySpringGetRestAngle(const cpConstraint *constraint);
	void           cpDampedRotarySpringSetRestAngle(cpConstraint *constraint, cpFloat value);
	cpFloat        cpDampedRotarySpringGetStiffness(const cpConstraint *constraint);
	void           cpDampedRotarySpringSetStiffness(cpConstraint *constraint, cpFloat value);
	cpFloat        cpDampedRotarySpringGetDamping(const cpConstraint *constraint);
	void           cpDampedRotarySpringSetDamping(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpRotaryLimitJointNew(cpBody *a, cpBody *b, cpFloat min, cpFloat max);

	cpFloat        cpRotaryLimitJointGetMin(const cpConstraint *constraint);
	void           cpRotaryLimitJointSetMin(cpConstraint *constraint, cpFloat value);
	cpFloat        cpRotaryLimitJointGetMax(const cpConstraint *constraint);
	void           cpRotaryLimitJointSetMax(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpRatchetJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratchet);

	cpFloat        cpRatchetJointGetAngle(const cpConstraint *constraint);
    void           cpRatchetJointSetAngle(cpConstraint *constraint, cpFloat value);
    cpFloat        cpRatchetJointGetPhase(const cpConstraint *constraint);
    void           cpRatchetJointSetPhase(cpConstraint *constraint, cpFloat value);
    cpFloat        cpRatchetJointGetRatchet(const cpConstraint *constraint);
    void           cpRatchetJointSetRatchet(cpConstraint *constraint, cpFloat value);

    cpConstraint * cpGearJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratio);

    cpFloat        cpGearJointGetPhase(const cpConstraint *constraint);
	void           cpGearJointSetPhase(cpConstraint *constraint, cpFloat value);
	cpFloat        cpGearJointGetRatio(const cpConstraint *constraint);
	void           cpGearJointSetRatio(cpConstraint *constraint, cpFloat value);

	cpConstraint * cpSimpleMotorNew(cpBody *a, cpBody *b, cpFloat rate);

	cpFloat        cpSimpleMotorGetRate(const cpConstraint *constraint);
	void           cpSimpleMotorSetRate(cpConstraint *constraint, cpFloat value);

	cpFloat cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset);
	cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b, cpFloat radius);
	cpFloat cpMomentForPoly(cpFloat m, int count, const cpVect *verts, cpVect offset, cpFloat radius);
	cpFloat cpMomentForBox(cpFloat m, cpFloat width, cpFloat height);

]]

local Physics = {}


-- Physics.Space
Physics.Space = {}
Physics.Space.__index = Physics.Space

function Physics.MomentForCircle(mass, r1, r2, offset_x, offset_y)
	return cp.cpMomentForCircle(mass, r1, r2, {offset_x, offset_y})
end

function Physics.MomentForSegment(mass, x1, y1, x2, y2, radius)
	return cp.cpMomentForSegment(mass, {x1, y1}, {x2, y2}, radius)
end

function Physics.MomentForPoly(mass, count, vertices, offset_x, offset_y, radius)
	local c_verts = ffi.new("cpVect[" .. tostring(count) .. "]")
	for i=0,count * 2,2 do
		c_verts[i]     = vertices[i + 1]
		c_verts[i + 1] = vertices[i + 2]
	end
	ffi.gc(c_verts, ffi.C.free)
	return cp.cpMomentForPoly(mass, count, c_verts, {offset_x, offset_y}, radius)
end

function Physics.MomentForBox(mass, width, height)
	return cp.cpMomentForBox(mass, width, height)
end

function Physics.Space.Create()
	local t = setmetatable({}, Physics.Space)
	t.cpSpace = cp.cpSpaceNew()
	ffi.gc(t.cpSpace, cp.cpSpaceFree)
	return t
end

function Physics.Space:Step(delta_time)
	cp.cpSpaceStep(self.cpSpace, delta_time)
end

-- Implemented as Physics.Body:AddToSpace(space)
--[[function Physics.Space:AddBody(body)
	cp.cpSpaceAddBody(self.cpSpace, body.cpBody)
	return body
end--]]

function Physics.Space:GetGravity()
	local vec = cp.cpSpaceGetGravity(self.cpSpace)
	return vec.x, vec.y
end

function Physics.Space:SetGravity(gravity_x, gravity_y)
	cp.cpSpaceSetGravity(self.cpSpace, {gravity_x, gravity_y})
end

function Physics.Space:GetDamping()
	return cp.cpSpaceGetDamping(self.cpSpace)
end

function Physics.Space:SetDamping(value)
	cp.cpSpaceSetDamping(self.cpSpace, value)
end

-- Physics.Body
Physics.Body = {}
Physics.Body.__index = Physics.Body

function Physics.Body.Create(moment, inertia)
	local t = setmetatable({}, Physics.Body)
	t.cpBody = cp.cpBodyNew(moment, inertia)

	local body_free = function(body)
		local space = cp.cpBodyGetSpace(body)
		if space ~= nil then
			cp.cpSpaceRemoveBody(space, body)
		end
		cp.cpBodyFree(body)
	end

	ffi.gc(t.cpBody, body_free)
	return t
end

function Physics.Body.CreateStatic()
	local t = setmetatable({}, Physics.Body)
	t.cpBody = cp.cpBodyNewStatic()

	local body_free = function(body)
		local space = cp.cpBodyGetSpace(body)
		if space ~= nil then
			cp.cpSpaceRemoveBody(space, body)
		end
		cp.cpBodyFree(body)
	end

	ffi.gc(t.cpBody, body_free)
	return t
end

function Physics.Body.CreateKinematic()
	local t = setmetatable({}, Physics.Body)
	t.cpBody = cp.cpBodyNewKinematic()

	local body_free = function(body)
		local space = cp.cpBodyGetSpace(body)
		if space ~= nil then
			cp.cpSpaceRemoveBody(space, body)
		end
		cp.cpBodyFree(body)
	end

	ffi.gc(t.cpBody, body_free)
	return t
end

function Physics.Body:GetPos()
	local vec = cp.cpBodyGetPosition(self.cpBody)
	return vec.x, vec.y
end

function Physics.Body:SetPos(x, y)
	cp.cpBodySetPosition(self.cpBody, {x, y})
end

function Physics.Body:GetRot()
	return cp.cpBodyGetAngle(self.cpBody)
end

function Physics.Body:SetRot(rotation)
	cp.cpBodySetAngle(self.cpBody, rotation)
end

function Physics.Body:GetTorque()
	return cp.cpBodyGetTorque(self.cpBody)
end

function Physics.Body:SetTorque(torque)
	cp.cpBodySetTorque(self.cpBody, torque)
end

function Physics.Body:AddToSpace(space)
	cp.cpSpaceAddBody(space.cpSpace, self.cpBody)
	self.space = space
	return body
end

function Physics.Body:RemoveFromSpace()
	if self.space ~= nil then
		cp.cpSpaceRemoveBody(self.space.cpSpace, self.cpBody)
		self.space = nil
	end
end

function Physics.Body:ApplyForceAtWorldPoint(force_x, force_y, point_x, point_y)
	cp.cpBodyApplyForceAtWorldPoint(self.cpBody, {force_x, force_y}, {point_x, point_y})
end

function Physics.Body:ApplyForceAtLocalPoint(force_x, force_y, point_x, point_y)
	cp.cpBodyApplyForceAtLocalPoint(self.cpBody, {force_x, force_y}, {point_x, point_y})
end

function Physics.Body:ApplyImpulseAtWorldPoint(impulse_x, impulse_y, point_x, point_y)
	cp.cpBodyApplyImpulseAtWorldPoint(self.cpBody, {impulse_x, impulse_y}, {point_x, point_y})
end

function Physics.Body:ApplyImpulseAtLocalPoint(impulse_x, impulse_y, point_x, point_y)
	cp.cpBodyApplyImpulseAtLocalPoint(self.cpBody, {impulse_x, impulse_y}, {point_x, point_y})
end

-- Physics.Shape
Physics.Shape = {}
Physics.Shape.__index = Physics.Shape

function Physics.Shape.CreateCircle(body, radius, offset_x, offset_y)
	local t = setmetatable({}, Physics.Shape)
	t.cpShape = cp.cpCircleShapeNew(body.cpBody, radius, {offset_x, offset_y})
	t.body = body

	local shape_free = function(shape)
		local space = cp.cpShapeGetSpace(shape)
		if space ~= nil then
			cp.cpSpaceRemoveShape(space, shape)
		end
		local body = cp.cpShapeGetBody(shape)
		if body ~= nil then
			cp.cpShapeSetBody(shape, nil)
		end
		cp.cpShapeFree(shape)
	end

	ffi.gc(t.cpShape, shape_free)
	return t
end

function Physics.Shape.CreateBox(body, width, height, radius)
	local t = setmetatable({}, Physics.Shape)
	t.cpShape = cp.cpBoxShapeNew(body.cpBody, width, height, radius)
	t.body = body

	local shape_free = function(shape)
		local space = cp.cpShapeGetSpace(shape)
		if space ~= nil then
			cp.cpSpaceRemoveShape(space, shape)
		end
		local body = cp.cpShapeGetBody(shape)
		if body ~= nil then
			cp.cpShapeSetBody(shape, nil)
		end
		cp.cpShapeFree(shape)
	end

	ffi.gc(t.cpShape, shape_free)
	return t
end

function Physics.Shape:AddToSpace(space)
	cp.cpSpaceAddShape(space.cpSpace, self.cpShape)
	self.space = space
end

function Physics.Shape:RemoveFromSpace()
	cp.cpSpaceRemoveShape(self.space.cpSpace, self.cpShape)
end

function Physics.Shape:GetSensor()
	return cp.cpShapeGetSensor(self.cpShape)
end

function Physics.Shape:SetSensor(sensor)
	cp.ShapeSetSensor(self.cpShape, sensor)
end

function Physics.Shape:GetFriction()
	return cp.cpShapeGetFriction(self.cpShape)
end

function Physics.Shape:SetFriction(friction)
	cp.cpShapeSetFriction(self.cpShape, friction)
end

-- Physics.Constraint
Physics.Constraint = {}
Physics.Constraint.__index = Physics.Constraint

function Physics.Constraint.CreatePinJoint(body1, body2, x1, y1, x2, y2)
	local t = setmetatable({}, Physics.Constraint)
	t.cpConstraint = cp.cpPinJointNew(body1, body2, {x1, y1}, {x2, y2})

	ffi.gc(t.cpConstraint, cp.cpConstraintFree)
	return t
end

function Physics.Constraint:GetPinJointDistance()
	return cp.cpPinJointGetDist(self.cpConstraint)
end

function Physics.Constraint:SetPinJointDistance(distance)
	cp.cpPinJointSetDist(self.cpConstraint, distance)
end

return Physics