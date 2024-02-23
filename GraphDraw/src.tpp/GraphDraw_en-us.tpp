topic "5 - GraphDraw class";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 LocalStyle class]]}}&]
[s0; &]
[s0; [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 TYPES][3 , ][@(0.0.255)3 class][3 _][*@4;3 D
ERIVED][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:LocalStyle`:`:class: [@(0.0.255)3 class][3 _][*3 LocalStyle]&]
[s2;%% Helper class that manages the LocalStyle of GraphDraw instances&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphDraw class]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:class: [@(0.0.255) class]_[* CRTP`_E
mptyGraphDraw]_:_[@(0.0.255) public]_[*@3 SeriesGroup]_, [@(0.0.255) public]_[*@3 GraphEle
mentParent]&]
[s2;%% This class is the base class of GraphDraw, it contains all 
the common methods.&]
[s2;%% See [^topic`:`/`/GraphDraw`/src`/ClassHierarchy`$en`-us^ ClassHierarchy 
]for details on hinheritance tree.&]
[s2;%% &]
[s2;%% &]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:localChStyle: [_^Upp`:`:GraphDraw`_ns`:`:LocalStyle^ L
ocalStyle]_[* localChStyle]&]
[s2;%% Stores the local Style object that is used when layout Designer 
methods are used.&]
[s2;%% Note: Chameleon is bypassed when localStyle is not empty (means 
that user has set a specific style or modified the chameleon 
style)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:p1: [_^Upp`:`:Vector^ Vector]<_Poi
ntGraph_>_[* p1]&]
[s2;%% &]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Chameleon management]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:GetLocalChStyle`(`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* GetLocalChStyle]()&]
[s2;%% This method is here to allow Chameleon support while also 
allowing setting colors, fonts, ... in layout designer.&]
[s2;%% Until the first call to [%-* GetLocalChStyle(), ]the Chameleon 
style is active (which means that the global chameleon style 
is active and not modified).&]
[s2;%% After the first call to [%-* GetLocalChStyle()], it`'s a local 
instance of the style which is used : this means that you`'re 
widget is not  pointing to the global Chameleon style anymore.&]
[s2;%% &]
[s2;%% Returns the local chameleon Style used.&]
[s2;%% If the style hasn`'t been alocated yet, a new instance is 
created and initialised by copying the current Chameleon style 
used (so the result is the mix of Chameleon style `+ local modifications).&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:RequestChStyleLocal`(`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* RequestChStyleLocal]()&]
[s2;%% Forces the use of a LOCAL STYLE.&]
[s2; [%% This method encapsulates the use of ][* GetLocalChStyle() ]but 
hiding the template parameter.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:OverrideLocalChStyle`(const STYLE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) typename]_[*@4 STYLE]>_[@(0.0.255) void]_[* OverrideLocalChStyle]([@(0.0.255) c
onst]_[*@4 STYLE][@(0.0.255) `&]_[*@3 st])&]
[s2;%% If the local style is in use, this method clears the local 
style and sets style to [%-*@3 st].&]
[s2;%% Intended [@6 to be used only in GraphDraw child classes ](not 
in user code that uses the class) &]
[s3;%% &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* General methods]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:DisableGE`(const T`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[@(0.0.255) void]_[* DisableGE]([@(0.0.255) const]_[*@4 T
][@(0.0.255) `&]_[*@3 ge])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:DisableGE`(const Upp`:`:GraphDraw`_ns`:`:GraphElement`*`): [@(0.0.255) v
oid]_[* DisableGE]([@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:GraphElement^ GraphEle
ment][@(0.0.255) `*]_[*@3 ge])&]
[s2;%% Disables Graph Element [%-*@3 ge] : which means that [%-*@3 ge] 
will not be displayed on graph nor in properties menu.&]
[s2;%% [_ Note] : [*@6 This is a one way call], once disabled, [%-*@3 ge] 
cannot be enabled again. This method is intented for configuring 
simplified versions of complex Graphs (make one complex Graph 
and then disable the unneeded Graph Elements).&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetGDModify`(`): [@(0.0.255) virtu
al] [@(0.0.255) void]_[* SetGDModify]()&]
[s2;%% Indicates that the control has been modified (serves as a 
replacement for [^topic`:`/`/CtrlCore`/src`/Ctrl`_en`-us`#Ctrl`:`:SetModify`(`)^ Ct
rl`::SetModify()] when in headless mode, therefor without using 
GraphCtrl package )&]
[s2;%% Intended to be used only in GraphDraw package classes that 
need to indicate the Ctrl has been modified.&]
[s2;%% Default implementation available in GraphDraw package is empty. 
The real implementation is available in GraphCtrl package.&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetDrawMode`(DrawMode`): [*@4 DERI
VED][@(0.0.255) `&]_[* SetDrawMode](DrawMode_[*@3 m])&]
[s2;%% Set the drawing mode to be used&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:GetDrawMode`(`): [@(0.0.255) virtu
al] DrawMode_[* GetDrawMode]()&]
[s2;%% Returns the drawing mode used&]
[s2;%% [*_ NB:] Part of [^topic`:`/`/GraphDraw`/src`/GraphElementParent`$en`-us`#GraphElementParent`:`:class^ G
raphElementParent ]interface&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddXConverter`(Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`*`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* AddXConverter]([_^CoordinateConverter^ CoordinateConverter
][@(0.0.255) `*]_[*@3 conv])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddYConverter`(Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`*`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* AddYConverter]([_^CoordinateConverter^ CoordinateConverter
][@(0.0.255) `*]_[*@3 conv])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddXConverter`(Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`&`): [@(0.0.255) v
oid]_[* AddXConverter]([_^Upp`:`:GraphDraw`_ns`:`:CoordinateConverter^ CoordinateConv
erter][@(0.0.255) `&]_[*@3 conv])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddYConverter`(Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`&`): [@(0.0.255) v
oid]_[* AddYConverter]([_^Upp`:`:GraphDraw`_ns`:`:CoordinateConverter^ CoordinateConv
erter][@(0.0.255) `&]_[*@3 conv])&]
[s2;%% [%-*@3 conv] : CoordinateConverter instance to add&]
[s2;%% Adds a CoordinateConverter instance to the list of the ones 
managed by GraphDraw.&]
[s2;%% Plotting can then use this CoordinateConverter for plotting.&]
[s2;%% [@6 GraphDraw does not take the ownership] of the CoordinateConverter 
instance so it has to be managed elsewhere.&]
[s2;%% It`'s main usage is for GraphDraw child classes and to add 
more axis.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetCurrentXConverter`(int`): [@(0.0.255) v
oid]_[* SetCurrentXConverter]([@(0.0.255) int]_[*@3 n])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetCurrentYConverter`(int`): [@(0.0.255) v
oid]_[* SetCurrentYConverter]([@(0.0.255) int]_[*@3 n])&]
[s2;%%  [%-*@3 n] : index of CoordinateConverter to use&]
[s2;%% Set the CoordinateConverter that will be used when adding 
a series.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:GetXCoordConverter`(int`): [_^CoordinateConverter^ C
oordinateConverter][@(0.0.255) `&]_[* GetXCoordConverter]([@(0.0.255) int]_[*@3 N][@(0.0.255) `=
`-][@3 1])&]
[s2;%% Returns the [*@3 N][` th] [* X] coordinate converter&]
[s2;%% [%- if ][%-*@3 N] < 0 : returns current coordinate converter&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:GetYCoordConverter`(int`): [_^CoordinateConverter^ C
oordinateConverter][@(0.0.255) `&]_[* GetYCoordConverter]([@(0.0.255) int]_[*@3 N][@(0.0.255) `=
`-][@3 1])&]
[s2;%% Returns the [*@3 N][` th] [* Y ]coordinate converter&]
[s2;%% [%- if ][%-*@3 N] < 0 : returns current coordinate converter&]
[s3;%% &]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetPlotBackgroundStyle`(T`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 DERIVED][@(0.0.255) `&]_[* SetPlotBackgroundStyl
e]([*@4 T]_[*@3 c])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:SetCtrlBackgroundStyle`(T`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 DERIVED][@(0.0.255) `&]_[* SetCtrlBackgroundStyl
e]([*@4 T]_[*@3 c])&]
[s2;%% `-`-`-`-`- TODO  move this somewhere else `-`-`-`-`-&]
[s2;%% Sets the background style of Plot or whole Ctrl area. [%-*@3 `'c`' 
]can be anything that is accepted by [^topic`:`/`/CtrlCore`/srcdoc`/AboutChameleon`$en`-us^ C
hameleon] ChPaint() method : &]
[s2;i150;O0;%% Color&]
[s2;i150;O0;%% Image (hot spots are used)&]
[s2;i150;O0;%% ...&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:FitToData`(FitToDataStrategy`): [@(0.0.255) v
oid]_[* FitToData](FitToDataStrategy_[*@3 fitStrategy][@(0.0.255) `=]ALL`_SERIES)&]
[s2;%%  [%-*@3 fitStrategy] .&]
[s3;%% &]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* GraphElements management]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:updateSizes`(const int`): [@(0.0.255) v
oid]_[* updateSizes](_[@(0.0.255) const]_[@(0.0.255) int]_[*@3 scale]_`=_[@3 1]_)&]
[s2;%% [*@(128.0.255) For internal use only]&]
[s2;%% Updates all the stacked elements and Plotting area sizes.&]
[s2;%% This method [@6 MUST BE CALLED], if a GraphElement is added.&]
[s2;%% It manages the following aspects :&]
[s2;i150;O0;%% GraphElements position/size calculation&]
[s2;i150;O0;%% Plot area position/size calculation&]
[s2;i150;O0;%% Manages the [*c@(128.0.255) NEGATIVE PRIORITY] cases&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AppendElementToRect`(Upp`:`:GraphDraw`_ns`:`:GraphElement`&`,Upp`:`:GraphDraw`_ns`:`:RectScreen`&`,const int`)const: [@(0.0.255) v
oid]_[* AppendElementToRect]([_^Upp`:`:GraphDraw`_ns`:`:GraphElement^ GraphElement][@(0.0.255) `&
]_[*@3 element], [_^Upp`:`:GraphDraw`_ns`:`:RectScreen^ RectScreen][@(0.0.255) `&]_[*@3 f
romRect], [@(0.0.255) const]_[@(0.0.255) int]_[*@3 scale])_[@(0.0.255) const]&]
[s2;%% [*@6 For internal use only]&]
[s2;%% Appends a GraphElement to [%-*@3 fromRect]. It sets the [%-*@3 element 
]size (only one side of the size is valid depending on the side 
on which the GraphElement has been added) &]
[s2;%% The [%-*@3 fromRect] size is modified to take in account the 
[%-*@3 element ]added.&]
[s2;%% [*_ NB][*  :] the list of GraphElements have to be sorted by StackingPriority 
before using [%-* AppendElementToRect().].&]
[s3;%% &]
[s4;%% &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:CreateElement`(int`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T], [@(0.0.255) int]_[*@4 POS`_OF`_GRAPH]>_[*@4 T][@(0.0.255) `&
]_[* CreateElement]([@(0.0.255) int]_[*@3 elementWidth], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:CreateElement`(ElementPosition`,int`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* CreateElement](ElementPosit
ion_[*@3 pos], [@(0.0.255) int]_[*@3 elementWidth], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:CreateElement1`(int`,int`,P1`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T], [@(0.0.255) int]_[*@4 POS`_OF`_GRAPH], 
[@(0.0.255) class]_[*@4 P1]>_[*@4 T][@(0.0.255) `&]_[* CreateElement1]([@(0.0.255) int]_[*@3 el
ementWidth], [@(0.0.255) int]_[*@3 stackPrio], [*@4 P1][@(0.0.255) `&]_[*@3 p1]_)&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:CreateElement2`(int`,int`,P1`&`,P2`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T], [@(0.0.255) int]_[*@4 POS`_OF`_GRAPH], 
[@(0.0.255) class]_[*@4 P1], [@(0.0.255) class]_[*@4 P2]>_[*@4 T][@(0.0.255) `&]_[* CreateEleme
nt2]([@(0.0.255) int]_[*@3 elementWidth], [@(0.0.255) int]_[*@3 stackPrio], 
[*@4 P1][@(0.0.255) `&]_[*@3 p1], [*@4 P2][@(0.0.255) `&]_[*@3 p2]_)&]
[s7;i512;~~~.800;%% [%-*@3 p1][%- , ][%-*@3 p2] : parameters needed by constructor 
of <T> class.&]
[s7;i512;~~~.800;%% [%-*@3 stackPrio][%-  ]:Used to manage the stacking 
order of GraphElements (can be interpreted as the distance from 
the graph). See[^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphElement Stacks^  
stacking details].&]
[s7;i512;~~~.800; [*@3 elementWidth : ]&]
[s7;i512;~~~.800; [*@3 pos : ]&]
[s2;%% Same as [%-*^topic`:`/`/GraphDraw`/src`/CRTP`_EmptyGraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:CreateElement`(int`,int`)^ C
reateElement()] but with additionnal parameters needed by GraphElement 
contructor&]
[s3;%% &]
[s4; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddElement`(ElementPosition`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddElement](ElementPosition
_[*@3 pos], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddElement`(ElementPosition`,int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddElement](ElementPosition
_[*@3 pos], [@(0.0.255) int]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], 
[@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T], [@(0.0.255) int]_[*@4 POS`_OF`_GRAPH]>_[*@4 T][@(0.0.255) `&
]_[* AddElement]([*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T], [@(0.0.255) int]_[*@4 POS`_OF`_GRAPH]>_[*@4 T][@(0.0.255) `&
]_[* AddElement]([@(0.0.255) int]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], 
[@(0.0.255) int]_[*@3 stackPrio])&]
[s2;%% [%-*@3 elementWidth] :&]
[s2;%% [%-*@3 v] : [^topic`:`/`/GraphDraw`/src`/2`_GraphElementFrame`$en`-us`#GraphElementFrame`:`:class^ G
raphElement ]instance to add&]
[s2;%% [%-*@3 stackPrio] :&]
[s2;%% Add a [^topic`:`/`/GraphDraw`/src`/2`_GraphElementFrame`$en`-us`#GraphElementFrame`:`:class^ G
raphElement ]to one of the [^topic`:`/`/GraphDraw`/src`/1`_GraphDraw`_basics`$en`-us^ f
ive stacks available].&]
[s2;%% When using this method the wonership of the GraphElement is 
not managed by GraphDraw class.&]
[s3;%% &]
[s4; &]
[s2;%%  [%-*@3 pos] [%-*@3 elementWidth] [%-*@3 v] [%-*@3 stackPrio] .&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddLeftElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddLeftElement]([*@4 T][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddRightElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddRightElement]([*@4 T][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddTopElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddTopElement]([*@4 T][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddBottomElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddBottomElement]([*@4 T][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddFloatElement`(T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddFloatElement]([*@4 T][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s2;%% Same as [%-*^topic`:`/`/GraphDraw`/src`/3`_GraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:AddElement`(T`&`,int`)^ A
ddElement()].&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddLeftElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddLeftElement]([@(0.0.255) i
nt]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddRightElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddRightElement]([@(0.0.255) i
nt]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddTopElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddTopElement]([@(0.0.255) in
t]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddBottomElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddBottomElement]([@(0.0.255) i
nt]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddFloatElement`(int`,T`&`,int`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* AddFloatElement]([@(0.0.255) i
nt]_[*@3 elementWidth], [*@4 T][@(0.0.255) `&]_[*@3 v], [@(0.0.255) int]_[*@3 stackPrio])&]
[s2;%% Same as [%-*^topic`:`/`/GraphDraw`/src`/3`_GraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:AddElement`(T`&`,int`)^ A
ddElement()].&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:`_ctrlRect: [_^Rect^ Rect]_[* `_ctrl
Rect]&]
[s2;%% Rect of the whole Graph (Plot area `+ all GraphElements surrounding)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:`_plotRect: [_^Rect^ Rect]_[* `_plot
Rect]&]
[s2;%% Rect of the graph plot area ( inside the `_ctrlRect )&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:`_PlotDrawImage: [_^Image^ Image]_
[* `_PlotDrawImage]&]
[s2;%% Image of the drawn Plot data (and only that).&]
[s2;%% This Image is used to store data plotting result and therefor 
speed`-up drawing of Graph when plot data hasn`'t changed. In 
this case the plot image is just drawn on the Graph result without 
really processing the plot data&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Undo/Redo management methods]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:AddUndoAction`(Upp`:`:UndoStackData`&`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* AddUndoAction]([_^GraphUndoData^ GraphUndoData][@(0.0.255) `&
]_[*@3 CB])&]
[s2;%%  [%-*@3 CB] : GraphUndoData object containg the Undo/Redo actions.&]
[s2;%% Undo/Redo is accomplished by using a stack of Undo/Redo objects.&]
[s2;%% See [^topic`:`/`/GraphDraw`/src`/GraphUndo`$en`-us`#GraphUndo`:`:class^ GraphUnd
o] for more details.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:MakeRestoreGraphSizeCB`(`): [@(0.0.255) v
irtual] [_^Callback^ Callback]_[* MakeRestoreGraphSizeCB]()&]
[s2;%% Returns a Callback that, when executed, will set the Graph 
size settings identical to the current settings.&]
[s2;%% This is useful for UNDO / REDO management&]
[s2;%% NB: This method is part of the [^topic`:`/`/GraphDraw`/src`/GraphElementParent`$en`-us`#GraphElementParent`:`:MakeRestoreGraphSizeCB`(`)^ G
raphElementParent ]interface&]
[s3; &]
[s0;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:Undo`(`): [@(0.0.255) void]_[* Undo](
)&]
[s2;%% Execute the most recent Undo action&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:Redo`(`): [@(0.0.255) void]_[* Redo](
)&]
[s2;%% Execute the most recent Redo action&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Painting methods]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:RefreshFromChild`(RefreshStrategy`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* RefreshFromChild](_RefreshStrategy_[*@3 doFastPaint]_)&]
[s2;%%  [%-*@3 doFastPaint] :&]
[s2;%% Method called from child GraphElements of GraphDraw when a 
Refresh is requested by the child&]
[s2;%% [*_ NB:] Part of [^topic`:`/`/GraphDraw`/src`/GraphElementParent`$en`-us`#GraphElementParent`:`:class^ G
raphElementParent ]interface&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:Paint`(T`&`,int`): [@(0.0.255) tem
plate]_<[@(0.0.255) class]_[*@4 T]>_[@(0.0.255) void]_[* Paint]([*@4 T][@(0.0.255) `&]_[*@3 dw],
 [@(0.0.255) int]_[*@3 scale])&]
[s2;%% [%-*@3 dw] :&]
[s2;%% [%-*@3 scale] :&]
[s2;%% This method paints the complete GraphDraw ( it calls [%-^topic`:`/`/GraphDraw`/src`/3`_GraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:PaintPlotData`(T`&`,int`)^ P
aintPlotData()] to plot the data points ).&]
[s2;%% This method also manages the following cache related points:&]
[s2;i150;O0;%% GraphDraw background image caching&]
[s2;i150;O0;%% Plot area background image caching&]
[s2;i150;O0;%% Plotted data image caching&]
[s2;%% These points allow to speed up the drawing of GraphDraw when 
necessary&]
[s3;%% &]
[s0;%% &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s0;%% &]
[s0;%% &]
[s0;%% ]]