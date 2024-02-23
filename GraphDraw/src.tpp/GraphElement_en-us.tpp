topic "1 - GraphElement class";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 Custom types]]}}&]
[s0; &]
[s0; &]
[s4; &]
[s9; [@(0.0.255) typedef_enum]_[*3 RefreshStrategy]&]
[s2;%% Used to indicate if refresh needs to be complete or partial 
(in order to be FAST).&]
[s2;%% This is usefull when accomplishing mouse move/resize and that 
the data is to big to get refreshed rapidly.&]
[s2;%% The values accepted are the following :&]
[s3; &]
[s5;i150;O0;:Upp`:`:GraphDraw`_ns`:`:REFRESH`_DEFAULT: [*@3 REFRESH`_DEFAULT]_`=_[@3 0] 
&]
[s5;i150;O0;:Upp`:`:GraphDraw`_ns`:`:REFRESH`_FAST:%% [%-*@3 REFRESH`_FAST][%-*  
: ]only partial PLOT DATA is draw (to be faster)&]
[s5;i150;O0;:Upp`:`:GraphDraw`_ns`:`:REFRESH`_FULL:%% [%-*@3 REFRESH`_FULL 
][%-* : ]everything is redrawn ( all the PLOT DATA is redrawn)&]
[s5;i150;O0;:Upp`:`:GraphDraw`_ns`:`:REFRESH`_KEEP`_DATA:%% [%-*@3 REFRESH`_KEEP`_DATA][%-*  
: ]PLOT DATA is not redrawn, it`'s buffered image is used instead 
to refresh the Graph&]
[s3; &]
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphElement]]}}&]
[s4; &]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:class: [@(0.0.255)3 class][3 _][*3 GraphElemen
t]&]
[s2;%% Base class used to implement all Graph Elements.&]
[s2;%% It manages all the common details&]
[s3; &]
[s4; &]
[s9; [@(0.0.255) typedef enum] [* ElementPosition ]`{&]
[s0; -|-|[*@(128.0.255) LEFT`_OF`_GRAPH]         `= 0x001,&]
[s0; -|-|[*@(128.0.255) RIGHT`_OF`_GRAPH]       `= 0x002,&]
[s0; -|-|[*@(128.0.255) TOP`_OF`_GRAPH]          `= 0x010,&]
[s0; -|-|[*@(128.0.255) BOTTOM`_OF`_GRAPH]  `= 0x020,&]
[s0; -|-|[*@(128.0.255) FLOAT`_OVER`_GRAPH] `= 0x100&]
[s0; -|`} ElementPosition;&]
[s3; &]
[s0; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Private Members List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:`_overlapPreviousElement: [@(0.0.255) bool
]_[* `_overlapPreviousElement]&]
[s2;%% &]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:AdjustToPlotRect`(const Upp`:`:GraphDraw`_ns`:`:RectScreen`&`): [@(0.0.255) v
oid]_[* AdjustToPlotRect]([@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:RectScreen^ Rec
tScreen][@(0.0.255) `&]_[*@3 plotRect])&]
[s2;%% [%-*@3 plotRect] : plot area Rect&]
[s2;%% Adjusts ElementFrame according to plotRect.&]
[s2;%% This method is called when all GraphElements have been added 
to the Graph, and finally, all elements need they`'re size to 
be adjusted.&]
[s2;%% NB: for [/@6 internal use only] `=`=> not to be used.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:Contains`(Upp`:`:GraphDraw`_ns`:`:PointScreen`)const: [@(0.0.255) v
irtual] [@(0.0.255) bool]_[* Contains]([_^Upp`:`:GraphDraw`_ns`:`:PointScreen^ PointScr
een]_[*@3 p])_[@(0.0.255) const]&]
[s2;%% [%-*@3 p] : position to test ( absolute position in whole GraphCtrl 
).&]
[s2;%% Returns TRUE if p is in the GraphElement. This is used to 
distribute events to the correct element according to mouse position.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:PrePaint`(int`): [@(0.0.255) virtual] 
[@(0.0.255) void]_[* PrePaint]([@(0.0.255) int]_[*@3 scale])&]
[s2;%% Called before the GraphElement get`'s painted.&]
[s2;%% It is intended to contain general painting prepapration actions 
: update, recalculations, ...&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:SetElementPos`(ElementPosition`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* SetElementPos](ElementPosition_[*@3 v])&]
[s2;%% Sets the position of the element `=`=> on which side of the 
Graph is positionned the GraphElement.&]
[s2;%% The allowed positions are checked according to the masks set 
using [%-* DisablePos() ][%- or][%-*  SetAllowedPosMask()].&]
[s2;%% Ex: allow only TOP and BOTTOM only for an X axis GraphElement.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:DisablePos`(int`): [@(0.0.255) void]_[* Disa
blePos](_[@(0.0.255) int]_[*@3 v]_)&]
[s2;%%  [%-*@3 v] : appends current [%- allowed positions ]mask .&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:SetAllowedPosMask`(int`): [@(0.0.255) void
]_[* SetAllowedPosMask](_[@(0.0.255) int]_[*@3 v]_)&]
[s2; [*@3  v][%%  : must be a combination of the ][* ElementPosition ]values.&]
[s2; Set the allowed positions mask.&]
[s2; Ex:   SetAllowedPosMask(BOTTOM`_OF`_GRAPH `| TOP`_OF`_GRAPH);&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:SetOverlapPrevious`(bool`): [@(0.0.255) vo
id]_[* SetOverlapPrevious](_[@(0.0.255) bool]_[*@3 v]_)&]
[s2; [%%  ][*@3 v :] if true, then this element will overlap previous 
GraphElement&]
[s2;%% Set this GraphElement to overlap previous Element (the one 
with lower stacking priority)&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:GetOverlapPrevious`(`)const: [@(0.0.255) b
ool]_[* GetOverlapPrevious]()_[@(0.0.255) const]&]
[s2;%% Returns overlap value&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:SetBackGroundStyle`(const Upp`:`:Value`&`): [@(0.0.255) v
oid]_[* SetBackGroundStyle](_[_^Value^ Value][@(0.0.255) `&]_[*@3 v])&]
[s0; -|`-`-`-`-`- TODO move this doc somewhere else `-`-`-`-&]
[s2;%% Sets the background style of the TickMark.&]
[s2;%% [%-*@3 s ]can be anything that is accepted by [^topic`:`/`/CtrlCore`/srcdoc`/AboutChameleon`$en`-us^ C
hameleon] ChPaint() method :&]
[s2;i150;O0;%% Color&]
[s2;i150;O0;%% Image (hot spots are used)&]
[s2;i150;O0;%% ...&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:PaintFloatElement`(Upp`:`:Draw`&`,int`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* PaintFloatElement]([_^Draw^ Draw][@(0.0.255) `&]_[*@3 dw], 
[@(0.0.255) int]_[*@3 scale])&]
[s2;%%  [%-*@3 dw ]:.&]
[s2;%%  [%-*@3 scale] :.&]
[s2;%% This method is called to paint the element [*@(128.0.255) WHEN 
it is FLOATING] (and only when it is floating). So if an element 
is not allowed to be flottable `=> no need to implement this 
method&]
[s2;%% Paints the graph element somewhere inside the ctrl area as 
a FLOATING element (legend, ...)&]
[s2;%% X/Y axis are not taken into account&]
[s2;%% [*@(128.0.255) Offset and clipping are set] with the `'`_floatFrame`' 
settings.&]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphElement Painting Details^ G
raphElement Painting Details] for more detailed explanations.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:PaintElement`(Upp`:`:Draw`&`,int`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* PaintElement]([_^Draw^ Draw][@(0.0.255) `&]_[*@3 dw], 
[@(0.0.255) int]_[*@3 scale])_`=_[@3 0]&]
[s2;%% [%-*@3 dw] : &]
[s2;%% [%-*@3 scale] : .&]
[s2;%% This method is called to paint the element [*@(128.0.255) WHEN 
it is NOT FLOATING]&]
[s2;%% Paints the element in his own area ( it is not dedicated to 
painting on plot area because only one axis is taken into account: 
either X or Y, another method exists for this purpose )&]
[s2;%% There is [*@(128.0.255) no clipping] `=`=> drawing can overlap 
plot or other elements&]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphElement Painting Details^ G
raphElement Painting Details] for more detailed explanations.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:PaintOnPlot`_underData`(Upp`:`:Draw`&`,int`,int`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* PaintOnPlot`_underData]([_^Draw^ Draw][@(0.0.255) `&]_[*@3 dw],
 [@(0.0.255) int]_[*@3 otherWidth], [@(0.0.255) int]_[*@3 scale])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:PaintOnPlot`_overData`(Upp`:`:Draw`&`,int`,int`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* PaintOnPlot`_overData]([_^Draw^ Draw][@(0.0.255) `&]_[*@3 dw],
 [@(0.0.255) int]_[*@3 otherWidth], [@(0.0.255) int]_[*@3 scale])&]
[s2;%%  [%-*@3 dw] :&]
[s2;%% [%-*@3 otherWidth] :&]
[s2;%% [%-*@3 scale] :&]
[s2;%% Draws additionnal  GraphElement element stuff on PLOT AREA 
: grids, square zones, ...anything you want.&]
[s2;%% This method is dedicated to painting on plotting area because 
both X/Y zoom/scroll are applied to the drawn data&]
[s2;%% [*@(128.0.255) Offset and clipping are set with the plot Rect] 
so nothing can be drawn outside.&]
[s2; [* PaintOnPlot`_underData() : ]draws under the data plot&]
[s2; [* PaintOnPlot`_overData() :  ] draws on top of the data plot&]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphElement Painting Details^ G
raphElement Painting Details] for more detailed explanations.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElement`:`:FitToData`(FitToDataStrategy`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* FitToData]([^topic`:`/`/GraphDraw`/src`/GraphElementFrame`$en`-us`#typedef^ F
itToDataStrategy]_[*@3 fitStrategy])&]
[s2;%%  [%-*@3 fitStrategy] .&]
[s2;%% Method dedicated to managing GridAxisDraw`::FitToData() direct 
access from GraphCtrl `=`=> unused for other GraphElement classes&]
[s3;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s0;%% &]
[s0;%% ]]