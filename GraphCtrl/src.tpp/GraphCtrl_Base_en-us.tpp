topic "GraphCtrl_Base";
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
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphCtrl`_Keys]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:struct: [@(0.0.255)3 struct][3 _][*3 GraphC
trl`_Keys]&]
[s2;%% Contains configurable [* keyboard masks] for the predefined 
actions : ZOOM, SCROLL, ...&]
[s2;%% A mask with value 0, will always be true: hence no keyboard 
key is necessary for action to be enabled.&]
[s2; [%% Default values are set by method : ][^topic`:`/`/GraphCtrl`/src`/GraphCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:Reset`(`)^ G
raphCtrl`_Keys`::Reset()]&]
[s2;^topic`:`/`/GraphCtrl`/src`/GraphCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:Reset`(`)^ &]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:Reset`(`): [@(0.0.255) static] 
[@(0.0.255) void] [* Reset]()&]
[s2;%% Set default keyboard mask values.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* `[Keyboard`] only actions masks]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_UNDO: [@(0.0.255) static] 
dword [* K`_KBD`_UNDO]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_REDO: [@(0.0.255) static] 
dword [* K`_KBD`_REDO]&]
[s2;%% Undo / Redo keyboard mask.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_SELECT`_CLEAR: [@(0.0.255) stat
ic] dword [* K`_KBD`_SELECT`_CLEAR]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_SELECT`_ALL: [@(0.0.255) static
] dword [* K`_KBD`_SELECT`_ALL]&]
[s2;%% Select all / Clear all select keyboard mask.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_LEFT`_SCROLL: [@(0.0.255) stati
c] dword [* K`_KBD`_LEFT`_SCROLL]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_RIGHT`_SCROLL: [@(0.0.255) stat
ic] dword [* K`_KBD`_RIGHT`_SCROLL]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_UP`_SCROLL: [@(0.0.255) static] 
dword [* K`_KBD`_UP`_SCROLL]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_KBD`_DOWN`_SCROLL: [@(0.0.255) stati
c] dword [* K`_KBD`_DOWN`_SCROLL]&]
[s2;%% Graph up/down/left/wright scroll keyboard mask.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* `[Keyboard `+ mouse`] ][*@(0.0.255) on plot ][*_@(0.0.255) AND 
][*@(0.0.255) GraphElement][*  ][*@(0.0.255) areas][*  actions masks]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_SCROLL: [@(0.0.255) static] 
dword [* K`_SCROLL]&]
[s2;%% Scroll graph using mouse move keyboard mask.&]
[s2;%% Mask is used for actions in plot area AND in GraphElement 
areas (like on Axis for ex)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_ZOOM: [@(0.0.255) static] 
dword [* K`_PLOT`_ZOOM]&]
[s2;%% Zoom graph using mouse move keyboard mask..&]
[s2;%% Mask is used for actions in plot area AND in GraphElement 
areas (like on Axis for ex)&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* `[Keyboard `+ mouse`] ][*@(0.0.255) on plot area][*  actions 
masks]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_POINT`_SELECT`_REPLACE: [@(0.0.255) s
tatic] dword [* K`_PLOT`_POINT`_SELECT`_REPLACE]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_POINT`_SELECT`_APPEND: [@(0.0.255) s
tatic] dword [* K`_PLOT`_POINT`_SELECT`_APPEND]&]
[s2;%% Serie and Data selection on plot area keyboard mask.&]
[s2;%% Selection is done by [* mouse click on a point] on plot area.&]
[s2;%% Select can be done in `'append to current selection`' or replace 
current selection.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_AREA`_SELECT`_REPLACE`_INCLUDED: [@(0.0.255) s
tatic] dword [* K`_PLOT`_AREA`_SELECT`_REPLACE`_INCLUDED]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_AREA`_SELECT`_APPEND`_INCLUDED: [@(0.0.255) s
tatic] dword [* K`_PLOT`_AREA`_SELECT`_APPEND`_INCLUDED]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_AREA`_SELECT`_REPLACE`_INTERSECT: [@(0.0.255) s
tatic] dword [* K`_PLOT`_AREA`_SELECT`_REPLACE`_INTERSECT]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_PLOT`_AREA`_SELECT`_APPEND`_INTERSECT: [@(0.0.255) s
tatic] dword [* K`_PLOT`_AREA`_SELECT`_APPEND`_INTERSECT]&]
[s2;%% Serie and Data selection on plot area keyboard mask.&]
[s2;%% Selection is done by [* mouse select rect ]on plot area&]
[s2;%% Select can be done in :&]
[s2;i150;O0;%% `'append to current selection`' or replace current 
selection.&]
[s2;i150;O0;%% Select fully included data elements only (mainly data 
points)&]
[s2;i150;O0;%% Select all data elements that intersect.&]
[s2;_%% &]
[s2;%% [_ Note] : intersect/include is intended for to be used with 
user custom GraphSeries data (take a &]
[s2;%% look at the SimpleJobSerie in GraphCtrl`_Demo example)&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* `[Keyboard `+ mouse`] ][*@(0.0.255) on GraphElement][*  actions 
masks]]}}&]
[s4;*%% &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_GE`_AXIS`_SELECT: [@(0.0.255) static
] dword [* K`_GE`_AXIS`_SELECT ]  (not used for the moment)&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_GE`_AXIS`_ZOOM: [@(0.0.255) static] 
dword [* K`_GE`_AXIS`_ZOOM]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_GE`_AXIS`_SCROLL: [@(0.0.255) static
] dword [* K`_GE`_AXIS`_SCROLL]&]
[s2;%% Select, Zoom and Scroll on GraphElement keyboard mask.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_GE`_FLOAT`_RESIZE: [@(0.0.255) stati
c] dword [* K`_GE`_FLOAT`_RESIZE]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Keys`:`:K`_GE`_FLOAT`_MOVE: [@(0.0.255) static] 
dword [* K`_GE`_FLOAT`_MOVE]&]
[s2;%% keyboard mask.fot actions that can be applied to floating 
GraphElements (Legend for example) whitch can be moved on graph 
and resized to fit user needs&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphCtrl`_Base]]}}&]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 TYPES][3 , 
][@(0.0.255)3 class][3 _][*@4;3 DERIVED][3 , ][@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _
][*@4;3 TYPES2][3 , ][@(0.0.255)3 class][3 _DERIVED2>_][@(0.0.255)3 class][3 _][*@3;3 GRAPHDRAW
`_BASE`_CLASS][3 _>]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:class: [@(0.0.255) class]_[* GraphCtrl`_B
ase]_:_[@(0.0.255) public]_[*@3 GRAPHDRAW`_BASE`_CLASS]<[*@4 TYPES], 
[*@4 DERIVED]>, [@(0.0.255) public]_[*@3 Ctrl]&]
[s2;%% &]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:OpenPropertiesDlg`(`): [@(0.0.255) virt
ual] [@(0.0.255) void]_[* OpenPropertiesDlg]()&]
[s2;%% Default implementation of properties dialog.&]
[s2;%% This implementation requires GraphCtrl child classes to implement 
[* AddAllPropertiesTabs()] method.&]
[s2;%% The AddAllPropertiesTabs() method is not declared in GraphCtrl`_Base 
because the Style parameter [_ has to be fully known] in order 
to be exploited in the method. So AddAllPropertiesTabs() cannot 
be a virtual method of GraphCtrl`_Base.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:WhenBar: [_^Callback1^ Callback1]<Bar[@(0.0.255) `&
]>_[* WhenBar]&]
[s2;%% Is called when user requests the Plot context menu ( the one 
tied to the plot area not to a GraphElement )&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:AddPropertiesTab`(ElementPropertiesDlgInterface`:`:VList`&`,TabCtrl`&`,const String`,ELEMENT`&`,ESTYLE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT], [@(0.0.255) class]_[*@4 ESTYLE]>_[@(0.0.255) vo
id]_[* AddPropertiesTab]([_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:VList^ E
lementPropertiesDlgInterface`::VList][@(0.0.255) `&]_[*@3 elemPropDlgList], 
[_^Upp`:`:TabCtrl^ TabCtrl][@(0.0.255) `&]_[*@3 tabs], [@(0.0.255) const]_[_^Upp`:`:String^ S
tring]_[*@3 title]_, [*@4 ELEMENT][@(0.0.255) `&]_[*@3 e1], [*@4 ESTYLE][@(0.0.255) `&]_[*@3 st
1])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:AddPropertiesTab`(ElementPropertiesDlgInterface`:`:VList`&`,TabCtrl`&`,const String`,ELEMENT1`&`,ESTYLE1`&`,ELEMENT2`&`,ESTYLE2`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT1], [@(0.0.255) class]_[*@4 ESTYLE1], 
[@(0.0.255) class]_[*@4 ELEMENT2], [@(0.0.255) class]_[*@4 ESTYLE2]>_[@(0.0.255) void]_[* Add
PropertiesTab]([_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:VList^ E
lementPropertiesDlgInterface`::VList][@(0.0.255) `&]_[*@3 elemPropDlgList], 
[_^Upp`:`:TabCtrl^ TabCtrl][@(0.0.255) `&]_[*@3 tabs], [@(0.0.255) const]_[_^Upp`:`:String^ S
tring]_[*@3 title]_, [*@4 ELEMENT1][@(0.0.255) `&]_[*@3 e1], [*@4 ESTYLE1][@(0.0.255) `&]_[*@3 s
t1]_, [*@4 ELEMENT2][@(0.0.255) `&]_[*@3 e2], [*@4 ESTYLE2][@(0.0.255) `&]_[*@3 st2])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:AddPropertiesTab`(ElementPropertiesDlgInterface`:`:VList`&`,TabCtrl`&`,const String`,ELEMENT1`&`,ESTYLE1`&`,ELEMENT2`&`,ESTYLE2`&`,ELEMENT3`&`,ESTYLE3`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT1], [@(0.0.255) class]_[*@4 ESTYLE1], 
[@(0.0.255) class]_[*@4 ELEMENT2], [@(0.0.255) class]_[*@4 ESTYLE2], 
[@(0.0.255) class]_[*@4 ELEMENT3], [@(0.0.255) class]_[*@4 ESTYLE3]>_[@(0.0.255) void]_[* Add
PropertiesTab]([_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:VList^ E
lementPropertiesDlgInterface`::VList][@(0.0.255) `&]_[*@3 elemPropDlgList], 
[_^Upp`:`:TabCtrl^ TabCtrl][@(0.0.255) `&]_[*@3 tabs], [@(0.0.255) const]_[_^Upp`:`:String^ S
tring]_[*@3 title]_, [*@4 ELEMENT1][@(0.0.255) `&]_[*@3 e1], [*@4 ESTYLE1][@(0.0.255) `&]_[*@3 s
t1]_, [*@4 ELEMENT2][@(0.0.255) `&]_[*@3 e2], [*@4 ESTYLE2][@(0.0.255) `&]_[*@3 st2]_, 
[*@4 ELEMENT3][@(0.0.255) `&]_[*@3 e3], [*@4 ESTYLE3][@(0.0.255) `&]_[*@3 st3])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphCtrl`_Base`:`:AddPropertiesTab`(ElementPropertiesDlgInterface`:`:VList`&`,TabCtrl`&`,const String`,ELEMENT1`&`,ESTYLE1`&`,ELEMENT2`&`,ESTYLE2`&`,ELEMENT3`&`,ESTYLE3`&`,ELEMENT4`&`,ESTYLE4`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT1], [@(0.0.255) class]_[*@4 ESTYLE1], 
[@(0.0.255) class]_[*@4 ELEMENT2], [@(0.0.255) class]_[*@4 ESTYLE2], 
[@(0.0.255) class]_[*@4 ELEMENT3], [@(0.0.255) class]_[*@4 ESTYLE3], 
[@(0.0.255) class]_[*@4 ELEMENT4], [@(0.0.255) class]_[*@4 ESTYLE4]>_[@(0.0.255) void]_[* Add
PropertiesTab]([_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:VList^ E
lementPropertiesDlgInterface`::VList][@(0.0.255) `&]_[*@3 elemPropDlgList], 
[_^Upp`:`:TabCtrl^ TabCtrl][@(0.0.255) `&]_[*@3 tabs], [@(0.0.255) const]_[_^Upp`:`:String^ S
tring]_[*@3 title]_, [*@4 ELEMENT1][@(0.0.255) `&]_[*@3 e1], [*@4 ESTYLE1][@(0.0.255) `&]_[*@3 s
t1]_, [*@4 ELEMENT2][@(0.0.255) `&]_[*@3 e2], [*@4 ESTYLE2][@(0.0.255) `&]_[*@3 st2]_, 
[*@4 ELEMENT3][@(0.0.255) `&]_[*@3 e3], [*@4 ESTYLE3][@(0.0.255) `&]_[*@3 st3]_, 
[*@4 ELEMENT4][@(0.0.255) `&]_[*@3 e4], [*@4 ESTYLE4][@(0.0.255) `&]_[*@3 st4])&]
[s2;%% Helper method used to build the properties editor dialog.&]
[s2;%% .&]
[s2;%% [%-*@3 elemPropDlgList] : list in which the properties dialog 
will be added&]
[s2;%% [%-*@3 tabs] : TabCtrl in which the tab must be added&]
[s2;%% [%-*@3 title] : tab title&]
[s2;%% [%-*@3 e1 / st1] : GraphElement 1 and it`'s associated style&]
[s2;%% [%-*@3 e2] / [%-*@3 st2] : GraphElement 2 and it`'s associated 
style&]
[s2;%% ...&]
[s3;%% &]
[s0;%% ]]