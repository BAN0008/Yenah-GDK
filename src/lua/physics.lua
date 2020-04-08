-- Yenah:physics.lua

local ffi = require 'ffi'

local PrintAddress = function(name, addr)
	print(string.format(name .. ": 0x%x", tonumber(ffi.cast("uintptr_t", addr))))
end

cp = ffi.load("chipmunk")
ffi.cdef[[
	void free(void *ptr);

	typedef void cpArbiter;

	typedef double cpFloat;
	typedef unsigned char cpBool;
	typedef struct cpVect{cpFloat x,y;} cpVect;

	typedef void cpSpace;
	typedef void *cpDataPointer;

	typedef int  (*cpCollisionBeginFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer data);
	typedef int  (*cpCollisionPreSolveFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer data);
	typedef void (*cpCollisionPostSolveFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer data);
	typedef void (*cpCollisionSeparateFunc)(cpArbiter *arb, cpSpace *space, cpDataPointer data);
	typedef void (*cpPostStepFunc)(cpSpace *space, void *obj, void *data);

	typedef uintptr_t cpCollisionType;
	typedef void cpBody;
	typedef void cpShape;
	typedef void cpCircleShape;
	typedef void cpPinJoint;
	typedef void cpConstraint;
	typedef struct cpCollisionHandler {
		const cpCollisionType typeA, typeB;
		cpCollisionBeginFunc     beginFunc;
		cpCollisionPreSolveFunc  preSolveFunc;
		cpCollisionPostSolveFunc postSolveFunc;
		cpCollisionSeparateFunc  seperateFunc;
		cpDataPointer userData;
	} cpCollisionHandler;
	
	typedef uintptr_t cpGroup;
	typedef unsigned int cpBitmask;
	
	typedef struct cpShapeFilter{cpGroup group; cpBitmask categories; cpBitmask mask;} cpShapeFilter;

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

	cpBody *        cpBodyNew(cpFloat m, cpFloat i);
	cpBody *        cpBodyNewStatic();
	cpBody *        cpBodyNewKinematic();
	void            cpBodyFree(cpBody *body);

	cpVect          cpBodyGetPosition(const cpBody *body);
	void            cpBodySetPosition(cpBody *body, cpVect pos);
	
	cpFloat         cpBodyGetAngle(const cpBody *body);
	void            cpBodySetAngle(cpBody *body, cpFloat angle);
	
	cpVect          cpBodyGetVelocity(const cpBody *body);
	void            cpBodySetVelocity(cpBody *body, const cpVect velocity);
	
	cpVect          cpBodyGetForce(const cpBody *body);
	void            cpBodySetForce(cpBody *body, const cpVect force);

	cpFloat         cpBodyGetTorque(const cpBody *body);
	void            cpBodySetTorque(cpBody *body, cpFloat torque);
	
	cpDataPointer   cpBodyGetUserData(const cpBody *body);
	void            cpBodySetUserData(cpBody *body, const cpDataPointer userdata);

	cpSpace *       cpBodyGetSpace(const cpBody *body);

	void            cpBodyApplyForceAtWorldPoint(cpBody *body, const cpVect force, const cpVect point);
	void            cpBodyApplyForceAtLocalPoint(cpBody *body, const cpVect force, const cpVect point);
	void            cpBodyApplyImpulseAtWorldPoint(cpBody *body, const cpVect impulse, const cpVect point);
	void            cpBodyApplyImpulseAtLocalPoint(cpBody *body, const cpVect impulse, const cpVect point);

	cpCircleShape * cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset);
	cpShape *       cpBoxShapeNew(cpBody *body, cpFloat width, cpFloat height, cpFloat radius);
	void            cpShapeFree(cpShape *shape);

	cpSpace *       cpShapeGetSpace(const cpShape *shape);

	cpBody *        cpShapeGetBody(const cpShape *shape);
	void            cpShapeSetBody(cpShape *shape, cpBody *body);

	cpBool          cpShapeGetSensor(const cpShape *shape);
	void            cpShapeSetSensor(cpShape *shape, cpBool value);

	cpFloat         cpShapeGetFriction(const cpShape *shape);
	void            cpShapeSetFriction(cpShape *shape, cpFloat friction);

	cpCollisionType cpShapeGetCollisionType(const cpShape *shape);
	void            cpShapeSetCollisionType(cpShape *shape, cpCollisionType type);

	cpShapeFilter   cpShapeGetFilter(const cpShape *shape);
	void            cpShapeSetFilter(cpShape *shape, cpShapeFilter filter);

	cpPinJoint *    cpPinJointNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB);
	void            cpConstraintFree(cpConstraint *constraint);

	cpVect          cpPinJointGetanchorA(const cpConstraint *constraint);
	void            cpPinJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect          cpPinJointGetanchorB(const cpConstraint *constraint);
	void            cpPinJointSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat         cpPinJointGetDist(const cpConstraint *constraint);
	void            cpPinJointSetDist(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpSlideJointNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat min, cpFloat max);

	cpVect          cpSlideJointGetanchorA(const cpConstraint *constraint);
	void            cpSlideJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect          cpSlideJointGetanchorB(const cpConstraint *constraint);
	void            cpSlideJointSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat         cpSlideJointGetMin(const cpConstraint *constraint);
	void            cpSlideJointSetMin(cpConstraint *constraint, cpFloat value);
	cpFloat         cpSlideJointGetMax(const cpConstraint *constraint);
	void            cpSlideJointSetMax(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpPivotJointNew(cpBody *a, cpBody *b, cpVect pivot);

	cpVect          cpPivotJointGetanchorA(const cpConstraint *constraint);
	void            cpPivotJointSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect          cpPivotJointGetanchorB(const cpConstraint *constraint);
	void            cpPivotJointSetanchorB(cpConstraint *constraint, cpVect value);

	cpConstraint *  cpGrooveJointNew(cpBody *a, cpBody *b, cpVect groove_a, cpVect groove_b, cpVect anchorB);

	cpVect          cpGrooveJointGetGrooveA(const cpConstraint *constraint);
	void            cpGrooveJointSetGrooveA(cpConstraint *constraint, cpVect value);
	cpVect          cpGrooveJointGetGrooveB(const cpConstraint *constraint);
	void            cpGrooveJointSetGrooveB(cpConstraint *constraint, cpVect value);
	cpVect          cpGrooveJointGetanchorB(const cpConstraint *constraint);
	void            cpGrooveJointSetanchorB(cpConstraint *constraint, cpVect value);

	cpConstraint *  cpDampedSpringNew(cpBody *a, cpBody *b, cpVect anchorA, cpVect anchorB, cpFloat restLength, cpFloat stiffness, cpFloat damping);

	cpVect          cpDampedSpringGetanchorA(const cpConstraint *constraint);
	void            cpDampedSpringSetanchorA(cpConstraint *constraint, cpVect value);
	cpVect          cpDampedSpringGetanchorB(const cpConstraint *constraint);
	void            cpDampedSpringSetanchorB(cpConstraint *constraint, cpVect value);
	cpFloat         cpDampedSpringGetRestLength(const cpConstraint *constraint);
	void            cpDampedSpringSetRestLength(cpConstraint *constraint, cpFloat value);
	cpFloat         cpDampedSpringGetStiffness(const cpConstraint *constraint);
	void            cpDampedSpringSetStiffness(cpConstraint *constraint, cpFloat value);
	cpFloat         cpDampedSpringGetDamping(const cpConstraint *constraint);
	void            cpDampedSpringSetDamping(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpDampedRotarySpringNew(cpBody *a, cpBody *b, cpFloat restAngle, cpFloat stiffness, cpFloat damping);

	cpFloat         cpDampedRotarySpringGetRestAngle(const cpConstraint *constraint);
	void            cpDampedRotarySpringSetRestAngle(cpConstraint *constraint, cpFloat value);
	cpFloat         cpDampedRotarySpringGetStiffness(const cpConstraint *constraint);
	void            cpDampedRotarySpringSetStiffness(cpConstraint *constraint, cpFloat value);
	cpFloat         cpDampedRotarySpringGetDamping(const cpConstraint *constraint);
	void            cpDampedRotarySpringSetDamping(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpRotaryLimitJointNew(cpBody *a, cpBody *b, cpFloat min, cpFloat max);

	cpFloat         cpRotaryLimitJointGetMin(const cpConstraint *constraint);
	void            cpRotaryLimitJointSetMin(cpConstraint *constraint, cpFloat value);
	cpFloat         cpRotaryLimitJointGetMax(const cpConstraint *constraint);
	void            cpRotaryLimitJointSetMax(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpRatchetJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratchet);

	cpFloat         cpRatchetJointGetAngle(const cpConstraint *constraint);
    void            cpRatchetJointSetAngle(cpConstraint *constraint, cpFloat value);
    cpFloat         cpRatchetJointGetPhase(const cpConstraint *constraint);
    void            cpRatchetJointSetPhase(cpConstraint *constraint, cpFloat value);
    cpFloat         cpRatchetJointGetRatchet(const cpConstraint *constraint);
    void            cpRatchetJointSetRatchet(cpConstraint *constraint, cpFloat value);

    cpConstraint *  cpGearJointNew(cpBody *a, cpBody *b, cpFloat phase, cpFloat ratio);

    cpFloat         cpGearJointGetPhase(const cpConstraint *constraint);
	void            cpGearJointSetPhase(cpConstraint *constraint, cpFloat value);
	cpFloat         cpGearJointGetRatio(const cpConstraint *constraint);
	void            cpGearJointSetRatio(cpConstraint *constraint, cpFloat value);

	cpConstraint *  cpSimpleMotorNew(cpBody *a, cpBody *b, cpFloat rate);

	cpFloat         cpSimpleMotorGetRate(const cpConstraint *constraint);
	void            cpSimpleMotorSetRate(cpConstraint *constraint, cpFloat value);

	cpFloat cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset);
	cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b, cpFloat radius);
	cpFloat cpMomentForPoly(cpFloat m, int count, const cpVect *verts, cpVect offset, cpFloat radius);
	cpFloat cpMomentForBox(cpFloat m, cpFloat width, cpFloat height);

	cpCollisionHandler *cpSpaceAddCollisionHandler(cpSpace *space, cpCollisionType a, cpCollisionType b);
	cpCollisionHandler *cpSpaceAddWildcardHandler(cpSpace *space, cpCollisionType type);
	cpBool              cpSpaceAddPostStepCallback(cpSpace *space, cpPostStepFunc func, void *key, void *data);

	void                cpArbiterGetBodies(const cpArbiter *arbiter, cpBody **a, cpBody **b);
	void                cpArbiterGetShapes(const cpArbiter *arbiter, cpShape **a, cpShape **b);
	cpBool              cpArbiterIsFirstContact(const cpArbiter *arbiter);
	cpBool              cpArbiterIsRemoval(const cpArbiter *arbiter);
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

function Physics.Body:GetVelocity()
	return cp.cpBodyGetVelocity(self.cpBody)
end

function Physics.Body:SetVelocity(vel_x, vel_y)
	cp.cpBodySetVelocity(self.cpBody, {vel_x, vel_y})
end

function Physics.Body:GetForce()
	return cp.cpBodyGetForce(self.cpBody)
end

function Physics.Body:SetForce(force_x, force_y)
	cp.cpBodySetForce(self.cpBody, {force_x, force_y})
end

function Physics.Body:GetUserData()
	return cp.cpBodyGetUserData(self.cpBody)
end

function Physics.Body:SetUserData(userdata)
	cp.cpBodySetUserData(self.cpBody, userdata)
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
	cp.cpShapeSetSensor(self.cpShape, sensor)
end

function Physics.Shape:GetFriction()
	return cp.cpShapeGetFriction(self.cpShape)
end

function Physics.Shape:SetFriction(friction)
	cp.cpShapeSetFriction(self.cpShape, friction)
end

function Physics.Shape:GetCollisionType()
	return cp.cpShapeGetCollisionType(self.cpShape)
end

function Physics.Shape:SetCollisionType(col_type)
	cp.cpShapeSetCollisionType(self.cpShape, col_type)
end

function Physics.Shape:GetFilter()
	return cp.cpShapeGetFilter(self.cpShape)
end

function Physics.Shape:SetFilter(filter)
	cp.cpShapeSetFilter(self.cpShape, filter)
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

-- Physics.Handler
Physics.Handler = {}
Physics.Handler.__index = Physics.Handler

-- cpCollisionPreSolveFunc
-- cpCollisionBeginFunc
-- cpCollisionPostSolveFunc
-- cpCollisionSeparateFunc

function Physics.Handler.Add(space, type_a, type_b, begin, pre, post, sep)
	cbegin = ffi.new("cpCollisionBeginFunc",     begin)
	cpre   = ffi.new("cpCollisionPreSolveFunc",  pre)
	cpost  = ffi.new("cpCollisionPostSolveFunc", post)
	csep   = ffi.new("cpCollisionSeparateFunc",  sep)
	handler = cp.cpSpaceAddCollisionHandler(space.cpSpace, type_a, type_b)
	handler.beginFunc     = cbegin
	handler.preSolveFunc  = cpre
	handler.postSolveFunc = cpost
	handler.seperateFunc  = csep
end

function Physics.Handler.AddWildcard(space, type_a, begin, pre, post, sep)
	--begin = sep
	--pre = sep
	--post = sep
	--cbegin = ffi.new("cpCollisionBeginFunc",     begin)
	--cpre   = ffi.new("cpCollisionPreSolveFunc",  pre)
	--cpost  = ffi.new("cpCollisionPostSolveFunc", post)
	--csep   = ffi.new("cpCollisionSeparateFunc",  sep)
	--handler = cp.cpSpaceAddWildcardHandler(space.cpSpace, type_a)
	local handler = ffi.new("cpCollisionHandler *", cp.cpSpaceAddWildcardHandler(space.cpSpace, type_a))
	print(string.format("%x", tonumber(ffi.cast("unsigned long long", handler))))
	local beginFuncAddress = ffi.cast("unsigned long long", 
		(handler + ffi.offsetof("cpCollisionHandler", "beginFunc"))
	)
	--ffi.cast("cpCollisionBeginFunc *", beginFuncAddress)[0] = ffi.new("cpCollisionBeginFunc", sep)
	
	print("offsetof beginFunc - " .. tostring(ffi.offsetof("cpCollisionHandler", "beginFunc")))

	local handlerBeginFunc = ffi.cast("cpCollisionBeginFunc *", ffi.cast("uintptr_t", handler) + ffi.offsetof("cpCollisionHandler", "beginFunc"))
	handlerBeginFunc[0] = begin

	print(string.format("beginFunc address %x", tonumber(ffi.cast("uintptr_t", handler) + ffi.offsetof("cpCollisionHandler", "beginFunc"))))
	--print(string.format("beginFunc address - %x", tonumber(beginFuncAddress)))
	--handler.beginFunc     = sep
	--handler.preSolveFunc  = pre
	--handler.postSolveFunc = post
	--handler.seperateFunc  = sep
end

function Physics.Handler.AddPostStep(cpSpace, func, key, data)
	cp.cpSpaceAddPostStepCallback(cpSpace, func, key, data)
end

-- Physics.Arbiter
Physics.Arbiter = {}
Physics.Arbiter.__index = Physics.Arbiter

function Physics.Arbiter.Create(arb_cdata)
	return setmetatable({cpArbiter = arb_cdata}, Physics.Arbiter)
end

function Physics.Arbiter:GetBodies()
	local body_a = setmetatable({}, Physics.Body)
	local body_b = setmetatable({}, Physics.Body)

	local body_a_ptr = ffi.new("cpBody *[1]", nil)
	local body_b_ptr = ffi.new("cpBody *[1]", nil)

	cp.cpArbiterGetBodies(self.cpArbiter, body_a_ptr, body_b_ptr)
	body_a.cpBody = body_a_ptr[0]
	body_b.cpBody = body_b_ptr[0]
	--PrintAddress("BA1", body_a_ptr[0])
	--PrintAddress("BA2", body_a.cpBody)
	return body_a, body_b
end

function Physics.Arbiter:GetShapes()
	local shape_a = setmetatable({}, Physics.Shape)
	local shape_b = setmetatable({}, Physics.Shape)

	local shape_a_ptr = ffi.new("cpShape *[1]", nil)
	local shape_b_ptr = ffi.new("cpShape *[1]", nil)

	cp.cpArbiterGetShapes(self.cpArbiter, shape_a_ptr, shape_b_ptr)
	shape_a.cpShape = shape_a_ptr[0]
	shape_b.cpShape = shape_b_ptr[0]
	shape_a.body = setmetatable({cpBody = cp.cpShapeGetBody(shape_a.cpShape)}, Physics.Body)
	shape_b.body = setmetatable({cpBody = cp.cpShapeGetBody(shape_b.cpShape)}, Physics.Body)
	return shape_a, shape_b
end

--Physics.ObjectRefs = setmetatable({}, {__mode = "kv"})
Physics.ObjectRefs = {}
function Physics.ObjectRefs_Add(object)
	local i = 1
	while Physics.ObjectRefs[i] ~= nil do
		i = i + 1
	end
	Physics.ObjectRefs[i] = object
	return i
end

return Physics