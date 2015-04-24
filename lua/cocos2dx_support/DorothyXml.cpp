#include "DorothyXml.h"

static void oHandler(const char* begin, const char* end)
{
#define CHECK_CDATA(name) if (strcmp(begin,#name) == 0) CCSAXParser::placeCDataHeader("</"#name">");
#define ELSE_CHECK_CDATA(name) else CHECK_CDATA(name)
	if (*(begin-1) != '/')
	{
		CHECK_CDATA(Listener)
		ELSE_CHECK_CDATA(Call)
		ELSE_CHECK_CDATA(Script)
		ELSE_CHECK_CDATA(Schedule)
		ELSE_CHECK_CDATA(TapHandler)
		ELSE_CHECK_CDATA(NodeHandler)
		ELSE_CHECK_CDATA(TouchHandler)
		ELSE_CHECK_CDATA(KeypadHandler)
		ELSE_CHECK_CDATA(AccelerateHandler)
	}
}

#define Self_Check(name) \
	if (self.empty()) { self = getUsableName(#name); names.insert(self); }\
	if (firstItem.empty()) firstItem = self;

// Schedule
#define Schedule_Check \
	CASE_STR(Priority) { priority = atts[++i]; break; }

// Vec2
#define Vec2_Define \
	const char* x = nullptr;\
	const char* y = nullptr;
#define Vec2_Check \
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }
#define Vec2_Handle \
	items.push(string("oVec2(")+(x ? x : "0")+","+(y ? y : "0")+")");

// Object
#define Object_Define \
	string self;
#define Object_Check \
	CASE_STR(Name) { self = atts[++i]; break; }\
	CASE_STR(Key) { if (strcmp(elementStack.top().type,"Data") == 0) currentKey = atts[++i]; break; }

// Speed
#define Speed_Define \
	Object_Define\
	const char* rate = nullptr;
#define Speed_Check \
	Object_Check\
	CASE_STR(Rate) { rate = atts[++i]; break; }
#define Speed_Create
#define Speed_Handle \
	oFunc func = {"CCSpeed(", (rate ? string(",")+rate+")" : ",1)")};\
	funcs.push(func);\
	items.push("");
#define Speed_Finish

// Loop
#define Loop_Define \
	Object_Define\
	const char* times = nullptr;
#define Loop_Check \
	Object_Check\
	CASE_STR(Times) { times = atts[++i]; break; }
#define Loop_Create
#define Loop_Handle \
	oFunc func = {(times ? "CCRepeat(" : "CCRepeatForever("), (times ? string(",")+times+")" : ")")};\
	funcs.push(func);\
	items.push("");
#define Loop_Finish

// Delay
#define Delay_Define \
	Object_Define\
	const char* time = nullptr;
#define Delay_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }
#define Delay_Create
#define Delay_Handle \
	string str("CCDelay(");\
	if (time) str += time; else str += "0";\
	str += ")";\
	oFunc func = {str,""};\
	funcs.push(func);
#define Delay_Finish

// Scale
#define Scale_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* ease = nullptr;
#define Scale_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Scale_Create
#define Scale_Handle \
	oFunc func = {string("oScale(")+(time ? time : "0")+","+(x ? x : "")+","+(y ? y : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Scale_Finish

// Move
#define Move_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* ease = nullptr;
#define Move_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Move_Create
#define Move_Handle \
	oFunc func = {string("oPos(")+(time ? time : "0")+","+(x ? x : "")+","+(y ? y : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Move_Finish

// Rotate
#define Rotate_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* angle = nullptr;\
	const char* ease = nullptr;
#define Rotate_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Angle) { angle = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Rotate_Create
#define Rotate_Handle \
	oFunc func = {string("oRotate(")+(time ? time : "0")+","+(angle ? angle : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Rotate_Finish

// Opacity
#define Opacity_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* alpha = nullptr;\
	const char* ease = nullptr;
#define Opacity_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Alpha) { alpha = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Opacity_Create
#define Opacity_Handle \
	oFunc func = {string("oOpacity(")+(time ? time : "0")+","+(alpha ? alpha : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Opacity_Finish

// Skew
#define Skew_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* ease = nullptr;
#define Skew_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Skew_Create
#define Skew_Handle \
	oFunc func = {string("oSkew(")+(time ? time : "0")+","+(x ? x : "")+","+(y ? y : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Skew_Finish

// Roll
#define Roll_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* angle = nullptr;\
	const char* ease = nullptr;
#define Roll_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Angle) { angle = atts[++i]; break; }\
	CASE_STR(Ease) { ease = atts[++i]; break; }
#define Roll_Create
#define Roll_Handle \
	oFunc func = {string("oRoll(")+(time ? time : "0")+","+(angle ? angle : "")+(ease ? ",oEase." : "")+(ease ? ease : "")+")",""};\
	funcs.push(func);
#define Roll_Finish

// Jump
#define Jump_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* height = nullptr;\
	const char* jumps = nullptr;
#define Jump_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Height) { height = atts[++i]; break; }\
	CASE_STR(Jumps) { jumps = atts[++i]; break; }
#define Jump_Create
#define Jump_Handle \
	oFunc func = {string("CCJumpTo(")+(time ? time : "0")+","+(x ? x : "")+","+(y ? y : "")+","+(height ? height : "")+","+(jumps ? jumps : "1")+")",""};\
	funcs.push(func);
#define Jump_Finish

// Bezier
#define Bezier_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* firstX = nullptr;\
	const char* firstY = nullptr;\
	const char* secondX = nullptr;\
	const char* secondY = nullptr;
#define Bezier_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(X1) { firstX = atts[++i]; break; }\
	CASE_STR(Y1) { firstY = atts[++i]; break; }\
	CASE_STR(X2) { secondX = atts[++i]; break; }\
	CASE_STR(Y2) { secondY = atts[++i]; break; }
#define Bezier_Create
#define Bezier_Handle \
	oFunc func = {string("CCBezierTo(")+(time ? time : "0")+",oVec2("+(x ? x : "")+","+(y ? y : "")+"),oVec2("+(firstX ? firstX : "")+","+(firstY ? firstY : "")+"),oVec2("+(secondX ? secondX : "")+","+(secondY ? secondY : "")+"))",""};\
	funcs.push(func);
#define Bezier_Finish

// Blink
#define Blink_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* blinks = nullptr;
#define Blink_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Blinks) { blinks = atts[++i]; break; }
#define Blink_Create
#define Blink_Handle \
	oFunc func = {string("CCBlink(")+(time ? time : "0")+","+(blinks ? blinks : "1")+")",""};\
	funcs.push(func);
#define Blink_Finish

// Tint
#define Tint_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* color = nullptr;
#define Tint_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Color) { color = atts[++i]; break; }
#define Tint_Create
#define Tint_Handle \
	oFunc func = {string("CCTintTo(")+(time ? time : "0")+","+(color ? color : "0xffffffff")+")",""};\
	funcs.push(func);
#define Tint_Finish

// Show
#define Show_Define \
	Object_Define
#define Show_Check \
	Object_Check
#define Show_Create
#define Show_Handle \
	oFunc func = {"CCShow()",""};\
	funcs.push(func);
#define Show_Finish

// Hide
#define Hide_Define \
	Object_Define
#define Hide_Check \
	Object_Check
#define Hide_Create
#define Hide_Handle \
	oFunc func = {"CCHide()",""};\
	funcs.push(func);
#define Hide_Finish

// Flip
#define Flip_Define \
	Object_Define\
	const char* flipX = nullptr;\
	const char* flipY = nullptr;
#define Flip_Check \
	Object_Check\
	CASE_STR(X) { flipX = atts[++i]; break; }\
	CASE_STR(Y) { flipY = atts[++i]; break; }
#define Flip_Create
#define Flip_Handle \
	oFunc func;\
	if (flipX && flipY) func.begin = string("CCSpawn({CCFlipX(")+flipX+"),CCFlipY("+flipY+")})";\
	else if (flipX && !flipY) func.begin = string("CCFlipX(")+flipX+")";\
	else if (!flipX && flipY) func.begin = string("CCFlipY(")+flipY+")";\
	funcs.push(func);
#define Flip_Finish

// Call
#define Call_Define \
	Object_Define
#define Call_Check \
	Object_Check
#define Call_Create
#define Call_Handle \
	oFunc func = {"CCCall(",")"};\
	funcs.push(func);
#define Call_Finish

// Orbit
#define Orbit_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* startRadius = nullptr;\
	const char* deltaRadius = nullptr;\
	const char* startAngleZ = nullptr;\
	const char* deltaAngleZ = nullptr;\
	const char* startAngleX = nullptr;\
	const char* deltaAngleX = nullptr;
#define Orbit_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(StartRadius) { startRadius = atts[++i]; break; }\
	CASE_STR(DeltaRadius) { deltaRadius = atts[++i]; break; }\
	CASE_STR(StartAngleZ) { startAngleZ = atts[++i]; break; }\
	CASE_STR(DeltaAngleZ) { deltaAngleZ = atts[++i]; break; }\
	CASE_STR(StartAngleX) { startAngleX = atts[++i]; break; }\
	CASE_STR(DeltaAngleX) { deltaAngleX = atts[++i]; break; }
#define Orbit_Create
#define Orbit_Handle \
	oFunc func = {string("CCOrbitCamera(")+(time ? time : "0")+","+(startRadius ? startRadius : "0")+","+(deltaRadius ? deltaRadius : "0")+","+(startAngleZ ? startAngleZ : "0")+","+(deltaAngleZ ? deltaAngleZ : "0")+","+(startAngleX ? startAngleX : "0")+","+(deltaAngleX ? deltaAngleX : "0")+")",""};\
	funcs.push(func);
#define Orbit_Finish

// CardinalSpline
#define CardinalSpline_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* tension = nullptr;
#define CardinalSpline_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Tension) { tension = atts[++i]; break; }
#define CardinalSpline_Create
#define CardinalSpline_Handle \
	oFunc func = {string("CCCardinalSplineTo(")+(time ? time : 0)+",{",string("},")+(tension ? tension : "0")+")"};\
	funcs.push(func);\
	items.push("CardinalSpline");
#define CardinalSpline_Finish

// Grid.FlipX3D
#define Grid_FlipX3D_Define \
	Object_Define\
	const char* time = nullptr;
#define Grid_FlipX3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }
#define Grid_FlipX3D_Create
#define Grid_FlipX3D_Handle \
	oFunc func = {string("CCGrid:flipX3D(")+(time ? time : "0")+")",""};\
	funcs.push(func);
#define Grid_FlipX3D_Finish

// Grid.FlipY3D
#define Grid_FlipY3D_Define \
	Object_Define\
	const char* time = nullptr;
#define Grid_FlipY3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }
#define Grid_FlipY3D_Create
#define Grid_FlipY3D_Handle \
	oFunc func = {string("CCGrid:flipY3D(")+(time ? time : "0")+")",""};\
	funcs.push(func);
#define Grid_FlipY3D_Finish

// Grid.Lens3D
#define Grid_Lens3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* radius = nullptr;
#define Grid_Lens3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Radius) { radius = atts[++i]; break; }
#define Grid_Lens3D_Create
#define Grid_Lens3D_Handle \
	oFunc func = {string("CCGrid:lens3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),oVec2("+(x ? x : "0")+","+(y ? y : "0")+"),"+(radius ? radius : "0")+")",""};\
	funcs.push(func);
#define Grid_Lens3D_Finish

// Grid.Liquid
#define Grid_Liquid_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* waves = nullptr;\
	const char* amplitude = nullptr;
#define Grid_Liquid_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Waves) { waves = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Grid_Liquid_Create
#define Grid_Liquid_Handle \
	oFunc func = {string("CCGrid:liquid(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(waves ? waves : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Grid_Liquid_Finish

// Grid.Reuse
#define Grid_Reuse_Define \
	Object_Define\
	const char* times = nullptr;
#define Grid_Reuse_Check \
	Object_Check\
	CASE_STR(Times) { times = atts[++i]; break; }
#define Grid_Reuse_Create
#define Grid_Reuse_Handle \
	oFunc func = {string("CCGrid:reuse(")+(times ? times : "0")+")",""};\
	funcs.push(func);
#define Grid_Reuse_Finish

// Grid.Ripple3D
#define Grid_Ripple3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* radius = nullptr;\
	const char* waves = nullptr;\
	const char* amplitude = nullptr;
#define Grid_Ripple3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Radius) { radius = atts[++i]; break; }\
	CASE_STR(Waves) { waves = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Grid_Ripple3D_Create
#define Grid_Ripple3D_Handle \
	oFunc func = {string("CCGrid:ripple3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),oVec2("+(x ? x : "0")+","+(y ? y : "0")+"),"+(radius ? radius : "0")+","+\
	(waves ? waves : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Grid_Ripple3D_Finish

// Grid.Shaky3D
#define Grid_Shaky3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* range = nullptr;\
	const char* shakeZ = nullptr;
#define Grid_Shaky3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Range) { range = atts[++i]; break; }\
	CASE_STR(ShakeZ) { shakeZ = atts[++i]; break; }
#define Grid_Shaky3D_Create
#define Grid_Shaky3D_Handle \
	oFunc func = {string("CCGrid:shaky3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(range ? range : "0")+","+(shakeZ ? shakeZ : "false")+")",""};\
	funcs.push(func);
#define Grid_Shaky3D_Finish

// Grid.Stop
#define Grid_Stop_Define \
	Object_Define
#define Grid_Stop_Check \
	Object_Check
#define Grid_Stop_Create
#define Grid_Stop_Handle \
	oFunc func = {"CCGrid:stop()",""};\
	funcs.push(func);
#define Grid_Stop_Finish

// Grid.Twirl
#define Grid_Twirl_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* twirls = nullptr;\
	const char* amplitude = nullptr;
#define Grid_Twirl_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Twirls) { twirls = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Grid_Twirl_Create
#define Grid_Twirl_Handle \
	oFunc func = {string("CCGrid:twirl(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),oVec2("+(x ? x : "0")+","+(y ? y : "0")+"),"+\
	(twirls ? twirls : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Grid_Twirl_Finish

// Grid.Wave
#define Grid_Wave_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* waves = nullptr;\
	const char* amplitude = nullptr;\
	const char* horizontal = nullptr;\
	const char* vertical = nullptr;
#define Grid_Wave_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Waves) { waves = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }\
	CASE_STR(Horizontal) { horizontal = atts[++i]; break; }\
	CASE_STR(Vertical) { vertical = atts[++i]; break; }
#define Grid_Wave_Create
#define Grid_Wave_Handle \
	oFunc func = {string("CCGrid:waves(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(waves ? waves : "0")+","+(amplitude ? amplitude : "0")+","+\
	(horizontal ? horizontal : "0")+","+(vertical ? vertical : "0")+")",""};\
	funcs.push(func);
#define Grid_Wave_Finish

// Grid.Wave3D
#define Grid_Wave3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* waves = nullptr;\
	const char* amplitude = nullptr;
#define Grid_Wave3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Waves) { waves = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Grid_Wave3D_Create
#define Grid_Wave3D_Handle \
	oFunc func = {string("CCGrid:waves3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(waves ? waves : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Grid_Wave3D_Finish

// Tile.FadeOut
#define Tile_FadeOut_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* orientation = nullptr;
#define Tile_FadeOut_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Dir) { orientation = atts[++i]; break; }
#define Tile_FadeOut_Create
#define Tile_FadeOut_Handle \
	oFunc func = {string("CCTile:fadeOut(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	"CCOrientation."+(orientation ? orientation : "Down")+")",""};\
	funcs.push(func);
#define Tile_FadeOut_Finish

// Tile.Jump3D
#define Tile_Jump3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* numberOfJumps = nullptr;\
	const char* amplitude = nullptr;
#define Tile_Jump3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Jumps) { numberOfJumps = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Tile_Jump3D_Create
#define Tile_Jump3D_Handle \
	oFunc func = {string("CCTile:jump3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(numberOfJumps ? numberOfJumps : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Tile_Jump3D_Finish

// Tile.Shaky3D
#define Tile_Shaky3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* range = nullptr;\
	const char* shakeZ = nullptr;
#define Tile_Shaky3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Range) { range = atts[++i]; break; }\
	CASE_STR(ShakeZ) { shakeZ = atts[++i]; break; }
#define Tile_Shaky3D_Create
#define Tile_Shaky3D_Handle \
	oFunc func = {string("CCTile:shaky3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(range ? range : "0")+","+(shakeZ ? shakeZ : "false")+")",""};\
	funcs.push(func);
#define Tile_Shaky3D_Finish

// Tile.Shuffle
#define Tile_Shuffle_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;
#define Tile_Shuffle_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }
#define Tile_Shuffle_Create
#define Tile_Shuffle_Handle \
	oFunc func = {string("CCTile:shuffle(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"))",""};\
	funcs.push(func);
#define Tile_Shuffle_Finish

#define Tile_SplitCols_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* cols = nullptr;
#define Tile_SplitCols_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Columns) { cols = atts[++i]; break; }
#define Tile_SplitCols_Create
#define Tile_SplitCols_Handle \
	oFunc func = {string("CCTile:splitCols(")+(time ? time : "0")+","+(cols ? cols : "0")+")",""};\
	funcs.push(func);
#define Tile_SplitCols_Finish

// Tile.SplitRows
#define Tile_SplitRows_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* rows = nullptr;
#define Tile_SplitRows_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(Rows) { rows = atts[++i]; break; }
#define Tile_SplitRows_Create
#define Tile_SplitRows_Handle \
	oFunc func = {string("CCTile:splitRows(")+(time ? time : "0")+","+(rows ? rows : "0")+")",""};\
	funcs.push(func);
#define Tile_SplitRows_Finish

// Tile.TurnOff
#define Tile_TurnOff_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;
#define Tile_TurnOff_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }
#define Tile_TurnOff_Create
#define Tile_TurnOff_Handle \
	oFunc func = {string("CCTile:turnOff(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"))",""};\
	funcs.push(func);
#define Tile_TurnOff_Finish

// Tile.Waves3D
#define Tile_Waves3D_Define \
	Object_Define\
	const char* time = nullptr;\
	const char* gridX = nullptr;\
	const char* gridY = nullptr;\
	const char* waves = nullptr;\
	const char* amplitude = nullptr;
#define Tile_Waves3D_Check \
	Object_Check\
	CASE_STR(Time) { time = atts[++i]; break; }\
	CASE_STR(GridX) { gridX = atts[++i]; break; }\
	CASE_STR(GridY) { gridY = atts[++i]; break; }\
	CASE_STR(Waves) { waves = atts[++i]; break; }\
	CASE_STR(Amplitude) { amplitude = atts[++i]; break; }
#define Tile_Waves3D_Create
#define Tile_Waves3D_Handle \
	oFunc func = {string("CCTile:waves3D(")+(time ? time : "0")+\
	",CCSize("+(gridX ? gridX : "0")+","+(gridY ? gridY : "0")+"),"+\
	(waves ? waves : "0")+","+(amplitude ? amplitude : "0")+")",""};\
	funcs.push(func);
#define Tile_Waves3D_Finish

// Sequence
#define Sequence_Define \
	Object_Define
#define Sequence_Check \
	Object_Check
#define Sequence_Create
#define Sequence_Handle \
	items.push("Sequence");
#define Sequence_Finish

// Spawn
#define Spawn_Define \
	Object_Define
#define Spawn_Check \
	Object_Check
#define Spawn_Create
#define Spawn_Handle \
	items.push("Spawn");
#define Spawn_Finish

// Data
#define Data_Define \
	Object_Define
#define Data_Check \
	Object_Check
#define Data_Create \
	stream << "local " << self << " = CCDictionary()\n";
#define Data_Handle
#define Data_Finish \
	if (!elementStack.empty()) {\
		const oItem& parent = elementStack.top();\
		stream << parent.name << ".data = " << self << "\n\n";\
	}

// Listener
#define Listener_Define \
	Object_Define\
	const char* event = nullptr;
#define Listener_Check \
	Object_Check\
	CASE_STR(Event) { event = atts[++i]; break; }
#define Listener_Create
#define Listener_Handle \
	oFunc func = {string("oListener(\"") + event + "\",",")"};\
	funcs.push(func);
#define Listener_Finish

#define Add_To_Parent \
	if (!elementStack.empty()) {\
		const oItem& parent = elementStack.top();\
		stream << parent.name << ":addChild(" << self;\
		if (zOrder) {\
			stream << ',' << zOrder;\
			if (tag) stream << ',' << tag;\
		}\
		else if (tag) stream << ",0," << tag;\
		stream << ")\n\n";\
	}

// Node
#define Node_Define \
	Object_Define\
	const char* width = nullptr;\
	const char* height = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* z = nullptr;\
	const char* anchorX = nullptr;\
	const char* anchorY = nullptr;\
	const char* passColor = nullptr;\
	const char* passOpacity = nullptr;\
	const char* color = nullptr;\
	const char* opacity = nullptr;\
	const char* angle = nullptr;\
	const char* scaleX = nullptr;\
	const char* scaleY = nullptr;\
	const char* scheduler = nullptr;\
	const char* skewX = nullptr;\
	const char* skewY = nullptr;\
	const char* zOrder = nullptr;\
	const char* tag = nullptr;\
	const char* transformTarget = nullptr;\
	const char* visible = nullptr;
#define Node_Check \
	Object_Check\
	CASE_STR(Width) { width = atts[++i]; break; }\
	CASE_STR(Height) { height = atts[++i]; break; }\
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Z) { z = atts[++i]; break; }\
	CASE_STR(AnchorX) { anchorX = atts[++i]; break; }\
	CASE_STR(AnchorY) { anchorY = atts[++i]; break; }\
	CASE_STR(PassColor) { passColor = atts[++i]; break; }\
	CASE_STR(PassOpacity) { passOpacity = atts[++i]; break; }\
	CASE_STR(Color) { color = atts[++i]; break; }\
	CASE_STR(Opacity) { opacity = atts[++i]; break; }\
	CASE_STR(Angle) { angle = atts[++i]; break; }\
	CASE_STR(ScaleX) { scaleX = atts[++i]; break; }\
	CASE_STR(ScaleY) { scaleY = atts[++i]; break; }\
	CASE_STR(Scheduler) { scheduler = atts[++i]; break; }\
	CASE_STR(SkewX) { skewX = atts[++i]; break; }\
	CASE_STR(SkewY) { skewY = atts[++i]; break; }\
	CASE_STR(ZOrder) { zOrder = atts[++i]; break; }\
	CASE_STR(Tag) { tag = atts[++i]; break; }\
	CASE_STR(TransformTarget) { transformTarget = atts[++i]; break; }\
	CASE_STR(Visible) { visible = atts[++i]; break; }
#define Node_Create \
	stream << "local " << self << " = CCNode()\n";
#define Node_Handle \
	if (anchorX && anchorY) stream << self << ".anchor = oVec2(" << anchorX << ',' << anchorY << ")\n";\
	else if (anchorX && !anchorY) stream << self << ".anchor = oVec2(" << anchorX << ',' << self << ".anchor.y)\n";\
	else if (!anchorX && anchorY) stream << self << ".anchor = oVec2(" << self << ".anchor.x," << anchorY << ")\n";\
	if (x) stream << self << ".positionX = " << x << '\n';\
	if (y) stream << self << ".positionY = " << y << '\n';\
	if (z) stream << self << ".positionZ = " << z << '\n';\
	if (passColor) stream << self << ".cascadeColor = " << passColor << '\n';\
	if (passOpacity) stream << self << ".cascadeOpacity = " << passOpacity << '\n';\
	if (color) stream << self << ".color = ccColor3(" << color << ")\n";\
	if (opacity) stream << self << ".opacity = " << opacity << '\n';\
	if (angle) stream << self << ".angle = " << angle << '\n';\
	if (scaleX) stream << self << ".scaleX = " << scaleX << '\n';\
	if (scaleY) stream << self << ".scaleY = " << scaleY << '\n';\
	if (scheduler) stream << self << ".scheduler = " << scheduler << '\n';\
	if (skewX) stream << self << ".skewX = " << skewX << '\n';\
	if (skewY) stream << self << ".skewY = " << skewY << '\n';\
	if (transformTarget) stream << self << ".transformTarget = " << transformTarget << '\n';\
	if (visible) stream << self << ".visible = " << visible << '\n';\
	if (width && height) stream << self << ".contentSize = CCSize(" << width << ',' << height << ")\n";\
	else if (width && !height) stream << self << ".contentSize = CCSize(" << width << ',' << self << ".contentSize.height)\n";\
	else if (!width && height) stream << self << ".contentSize = CCSize(" << self << ".contentSize.width," << height << ")\n";
#define Node_Finish \
	Add_To_Parent

// Node3D
#define Node3D_Define \
	Node_Define\
	const char* angleX = nullptr;\
	const char* angleY = nullptr;
#define Node3D_Check \
	Node_Check\
	CASE_STR(AngleX) { angleX = atts[++i]; break; }\
	CASE_STR(AngleY) { angleY = atts[++i]; break; }
#define Node3D_Create \
	stream << "local " << self << " = oNode3D()\n";
#define Node3D_Handle \
	Node_Handle\
	if (angleX) stream << self << ".angleX = " << angleX << '\n';\
	if (angleY) stream << self << ".angleY = " << angleY << '\n';
#define Node3D_Finish \
	Add_To_Parent

// Scene
#define Scene_Define \
	Node_Define
#define Scene_Check \
	Node_Check
#define Scene_Create \
	stream << "local " << self << " = CCScene()\n";
#define Scene_Handle \
	Node_Handle
#define Scene_Finish \
	stream << '\n';

// DrawNode
#define DrawNode_Define \
	Node_Define
#define DrawNode_Check \
	Node_Check
#define DrawNode_Create \
	stream << "local " << self << " = CCDrawNode()\n";
#define DrawNode_Handle \
	Node_Handle
#define DrawNode_Finish \
	Add_To_Parent

// DrawNode.Dot
#define Dot_Define \
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* radius = nullptr;\
	const char* color = nullptr;
#define Dot_Check \
	CASE_STR(X) { x = atts[++i]; break; }\
	CASE_STR(Y) { y = atts[++i]; break; }\
	CASE_STR(Radius) { radius = atts[++i]; break; }\
	CASE_STR(Color) { color = atts[++i]; break; }
#define Dot_Finish \
	if (!elementStack.empty())\
	{\
		stream << elementStack.top().name <<\
		":drawDot(oVec2(" << (x ? x : "0") << ',' << (y ? y : "0") << ")," <<\
		(radius ? radius : "0") << ",ccColor4(" << (color ? color : "") << "))\n\n";\
	}

// DrawNode.Polygon
#define Polygon_Define \
	const char* fillColor = nullptr;\
	const char* borderWidth = nullptr;\
	const char* borderColor = nullptr;
#define Polygon_Check \
	CASE_STR(FillColor) { fillColor = atts[++i]; break; }\
	CASE_STR(BorderWidth) { borderWidth = atts[++i]; break; }\
	CASE_STR(BorderColor) { borderColor = atts[++i]; break; }
#define Polygon_Finish \
	if (!elementStack.empty())\
	{\
		oFunc func = {elementStack.top().name+":drawPolygon({",\
		string("},ccColor4(")+(fillColor ? fillColor : "")+"),"+(borderWidth ? borderWidth : "0")+",ccColor4("+(borderColor ? borderColor : "")+"))\n\n"};\
		funcs.push(func);\
		items.push("Polygon");\
	}

// DrawNode.Segment
#define Segment_Define \
	const char* beginX = nullptr;\
	const char* beginY = nullptr;\
	const char* endX = nullptr;\
	const char* endY = nullptr;\
	const char* radius = nullptr;\
	const char* color = nullptr;
#define Segment_Check \
	CASE_STR(X1) { beginX = atts[++i]; break; }\
	CASE_STR(Y1) { beginY = atts[++i]; break; }\
	CASE_STR(X2) { endX = atts[++i]; break; }\
	CASE_STR(Y2) { endY = atts[++i]; break; }\
	CASE_STR(Radius) { radius = atts[++i]; break; }\
	CASE_STR(Color) { color = atts[++i]; break; }
#define Segment_Finish \
	if (!elementStack.empty())\
	{\
		stream << elementStack.top().name <<\
		":drawSegment(oVec2(" << (beginX ? beginX : "0") << ',' << (beginY ? beginY : "0") << "),oVec2(" <<\
		(endX ? endX : "0") << ',' << (endY ? endY : "0") << ")," << (radius ? radius : "0.5") << ",ccColor4(" <<\
		(color ? color : "") << "))\n\n";\
	}

// Line
#define Line_Define \
	Node_Define
#define Line_Check \
	Node_Check
#define Line_Create \
	stream << "local " << self << " = oLine()\n";
#define Line_Handle \
	Node_Handle
#define Line_Finish \
	Add_To_Parent\
	oFunc func = {string(self)+":set({","})\n\n"};\
	funcs.push(func);\
	items.push("Line");

// ClipNode
#define ClipNode_Define \
	Node_Define\
	const char* alphaThreshold = nullptr;\
	const char* inverted = nullptr;\
	const char* stencil = nullptr;
#define ClipNode_Check \
	Node_Check\
	CASE_STR(AlphaThreshold) { alphaThreshold = atts[++i]; break; }\
	CASE_STR(Inverted) { inverted = atts[++i]; break; }\
	CASE_STR(Stencil) { stencil = atts[++i]; break; }
#define ClipNode_Create \
	stream << "local " << self << " = CCClipNode(" << (stencil ? stencil : "Stencil") << ")\n";
#define ClipNode_Handle \
	Node_Handle\
	if (alphaThreshold) stream << self << ".alphaThreshold = " << alphaThreshold << '\n';\
	if (inverted) stream << self << ".inverted = " << inverted << '\n';
#define ClipNode_Finish \
	Add_To_Parent

// LabelAtlas
#define LabelAtlas_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fntFile = nullptr;
#define LabelAtlas_Check \
	Node_Check\
	CASE_STR(Text) { text = atts[++i]; break; }\
	CASE_STR(File) { fntFile = atts[++i]; break; }
#define LabelAtlas_Create \
	stream << "local " << self << " = CCLabelAtlas(\"" << (text ? text : "\"") << ',';\
	if (fntFile) stream << '\"' << fntFile << '\"';\
	else stream << "";\
	stream << ")\n";
#define LabelAtlas_Handle \
	Node_Handle
#define LabelAtlas_Finish \
	Add_To_Parent

// LabelBMFont
#define LabelBMFont_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fntFile = nullptr;\
	const char* fontWidth = nullptr;\
	const char* alignment = nullptr;\
	const char* imageOffset = nullptr;
#define LabelBMFont_Check \
	Node_Check\
	CASE_STR(Text) { text = atts[++i]; break; }\
	CASE_STR(File) { fntFile = atts[++i]; break; }\
	CASE_STR(FontWidth) { fontWidth = atts[++i]; break; }\
	CASE_STR(Alignment) { alignment = atts[++i]; break; }\
	CASE_STR(ImageOffset) { imageOffset = atts[++i]; break; }
#define LabelBMFont_Create \
	stream << "local " << self << " = CCLabelBMFont(\"" << (text ? text : "\"");\
	if (fntFile) stream << "\"," << fntFile << '\"';\
	else stream << ",";\
	stream << ',' << (fontWidth ? fontWidth : "CCLabelBMFont.AutomaticWidth") << ",CCTextAlign." << (alignment ? alignment : "HLeft") << ',' << (imageOffset ? imageOffset : "oVec2.zero") << ")\n";
#define LabelBMFont_Handle \
	Node_Handle
#define LabelBMFont_Finish \
	Add_To_Parent

// LabelTTF
#define LabelTTF_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fontName = nullptr;\
	const char* fontSize = nullptr;
#define LabelTTF_Check \
	Node_Check\
	CASE_STR(Text) { text = atts[++i]; break; }\
	CASE_STR(FontName) { fontName = atts[++i]; break; }\
	CASE_STR(FontSize) { fontSize = atts[++i]; break; }
#define LabelTTF_Create \
	stream << "local " << self << " = CCLabelTTF(\"" << (text ? text : "") << "\",\"" << (fontName ? fontName : "Arial") << "\"," << (fontSize ? fontSize : "12") << ")\n";
#define LabelTTF_Handle \
	Node_Handle
#define LabelTTF_Finish \
	Add_To_Parent

// Sprite
#define Sprite_Define \
	Node_Define\
	const char* file = nullptr;\
	const char* flipX = nullptr;\
	const char* flipY = nullptr;\
	const char* blendFuncSrc = nullptr;\
	const char* blendFuncDst = nullptr;
#define Sprite_Check \
	Node_Check\
	CASE_STR(File) { file = atts[++i]; break; }\
	CASE_STR(FlipX) { flipX = atts[++i]; break; }\
	CASE_STR(FlipY) { flipY = atts[++i]; break; }\
	CASE_STR(BlendSrc) { blendFuncSrc = atts[++i]; break; }\
	CASE_STR(BlendDst) { blendFuncDst = atts[++i]; break; }
#define Sprite_Create \
	stream << "local " << self << " = CCSprite(";\
	if (file) stream << '\"' << file << "\")\n";\
	else stream << ")\n";
#define Sprite_Handle \
	Node_Handle\
	if (flipX) stream << self << ".flipX = " << flipX << '\n';\
	if (flipY) stream << self << ".flipY = " << flipY << '\n';\
	if (blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ",ccBlendFunc." << blendFuncDst << ")\n";\
	else if (blendFuncSrc && !blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ',' << self << ".blendFunc.dst)\n";\
	else if (!blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(" << self\
									<< ".blendFunc.src,ccBlendFunc." << blendFuncDst << ")\n";
#define Sprite_Finish \
	Add_To_Parent

// SpriteBatch
#define SpriteBatch_Define \
	Node_Define\
	const char* file = nullptr;
#define SpriteBatch_Check \
	Node_Check\
	CASE_STR(File) { file = atts[++i]; break; }
#define SpriteBatch_Create \
	stream << "local " << self << " = CCSpriteBatchNode(\"" << (file ? file : "") << "\")\n";
#define SpriteBatch_Handle \
	Node_Handle
#define SpriteBatch_Finish \
	Add_To_Parent

// Layer
#define Layer_Define \
	Node_Define\
	const char* accelerometerEnabled = nullptr;\
	const char* keypadEnabled = nullptr;\
	const char* touchEnabled = nullptr;\
	const char* touchMode = nullptr;
#define Layer_Check \
	Node_Check\
	CASE_STR(AccelerometerEnabled) { accelerometerEnabled = atts[++i]; break; }\
	CASE_STR(KeypadEnabled) { keypadEnabled = atts[++i]; break; }\
	CASE_STR(TouchEnabled) { touchEnabled = atts[++i]; break; }\
	CASE_STR(TouchMode) { touchMode = atts[++i]; break; }\
	CASE_STR(TouchPriority) { touchPriority = atts[++i]; break; }\
	CASE_STR(MultiTouch) { isMultiTouches = atts[++i]; break; }\
	CASE_STR(SwallowTouch) { swallowsTouches = atts[++i]; break; }
#define Layer_Create \
	stream << "local " << self << " = CCLayer()\n";
#define Layer_Handle \
	Node_Handle\
	if (accelerometerEnabled) stream << self << ".accelerometerEnabled = " << accelerometerEnabled << '\n';\
	if (keypadEnabled) stream << self << ".keypadEnabled = " << keypadEnabled << '\n';\
	if (touchEnabled) stream << self << ".touchEnabled = " << touchEnabled << '\n';\
	if (touchMode) stream << self << ".touchMode = CCLayer.Touches" << touchMode << '\n';
#define Layer_Finish \
	Add_To_Parent

// LayerColor
#define LayerColor_Define \
	Layer_Define\
	const char* blendFuncSrc = nullptr;\
	const char* blendFuncDst = nullptr;
#define LayerColor_Check \
	Layer_Check\
	CASE_STR(BlendSrc) { blendFuncSrc = atts[++i]; break; }\
	CASE_STR(BlendDst) { blendFuncDst = atts[++i]; break; }
#define LayerColor_Create \
	stream << "local " << self << " = CCLayerColor(ccColor4(" << (color ? color : "") << "))\n";\
	color = nullptr;
#define LayerColor_Handle \
	Layer_Handle\
	if (blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ",ccBlendFunc." << blendFuncDst << ")\n";\
	else if (blendFuncSrc && !blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ',' << self << ".blendFunc.dst)\n";\
	else if (!blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(" << self\
									<< ".blendFunc.src,ccBlendFunc." << blendFuncDst << ")\n";
#define LayerColor_Finish \
	Add_To_Parent

// LayerGradient
#define LayerGradient_Define \
	LayerColor_Define\
	const char* start = nullptr;\
	const char* end = nullptr;\
	const char* vectorX = nullptr;\
	const char* vectorY = nullptr;
#define LayerGradient_Check \
	LayerColor_Check\
	CASE_STR(StartColor) { start = atts[++i]; break; }\
	CASE_STR(EndColor) { end = atts[++i]; break; }\
	CASE_STR(VectorX) { vectorX = atts[++i]; break; }\
	CASE_STR(VectorY) { vectorY = atts[++i]; break; }
#define LayerGradient_Create \
	stream << "local " << self << " = CCLayerGradient(";\
	if (!start || !start[0]) start = "0xffffffff";\
	if (!end || !end[0]) end = "0xffffffff";\
	if (!vectorX || !vectorX[0]) vectorX = "0";\
	if (!vectorY || !vectorY[0]) vectorY = "0.5";\
	stream << start << ',' << end << ',' << "oVec2(" << vectorX << ',' << vectorY << ")\n";
#define LayerGradient_Handle \
	LayerColor_Handle
#define LayerGradient_Finish \
	Add_To_Parent

// Menu
#define Menu_Define \
	Layer_Define\
	const char* enabled = nullptr;
#define Menu_Check \
	Layer_Check\
	CASE_STR(Enabled) { enabled = atts[++i]; break; }
#define Menu_Create \
	stream << "local " << self << " = CCMenu(" << (swallowsTouches ? swallowsTouches : "") << ")\n";\
	swallowsTouches = nullptr;
#define Menu_Handle \
	Layer_Handle\
	if (enabled) stream << self << ".enabled = " << enabled << '\n';
#define Menu_Finish \
	Add_To_Parent

// MenuItem
#define MenuItem_Define \
	Node_Define\
	const char* enabled = nullptr;
#define MenuItem_Check \
	Node_Check\
	CASE_STR(Enabled) { enabled = atts[++i]; break; }
#define MenuItem_Create \
	stream << "local " << self << " = CCMenuItem()\n";
#define MenuItem_Handle \
	Node_Handle\
	if (enabled) stream << self << ".enabled = " << enabled << '\n';
#define MenuItem_Finish \
	Add_To_Parent

// World
#define World_Define \
	Node_Define\
	const char* gravityX = nullptr;\
	const char* gravityY = nullptr;\
	const char* showDebug = nullptr;\
	const char* velocityIter = nullptr;\
	const char* positionIter = nullptr;
#define World_Check \
	Node_Check\
	CASE_STR(GravityX) { gravityX = atts[++i]; break; }\
	CASE_STR(GravityY) { gravityY = atts[++i]; break; }\
	CASE_STR(ShowDebug) { showDebug = atts[++i]; break; }\
	CASE_STR(VelocityIter) { velocityIter = atts[++i]; break; }\
	CASE_STR(PositionIter) { positionIter = atts[++i]; break; }
#define World_Create \
	stream << "local " << self << " = oWorld()\n";
#define World_Handle \
	Node_Handle\
	if (gravityX && gravityY) stream << self << ".gravity = oVec2("\
									<< gravityX << ',' << gravityY << ")\n";\
	else if (gravityX && !gravityY) stream << self << ".gravity = oVec2("\
									<< gravityX << ',' << self << ".gravity.y)\n";\
	else if (!gravityX && gravityY) stream << self << ".gravity = oVec2(" << self\
									<< ".gravity.x," << gravityY << ")\n";\
	if (showDebug) stream << self << ".showDebug = " << showDebug << '\n';\
	if (velocityIter || positionIter) stream << self << ":setIterations(" << (velocityIter ? velocityIter : "8")\
											<< ',' << (positionIter ? positionIter : "3") << ")\n";
#define World_Finish \
	Add_To_Parent

// PlatformWorld
#define PlatformWorld_Define \
	World_Define
#define PlatformWorld_Check \
	World_Check
#define PlatformWorld_Create \
	stream << "local " << self << " = oPlatformWorld()\n";
#define PlatformWorld_Handle \
	World_Handle
#define PlatformWorld_Finish \
	Add_To_Parent

// World.Contact
#define Contact_Define \
	const char* groupA = nullptr;\
	const char* groupB = nullptr;\
	const char* enabled = nullptr;
#define Contact_Check \
	CASE_STR(GroupA) { groupA = atts[++i]; break; }\
	CASE_STR(GroupB) { groupB = atts[++i]; break; }\
	CASE_STR(Enabled) { enabled = atts[++i]; break; }
#define Contact_Finish \
	if (!elementStack.empty())\
	{\
		stream << elementStack.top().name <<\
		":setShouldContact(" << (groupA ? groupA : "") << ',' << (groupB ? groupB : "") << ',' <<\
		(enabled ? enabled : "") << ")\n\n";\
	}

// Model
#define Model_Define \
	Node_Define\
	const char* filename = nullptr;\
	const char* look = nullptr;\
	const char* loop = nullptr;\
	const char* play = nullptr;\
	const char* faceRight = nullptr;\
	const char* speed = nullptr;
#define Model_Check \
	Node_Check\
	CASE_STR(File) { filename = atts[++i]; break; }\
	CASE_STR(Look) { look = atts[++i]; break; }\
	CASE_STR(Loop) { loop = atts[++i]; break; }\
	CASE_STR(Play) { play = atts[++i]; break; }\
	CASE_STR(FaceRight) { faceRight = atts[++i]; break; }\
	CASE_STR(Speed) { speed = atts[++i]; break; }
#define Model_Create \
	stream << "local " << self << " = oModel(\"" << (filename ? filename : "") << "\")\n";
#define Model_Handle \
	Node_Handle\
	if (look) stream << self << ".look = \"" << look << "\"\n";\
	if (loop) stream << self << ".loop = " << loop << '\n';\
	if (play) stream << self << ":play(\"" << play << "\")\n";\
	if (faceRight) stream << self << ".faceRight = " << faceRight << '\n';\
	if (speed) stream << self << ".speed = " << speed << '\n';
#define Model_Finish \
	Add_To_Parent

// Body
#define Body_Define \
	Node_Define\
	const char* filename = nullptr;\
	const char* group = nullptr;\
	const char* world = nullptr;
#define Body_Check \
	Node_Check\
	CASE_STR(File) { filename = atts[++i]; break; }\
	CASE_STR(Group) { group = atts[++i]; break; }\
	CASE_STR(World) { world = atts[++i]; break; }
#define Body_Create \
	stream << "local " << self << " = oBody(\"" << (filename ? filename : "")\
			<< "\"," << (world ? world : "") << ",oVec2(" << (x ? x : "0") << ',' << (y ? y : "0") << "),"\
			<< (angle ? angle : "0") << ")\n";\
	x = y = angle = nullptr;
#define Body_Handle \
	Node_Handle\
	if (group) stream << self << ".group = " << group << '\n';
#define Body_Finish \
	Add_To_Parent

#define Item_Define(name) name##_Define
#define Item_Loop(name) \
	for (int i = 0; atts[i] != nullptr; i++)\
	{\
		SWITCH_STR_START(atts[i])\
		{\
			name##_Check\
		}\
		SWITCH_STR_END\
	}
#define Item_Create(name) name##_Create
#define Item_Handle(name) name##_Handle
#define Item_Push(name) name##_Finish;oItem item = {#name,self};elementStack.push(item);

#define Item(name,var) \
	CASE_STR(name)\
	{\
		Item_Define(name)\
		Item_Loop(name)\
		Self_Check(var)\
		Item_Create(name)\
		Item_Handle(name)\
		Item_Push(name)\
		break;\
	}

#define CASE_STR_DOT(prename,name) __CASE_STR1(#prename"."#name, prename##name)
#define ItemDot_Push(prename,name) prename##_##name##_Finish;oItem item = {#prename"."#name,self};elementStack.push(item);
#define ItemDot(prename,name,var) \
	CASE_STR_DOT(prename,name)\
	{\
		Item_Define(prename##_##name)\
		Item_Loop(prename##_##name)\
		Self_Check(var)\
		Item_Create(prename##_##name)\
		Item_Handle(prename##_##name)\
		ItemDot_Push(prename,name)\
		break;\
	}

class oXmlDelegate : public CCSAXDelegator
{
public:
	oXmlDelegate():
	codes(nullptr),
	currentKey(nullptr),
	touchPriority(nullptr),
	isMultiTouches(nullptr),
	swallowsTouches(nullptr),
	priority(nullptr)
	{ }
	virtual void startElement(void *ctx, const char *name, const char **atts);
	virtual void endElement(void *ctx, const char *name);
	virtual void textHandler(void *ctx, const char *s, int len);
public:
	void clear()
	{
		currentKey = nullptr;
		codes = nullptr;
		for (; !elementStack.empty(); elementStack.pop());
		for (; !funcs.empty(); funcs.pop());
		for (; !items.empty(); items.pop());
		stream.clear();
		stream.str("");
		names.clear();
		firstItem.clear();
	}
	void begin()
	{
		oXmlDelegate::clear();
		stream <<
		"return function(data)\n"
			"if data then\n"
				"local _,dorothy = Dorothy()\n"
				"setmetatable(data,{__index=dorothy})\n"
				"setfenv(1,data)\n"
			"else\n"
				"setfenv(Dorothy())\n"
			"end\n\n";
	}
	void end()
	{
		stream << "\nreturn " << firstItem << "\n\nend";
	}
	string getResult()
	{
		return stream.str();
	}
private:
	string getUsableName(const char* baseName)
	{
		char number[7];// max number can only have 6 digits
		int index = 1;
		string base(baseName);
		string name;
		do
		{
			sprintf(number,"%d",index);
			name = base + number;
			auto it = names.find(name);
			if (it == names.end()) break;
			else index++;
		} 
		while (true);
		return name;
	}
private:
	struct oItem
	{
		const char* type;
		string name;
	};
	struct oFunc
	{
		string begin;
		string end;
	};
	// Script
	const char* codes;
	// Data
	const char* currentKey;
	// Layer
	const char* touchPriority;
	const char* isMultiTouches;
	const char* swallowsTouches;
	// Schedule
	const char* priority;
	// Loader
	string firstItem;
	stack<oFunc> funcs;
	stack<string> items;
	stack<oItem> elementStack;
	unordered_set<string> names;
	unordered_map<const char*, const char*> params;
	ostringstream stream;
};

void oXmlDelegate::startElement(void *ctx, const char *name, const char **atts)
{
	SWITCH_STR_START(name)
	{
		Item(Node, node)
		Item(Node3D, node3D)
		Item(Scene, scene)
		Item(DrawNode, drawNode)
		Item(Line, line)
		Item(Sprite, sprite)
		Item(SpriteBatch, spriteBatch)
		Item(Layer, layer)
		Item(LayerColor, layer)
		Item(LayerGradient, layer)
		Item(ClipNode, clipNode)
		Item(LabelAtlas, label)
		Item(LabelBMFont, label)
		Item(LabelTTF, label)
		Item(Menu, menu)
		Item(MenuItem, menuItem)

		Item(World, world)
		Item(PlatformWorld, world)
		Item(Model, model)
		Item(Body, body)

		Item(Data, data)

		Item(Listener, listener)
		Item(Speed, speed)

		Item(Delay, delay)
		Item(Scale, scale)
		Item(Move, move)
		Item(Rotate, rotate)
		Item(Opacity, opacity)
		Item(Skew, skew)
		Item(Roll, roll)
		Item(Jump, jump)
		Item(Bezier, bezier)
		Item(Blink, blink)
		Item(Tint, tint)
		Item(Show, show)
		Item(Hide, hide)
		Item(Flip, flip)
		Item(Call, call)
		Item(Orbit, orbit)

		Item(Sequence, sequence)
		Item(Spawn, spawn)
		Item(Loop, loop)
		Item(CardinalSpline, cardinalSpline)

		ItemDot(Grid,FlipX3D, gridFlipX3D)
		ItemDot(Grid,FlipY3D, gridFlipY3D)
		ItemDot(Grid,Lens3D, gridLens3D)
		ItemDot(Grid,Liquid, gridLiquid)
		ItemDot(Grid,Reuse, gridReuse)
		ItemDot(Grid,Ripple3D, gridRipple3D)
		ItemDot(Grid,Shaky3D, gridShaky3D)
		ItemDot(Grid,Stop, gridStop)
		ItemDot(Grid,Twirl, gridTwirl)
		ItemDot(Grid,Wave, gridWave)
		ItemDot(Grid,Wave3D, gridWave3D)

		ItemDot(Tile,FadeOut, tileFadeOut)
		ItemDot(Tile,Jump3D, tileJump3D)
		ItemDot(Tile,Shaky3D, tileShaky3D)
		ItemDot(Tile,Shuffle, tileShuffle)
		ItemDot(Tile,SplitCols, tileSplitCols)
		ItemDot(Tile,SplitRows, tileSplitRows)
		ItemDot(Tile,TurnOff, tileTurnOff)
		ItemDot(Tile,Waves3D, tileWaves3D)

		CASE_STR(Vec2)
		{
			Item_Define(Vec2)
			Item_Loop(Vec2)
			Item_Handle(Vec2)
			break;
		}
		CASE_STR(Schedule)
		{
			Item_Loop(Schedule)
			break;
		}
		CASE_STR(Dot)
		{
			Item_Define(Dot)
			Item_Loop(Dot)
			Dot_Finish
			break;
		}
		CASE_STR(Polygon)
		{
			Item_Define(Polygon)
			Item_Loop(Polygon)
			Polygon_Finish
			break;
		}
		CASE_STR(Segment)
		{
			Item_Define(Segment)
			Item_Loop(Segment)
			Segment_Finish
			break;
		}
		CASE_STR(Contact)
		{
			Item_Define(Contact)
			Item_Loop(Contact)
			Contact_Finish
			break;
		}
	}
	SWITCH_STR_END
}

void oXmlDelegate::endElement(void *ctx, const char *name)
{
	if (elementStack.empty()) return;
	oItem currentData = elementStack.top();
	if (strcmp(name, elementStack.top().type) == 0) elementStack.pop();
	bool parentIsData = !elementStack.empty() && strcmp(elementStack.top().type, "Data") == 0;

	SWITCH_STR_START(name)
	{
		CASE_STR(Listener)
		{
			oFunc func = funcs.top();
			funcs.pop();
			stream << "local " << currentData.name << " = " << func.begin << (codes ? codes : "") << func.end << '\n';
			codes = nullptr;
			break;
		}
		CASE_STR(Script)
		{
			stream << (codes ? codes : "") << '\n';
			codes = nullptr;
			break;
		}
		CASE_STR(TouchHandler)
		{
			stream << currentData.name << ":registerTouchHandler(" << (codes ? codes : "")
				<< ',' << (isMultiTouches ? isMultiTouches : "false")
				<< ',' << (touchPriority ? touchPriority : "0")
				<< ',' << (swallowsTouches ? swallowsTouches : "false") << ")\n";
			codes = nullptr;
			isMultiTouches = nullptr;
			touchPriority = nullptr;
			swallowsTouches = nullptr;
			break;
		}
		CASE_STR(AccelerateHandler)
		{
			stream << currentData.name << ":registerAccelerateHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
			break;
		}
		CASE_STR(KeypadHandler)
		{
			stream << currentData.name << ":registerKeypadHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
			break;
		}
		CASE_STR(NodeHandler)
		{
			stream << currentData.name << ":registerEventHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
			break;
		}
		CASE_STR(TapHandler)
		{
			stream << currentData.name << ":registerTapHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
			break;
		}
		CASE_STR(Schedule)
		{
			stream << currentData.name << ":schedule(" << (codes ? codes : "");
			if (priority) stream << ',' << priority;
			stream << ")\n";
			codes = nullptr;
			priority = nullptr;
			break;
		}
		CASE_STR(Call)
		{
			oFunc func = funcs.top();
			funcs.pop();
			string tempItem = func.begin + (codes ? codes : "") + func.end;
			if (parentIsData)
			{
				stream << "local " << currentData.name << " = " << tempItem << '\n';
			}
			else
			{
				items.push(tempItem);
				auto it = names.find(currentData.name);
				if (it != names.end()) names.erase(it);
			}
			break;
		}
		CASE_STR(Layer) goto FLAG_LAYER_BEGIN;
		CASE_STR(LayerColor) goto FLAG_LAYER_BEGIN;
		CASE_STR(LayerGradient) goto FLAG_LAYER_BEGIN;
		goto FLAG_LAYER_END;
		FLAG_LAYER_BEGIN:
		{
			if (touchPriority)
			{
				stream << currentData.name << ".touchPriority = " << touchPriority << '\n';
				touchPriority = nullptr;
			}
			break;
		}
		FLAG_LAYER_END:
		CASE_STR(Speed) goto FLAG_WRAP_ACTION_BEGIN;
		CASE_STR(Loop) goto FLAG_WRAP_ACTION_BEGIN;
		goto FLAG_WRAP_ACTION_END;
		FLAG_WRAP_ACTION_BEGIN:
		{
			oFunc func = funcs.top();
			funcs.pop();
			string tempItem = func.begin;
			if (items.top() != "")
			{
				tempItem += items.top();
				items.pop();
			}
			items.pop();
			tempItem += func.end;
			if (parentIsData)
			{
				stream << "local " << currentData.name << " = " << tempItem << '\n';
			}
			else
			{
				items.push(tempItem);
				auto it = names.find(currentData.name);
				if (it != names.end()) names.erase(it);
			}
			break;
		}
		FLAG_WRAP_ACTION_END:
		CASE_STR(Delay) goto FLAG_ACTION_BEGIN;
		CASE_STR(Scale) goto FLAG_ACTION_BEGIN;
		CASE_STR(Move) goto FLAG_ACTION_BEGIN;
		CASE_STR(Rotate) goto FLAG_ACTION_BEGIN;
		CASE_STR(Opacity) goto FLAG_ACTION_BEGIN;
		CASE_STR(Skew) goto FLAG_ACTION_BEGIN;
		CASE_STR(Roll) goto FLAG_ACTION_BEGIN;
		CASE_STR(Jump) goto FLAG_ACTION_BEGIN;
		CASE_STR(Bezier) goto FLAG_ACTION_BEGIN;
		CASE_STR(Blink) goto FLAG_ACTION_BEGIN;
		CASE_STR(Tint) goto FLAG_ACTION_BEGIN;
		CASE_STR(Show) goto FLAG_ACTION_BEGIN;
		CASE_STR(Hide) goto FLAG_ACTION_BEGIN;
		CASE_STR(Flip) goto FLAG_ACTION_BEGIN;
		CASE_STR(Orbit) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,FlipX3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,FlipY3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Lens3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Liquid) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Reuse) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Ripple3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Shaky3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Twirl) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Stop) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Wave) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Grid,Wave3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,FadeOut) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,Jump3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,Shaky3D) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,Shuffle) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,SplitCols) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,SplitRows) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,TurnOff) goto FLAG_ACTION_BEGIN;
		CASE_STR_DOT(Tile,Waves3D) goto FLAG_ACTION_BEGIN;
		goto FLAG_ACTION_END;
		FLAG_ACTION_BEGIN:
		{
			oFunc func = funcs.top();
			funcs.pop();
			if (parentIsData)
			{
				stream << "local " << currentData.name << " = " << func.begin << '\n';
			}
			else
			{
				items.push(func.begin);
				auto it = names.find(currentData.name);
				if (it != names.end()) names.erase(it);
			}
			break;
		}
		FLAG_ACTION_END:
		CASE_STR(Sequence) goto FLAG_ACTION_GROUP_BEGIN;
		CASE_STR(Spawn) goto FLAG_ACTION_GROUP_BEGIN;
		goto FLAG_ACTION_GROUP_END;
		FLAG_ACTION_GROUP_BEGIN:
		{
			string tempItem = string("CC") + name + "({";
			stack<string> tempStack;
			while (items.top() != name)
			{
				tempStack.push(items.top());
				items.pop();
			}
			items.pop();
			while (!tempStack.empty())
			{
				tempItem += tempStack.top();
				tempStack.pop();
				if (!tempStack.empty()) tempItem += ",";
			}
			tempItem += "})";
			if (parentIsData)
			{
				stream << "local " << currentData.name << " = " << tempItem << '\n';
			}
			else
			{
				items.push(tempItem);
				auto it = names.find(currentData.name);
				if (it != names.end()) names.erase(it);
			}
			break;
		}
		FLAG_ACTION_GROUP_END:
		CASE_STR(CardinalSpline)
		{
			oFunc func = funcs.top();
			funcs.pop();
			string tempItem = func.begin;
			stack<string> tempStack;
			while (items.top() != name)
			{
				tempStack.push(items.top());
				items.pop();
			}
			items.pop();
			while (!tempStack.empty())
			{
				tempItem += tempStack.top();
				tempStack.pop();
				if (!tempStack.empty()) tempItem += ",";
			}
			tempItem += func.end;
			if (parentIsData)
			{
				stream << "local " << currentData.name << " = " << tempItem << '\n';
			}
			else
			{
				items.push(tempItem);
				auto it = names.find(currentData.name);
				if (it != names.end()) names.erase(it);
			}
			break;
		}
		CASE_STR(Polygon) goto FLAG_VEC2_CONTAINER_BEGIN;
		CASE_STR(Line) goto FLAG_VEC2_CONTAINER_BEGIN;
		goto FLAG_VEC2_CONTAINER_END;
		FLAG_VEC2_CONTAINER_BEGIN:
		{
			oFunc func = funcs.top();
			funcs.pop();
			stream << func.begin;
			stack<string> tempStack;
			while (items.top() != name)
			{
				tempStack.push(items.top());
				items.pop();
			}
			items.pop();
			while (!tempStack.empty())
			{
				stream << tempStack.top();
				tempStack.pop();
				if (!tempStack.empty()) stream << ',';
			}
			stream << func.end;
			break;
		}
		FLAG_VEC2_CONTAINER_END:
		break;
	}
	SWITCH_STR_END

	if (parentIsData)
	{
		const oItem& data = elementStack.top();
		stream << data.name << "[\"" << (currentKey ? currentKey : currentData.name.c_str()) << "\"] = " << currentData.name << "\n\n";
		currentKey = nullptr;
	}
}

void oXmlDelegate::textHandler(void *ctx, const char *s, int len)
{
	codes = s;
}

oXmlLoader::oXmlLoader():_delegate(new oXmlDelegate())
{
	_parser.setDelegator(_delegate);
}

oXmlLoader::~oXmlLoader()
{ }

string oXmlLoader::load(const char* filename)
{
	_delegate->begin();
	CCSAXParser::setHeaderHandler(oHandler);
	bool result = _parser.parse(filename);
	CCSAXParser::setHeaderHandler(nullptr);
	_delegate->end();
	return result ? _delegate->getResult() : string();
}

string oXmlLoader::load(const string& xml)
{
	_delegate->begin();
	CCSAXParser::setHeaderHandler(oHandler);
	bool result = _parser.parse(xml.c_str(), (unsigned int)xml.size());
	CCSAXParser::setHeaderHandler(nullptr);
	_delegate->end();
	return result ? _delegate->getResult() : string();
}
