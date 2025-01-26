topic "2 - CoordinateConverter";
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[2 $$0,0#00000000000000000000000000000000:Default]
[{_} 
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 Coordinate Data Types]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:TypeScreenCoord: [@(0.0.255) typedef]_[_^int32^ Upp`::int32]_
[* TypeScreenCoord]&]
[s2;%% Type used for [*@3 physical ]coordinates : the ones used for 
screen positions (pixels)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:PointScreen: [@(0.0.255) typedef] Point`_<TypeScreenCoord>
 [* PointScreen]&]
[s2;%% XY type used for [*@3 physical ]coordinates : the ones used for 
screen positions (pixels)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:RectScreen: [@(0.0.255) typedef] Rect`_<TypeScreenCoord> 
[* RectScreen]&]
[s2;%% Rect type used for [*@3 physical ]Rect: the ones used for screen 
positions (pixels)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord: [@(0.0.255) typedef]_[@(0.0.255) double]_[* Ty
peGraphCoord]&]
[s2;%% Type used for [*@3 logical ]coordinates : the same one as you`'re 
data, not pixels&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:PointGraph: [@(0.0.255) typedef] Point`_<TypeGraphCoord> 
[* PointGraph]&]
[s2;%% XY type used for [*@3 logical ]coordinates : the same one as 
you`'re data, not pixels&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:RectGraph: [@(0.0.255) typedef] Rect`_<TypeGraphCoord> 
[* RectGraph]&]
[s2;%% Rect type used for [*@3 logical ]Rect : the same one as you`'re 
data, not pixels&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 Class LinearConverter]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:LinearConverter`:`:class: [@(0.0.255)3 class][3 _][*3 LinearCo
nverter]&]
[s2;%% Helper class used to manage screen coordinate conversion. 
It does a linear conversion.&]
[s2;%% Also manages axis inversion&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 Class CoordinateConverter]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:class: [@(0.0.255)3 class][3 _][*3 Coor
dinateConverter]&]
[s2;%% Class dedicated to managing conversion between logical an 
physical coordinates in ONE axis. To manage X axis and Y axis, 
two different CoordinateConverter instances are needed.&]
[s2;%% the CoordinateConverter is responsible of :&]
[s2;i150;O0;%% Managing conversion To/Fromm Screen/Graph coordinates&]
[s2;i150;O0;%% Applying range limits&]
[s2;i150;O0;%% Defines Scroll/Zoom methods that apply all range testing&]
[s2;%% &]
[s2;%% It is the base class of all CoordinateConversion classes&]
[s2;%% `=`=> if you want a special conversion, you`'re class has 
to derive from CoordinateConverter&]
[s3;%% &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:IsInGraphVisibleRange`(TypeGraphCoord`)const: [@(0.0.255) b
ool]_[* IsInGraphVisibleRange]([_^topic`:`/`/GraphDraw`/src`/CoordinateConverter`$en`-us`#TypeGraphCoord`:`:typedef^ T
ypeGraphCoord]_[*@3 p])_[@(0.0.255) const]&]
[s2;%%  [%-*@3 p] : &]
[s2;%% [*@(128.0.255) TRUE ]: p is in graph range         `=`=> p is 
visible in plot.&]
[s2;%% [*@(128.0.255) FALSE ]: p is not in graphRange  `=`=> p is NOT 
visible in polt&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:AllowZoom`(bool`): [@(0.0.255) void
]_[* AllowZoom]([@(0.0.255) bool]_[*@3 p]_`=_[@(0.0.255) true])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:AllowAxisZoom`(bool`): [@(0.0.255) v
oid]_[* AllowAxisZoom]([@(0.0.255) bool]_[*@3 p]_`=_[@(0.0.255) true])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:AllowScroll`(bool`): [@(0.0.255) vo
id]_[* AllowScroll]([@(0.0.255) bool]_[*@3 p]_`=_[@(0.0.255) true])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:AllowAxisScroll`(bool`): [@(0.0.255) v
oid]_[* AllowAxisScroll]([@(0.0.255) bool]_[*@3 p]_`=_[@(0.0.255) true])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:IsZoomAllowed`(`)const: [@(0.0.255) b
ool]_[* IsZoomAllowed]()_[@(0.0.255) const]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:IsAxisZoomAllowed`(`)const: [@(0.0.255) b
ool]_[* IsAxisZoomAllowed]()_[@(0.0.255) const]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:IsScrollAllowed`(`)const: [@(0.0.255) b
ool]_[* IsScrollAllowed]()_[@(0.0.255) const]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:IsAxisScrollAllowed`(`)const: [@(0.0.255) b
ool]_[* IsAxisScrollAllowed]()_[@(0.0.255) const]&]
[s2;%% Zooming and scrolling are managed by GraphCtrl derived classes, 
but to have a common interface throughout all the GridCtrls made 
by users : zoom and Scroll authorisations are hosted by the CoordinateConverter 
class and made available through them.&]
[s2;%% [_ NB] : The internal data is not used in any way by CoordinateConverter 
class.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:MakeRestoreAxisMinMaxCB`(`): [_^Callback^ C
allback]_[* MakeRestoreAxisMinMaxCB]()&]
[s2;%% Returns a CallBack that, when executed, sets the axis Min/Max 
values to the current values&]
[s2;%% This is usefull for UNDO/REDO&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:UpdateScreenSize`(TypeScreenCoord`,TypeScreenCoord`): [@(0.0.255) i
nline void]_[* updateScreenSize](TypeScreenCoord_[*@3 screenMin], 
TypeScreenCoord_[*@3 screenMax])&]
[s2;%% Set screen size in pixels (physical coordinates).&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:UpdateGraphSize`(TypeGraphCoord`,TypeGraphCoord`): [@(0.0.255) i
nline void]_[* updateGraphSize](TypeGraphCoord_[*@3 graphMin], TypeGraphCoord_[*@3 grap
hMax])&]
[s2;%% Set the visible graphic size ( logical coordinates ).&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:applyRangeLimits`(TypeGraphCoord`): [@(0.0.255) v
irtual] TypeGraphCoord_[* applyRangeLimits](TypeGraphCoord_[*@3 v])&]
[s2;%% Apply logical range limits (in graph coordinates ) to the 
value V.&]
[s2;%% `=`=> If V is not in authorized range then it is modified 
to be in the range.&]
[s2;%% Returns the modified value&]
[s3;%% &]
[s4;%% &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:toScreen`(const TypeGraphCoord`)const: [@(0.0.255) v
irtual] TypeScreenCoord_[* toScreen](TypeGraphCoord_[*@3 v]) [@(0.0.255) const]&]
[s2;%% Convert [%-*@3 v] from logical coordinates to physical coordinates 
(pixels).&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:toScreen`(const TypeGraphCoord`)const: [@(0.0.255) v
irtual] TypeGraphCoord_[* toGraph](TypeScreenCoord_[*@3 v]) [@(0.0.255) const]&]
[s2;%% Convert [%-*@3 v] from physical coordinates (pixels) to logical 
coordinates.&]
[s3;%% &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s3; &]
[s3;%% &]
[s4; &]
[s0;%% ]]